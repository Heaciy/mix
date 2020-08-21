import requests

# 处理header
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.105 Safari/537.36"}

# 所需的url
url_0 = 'http://bkjx.wust.edu.cn/Logon.do?method=logon&flag=sess'  # Ajax,登陆时第一次post的请求链接
url_1 = 'http://bkjx.wust.edu.cn/Logon.do?method=logon'  # 登陆时第二次post的请求链接
url_2 = 'http://bkjx.wust.edu.cn/jsxsd/xskb/xskb_list.do'  # 学期课表
url_3 = 'http://bkjx.wust.edu.cn/jsxsd/framework/main_index_loadkb.jsp'  # 实时课表


def get_session(headers, data):
    session = requests.session()  # 创建session对象，用保存cookie
    dataStr = session.post(url_0, data=data, headers=headers).text  # 第一次post提交
    # 模拟js加密过程以获取encoded
    scode = dataStr.split('#')[0]
    sxh = dataStr.split('#')[1]
    code = data['userAccount'] + r"%%%" + data['userPassword']
    encoded = ""
    i = 0
    while i < len(code):
        if i < 20:
            t = int(sxh[i])
            encoded = encoded+code[i]+scode[0:t]
            tt = len(scode)
            scode = scode[t:tt]
        else:
            encoded = encoded+code[i:len(code)]
            i = len(code)
        i += 1
    # 第二次post提交，获取用域登陆的cookie
    session.post(url_1, data={
                 "userAccount": data['userAccount'], "userPassword": '', "encoded": encoded})
    return session


if __name__ == '__main__':
    # 登陆所需的用户名和密码
    data = {"userAccount": '你的学号',
            "userPassword": '你的密码', "encoded": ''}
    session = get_session(headers, data)
    with open('tmp.html', 'w', encoding='utf8') as f:
        f.write(session.post(url_2, data={'xnxq01id': '2019-2020-2'}).text)
    # sjmsValue默认为：9486203B90F3E3CBE0532914A8C03BE2, 青山校区为D012D3EAA2564458AE988FFDC28BF44A
    with open('tmp_.html', 'w', encoding='utf8') as f:
        f.write(session.post(url_3, data={
                'rq': '2020-08-21', 'sjmsValue': '9486203B90F3E3CBE0532914A8C03BE2'}).text)
