//
// Created by 何嘉豪 on 2020/2/27.
//

#ifndef TAKEBUS_MENU_H
#define TAKEBUS_MENU_H

#include <algorithm>
#include "map.h"

using namespace std;

void printMenu();

int findStation(const string& name);

void run(int index);

#endif //TAKEBUS_MENU_H
