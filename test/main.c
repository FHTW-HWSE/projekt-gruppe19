#define TEST
#include "userinterface.c"
#include <stdio.h>
#include <assert.h>
#include "classroom.h"


void test_clearStdinBuffer() {
    // Test case: Test clearing the input buffer
    // Assuming the input buffer has 5 characters: "Hello"
    // The function should clear the buffer and return 5
    printf("This is a test for clearing the input buffer. Please type 'Hello': ");
    int bufferedCharacters = clearStdinBuffer();

    assert(bufferedCharacters == 5);
}

void test_inputNumbers() {
    // Test case: Test inputNumbers function
    // Assuming the user enters a number between 1 and 10
    // The function should return the entered number

    unsigned int result = inputNumbers("This is a test for the input of numbers.", 10, 1);
    assert(result >= 1 && result <= 10);
}

void test_inputStudentID() {
    // Test case: Test inputStudentID function
    // Assuming the user enters a valid student ID that doesn't exist in the classroom
    // The function should return 1

    classroom *Classroom = classroomCreate();

    char newStudent[9] = "student1";
    char result = inputStudentID(Classroom, newStudent, "Please enter a student ID: ",
                                 "Student already exists.\n", "Student not found.\n");
    assert(result == 1);

}

void test_generateSeatingArrangement() {
    // Test case: Test generateSeatingArrangement function
    // For this test we assume the user enters 5 for rows as well as columns and wants a Chessboard-Layout
    // The function should return the number of students that can sit in the classroom
    rows = 5; cols = 5; seatingArrangement = CHESSBOARD;
    classroom *test_classroom = classroomCreate();

    unsigned short result = 13;
    assert(result == generateSeatingArrangement(test_classroom));
}

void test_classroomAssignStudent() {
    // Test case: Test classroomAssignStudent function
    // For this test we assume the classroom has 5 rows, 5 columns and a Chessboard-Layout - the user wants to assign the student to seat nr. 3
    // The function should return a 1 if the assignment was successful
    rows = 5; cols = 5; seatingArrangement = CHESSBOARD;

    classroom *test_classroom = classroomCreate();
    generateSeatingArrangement(test_classroom);
    char result = classroomAssignStudent(test_classroom, "student1", 2);

    assert(result == 1);
    assert(strcmp(test_classroom->firstSeat->nextSeat->nextSeat->student, "student1") == 0);
}

void test_classroomAppendLastSeat() {
    // Test case: Test classroomAppendLastSeat function
    // The user wants to assign a student to the next possible seat
    // The function should copy the student ID into the corresponding seat
    rows = 5; cols = 5; seatingArrangement = CHESSBOARD;
    classroom *test_classroom = classroomCreate();
    generateSeatingArrangement(test_classroom);
    char newStudent[9] = "student1";
    classroomAppendLastSeat(test_classroom, (char*)&newStudent);
    assert(strcmp(test_classroom->lastSeat->student, newStudent) == 0);
}

void test_classroomPrintWhole() {
    // Test case: Test classroomPrintWhole function
    // The function should put out the Layout of the classroom
    rows = 5; cols = 5; seatingArrangement = CHESSBOARD; char answer;
    char filePath[201] = "Test";

    classroom *test_classroom = classroomCreate();
    generateSeatingArrangement(test_classroom);
    classroomPrintWhole(test_classroom, rows, cols, filePath);
    printf("This is a test for the seating arrangement print function. \n");
    printf("Can you see a successfully printed out seating chart in the console? Answer y for yes if so.\n");
    scanf(" %c", &answer);
    assert(answer == 'y');
}

void test_getSeatDetails() {
    // Test case: Test getSeatDetails function
    // The user wants to find the Seat Index for an already assigned student
    // Function should return the seat index of the student
    rows = 5; cols = 5; seatingArrangement = CHESSBOARD;

    classroom *test_classroom = classroomCreate();
    char newStudent[9] = "student1";
    generateSeatingArrangement(test_classroom);
    classroomAssignStudent(test_classroom, (char*) &newStudent, 2);
    unsigned int seatIndex_test = getSeatDetails(test_classroom, (char*) &newStudent,&rows, &cols);
    assert(seatIndex_test == 2);
}

void test_findNeighbors() {
    // Test case: Test find Neighbors function
    // The user wants to either find the direct or indirect neighbors of a specific student
    // The function should print out the layout surrounding the student
    rows = 5; cols = 5; seatingArrangement = CHESSBOARD; char answer;
    char filePath[201] = "Test";
    classroom *test_classroom = classroomCreate();
    char newStudent[9] = "student1";
    generateSeatingArrangement(test_classroom);
    classroomAssignStudent(test_classroom, (char*) &newStudent, 2);
    findNeighbors(test_classroom, newStudent, 1, filePath);
    printf("This is a test for the find Neighbors function. \n");
    printf("Can you see the immediate surroundings of Student1? Answer y for yes if so.\n");
    scanf(" %c", &answer);
    assert(answer == 'y');
}
void test_incorrectvalues_dimensions() {
    // Test case: Incorrect values for dimension
    // This should test if the user can retry if he enters wrong dimensions for the input
    char answer; seatingArrangement = CHESSBOARD;
    classroom *test_classroom = classroomCreate();
    printf("This is a test for the input of dimensions. Please try to enter wrong inputs, the program should always allow you to try again.\n");
    rows = inputNumbers("Please enter the number of rows.",
                        MAX_ROWS, 1);
    cols = inputNumbers("Please enter the number of columns.",
                        MAX_COLS, 1);


    generateSeatingArrangement(test_classroom);
    printf("Were you able to retry all the inputs? Answer y for yes if so.\n");
    scanf(" %c", &answer);
    assert(answer == 'y');
}

// Add more test cases for the remaining functions...

int main() {
    // Run the unit tests
    test_clearStdinBuffer();
    test_inputNumbers();
    test_inputStudentID();
    test_generateSeatingArrangement();
    test_classroomAssignStudent();
    test_getSeatDetails();
    test_classroomPrintWhole();
    test_classroomAppendLastSeat();
    test_findNeighbors();
    test_incorrectvalues_dimensions();
    // Call other test functions here

    printf("All tests passed successfully!\n");

    return 0;
}
