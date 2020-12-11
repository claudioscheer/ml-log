#include "QueryController.hpp"

namespace ml_log::web_server {

void QueryController::test(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    const std::string &p1) const {
    Json::Value json;
    json["parameter"] = p1;
    Json::Value array;
    for (int i = 0; i < 5; ++i) {
        Json::Value user;
        user["id"] = i;
        array.append(user);
    }
    json["rows"] = array;
    auto resp = HttpResponse::newHttpJsonResponse(json);
    assert(resp->jsonObject().get());
    callback(resp);
}

} // namespace ml_log::web_server
