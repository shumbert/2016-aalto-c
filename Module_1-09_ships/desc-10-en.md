title: Ship Sinker
task_id: 09-ships
points: 4


**Objective:** Practice use of function calls as part of a (slightly)
bigger program

We will now implement a basic ship sinking game. Because it requires
features of C language that have not yet been discussed so far, part
of the functions are already given to you, and you will implement four
additional functions to complete the logic.

The game field is 10x10 squares, and each ship is 3 squares tall. The
coordinate range is between 0 and 9 both vertically and horizontally
(i.e., (0,0) is the upper left corner; (9,9) is the lower right).
The game ends when all ships are sunk.

The exercise code is divided into two c source files. **shiplib.c**
contains support functions for operating the game field. You will need
to call these functions in the exercise tasks, but you should not
modify this file. See the comments in the source code for explanations
about how this functions are used. **ships.c** contains the functions
you will need to implement.

You will need to implement four functions as follows. You will gain a
point for each of them, if implemented by the primary deadline.

a) Place ships
-----------------

Implement function `void set_ships(unsigned int num)` that places
'**num**' ships to the game field. To place one ship at given
location, you should call function **place_ship()**, with the
location and direction of the ship (see source code for detailed
explanation). Note that **place_ship()** function fails if you try to
place ship to a location that overlaps with an existing ship, or goes
out of bounds, so you'll need to investigate its return value.

**Hint:** You can use C library function
**[rand()](http://linux.die.net/man/3/rand)** to pick a random
location and direction for a ship. The function returns a random
integer, which you can scale to the appropriate range using the
*modulo* operation (`%`). For example, `rand() % 10` produces random
numbers between 0 and 9.

b) Print gamefield
--------------------

Implement function `void print_field(void)` that prints the whole
gamefield on screen. If a location **is not** yet visible to user, '?'
should be printed. If the location **is** visible (i.e., it has been
shot at already), there are three options to be printed:

  * '.' if the location does not have a ship
  * '+' if the location has a part of a ship that has not yet been hit (when is
this needed?)
  * '#' if the location has a part of a ship that has been hit 

Initially all sectors are invisible, and a sector becomes visible
when the player shoots at it.

You will need to use two functions: **is_visible(x,y)** tells whether
the given sector is visible to the player. **is_ship(x,y)** tells
whether a location has a ship, and if it is hit. See the source code
comments at 'shiplib.c' for more detailed descriptions of these functions.

c) Shoot
-----------

Implement function `int shoot(void)` that asks two unsigned numbers from the
user, separated by space, that represent coordinates in the game
field. If user input is invalid or coordinates are out of bounds, the
function should return -1. If the given location has ship, the
function should call function **hit_ship()** to mark the location
hit, and return 1. If the given location does not have ship, the
function should return 0. In either case, the function should call
function **checked()** that marks the location visible.

d) End of game
-----------------

Implement function `int game_over(unsigned int num)` that returns 1 if
all ships are sunk, or 0, if there are still ships to be hit. Parameter
'**num**' tells the number of ships on the game field. You know about
ships' status using the **is_ship()** function, and since you know
that each ship occupies 3 squares in game field, you can determine if
all ship positions have been hit.
