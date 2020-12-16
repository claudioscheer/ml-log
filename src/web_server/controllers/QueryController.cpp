#include "QueryController.hpp"
#include "../../ml_log/ml_log.cpp"

namespace ml_log::web_server {

void QueryController::queryXYItems(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &key) const {

    ml_log::redis::RedisCommands *redisCommands =
        ml_log::redis::RedisCommands::getInstance();
    std::string response = redisCommands->getXYArray(key);

    Json::Value json;
    Json::Reader reader;
    reader.parse(response.c_str(), json);

    auto resp = HttpResponse::newHttpJsonResponse(json);
    assert(resp->jsonObject().get());
    callback(resp);
}

void QueryController::queryKeys(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {

    ml_log::redis::RedisCommands *redisCommands =
        ml_log::redis::RedisCommands::getInstance();
    std::vector<std::string> keys = redisCommands->getKeys();

    Json::Value json;
    for (auto key : keys) {
        json.append(key);
    }

    auto resp = HttpResponse::newHttpJsonResponse(json);
    assert(resp->jsonObject().get());
    callback(resp);
}

} // namespace ml_log::web_server
