#include <stdio.h>

#include <field.h>


int main()
{
    field_t field;
    ship_t ship1 = {.column_idx = 5, .row_idx = 6, vertical};
    ship_t ship2 = {.column_idx = 7, .row_idx = 3, horizontal};
    ship_t ship3 = {.column_idx = 1, .row_idx = 1, diagonal};
    ship_t *ships[] = {&ship1, &ship2, &ship3};

    init_field(&field);

    for (uint8_t i = 0; i < sizeof(ships) / sizeof(ship_t *); i++)
    {
        bool status = put_ship(&field, ships[i]);

        if (status == false)
        {
            printf("Erro ao posicionar navio\n");
            return 1;
        }
    }

    print_field(&field);

    return 0;
}