import json
from func import gandi,namesilo,name
from settings import *

def loadJsonData(domain): # 需要加入异常处理
    fileName = domain+".json"
    with open(fileName,'w',encoding='utf-8') as f:
        jsonData = json.loads(f)
    return jsonData

def init():
    data = {domain:loadJsonData(domain) for domain in domainList}
    return data

if __name__=="__main__":
    pass

# 规划
# 多线程/先使用json数据，再使用数据库(mysql+redis)
# 异步爬虫框架(或者是自己实现异步爬虫框架)
# 最后与Django或者是Flask对接(VUE+DRF+AJAX)