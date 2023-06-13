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
char logPath[201];
char opt1[] = "Generate seating arrangement";

//-----FUNCTIONS-----//
/**
 * @brief Clears the input buffer to avoid input type mismatches.
 * @return The number of buffered characters.
 */
int clearStdinBuffer() {
    int countOfBufferedCharacters = -1;
    char bufferedCharacter;
    do {
        scanf("%c", &bufferedCharacter);
        if (++countOfBufferedCharacters == -1) {
            countOfBufferedCharacters++;
        }
    } while (bufferedCharacter != '\n' && bufferedCharacter != EOF);

    return countOfBufferedCharacters;
}

/**
 * @brief Asks the user to input a number within the specified range.
 * @param msgOnRequest The message displayed when requesting the input.
 * @param upperLimit The maximum allowed number.
 * @param lowerLimit The minimum allowed number.
 * @return The entered number.
 */
int inputNumbers(char *msgOnRequest, unsigned int upperLimit, unsigned int lowerLimit) {
    int enteredNumber;
    do {
        printf("%s The minimum number to enter is %d, the maximum is %d.\n",
               msgOnRequest, lowerLimit, upperLimit);
        scanf("%d", &enteredNumber);
        clearStdinBuffer();
    } while (enteredNumber > upperLimit || enteredNumber < lowerLimit);

    return enteredNumber;
}

/**
 * @brief Asks the user to input a student ID and checks if it already exists in the classroom.
 * @param Classroom Pointer to the `classroom` data structure.
 * @param newStudent Buffer to store the entered student ID.
 * @param msgOnRequest The message displayed when requesting the input.
 * @param msgOnFound The message displayed if the student is found in the classroom.
 * @param msgOnNotFound The message displayed if the student is not found in the classroom.
 * @return 1 if the student is found, -1 if the student is not found, and 0 if an error occurs.
 */
char inputStudentID(classroom *Classroom, char *newStudent, char *msgOnRequest,
                    char *msgOnFound, char *msgOnNotFound) {
    char isValid;
    do {
        printf("%s The student ID must be eight characters long"
               " and can only contain lowercase characters and numbers.\n", msgOnRequest);
        scanf("%8s", newStudent);
        int countOfBufferedCharacters = clearStdinBuffer();
        for (int i = 0; i < 8; ++i) {
            char currentChar = newStudent[i];
            isValid = ((currentChar >= '0' && currentChar <= '9')
                       || (currentChar >= 'a' && currentChar <= 'z')) && !countOfBufferedCharacters;
            if (!isValid) {
                break;
            }
        }
    } while (!isValid);

    char result = classroomCheckStudent(Classroom, newStudent);
    if (result == -1) {
        printf("%s", msgOnFound);
    } else if (!result) {
        printf(ERROR);
    } else {
        printf("%s", msgOnNotFound);
    }
    return result;
}

/**
 * @brief Asks the user to input a file path and checks if the file can be opened.
 * @param path Buffer to store the entered file path.
 */
void inputFilePath(char *path) {
    FILE *file = NULL;
    int countOfBufferedCharacters;
    do {
        printf("Please enter a valid file path. "
               "If it doesn't exist yet, it will be created.\n");
        scanf("%200s", path);
        countOfBufferedCharacters = clearStdinBuffer();
        if (!countOfBufferedCharacters) {
            file = fopen(path, "a");
        }
    } while (!file || countOfBufferedCharacters);

    if (!strcmp(logPath, path)) {
        time_t rawTime;
        struct tm *timeInfo;

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        fprintf(file, "----------------------------\n"
                      "\nTime: %sNew logging session has been started!\n", asctime(timeInfo));

        printf("The path is now: %s\n", logPath);
        printf(CURRENT_TIME, asctime(timeInfo));
    }

    fclose(file);
}

/**
 * @brief Calculates the seat index from the row and column numbers based on the seating arrangement.
 * @param row The row of the seat (1 is the first row).
 * @param col The column of the seat (1 is the first column).
 * @return The seat index.
 */
unsigned int calcSeat(unsigned int row, unsigned int col) {
    unsigned int seatIndex = (row - 1) * cols + col - 1;
    if ((seatingArrangement == FAR_SPACED && row & 1 && col & 1)
        || (seatingArrangement == CHESSBOARD && !((row + col) & 1)) || seatingArrangement == SAFE)
        return seatIndex;
    return -1;
}

/**
    @brief Reads a character from stdin and saves it as the seating arrangement.
    This function prompts the user to enter a character representing the seating arrangement pattern
    (SAFE, FAR_SPACED, or CHESSBOARD) and saves it in the global variable 'seatingArrangement'.
    It continues to prompt until a valid input is provided.
    */
void inputSeatingArrangement(void) {
    char isValid;
    do {
        printf("Please enter the arrangement pattern (c - chessboard; f - far spaced; s - safe): ");
        scanf("%c", &seatingArrangement);
        int buffered = clearStdinBuffer();
        isValid = (seatingArrangement == FAR_SPACED || seatingArrangement == CHESSBOARD
                   || seatingArrangement == SAFE) && !buffered;
        if (!isValid) {
            printf("You can't enter anything but s, c or f!\n");
        }
    } while (!isValid);
}
/**
    @brief Calculates the row and column for a given seat index.
    Given a seat index and the number of columns, this function calculates the corresponding row and column values.
    The row and column values are updated through pointer parameters.
    @param seatIndex The seat index for which to calculate the row and column.
    @param row [out] Pointer to the variable that will hold the calculated row value.
    @param col [out] Pointer to the variable that will hold the calculated column value.
    */
void calcRowsCols(unsigned int seatIndex, unsigned int *row, unsigned int *col) {
    *col = seatIndex % cols + 1;
    if (!*col) {
        *col += cols - 1;
    }
    *row = seatIndex / cols + 1;
    if (!seatIndex % cols) {
        (*row)--;
    }
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

/**
    @brief Generates the seating arrangement of a classroom.
    This function generates the seating arrangement for a classroom based on the specified rows and columns.
    The seating arrangement pattern is determined by the global variable 'seatingArrangement', which can be
    SAFE, FAR_SPACED, or CHESSBOARD.
    @param Classroom A pointer to the classroom structure that will hold the seating arrangement.
    @return The number of safe seats in the generated seating arrangement.
    */
unsigned short generateSeatingArrangement(classroom *Classroom) {
    unsigned short maxStudents = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (seatingArrangement == SAFE || (seatingArrangement == CHESSBOARD && !((i + j) & 1))
                || (seatingArrangement == FAR_SPACED && !(i & 1) && !(j & 1))) {
                classroomAppendLastSeat(Classroom, "########");
                maxStudents++;
            } else {
                classroomAppendLastSeat(Classroom, "--------");
            }
        }
    }

    return maxStudents;
}

/// Logs the events of options 2, 3, 6.
/// \param seatIndex index of the student's seat (0 is the first seat)
/// \param enteredString the student ID
/// \param assignmentStatus e for assigned student, r for removed student, s for saved student
/// \param row the row of the student's seat (1 is the first row)
/// \param col the column of the student's seat (1 is the first column)
void logFileSeatAssignment(unsigned int seatIndex, char *enteredString, char assignmentStatus,
                           unsigned int row, unsigned int col) {
    time_t rawTime;
    struct tm *timeInfo;

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    FILE *file = fopen(logPath, "r+");
    if (file == NULL) {
        fprintf(stderr, "Error, the logfile %s can't be opened!\n", logPath);
        return;
    }

    fseek(file, 0, SEEK_END);

    fprintf(file, "\nTime: %s", asctime(timeInfo));
    if (assignmentStatus == '\0') {
        printf(CURRENT_TIME, asctime(timeInfo));
        fprintf(file, "%s %d\n", enteredString, seatIndex);
    } else if (assignmentStatus == 'e') {
        printf(CURRENT_TIME, asctime(timeInfo));
        fprintf(file,
                "Assigned student:\nThe student with the ID %s has been assigned "
                "to the seat %d (row %d col %d).\n", enteredString, seatIndex, row, col);
    } else if (assignmentStatus == 'r') {
        printf(CURRENT_TIME, asctime(timeInfo));
        fprintf(file,
                "Removed student:\nThe student with the ID %s has been removed "
                "from the seat %d (row %d col %d).\n", enteredString, seatIndex, row, col);
    } else if (assignmentStatus == 's') {
        fprintf(file,
                "Queried student:\nA student's surroundings have been saved "
                "to the following file: %s\n", enteredString);
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
    } else if (wasItSuccessful == 0) {
        printf(ERROR);
    } else {
        printf("The seat is already occupied.\n");
    }
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
    unsigned int seatIndex = classroomSearchStudOrd(Classroom, searchedStudent);
    calcRowsCols(seatIndex, row, col);
    return seatIndex;
}

/// Prints the surroundings of a specific student in the classroom.
/// \param Classroom the classroom's memory address
/// \param searchedStudent the student's 8-digit ID
/// \param neighborhoodType 1: only the student and their direct neighbors; 2: the indirect neighbors too
/// \param filePath the file's path where it will be stored
void findNeighbors(classroom *Classroom, char *searchedStudent, char neighborhoodType, char *filePath) {
    unsigned int row, col;
    unsigned int seatIndex = getSeatDetails(Classroom, searchedStudent, &row, &col);
    if (seatIndex == -1) {
        printf(ERROR);
        return;
    }
    classroomPrintPartial(Classroom, rows, cols, row, col, neighborhoodType, filePath);
}

/// Removes student from the classroom.
/// \param Classroom the classroom's memory address
/// \param studentToRemove the student's 8-digit ID
/// \param countOfCurrentStudents the amount of the currently already assigned students
void removeStudent(classroom *Classroom, char *studentToRemove, unsigned short *countOfCurrentStudents) {
    unsigned int row, col;
    unsigned int seatIndex = getSeatDetails(Classroom, studentToRemove, &row, &col);
    if (seatIndex == -1) {
        printf(ERROR);
        return;
    }
    char wasItSuccessful = classroomRemoveStudent(Classroom, seatIndex);

    if (wasItSuccessful == 1) {

        (*countOfCurrentStudents)--;
        printf("Student %s has been removed from seat %d (%d. row, %d. column).\n",
               studentToRemove, seatIndex,
               row, col);
        logFileSeatAssignment(seatIndex, studentToRemove, 'r', row, col);
    } else {
        printf(ERROR);
    }
}

#ifndef TEST
/// Here starts the program.
int main() {
    classroom *Classroom = classroomCreate();
    int option = -1;
    unsigned short countOfCurrentStudents = 0, maxStudents;

    do {
        displayMenu();
        scanf("%d", &option);
        int countOfBufferedCharacters = clearStdinBuffer();

        if (!strcmp(logPath, "") && option != 7 && option != 0) {
            printf("Please enter a logfile path first at option 7.\n");
            continue;
        }
        if (!rows && strcmp(logPath, "") && option != 1 && option != 7 && option != 0) {
            printf("Please generate a classroom first at option 1.\n");
            continue;
        }
        if (!countOfCurrentStudents && option != 1 && option != 2 && option != 7 && option != 0) {
            printf("Please add a student first at option 2.\n");
            continue;
        }
        if (countOfBufferedCharacters) {
            printf(INVALID);
            continue;
        }

        switch (option) {
            case CASE_GENERATE: {
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
                classroomPrintWhole(Classroom, rows, cols, logPath);
                printf("Chart printed.\n");
                break;
            }
            case CASE_ASSIGN: {
                if (countOfCurrentStudents == maxStudents) {
                    printf("Maximal assignable student count is reached.\n");
                    break;
                }

                char newStudent[9];
                char inputResult = inputStudentID(Classroom, newStudent,
                                                  "Please enter the student ID you would like to assign.",
                                                  "The student is already assigned.\n", "");
                if (inputResult != 1) {
                    break;
                }

                unsigned int row, col, seatNumber;

                do {
                    row = inputNumbers("Please enter the seats row.",
                                       rows, 1);
                    col = inputNumbers("Please enter the seats column.",
                                       cols, 1);
                    seatNumber = calcSeat(row, col);
                    if (seatNumber == -1) {
                        printf("You can't assign a student here!\n");
                    }
                } while (seatNumber == -1);

                assignSeat(Classroom, newStudent, seatNumber, row, col, &countOfCurrentStudents);

                break;
            }
            case CASE_SAVE: {
                char studentToSave[9];
                char inputResult = inputStudentID(
                        Classroom,
                        studentToSave,
                        "Please enter the student ID you would like to query.",
                        "", "The student was not found.\n");
                if (inputResult != -1) {
                    break;
                }

                char filePath[201];

                inputFilePath(filePath);

                findNeighbors(Classroom, studentToSave, 2, filePath);
                logFileSeatAssignment(0, filePath, 's', 0, 0);
                break;
            }
            case CASE_DIRECT_NEIGHBORS: {
                char studentToSearch[9];
                char inputResult = inputStudentID(Classroom, studentToSearch,
                                                  "Please enter the students ID to be searched for.",
                                                  "", "The student was not found.\n");
                if (inputResult != -1) {
                    break;
                }

                findNeighbors(Classroom, studentToSearch, 1, logPath);

                break;
            }
            case CASE_INDIRECT_NEIGHBORS: {
                char studentToSearch[9];
                char inputResult = inputStudentID(Classroom, studentToSearch,
                                                  "Please enter the students ID to be searched for.",
                                                  "", "The student was not found.\n");
                if (inputResult != -1) {
                    break;
                }

                findNeighbors(Classroom, studentToSearch, 2, logPath);

                break;
            }

            case CASE_REMOVE: {
                char studentToRemove[9];
                char inputResult = inputStudentID(
                        Classroom,
                        studentToRemove,
                        "Please enter the student ID you would like to remove.",
                        "", "The student was not found.\n");
                if (inputResult != -1) {
                    break;
                }

                removeStudent(Classroom, studentToRemove, &countOfCurrentStudents);

                break;
            }

            case CASE_LOG_PATH: {
                if (strcmp(logPath, "")) {
                    printf("Current path: %s\nDo you want to change the path?"
                           " (y - yes; n - no): ", logPath);

                    char wantNewPath;
                    do {
                        scanf("%c", &wantNewPath);
                        clearStdinBuffer();
                    } while (wantNewPath != 'y' && wantNewPath != 'n');

                    if (wantNewPath == 'n') {
                        printf("The path remains: %s\n", logPath);
                        break;
                    }

                    inputFilePath(logPath);
                    break;
                }

                inputFilePath(logPath);
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
#endif
