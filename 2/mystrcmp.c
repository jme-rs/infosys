#include <stdio.h>

// Get the length of the string
int my_strlen(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }
    return len;
}

// Compare two strings
int my_strcmp(char *str1, char *str2)
{
    int str1_len = my_strlen(str1) + 1;
    int str2_len = my_strlen(str2) + 1;

    for (int i = 0; i < str1_len && i < str2_len; ++i)
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
    }

    return 0;
}

int main(char args, char *argv[])
{
    if (args != 3)
    {
        puts("Usage: mystrcmp str1 str2");
        return 1;
    }

    // Compare two strings
    char *str1 = argv[1];
    char *str2 = argv[2];
    printf("%d\n", my_strcmp(str1, str2));

    return 0;
}
