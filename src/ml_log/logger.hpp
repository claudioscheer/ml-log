#include "redis_commands.hpp"
#include "structs.hpp"
#include <iostream>
#include <string>

namespace ml_log {

class Logger {
  public:
    // Methods.
    void appendXYItem(std::string key, XYType item);

    // Constructors.
    explicit Logger(std::string applicationName, std::string redisHost,
                    int redisPort, int redisDatabaseIndex) {
        this->_redisCommands = ml_log::redis::RedisCommands::getInstance(
            applicationName, redisHost, redisPort, redisDatabaseIndex);
    }

  private:
    // Attributes.
    ml_log::redis::RedisCommands *_redisCommands;
};

} // namespace ml_log
