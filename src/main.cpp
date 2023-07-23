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
#include "../include/Terrain.h"
#include <vector>

int main(int argc, char** argv) {
	
	const int TERRAIN_WIDTH = 2560;
	const int TERRAIN_HEIGHT = 1440;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int levelWidth, levelHeight;
	SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	int highScore = 0;

	GraphicsSystem graphic("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	TextureManager textureManager;
	Player player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	EnemySpawner enemySpawner;
	BulletSpawner bulletSpawner;

	std::vector<EnemyPtr> enemies;
	std::vector<BulletPtr> bullets;
	bullets.reserve(100);
	std::vector<SDL_Event> events;

	std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>();
	std::shared_ptr<Texture> bgTexture = std::make_shared<Texture>();
	std::shared_ptr<Texture> scoreTexture = std::make_shared<Texture>();
	std::shared_ptr<Texture> finalBgTexture = std::make_shared<Texture>();
	// finalizing background texture
	finalBgTexture->SetTexture( SDL_CreateTexture(graphic.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TERRAIN_WIDTH, TERRAIN_HEIGHT));
	SDL_SetRenderTarget(graphic.GetRenderer(), finalBgTexture->GetTexture());
	SDL_SetRenderDrawColor(graphic.GetRenderer(), 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(graphic.GetRenderer());

	textureManager.LoadFromFile(graphic.GetRenderer(), playerTexture.get(), "../media/doom.png", player.GetWidth(), player.GetHeight());
	textureManager.LoadFromFile(graphic.GetRenderer(), bgTexture.get(), "../media/tileset.png", 300, 100);
	textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), scoreTexture.get(), "Score: " + std::to_string(highScore), {0x0, 0x0, 0x0, 0x0});
	SDL_QueryTexture(finalBgTexture->GetTexture(), NULL, NULL, &levelWidth, &levelHeight);

	Terrain terrain(WINDOW_WIDTH, WINDOW_HEIGHT, 100);
	terrain.CreateTile('a', {0,0,100,100});
	terrain.CreateTile('b', {100,0,100,100});
	terrain.CreateTile('c', {200,0,100,100});
	terrain.LoadMap("../media/map.txt");
	terrain.SetTexture(bgTexture);
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
		MoveLogic( player, WINDOW_WIDTH, WINDOW_HEIGHT);

		if (countedFrames % 15 == 0)
			enemies.push_back(enemySpawner.Spawn(WINDOW_WIDTH, WINDOW_HEIGHT));
		auto bullet = bulletSpawner.Spawn(player, events, camera);
		if (bullet && (bullets.size() < 100))
			bullets.push_back(bulletSpawner.Spawn(player, events, camera));
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
			CheckCollision(bullet.get(), levelWidth, levelHeight);
			bullet->Move();
		}
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			MoveTo(*enemyIt, player, camera);
		}

		camera.x = static_cast<int>(player.GetPosition().x) - (WINDOW_WIDTH / 2);
		camera.y = static_cast<int>(player.GetPosition().y) - (WINDOW_HEIGHT / 2);

		if (camera.x < 0)
			camera.x = 0;
		if (camera.y < 0)
			camera.y = 0;
		if (camera.x + camera.w >= levelWidth )
			camera.x = levelWidth - camera.w;
		if (camera.y + camera.h >= levelHeight)
			camera.y = levelHeight - camera.h;

		SDL_SetRenderDrawColor(graphic.GetRenderer(), 0xFF, 0xC0, 0xCF, 0xFF);
		SDL_RenderClear(graphic.GetRenderer());
		
		terrain.RenderTerrain(&graphic);
		SDL_SetRenderTarget(graphic.GetRenderer(), nullptr);
		SDL_RenderCopy(graphic.GetRenderer(), finalBgTexture->GetTexture(), &camera, nullptr /* &destination */);

		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			graphic.RenderEnemy((*enemyIt)->m_Position, (*enemyIt)->m_Width, (*enemyIt)->m_Height);
		}
		if (newHighScore > highScore) {
			highScore = newHighScore;
			textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), scoreTexture.get(), "Score: " + std::to_string(highScore), {0x0, 0x0, 0x0, 0x0});
		}
		graphic.RenderTexture(*scoreTexture, {10, 10}, nullptr);
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
			graphic.RenderBullet((*bulletIt)->m_StartPosition, (*bulletIt)->m_Width, (*bulletIt)->m_Height);
		}
		
		graphic.RenderPlayer(*playerTexture, player.GetPosition(), &camera);
		SDL_RenderPresent(graphic.GetRenderer());

		avgFPS = countedFrames / (timer.GetTicks() / 1000.f);
		// printf("FPS: %f\n", avgFPS);
		// printf("enemies vector size : %zu\n", enemies.size());
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
