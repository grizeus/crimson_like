#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Bullets.h"

void MoveToPlayer(EnemyPtr enemy, Player& player);
void ProjectileToPoint(BulletPtr bullet);
