# coding:utf-8
import time
import redis

rc = redis.StrictRedis(host='0.0.0.0', port='6379', db=3)
ps = rc.pubsub()
ps.subscribe('Xuefeng')
for item in ps.listen():
    if item['type'] == 'message':
        print(item['channel'])
        print(item['data'])
        time.sleep(0.3)


