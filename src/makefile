chip8: main.o chip_8.o
	g++ -Wall -pedantic-errors -std=c++14 -g -O0 main.o chip_8.o -o chip8

main.o: main.cpp chip_8.h
	gcc -Wall -pedantic-errors -std=c++14 -g -O0 -lSDL2main -lSDL2 -c main.cpp

chip_8.o: chip_8.cpp chip_8.h
	gcc -Wall -pedantic-errors -std=c++14 -g -O0 -c chip_8.cpp

run: chip8
	./chip8

clean:
	rm -rf chip8
	rm -rf *.o
