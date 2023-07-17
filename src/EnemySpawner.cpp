#include "../include/EnemySpawner.h"
#include <cstdlib>
#include <time.h>

EnemyPtr EnemySpawner::Spawn(int winWidth, int winHeight ) { 
    srand(static_cast<unsigned>(time(nullptr)));
    EnemyPtr enemy = std::make_shared<Enemy>();

    int temp_x = rand() % winWidth;
    if (temp_x + enemy->m_Width > winWidth)
        enemy->m_Position.x = temp_x - enemy->m_Width;
    else 
        enemy->m_Position.x = temp_x;
    
    int temp_y = rand() % winHeight;
    if (temp_y + enemy->m_Height > winHeight)
        enemy->m_Position.y = temp_y - enemy->m_Height;
    else 
        enemy->m_Position.y = temp_y;
    
    enemy->m_Direction = static_cast<Direction>(rand() % 4);
    return enemy;
}
