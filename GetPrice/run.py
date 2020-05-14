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
