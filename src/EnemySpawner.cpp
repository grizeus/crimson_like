#include "../include/EnemySpawner.h"
#include <cstdlib>
#include <time.h>

EnemyPtr EnemySpawner::Spawn(int win_width, int win_height ) { 
    srand(static_cast<unsigned>(time(nullptr)));
    EnemyPtr enemy = std::make_shared<Enemy>();

    int temp_x = rand() % win_width;
    if (temp_x + enemy->m_Width > win_width)
        enemy->m_Position.x = temp_x - enemy->m_Width;
    else 
        enemy->m_Position.x = temp_x;
    
    int temp_y = rand() % win_height;
    if (temp_y + enemy->m_Height > win_height)
        enemy->m_Position.y = temp_y - enemy->m_Height;
    else 
        enemy->m_Position.y = temp_y;
    
    enemy->m_Direction = static_cast<Direction>(rand() % 4);
    return enemy;
}
