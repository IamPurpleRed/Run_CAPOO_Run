// NOTE: grass = 0, road = 1
#include "grass.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

grass::grass() {
    // 預設該 row 沒有 grass
    grass_num = 0;
    for (int i = 0; i < 5; i++) road[i] = 1;
}

void grass::create() {
    srand(time(NULL));
    grass_num = 4;  // TODO: 之後要改成隨機取2~4
    while (grass_num) {
        // TODO: 尚未完成 (現在只能一條路
        road[rand() % 5] = 0;
        grass_num--;
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

void grass::reset() {
    for (int i = 0; i < 5; i++) road[i] = 1;
}
