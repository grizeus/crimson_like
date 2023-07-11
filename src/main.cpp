#include <iostream>
#include "../include/SDL_Tools.h"

int main(int argc, char** argv) {
	SDL_Tools* tool = new SDL_Tools();
	tool->ToolsInit();
	std::cout << "Hello from crimson game!" << std::endl;
	tool->ToolsQuit();
	delete tool;
	return 0;
}
