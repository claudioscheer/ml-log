#pragma once
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
    explicit RedisCommands(std::string applicationName, std::string redisHost,
                           int redisPort, int redisDatabaseIndex) {
        this->connect(applicationName, redisHost, redisPort,
                      redisDatabaseIndex);
    }

    static RedisCommands *getInstance(std::string applicationName,
                                      std::string redisHost, int redisPort,
                                      int redisDatabaseIndex) {
        if (_instance == NULL) {
            _instance = new RedisCommands(applicationName, redisHost, redisPort,
                                          redisDatabaseIndex);
        }
        return _instance;
    }

    ~RedisCommands() { delete _instance; }

  private:
    // Attributes.
    static RedisCommands *_instance;
    std::string _applicationName;

    // Methods.
    void connect(std::string applicationName, std::string redisHost,
                 int redisPort, int redisDatabaseIndex);
    std::string processKey(std::string key, int addApplicationName) {
        std::string suffix = "-" + this->_applicationName;
        if (addApplicationName) {
            return key + suffix;
        } else {
            int hyphenPosition = key.find('-');
            return key.replace(key.begin() + hyphenPosition, key.end(), "");
        }
    }
};

RedisCommands *RedisCommands::_instance = NULL;

void RedisCommands::connect(std::string applicationName, std::string redisHost,
                            int redisPort, int redisDatabaseIndex) {
    this->_applicationName = applicationName;
    this->client.connect(
        redisHost, redisPort,
        [&](const std::string &host, std::size_t port,
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
        this->client.select(redisDatabaseIndex);
    this->client.sync_commit();
    std::cout << "Select database: " << replyFuture.get() << "." << std::endl;

    // TODO: Make sure that application do not exists in database.
}

void RedisCommands::appendXYItem(std::string key, XYType item) {
    std::string processedKey = this->processKey(key, 1);
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
    std::string processedKey = this->processKey(key, 1);

    std::future<cpp_redis::reply> replyFuture =
        this->client.send({"JSON.GET", processedKey});
    this->client.sync_commit();

    return replyFuture.get().as_string();
}

std::vector<std::string> RedisCommands::getKeys() {
    std::future<cpp_redis::reply> replyFuture =
        this->client.keys("*" + this->_applicationName);
    this->client.sync_commit();

    std::vector<cpp_redis::reply> replies = replyFuture.get().as_array();
    std::vector<std::string> keys;
    keys.resize(replies.size());

    std::transform(
        replies.begin(), replies.end(), keys.begin(),
        [&](cpp_redis::reply r) { return this->processKey(r.as_string(), 0); });

    return keys;
}

} // namespace ml_log::redis
