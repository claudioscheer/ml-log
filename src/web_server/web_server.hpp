#include "controllers/QueryController.cpp"
#include <drogon/drogon.h>
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;
using namespace drogon;

namespace ml_log::web_server {

class WebServer {
  public:
    // Methods.
    void startWebServer();

    // Constructors.
    explicit WebServer(int port, string web_client_folder) {
        this->_port = port;
        this->_web_client_folder = web_client_folder;
    }

  private:
    int _port;
    string _web_client_folder;
};

void WebServer::startWebServer() {
    app().addListener("0.0.0.0", this->_port);

    app().setDocumentRoot(this->_web_client_folder);

    auto queryController = std::make_shared<QueryController>();
    app().registerController(queryController);

    app().run();
}

} // namespace ml_log::web_server
