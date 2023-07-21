#include <iostream>
#include "../include/GraphicsSystem.h"
#include "../include/TextureManager.h"
#include "../include/InputLogic.h"
#include "../include/CheckCollision.h"
#include "../include/Player.h"
#include "../include/EnemySpawner.h"
#include "../include/EnemyAI.h"
#include "../include/Timer.h"
#include "../include/BulletSpawner.h"
#include <vector>

int main(int argc, char** argv) {

	int windowWidth = 1920;
	int windowHwight = 1080;

	int highScore = 0;

	GraphicsSystem graphic("Game", windowWidth, windowHwight);
	TextureManager textureManager;
	Player player(windowWidth, windowHwight);
	EnemySpawner enemySpawner;
	BulletSpawner bulletSpawner;
	std::vector<EnemyPtr> enemies;
	std::vector<BulletPtr> bullets;
	std::vector<SDL_Event> events;
	std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>();
	std::shared_ptr<Texture> scoreTexture = std::make_shared<Texture>();
	textureManager.LoadFromFile(graphic.GetRenderer(), playerTexture.get(), "../media/doom.png");
	textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), scoreTexture.get(), "Score: " + std::to_string(highScore), {0, 0, 0, 0});

	Timer timer;
	Timer capTimer;
	int countedFrames = 0;
	int frameTicks = 0;
	float avgFPS = 0;
	const float ticksPerFrame = 1000.0 / 144.0; // 60 FPS
	timer.Start();
	while(true) {
		InputHandler(events);
		if (Quit(events))
			break;
		MoveLogic( player );
		if (countedFrames % 30 == 0)
			enemies.push_back(enemySpawner.Spawn(windowWidth, windowHwight));
		auto bullet = bulletSpawner.Spawn(player, events);
		if (bullet)
			bullets.push_back(bulletSpawner.Spawn(player, events));
		events.clear();
		std::vector<EnemyPtr>::iterator enemyIt;
		int newHighScore = highScore;
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			for (auto it2 = enemyIt + 1; it2 != enemies.end(); ++it2) {
				if (enemyIt != it2) {
					// colissions btw enemies
					CheckCollision(enemyIt->get(), it2->get());
				}
			}
			for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
				// colissions btw enemies and bullets
				CheckCollision(enemyIt->get(), bulletIt->get());
				if (bulletIt->get()->m_HP <= 0) {
					bullets.erase(bulletIt);
					break;
				}
			}
			CheckCollision(player, enemyIt->get());
			if (enemyIt->get()->m_HP <= 0) {
				newHighScore += 10;
				enemies.erase(enemyIt);
				break;
			}
		}
		for (auto& bullet : bullets) {
			CheckCollision(bullet.get(), windowWidth, windowHwight);
			bullet->Move();
		}
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			MoveToPlayer(*enemyIt, player);
		}

		SDL_SetRenderDrawColor(graphic.GetRenderer(), 0xFF, 0xC0, 0xCF, 0xFF);
		SDL_RenderClear(graphic.GetRenderer());
		
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			graphic.RenderEnemy((*enemyIt)->m_Position, (*enemyIt)->m_Width, (*enemyIt)->m_Height);
		}
		if (newHighScore > highScore) {
			highScore = newHighScore;
			textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), scoreTexture.get(), "Score: " + std::to_string(highScore), {0, 0, 0, 0});
		}
		graphic.RenderTexture(*scoreTexture, {0, 0}, windowWidth / 20 , windowHwight / 30);
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
			graphic.RenderBullet((*bulletIt)->m_StartPosition, (*bulletIt)->m_Width, (*bulletIt)->m_Height);
		}
		graphic.RenderTexture(*playerTexture, player.GetPosition(), player.GetWidth(), player.GetHeight()); 
		SDL_RenderPresent(graphic.GetRenderer());

		avgFPS = countedFrames / (timer.GetTicks() / 1000.f);
		printf("FPS: %f\n", avgFPS);
		// printf("Vector size: %zu\n", enemies.size());
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
