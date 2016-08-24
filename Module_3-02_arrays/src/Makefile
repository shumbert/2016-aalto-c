SRC_FILES=main.c source.c

all: main

main: $(SRC_FILES)
	gcc -Wall -Wextra -Wvla -pedantic -std=c99 -g -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
