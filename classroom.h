///CLASSROOM HEADER FILE FOR PROJEKT GRUPPE 19'S HWSE2 PROJECT (2023SS) (v1)

#ifndef CLASSROOM_H_INCLUDED
#define CLASSROOM_H_INCLUDED

//-----HEADER FILES-----//
#include <malloc.h>
#include <stdio.h>
#include <string.h>

//-----MACROS-----//
#define ERROR "An error occurred.\n"

//-----STRUCTURES-----//
typedef struct seat {
    char student[9];
    struct seat *nextSeat;
} seat;
typedef struct classroom {
    seat *firstSeat;
    seat *lastSeat;
} classroom;

//-----FUNCTIONS-----//
///Creates a new classroom. Returns the created classroom's memory address,
/// or 0 when failed.
///classroom * [desired name of classroom] = classroomCreate();
classroom *classroomCreate(void) {
    classroom *newClassroom = (classroom *) malloc(sizeof(classroom));
    if (!newClassroom) return 0;

    newClassroom->firstSeat = 0;
    newClassroom->lastSeat = 0;

    return newClassroom;
}

///Adds a student to the back of the classroom.
///classroomAppendLastSeat([the earlier created classroom's name],
/// [the ID of the student to book a seat for]);
void classroomAppendLastSeat(classroom *myClassroom, char *newStudent) {
    seat *newSeat = (seat *) malloc(sizeof(seat));
    if (!newSeat) {
        printf(ERROR);
        return;
    }

    newSeat->nextSeat = 0;
    strcpy(newSeat->student, newStudent);
    if (!myClassroom->firstSeat) myClassroom->firstSeat = newSeat;
    else myClassroom->lastSeat->nextSeat = newSeat;
    myClassroom->lastSeat = newSeat;
}

///Searches for a specific student's seat's address in the memory. Returns the seat's
/// memory address, or 0 when failed. Stayed here for debugging.
///seat * [desired pointer name] = classroomSearchStudAddr([the classroom's name to search in],
/// [the student ID to search for]);
seat *classroomSearchStudAddr(classroom *myClassroom, char *searchedStudent) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if (!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while (searchSeat && strcmp(searchSeat->student, searchedStudent)) {
        searchSeat = searchSeat->nextSeat;
    }

    return searchSeat;
}

///Searches for a specific student's seat's number in the memory.
/// Returns with the index of the seat (0 is the first seat's index),
/// or -1 when failed.
///unsigned int [desired variable name] =
/// classroomSearchStudOrd([the classroom's name to search in],
/// [the student ID to search for]);
unsigned int classroomSearchStudOrd(classroom *myClassroom, char *searchedStudent) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if (!searchSeat) return -1;

    unsigned int ord = 0;
    searchSeat = myClassroom->firstSeat;
    while (searchSeat && strcmp(searchSeat->student, searchedStudent)) {
        searchSeat = searchSeat->nextSeat;
        ord++;
    }
    return ord;
}

///Searches for a specific seat number's address in the memory. Returns the address,
/// or 0 when failed. Stayed here for debugging.
///seat * [desired pointer name] = classroomSearchOrdAddr([the classroom's name to search in],
/// [the seat number to search for]);
seat *classroomSearchOrdAddr(classroom *myClassroom, unsigned int searchedOrd) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if (!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while (searchSeat && searchedOrd) {
        searchSeat = searchSeat->nextSeat;
        searchedOrd--;
    }

    return searchSeat;
}

///Searches for a specific seat's student in the memory. Returns the seat number,
/// or 0 when failed. Stayed here for debugging.
///char * [desired pointer/string name] =
/// classroomSearchOrdStud([the classroom's name to search in], [the seat number to search for]);
char *classroomSearchOrdStud(classroom *myClassroom, unsigned int searchedOrd) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if (!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while (searchSeat && searchedOrd) {
        searchSeat = searchSeat->nextSeat;
        searchedOrd--;
    }
    return searchSeat->student;
}

///Lists all the students in the classroom.
///classroomPrintWhole([the name of the classroom], [the number of rows in the classroom],
/// [the number of columns in the classroom]);
void classroomPrintWhole(classroom *myClassroom, unsigned int rows, unsigned int cols) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) {
        printf(ERROR);
        return;
    }

    searchSeat = myClassroom->firstSeat;

    printf("The whole seating chart:\n---front---\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            printf("%s ", searchSeat->student);
            searchSeat = searchSeat->nextSeat;
        }
        printf("%d\n", i + 1);
    }
    for (int j = 0; j < cols; j++) printf("%2d       ", j + 1);
    printf("\n");
}

///Lists a seat's neighborhood in the classroom. nT is the neighborhood type, can be
/// 1 (listing only the student and the direct neighbors) or 2 (listing
/// the indirect neighbors too).
///classroomPrintPartial([the name of the classroom], [the number of rows in the classroom],
/// [the number of columns in the classroom], [the row of the seat to be queried],
/// [the columns of the seat to be queried], [neighborhood type]);
void classroomPrintPartial(classroom *myClassroom, unsigned int rows, unsigned int cols,
                           unsigned int row, unsigned int col, char nT) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) {
        printf(ERROR);
        return;
    }

    int rowIndex = row - 1, colIndex = col - 1;

    searchSeat = myClassroom->firstSeat;

    printf("The surroundings of the queried student:\n---front---\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            if (i >= rowIndex - nT && i <= rowIndex + nT
                && j >= colIndex - nT && j <= colIndex + nT) {
                printf("%s ", searchSeat->student);
            }
            searchSeat = searchSeat->nextSeat;
        }
        if (i >= rowIndex - nT && i <= rowIndex + nT) printf("%d\n", i + 1);
    }
    for (int j = 0; j < cols; j++) {
        if (j >= colIndex - nT && j <= colIndex + nT) printf("%2d       ", j + 1);
    }
    printf("\n");
}

///Assigns a student to a seat in the classroom. Used for the removing function too. Returns
/// 1 when succeeded, 0 in case of a memory allocation failure, -1 when the seat is already
/// occupied.
///char [variable storing whether it was successful or not] classroomAssignStudent(
/// [classroom's name], [student ID], [seat number]);
char classroomAssignStudent(classroom *myClassroom, char *newStudent, unsigned int seatNumber) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if (!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;

    for (int i = 0; i < seatNumber; ++i) searchSeat = searchSeat->nextSeat;
    if (strcmp(searchSeat->student, "########") && strcmp(newStudent, "########")) return -1;
    strcpy(searchSeat->student, newStudent);
    return 1;
}

///Removes a student from the classroom. Based on classroomAssignStudent(). Returns
/// 1 when succeeded, or 0 when failed.
///classroomRemoveStudent([classroom's name], [student ID], [seat number]);
char classroomRemoveStudent(classroom *myClassroom, unsigned int seatNumber) {
    return classroomAssignStudent(myClassroom, "########", seatNumber);
}

///Checks whether a student exists in the classroom or not. Returns -1 when student is found,
/// 1 when student is not found, 0 when fails.
///classroomCheckStudent([classroom's name], [student ID to search for]);
char classroomCheckStudent(classroom *myClassroom, char *myStudent) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));
    if (!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while (searchSeat) {
        if (!strcmp(searchSeat->student, myStudent)) return -1;
        searchSeat = searchSeat->nextSeat;
    }

    return 1;
}

#endif // CLASSROOM_H_INCLUDED
