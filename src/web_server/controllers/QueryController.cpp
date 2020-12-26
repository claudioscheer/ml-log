#include "QueryController.hpp"
#include "../../ml_log/ml_log.cpp"
#include <iostream>

namespace ml_log::web_server {

void QueryController::queryKeys(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &applicationName, const std::string &redisHost,
    const std::string &redisPort, const std::string &redisDatabaseIndex) const {

    ml_log::redis::RedisCommands *redisCommands =
        ml_log::redis::RedisCommands::getInstance(
            applicationName, redisHost, std::stoi(redisPort),
            std::stoi(redisDatabaseIndex));
    std::vector<std::string> keys = redisCommands->getKeys();

    Json::Value json;
    for (auto key : keys) {
        json.append(key);
    }

    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->addHeader("Access-Control-Allow-Origin", "*");
    assert(resp->jsonObject().get());
    callback(resp);
}

void QueryController::queryXYItems(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &key) const {

    /* ml_log::redis::RedisCommands *redisCommands = */
    /*     ml_log::redis::RedisCommands::getInstance(); */
    /* std::string response = redisCommands->getXYArray(key); */

    /* Json::Value json; */
    /* Json::Reader reader; */
    /* reader.parse(response.c_str(), json); */

    /* auto resp = HttpResponse::newHttpJsonResponse(json); */
    /* assert(resp->jsonObject().get()); */
    /* callback(resp); */
}

} // namespace ml_log::web_server
