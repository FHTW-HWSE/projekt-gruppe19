#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void lisD_Add(char *studentID, int seatNumber, int row, int column);
void createSeatingChart(void);

typedef struct lisD
{
    static int value = 0;
    char studentID[9];
    int seatNumber;
    int row;
    int column;
    struct linD *nE;
} lisD;

lisD *fE = NULL;
lisD *lE = NULL;

void createSeatingChart(void)
{
    lisD seatingChart;
}

void lisD_Add(lisD *list, char *studentID, int seatNumber, int row, int column)
{
    strcpy(list.studentID, scanf());
}
