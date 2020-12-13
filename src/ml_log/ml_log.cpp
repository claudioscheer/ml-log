#include <cpp_redis/cpp_redis>
#include <iostream>
#include <string>

namespace ml_log::redis {

struct AppendItemType {
    std::string key;
    std::string json;
};

class RedisCommands {
  public:
    // Attributes.
    cpp_redis::client client;

    // Methods.
    void appendItem(AppendItemType item);

    // Constructors.
    explicit RedisCommands(std::string redisHost, int redisPort)
        : _redisHost(redisHost), _redisPort(redisPort) {
        this->connect();
    }

  private:
    // Attributes.
    std::string _redisHost;
    int _redisPort;

    // Methods.
    void connect();
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
}

void RedisCommands::appendItem(AppendItemType appendType) {
    std::cout << appendType.key << std::endl;
}

} // namespace ml_log::redis
