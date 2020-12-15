#ifndef ML_LOG_UTILS
#define ML_LOG_UTILS

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace ml_log {

struct Config {
    std::string applicationName;
    std::string redisHost;
    int redisPort;
    int redisDatabaseIndex;
};

Config loadConfig() {
    // TODO: Cache the file loaded. Avoid parsing the file every time this
    // function is called.
    char *mlLogConfigEnv = std::getenv("ML_LOG_CONFIG");
    if (mlLogConfigEnv == NULL) {
        throw std::runtime_error(
            "Environment variable ML_LOG_CONFIG is not defined. See more here: "
            "https://github.com/dl4all/ml-log#configuration-file.");
    }

    std::filesystem::path filePath = std::string(mlLogConfigEnv);

    Config config;
    std::fstream fileStream;
    fileStream.open(filePath);

    std::string line;
    while (std::getline(fileStream, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '=')) {
            std::string value;
            if (std::getline(lineStream, value)) {
                if (key == "applicationName") {
                    config.applicationName = value;
                } else if (key == "redisHost") {
                    config.redisHost = value;
                } else if (key == "redisPort") {
                    config.redisPort = std::stoi(value);
                } else if (key == "redisDatabaseIndex") {
                    config.redisDatabaseIndex = std::stoi(value);
                }
            }
        }
    }

    return config;
}

} // namespace ml_log

#endif
