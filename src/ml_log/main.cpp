#include "ml_log.cpp"
#include <iostream>
#include <string>

int main() {
    ml_log::redis::RedisCommands *redisCommands =
        ml_log::redis::RedisCommands::getInstance("test", "172.17.0.2", 6379,
                                                  0);

    std::string key = "validation";
    ml_log::redis::XYType item;
    for (int i = 0; i <= 10; i++) {
        item.x = i + 1;
        item.y = i * i;
        redisCommands->appendXYItem(key, item);
    }

    std::string r = redisCommands->getXYArray(key);
    /* std::cout << r << std::endl; */

    return 0;
}
