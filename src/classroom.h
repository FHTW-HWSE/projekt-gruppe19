/*       __
*     <(o )___
* 	   ( ._> /
*       `---'
*/
//
// CLASSROOM HEADER FILE FOR PROJEKT GRUPPE 19'S HWSE2 PROJECT (2023SS) (v1)
//

#ifndef CLASSROOM_H_INCLUDED
#define CLASSROOM_H_INCLUDED

//-----HEADER FILES-----//
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//-----MACROS-----//
#define ERROR "An error occurred.\n"    //error indicator generic message

//-----STRUCTURES-----//
typedef struct seat {                   //seat (chain links of the linked list structure)
    char student[9];                    //the student's 8-digit ID
    struct seat *nextSeat;              //the next seat's memory address
} seat;
typedef struct classroom {              //classroom (the chain of the linked list structure)
    seat *firstSeat;                    //the first seat's memory address
    seat *lastSeat;                     //the last seat's memory address
} classroom;

//-----FUNCTIONS-----//
/// Creates a new classroom.#################################################
/// \return the created classroom's memory address, or 0 when failed
classroom *classroomCreate(void) {
    classroom *newClassroom = (classroom *) malloc(sizeof(classroom));
    //allocate disk space for the classroom
    if (!newClassroom) return 0;    //return 0 when failed (newClassroom is null pointer)

    newClassroom->firstSeat = 0;    //make the first seat of the classroom default null pointer
    newClassroom->lastSeat = 0;     //make the last seat of the classroom default null pointer

    return newClassroom;            //return the classroom's memory address
}

/// Adds a student to the last empty seat of the classroom.
/// \param myClassroom the classroom's memory address
/// \param newStudent the student's 8-digit ID
void classroomAppendLastSeat(classroom *myClassroom, char *newStudent) {
    seat *newSeat = (seat *) malloc(sizeof(seat));  //allocate disk space for the new seat
    if (!newSeat) {            //if failed (newSeat is null pointer)...
        printf(ERROR);  //print the default error message to the stdout
        return;                //exit the function
    }

    newSeat->nextSeat = 0;                                          //no next element by default
    strcpy(newSeat->student, newStudent);               //set the new student to the new seat
    if (!myClassroom->firstSeat) myClassroom->firstSeat = newSeat;  //create the first seat is it doesn't exist yet...
    else myClassroom->lastSeat->nextSeat = newSeat;                 //or just append the list if it does
    myClassroom->lastSeat = newSeat;                                //make the newly added seat the last one
}

/// Searches for a specific student's seat's address in the memory. Stayed here for debugging.
/// \param myClassroom the classroom's memory address
/// \param searchedStudent the student's 8-digit ID
/// \return the seat's memory address, or 0 when failed
seat *classroomSearchStudAddr(classroom *myClassroom, char *searchedStudent) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));                   //allocate disk space for the stepping seat
    if (!searchSeat) return 0;              //return 0 when failed (searchSeat is null pointer)

    searchSeat = myClassroom->firstSeat;    //start the search with the classroom's first seat
    while (searchSeat && strcmp(searchSeat->student, searchedStudent)) {    //while there are seats
        //and the student wasn't found...
        searchSeat = searchSeat->nextSeat;  //step to the next seat
    }

    return searchSeat;                      //returns the searched seat's memory address
}

/// Searches for a specific student's seat's number in the memory.
/// \param myClassroom the classroom's memory address
/// \param searchedStudent the student's 8-digit ID
/// \return the index of the seat (0 is the first seat's index), or -1 when failed
unsigned int classroomSearchStudOrd(classroom *myClassroom, char *searchedStudent) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));               //allocate disk space for the stepping seat
    if (!searchSeat) return -1;             //return -1 when failed (searchSeat is null pointer)

    unsigned int ord = 0;                   //create the seat index counter variable
    searchSeat = myClassroom->firstSeat;    //start the search with the classroom's first seat
    while (searchSeat && strcmp(searchSeat->student, searchedStudent)) {    //while there are seats
        //and the student wasn't found...
        searchSeat = searchSeat->nextSeat;  //step to the next seat
        ord++;                              //also increment the index counter
    }
    return ord;                             //return the seat's index
}


/// ///Searches for a specific seat number's address in the memory. Stayed here for debugging.
/// \param myClassroom the classroom's memory address
/// \param searchedOrd the student's 8-digit ID
/// \return the seat's address, or 0 when failed
seat *classroomSearchOrdAddr(classroom *myClassroom, unsigned int searchedOrd) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));  //allocate disk space for the stepping seat
    if (!searchSeat) return 0;              //return 0 when failed (searchSeat is null pointer)

    searchSeat = myClassroom->firstSeat;    //start the search with the classroom's first seat
    while (searchSeat && searchedOrd) {     //while there are seats and the seat index wasn't found...
        searchSeat = searchSeat->nextSeat;  //step to the next seat
        searchedOrd--;                      //also decrement the index counter
    }

    return searchSeat;                      //return the seat's memory address
}

/// Searches for a specific seat's student in the memory. Stayed here for debugging.
/// \param myClassroom the classroom's memory address
/// \param searchedOrd the student's seat's index (0 is the first seat's index)
/// \return the student's 8-digit ID, or 0 when failed
char *classroomSearchOrdStud(classroom *myClassroom, unsigned int searchedOrd) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));   //allocate disk space for the stepping seat
    if (!searchSeat) return 0;              //return 0 when failed (searchSeat is null pointer)

    searchSeat = myClassroom->firstSeat;    //start the search with the classroom's first seat
    while (searchSeat && searchedOrd) {     //while there are seats and the seat index wasn't found...
        searchSeat = searchSeat->nextSeat;  //step to the next seat
        searchedOrd--;                      //also decrement the index counter
    }
    return searchSeat->student;             //return the student ID
}

/// Lists all the students in the classroom.
/// \param myClassroom the classroom's memory address
/// \param rows the count of rows of the classroom
/// \param cols the count of columns in the classroom
void classroomPrintWhole(classroom *myClassroom, unsigned int rows, unsigned int cols, char *ptr_path) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));       //allocate disk space for the stepping seat
    if (!searchSeat) {           //if failed (searchSeat is null pointer)...
        printf(ERROR);   //print the default error message to the stdout
        return;                 //exit the function
    }

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current local time and date: %s", asctime(timeinfo));


    searchSeat = myClassroom->firstSeat;                        //start the search with the classroom's first seat
    FILE *file = fopen(ptr_path, "a+");
    printf("The whole seating chart:\n---front---\n");			//print the classroom board to the stdout

    fprintf(file, "\nTime %sSeatingplan: \n", asctime(timeinfo));

    for (int i = 0; i < rows; i++) {                            //iterate through the rows
        for (int j = 0; j < cols; ++j) {                        //iterate through the columns
            printf("%s ", searchSeat->student); 				//print the current student ID to stdout
            fprintf(file, "%s", searchSeat->student);			//printf the currend studentID to file
            searchSeat = searchSeat->nextSeat;                  //step to the next seat
        }
        printf("%d\n", i + 1);									//add the column number in the end of the line
        fprintf(file, "%d\n", i+1);								//add the column number to the end of the line in file
    }
    for (int j = 0; j < cols; j++){ printf("%2d       ", j + 1); //add the row numbers in the end
        fprintf(file, "%2d       ", j + 1);}						//print row numbers to file
    printf("\n");												//insert a new line
    fprintf(file, "\n");										//inser new line in file
    fprintf(file, "------------------------------------------------------------------------------------");
    fclose(file);
}

/// Lists a seat's neighborhood in the classroom.
/// \param myClassroom the classroom's memory address
/// \param rows the count of rows of the classroom
/// \param cols the count of columns of the classroom
/// \param row the row of the searched student's seat (1 is the number of the first row)
/// \param col the column of the searched student's seat (1 is the number of the first column)
/// \param nT neighborhood type: 1 to list the student and the direct neighbors, 2 to lists the indirect neighbors too
void classroomPrintPartial(classroom *myClassroom, unsigned int rows, unsigned int cols,
                           unsigned int row, unsigned int col, char nT) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));   //allocate disk space for the stepping seat
    if (!searchSeat) {                                      //if failed (searchSeat is null pointer)...
        printf(ERROR);                               //print the default error message to the stdout
        return;                                             //exit the function
    }

    int rowIndex = row - 1, colIndex = col - 1;             //calculate the row and column indexes

    searchSeat = myClassroom->firstSeat;                    //start the search with the classroom's first seat

    printf("The surroundings of the queried student:\n---front---\n");  //print the classroom board to the stdout
    for (int i = 0; i < rows; i++) {                        //iterate through the rows
        for (int j = 0; j < cols; ++j) {                    //iterate through the columns
            if (i >= rowIndex - nT && i <= rowIndex + nT    //if the current student is the searched student
                && j >= colIndex - nT && j <= colIndex + nT) {  //or its direct/indirect neighbor...
                printf("%s ", searchSeat->student);   //print the current student ID to stdout
            }
            searchSeat = searchSeat->nextSeat;              //step to the next seat
        }
        if (i >= rowIndex - nT && i <= rowIndex + nT) printf("%d\n", i + 1);    //print the column number
    }                                                                                  //in the end of the line
    for (int j = 0; j < cols; j++) {                                                   //print the row numbers
        if (j >= colIndex - nT && j <= colIndex + nT) printf("%2d       ", j + 1);  //in the end
    }
    printf("\n");                                       //insert new line
}

/// Assigns a student to a seat in the classroom. Used for the removing function too.
/// \param myClassroom the classroom's memory address
/// \param newStudent the student's 8-digit ID
/// \param seatNumber the student's seat's index (0 is the first seat's index)
/// \return 1 when succeeded, 0 in case of a memory allocation error, or -1 when the seat is occupied
char classroomAssignStudent(classroom *myClassroom, char *newStudent, unsigned int seatNumber) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));   //allocate disk space for the stepping seat
    if (!searchSeat) return 0;                              //return 0 when failed (searchSeat is null pointer)

    searchSeat = myClassroom->firstSeat;                    //start the search with the first seat

    for (int i = 0; i < seatNumber; ++i) searchSeat = searchSeat->nextSeat; //navigate to the selected seat
    if (strcmp(searchSeat->student, "########") && strcmp(newStudent, "########")) return -1;   //return -1 if occupied
    strcpy(searchSeat->student, newStudent);     //assign the student to the seat
    return 1;                                                //return 1, indicating success
}

/// Removes a student from the classroom. Based on classroomAssignStudent().
/// \param myClassroom the classroom's memory address
/// \param seatNumber the student's seat's index (0 is the first seat's index)
/// \return returns 1 when succeeded, or 0 when failed
char classroomRemoveStudent(classroom *myClassroom, unsigned int seatNumber) {
    return classroomAssignStudent(myClassroom, "########", seatNumber); //invokes assigning function
}                                                                  //with placeholder character as new student

/// Checks whether a student exists in the classroom or not.
/// \param myClassroom the classroom's memory address
/// \param myStudent the student's 8-digit ID
/// \return returns -1 when student was found, 1 when was not found, or 0 in case of memory allocation error
char classroomCheckStudent(classroom *myClassroom, char *myStudent) {
    seat *searchSeat = (seat *) malloc(sizeof(seat));       //allocate disk space for the stepping seat
    if (!searchSeat) return 0;                                  //return 0 when failed (searchSeat is null pointer)

    searchSeat = myClassroom->firstSeat;                        //start the search with the first seat
    while (searchSeat) {                                        //while there are seats in the classroom...
        if (!strcmp(searchSeat->student, myStudent)) return -1; //return -1 if current student is the searched student
        searchSeat = searchSeat->nextSeat;                      //step to the next seat
    }

    return 1;                                                   //return 1 if student was not found
}

#endif // CLASSROOM_H_INCLUDED
