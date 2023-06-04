#include <stdio.h>
#include <string.h>
#include "../classroom.h"

#define MAX_ROWS 20
#define MAX_COLS 20

#define CASE_GENERATE 1
#define CASE_ASSIGN 2
#define CASE_SAVE 3
#define CASE_DIRECT_NEIGHBORS 4
#define CASE_INDIRECT_NEIGHBORS 5
#define CASE_EXIT 6

unsigned int rows = 0;
unsigned int cols = 0;
char seatingArrangement;

char opt1[50] = "Generate seating arrangement";

int clearStdinBuffer() {
    int bufferedCharacters = -1;
    int c;
    do {
        scanf("%c", &c);
        if (++bufferedCharacters == -1) bufferedCharacters++;
    } while (c != '\n' && c != EOF);

    return bufferedCharacters;
}

unsigned int inputNumbers(char *request, unsigned int upperLimit, unsigned int lowerLimit) {
    unsigned int result;
    do {
        printf("%s", request);
        scanf("%d", &result);
        clearStdinBuffer();
    } while (result > upperLimit || result < lowerLimit);

    return result;
}

void inputSeatingArrangement(void) {
    do {
        printf("Please enter the arrangement pattern (c - chessboard; f - far spaced): ");
        scanf("%c", &seatingArrangement);
        clearStdinBuffer();
    } while (seatingArrangement != 'f' && seatingArrangement != 'c');
}

void inputStudentID(char *newStudent) {
    char isValid;
    do {
        printf("Please enter the student ID you would like to assign: ");
        scanf("%8s", newStudent);
        int buffered = clearStdinBuffer();
        for (int i = 0; i < 8; ++i) {
            isValid = newStudent[i] != 0 && !buffered;
            if (!isValid) break;
        }
    } while (!isValid);
}

int isSeatPlanGenerated() {
    return (rows != 0 && cols != 0);
}

unsigned int calcSeat(unsigned int row, unsigned int col) {
    unsigned int seatIndex = (row - 1) * cols + col - 1;
    if ((seatingArrangement == 'f' && row & 1 && col & 1)
        || (seatingArrangement == 'c' && !((row + col) & 1)))
        return seatIndex;
    return -1;
}

void displayMenu() {
    printf("Menu:\n");
    printf("1. %s\n", opt1);
    printf("2. Assign seat to a student\n");
    printf("3. Save student seat information\n");
    printf("4. Find direct neighbors of a student\n");
    printf("5. Find indirect neighbors of a student\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

unsigned short generateSeatingArrangement(classroom *Classroom) {
    unsigned short result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((seatingArrangement == 'c' && !((i + j) & 1)) || (seatingArrangement == 'f' && !(i & 1) && !(j & 1))) {
                classroomAppendLastSeat(Classroom, "########");
                result++;
            } else { classroomAppendLastSeat(Classroom, "--------"); }
        }
    }

    return result;
}

/*
void assignSeat(Student* student, int seatingArrangement[][MAX_COLS]) {
    // Implementation for assigning a seat to a student
    // ...
}

void saveStudentInfo(Student* student, FILE* file) {
    // Implementation for saving student information to a file
    // ...
}

void getDirectNeighbors(Student* student, int rows, int cols) {
    // Implementation for finding direct neighbors of a student
    // ...
}

void getIndirectNeighbors(Student* student, int rows, int cols) {
    // Implementation for finding indirect neighbors of a student
    // ...
}
*/
int main() {
    classroom *Classroom = classroomCreate();
    int option = -1;
    unsigned short currentStudents = 0, maxStudents;

    do {
        displayMenu();
        scanf("%d", &option);
        clearStdinBuffer();

        switch (option) {
            case CASE_GENERATE:
                if (!isSeatPlanGenerated()) {
                    rows = inputNumbers("Please enter the number of rows: ",
                                        MAX_ROWS, 1);
                    cols = inputNumbers("Please enter the number of columns: ",
                                        MAX_COLS, 1);
                    inputSeatingArrangement();

                    maxStudents = generateSeatingArrangement(Classroom);
                    printf("Seats arranged.\n");
                    strcpy(opt1, "Print seating chart");
                }
                classroomPrint(Classroom, rows, cols);
                printf("Chart printed.\n");
                break;

            case CASE_ASSIGN: {
                if (!isSeatPlanGenerated()) {
                    printf("Seats have to be arranged first.\n");
                } else if (currentStudents == maxStudents) {
                    printf("Maximal assignable student count is reached.\n");
                } else {
                    char newStudent[9];
                    inputStudentID(newStudent);

                    unsigned int rowToAssign = 0;
                    unsigned int colToAssign = 0;
                    unsigned int seatNumber;

                    do {
                        rowToAssign = inputNumbers("Enter the seat's row: ",
                                                   rows, 1);
                        colToAssign = inputNumbers("Enter the seat's column: ",
                                                   cols, 1);
                        seatNumber = calcSeat(rowToAssign, colToAssign);
                    } while (seatNumber == -1);

                    char wasItSuccessful = classroomAssignStudent(Classroom,
                                                                 newStudent, seatNumber);
                    if (wasItSuccessful == 1) {

                        currentStudents++;
                        printf("Student %s assigned to seat %d (%d. row, %d. column).\n",
                               newStudent, seatNumber,
                               rowToAssign, colToAssign);
                    } else if (wasItSuccessful == 0) { printf("The student couldn't be assigned.\n"); }
                    else if(wasItSuccessful == -1) { printf("The seat is already occupied.\n"); }
                    else { printf("The student is already assigned.\n"); }
                }
                break;
            }
            case CASE_SAVE: {
                if (!isSeatPlanGenerated()) {
                    printf("Seat arrangement has to be generated first.\n");
                    break;
                }
                // Rest of the code for case 3
                break;
            }
            case CASE_DIRECT_NEIGHBORS: {
                if (!isSeatPlanGenerated()) {
                    printf("Seat arrangement has to be generated first.\n");
                    break;
                }
                // Rest of the code for case 4
                break;
            }
            case CASE_INDIRECT_NEIGHBORS: {
                if (!isSeatPlanGenerated()) {
                    printf("Seat arrangement has to be generated first.\n");
                    break;
                }
                // Rest of the code for case 5
                break;
            }
            case CASE_EXIT:
                printf("Program is exiting.\n");
                break;
            default:
                printf("Invalid option. Choose again.\n");
        }
    } while (option != CASE_EXIT);

    return 0;
}
