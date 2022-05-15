// savegame.c
// Compile using `gcc -fno-stack-protector savegame.c`

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hero {
    unsigned int hp;
    char name[10];
    unsigned int gold;
};


void secret_function()
{
	printf("You made it!\n");
	return;
}

struct hero setup_hero()
{
    struct hero h;
    h.hp = 30;
    h.gold = 8;

    scanf("%s", h.name);

    return h;
}


int main(int argc, const char *argv[])
{

    struct hero h = setup_hero();

    printf("Name: %s\n", h.name);
    printf("HP: %d | Gold: %d\n", h.hp, h.gold);

    return 0;
}
