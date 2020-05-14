//
// Created by 何嘉豪 on 2020/2/27.
//

#include "map.h"
#include "model.h"

static const char *BUS_FILE_PATH = "../data/buses.txt";
static const char *STATION_FILE_PATH = "../data/stations.txt";
static const char *ROUTE_FILE_PATH = "../data/routes.txt";

BusMap g_BusMap;

void readBusData() {
    ifstream busFile(BUS_FILE_PATH);
    string tmp;
    int index, start, end;
    string name;
    istringstream dataStream;
    while (getline(busFile, tmp) && tmp.length() > 0) {
        dataStream.clear();
        dataStream.str(tmp);
        dataStream >> index >> name >> start >> end;
        g_BusMap.buses.emplace_back(Bus(name, start, end));
    }
    busFile.close();
}

void readStationData() {
    ifstream stationFile(STATION_FILE_PATH);
    string tmp;
    int index = 0;
    string name;
    istringstream dataStream;
    while (getline(stationFile, tmp) && tmp.length() > 0) {
        dataStream.clear();
        dataStream.str(tmp);
        dataStream >> index >> name;
        g_BusMap.stations.emplace_back(Station(name));
    }
    stationFile.close();
}

void readRouteData() {
    ifstream routeFile(ROUTE_FILE_PATH);
    string tmp;
    int bus, from, to, distance;
    istringstream dataStream;
    while (getline(routeFile, tmp) && tmp.length() > 0) {
        dataStream.clear();
        dataStream.str(tmp);
        dataStream >> bus >> from >> to >> distance;
        g_BusMap.routes.emplace_back(Route(from, to, bus, distance));
    }
    routeFile.close();
}

void loadRouteData() {
    for (auto &station : g_BusMap.stations) station.routes.clear();
    for (const auto &route : g_BusMap.routes) {
        if (route.bus != -1)
            g_BusMap.stations[route.from].routes.emplace_back(&(route));
    }
}

void loadMapData() {
    readBusData();
    readStationData();
    readRouteData();
    loadRouteData();
}

pair<int, int> searchRoute(int station, int bus) {
    pair<int, int> result(-1, -1);
    for (size_t i = 0; i < g_BusMap.routes.size(); i++) {
        if (g_BusMap.routes[i].bus == bus) {
            if (g_BusMap.routes[i].to == station) result.first = i;
            if (g_BusMap.routes[i].from == station) result.second = i;
        }
    }
    return result;
}

void writeBusData() {
    ofstream busFile(BUS_FILE_PATH);
    for (size_t i = 0; i < g_BusMap.buses.size(); i++) {
        busFile << i << ' ' << g_BusMap.buses[i].name << ' '
                << g_BusMap.buses[i].start << ' ' << g_BusMap.buses[i].end << endl;
    }
    busFile.close();
}

void writeStationData() {
    ofstream stationFile(STATION_FILE_PATH);
    for (size_t i = 0; i < g_BusMap.stations.size(); i++) {
        stationFile << i << ' ' << g_BusMap.stations[i].name << endl;
    }
    stationFile.close();
}

void writeRouteData() {
    ofstream routeFile(ROUTE_FILE_PATH);
    for (const auto &route : g_BusMap.routes) {
        routeFile << route.bus << ' ' << route.from << ' ' << route.to << ' '
                  << route.distance << endl;
    }
    routeFile.close();
}

void writeMapData() {
    writeBusData();
    writeStationData();
    writeRouteData();
}