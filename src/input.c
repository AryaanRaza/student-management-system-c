#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"


int isNumber(char *str)
{
    if (str[0] == '\0') // empty input
        return 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }

    return 1; // true, valid number
}

int safeInputInt(const char *prompt, int min, int max)
{
    char input[100];
    int value = 0, len;

    while (1)
    {
        printf("%s", prompt);
        // Input from user as string to avoid crashing if user gives string instead of int.

        fgets(input, sizeof(input), stdin);

        // Remove new line.
        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        // Check if number is Valid
        if (!isNumber(input))
        {
            printf("Invalid input! Please enter a valid integer.\n");
            continue;
        }

        // Convert to Integer
        value = atoi(input);

        // Checks Rangs
        if (value < min || value > max)
        {
            printf("Please enter a number between %d and %d.\n", min, max);
            continue; // ask again
        }
        return value; // valid input, return it
    }
}