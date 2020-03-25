#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int get_digits_sum(int num);

int invalid(void)
{
    printf("INVALID\n");
    return 1;
}
bool is_valid_number(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    bool is_valid = false;
    string credit_card = get_string("Number: ");
    while (!is_valid_number(credit_card))
    {
        credit_card = get_string("Number: ");
    }
    int len = strlen(credit_card);

    switch (len)
    {
    case 13:
    //VISA
    case 16:
    //VISA OR MC
    case 15:
        //AMEX
        break;
    default:
        invalid();
        return 0;
    }

    int sp_len, other_len = 0;
    if (len % 2 == 0)
    {
        sp_len = other_len = len / 2;
    }
    else
    {
        sp_len = (len - 1) / 2;
        other_len = len - sp_len;
    }

    int special_digits[sp_len];
    int other_digits[other_len];

    for (int i = len - 1, current = 1; i >= 0; i--)
    {
        int val = credit_card[i] - '0';
        if (current % 2 == 0)
        {
            special_digits[i / 2] = val * 2;
        }
        else
        {
            other_digits[current / 2] = val;
        }
        current++;
    }
    //first step
    int result = 0;
    for (int i = 0; i < sp_len; i++)
    {
        result += get_digits_sum(special_digits[i]);
    }
    for (int i = 0; i < other_len; i++)
    {
        result += other_digits[i];
    }
    //printf("%i\n",result);
    if (result % 10 == 0)
    {
        int first_digit = credit_card[0] - '0';
        int second_digit = credit_card[1] - '0';

        if (first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
            return 0;
        }

        if (first_digit == 5 && second_digit >= 1 && second_digit <= 5)
        {
            printf("MASTERCARD\n");
            return 0;
        }

        if (first_digit == 4)
        {
            printf("VISA\n");
            return 0;
        }
    }
    printf("INVALID\n");
}

int get_digits_sum(int num)
{
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
