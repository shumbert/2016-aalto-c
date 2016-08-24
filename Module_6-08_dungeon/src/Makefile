SRC_FILES=main.c userif.c mapgen.c monster.c

all: main

main: $(SRC_FILES)
	gcc -pedantic -Wall -Wextra -std=c99 -g -o $@ $(SRC_FILES) -lm

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
