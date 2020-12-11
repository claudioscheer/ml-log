#include "ml_log/ml_log.cpp"
#include "ml_log/web_server/web_server.cpp"
#include <iostream>

int main() {
    ml_log::web_server::startWebServer(8080);

    std::cout << "main" << std::endl;
}
