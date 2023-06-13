/*
*       __
*     <(o )___
* 	   ( ._> /
*       `---'
*/
//-----HEADER FILES-----//
#include <stdio.h>
#include <string.h>
#include "classroom.h"
#include <time.h>

//-----MACROS-----//
#define MAX_ROWS 20
#define MAX_COLS 20
#define CHESSBOARD 'c'
#define FAR_SPACED 'f'
#define SAFE 's'

#define ERROR "An error occurred.\n"
#define CURRENT_TIME "Current local time and date: %s"
#define INVALID "Invalid option. Choose again.\n"

#define CASE_GENERATE 1
#define CASE_ASSIGN 2
#define CASE_SAVE 3
#define CASE_DIRECT_NEIGHBORS 4
#define CASE_INDIRECT_NEIGHBORS 5
#define CASE_REMOVE 6
#define CASE_LOG_PATH 7
#define CASE_EXIT 0

//-----GLOBAL VARIABLES-----//
unsigned int rows = 0;
unsigned int cols = 0;
char seatingArrangement;
char log_path[201];
char *ptr_path[201];
char opt1[] = "Generate seating arrangement";

//-----FUNCTIONS-----//
/// Clears input buffer. Must used to avoid input type mismatches of scanf function.
/// \return the amount of buffered characters
int clearStdinBuffer() {
    int bufferedCharacters = -1;
    char c;
    do {
        scanf("%c", &c);
        if (++bufferedCharacters == -1) bufferedCharacters++;
    } while (c != '\n' && c != EOF);

    return bufferedCharacters;
}

/// Reads numbers from Stdin.
/// \param request the string to ask for the input with
/// \param upperLimit the possibly highest number to enter
/// \param lowerLimit the possibly lowest number to enter
/// \return the entered number
int inputNumbers(char *request, unsigned int upperLimit, unsigned int lowerLimit) {
    int result;
    do {
        printf("%s The minimum number to enter is %d, the maximum is %d.\n",
               request, lowerLimit, upperLimit);
        scanf("%d", &result);
        clearStdinBuffer();
    } while (result > upperLimit || result < lowerLimit);

    return result;
}

/// Asks for student ID and checks whether it already exists in the classroom.
/// \param Classroom the classroom's memory address
/// \param newStudent the student's 8-digit ID
/// \param request the string to ask for the input with
/// \param found the string to print to Stdout if the student was found
/// \param notFound the string to print to Stdout if the student was not found
/// \return 1 when the student was found, -1  when the student was not found, 0 when failed
char inputStudentID(classroom *Classroom, char *newStudent, char *request,
                    char *found, char *notFound) {
    char isValid;
    do {
        printf("%s The student ID must be eight characters long"
               " and can only contain lowercase characters and numbers.\n", request);
        scanf("%8s", newStudent);
        int buffered = clearStdinBuffer();
        for (int i = 0; i < 8; ++i) {
            char c = newStudent[i];
            isValid = (c >= '0' && c <= '9' || c >= 'a' && c <= 'z') && !buffered;
            if (!isValid) break;
        }
    } while (!isValid);

    char result = classroomCheckStudent(Classroom, newStudent);
    if (result == -1) printf("%s", found);
    else if (result == 0) printf(ERROR);
    else printf("%s", notFound);
    return result;
}

/// Asks for file path.
/// \param path the memory address to store the path at
void inputFilePath(char *path) {
    FILE *file;
    int buffered;
    do {
        printf("Please enter a valid file path. "
               "If it doesn't exist yet, it will be created.\n");
        scanf("%200s", path);
        buffered = clearStdinBuffer();
        if (buffered) continue;
        file = fopen(path, "a");
    } while (!file || buffered);

    if (!strcmp(log_path, path)) {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        fprintf(file, "----------------------------\n"
                      "\nTime: %sNew logging session has been started!\n", asctime(timeinfo));

        printf("The path is now: %s\n", log_path);
        printf(CURRENT_TIME, asctime(timeinfo));
    }

    fclose(file);
}

/// Calculates seat index from row and column numbers.
/// \param row the row of the seat (1 is the first row)
/// \param col the column of the seat (1 is the first column)
/// \return the index of the seat (0 is the first seat)
unsigned int calcSeat(unsigned int row, unsigned int col) {
    unsigned int seatIndex = (row - 1) * cols + col - 1;
    if ((seatingArrangement == FAR_SPACED && row & 1 && col & 1)
        || (seatingArrangement == CHESSBOARD && !((row + col) & 1)) || seatingArrangement == SAFE)
        return seatIndex;
    return -1;
}

/// Reads a character from stdin and saves it as the seating arrangement (global variable),
/// which can be SAFE, FAR_SPACED or CHESSBOARD.
void inputSeatingArrangement(void) {
    char isValid;
    do {
        printf("Please enter the arrangement pattern (c - chessboard; f - far spaced; s - safe): ");
        scanf("%c", &seatingArrangement);
        int buffered = clearStdinBuffer();
        isValid = (seatingArrangement == FAR_SPACED || seatingArrangement == CHESSBOARD
                  || seatingArrangement == SAFE) && !buffered;
        if (!isValid) printf("You can't enter anything but s, c or f!\n");
    } while (!isValid);
}

/// Calculates rows and columns from the received seat index. It writes the value into the original
/// variables through pointers.
/// \param seatIndex the seat's index (0 is the first seat)
/// \param row the seat's row's memory address (1 is the first row)
/// \param col the seat's column's memory address (1 is the first column)
void calcRowsCols(unsigned int seatIndex, unsigned int *row, unsigned int *col) {
    *col = seatIndex % cols + 1;
    if (!*col) *col += cols - 1;
    *row = seatIndex / cols + 1;
    if (!seatIndex % cols) (*row)--;
}

/// Displays the main menu.
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. %s\n", opt1);
    printf("2. Assign seat to a student\n");
    printf("3. Save student seat information\n");
    printf("4. Find direct neighbors of a student\n");
    printf("5. Find indirect neighbors of a student\n");
    printf("6. Remove student from a seat\n");
    printf("7. Enter a logfile path\n");
    printf("0. Exit the program\n");
    printf("Enter your choice: ");
}

/// Generates the seating arrangement of a classroom, using the rows' and columns' global variables.
/// \param Classroom the classroom's memory address
/// \return the amount of safe seats
unsigned short generateSeatingArrangement(classroom *Classroom) {
    unsigned short result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (seatingArrangement == SAFE || (seatingArrangement == CHESSBOARD && !((i + j) & 1))
                || (seatingArrangement == FAR_SPACED && !(i & 1) && !(j & 1))) {
                classroomAppendLastSeat(Classroom, "########");
                result++;
            } else { classroomAppendLastSeat(Classroom, "--------"); }
        }
    }

    return result;
}

/// Logs the events of options 2, 3, 6.
/// \param place_ID index of the student's seat (0 is the first seat)
/// \param student_ID the student ID
/// \param assignment_status e for assigned student, r for removed student, s for saved student
/// \param row the row of the student's seat (1 is the first row)
/// \param col the column of the student's seat (1 is the first column)
void logFileSeatAssignment(unsigned int place_ID, char *student_ID, char assignment_status,
                           unsigned int row, unsigned int col) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    FILE *file = fopen(log_path, "r+");
    if (file == NULL) {
        fprintf(stderr, "Error, the logfile %s can't be opened!\n", log_path);
        return;
    }

    fseek(file, 0, SEEK_END);

    fprintf(file, "\nTime: %s", asctime(timeinfo));
    if (assignment_status == '\0') {
        printf(CURRENT_TIME, asctime(timeinfo));
        fprintf(file, "%s %d\n", student_ID, place_ID);
    } else if (assignment_status == 'e') {
        printf(CURRENT_TIME, asctime(timeinfo));
        fprintf(file,
                "Assigned student:\nThe student with the ID %s has been assigned "
                "to the seat %d (row %d col %d).\n", student_ID, place_ID, row, col);
    } else if (assignment_status == 'r') {
        printf(CURRENT_TIME, asctime(timeinfo));
        fprintf(file,
                "Removed student:\nThe student with the ID %s has been removed "
                "from the seat %d (row %d col %d).\n", student_ID, place_ID, row, col);
    } else if (assignment_status == 's') {
        fprintf(file,
                "Queried student:\nA student's surroundings have been saved "
                "to the following file: %s\n", student_ID);
    }

    fclose(file);
}

/// Assigns a student to a seat in the classroom.
/// \param Classroom the classroom's memory address
/// \param newStudent the student's 8-digit ID
/// \param seatNumber the seat's index (0 is the first seat)
/// \param row the seat's row (1 is the first row)
/// \param col the seat's column (1 is the first column)
/// \param currentStudents the amount of the currently already assigned students
void assignSeat(classroom *Classroom, char *newStudent, unsigned int seatNumber,
                unsigned int row, unsigned int col, unsigned short *currentStudents) {
    char wasItSuccessful = classroomAssignStudent(Classroom,
                                                  newStudent, seatNumber);
    if (wasItSuccessful == 1) {

        (*currentStudents)++;
        printf("Student %s has been assigned to seat %d (%d. row, %d. column).\n",
               newStudent, seatNumber,
               row, col);
        logFileSeatAssignment(seatNumber, newStudent, 'e', row, col);
    } else if (wasItSuccessful == 0) { printf(ERROR); }
    else { printf("The seat is already occupied.\n"); }
}

/// Gets the row, column and index of a specific student's seat in the classroom.
/// To store the row and column, pointers are used.
/// \param Classroom the classroom's memory address
/// \param searchedStudent the student's 8-digit ID
/// \param row the seat's row (1 is the first row)
/// \param col the seat's column (1 is the first column)
/// \return the seat's index (0 is the first seat)
unsigned int getSeatDetails(classroom *Classroom, char *searchedStudent,
                            unsigned int *row, unsigned int *col) {
    unsigned int foundSeatIndex = classroomSearchStudOrd(Classroom, searchedStudent);
    calcRowsCols(foundSeatIndex, row, col);
    return foundSeatIndex;
}

/// Prints the surroundings of a specific student in the classroom.
/// \param Classroom the classroom's memory address
/// \param searchedStudent the student's 8-digit ID
/// \param neighborhoodType 1: only the student and their direct neighbors; 2: the indirect neighbors too
/// \param file_path the file's path where it will be stored
void findNeighbors(classroom *Classroom, char *searchedStudent, char neighborhoodType, char *file_path) {
    unsigned int row, col;
    unsigned int seatIndex = getSeatDetails(Classroom, searchedStudent, &row, &col);
    if (seatIndex == -1) {
        printf(ERROR);
        return;
    }
    classroomPrintPartial(Classroom, rows, cols, row, col, neighborhoodType, file_path);
}

/// Removes student from the classroom.
/// \param Classroom the classroom's memory address
/// \param studentToRemove the student's 8-digit ID
/// \param currentStudents the amount of the currently already assigned students
void removeStudent(classroom *Classroom, char *studentToRemove, unsigned short *currentStudents) {
    unsigned int row, col;
    unsigned int seatIndex = getSeatDetails(Classroom, studentToRemove, &row, &col);
    if (seatIndex == -1) {
        printf(ERROR);
        return;
    }
    char wasItSuccessful = classroomRemoveStudent(Classroom, seatIndex);

    if (wasItSuccessful == 1) {

        (*currentStudents)--;
        printf("Student %s has been removed from seat %d (%d. row, %d. column).\n",
               studentToRemove, seatIndex,
               row, col);
        logFileSeatAssignment(seatIndex, studentToRemove, 'r', row, col);
    } else { printf(ERROR); }
}

/// Here starts the program.
int main() {
    classroom *Classroom = classroomCreate();
    int option = -1;
    unsigned short currentStudents = 0, maxStudents;

    do {
        displayMenu();
        scanf("%d", &option);
        int buffered = clearStdinBuffer();

        if (!strcmp(log_path, "") && option != 7) {
            printf("Please enter a logfile path first at option 7.\n");
            continue;
        }
        if (!rows && option != 1 && option != 7 && strcmp(log_path, "")) {
            printf("Please generate a classroom first at option 1.\n");
            continue;
        }
        if (!currentStudents && option != 1 && option != 2 && option != 7) {
            printf("Please add a student first at option 2.\n");
            continue;
        }
        if (buffered) {
            printf(INVALID);
            continue;
        }

        switch (option) {
            case CASE_GENERATE:
                if (!rows) {
                    rows = inputNumbers("Please enter the number of rows.",
                                        MAX_ROWS, 1);
                    cols = inputNumbers("Please enter the number of columns.",
                                        MAX_COLS, 1);
                    inputSeatingArrangement();

                    maxStudents = generateSeatingArrangement(Classroom);
                    printf("Seats arranged.\n");
                    strcpy(opt1, "Print seating chart");
                }
                *ptr_path = log_path;
                classroomPrintWhole(Classroom, rows, cols, *ptr_path);
                printf("Chart printed.\n");
                break;

            case CASE_ASSIGN: {
                if (currentStudents == maxStudents) {
                    printf("Maximal assignable student count is reached.\n");
                    break;
                }

                char newStudent[9];
                char inputResult = inputStudentID(Classroom, newStudent,
                                                  "Please enter the student ID you would like to assign.",
                                                  "The student is already assigned.\n", "");
                if (inputResult != 1) break;

                unsigned int row, col, seatNumber;

                do {
                    row = inputNumbers("Please enter the seat's row.",
                                       rows, 1);
                    col = inputNumbers("Please enter the seat's column.",
                                       cols, 1);
                    seatNumber = calcSeat(row, col);
                    if (seatNumber == -1) printf("You can't assign a student here!\n");
                } while (seatNumber == -1);

                assignSeat(Classroom, newStudent, seatNumber, row, col, &currentStudents);

                break;
            }
            case CASE_SAVE: {
                char sStudent[9];
                char inputResult = inputStudentID(
                        Classroom,
                        sStudent,
                        "Please enter the student ID you would like to query.",
                        "", "The student was not found.\n");
                if (inputResult != -1) break;

                char file_path[201];

                inputFilePath(file_path);

                findNeighbors(Classroom, sStudent, 2, file_path);
                logFileSeatAssignment(0, file_path, 's', 0, 0);
                break;
            }
            case CASE_DIRECT_NEIGHBORS: {
                char searchedStudent[9];
                char inputResult = inputStudentID(Classroom, searchedStudent,
                                                  "Please enter the student's ID to be searched for.",
                                                  "", "The student was not found.\n");
                if (inputResult != -1) break;

                findNeighbors(Classroom, searchedStudent, 1, log_path);

                break;
            }
            case CASE_INDIRECT_NEIGHBORS: {
                char searchedStudent[9];
                char inputResult = inputStudentID(Classroom, searchedStudent,
                                                  "Please enter the student's ID to be searched for.",
                                                  "", "The student was not found.\n");
                if (inputResult != -1) break;

                findNeighbors(Classroom, searchedStudent, 2, log_path);

                break;
            }

            case CASE_REMOVE: {
                char rmStudent[9];
                char inputResult = inputStudentID(
                        Classroom,
                        rmStudent,
                        "Please enter the student ID you would like to remove.",
                        "", "The student was not found.\n");
                if (inputResult != -1) break;

                removeStudent(Classroom, rmStudent, &currentStudents);

                break;
            }

            case CASE_LOG_PATH: {
                if (strcmp(log_path, "")) {
                    printf("Current path: %s\nDo you want to change the path?"
                           " (y - yes; n - no): ", log_path);

                    char wantNewPath;
                    do {
                        scanf("%c", &wantNewPath);
                        clearStdinBuffer();
                    } while (wantNewPath != 'y' && wantNewPath != 'n');

                    if (wantNewPath == 'n') {
                        printf("The path remains: %s\n", log_path);
                        break;
                    }

                    inputFilePath(log_path);
                    break;
                }

                inputFilePath(log_path);
                break;
            }

            case CASE_EXIT:
                printf("Program is exiting.\n");
                break;
            default:
                printf(INVALID);
        }
    } while (option != CASE_EXIT);

    return 0;
}
