#ifndef FIELD_H
#define FIELD_H

#include <stdbool.h>
#include <stdint.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define FIELD_COLUMNS 10
#define FIELD_ROWS 10
#define SHIP_LENGTH 3

typedef struct field_t field_t;
typedef struct ship_t ship_t;
typedef enum { vertical, horizontal, diagonal } ship_direction_t;
typedef struct tile_t tile_t;

void init_field(field_t *field);
void print_field(field_t *field);
bool put_ship(field_t *field, ship_t *ship);

struct ship_t
{
    uint8_t column_idx;
    uint8_t row_idx;
    ship_direction_t direction;
};

struct tile_t
{
    char value;
};

struct field_t
{
    tile_t tiles[FIELD_COLUMNS][FIELD_ROWS];

};

#endif /* FIELD_H */