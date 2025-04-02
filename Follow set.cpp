
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0, p, i = 0, j = 0;
char a[10][10], followResult[10];

void follow(char c);
void first(char c);
void addToResult(char);

int main() {
    int i;
    int choice;
    char c, ch;

    printf("Enter the number of productions: ");
    scanf("%d", &n);
    printf("Enter %d productions\nProduction with multiple terms should be given as separate productions\n", n);

    for (i = 0; i < n; i++) {
        scanf("%s%c", a[i], &ch);
    }

    // Repeat the process of finding FOLLOW for different non-terminals
    do {
        m = 0;
        printf("Find FOLLOW of --> ");
        scanf(" %c", &c);
        follow(c);

        // Output the FOLLOW set for the given non-terminal
        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++)
            printf("%c ", followResult[i]);
        printf("}\n");

        printf("Do you want to continue (Press 1 to continue)? ");
        scanf("%d%c", &choice, &ch);

    } while (choice == 1);

    return 0;
}

// Function to compute FOLLOW set
void follow(char c) {
    // If the first non-terminal is the current non-terminal, add $ to FOLLOW(c)
    if (a[0][0] == c)
        addToResult('$');

    // Traverse through all productions
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(a[i]); j++) {
            // If current non-terminal appears in the right-hand side of a production
            if (a[i][j] == c) {
                // If the next symbol exists, add the FIRST set of the next symbol to FOLLOW(c)
                if (a[i][j + 1] != '\0') {
                    first(a[i][j + 1]);
                }
                // If next symbol is the end of the production, follow the first symbol of the production
                if (a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]);
                }
            }
        }
    }
}

// Function to compute FIRST set of a non-terminal
void first(char c) {
    int k;
    // If c is a terminal, add it directly to the FOLLOW set
    if (!isupper(c)) {
        addToResult(c);
    }
    // If c is a non-terminal, process its production rules
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            // If the production starts with an epsilon (empty string), follow the first symbol of the production
            if (a[k][2] == '#') {
                follow(a[k][0]);
            }
            // If the production starts with a terminal, add it to the FOLLOW set
            else if (islower(a[k][2])) {
                addToResult(a[k][2]);
            }
            // If the production starts with a non-terminal, recursively call first()
            else {
                first(a[k][2]);
            }
        }
    }
}

// Function to add a symbol to the FOLLOW result set
void addToResult(char c) {
    int i;
    // Check if the symbol is already in the FOLLOW result set
    for (i = 0; i < m; i++) {
        if (followResult[i] == c) {
            return;
        }
    }
    // If not present, add it to the FOLLOW result set
    followResult[m++] = c;
}




