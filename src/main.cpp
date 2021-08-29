#include "chip_8.h"
#include <iostream>
#include "SDL2/SDL.h"

Chip_8 emulator;
int main(int argc, char** argv) {

	try {
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			throw "SDL Init fail to initilized";
		}
		// set up render system and register input callback
		// setupGraphics()
		// setupInput()

		//Initialized chip8 system and load game
		emulator.initialized();
		// emulator.load_game("pong");
		// std::cout << argv[1] << std::endl;
	} catch(const char* e) {
		std::cout << e << std::endl;
		return 1;
	}

	//while(true) {
	// Emulate one cycle
	emulator.emulate_cycle();

	if(emulator.draw_flag) {
		//drawgraphics()
		emulator.draw_flag = false;
	}

	emulator.set_keys();
	//}

	SDL_Quit();
	return 0;
}
