#pragma once
#include "Enemy.h"
#include <vector>

class EnemySpawner {
public:
    EnemySpawner() {}
    ~EnemySpawner() {} 
    void Spawn(int, int);
private:
    std::vector<Position> m_EnemyPositions;
    std::vector<Direction> m_EnemyDirections;
    std::vector<CollisionBox> m_EnemyCollisionBoxes;
};
