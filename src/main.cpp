#include "chip_8.h"

Chip_8 emulator;
int main(void) {

    // set up render system and register input callback
    // setupGraphics()
    // setupInput()

    //Initialized chip8 system and load game
    emulator.initialized();
    // emulator.load_game("pong");

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
