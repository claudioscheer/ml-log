#include "web_server.cpp"
#include <iostream>

int main() {
    ml_log::web_server::WebServer webServer(3005);
    webServer.startWebServer();

    return 0;
}
