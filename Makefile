connectn.out: main.o game_compute.o
	gcc -g -Wall -Werror -o connectn.out main.o game_compute.o

main.o: main.cpp game_compute.cpp game_compute.h
	gcc -g -Wall -Werror -c main.cpp

game_compute.o: game_compute.cpp game_compute.h
	gcc -g -Wall -Werror -c game_compute.cpp

clean:
	rm -f *.o *.out
