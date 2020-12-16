#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

namespace ml_log::web_server {

class QueryController : public drogon::HttpController<QueryController, false> {
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(QueryController::queryXYItems, "/api/query/xy-items/{key}",
                  Get);
    ADD_METHOD_TO(QueryController::queryKeys, "/api/query/keys", Get);
    METHOD_LIST_END

    void queryXYItems(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      const std::string &key) const;
    void
    queryKeys(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback) const;
};

} // namespace ml_log::web_server
