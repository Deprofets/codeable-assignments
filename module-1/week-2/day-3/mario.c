#include <cs50.h>
#include <string.h>
#include <stdio.h>

void print_piramid_line(int height, int level)
{
    int spaces_len = level - 1;
    int bricks_len = height - level + 1;
    char bricks[bricks_len + 1];
    char spaces[spaces_len + 1];

    // terminate strings
    bricks[bricks_len] = '\0';
    spaces[spaces_len] = '\0';
    // fill strings with bricks and spaces
    memset(bricks, '#', sizeof(char) * bricks_len);
    memset(spaces, ' ', sizeof(char) * spaces_len);

    printf("%s%s  %s%s\n", spaces, bricks, bricks, spaces);
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
        print_piramid_line(height, current_level);
        current_level--;
    }
}
