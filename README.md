# ml-log

A machine learning log system that uses Redis and shows plotting results almost in real time for C++.

# Dependencies

ml-log depends on [cpp_redis](https://github.com/cpp-redis/cpp_redis). For more details on how to install cpp_redis, click [here](https://github.com/cpp-redis/cpp_redis/wiki/Mac-&-Linux-Install).

# Install Redis using docker

Use the following commands to create a Redis docker container.

```bash
docker create -ti --name redis-ml-log -p 6379:6379 redis
docker start redis-ml-log
docker exec -it redis-ml-log bash
```

To find out the IP of your docker instance, use this command.

```bash
docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' redis-ml-log
```

`redis-ml-log` is the name of your container. You can choose any name you want.
