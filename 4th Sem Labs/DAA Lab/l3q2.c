#include <stdio.h>

int opcount = 0;

void smatch(char s[], char sub[]) {
    int f = -1, i = 0, j = 0;

    while (s[i] != '\0') {
        opcount++;
        if (s[i] == sub[j]) {
            j++;
            while (sub[j] != '\0' && s[i + j] == sub[j]) {
                opcount++;
                j++;
            }
            if (sub[j] == '\0') {
                f = i;
                break; // Substring found, exit the loop
            }
            j = 0; // Reset j for the next comparison
        }
        i++; // Move to the next character in the main string
    }

    if (f == -1)
        printf("No match");
    else
        printf("Substring found at index %d", f);
}

int main() {
    char s[100], sub[100];
    printf("Enter the main string: ");
    scanf("%s", s);
    printf("Enter the substring: ");
    scanf("%s", sub);
    smatch(s, sub);
    printf("\nOpcount= %d\n", opcount);
    return 0;
}
