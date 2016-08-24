SRC_FILES=main.c queue.c

all: main

main: $(SRC_FILES)
	gcc -g -Wall -Wextra -Wvla -pedantic -std=c99 -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
