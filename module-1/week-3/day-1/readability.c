#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    char *text = get_string("Text: ");
    int grade;
    int
        valid_chars,
        words,
        sentences;

    float char_avg,
        sen_avg;

    char_avg = sen_avg = 0.0;
    valid_chars = words = sentences = 0;

    int text_len = strlen(text);

    for (int c = 0; c < text_len; c++)
    {

        switch (text[c])
        {
        // new word
        case ' ':
            words++;
            break;
        // sentence ending
        case '.':
        case '!':
        case '?':
            sentences++;
            break;
        }
        if (isalpha(text[c]))
            valid_chars++;
    }
    // add last word
    words++;

    char_avg = ((float)valid_chars / (float)words) * 100;
    sen_avg = ((float)sentences / (float)words) * 100;

    float index = (0.0588 * char_avg) - (0.296 * sen_avg) - 15.8;

    grade = (int)round(index);

    if (grade > 16)
    {

        printf("Grade 16+\n");
        return 0;
    }

    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    printf("Grade %i\n", grade);
}
