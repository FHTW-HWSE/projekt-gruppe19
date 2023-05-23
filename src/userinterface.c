#include stdio.h

#define MAX_ROWS 20
#define MAX_COLS 20

    int option;
    do {
        displayMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Please enter the number of rows: ");
                scanf("%d", &rows);
                printf("Please enter the number of columns: ");
                scanf("%d", &cols);
                generateSeatingArrangement(rows, cols, seatingArrangement);
                printf("Seats arranged.\n");
                break;
            case 2: {
                if (rows == 0 || cols == 0) {
                    printf("Seats have to be arranged first.\n");
                    break;
                }
                Student student;
                printf("Please enter student ID: ");
                scanf("%s", student.studentID);
                printf("Please enter the row of the seat ");
                scanf("%d", &student.row);
                printf("Please enter the column of the seat ");
                scanf("%d", &student.col);

                if (student.row < 0 || student.row >= rows || student.col < 0 || student.col >= cols) {
                    printf("invalid seat position.\n");
                    break;
                }

                assignSeat(&student, seatingArrangement);
                printf("seat already taken.\n");
                break;
            }
            case 3:
                if (rows == 0 || cols == 0) {
                    printf("Seat arrangment has to be generated first.\n");
                    break;
                }
                if (file == NULL) {
                    printf("error opening file.");
                    break;
                }
                Student student;
                printf("Please enter student ID: ");
                scanf("%s", student.studentID);
                printf("Please enter row of the seat: ");
                scanf("%d", &student.row);
                printf("Please enter column of the seat: ");
                scanf("%d", &student.col);

                if (student.row < 0 || student.row >= rows || student.col < 0 || student.col >= cols) {
                    printf("invalid seat position.\n");
                    break;
                }

                saveStudentInfo(&student, file);
                printf("Seat position and student ID saved.\n");
                break;
            case 4: {
                if (rows == 0 || cols == 0) {
                    printf("Seat arrangment has to be generated first.\n");
                    break;
                }
                if (file == NULL) {
                    printf("error opening file.");
                    break;
                }

                char searchID[10];
                printf("Please enter student ID: ");
                scanf("%s", searchID);

                //Look for student ID in file and get position

                Student searchStudent;
                // Beispielannahme: Die Position des gesuchten Studenten ist searchStudent.row und searchStudent.col

                searchStudent.row = student.row;
                searchStudent.col = student.col;
                getDirectNeighbors(&searchStudent, rows, cols);
                break;
            }
            case 5: {
                if (rows == 0 || cols == 0) {
                    printf("Seat arrangment has to be generated first.\n");
                    break;
                }
                if (file == NULL) {
                    printf("error opening file.");
                    break;
                }

                char searchID[10];
                printf("Please enter student ID: ");
                scanf("%s", searchID);

                //Look for student ID in file and get position

                Student searchStudent;
                // Beispielannahme: Die Position des gesuchten Studenten ist searchStudent.row und searchStudent.col

                searchStudent.row = student.row;
                searchStudent.col = student.col;
                getIndirectNeighbors(&searchStudent, rows, cols);
                break;
            }
            case 6:
                printf("Program is exiting.\n");
                break;
            default:
                printf("Invalid option. Choose again.\n");
        }
    } while (option != 6);

