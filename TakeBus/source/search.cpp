//
// Created by 何嘉豪 on 2020/3/8.
//

#include "menu.h"

int MAX_CHANGE_NUM = 1; //最大换乘次数

// 采用深度优先算法搜索两站之间符合要求的所有线路
static void doSearch(int index, int target, list<int> &visited,
                     list<const Route *> &routes,
                     vector<list<const Route *>> &results,
                     int changed) {
    visited.emplace_back(index); //将起始点压入(即标记为已访问)
    for (auto route:g_BusMap.stations[index].routes) { //找到所有route中以index为起点的符合要求的route
        bool flag = true;
        for (auto station: visited) {
            if (route->to == station) {
                flag = false; //如果该route的to在已访问的列表中则不符合要求
                break;
            }
        }
        if (flag) { //如果该route符合要求
            int tmp = changed; //用于判断在运行过程中changed是否改变(changed++)了,若发生改变，则在回溯时将其复原(changed--)
            if (!routes.empty() && route->bus != routes.back()->bus) changed++; //若发生换乘,则换乘次数加一
            if (changed <= MAX_CHANGE_NUM) { //若换乘次数小于最大换乘次数限制
                routes.emplace_back(route); //将route接到该条routes后面
                if (route->to == target) { //如果该route连接终点
                    results.emplace_back(routes); //则该条路线满足要求,将其压入results中
                    routes.pop_back(); //将routes末端的route弹出,探索剩余的以index节点为起点的route
                    if (changed > tmp) changed--; //如果在压入最后一段route时发生了换乘,则在将其弹出时也要将changed次数还原
                } else {
                    //若此route未连接终点,则继续探索以该route终点为起点的其他route(递归)
                    doSearch(route->to, target, visited, routes, results, changed);
                    if (changed > tmp) changed--; //在探索某route时发生了换乘,则在回溯时需要将changed次数还原
                }
            } else { //换乘次数大于限制次数
                if (changed > tmp) changed--; //发生了换乘,在退出该route时需要将changed次数还原
                continue; //探索以index为节点的下一条route
            }
        }
    }
    visited.pop_back(); //将某个节点的所有后续route探索完后,回溯时将该节点从已访问节点(visited)中删除
    if (!routes.empty()) routes.pop_back(); //弹出该节点的同时也弹出通往该节点的route
}

void takeBus() {
    string from, to;
    cout << "输入起始站 终点站(如A B):";
    int from_, to_;
    cin >> from >> to;
    while (((from_ = findStation(from)) == -1) || ((to_ = findStation(to)) == -1)) {
        cout << "输入错误!重新输入:";
        cin >> from >> to;
    }
    list<int> visited; //已访问的路线
    list<const Route *> routes; //某一条符合要求的路线
    vector<list<const Route *>> results; //所有符合要求的路线
    int changed = 0; //已换乘的次数
    doSearch(from_, to_, visited, routes, results, changed); //搜索线路
    for (const auto &result : results) { //打印results中的所有的线路
        for (const auto &route : result) {
            cout << g_BusMap.buses[route->bus].name << ": "
                 << g_BusMap.stations[route->from].name << "-->"
                 << g_BusMap.stations[route->to].name << " (" << route->distance << "m)" << endl;
        }
        cout << "-----------------" << endl;
    }
}