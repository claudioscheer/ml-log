# IMPORTANT: ONLY TESTED ON UBUNTU. OTHER PLATFORMS WILL BE TESTED IN THE FUTURE.

# ml-log

A machine learning log system that uses Redis and shows plotting results almost in real time for C++.

## Dependencies

- [cpp_redis](https://github.com/cpp-redis/cpp_redis): for more details on how to install cpp_redis, click [here](https://github.com/cpp-redis/cpp_redis/wiki/Mac-&-Linux-Install).
- [drogon](https://github.com/an-tao/drogon): for more details on how to install drogon, click [here](https://github.com/an-tao/drogon/wiki/ENG-02-Installation).

## Building the project

```bash
git clone https://github.com/dl4all/ml-log.git
cd ml-log
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

## Install Redis using docker

Use the following commands to create a Redis docker container. If you do not use Docker, make sure that your installation supports [RedisJSON](http://redisjson.io).

```bash
docker create -ti --name redis-ml-log -p 6379:6379 redislabs/rejson:latest
docker start redis-ml-log
```

To find out the IP of your docker instance, use this command.

```bash
docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' redis-ml-log
```

To access your container, use this command.

```bash
docker exec -it redis-ml-log bash
```

`redis-ml-log` is the name of your container. You can choose any name you want.
