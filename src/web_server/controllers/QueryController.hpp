#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

namespace ml_log::web_server {

class QueryController : public drogon::HttpController<QueryController, false> {
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(QueryController::queryKeys,
                  "/api/query/"
                  "keys?applicationName={1}&redisHost={2}&redisPort={3}&"
                  "redisDatabaseIndex={4}",
                  Get);
    ADD_METHOD_TO(QueryController::queryXYItems, "/api/query/xy-items/{key}",
                  Get);
    METHOD_LIST_END

    void queryKeys(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   const std::string &applicationName,
                   const std::string &redisHost, const std::string &redisPort,
                   const std::string &redisDatabaseIndex) const;

    void queryXYItems(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      const std::string &key) const;
};

} // namespace ml_log::web_server
