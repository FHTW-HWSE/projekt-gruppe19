void logFile(const char *log_pfad, char place_ID, char student_ID, char assignment_status ){

    char write_time[20];
    char add_or_remove;

    add_remove = assignment_status;

    write_time = time_function;
    FILE *file = fopen(log_pfad, "a");
	if (file == NULL) {
		fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
		return;
	}

    if (add_or_remove == NULL) {

        fprintf(file, "%c %s\n", write_time, place_ID, student_ID);
    }

    if (add_remove == "ENTER"){

        fprintf(file, "Der Student mit der Nummer %c hat um %c den Sitzplatz %s bezogen.\n", student_ID, write_time, place_ID);4

        fprintf(file, "Die Nachbarn des Studenten mit der Nummer %c am Sitzplatz %c sind um %s ---------Nachbarn-------", student_ID, place_ID, write_time);

    }

    if (add_remove == "EXIT"){

        fprintf(file, "Der Student mit der Nummer %c hat um %c den Sitzplatz %s verlassen.\n", student_ID, write_time, place_ID);

        fprintf(file, "Die Nachbarn des Studenten mit der Nummer %c am Sitzplatz %c sind um %s ---------Nachbarn-------", student_ID, place_ID, write_time);

    }
	fclose(file);
}

void time_function(){

    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char time_string[20];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

    return time_string;


}

/* void time_track(const char *time_pfad, char *place_ID, char Stud_ID) {

	time_t current_time = time(NULL);
	struct tm *time_info = localtime(&current_time);
	char time_string[20];
	strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

	FILE *file = fopen(time_pfad, "a");
	if (file == NULL) {
		fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", time_pfad);
		return;
	}

	fprintf(file, "Um: %s\nWurde der Platz %s an den Studenten mit der StudentID %s vergeben.\n\n", time_string, place_ID, Stud_ID);

	fclose(file);
}
*/
2