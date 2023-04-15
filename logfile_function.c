void logFile(const char *log_pfad, char data){

    FILE *file = fopen(log_pfad, "a");
	if (file == NULL) {
		fprintf(stderr, "Fehler, die Datei konnte nicht geöffnet werden %s\n", log_pfad);
		return;
	}

	fprintf(file, "%s\n", data);

	fclose(file);
}
