/*
*       __
*     <(o )___
* 	   ( ._> /
*       `---'
*/
#define TEST

#include "userinterface.c"

#include "write_to_stdin.h"

#define SUCCESSFUL "Test successfully passed!\n"


#define FAILED "Test failed!\n"

unsigned char countOfSuccessfulInputs;
unsigned short countOfStudentsToAssign;
unsigned char countOfOptions;
unsigned short maxStudents;
classroom *Classroom;

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

int main() {
    // Run the unit tests
    printf("TESTS\n");
    //Generating seating chart
    testInputRowsAndColumns();
    testInputCountOfStudents();
    testInputSeatingArrangementPattern();

    return 0;
}
