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
    static int seatNumber;
    int row;
    int column;
    struct linD *nE;
} lisD;

lisD *fE = NULL;
lisD *lE = NULL;

void main(void)
{
    lisD seatingChart;
}

void lisD_Add(lisD *list, char *studentID, int seatNumber, int row, int column)
{
    lisD *newE, *currentE;
    currentE = fE;
    newE = (lisD *) malloc(sizeof(lisD));
    
    if(!fE)
    {
        newE.nE = NULL;
        fE = newE;
        lE = newE;
        printf("first");
    }
}
