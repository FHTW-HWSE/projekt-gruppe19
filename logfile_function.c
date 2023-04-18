void logFile(const char *log_pfad, char data){

    FILE *file = fopen(log_pfad, "a");
	if (file == NULL) {
		fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
		return;
	}

	fprintf(file, "%s\n", data);

	fclose(file);
}


void time_track(const char *time_pfad, char *data) {

	time_t current_time = time(NULL);
	struct tm *time_info = localtime(&current_time);
	char time_string[20];
	strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

	FILE *file = fopen(time_pfad, "a");
	if (file == NULL) {
		fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n",
				time_pfad);
		return;
	}

	fprintf(file, "Um: %s\nWurde der Buchstabe: %s\t eingegeben\n\n",
			time_string, data);

	fclose(file);
}
