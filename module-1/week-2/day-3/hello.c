#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char* name;
    name = get_string("What is your name?\n");
    printf("hello, %s\n",name);
}
