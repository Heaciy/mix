# 测试用文件
import re
import json
import requests

# def getJson(html):
#     tmp = {}
#     pattern = re.compile(
#         '<table class="product-domain-pricing-table">.*?<tbody>(.*?)</tbody>.*?</table>', re.S)
#     with open('gandi.json', 'w')as f:
#         items = re.findall(pattern, html)
#         pattern1 = re.compile(
#             '<tr.*?>.*?<a.*?>(.*?)</a>.*?<td><span.*?>(.*?)</span></td>.*?<td><span.*?>(.*?)</span></td>.*?<td><span.*?>(.*?)</span></td>', re.S)
#         items1 = re.findall(pattern1, items[0])
#         for item in items1:
#             tmp[item[0].strip()] = [item[1], item[2], item[3]]
#         json.dump(tmp, f, ensure_ascii=False)


# def getJson(html):
#     tmp = {}
#     with open('namesilo1.json', 'w', encoding='utf-8') as ff:
#         pattern = re.compile('<tr.*?>.*?<td.*?>(.*?)</td>.*?<div>(.*?)</div>', re.S)
#         items = re.findall(pattern, html)
#         for item in items:
#             # print(item[0].strip)
#             tmp[item[0].strip()] = item[1]
#         json.dump(tmp, ff, ensure_ascii=False)


def getJson(html):
    tmp = {}
    with open('name.json', 'w', encoding='utf-8')as f:
        # pattern = re.compile(
        #     '<div.*?class="row pricerow">.*?<div.*?>.*?<a.*?>(.*?)</a>.*?<div.*?><span.*?class="proximanovabold">(.*?)</span>.*?<div.*?>(.*?)</div>.*?<div.*?>(.*?)</div>', re.S)
        pattern = re.compile(
            '<div.*?class="row pricerow">.*?<div.*?>.*?<a.*?>(.[a-zA-Z]+[.]*[a-zA-Z]+)</a>.*?<div.*?class="col-xs-3.*?col-sm-2">.*?<span.*?>(.*?)</span>.*?<div.*?class="col-xs-3.*?col-sm-2">\n*\t*(.*?)\n*\t*</div>.*?<div.*?class="col-xs-3.*?col-sm-2">\n*\t*(.*?)\n*\t*</div>', re.S)
        items = re.findall(pattern, html)
        # for item in items:
        #     tmp[item[0].strip().lower()] = [item[1].strip(), item[2].strip(), item[3].strip()]
        for i in range(len(items)):
            tmp[items[i][0].strip().lower()] = [items[i][1],items[i][2], items[i][3]]
        tmp['.co.uk'][2], tmp['.uk'][2] = '$0.00', '$0.00'
        json.dump(tmp, f, ensure_ascii=False)


if __name__ == '__main__':
    # with open('tmp.html','r')as f:
    #     getJson(f.read())

    # response = requests.get('https://www.namesilo.com/pricing')
    # pattern = re.compile('<table.*?id="table_transfer".*?>.*?<tbody.*?>(.*?)</tbody>', re.S)
    # pattern = re.compile('<table.*?id="table_registration".*?>.*?<tbody.*?>(.*?)</tbody>', re.S)
    # pattern = re.compile('<table.*?id="table_renewal".*?>.*?<tbody.*?>(.*?)</tbody>', re.S)
    # item = re.findall(pattern,response.text)
    # getJson(item[0])

    with open('name.html', 'r', encoding='utf-8')as f:
        getJson(f.read())
