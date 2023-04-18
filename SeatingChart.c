typedef struct chartstruct {
    char seatingChart[20][20];
} chartstruct;
chartstruct seatingchart (int rows, int cols, int numStudents);


chartstruct seatingchart (int rows, int cols, int numStudents) {
    chartstruct chart;
    int maxSeats = rows * cols;

    if (rows > 20 || cols > 20) {
        printf("Error: Nicht mehr als 20 Spalten/Reihen möglich.\n");
    }
    if (numStudents > (maxSeats / 2)) { //divide by 2 to guarantee the minimal distance
        printf("Error: Nicht genug Sitzplätze.\n");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            chart.seatingChart[i][j] = '-';
        }
    }
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (count == numStudents) {
                break;
            }

            if ((i + j) % 2 == 0 && chart.seatingChart[i][j] == '-') {
                chart.seatingChart[i][j] = 'S';
                count++;
            }
        }
    }
    return chart;
}