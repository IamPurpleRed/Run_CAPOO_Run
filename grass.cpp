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
    
    
    grass_num = rand() % 2 + 3;  // TODO: 之後要改成隨機取2~4
    while (grass_num) {
        grass_position = rand() % 5;
        if (road[grass_position] == 1) road[grass_position] = 0;
        else continue;
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



