#include "ml_log.cpp"
#include <iostream>
#include <string>

int main() {
    ml_log::redis::RedisCommands redisCommands("172.17.0.2", 6379, "test");
    redisCommands.databaseIndex = 0;

    std::string key = "train";
    ml_log::redis::XYType item;
    for (int i = 0; i <= 10; i++) {
        item.x = i + 1;
        item.y = i * i;
        redisCommands.appendXYItem(key, item);
    }

    return 0;
}
