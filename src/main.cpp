#include "chip_8.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <stdexcept>

Chip_8 emulator;
int main(int argc, char** argv) {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error("SDL Init fail to initilized");
	}
	// set up render system and register input callback
	// setupGraphics()
	// setupInput()

	//Initialized chip8 system and load game
	emulator.initialized();
	// emulator.load_game("pong");
	// std::cout << argv[1] << std::endl;

	//while(true) {
	// Emulate one cycle
	emulator.emulate_cycle();

	if(emulator.draw_flag) {
		//drawgraphics()
	}

	emulator.set_keys();
	//}
	return 0;
}
