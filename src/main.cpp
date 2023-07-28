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
	
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int levelWidth, levelHeight;
	SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	int highScore = 0;

	GraphicSystem::Init("Game", WINDOW_WIDTH, WINDOW_HEIGHT);

	auto playerID = TextureManager::GetInstance()->Loadtexture("../media/doom.png");
	auto bgID = TextureManager::GetInstance()->Loadtexture("../media/tileset.png");
	auto enemyID = TextureManager::GetInstance()->Loadtexture("../media/enemy.png");
	auto bulletID = TextureManager::GetInstance()->Loadtexture("../media/projectile.png");
	auto scoreID = TextureManager::GetInstance()->CreateTexture("Score: " + std::to_string(highScore), {0x0, 0x0, 0x0, 0x0});

	Terrain terrain(bgID, 100);
	Player player(terrain.GetWidth() / 2, terrain.GetHeight() / 2);
	EnemySpawner enemySpawner;
	BulletSpawner bulletSpawner;

	std::vector<EnemyPtr> enemies;
	std::vector<BulletPtr> bullets;
	std::vector<SDL_Event> events;
	
	terrain.CreateTile('a', {0,0,100,100});
	terrain.CreateTile('b', {100,0,100,100});
	terrain.CreateTile('c', {200,0,100,100});
	terrain.LoadMap("../media/map.txt");
	Timer timer;
	Timer capTimer;
	int countedFrames = 0;
	int frameTicks = 0;
	float avgFPS = 0;
	auto fpsID = TextureManager::GetInstance()->CreateTexture("Avg FPS: " + std::to_string(avgFPS), {0x0, 0x0, 0x0, 0x0});
	constexpr float ticksPerFrame = 1000.0 / 144.0; // 60 FPS
	timer.Start();

	while(true) {
		InputHandler(events);
		if (Quit(events))
			break;
		MoveLogic( player, terrain.GetWidth(), terrain.GetHeight());

		if (countedFrames % 120 == 0)
			enemies.push_back(enemySpawner.Spawn(terrain.GetWidth(), terrain.GetHeight()));
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
			CheckCollision(bullet.get(), terrain.GetWidth(), terrain.GetHeight());
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
		if (camera.x + camera.w >= terrain.GetWidth())
			camera.x = terrain.GetWidth() - camera.w;
		if (camera.y + camera.h >= terrain.GetHeight())
			camera.y = terrain.GetHeight() - camera.h;

		SDL_SetRenderDrawColor(GraphicSystem::GetRenderer(), 0xFF, 0xC0, 0xCF, 0xFF);
		SDL_RenderClear(GraphicSystem::GetRenderer());
		
		terrain.RenderTerrain(camera);

		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			SDL_Rect enemyRect = {static_cast<int>((*enemyIt)->m_Position.x), static_cast<int>((*enemyIt)->m_Position.y), (*enemyIt)->m_Width, (*enemyIt)->m_Height};
			TextureManager::GetInstance()->RenderTexture(enemyID, nullptr, &enemyRect);
		}
		if (newHighScore > highScore) {
			highScore = newHighScore;
			TextureManager::GetInstance()->CreateTexture("Score: " + std::to_string(highScore), scoreID, {0x0, 0x0, 0x0, 0x0});
		}
		TextureManager::GetInstance()->CreateTexture("Avg FPS: " + std::to_string(avgFPS), fpsID, {0x0, 0x0, 0x0, 0x0});
		SDL_Rect scoreRect = {10, 10, WINDOW_WIDTH / 9, WINDOW_HEIGHT / 72};
		SDL_Rect fpsRect = {10, 30, WINDOW_WIDTH / 9, WINDOW_HEIGHT / 72};
		TextureManager::GetInstance()->RenderTexture(scoreID, nullptr, &scoreRect);
		TextureManager::GetInstance()->RenderTexture(fpsID, nullptr, &fpsRect);
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
			SDL_Rect bulletRect = {static_cast<int>((*bulletIt)->m_StartPosition.x), static_cast<int>((*bulletIt)->m_StartPosition.y), (*bulletIt)->m_Width, (*bulletIt)->m_Height};
			TextureManager::GetInstance()->RenderTexture(bulletID, nullptr, &bulletRect);
		}
		// std::cout << "Player x " << player.GetPosition().x << " y" << player.GetPosition().y << std::endl;
		// std::cout << "Camera x " << camera.x << " y" << camera.y << std::endl;
		SDL_Rect dst = {WINDOW_WIDTH / 2 - player.GetWidth() / 2,
			WINDOW_HEIGHT / 2 - player.GetHeight() / 2,
			player.GetWidth(), player.GetHeight()};
		TextureManager::GetInstance()->RenderTexture(playerID, nullptr, &dst);	
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

	TextureManager::GetInstance()->Clear();

	return 0;
}
