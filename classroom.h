///CLASSROOM HEADER FILE FOR PROJEKT GRUPPE 19'S HWSE2 PROJECT (2023SS) (v1)

#ifndef CLASSROOM_H_INCLUDED
#define CLASSROOM_H_INCLUDED

//-----HEADER FILES-----
#include <malloc.h>
#include <stdio.h>
#include <string.h>

//-----STRUCTURES-----
typedef struct seat {
    char student[9];
    struct seat * nextSeat;
} seat;
typedef struct classroom {
    seat * firstSeat;
    seat * lastSeat;
} classroom;

//-----FUNCTIONS-----

///classroomCreate - creating a new classroom:
///classroom * [desired name of classroom] = classroomCreate();
classroom * classroomCreate(void)
{
    classroom * newClassroom = (classroom *) malloc(sizeof(classroom));
    if(!newClassroom) return 0;

    newClassroom->firstSeat = 0;
    newClassroom->lastSeat = 0;

    return newClassroom;
}

///classRoomAppendLastSeat - adding a student to the back of the classroom:
///classroomAppendLastSeat([the earlier created classroom's name], [the ID of the student to book a seat for]);
void classroomAppendLastSeat(classroom * myClassroom, char * newStudent)
{
    seat * newSeat = (seat *) malloc(sizeof(seat));
    if(!newSeat) return;

    newSeat->nextSeat = 0;
    strcpy(newSeat->student, newStudent);
    if(!myClassroom->firstSeat) myClassroom->firstSeat = newSeat;
    else myClassroom->lastSeat->nextSeat = newSeat;
    myClassroom->lastSeat = newSeat;
}

///classRoomAppendFirstSeat - adding a student to the front of the classroom:
///classroomAppendFirstSeat([the earlier created classroom's name], [the ID of the student to book a seat for]);
void classroomAppendFirstSeat(classroom * myClassroom, char * newStudent)
{
    seat * newSeat = (seat *) malloc(sizeof(seat));
    if(!newSeat) return;

    newSeat->nextSeat = myClassroom->firstSeat;
    strcpy(newSeat->student, newStudent);
    myClassroom->firstSeat = newSeat;
}

///classroomSearchStudAddr - searching for a specific student's seat's address in the memory:
///seat * [desired pointer name] = classroomSearchStudAddr([the classroom's name to search in], [the student ID to search for]);
seat * classroomSearchStudAddr(classroom * myClassroom, char * searchedStudent)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while(searchSeat && strcmp(searchSeat->student, searchedStudent))
    {
        searchSeat = searchSeat->nextSeat;
    }

    return searchSeat;
}

///classroomSearchStudOrd - searching for a specific student's seat's number in the memory:
///unsigned int [desired variable name] = classroomSearchStudOrd([the classroom's name to search in], [the number to search for]);
unsigned int classroomSearchStudOrd(classroom * myClassroom, char * searchedStudent)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return 0;

    unsigned int ord = 0;
    searchSeat = myClassroom->firstSeat;
    while(searchSeat && strcmp(searchSeat->student, searchedStudent))
    {
         searchSeat = searchSeat->nextSeat;
         ord++;
    }
    return ord;
}

///classroomSearchOrdAddr - searching for a specific seat number's address in the memory:
///seat * [desired pointer name] = classroomSearchOrdAddr([the classroom's name to search in], [the seat number to search for]);
seat * classroomSearchOrdAddr(classroom * myClassroom, unsigned int searchedOrd)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while(searchSeat && searchedOrd)
    {
        searchSeat = searchSeat->nextSeat;
        searchedOrd--;
    }

    return searchSeat;
}

///classroomSearchOrdStud - searching for a specific seat's student in the memory:
///char * [desired pointer/string name] = classroomSearchOrdStud([the classroom's name to search in], [the seat number to search for]);
char * classroomSearchOrdStud(classroom * myClassroom, unsigned int searchedOrd)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while(searchSeat && searchedOrd)
    {
         searchSeat = searchSeat->nextSeat;
         searchedOrd--;
    }
    return searchSeat->student;
}
///classroomRemove - removing a student from the classroom:
///classroomRemove([the name of the classroom], [the student ID of the student to remove]);
void classroomRemove(classroom * myClassroom, char * removeStudent)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return;

    searchSeat = myClassroom->firstSeat;
    while(searchSeat && strcmp(searchSeat->nextSeat->student, removeStudent)) searchSeat = searchSeat->nextSeat;

    seat * removeSeat = searchSeat->nextSeat;
    searchSeat->nextSeat = removeSeat->nextSeat;
    free((seat *) removeSeat);
}

///classroomPrint - listing all the students in the classroom:
///classroomPrint([the name of the classroom]);
void classroomPrintWhole(classroom * myClassroom, unsigned int rows, unsigned int cols)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return;

    searchSeat = myClassroom->firstSeat;

    printf("---front---\n");
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; ++j) {
            printf("%s ", searchSeat->student);
            searchSeat = searchSeat->nextSeat;
        }
        printf("%d\n", i + 1);
    }
    for(int j = 0; j < cols; j++) printf("%2d       ", j + 1);
    printf("\n");
}

void classroomPrintPartial(classroom * myClassroom, unsigned int rows, unsigned int cols,
                           unsigned int row, unsigned int col, char nT)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return;

    unsigned int rowIndex = row - 1, colIndex = col - 1;

    searchSeat = myClassroom->firstSeat;

    printf("---front---\n");
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; ++j) {
            if(i >= rowIndex - nT && i <= rowIndex + nT
            && j >= colIndex - nT && j <= colIndex + nT) {
                printf("%s ", searchSeat->student);
            }
            searchSeat = searchSeat->nextSeat;
        }
        if(i >= rowIndex - nT && i <= rowIndex + nT) printf("%d\n", i + 1);
    }
    for(int j = 0; j < cols; j++) {
        if(j >= colIndex - nT && j <= colIndex + nT) printf("%2d       ", j + 1);
    }
    printf("\n");
}

char classroomAssignStudent(classroom * myClassroom, char * newStudent, unsigned int seatNumber)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;

    for (int i = 0; i < seatNumber; ++i) searchSeat = searchSeat->nextSeat;
    if(strcmp(searchSeat->student, "########")) return -1;
    strcpy(searchSeat->student, newStudent);
    return 1;
}

void classroomRemoveStudent(classroom * myClassroom, unsigned int seatNumber)
{
    classroomAssignStudent(myClassroom, "########", seatNumber);
}

char classroomCheckStudent(classroom * myClassroom, char * myStudent)
{
    seat * searchSeat = (seat *) malloc(sizeof(seat));
    if(!searchSeat) return 0;

    searchSeat = myClassroom->firstSeat;
    while(searchSeat) {
        if(!strcmp(searchSeat->student, myStudent)) return -1;
        searchSeat = searchSeat->nextSeat;
    }

    return 1;
}

#endif // CLASSROOM_H_INCLUDED
