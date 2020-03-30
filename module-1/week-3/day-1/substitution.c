#import <stdio.h>
#import <cs50.h>
#import <string.h>
#import <ctype.h>
#define CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void str_tolower(char *str);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *cipher = argv[1];
    int cipher_len = strlen(argv[1]);

    if (cipher_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // case doesn't matter so lowercase the cipher
    str_tolower(cipher);

    // check if key is valid
    for (int i = 0; i < cipher_len; i++)
    {

        // does the key contain invalid characters?
        if (!isalpha(cipher[i]))
        {
            printf("Invalid Key\n");
            return 1;
        }

        //check if same character appears afterwards
        for (int j = i + 1; j < cipher_len; j++)
        {
            if (cipher[i] == cipher[j])
            {
                printf("Invalid Key\n");
                return 1;
            }
        }
    }

    char *text = get_string("plaintext: ");
    int text_len = strlen(text);

    for (int i = 0; i < text_len; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            // get replace index
            char c = text[i];
            if (isalpha(c) && (char)toupper(c) == CHARS[j])
            {
                // replace
                if (islower(c))
                {
                    text[i] = cipher[j];
                }
                else
                {
                    text[i] = (char)toupper(cipher[j]);
                }
                // avoid further replacements
                break;
            }
        }
    }

    printf("ciphertext: %s\n", text);
    return 0;
}

void str_tolower(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        str[i] = (char)tolower(str[i]);
    }
}