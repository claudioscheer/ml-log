class ApplicationRedisSingleton {
    applicationName;
    redisHost;
    redisPort;
    redisDatabaseIndex;

    constructor() {
        this.applicationName =
            localStorage.getItem('mlLogApplicationName') || '';
        this.redisHost = localStorage.getItem('mlLogRedisHost') || '';
        this.redisPort = localStorage.getItem('mlLogRedisPort') || 0;
        this.redisDatabaseIndex =
            localStorage.getItem('mlLogRedisDatabaseIndex') || 0;
    }
}

const applicationRedisSingleton = new ApplicationRedisSingleton();
export default applicationRedisSingleton;
