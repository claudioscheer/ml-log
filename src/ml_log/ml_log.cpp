#include <cpp_redis/cpp_redis>
#include <iostream>

using namespace std;

namespace ml_log::redis {

class RedisCommands {
  public:
    RedisCommands(string redis_host, int redis_port);

  private:
    string _redis_host;
    int _redis_port;
};

RedisCommands::RedisCommands(string redis_host, int redis_port) {
    this->_redis_host = redis_host;
    this->_redis_port = redis_port;
}

} // namespace ml_log::redis
