#include <iostream>
#include "../include/GraphicsSystem.h"
#include "../include/Player.h"
#include "../include/Enemy.h"
#include "../include/EnemySpawner.h"
// #include "../include/Bullets.h"
#include <vector>

int main(int argc, char** argv) {
	int windowWidth = 1920;
	int windowHwight = 1080;
	GraphicsSystem graphic("Game", windowWidth, windowHwight);
	Player player;
	EnemySpawner spawner;
	std::vector<EnemyPtr> enemies;
	enemies.push_back(spawner.Spawn(windowWidth, windowHwight));
	// vector<Bullets> bullets;
	while(true)
	{

	}
}
/*
	check and process input;
	player shoot;
	spawn enemy;
	check enemies colision with each other;
	check enemies colision with bullets;
	check enemies colision with player;
	check player HP;
	move player;
	move enemy;
	move bullets;
	render all;
*/
