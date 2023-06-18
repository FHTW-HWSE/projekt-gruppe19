/*
*       __
*     <(o )___
* 	   ( ._> /
*       `---'
*/
#define TEST

#include "userinterface.c"

#define SUCCESSFUL "Test successfully passed!\n"
#define FAILED "Test failed!\n"

unsigned char countOfSuccessfulInputs;
unsigned short countOfStudentsToAssign;
unsigned char countOfOptions;

void testInputRowsAndColumns(void) {
    printf("\nTest cases: Input of classroom dimensions & Incorrect values for dimension\n"
           "Please follow the instructions and try the input. After four correct "
           "inputs (twice the rows and twice the columns), the test is over.\n");

    countOfSuccessfulInputs = 0;
    for (int i = 0; i < 2; i++) {
        rows = inputIntegerNumbers("Please enter the number of rows.",
                                   MAX_ROWS, 1);

        if (rows >= 1 && rows <= MAX_ROWS) {
            printf("\nSuccessful input of rows! (%d/4)\n"
                   "rows: %d\n\n", ++countOfSuccessfulInputs, rows);
        }

        cols = inputIntegerNumbers("Please enter the number of columns.",
                                   MAX_COLS, 1);

        if (cols >= 1 && cols <= MAX_COLS) {
            printf("\nSuccessful input of rows! (%d/4)\n"
                   "columns: %d\n\n", ++countOfSuccessfulInputs, cols);
        }
    }
    if (countOfSuccessfulInputs == 4) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
    rows = 12;
    cols = 8;
}

void testInputCountOfStudents(void) {
    printf("\nTest cases: Input of the count of students & No half students accepted\n"
           "Please follow the instructions and try the input. After two correct "
           "inputs, the test is over.\nThe test uses the last entered rows and columns or 12x8, if the"
           " that test failed.\n");

    countOfSuccessfulInputs = 0;
    for (int i = 0; i < 2; i++) {
        unsigned short productOfRC = rows * cols;
        countOfStudentsToAssign = inputIntegerNumbers("Please enter the count of students "
                                                      "taking the exam.", productOfRC,
                                                      1);

        countOfOptions = 1;
        if (countOfStudentsToAssign <= (productOfRC / 2 + (productOfRC & 1))) {
            countOfOptions++;
        }
        if (countOfStudentsToAssign <= (rows / 2 + (rows & 1)) * (cols / 2 + (cols & 1))) {
            countOfOptions++;
        }

        printf("With the given number of the students taking the exam (%d), the possible seating patterns "
               "are the following:\n- unsafe (100 % room saturation)\n", countOfStudentsToAssign);
        if (countOfOptions >= 2) {
            printf("- chessboard (50 % room saturation)\n");
        }
        if (countOfOptions == 3) {
            printf("- far spaced (25 % room saturation)\n");
        }

        if (countOfStudentsToAssign >= 1 && countOfStudentsToAssign <= productOfRC) {
            printf("\nSuccessful input of count of students taking the exam! (%d/2)\n"
                   "count of students taking the exam: %d\n\n", ++countOfSuccessfulInputs, countOfStudentsToAssign);
        }
    }

    if (countOfSuccessfulInputs == 2) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
    countOfStudentsToAssign = 1;
}

void testInputSeatingArrangementPattern(void) {
    printf("\nTest cases: Seating arrangement pattern & Invalid pattern\n"
           "Please follow the instructions and try the input. After three correct "
           "inputs, the test is over.\nThe test uses the last entered rows and columns or 12x8, if the"
           " that test failed.\nThe test uses the last entered number of students taking the exam, or 1, "
           "if that test failed.\n");

    countOfSuccessfulInputs = 0;
    for (int i = 0; i < 3; i++) {
        inputSeatingArrangement(countOfOptions);

        if (seatingArrangement == UNSAFE || seatingArrangement == CHESSBOARD
            || seatingArrangement == FAR_SPACED) {
            printf("\nSuccessful input of count of students taking the exam! (%d/3)\n"
                   "the selected seating arrangement pattern: %c\n\n", ++countOfSuccessfulInputs, seatingArrangement);
        }
    }

    if (countOfSuccessfulInputs == 3) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
    seatingArrangement = UNSAFE;
}

void testClassroomGeneratePrint(classroom *Classroom) {
    printf("\nTest case: Displaying the seating arrangement\n"
           "This test is about generating and printing a classroom. If a classroom"
           " with the last entered parameters (or if those tests failed, 12x8xUNSAFE) shows up, it worked.\n");

    generateSeatingArrangement(Classroom);
    classroomPrintWhole(Classroom, rows, cols, 0);
}

void testSeatAssignment(classroom *Classroom) {
    printf("\nTest cases: Seat assignment & Unavailable seat & Student ID already assigned\n"
           "To perform this test, please follow the instructions and try the input. One valid student ID "
           "must be entered right. After that, you can try to assign it again. You can try to assign the same "
           "student twice or assign a new student to an available or an unavailable seat. "
           "The test will be done with a classroom having 12 rows, 8 columns and chessboard pattern. "
           "The test finishes after you assigned two student or assigned one and tried to reassign them. "
           "During the test, the classroom will be printed multiple times to show you what happens.\n");
    rows = 12;
    cols = 8;
    seatingArrangement = CHESSBOARD;
    unsigned short countOfAssignedStudents = 0, maxStudents = generateSeatingArrangement(Classroom);
    classroomPrintWhole(Classroom, rows, cols, 0);

    caseAssign(Classroom, &countOfAssignedStudents, maxStudents);
    classroomPrintWhole(Classroom, rows, cols, 0);

    caseAssign(Classroom, &countOfAssignedStudents, maxStudents);
    classroomPrintWhole(Classroom, rows, cols, 0);
}

void testFullClassroom(classroom *Classroom) {
    printf("\nTest case: Social distancing norms upheld\nTo perform this test,"
           "a classroom has been created with two rows, three columns and far spaced pattern. "
           "Two students will be assigned by the system, and it will try to assign a new one. If a message "
           "pops up saying that the classroom is full, it works.\n");
    rows = 2;
    cols = 3;
    seatingArrangement = FAR_SPACED;

    unsigned short maxStudents = generateSeatingArrangement(Classroom), countOfAssignedStudents = 0;
    classroomPrintWhole(Classroom, rows, cols, 0);

    assignSeat(Classroom, "ic22b039", 0, 1, 1, &countOfAssignedStudents);
    classroomPrintWhole(Classroom, rows, cols, 0);

    assignSeat(Classroom, "ic22b112", 2, 1, 3, &countOfAssignedStudents);
    classroomPrintWhole(Classroom, rows, cols, 0);

    caseAssign(Classroom, &countOfAssignedStudents, maxStudents);
    classroomPrintWhole(Classroom, rows, cols, 0);
}

void testDirectNeighbors(classroom *Classroom) {
    printf("\nTest cases: Neighbors are checkable & Student not found\nFor this test,"
           "the previous classroom will be used. Please follow the instructions and try the input. "
           "The test finishes after your second attempt. If the program doesn't find anything for "
           "non-assigned students, but it finds something for assigned ones, the test passes.\n");

    classroomPrintWhole(Classroom, rows, cols, 0);
    for (int i = 0; i < 2; i++) {
        caseNeighbors(Classroom, 1);
    }
}

void testIndirectNeighbors(classroom *Classroom) {
    printf("\nTest cases: Displaying the indirect neighbors & Student not found 2\nThe same will happen "
           "as before but indirect neighbors will be looked for too. The test passes if they will be printed for "
           "the assigned but not for the non-assigned students.\n");

    classroomPrintWhole(Classroom, rows, cols, 0);
    for (int i = 0; i < 2; i++) {
        caseNeighbors(Classroom, 2);
    }
}

void testClearStdinBuffer() {
    // Test case: Test clearing the input buffer
    // Assuming the input buffer has 5 characters: "Hello"
    // The function should clear the buffer and return 5
    printf("\nThis is a test for clearing the input buffer. Please type five characters, "
           "without new lines or whitespaces at the beginning and the end. "
           "The test succeeds if the program finds five characters in the buffer.\n");
    int bufferedCharacters = clearStdinBuffer();
    printf("\n%d\n", bufferedCharacters);

    if (bufferedCharacters == 5) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
}

void testInputIntegerNumbers() {
    // Test case: Test inputIntegerNumbers function
    // Assuming the user enters a number between 1 and 10
    // The function should return the entered number
    printf("\nThis is a test for integer number input.\n");
    int result = inputIntegerNumbers("Please enter a number.", 10, 1);
    if (result >= 1 && result <= 10) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
}

void testGenerateSeatingArrangement(classroom *Classroom) {
    // Test case: Test generateSeatingArrangement function
    // For this test we assume the user enters 5 for rows as well as columns and wants a Chessboard-Layout
    // The function should return the number of students that can sit in the classroom
    printf("\nThis test tries to generate a 5x5 classroom with chessboard pattern. It passes if "
           "the return value (the maximal assignable students) is 13.\n");

    rows = 5;
    cols = 5;
    seatingArrangement = CHESSBOARD;

    unsigned short result = 13;
    if (result == generateSeatingArrangement(Classroom)) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
}

void testCalcSeat() {
    printf("\nThis test calculates a seat index from the given row (6) and column (5) in the "
           "classroom with the determined dimension (12x8). If the result is 44, it works.\n");
    rows = 12;
    cols = 8;
    seatingArrangement = UNSAFE;

    printf("\n%d\n", calcSeat(6, 5));
    if (calcSeat(6, 5) == 44) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
}

void testCalcRowsCols() {
    printf("\nThis test calculates the rows and the columns for the same 12x8 for the seat with "
           "the index 68. If the row is 9 and the columns is 5, it works.\n");

    unsigned short row, col;

    calcRowsCols(68, &row, &col);

    printf("\n%d %d\n", row, col);
    if (row == 9 && col == 5) {
        printf(SUCCESSFUL);
        return;
    }
    printf(FAILED);
}

void testDisplayMenu() {
    printf("\nThis test is for displaying the menu. If the menu is displayed, it works.\n");
    displayMenu();
}

int main() {
    // Run the unit tests
    printf("TESTS\n");

    //Generating seating chart
    testInputRowsAndColumns();

    testInputCountOfStudents();

    testInputSeatingArrangementPattern();

    classroom *Classroom = classroomCreate();
    testClassroomGeneratePrint(Classroom);
    classroomDelete(Classroom);

    //Seat assignment
    Classroom = classroomCreate();
    testSeatAssignment(Classroom);
    classroomDelete(Classroom);

    //Social distancing
    Classroom = classroomCreate();
    testFullClassroom(Classroom);

    //Direct neighbors
    testDirectNeighbors(Classroom);

    //Indirect neighbors
    testIndirectNeighbors(Classroom);
    classroomDelete(Classroom);

    //Other tests
    testClearStdinBuffer();

    testInputIntegerNumbers();

    Classroom = classroomCreate();
    testGenerateSeatingArrangement(Classroom);
    classroomDelete(Classroom);

    testCalcSeat();

    testCalcRowsCols();

    testDisplayMenu();


    return 0;
}
