#include <stdio.h>
#include <stdlib.h>

// Seat Structure
typedef struct Seat {
    int row;
    int column;
    struct Seat* next;
} Seat;

Seat* createSeat(int row, int column);
Seat* generateSeatingChart(int rows, int columns);
void printSeatingChart(Seat* head, int rows, int columns, char choice);
void freeSeatingChart(Seat* head);
int inputRowsAndCols(void);


int main() {
    int rows = 21, columns = 21;
    char choice = 'a';
    while (rows > 20 || columns > 20) { // stops the function if the number of rows and columns are too high

        printf("Enter the number of rows (maximum 20): ");
        rows = inputRowsAndCols();

        printf("Enter the number of columns (maximum 20): ");
        columns = inputRowsAndCols();
        if (rows > 20 || columns > 20) printf("Maximum number of rows or columns exceeded. Please try again\n");
    }
    printf("Choose what type of layout you want for the seating chart: 's' for a chessboard-Layout, 'p' for a far spaced Layout (only lowercase): ");
    while (choice != 's' && choice != 'p') {
        choice = getchar();
        if (choice != 's' && choice != 'p') {
            printf("Invalid Input. Please try again. The only valid inputs are 's' for a Chessboard Layout or 'p' for a far spaced Layout (only lowercase): ");
            while (getchar() != '\n');  // Clear input buffer
        }
    }

    Seat* head = generateSeatingChart(rows, columns);
    if (head != NULL) {
        printSeatingChart(head, rows, columns, choice);
        freeSeatingChart(head);
    }

    return 0;
}

Seat* createSeat(int row, int column) {
    Seat* newSeat = (Seat*)malloc(sizeof(Seat));
    newSeat->row = row;
    newSeat->column = column;
    newSeat->next = NULL;
    return newSeat;
}

Seat* generateSeatingChart(int rows, int columns) {
    if (rows > 20 || columns > 20) { // stops the function if the number of rows and columns are too high
        printf("Maximum number of rows and columns exceeded.\n");
        return NULL;
    }

    Seat* head = NULL;
    Seat* currentSeat = NULL;

    // Create the linked list of seats
    int count = 0;
    for (int row = 1; row <= rows; row++) {
        for (int col = 1; col <= columns; col++) {
            // Skip one seat after each student in the same row
            if ((row % 2 == 1 && col % 2 == 0) || (row % 2 == 0 && col % 2 == 1))
                continue;

            Seat* newSeat = createSeat(row, col);

            if (head == NULL) {
                head = newSeat;
                currentSeat = newSeat;
            } else {
                currentSeat->next = newSeat;
                currentSeat = newSeat;
            }
            count++;

            // Check if the maximum number of seats is reached
            if (count >= rows * columns)
                return head;
        }
    }

    return head;
}

// Function to print the seating chart
void printSeatingChart(Seat* head, int rows, int columns, char choice) {
    // Create a 2D array to represent the seating layout
    char seatingChart[20][20];

    // Initialize the seating layout with empty indicators
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            seatingChart[i][j] = '-';
        }
    }
    if (choice == 's') {
        // Traverse the linked list and mark the seats as occupied
        Seat *currentSeat = head;
        while (currentSeat != NULL) {
            seatingChart[currentSeat->row - 1][currentSeat->column - 1] = 'X';
            currentSeat = currentSeat->next;
        }
    } else {
        Seat *currentSeat = head;
        while (currentSeat != NULL) {
            seatingChart[currentSeat->row - 1][currentSeat->column - 1] = 'X';
            if(currentSeat->column % 2 == 0) seatingChart[currentSeat->row - 1][currentSeat->column - 1] = '-';
            currentSeat = currentSeat->next;
        }
    }

    // Print the seating chart with seat indicators
    printf("Seating Chart:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", seatingChart[i][j]);
        }
        printf("\n");
    }
}

// Function to free the memory allocated for the seating chart
void freeSeatingChart(Seat* head) {
    Seat* currentSeat = head;

    while (currentSeat != NULL) {
        Seat* temp = currentSeat;
        currentSeat = currentSeat->next;
        free(temp);
    }
}

int inputRowsAndCols(void)
{
    int inputDigit = 0;
    char inputCharacter;
    char inputString[3] = {};

    while (1)
    {
        inputCharacter = getchar();
        if ((inputCharacter >= '0' && inputCharacter <= '9'))
        {
            inputString[inputDigit++] = inputCharacter;
            putchar(inputCharacter);
        }
        else if (inputCharacter == 127 && inputDigit)
        {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            inputString[--inputDigit] = 0;
        }
        else if (inputCharacter == '\n' && inputDigit)
        {
            printf("\nThe selected number of rows or columns: %s\n", inputString);
            return atoi(inputString);
        }
        else
        {
            printf("Invalid input. Please try again.\nEnter a valid number (maximum 20): ");
            while (getchar() != '\n'); // Clear input buffer
            inputDigit = 0; // Reset inputDigit
            inputString[0] = '\0'; // Reset inputString
        }
    }
}
