#include <stdio.h>
#include <ctype.h>

int isStringEmpty(const char *str) {
    while (*str) {
        if (!isspace(*str))
            return 0; // String is not empty
        str++;
    }
    return 1; // String is empty
}


int main() {
    const char *str1 = "   \t\n";
    const char *str2 = "Hello, World!";
    const char *str3 = "";

    if (isStringEmpty(str1))
        printf("String 1 is empty.\n");
    else
        printf("String 1 is not empty.\n");

    if (isStringEmpty(str2))
        printf("String 2 is empty.\n");
    else
        printf("String 2 is not empty.\n");

    if (isStringEmpty(str3))
        printf("String 3 is empty.\n");
    else
        printf("String 3 is not empty.\n");

    return 0;
}
