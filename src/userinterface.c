#include stdio.h

#define MAX_ROWS 20
#define MAX_COLS 20

    int option;
    do {
        displayMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Bitte geben Sie die Anzahl der Reihen ein: ");
                scanf("%d", &rows);
                printf("Bitte geben Sie die Anzahl der Spalten ein: ");
                scanf("%d", &cols);
                generateSeatingArrangement(rows, cols, seatingArrangement);
                printf("Belegungsmuster generiert.\n");
                break;
            case 2: {
                if (rows == 0 || cols == 0) {
                    printf("Belegungsmuster muss zuerst generiert werden.\n");
                    break;
                }
                Student student;
                printf("Bitte geben Sie die Studierendenkennung ein: ");
                scanf("%s", student.studentID);
                printf("Bitte geben Sie die Reihe des Sitzplatzes ein: ");
                scanf("%d", &student.row);
                printf("Bitte geben Sie die Spalte des Sitzplatzes ein: ");
                scanf("%d", &student.col);

                if (student.row < 0 || student.row >= rows || student.col < 0 || student.col >= cols) {
                    printf("Ungültige Sitzplatzposition.\n");
                    break;
                }

                assignSeat(&student, seatingArrangement);
                printf("Sitzplatz vergeben.\n");
                break;
            }
            case 3:
                if (rows == 0 || cols == 0) {
                    printf("Belegungsmuster muss zuerst generiert werden.\n");
                    break;
                }
                if (file == NULL) {
                    printf("Fehler beim Öffnen der Datei.");
                    break;
                }
                Student student;
                printf("Bitte geben Sie die Studierendenkennung ein: ");
                scanf("%s", student.studentID);
                printf("Bitte geben Sie die Reihe des Sitzplatzes ein: ");
                scanf("%d", &student.row);
                printf("Bitte geben Sie die Spalte des Sitzplatzes ein: ");
                scanf("%d", &student.col);

                if (student.row < 0 || student.row >= rows || student.col < 0 || student.col >= cols) {
                    printf("Ungültige Sitzplatzposition.\n");
                    break;
                }

                saveStudentInfo(&student, file);
                printf("Studierendenkennung und Sitzplatz abgespeichert.\n");
                break;
            case 4: {
                if (rows == 0 || cols == 0) {
                    printf("Belegungsmuster muss zuerst generiert werden.\n");
                    break;
                }
                if (file == NULL) {
                    printf("Fehler beim Öffnen der Datei.");
                    break;
                }

                char searchID[10];
                printf("Bitte geben Sie die Studierendenkennung ein: ");
                scanf("%s", searchID);

                // Nach Studierendenkennung in der Datei suchen und die Position abrufen

                Student searchStudent;
                // Beispielannahme: Die Position des gesuchten Studenten ist searchStudent.row und searchStudent.col

                searchStudent.row = student.row;
                searchStudent.col = student.col;
                getDirectNeighbors(&searchStudent, rows, cols);
                break;
            }
            case 5: {
                if (rows == 0 || cols == 0) {
                    printf("Belegungsmuster muss zuerst generiert werden.\n");
                    break;
                }
                if (file == NULL) {
                    printf("Fehler beim Öffnen der Datei.");
                    break;
                }

                char searchID[10];
                printf("Bitte geben Sie die Studierendenkennung ein: ");
                scanf("%s", searchID);

                // Nach Studierendenkennung in der Datei suchen und die Position abrufen

                Student searchStudent;
                // Beispielannahme: Die Position des gesuchten Studenten ist searchStudent.row und searchStudent.col

                searchStudent.row = student.row;
                searchStudent.col = student.col;
                getIndirectNeighbors(&searchStudent, rows, cols);
                break;
            }
            case 6:
                printf("Programm wird beendet.\n");
                break;
            default:
                printf("Ungültige Option. Bitte wählen Sie erneut.\n");
        }
    } while (option != 6);

