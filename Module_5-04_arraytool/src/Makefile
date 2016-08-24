SRC_FILES=main.c

all: main arraytool.h

main: $(SRC_FILES)
	gcc -pedantic -Wall -Wextra -Wvla -Wformat-security -std=c99 -g -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
