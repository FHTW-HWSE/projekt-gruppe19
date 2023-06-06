#include "time_track.h"

void logFile(const char *log_pfad, char place_ID, char student_ID, char assignment_status ){

    char write_time[20] = {};
    char add_or_remove;

    add_or_remove = assignment_status;

    write_time = time_function();
    FILE *file = fopen(log_path, "a");
	if (file == NULL) {
		fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
		return;
	}

    if (add_or_remove == NULL) {

        fprintf(file, "%c %s\n", write_time, place_ID, student_ID);
    }

    if (add_or_remove == "Enter"){

        fprintf(file, "Der Student mit der Nummer %c hat um %c den Sitzplatz %s bezogen.\n", student_ID, write_time, place_ID);

        fprintf(file, "Die Nachbarn des Studenten mit der Nummer %c am Sitzplatz %c sind um %s ---------Nachbarn-------", student_ID, place_ID, write_time);

    }

    if (add_or_remove == "Remove"){

        fprintf(file, "Der Student mit der Nummer %c hat um %c den Sitzplatz %s verlassen.\n", student_ID, write_time, place_ID);

        fprintf(file, "Die Nachbarn des Studenten mit der Nummer %c am Sitzplatz %c sind um %s ---------Nachbarn-------", student_ID, place_ID, write_time);

    }
	fclose(file);
}

/*
 * Zeit tracken wann das Programm gestartet wurde
 * aktuelle Logfile enthält alle Einträge die während der aktuellen Sitzung erstellt wurden
 *
 * Diese Einträge können abgerufen werden und in einer geordneten struktur ausgegeben werden
 */


void print_Seating_Chart_to_log_Array(const char *log_path, char seatingChart[][][], int rows, int columns, int inhalt) {

    char write_time[20] = {};

    write_time = time_function();

    FILE *file = fopen(log_path/Sitzplan.txt, "a");

    if (file == NULL) {
        fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
        return;
    }

    fprintf("###########################################################################\n");

    fprintf("Um %s war der Raum mit wie folgt belegt:\n", write_time);


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            for (int k = 0; k < inhalt; k++) {
                fprintf("|| %c | %c | %c ||\n", i, j, k);
            }
        }
    }

    fprintf("###########################################################################\n");

    fclose(file);

    return 0;
}


void print_Seating_Chart_to_log_List(const char *log_path,  )





    /*
     * gibt den derzeitigen Sitzplan aus und speichert diesen zusätzlich in die eine Datei "Sitzplan" mit der aktuellen Zeit
     */



}





2

parcour
