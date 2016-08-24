CHECK_CFLAGS=$(shell pkg-config --cflags check)
CHECK_LDFLAGS=$(shell pkg-config --libs check)
SRC_FILES=
SRC_FILES_W=$(SRC_FILES) .wrap.c
SRC_TESTER=test_source.c tmc-check.c checkhelp.c

CFLAGS= -g -Wall -Wextra -Wvla -std=c99

PWD=$(shell pwd)

all: test

test: $(SRC_FILES) ../src/arraytool.h
	gcc $(CHECK_CFLAGS) -g -Wall -Wextra -Werror -Wvla -Wformat-security -std=c99 -o $@ $(SRC_FILES) $(SRC_TESTER) $(CHECK_LDFLAGS)

clean:
	rm -f test tmc_available_points.txt tmc_test_results.xml valgrind.log mockinput mockoutput
	rm -f *.so *.o

run: test
	# Printing available points
	./test --print-available-points
	./test
get-points:
	./test --print-available-points
