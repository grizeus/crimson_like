#pragma once
#include "Enemy.h"
#include <memory>

using EnemyPtr = std::shared_ptr<Enemy>;

class EnemySpawner {
public:
    EnemySpawner() {}
    ~EnemySpawner() {} 
    EnemyPtr Spawn(int, int);
};
