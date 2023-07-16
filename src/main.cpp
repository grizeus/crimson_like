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
	Player player(windowWidth, windowHwight);
	EnemySpawner spawner;
	std::vector<EnemyPtr> enemies;
	// vector<Bullets> bullets;
	//
	std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>();
	textureManager.LoadFromFile(graphic.GetRenderer(), playerTexture.get(), "../media/doom.png");
	
	Timer timer;
	Timer capTimer;
	int countedFrames = 0;
	int frameTicks = 0;
	float avgFPS = 0;
	const float ticksPerFrame = 1000.0 / 60.0; // 60 FPS
	timer.Start();
	
	while(true) {
		if (InputHandler() == QUIT)
			break;
		InputLogic( player );
		if (countedFrames % 60 == 0)
			enemies.push_back(spawner.Spawn(windowWidth, windowHwight));
		std::vector<EnemyPtr>::iterator it;
		for (it = enemies.begin(); it != enemies.end(); ++it) {
			for (auto it2 = it + 1; it2 != enemies.end(); ++it2) {
				if (it != it2) {
					// colissions btw enemies
					CheckCollision(it->get(), it2->get());
				}
			}
			CheckCollision(player, it->get());
			if (it->get()->m_HP <= 0) {
				enemies.erase(it);
				break;
			}
		}
		for (it = enemies.begin(); it != enemies.end(); ++it) {
			MoveToPlayer(*it, player);
		}
		SDL_SetRenderDrawColor(graphic.GetRenderer(), 0xFF, 0xC0, 0xCF, 0xFF);
		SDL_RenderClear(graphic.GetRenderer());
		
		for (it = enemies.begin(); it != enemies.end(); ++it) {
			graphic.RenderEnemy((*it)->m_Position, (*it)->m_Width, (*it)->m_Height);
		}
		graphic.RenderTexture(*playerTexture, player.GetPosition(), player.GetWidth(), player.GetHeight()); 
		SDL_RenderPresent(graphic.GetRenderer());

		avgFPS = countedFrames / (timer.GetTicks() / 1000.f);
		printf("FPS: %f\n", avgFPS);
		printf("Vector size: %zu\n", enemies.size());
		if (avgFPS > 2000000)
			avgFPS = 0;

		++countedFrames;
		frameTicks = capTimer.GetTicks();
		if (frameTicks < ticksPerFrame)
			SDL_Delay(ticksPerFrame - frameTicks);
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
