#pragma once
#include "CollisionBox.h"
#include "Enemy.h"
#include "Player.h"
// #include "Bullet.h"

bool IsCollision(const CollisionBox& box1, const Position& pos1, const CollisionBox& box2, const Position& pos2);

void CheckCollision(Player& player, Enemy* enemy);
void CheckCollision(Enemy* enemy, Bullet* bullet);
void CheckCollision(Enemy* enemy1, Enemy* enemy2);
void CheckCollision(Bullet* bullet, int winWidth, int winHeight);
