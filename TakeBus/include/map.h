//
// Created by 何嘉豪 on 2020/2/27.
//

#ifndef TAKEBUS_MAP_H
#define TAKEBUS_MAP_H

#include <utility>
#include <fstream>
#include <sstream>
#include "model.h"

using namespace std;

extern BusMap g_BusMap;

void readBusData();

void readStationData();

void readRouteData();

void loadRouteData();

void loadMapData();

// 搜索包含该station的前后route
std::pair<int, int> searchRoute(int station, int flag);

void writeBusData();

void writeStationData();

void writeRouteData();

void writeMapData();

#endif //TAKEBUS_MAP_H
