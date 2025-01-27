#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIECES 100

typedef struct {
    int length;
    int price;
} Piece;

// Function Prototypes: Helps with accidental function missuse
void read_input(Piece pieces[], int *count);
void solve_rod_cutting(Piece pieces[], int count, int rod_length);
void print_solution(int rod_length, Piece pieces[], int *cuts, int total_value);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rod_length>\n", argv[0]);
        return 1;
    }

    int rod_length = atoi(argv[1]);

    if (rod_length <= 0 || rod_length > MAX_PIECES) {
        fprintf(stderr, "Rod length must be between 1 and %d.\n", MAX_PIECES);
        return 1;
    }
    
    Piece pieces[MAX_PIECES];
    int count = 0;

    read_input(pieces, &count);
    solve_rod_cutting(pieces, count, rod_length);

    return 0;
}

/**
 * Reads piece data from standard input in the format "<length>, <value>"
 * Input:
 *   - pieces[]: Array to store piece length and value pairs.
 *   - count: Pointer to an integer tracking the number of pieces read.
 * Processing:
 *   - Reads lines from standard input until EOF.
 *   - Each line contains a length and value pair separated by a comma.
 * Output:
 *   - Updates the pieces array and the count of pieces.
 */
void read_input(Piece pieces[], int *count) {
    while (scanf("%d, %d", &pieces[*count].length, &pieces[*count].price) == 2) {
        (*count)++;
        if (*count >= MAX_PIECES) {
            fprintf(stderr, "Warning: Max piece count reached\n");
            break;
        }
    }
}

/**
 * Solves the rod cutting problem using dynamic programming.
 * Input:
 *   - rod_length: The total length of the rod to be cut.
 *   - pieces[]: Array of available pieces with their lengths and values.
 *   - count: Number of available pieces.
 * Processing:
 *   - Determines the maximum value obtainable by cutting the rod optimally.
 *   - Uses a dynamic programming approach to find the best cuts.
 * Output:
 *   - Calls print_solution to display the result.
 */
void solve_rod_cutting(Piece pieces[], int count, int rod_length) {
    int *values = (int *)malloc((rod_length + 1) * sizeof(int));
    int *cuts = (int *)malloc((rod_length + 1) * sizeof(int));

    if (values == NULL || cuts == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= rod_length; i++) {
        values[i] = 0;
        cuts[i] = -1;
    }

    for (int i = 1; i <= rod_length; i++) {
        for (int j = 0; j < count; j++) {
            if (pieces[j].length <= i) {
                int new_value = pieces[j].price + values[i - pieces[j].length];
                if (new_value > values[i]) {
                    values[i] = new_value;
                    cuts[i] = j;
                }
            }
        }
    }

    print_solution(rod_length, pieces, cuts, values[rod_length]);

    free(values);
    free(cuts);
}

/**
 * Prints the final cutting solution.
 * Input:
 *   - cuts[]: Array storing the count of each piece used.
 *   - pieces[]: Array containing the piece information.
 *   - count: Number of available pieces.
 *   - remainder: The leftover rod length that couldn't be cut optimally.
 *   - total_value: The maximum total value obtained from cuts.
 * Output:
 *   - Prints the cutting plan and total value in the required format.
 */

void print_solution(int rod_length, Piece pieces[], int cuts[], int total_value) {
    if (total_value == 0) {
        printf("Remainder: %d\n", rod_length);
        printf("Value: 0\n");
        return;
    }

    int remainder = rod_length;
    int count[MAX_PIECES] = {0};

    while (remainder > 0 && cuts[remainder] != -1) {
        count[cuts[remainder]]++;
        remainder -= pieces[cuts[remainder]].length;
    }

    for (int i = 0; i < MAX_PIECES && pieces[i].length > 0; i++) {
        if (count[i] > 0) {
            printf("%d @ %d = %d\n", count[i], pieces[i].length, count[i] * pieces[i].price);
        }
    }

    printf("Remainder: %d\n", remainder);
    printf("Value: %d\n", total_value);
}
