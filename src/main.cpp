#include <iostream>
#include "../include/SDL_Tools.h"
#include "../include/Player.h"


int main(int argc, char** argv) {
	// SDL_Tools* tool = new SDL_Tools();
	ToolsPtr tool = std::make_shared<SDL_Tools>();
	tool->ToolsInit();
	Player player(tool);
	std::cout << "Hello from crimson game!" << std::endl;
	while(true) {
		SDL_RenderClear(tool->m_Renderer);
		player.Draw();
		SDL_RenderPresent(tool->m_Renderer);
	}
	tool->ToolsQuit();
	return 0;
}
