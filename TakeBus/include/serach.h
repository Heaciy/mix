//
// Created by 何嘉豪 on 2020/3/1.
//

#ifndef TAKEBUS_SERACH_H
#define TAKEBUS_SERACH_H

#include <utility>
#include <vector>

using namespace std;

static void printThru(int from, int to, int bus);

static pair<bool, vector<int>> isThru(int from, int to);

static void printTurn(int from, int to, int bus, vector<int> preStation);

void takeBus();

#endif //TAKEBUS_SERACH_H