#include "chip_8.h"
#include <stdexcept>
#include <stdio.h>
#include <ctype.h>

/**
 * Initialized emulator. Funtion will clear display, memory, register, stack
 * timers, and keys. Also fonts are loaded into memory at location 0x050 to 0x1FF.
 */
void Chip_8::initialized(void) {
    draw_flag = false;
    pc = 0x200;
    delay_timer = 60;
    sound_timer = 60;
    opcode = 0;
    I = 0;
    sp = 0;

    // clear display and memory
    for(int i = 0; i < 64 * 32; ++i) {
        display[i] = 0;
        memory[i] = 0;
        memory[i + 2048] = 0;
    }

    // clear stack, V0 - VF register, and keys
    for(int i = 0; i < 16; ++i) {
        stack[i] = 0;
        V[i] = 0;
        keys[i] = 0;
    }

    // load fonts to memory at 0x050 - 0x1FF
    for(int i = 0; i < 80; ++i) {
        memory[80 + i] = fonts[i];
    }
}

/**
 * Function that load the given ROM into memory.
 *
 * @param ROM String of path to the ROM file.
 * @throws std::invalid_argument Thrown if the ROM path is invalid or the ROM file is corrupted.
 * @throws std::length_error Thrown if ROM file is larger then the system memory, 3584 kb in this case.
 */
void Chip_8::load_game(const char* ROM) {
    FILE* rom_file;
    char buffer[3584]; // 3584 kb are left for game storage, first 512 kb are reserved
    int len;

    rom_file = fopen(ROM, "r");
    if (rom_file == NULL) {
        throw std::invalid_argument("The ROM given produce an empty file");
    }

    fseek(rom_file, 0, SEEK_END);
    len = ftell(rom_file);

    if (len > 3584) {
        throw std::length_error("The ROM file's size is too large");
    }

    while(!feof(rom_file)) {
        if (fgets(buffer, 3584, rom_file) == NULL) break;
    }

    for(int i = 0; i < len; ++i) {
        memory[i + 512] = buffer[i];
    }

    fclose(rom_file);
}

/**
 * Emulate a single cycle of the game.
 */
void Chip_8::emulate_cycle(void) {
    opcode = memory[pc] << 8 | memory[pc + 1];

    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x00F0) {
                case 0x00E0:
                    switch(opcode & 0x000F) {
                        case 0x0000: // 00E0
                            for(int i = 0; i < 2048; ++i) {
                                display[i] = 0;
                            }
                            break;
                        case 0x000E: // 00EE
                            break;
                        default:
                            printf("Unknown opcode: 0x%X\n", opcode);
                            break;
                    }
                    break;
                default: // 0NNN
                    break;
            }
            break;
        case 0x1000: // 1NNN
            break;
        case 0x2000: // 2NNN
            break;
        case 0x3000: // 3XNN
            break;
        case 0x4000: // 4XNN
            break;
        case 0x5000: // 5XY0
            break;
        case 0x6000: // 6XNN
            break;
        case 0x7000: // 7XNN
            break;
        case 0x8000:
            switch(opcode & 0x000F) {
                case 0x0000: // 8XY0
                    break;
                case 0x0001: // 8XY1
                    break;
                case 0x0002: // 8XY2
                    break;
                case 0x0003: // 8XY3
                    break;
                case 0x0004: // 8XY4
                    break;
                case 0x0005: // 8XY5
                    break;
                case 0x0006: // 8XY6
                    break;
                case 0x0007: // 8XY7
                    break;
                case 0x000E: // 8XYE
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
                    break;
            }
            break;
        case 0x9000: // 9XY0
            break;
        case 0xA000: // ANNN
            break;
        case 0xB000: // BNNN
            break;
        case 0xC000: // CXNN
            break;
        case 0xD000: // DXYN
            break;
        case 0xE000:
            switch(opcode & 0x000F) {
                case 0x000E: // EX9E
                    break;
                case 0x0001: // EXA1
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x000F) {
                case 0x0007: // FX07
                    break;
                case 0x000A: // FX0A
                    break;
                case 0x0005:
                    switch(opcode & 0x00F0) {
                        case 0x0010: // FX15
                            break;
                        case 0x0050: // FX55
                            break;
                        case 0x0060: // FX65
                            break;
                        default:
                            printf("Unknown opcode: 0x%X\n", opcode);
                            break;
                    }
                    break;
                case 0x0008: // FX18
                    break;
                case 0x000E: // FX1E
                    break;
                case 0x0009: // FX29
                    break;
                case 0x0003: // FX33
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
                    break;
            }
            break;
        default:
            printf("Unknown opcode: 0x%X\n", opcode);
    }
}

void Chip_8::set_keys(void) {

}

/**
 * Push the given address onto the stack.
 *
 * @param address The address to push to the stack.
 * @throws std::overflow_error Thrown when the stack is full and there is an attempt to add
 * another address.
 */
void Chip_8::push(short address) {
    if (sp < 16) {
        stack[sp++] = address;
    } else {
        throw std::overflow_error("sp value is 16 or over");
    }
}

/**
 * Pop the top address from the stack.
 *
 * @return the address on the top of the stack.
 * @throws std::underflow_error Thrown when attempting to pop and empty stack.
 */
short Chip_8::pop(void) {
    if (sp <= 0) {
        throw std::underflow_error("sp value is 0 or less");
    }
    return stack[--sp];
}
