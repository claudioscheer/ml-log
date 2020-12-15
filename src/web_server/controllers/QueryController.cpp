#include "QueryController.hpp"
#include "../../ml_log/ml_log.cpp"

namespace ml_log::web_server {

void QueryController::test(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &p1) const {

    ml_log::redis::RedisCommands redisCommands;
    std::string response = redisCommands.getXYArray("train");

    Json::Value json;
    Json::Reader reader;
    reader.parse(response.c_str(), json);

    auto resp = HttpResponse::newHttpJsonResponse(json);
    assert(resp->jsonObject().get());
    callback(resp);
}

} // namespace ml_log::web_server
