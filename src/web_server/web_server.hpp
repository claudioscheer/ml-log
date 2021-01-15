#include "controllers/QueryController.cpp"
#include <drogon/drogon.h>
#include <filesystem>
#include <iostream>

using namespace std;
using namespace drogon;

namespace ml_log::web_server {

class WebServer {
  public:
    // Attributes.
    string web_client_root = "./web/build";

    // Methods.
    void startWebServer();

    // Constructors.
    explicit WebServer(int port) : _port(port) {}

  private:
    int _port;
};

void WebServer::startWebServer() {
    app().addListener("0.0.0.0", this->_port);

    app().setDocumentRoot(this->web_client_root);

    auto queryController = std::make_shared<QueryController>();
    app().registerController(queryController);

    app().run();
}

} // namespace ml_log::web_server
