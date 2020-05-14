# 本次任务要处理的原始数据(可否改为文件列表)
file_name = 'publishers_0.txt'

# webAPI接口
url_json = 'https://data.seattle.gov/resource/6vkj-f5xf.json'
url_csv = 'https://data.seattle.gov/resource/6vkj-f5xf.csv'

#等待API接口的最大响应时间
limite_times = 10

# 发生错误后执行递归修复的次数
recursive_times = 1

# 处理后的路径
origin_path = './origin/'
file_path = origin_path + file_name
