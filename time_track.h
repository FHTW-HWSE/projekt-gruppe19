//
// Created by mark on 4/25/23.
//
#include <time.h>
#ifndef PROJEKT_GRUPPE19_TIME_TRACK_H
#define PROJEKT_GRUPPE19_TIME_TRACK_H

void time_function() {

    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char time_string[20];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

    return time_string;

}

#endif //PROJEKT_GRUPPE19_TIME_TRACK_H
