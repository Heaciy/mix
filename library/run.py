import os
import sys
import requests
import json
import settings
from programs import views

path_list = os.getcwd().split('\\')
path_now = '/'.join(path_list)
path_data = path_now + '/data'

# 生成publishers.json
# with open(settings.file_path, 'r', encoding='utf8') as publishers_txt:
#     with open('./data/publishers.json', 'w', encoding='utf8') as publishers_json:
#         views.get_publishers_json(publishers_txt, publishers_json)

# 生成books_of_publisher.json和books_all.json
# with open('./data/publishers.json', 'r', encoding='utf8') as publishers_json:
#     views.get_books_of_publisher(settings.url_json, views.get_all_publishers(publishers_json), settings.limite_times, path_data, settings.recursive_times+1)

# with open('./data/publishers.json', 'r', encoding='utf8') as publishers_json:
#     with open('./data/data_json/books/books_all.json', 'w', encoding='utf-8') as books_all_json:
#         views.get_books_all(settings.url_json, views.get_all_publishers(publishers_json), books_all_json)


# 生成details_of_publisher.json
views.get_details_of_publisher(path_data)

# 生成details_all.json
views.get_details_all(path_data)