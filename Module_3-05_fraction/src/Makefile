SRC_FILES=main.c fraction.c

all: main

main: $(SRC_FILES)
	gcc -Wall -Wextra -Wvla -pedantic -g -std=c99 -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
