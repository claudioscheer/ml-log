#include "../utils.hpp"
#include "structs.hpp"
#include <cpp_redis/cpp_redis>
#include <future>
#include <iostream>
#include <string>

// TODO: Support a pipeline of Redis commands (appendXYItem, for example).

namespace ml_log::redis {

class RedisCommands {
  public:
    // Attributes.
    cpp_redis::client client;

    // Methods.
    void appendXYItem(std::string key, XYType item);
    std::string getXYArray(std::string key);
    std::vector<std::string> getKeys();

    // Constructors.
    explicit RedisCommands() {
        this->_config = ml_log::loadConfig();
        this->connect();
    }

    static RedisCommands *getInstance() {
        if (_instance == NULL) {
            _instance = new RedisCommands();
        }
        return _instance;
    }

    ~RedisCommands() { delete _instance; }

  private:
    // Attributes.
    static RedisCommands *_instance;
    ml_log::Config _config;

    // Methods.
    void connect();
    std::string processKey(std::string key) {
        return key + "-" + this->_config.applicationName;
    }
};

RedisCommands *RedisCommands::_instance = NULL;

void RedisCommands::connect() {
    this->client.connect(
        this->_config.redisHost, this->_config.redisPort,
        [](const std::string &host, std::size_t port,
           cpp_redis::connect_state status) {
            if (status == cpp_redis::connect_state::dropped) {
                std::cout << "Redis client disconnected from " << host << ":"
                          << port << "." << std::endl;
            } else if (status == cpp_redis::connect_state::ok) {
                std::cout << "Redis client connected to " << host << ":" << port
                          << "." << std::endl;
            }
        });

    std::future<cpp_redis::reply> replyFuture =
        this->client.select(this->_config.redisDatabaseIndex);
    this->client.sync_commit();
    std::cout << "Select database: " << replyFuture.get() << "." << std::endl;

    // TODO: Make sure that application do not exists in database.
}

void RedisCommands::appendXYItem(std::string key, XYType item) {
    std::string processedKey = this->processKey(key);
    std::future<cpp_redis::reply> replyFuture =
        this->client.exists({processedKey});
    this->client.sync_commit();
    if (!replyFuture.get().as_integer()) {
        replyFuture = this->client.send({"JSON.SET", processedKey, ".", "[]"});
    }

    std::string json = "{\"x\":";
    json += std::to_string(item.x);
    json += ",\"y\":";
    json += std::to_string(item.y);
    json += "}";

    replyFuture =
        this->client.send({"JSON.ARRAPPEND", processedKey, ".", json});
    this->client.sync_commit();
}

std::string RedisCommands::getXYArray(std::string key) {
    std::string processedKey = this->processKey(key);

    std::future<cpp_redis::reply> replyFuture =
        this->client.send({"JSON.GET", processedKey, "INDENT", " ", "NEWLINE",
                           "\n", "SPACE", " "});
    this->client.sync_commit();

    return replyFuture.get().as_string();
}

std::vector<std::string> RedisCommands::getKeys() {
    std::future<cpp_redis::reply> replyFuture =
        this->client.keys("*" + this->_config.applicationName);
    this->client.sync_commit();

    std::vector<cpp_redis::reply> replies = replyFuture.get().as_array();
    std::vector<std::string> keys;
    keys.resize(replies.size());

    std::transform(replies.begin(), replies.end(), keys.begin(),
                   [](cpp_redis::reply r) { return r.as_string(); });

    return keys;
}

} // namespace ml_log::redis
