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

    // Constructors.
    explicit RedisCommands() {
        this->config = ml_log::loadConfig();
        this->connect();
    }

  private:
    // Attributes.
    ml_log::Config config;

    // Methods.
    void connect();
    std::string processKey(std::string key) {
        return key + "-" + this->config.applicationName;
    }
};

void RedisCommands::connect() {
    this->client.connect(
        this->config.redisHost, this->config.redisPort,
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
        this->client.select(this->config.redisDatabaseIndex);
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

} // namespace ml_log::redis
