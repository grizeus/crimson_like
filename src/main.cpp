#include <iostream>
#include "../include/GraphicsSystem.h"
#include "../include/TextureManager.h"
#include "../include/InputLogic.h"
#include "../include/CheckCollision.h"
#include "../include/Player.h"
#include "../include/EnemySpawner.h"
#include "../include/EnemyAI.h"
#include "../include/Timer.h"
// #include "../include/Bullets.h"
#include <vector>

int main(int argc, char** argv) {
	int windowWidth = 1920;
	int windowHwight = 1080;

	GraphicsSystem graphic("Game", windowWidth, windowHwight);
	TextureManager textureManager;
	Player player;
	EnemySpawner spawner;
	std::vector<EnemyPtr> enemies;
	// vector<Bullets> bullets;
	//
	std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>();
	textureManager.LoadFromFile(graphic.GetRenderer(), playerTexture.get(), "../media/doom.png", player.GetWidth(), player.GetHeight());
	
	Timer timer;
	Timer capTimer;
	int countedFrames = 0;
	timer.Start();

	while(true) {
		InputLogic(InputHandler(), player);
		enemies.push_back(spawner.Spawn(windowWidth, windowHwight));
		std::vector<EnemyPtr>::iterator it;
		for (it = enemies.begin(); it != enemies.end(); ++it) {
			for (auto it2 = it + 1; it2 != enemies.end(); ++it2) {
				if (it != it2) {
					CheckCollision(it->get(), it2->get());
				}
			}
			CheckCollision(player, it->get());
		}
		for (it = enemies.begin(); it != enemies.end(); ++it) {
			MoveToPlayer(*it, player);
		}
		for (it = enemies.begin(); it != enemies.end(); ++it) {
			graphic.RenderEnemy((*it)->m_Position, (*it)->m_Width, (*it)->m_Height);
		}
		graphic.RenderTexture(*playerTexture, player.GetPosition(), player.GetWidth(), player.GetHeight());
	}

	return 0;
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
