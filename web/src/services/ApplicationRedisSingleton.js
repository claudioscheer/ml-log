class ApplicationRedisSingleton {
    applicationName;
    redisHost;
    redisPort;
    redisDatabaseIndex;
}

const applicationRedisSingleton = new ApplicationRedisSingleton();
export default applicationRedisSingleton;
