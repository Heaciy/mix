//
// Created by 何嘉豪 on 2020/2/27.
//

#ifndef TAKEBUS_MODEL_H
#define TAKEBUS_MODEL_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

struct Bus {
    Bus(std::string name, int start, int end)
            : name(name), start(start), end(end) {}
    std::string name;
    int start;
    int end;
};

struct Route {
    Route(int from, int to, int bus, int distance)
            : from(from), to(to), bus(bus), distance(distance) {}
    int from;
    int to;
    int bus;
    int distance;
};

struct Station {
    Station(std::string name) : name(name) {} //先构造name,routes在加载routes时构造
    std::string name;
    std::list<const Route*> routes;
};

struct BusMap {
    std::vector<Bus> buses;
    std::vector<Station> stations;
    std::vector<Route> routes;
};

#endif //TAKEBUS_MODEL_H
