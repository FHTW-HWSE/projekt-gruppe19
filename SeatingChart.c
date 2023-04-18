#include <stdio.h>
int seatingchart(int rows, int cols, int numStudents);

int seatingchart (int rows, int cols, int numStudents) {
    char seatingChart[20][20];
    int maxSeats = rows * cols;

    if (numStudents > (maxSeats / 2)) { //divide by 2 to guarantee the minimal distance
        printf("Error: Nicht genug Sitzplätze.\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            seatingChart[i][j] = '-';
        }
    }
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (count == numStudents) {
                break;
            }

            if ((i + j) % 2 == 0 && seatingChart[i][j] == '-') {
                seatingChart[i][j] = 'S';
                count++;
            }
        }
    }
    return 0;
}