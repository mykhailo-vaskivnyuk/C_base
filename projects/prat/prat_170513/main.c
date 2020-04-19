/* rhodium.c - стоимость родия, вес которого равен вашему весу */
#include <stdio.h>

int main(void)
{
    float weight; /* вес пользователя */
    float value; /* родиевый эквивалент пользователя */

    printf("Do you want to know ...?\n");
    printf("Let's calculate.\n");
    printf("Enter your weight: ");

    /* получить входные данные от пользователя */
    scanf("%f", &weight);

    /* считаем, что цена родия равна $770 за тройскую унцию */
    /* 14.5833 коэффициент для переводавеса, выраженного в фунтах, в тройские унции */
    value = 770.0 * weight * 14.5833;

    printf("Your ... is $%.2f.\n", value);
    printf("If price ... down,\n");
    printf("eat more for price.\n");

    return 0;
}

