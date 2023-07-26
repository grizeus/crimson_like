cmake_minimum_required(VERSION 3.22)

set(This crimson_UT)

set(Sources
	# "../src/Bullets.cpp"
	# "../src/BulletSpawner.cpp"
	# "../src/CheckCollision.cpp"
	# "../src/Enemy.cpp"
	# "../src/EnemyAI.cpp"
	# "../src/EnemySpawner.cpp"
	# "../src/GraphicSystem.cpp"
	# "../src/InputLogic.cpp"
	# "../src/Player.cpp"
	# "../src/Terrain.cpp"
	# "../src/Texture.cpp"
	"../src/TextureManager.cpp"
	# "../src/Timer.cpp"
	# "../include/Bullets.h"
	# "../include/BulletSpawner.h"
	# "../include/CheckCollision.h"
	# "../include/Enemy.h"
	# "../include/EnemyAI.h"
	# "../include/EnemySpawner.h"
	# "../include/GraphicSystem.h"
	# "../include/InputLogic.h"
	# "../include/Orientation.h"
	# "../include/Player.h"
	# "../include/Terrain.h"
	# "../include/Texture.h"
	"../include/TextureManager.h"
	# "../include/Timer.h"
    Crimson_UT.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
)

add_test(
    NAME ${This}
    COMMAND ${This}
)

add_custom_command(
    TARGET ${This}
    COMMENT "Run tests"
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^crimson_UT" --output-on-failures
)
