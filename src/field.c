#include <stdint.h>
#include <stdio.h>

#include <field.h>


void init_field(field_t *field);
static void color_tile(char value);
void print_field(field_t *field);
static void print_field_bottom();
static void print_field_top();
static void print_row(field_t *field, uint8_t row_idx);
bool put_ship(field_t *field, ship_t *ship);


void init_field(field_t *field)
{
    for (uint8_t i = 0; i < FIELD_ROWS; i++)
    {
        for (uint8_t j = 0; j < FIELD_COLUMNS; j++)
            field->tiles[i][j].value = '0';
    }
}

static void color_tile(char value)
{
    switch (value)
    {
        case '0':
            printf(ANSI_COLOR_BLUE);
            break;
        case '3':
            printf(ANSI_COLOR_YELLOW);
            break;
        default:
            printf(ANSI_COLOR_BLUE);
    }
}

static void print_field_top()
{
    printf("\n   ");

    for (uint8_t i = 0; i < FIELD_COLUMNS; i++)
        printf("  %2c", 'A' + i);

    printf("\n    .");

    for (uint8_t i = 0; i < FIELD_COLUMNS; i++)
        printf("---.");

    printf("\n");
}

static void print_field_bottom()
{
    printf("    '");

    for (uint8_t i = 0; i < FIELD_COLUMNS; i++)
        printf("---'");

    printf("\n\n");
}

static void print_row(field_t *field, uint8_t row_idx)
{
    printf(" %2hi |", row_idx);

    for (uint8_t j = 0; j < FIELD_COLUMNS; j++)
    {
        tile_t tile = field->tiles[row_idx - 1][j];

        color_tile(tile.value);
        printf(" %c " ANSI_COLOR_RESET "|", tile.value);
    }

    if (row_idx < FIELD_ROWS)
    {
        printf("\n    :");

        for (uint8_t j = 0; j < FIELD_COLUMNS; j++)
            printf("---:");
    }

    printf("\n");
}

void print_field(field_t *field)
{
    print_field_top();

    for (uint8_t i = 1; i <= FIELD_ROWS; i++)
        print_row(field, i);

    print_field_bottom();
}

bool put_ship(field_t *field, ship_t *ship)
{
    if (field == NULL || ship == NULL)
        return false;

    if (ship->row_idx >= FIELD_ROWS || ship->column_idx >= FIELD_COLUMNS)
        return false;


    int8_t last_row_idx = ship->row_idx + SHIP_LENGTH - 1;
    int8_t last_column_idx = ship->column_idx + SHIP_LENGTH - 1;
    bool it_fits = true;

    switch (ship->direction)
    {
        case vertical:
            if (last_row_idx >= FIELD_ROWS)
                return false;

            for (int8_t i = ship->row_idx; i <= last_row_idx; i++)
            {
                if (field->tiles[i][ship->column_idx].value != '0')
                {
                    it_fits = false;
                    break;
                }
            }

            if (!it_fits)
                return false;

            for (int8_t i = ship->row_idx; i <= last_row_idx; i++)
                field->tiles[i][ship->column_idx].value = '3';

            return true;

        case horizontal:
            if (last_column_idx >= FIELD_COLUMNS)
                return false;

            for (int8_t i = ship->column_idx; i <= last_column_idx; i++)
            {
                if (field->tiles[ship->row_idx][i].value != '0')
                {
                    it_fits = false;
                    break;
                }
            }

            if (!it_fits)
                return false;

            for (int8_t i = ship->column_idx; i <= last_column_idx; i++)
                field->tiles[ship->row_idx][i].value = '3';

            return true;

        case diagonal:
            if (last_column_idx >= FIELD_COLUMNS || last_row_idx >= FIELD_ROWS)
                return false;

            for (int8_t i = ship->row_idx, j = ship->column_idx; i <= last_row_idx; i++, j++)
            {
                if (field->tiles[i][j].value != '0')
                {
                    it_fits = false;
                    break;
                }
            }

            if (!it_fits)
                return false;

            for (int8_t i = ship->row_idx, j = ship->column_idx; i <= last_row_idx; i++, j++)
                field->tiles[i][j].value = '3';

            return true;

        default:
            return false;
    }
}