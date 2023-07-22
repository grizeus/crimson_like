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
	
	const int LEVEL_WIDTH = 2560;
	const int LEVEL_HEIGHT = 1440;
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;

	int highScore = 0;

	GraphicsSystem graphic("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	TextureManager textureManager;
	Player player(WINDOW_WIDTH, WINDOW_HEIGHT);
	EnemySpawner enemySpawner;
	BulletSpawner bulletSpawner;
	std::vector<EnemyPtr> enemies;
	std::vector<BulletPtr> bullets;
	std::vector<SDL_Event> events;
	std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>();
	std::shared_ptr<Texture> bgTexture = std::make_shared<Texture>();
	std::shared_ptr<Texture> scoreTexture = std::make_shared<Texture>();
	textureManager.LoadFromFile(graphic.GetRenderer(), playerTexture.get(), "../media/doom.png", player.GetWidth(), player.GetHeight());
	textureManager.LoadFromFile(graphic.GetRenderer(), bgTexture.get(), "../media/bg.png", WINDOW_WIDTH, WINDOW_HEIGHT);
	textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), scoreTexture.get(), "Score: " + std::to_string(highScore), {0x0, 0x0, 0x0, 0x0});
	
	SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

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
		MoveLogic( player, LEVEL_WIDTH, LEVEL_HEIGHT);

		if (countedFrames % 60 == 0)
			enemies.push_back(enemySpawner.Spawn(WINDOW_WIDTH, WINDOW_HEIGHT));
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
			CheckCollision(bullet.get(), LEVEL_WIDTH, LEVEL_HEIGHT);
			bullet->Move();
		}
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			MoveToPlayer(*enemyIt, player);
		}

		// center camera on player
		float playerX = player.GetPosition().x;
		float playerY = player.GetPosition().y;
		int playerW = player.GetWidth();
		int playerH = player.GetHeight();
		camera.x = (static_cast<int>(playerX) + playerW / 2) - WINDOW_WIDTH / 2;
		camera.y = (static_cast<int>(playerY) + playerH / 2) - WINDOW_HEIGHT / 2;
		// Keep camera in bounds
		if (camera.x < 0)
			camera.x = 0;
		if (camera.y < 0)
			camera.y = 0;
		if (camera.x > LEVEL_WIDTH - camera.w)
			camera.x = LEVEL_WIDTH - camera.w;
		if (camera.y > LEVEL_HEIGHT - camera.h)
			camera.y = LEVEL_HEIGHT - camera.h;

		SDL_SetRenderDrawColor(graphic.GetRenderer(), 0xFF, 0xC0, 0xCF, 0xFF);
		SDL_RenderClear(graphic.GetRenderer());
		
		graphic.RenderTexture(*bgTexture, {0, 0}, &camera);
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			graphic.RenderEnemy((*enemyIt)->m_Position, (*enemyIt)->m_Width, (*enemyIt)->m_Height);
		}
		if (newHighScore > highScore) {
			highScore = newHighScore;
			textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), scoreTexture.get(), "Score: " + std::to_string(highScore), {0x0, 0x0, 0x0, 0x0});
		}
		graphic.RenderTexture(*scoreTexture, {0, 0});
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
			graphic.RenderBullet((*bulletIt)->m_StartPosition, (*bulletIt)->m_Width, (*bulletIt)->m_Height);
		}

		graphic.RenderTexture(*playerTexture, {player.GetPosition().x - camera.x, player.GetPosition().y - camera.y});
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
