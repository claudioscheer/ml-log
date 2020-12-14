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
    int databaseIndex = 0;

    // Methods.
    void appendXYItem(std::string key, XYType item);

    // Constructors.
    explicit RedisCommands(std::string redisHost, int redisPort,
                           std::string applicationName)
        : _redisHost(redisHost), _redisPort(redisPort),
          _applicationName(applicationName) {
        this->connect();
    }

  private:
    // Attributes.
    std::string _redisHost;
    int _redisPort;
    std::string _applicationName;

    // Methods.
    void connect();
    std::string processKey(std::string key) {
        return key + "-" + this->_applicationName;
    }
};

void RedisCommands::connect() {
    this->client.connect(
        this->_redisHost, this->_redisPort,
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

    std::future<cpp_redis::reply> reply_future =
        this->client.select(this->databaseIndex);
    this->client.sync_commit();
    std::cout << "Select database: " << reply_future.get() << "." << std::endl;

    // TODO: Make sure that application do not exists in database.
}

void RedisCommands::appendXYItem(std::string key, XYType item) {
    std::string processedKey = this->processKey(key);
    std::future<cpp_redis::reply> reply_future =
        this->client.exists({processedKey});
    this->client.sync_commit();
    if (!reply_future.get().as_integer()) {
        reply_future = this->client.send({"JSON.SET", processedKey, ".", "[]"});
    }

    std::string json = "{\"x\":";
    json += std::to_string(item.x);
    json += ",\"y\":";
    json += std::to_string(item.y);
    json += "}";

    reply_future =
        this->client.send({"JSON.ARRAPPEND", processedKey, ".", json});
    this->client.sync_commit();
    std::cout << json << reply_future.get() << std::endl;
}

} // namespace ml_log::redis
