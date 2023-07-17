#pragma once
#include "Enemy.h"

class EnemySpawner {
public:
    EnemySpawner() {}
    ~EnemySpawner() {} 
    EnemyPtr Spawn(int winWidth, int winHeight);
};
