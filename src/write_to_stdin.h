//
// Created by magoc on 6/13/2023.
//

#ifndef PROJEKT_GRUPPE19_WRITE_TO_STDIN_H
#define PROJEKT_GRUPPE19_WRITE_TO_STDIN_H

#include <stdio.h>

void writeToStdin(char *filePath, char *yourInput) {
    FILE *out = fopen(filePath, "a");
    fwrite(yourInput, 1, sizeof(yourInput), out);
    fclose(out);
    FILE *in = freopen(filePath, "r", stdin);
    if(!in) printf("Error!");
}

#endif //PROJEKT_GRUPPE19_WRITE_TO_STDIN_H
