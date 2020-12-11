#include "QueryController.cpp"
#include <drogon/drogon.h>
#include <iostream>

using namespace std;
using namespace drogon;

namespace ml_log::web_server {

void startWebServer(int port) {
    app().addListener("0.0.0.0", port);
    app().setDocumentRoot("./web/build");

    auto queryController = std::make_shared<QueryController>();
    app().registerController(queryController);

    app().run();
}

} // namespace ml_log::web_server
