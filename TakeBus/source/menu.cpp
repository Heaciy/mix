//
// Created by 何嘉豪 on 2020/2/29.
//

#include <utility>
#include "menu.h"
#include "search.h"

void printMenu() {
    cout << "=====公交管理系统=====" << "\n"
         << "1.\t查看所有站点" << "\n"
         << "2.\t查看所有公交" << "\n"
         << "3.\t查询站点信息" << '\n'
         << "4.\t查询公交线路" << '\n'
         << "5.\t查询路线" << '\n'
         << "6.\t添加站点" << '\n'
         << "7.\t修改站点" << '\n'
         << "8.\t删除站点" << '\n'
         << "9.\t添加线路" << '\n'
         << "10.\t修改线路" << '\n'
         << "11.\t删除线路" << '\n'
         << "12.\t添加公交" << '\n'
         << "13.\t修改公交" << '\n'
         << "14.\t删除公交" << '\n'
         << "15.\t保存数据" << '\n'
         << "0.\t退出" << '\n'
         << "===================" << '\n'
         << "请输入指令编号：";
}

//根据公交名查找该公交的索引
static int findBus(const string &name) {
    for (size_t i = 0; i < g_BusMap.buses.size(); i++) {
        if (g_BusMap.buses[i].name == name) return i;
    }
    return -1;
}

//根据起点，终点，公交名查找route的索引
static int findRoute(int from, int to, int bus) {
    for (size_t i = 0; i < g_BusMap.routes.size(); i++) {
        auto &route = g_BusMap.routes[i];
        if (route.from == from && route.to == to && route.bus == bus) {
            return i;
        }
    }
    return -1;
}

//根据站点的名字查找站点的索引
int findStation(const string &name) {
    for (size_t i = 0; i < g_BusMap.stations.size(); i++) {
        if (g_BusMap.stations[i].name == name) {
            return i;
        }
    }
    return -1;
}

//1.查看所有站点
static void listStations() {
    for (size_t i = 0; i < g_BusMap.stations.size(); i++) {
        cout << i << "--" << g_BusMap.stations[i].name << endl;
    }
}

//2.查看所有公交
static void listBuses() {
    for (size_t i = 0; i < g_BusMap.buses.size(); i++) {
        const auto &bus = g_BusMap.buses[i];
        cout << bus.name << " \t"
             << g_BusMap.stations[bus.start].name
             << "-->"
             << g_BusMap.stations[bus.end].name << endl;
    }
}

//3.查询站点信息
static void printStationInfo() {
    string temp;
    cout << "输入站点名称：";
    cin >> temp;
    int index = findStation(temp);
    if (index != -1) {
        for (const auto &route : g_BusMap.routes)
            if ((route.from == index || route.to == index) && route.bus != -1) {
                cout << g_BusMap.stations[route.from].name << "-->" << g_BusMap.buses[route.bus].name
                     << "-->" << g_BusMap.stations[route.to].name << endl;
            }
    } else {
        cout << "输入错误!" << endl;
    }
}

//辅助打印公交线路
static void doPrintBusInfo(int station, int bus) {
    for (auto it = g_BusMap.stations[station].routes.cbegin(); it != g_BusMap.stations[station].routes.cend(); it++) {
        if ((*it)->bus == bus) {
            cout << "-->" << g_BusMap.stations[(*it)->to].name;
            doPrintBusInfo((*it)->to, bus);
        }
    }
}

//4.查询公交线路
static void printBusInfo() {
    string temp;
    cout << "输入公交名称：";
    cin >> temp;
    int index = findBus(temp);
    if (index != -1) {
        int start = g_BusMap.buses[index].start;
        cout << g_BusMap.stations[start].name;
        doPrintBusInfo(start, index);
        cout << endl;
    } else {
        cout << "输入错误!" << endl;
    }
}

//6.添加站点
static void addStation() {
    string name;
    cout << "输入新增站点的名称:";
    cin >> name;
    if (findStation(name) == -1) {
        g_BusMap.stations.emplace_back(Station(name));
    } else {
        cout << "名称占用!" << endl;
    }
}

//7.修改站名(名字)
static void changeStation() {
    string oldName, newName;
    cout << "输入待修改站点的名称:";
    cin >> oldName;
    int index = findStation(oldName);
    if (index != -1) {
        cout << "输入新名称:";
        cin >> newName;
        g_BusMap.stations[index].name = newName;
    } else cout << "输入站点不存在!";
}

//8.删除站点
static void deleteStation() {
    string name;
    cout << "输入待删除站点的名称:";
    cin >> name;
    int index = findStation(name);
    if (index != -1) {
        for (size_t i = 0; i < g_BusMap.buses.size(); i++) {
            pair<int, int> temp = searchRoute(index, i);
            if (temp.first == -1 && temp.second == -1)// 该bus上没有此点
                continue;
            else if (temp.first == -1) {//为该bus的起点
                g_BusMap.buses[i].start = g_BusMap.routes[temp.second].to;
                g_BusMap.routes[temp.second].bus = -1;
            } else if (temp.second == -1) {//为该路线的终点
                g_BusMap.buses[i].end = g_BusMap.routes[temp.first].from;
                g_BusMap.stations[g_BusMap.buses[i].end].routes.remove(&g_BusMap.routes[temp.first]);
                g_BusMap.routes[temp.first].bus = -1;
            } else {//为中转站
                g_BusMap.routes[temp.first].to = g_BusMap.routes[temp.second].to;
                g_BusMap.routes[temp.first].distance += g_BusMap.routes[temp.second].distance;
                g_BusMap.routes[temp.second].bus = -1;
            }
        }
        // 从g_BusMap中删除该站点
        g_BusMap.stations.erase(g_BusMap.stations.begin() + index);
        // 调整route中station的编号
        for (auto &route:g_BusMap.routes) {
            if (route.from > index) route.from--;
            if (route.to > index) route.to--;
        }
        // 调整bus中station的编号
        for (auto &bus:g_BusMap.buses) {
            if (bus.start > index) bus.start--;
            if (bus.end > index) bus.end--;
        }
        cout << "删除成功!" << endl;
    } else cout << "输入站点不存在!";
}

//9.添加线路
static void addRoute(int from, int to, int bus, int distance) {
    g_BusMap.routes.emplace_back(Route(from, to, bus, distance));
    g_BusMap.stations[from].routes.emplace_back(&(g_BusMap.routes.back()));
}

//10.修改线路
static void changeRoute(int from, int to, int bus, int distance) {
    int index = findRoute(from, to, bus);
    if (index != -1) {
        g_BusMap.routes[index].distance = distance;
    } else cout << "输入的路线不存在,请检查数据!";
}

//11.删除线路
static void deleteRoute(int from, int to, int bus) {
    int index = findRoute(from, to, bus);
    if (index != -1) {
        g_BusMap.routes[index].bus = -1; //在删除某条route时,先暂时将其route.bus置为-1(为了防止vector中元素的指针改变)
        g_BusMap.stations[from].routes.remove(&g_BusMap.routes[index]);
    } else cout << "输入的路线不存在,请检查数据!";
}

//14.删除公交
static void deleteBus(const string &name) {
    int index = findBus(name);
    int from = g_BusMap.buses[index].start;
    int end = g_BusMap.buses[index].end;
    while (from != end) {
        for (auto route: g_BusMap.stations[from].routes)
            if (route->bus == index) {
                int tmp = route->to;
                deleteRoute(from, route->to, index);
                from = tmp;
                break; //?
            }
    }
    g_BusMap.buses.erase(g_BusMap.buses.begin() + index);
    for (auto &route:g_BusMap.routes) {
        if (route.bus > index) route.bus--;
    }
}

//12.添加公交
static void addBus(string name) {
    int num, distance;
    cout << "输入此公交中包含的站点数:";
    cin >> num;
    vector<string> nameList;
    vector<int> numList;
    vector<int> distanceList;
    string from, tmp;
    cout << "输入始发站名称:";
    cin >> from;
    num--;
    while (findStation(from) == -1) {
        cout << "输入的站点不存在!请重新输入:";
        cin >> from;
    }
    nameList.emplace_back(from);
    while (num--) {
        cout << "输入距离 站点(如:100 A):";
        cin >> distance >> tmp;
        while (findStation(tmp) == -1) {
            cout << "输入的站点不存在!请重新输入:";
            cin >> distance >> tmp;
        }
        distanceList.emplace_back(distance);
        nameList.emplace_back(tmp);
    }
    //添加相关的route
    for (size_t i = 0; i < nameList.size() - 1; i++) {
        addRoute(findStation(nameList[i]), findStation(nameList[i + 1]), g_BusMap.buses.size(), distanceList[i]);
    }
    //添加公交
    g_BusMap.buses.emplace_back(Bus(std::move(name), findStation(nameList[0]), findStation(nameList.back())));
}

//13.修改公交
static void changeBus() {
    string name;
    cout << "输入待修改公交的名称(如:1_U)";
    cin >> name;
    int index = findBus(name);
    if (index != -1) {
        deleteBus(name);
        addBus(name);
    } else cout << "该公交名不存在,请检查数据!";
}

//辅助用户输入
static vector<int> enter_check() {
    string from, to, bus;
    vector<int> tmp;
    cout << "输入出发站 到达站 所属公交(如:A B 1_U):";
    cin >> from >> to >> bus;
    while (findStation(from) == -1 || findStation(to) == -1 || findBus(bus) == -1) {
        cout << "输入错误!重新输入:";
        cin >> from >> to >> bus;
    }
    tmp.emplace_back(findStation(from));
    tmp.emplace_back(findStation(to));
    tmp.emplace_back(findBus(bus));
    return tmp;
}

//给route添加检查修正警告函数
static void doAddRoute() {
    vector<int> tmp = enter_check();
    int distance;
    cout << "输入距离:";
    cin >> distance;
    while (distance <= 0) {
        cout << "输入错误!重新输入:";
        cin >> distance;
    }
    addRoute(tmp[0], tmp[1], tmp[2], distance);
}

static void doChangeRoute() {
    vector<int> tmp = enter_check();
    int distance;
    cout << "输入新距离:";
    cin >> distance;
    while (distance <= 0) {
        cout << "输入错误!重新输入:";
        cin >> distance;
    }
    changeRoute(tmp[0], tmp[1], tmp[2], distance);
}

static void doDeleteRoute() {
    vector<int> tmp = enter_check();
    deleteRoute(tmp[0], tmp[1], tmp[2]);
}

static void doDeleteBus() {
    string name;
    cout << "输入待删除公交的名称:";
    cin >> name;
    while (findBus(name) == -1) {
        cout << "该公交名不存在!请重新输入:";
        cin >> name;
    }
    deleteBus(name);
}

static void doAddBus() {
    string name;
    cout << "输入待添加公交的名称:";
    cin >> name;
    while (findBus(name) != -1) {
        cout << "该公交名已存在!请重新输入:";
        cin >> name;
    }
    addBus(name);
}

//删除有已删除标记的route(既route.bus==-1)
static void filterRoute() {
    for (auto it = g_BusMap.routes.begin(); it != g_BusMap.routes.end(); it++) {
        if (it->bus == -1) g_BusMap.routes.erase(it--);
    }
}

void run(int index) {
    switch (index) {
        case 1:
            listStations();
            break;
        case 2:
            listBuses();
            break;
        case 3:
            printStationInfo();
            break;
        case 4:
            printBusInfo();
            break;
        case 5:
            takeBus();
            break;
        case 6:
            addStation();
            break;
        case 7:
            changeStation();
            break;
        case 8:
            deleteStation();
            break;
        case 9:
            doAddRoute();
            break;
        case 10:
            doChangeRoute();
            break;
        case 11:
            doDeleteRoute();
            break;
        case 12:
            doAddBus();
            break;
        case 13:
            changeBus();
            break;
        case 14:
            doDeleteBus();
            break;
        case 15:
            filterRoute();//先过滤数据
            writeMapData();//写入数据
            break;
        default:
            cout << "输入错误!" << endl;
            break;
    }
}