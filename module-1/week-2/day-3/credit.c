#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int get_digits_sum(int num);
int parse_digit(char digit);
void get_cc_digits(int *target, char *cc_number);
void reverse_array(int *target, int len);
bool is_valid_number(char *str);

int main(void)
{
    string credit_card = get_string("Number: ");
    // Ask until we get valid input
    while (!is_valid_number(credit_card))
    {
        credit_card = get_string("Number: ");
    }

    int len = strlen(credit_card);

    // Check if it's a valid VISA, MC, AMEX number
    if (len != 13 && len != 16 && len != 15)
    {
        printf("INVALID\n");
        return 0;
    }

    int all_digits[len];
    /* Parse digits and move them to the array */
    get_cc_digits(all_digits, credit_card);
    /* Reverse digits so we can start counting at odd indexes */
    reverse_array(all_digits, len);

    int digits_sum = 0;
    for (int i = 0; i < len; i++)
    {
        int val = all_digits[i];
        if (i % 2 != 0)
        {
            // if it's odd we add the sum of digits of twice the current value
            digits_sum += get_digits_sum(val * 2);
        }
        else
        {
            //else we just add the current value
            digits_sum += val;
        }
    }

    // If the last digit is 0, i.e. divisible by 10...
    if (digits_sum % 10 == 0)
    {
        int f_digit = parse_digit(credit_card[0]);
        int s_digit = parse_digit(credit_card[1]);

        /* check which card it is */
        if (f_digit == 3 && (s_digit == 4 || s_digit == 7))
        {
            printf("AMEX\n");
            return 0;
        }

        if (f_digit == 5 && s_digit >= 1 && s_digit <= 5)
        {
            printf("MASTERCARD\n");
            return 0;
        }

        if (f_digit == 4)
        {
            printf("VISA\n");
            return 0;
        }
    }

    // Card must be invalid
    printf("INVALID\n");
}

/* Returns sum of digits of number */
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

int parse_digit(char digit)
{
    return digit - '0';
}

/* Copies all digits from a credit card string to an array */
void get_cc_digits(int *target, char *cc_number)
{
    int len = strlen(cc_number);
    for (int i = 0; i < len; i++)
    {
        target[i] = parse_digit(cc_number[i]);
    }
}

/*  Reverses Array In Place */
void reverse_array(int *target, int len)
{
    for (int i = 0; i < len - i - 1; i++)
    {
        int tmp = target[i];
        target[i] = target[len - i - 1];
        target[len - i - 1] = tmp;
    }
}

/* Returns true if entire string only has digits */
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