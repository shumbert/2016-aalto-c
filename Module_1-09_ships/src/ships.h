#define NOSHIP '.'
#define SHIP '+'
#define SUNKEN '#'

struct field_st {
    char ship;
    char vis;
};

/* given functions */
void create_field(void);
int place_ship(unsigned int xp, unsigned int yp, int dir);
int is_visible(unsigned int x, unsigned int y);
char is_ship(unsigned int x, unsigned int y);
void hit_ship(unsigned int x, unsigned int y);
void checked(unsigned int x, unsigned int y);

/* Student functions*/
void set_ships(unsigned int num);
void print_field(void);
int shoot(void);
int game_over(unsigned int num);
