// NOTE: grass = 0, road = 1
#include "grass.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

grass::grass() {
    // 預設該 row 沒有 grass
    have_grass = false;
    grass_num = 0;
    memset(road, 1, sizeof(road));
}

void grass::create() {
    srand(time(NULL));
    grass_num = 4;              // TODO: 之後要改成隨機取2~4
    int empty = 5 - grass_num;  // 還有幾個空路的位置要隨機
    while (empty) {
        // TODO: 尚未完成
    }
}

int& grass::send() {
    return road[0];
}

void grass::receive(int& row) {
    for (int i = 0; i < 5; i++) {
        road[i] = *(&row + i);
    }
}
