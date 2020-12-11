#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

namespace ml_log::web_server {

class QueryController : public drogon::HttpController<QueryController, false> {
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(QueryController::test, "/query/{p1}", Get);
    METHOD_LIST_END

    void test(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              const std::string &p1) const;
};

} // namespace ml_log::web_server
