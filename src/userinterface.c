//-----HEADER FILES-----//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "classroom.h"
//#include "time_track_aktuell.h"
#include <time.h>

//-----MACROS-----//
#define MAX_ROWS 20
#define MAX_COLS 20
#define CHESSBOARD 'c'
#define FAR_SPACED 'f'

#define ERROR "An error occurred.\n"

#define CASE_GENERATE 1
#define CASE_ASSIGN 2
#define CASE_SAVE 3
#define CASE_DIRECT_NEIGHBORS 4
#define CASE_INDIRECT_NEIGHBORS 5
#define CASE_REMOVE 6
#define CASE_LOGPATH 7
#define CASE_EXIT 0

//-----GLOBAL VARIABLES-----//
unsigned int rows = 0;
unsigned int cols = 0;
char seatingArrangement;
const char *logpath = NULL;

char opt1[] = "Generate seating arrangement";
//-----FUNCTIONS-----//
///Clears input buffer. Must used to avoid input type mismatches of scanf function.
///int [count of buffered and deleted characters] = clearStdinBuffer();
int clearStdinBuffer() {
    int bufferedCharacters = -1;
    int c;
    do {
        scanf("%i", &c);
        if (++bufferedCharacters == -1) bufferedCharacters++;
    } while (c != '\n' && c != EOF);

    return bufferedCharacters;
}

///Reads numbers from stdin. It needs the string it will ask for the numbers with,
/// the maximum and the minimum of the numbers that can be entered. Returns with the number
/// received from the user.
///int userInputNumber = inputNumbers([String like "Please input a number here: "],
/// [max value to enter], [min value to enter]);
int inputNumbers(char *request, unsigned int upperLimit, unsigned int lowerLimit) {
    int result;
    do {
        printf("%s", request);
        scanf("%d", &result);
        clearStdinBuffer();
    } while (result > upperLimit || result < lowerLimit);

    return result;
}

char inputStudentID(classroom *Classroom, char *newStudent, char *request,
                    char *found, char *notFound) {
    char isValid;
    do {
        printf("%s", request);
        scanf("%8s", newStudent);
        int buffered = clearStdinBuffer();
        for (int i = 0; i < 8; ++i) {
            isValid = newStudent[i] != 0 && !buffered;
            if (!isValid) break;
        }
    } while (!isValid);

    char result = classroomCheckStudent(Classroom, newStudent);
    if (result == -1) printf("%s", found);
    else if (result == 0) printf(ERROR);
    else printf("%s", notFound);
    return result;
}

int isSeatPlanGenerated() {
    return (rows != 0 && cols != 0);
}


///Checks if a logfile path has already been entered
int isPathKnown(){
    return (logpath != NULL);
}

unsigned int calcSeat(unsigned int row, unsigned int col) {
    unsigned int seatIndex = (row - 1) * cols + col - 1;
    if ((seatingArrangement == FAR_SPACED && row & 1 && col & 1)
        || (seatingArrangement == CHESSBOARD && !((row + col) & 1)))
        return seatIndex;
    return -1;
}

///Reads a character from stdin and saves it as the seating arrangement
/// (global variable), which can be FAR_SPACED or CHESSBOARD.
///inputSeatingArrangement();
void inputSeatingArrangement(void) {
    do {
        printf("Please enter the arrangement pattern (c - chessboard; f - far spaced): ");
        scanf("%c", &seatingArrangement);
        clearStdinBuffer();
    } while (seatingArrangement != FAR_SPACED && seatingArrangement != CHESSBOARD);
}

///Calculates rows and columns (both starting from 1) from the received seat number
/// (seat index, which is 0 for the first seat). It writes the value into the original
/// variables through pointers, so it takes the original variables' memory address.
///calcRowsCols([the seat number], [the memory address of the variable containing the
/// specific row], [similar memory address for the column]);
void calcRowsCols(unsigned int seatIndex, unsigned int *row, unsigned int *col) {
    *col = seatIndex % cols + 1;
    if (!*col) *col += cols - 1;
    *row = seatIndex / cols + 1;
    if (!seatIndex % cols) (*row)--;
}

///Displays the main menu.
///displayMenu();
void displayMenu() {
    printf("Menu:\n");
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

///Generates the seating arrangement, using the rows' and columns' global variables.
/// Takes the classroom to fill. returns with the maximal number of students to be
/// assigned safely in the room.
///unsigned short [max people] = generateSeatingArrangement([name of classroom]);
unsigned short generateSeatingArrangement(classroom *Classroom) {
    unsigned short result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((seatingArrangement == CHESSBOARD && !((i + j) & 1)) ||
                (seatingArrangement == FAR_SPACED && !(i & 1) && !(j & 1))) {
                classroomAppendLastSeat(Classroom, "########");
                result++;
            } else { classroomAppendLastSeat(Classroom, "--------"); }
        }
    }

    return result;
}

///Assigns a student to a seat. Takes the classroom, the student ID, the seat's number,
/// the seat's row and column and the address of the variable which stores the amount
/// of students assigned to the room.
///assignSeat([name of classroom], [ID of student to be assigned], [seat's index],
/// [seat's row], [seat's column], [the address of the current student's count variable]);
void assignSeat(classroom *Classroom, char *newStudent, unsigned int seatNumber,
                unsigned int row, unsigned int col, unsigned short *currentStudents) {
    char wasItSuccessful = classroomAssignStudent(Classroom,
                                                  newStudent, seatNumber);
    if (wasItSuccessful == 1) {

        (*currentStudents)++;
        printf("Student %s has been assigned to seat %d (%d. row, %d. column).\n",
               newStudent, seatNumber,
               row, col);
        logFileSeatAssignment(*logpath, seatNumber, newStudent, 'e');
    } else if (wasItSuccessful == 0) { printf(ERROR); }
    else { printf("The seat is already occupied.\n"); }
}

/*
void saveStudentInfo(Student* student, FILE* file) {
    // Implementation for saving student information to a file
    // ...
}
*/

///Gets the rows and columns of a specific student's seat. Takes the classroom to search in,
/// the student to search for, and the memory addresses of the external rows and columns to write,
/// the values into them. Returns the seat index it has found (and technically, the row and column
/// numbers through the pointers).
///unsigned int [the seat number's variable that receives the value] =
/// getSeatDetails([classroom's name], [student ID], address of the rows that receives the value],
/// [address of the column that receives the value]);
unsigned int getSeatDetails(classroom * Classroom, char * searchedStudent,
                            unsigned int * row, unsigned int * col) {
    unsigned int foundSeatIndex = classroomSearchStudOrd(Classroom, searchedStudent);
    calcRowsCols(foundSeatIndex, row, col);

    return foundSeatIndex;
}

///Prints the surroundings of a specific student. Takes the name of the classroom, the searched
/// student's ID and the neighborhood type, which can be 1 (direct neighbors) or 2
/// (indirect neighbors too).
///findNeighbors([the classroom's name], [the searched student's ID], [neighborhood type]);
void findNeighbors(classroom *Classroom, char *searchedStudent, char neighborhoodType) {
    unsigned int row, col;
    unsigned int seatIndex = getSeatDetails(Classroom, searchedStudent, &row, &col);
    if(seatIndex == -1) {
        printf(ERROR);
        return;
    }
    classroomPrintPartial(Classroom, rows, cols, row, col, neighborhoodType);
}

///Removes student from the classroom. Takes the classroom name, the ID of the student to remove,
/// and the memory address of the variable containing the currently assigned students.
///removeStudent([name of the classroom], [student ID to remove], [current students variable's address]);
void removeStudent(classroom * Classroom, char * studentToRemove, unsigned short * currentStudents){
    unsigned int row, col;
    unsigned int seatIndex = getSeatDetails(Classroom, studentToRemove, &row, &col);
    if(seatIndex == -1) {
        printf(ERROR);
        return;
    }
    char wasItSuccessful = classroomRemoveStudent(Classroom, seatIndex);

    if (wasItSuccessful == 1) {

        (*currentStudents)--;
        printf("Student %s has been removed from seat %d (%d. row, %d. column).\n",
               studentToRemove, seatIndex,
               row, col);
        logFileSeatAssignment(*logpath, seatIndex, studentToRemove, 'r');
    }
    else { printf(ERROR); }
}

///Checks if the entered path is valid or not
bool validPath(const char log_path){

    if(log_path == NULL) {
        return (false);
    }
    else{
        return (true);
    }
}

/*void writeSeatingChartToFile(FILE *log_pfad, Node *head){

    char write_time[20] = {};
    write_time = time_function();
    FILE *file = fopen(log_path, "a");
    if (file == NULL) {
        fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
        return;
    }

    if(head->next != NULL)
    {
        fprintf(fptr, "\nPet Name: %s\nAge: %d\n\n", head->name, head->age);
        writeToFile(fptr, head->next);
    }
    else
        fprintf(fptr, "\nPet Name: %s\nAge: %d\n\n", head->name, head->age);
}
*/

void logFileSeatAssignment(const char *log_pfad, char place_ID, char student_ID, char assignment_status ){

    //char write_time[20] = {};
    char add_or_remove = '\0';

    add_or_remove = assignment_status;

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current local time and date: %s", asctime (timeinfo) );

    //write_time = time_function();
    FILE *file = fopen(log_pfad, "a");
    if (file == NULL) {
        fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
        return;
    }

    if (add_or_remove == '\0') {

        fprintf(file, "%s %c %c\n", asctime(timeinfo), place_ID, student_ID);
    }

    if (add_or_remove == 'e'){

        fprintf(file, "Der Student mit der Nummer %c hat um %s den Sitzplatz %s bezogen.\n", student_ID, asctime(timeinfo), place_ID);

        fprintf(file, "Die Nachbarn des Studenten mit der Nummer %c am Sitzplatz %c sind um %s ---------Nachbarn-------", student_ID, place_ID, asctime(timeinfo));

    }

    if (add_or_remove == 'r'){

        fprintf(file, "Der Student mit der Nummer %c hat um %s den Sitzplatz %s verlassen.\n", student_ID, asctime(timeinfo), place_ID);

        fprintf(file, "Die Nachbarn des Studenten mit der Nummer %c am Sitzplatz %c sind um %s ---------Nachbarn-------", student_ID, place_ID, asctime(timeinfo));

    }
    fclose(file);
}


int main() {
    classroom *Classroom = classroomCreate();
    int option = -1;
    int convertedOption;

    unsigned short currentStudents = 0, maxStudents;
    char wantNewPath = '\0';

    do {
        displayMenu();
        while((option = getchar()) != '\n' && option != EOF){
            convertedOption = option - '0';
        }

        printf("%i",convertedOption);
        //clearStdinBuffer();

        switch (convertedOption) {
            case CASE_GENERATE:
                if (!isPathKnown()){
                    printf("Please enter a logpath first at option 7.\n");
                    break;
                }
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
                classroomPrintWhole(Classroom, rows, cols);
                printf("Chart printed.\n");

                break;


            case CASE_ASSIGN:
                if (!isPathKnown()){
                    printf("Please enter a logpath first at option 7.\n");
                    break;
                }
                if (!isSeatPlanGenerated()) {
                    printf("Seats have to be arranged first.\n");
                } else if (currentStudents == maxStudents) {
                    printf("Maximal assignable student count is reached.\n");
                } else {
                    char newStudent[9];
                    char inputResult = inputStudentID(Classroom, newStudent,
                                                      "Please enter the student ID you would like to assign: ",
                                                      "The student is already assigned.\n", "");
                    if (inputResult != 1) break;

                    unsigned int row, col, seatNumber;

                    do {
                        row = inputNumbers("Please enter the seat's row: ",
                                           rows, 1);
                        col = inputNumbers("Please enter the seat's column: ",
                                           cols, 1);
                        seatNumber = calcSeat(row, col);
                    } while (seatNumber == -1);

                    assignSeat(Classroom, newStudent, seatNumber, row, col, &currentStudents);
                }
                break;

            case CASE_SAVE:
                if (!isPathKnown()){
                    printf("Please enter a logpath first at option 7.\n");
                    break;
                }
                if (!isSeatPlanGenerated()) {
                    printf("Seat arrangement has to be generated first.\n");
                    break;
                }



                break;

            case CASE_DIRECT_NEIGHBORS:
                if (!isPathKnown()){
                    printf("Please enter a logpath first at option 7.\n");
                    break;
                }
                if (!isSeatPlanGenerated()) {
                    printf("Seat arrangement has to be generated first.\n");
                    break;
                }

                char searchedStudent[9];
                char inputResult = inputStudentID(Classroom, searchedStudent,
                                                  "Please enter the student's ID to be searched for: ",
                                                  "", "The student was not found.\n");
                if (inputResult != -1) break;

                findNeighbors(Classroom, searchedStudent, 1);

                break;

            case CASE_INDIRECT_NEIGHBORS:
                if (!isPathKnown()){
                    printf("Please enter a logpath first at option 7.\n");
                    break;
                }
                if (!isSeatPlanGenerated()) {
                    printf("Seat arrangement has to be generated first.\n");
                    break;
                }
                else{
                    char searchedStudent[9];
                    char inputResult = inputStudentID(Classroom, searchedStudent,
                                                      "Please enter the student's ID to be searched for: ",
                                                      "", "The student was not found.\n");
                }
                if (inputResult != -1) break;

                findNeighbors(Classroom, searchedStudent, 2);

                break;


            case CASE_REMOVE:
                if (!isPathKnown()){
                    printf("Please enter a logpath first at option 7.\n");
                    break;
                }
                if (!isSeatPlanGenerated()) {

                    printf("Seats have to be arranged first.\n");
                    break;
                } else {
                    char rmStudent[9];
                    char inputResult = inputStudentID(
                            Classroom,
                            rmStudent,
                            "Please enter the student ID you would like to remove: ",
                            "", "The student was not found.\n");
                    if (inputResult != -1) break;

                    removeStudent(Classroom, rmStudent, &currentStudents);
                }
                break;


            case CASE_LOGPATH:

                if (isPathKnown()) {
                    printf("Current path %c \n: ", *logpath);
                    printf("Do you want to create a new path? y: yes, n: no");
                    do {
                        wantNewPath = getchar();
                        if (wantNewPath != 'y' || wantNewPath != 'n') {
                            wantNewPath = '\0';
                            printf("Invalid option!\n");
                        }
                    } while (wantNewPath == '\0');
                    if(wantNewPath == 'y'){
                        do {
                            printf("Please enter a new logpath:\n");
                            scanf(*logpath);

                        }while(!validPath(*logpath));
                    }
                    else{
                        break;
                    }
                }
                if(!isPathKnown()){
                    do {
                        printf("Please enter a valid logpath.\n");
                        scanf(*logpath);
                    }while(!validPath(*logpath));
                }
                break;

            case CASE_EXIT:
                printf("Program is exiting.\n");
                break;

            default:
                printf("Invalid option. Choose again.\n");
                break;
        }
    } while (option != CASE_EXIT);

    return 0;
}


