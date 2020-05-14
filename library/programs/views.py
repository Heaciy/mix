import json
import os
import requests
from time import perf_counter as pc
import glob


def get_publishers_json(publisher_txt, file):
    t0 = pc()
    publishers = set()
    lines = publisher_txt.readlines()
    for line in lines:
        publishers.add(line.split('",')[0])
    publishers = sorted(list(publishers))
    the_dict = {"publishers": publishers, 'num': len(publishers)}
    json.dump(the_dict, file, ensure_ascii=False)
    print("Add {} publisher to publishers.json / cost: {} s".format(len(publishers), pc() - t0))


def get_all_publishers(publisher_json):
    return json.load(publisher_json)['publishers']

# 改成多线程(线程锁？)
# 文件在第一次发生错误时将id和publisher加入到wrong_list,最后处理完后再请求一次，如果还有错误的则添加到./data/wrong_file.json中手动处理
# 添加矫正机制


def get_books_of_publisher(url, publishers, limite_times, path, recursive_times):
    os.chdir(path+'/data_json/books/books')
    t = pc()
    id = 0
    right_num = 0
    books_num = 0
    wrong_list = []
    for publisher in publishers:
        try:
            t0 = pc()
            with open('books_of_{}.json'.format(publisher), 'w', encoding='utf8') as file:
                bibnum = []
                books = []
                payload = {'publisher': publisher + ','}
                for book in requests.get(url, params=payload, timeout=limite_times).json():
                    if book['bibnum'] not in bibnum:
                        bibnum.append(book['bibnum'])
                        books.append(book)
                the_dict = {'publisher': publisher,
                            'num': len(books), 'books': books}
                json.dump(the_dict, file, ensure_ascii=False)
                print('{:>3d} | Added {} books to books_of_{}.json  /  Cost: {} s'.format(
                    id, len(books), publisher, pc()-t0))
                books_num += len(books)
                right_num += 1
                id += 1
        except:
            print('{:>3d} | Something Wrong with books_of_{}.json'.format(
                id, publisher))
            wrong_list.append(publisher)
            id += 1
            continue
    print("TotalFileNum: {} / TotalBookNum{} / RightNum: {} / WrongNum: {} / Cost: {} s ({} min)".format(id,
                                                                                                         books_num, right_num, len(wrong_list), pc()-t, (pc()-t)/60.0))

    recursive_times -= 1

    if recursive_times == 0 and len(wrong_list) > 0:
        os.chdir(path + '/data_json/')
        wrong_dict = {'wrong': wrong_list}
        with open('wrong.json', 'w', encoding='utf8') as wrong_json:
            json.dump(wrong_dict, wrong_json, ensure_ascii=False)

    if len(wrong_list) > 0 and recursive_times > 0:
        get_books_of_publisher(
            url, [publisher for publisher in wrong_list], limite_times, path, recursive_times)


def get_books_all(url, publishers, file):
    bibnum = []
    books_all = []
    for publisher in publishers:
        payload = {'publisher': publisher + ','}
        for book in requests.get(url, params=payload).json():
            if book['bibnum'] not in bibnum:
                bibnum.append(book['bibnum'])
                books_all.append(book)
    the_dict = {'publishers': publishers, 'books': books_all}
    json.dump(the_dict, file, ensure_ascii=False)


def get_details_of_publisher(path):
    t0 = pc()
    books_dir = path + "/data_json/books/books/"
    details_dir = path + "/data_json/details"
    os.chdir(books_dir)
    details = ['author', 'publisher', 'subjects',
               'itemtype', 'itemcollection', 'itemlocation']
    for file in glob.glob("*.json"):
        with open(file, 'r', encoding='utf8') as f:
            detail_datas = {}
            book_data = json.load(f)
            for detail in details:
                try:
                    the_data = set()
                    for book in book_data['books']:
                        the_data.add(book[detail])
                    detail_datas[detail] = list(the_data)
                except:
                    print('KeyError: %s' % detail)
            target_file = details_dir+'/details/' + \
                'details_of_'+book_data['publisher']+'.json'
            with open(target_file, 'w', encoding='utf8') as fe:
                json.dump(detail_datas, fe, ensure_ascii=False)
    print('Cost {} s'.format(pc()-t0))


def get_details_all(path):
    t0 = pc()
    details_dir = path + "/data_json/details/"
    os.chdir(details_dir + 'details/')
    details = ['author', 'publisher', 'subjects',
               'itemtype', 'itemcollection', 'itemlocation']
    detail_datas = {'author': [], 'publisher': [], 'subjects': [],
                    'itemtype': [], 'itemcollection': [], 'itemlocation': []}
    for file in glob.glob("*.json"):
        with open(file, 'r', encoding='utf8') as f:
            temp = json.load(f)
            for detail in details:
                try:
                    detail_datas[detail] = sorted(list(
                        set(detail_datas[detail]).union(set(temp[detail]))))
                except:
                    print('KeyError: %s' % detail)
    # 进一步切割subjects
    sub = set()
    for subject in detail_datas['subjects']:
        sub |= set(subject.split(', '))
    detail_datas['subjects'] = sorted(list(sub))
    
    target_file = details_dir + 'details_all.json'
    with open(target_file, 'w', encoding='utf') as fe:
        json.dump(detail_datas, fe, ensure_ascii=False)
    print('Cost {} s'.format(pc()-t0))
