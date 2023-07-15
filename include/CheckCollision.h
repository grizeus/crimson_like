#pragma once
#include "CollisionBox.h"
#include "Enemy.h"
#include "Player.h"
// #include "Bullet.h"

bool IsCollision(const CollisionBox&, const Position&, const CollisionBox&, const Position&);

void CheckCollision(Player&, Enemy&);
// void CheckCollision(Enemy&, Bullet&); // TODO: Implement this function
void CheckCollision(Enemy&, Enemy&);
