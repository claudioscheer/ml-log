#include "QueryController.hpp"
#include "../../ml_log/ml_log.cpp"
#include <iostream>

namespace ml_log::web_server {

void QueryController::queryXYItems(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &applicationName, const std::string &redisHost,
    const std::string &redisPort, const std::string &redisDatabaseIndex) const {

    ml_log::redis::RedisCommands *redisCommands =
        ml_log::redis::RedisCommands::getInstance(
            applicationName, redisHost, std::stoi(redisPort),
            std::stoi(redisDatabaseIndex));
    std::vector<std::string> keys = redisCommands->getKeys();

    Json::Reader reader;

    Json::Value json;
    for (auto key : keys) {
        Json::Value keyObject;
        keyObject["key"] = key;

        std::string xyItems = redisCommands->getXYArray(key);
        Json::Value items;
        reader.parse(xyItems.c_str(), items);
        keyObject["items"] = items;

        json.append(keyObject);
    }

    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->addHeader("Access-Control-Allow-Origin", "*");
    assert(resp->jsonObject().get());
    callback(resp);
}

} // namespace ml_log::web_server
