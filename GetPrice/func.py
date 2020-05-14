import requests
import json
import re
from time import perf_counter as pc


def gandi():
    # paramsList = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    #               'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
    paramsList = ['a']
    tmp = {}

    # 提取数据
    def getData(html):
        pattern = re.compile(
            '<table class="product-domain-pricing-table">.*?<tbody>(.*?)</tbody>.*?</table>', re.S)
        items = re.findall(pattern, html)
        pattern1 = re.compile(
            '<tr.*?>.*?<a.*?>(.*?)</a>.*?<td><span.*?>(.*?)</span></td>.*?<td><span.*?>(.*?)</span></td>.*?<td><span.*?>(.*?)</span></td>', re.S)
        pattern2 = re.compile('class.*?id="(.*?)">.*?<td.*?><.*?class="price(?: is-new-price)?">(.*?)<\/(?:span|ins)><\/td>.*?<td.*?><.*?class="price(?: is-new-price)?">(.*?)<\/(?:span|ins)><\/td>.*?<td.*?><.*?class="price(?: is-new-price)?">(.*?)<\/(?:span|ins)><\/td>', re.S)
        items1 = re.findall(pattern2, items[0])
        for item in items1:
            tmp[item[0].strip()] = [item[1], item[2], item[3]]

    # params = {'c': 'US', 'currency': 'USD', 'sw': 'currency'}
    params = {'c': 'CN', 'currency': 'CNY', 'sw': 'currency'}
    for i in paramsList:
        t0 = pc()
        params['prefix'] = i
        api = "https://www.gandi.net/en-US/domain/tld"
        response = requests.get(api, params=params)
        getData(response.text)
        print('Params: {} | Status: {} | Cost {} s'.format(
            i, response.status_code, pc()-t0))
    # 将处理好的数据存入文件
    with open('gandi.json', 'w', encoding='utf-8')as f:
        json.dump(tmp, f, ensure_ascii=False)


def namesilo():
    t0 = pc()
    tmp = {}

    def getData(html):
        patterns = [re.compile('<table.*?id="table_registration".*?>.*?<tbody.*?>(.*?)</tbody>', re.S),
                    re.compile(
                        '<table.*?id="table_transfer".*?>.*?<tbody.*?>(.*?)</tbody>', re.S),
                    re.compile('<table.*?id="table_renewal".*?>.*?<tbody.*?>(.*?)</tbody>', re.S)]
        pattern = re.compile(
            '<tr.*?>.*?<td.*?>(.*?)</td>.*?<div>(.*?)</div>', re.S)
        for i in range(len(patterns)):
            # for i in range(3):
            items = re.findall(patterns[i], html)
            items1 = re.findall(pattern, items[0])
            if i == 0:
                for item in items1:
                    tmp[item[0].strip()] = [item[1]]
            elif i == 1:
                for item in items1:
                    tmp['.'+item[0].strip()].append(item[1])
            else:
                for item in items1:
                    tmp[item[0].strip()].append(item[1])
    api = 'https://www.namesilo.com/pricing'
    t1 = pc()
    response = requests.get(api)
    print('client cost {} s'.format(pc()-t1))
    getData(response.text)
    print('Status: {} | Cost {} s'.format(response.status_code, pc()-t0))
    with open('namesilo.json', 'w', encoding='utf-8') as f:
        json.dump(tmp, f, ensure_ascii=False)


def name():
    api = 'https://www.name.com/pricing'
    with open('name.html', 'w',encoding='utf-8') as f:
        f.write(requests.get(api).text)


if __name__ == '__main__':
    # gandi()
    # namesilo()
    name()
