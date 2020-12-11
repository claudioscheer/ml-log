#include "controllers/QueryController.cpp"
#include <drogon/drogon.h>
#include <iostream>

using namespace std;
using namespace drogon;

namespace ml_log::web_server {

class WebServer {
  public:
    void startWebServer();
    WebServer(int port);

  private:
    int _port;
};

WebServer::WebServer(int port) { this->_port = port; }

void WebServer::startWebServer() {
    app().addListener("0.0.0.0", this->_port);
    app().setDocumentRoot("./web/build");

    auto queryController = std::make_shared<QueryController>();
    app().registerController(queryController);

    app().run();
}

} // namespace ml_log::web_server
