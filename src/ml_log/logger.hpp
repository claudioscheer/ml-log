#include "../web_server/web_server.hpp"
#include "redis_commands.hpp"
#include "structs.hpp"
#include <iostream>
#include <string>

namespace ml_log {

class Logger {
  public:
    // Methods.
    void appendXYItem(std::string key, XYType item);
    void startWebServer(int port, std::string web_client_folder);

    // Constructors.
    explicit Logger(std::string applicationName, std::string redisHost,
                    int redisPort, int redisDatabaseIndex) {
        this->_redisCommands = ml_log::redis::RedisCommands::getInstance(
            applicationName, redisHost, redisPort, redisDatabaseIndex);
    }

  private:
    // Attributes.
    ml_log::redis::RedisCommands *_redisCommands;
    ml_log::web_server::WebServer *_webServer;
};

void ml_log::Logger::startWebServer(int port, std::string web_client_folder) {
    if (!this->_webServer) {
        this->_webServer =
            new ml_log::web_server::WebServer(port, web_client_folder);
        this->_webServer->startWebServer();
    } else {
        std::runtime_error(
            "error: web server cannot be started more than once.");
    }
}

} // namespace ml_log
