import time
import redis


messages = 0

rc = redis.StrictRedis(host='0.0.0.0', port='6379', db=3)
while messages != '^' :
    messages = input("Publish messages to Receiver here:   ")
    rc.publish("Xuefeng", messages)
