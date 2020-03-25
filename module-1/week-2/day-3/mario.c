#include <cs50.h>
#include <string.h>
#include <stdio.h>

void print_piramid_line(int height, int level)
{
    int _spaces = level - 1;
    int _bricks = height - level + 1;
    char bricks[_bricks + 1];

    //terminate string
    bricks[_bricks] = '\0';
    memset(bricks, '#', sizeof(char) * _bricks);
    if (_spaces > 0)
    {
        char spaces[_spaces + 1];

        //terminate string
        spaces[_spaces] = '\0';
        memset(spaces, ' ', sizeof(char) * _spaces);
        printf("%s%s  %s%s\n", spaces, bricks, bricks, spaces);
    }
    else
    {
        printf("%s  %s\n", bricks, bricks);
    }
}

int main(void)
{
    int height = get_int("Height: ");

    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    int current_level = height;

    while (current_level != 0)
    {
        printf("%i", current_level);
        print_piramid_line(height, current_level);
        current_level--;
    }
}
