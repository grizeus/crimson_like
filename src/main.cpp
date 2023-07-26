#include <iostream>
#include "../include/GraphicSystem.h"
#include "../include/TextureManager.h"
#include "../include/InputLogic.h"
#include "../include/CheckCollision.h"
#include "../include/Player.h"
#include "../include/EnemySpawner.h"
#include "../include/EnemyAI.h"
#include "../include/Timer.h"
#include "../include/BulletSpawner.h"
#include "../include/Terrain.h"
#include <string>
#include <vector>

int main(int argc, char** argv) {
	
	const int TERRAIN_WIDTH = 2560;
	const int TERRAIN_HEIGHT = 1440;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int levelWidth, levelHeight;
	SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	int highScore = 0;

	GraphicSystem::Init("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	auto textureManager = TextureManager::GetInstance();
	Player player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	EnemySpawner enemySpawner;
	BulletSpawner bulletSpawner;

	std::vector<EnemyPtr> enemies;
	std::vector<BulletPtr> bullets;
	std::vector<SDL_Event> events;

	auto playerID = textureManager->Loadtexture("../media/doom.png");
	auto bgID = textureManager->Loadtexture("../media/tileset.png");
	auto scoreID = textureManager->CreateTexture("Score: " + std::to_string(highScore), {0x0, 0x0, 0x0, 0x0});

	Terrain terrain(WINDOW_WIDTH, WINDOW_HEIGHT, 100);
	terrain.CreateTile('a', {0,0,100,100});
	terrain.CreateTile('b', {100,0,100,100});
	terrain.CreateTile('c', {200,0,100,100});
	terrain.LoadMap("../media/map.txt");
	Timer timer;
	Timer capTimer;
	int countedFrames = 0;
	int frameTicks = 0;
	float avgFPS = 0;
	constexpr float ticksPerFrame = 1000.0 / 144.0; // 60 FPS
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

		SDL_SetRenderDrawColor(GraphicSystem::GetRenderer(), 0xFF, 0xC0, 0xCF, 0xFF);
		SDL_RenderClear(GraphicSystem::GetRenderer());
		
		// terrain.RenderTerrain(&graphic, finalBgTexture, &camera, TERRAIN_WIDTH, TERRAIN_HEIGHT);

		// for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
		// 	graphic.RenderEnemy((*enemyIt)->m_Position, (*enemyIt)->m_Width, (*enemyIt)->m_Height);
		// }
		if (newHighScore > highScore) {
			highScore = newHighScore;
			textureManager->CreateTexture("Score: " + std::to_string(highScore), scoreID, {0x0, 0x0, 0x0, 0x0});
		}
		// textureManager.LoadFromRenderedText(graphic.GetRenderer(), graphic.GetFont(), fpsTexture.get(), "Avg FPS: " + std::to_string(avgFPS), {0x0, 0x0, 0x0, 0x0});
		// graphic.RenderTexture(*scoreTexture, {10, 10}, nullptr);
		// graphic.RenderTexture(*fpsTexture, {10, 30}, nullptr);
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
			// graphic.RenderBullet((*bulletIt)->m_StartPosition, (*bulletIt)->m_Width, (*bulletIt)->m_Height);
		}
		
		// graphic.RenderPlayer(*playerTexture, player.GetPosition(), &camera);
		SDL_RenderPresent(GraphicSystem::GetRenderer());

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

	textureManager->Clear();

	return 0;
}
