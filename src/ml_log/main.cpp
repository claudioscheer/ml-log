#include "ml_log.cpp"
#include <iostream>

int main() {
    ml_log::redis::RedisCommands redisCommands("172.17.0.2", 6379);

    ml_log::redis::AppendItemType appendType;
    for (int i = 0; i <= 10; i++) {
        appendType.key = "train";
        /* appendType.json = format("{}"); */
        redisCommands.appendItem(appendType);
    }

    return 0;
}
