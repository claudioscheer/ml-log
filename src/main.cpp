#include <cpp_redis/cpp_redis>
#include <iostream>

int main() {
    cpp_redis::client client;
    client.connect("172.17.0.2", 6379,
                   [](const std::string &host, std::size_t port,
                      cpp_redis::connect_state status) {
                       if (status == cpp_redis::connect_state::dropped) {
                           std::cout << "client disconnected from " << host
                                     << ":" << port << std::endl;
                       }
                   });

    std::cout << "main" << std::endl;
}
