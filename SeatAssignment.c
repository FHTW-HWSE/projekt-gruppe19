#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

//*seatingChart: pointer to the seatingChart's [0][0] element. it is a
  //long long int, because it will store memory addresses, whose size is 8 B
//*studentID: pointer to the first character of the student's ID
int seatAssignment(long long int *seatingChart, char *studentID);

int seatAssignment(long long int *seatingChart, char *studentID)
{
	int i;
	int seatNumber = -1;
    
	//the for loop runs until 400, because that is the maximal count of seats
	for(i = 0; (*(seatingChart + i) != studentID) && i < 400; i++)
    {
		//if the student doesn't have a seat yet and the currently selected
          //seat isn't occupied
		if((seatNumber == -1) && (*(seatingChart + i) == 'S')) seatNumber = i;
    }
	//if the student is not assigned yet, the memory address of their ID's
	  //first character is assigned to the seat
	if(i == 400) *(seatingChart + seatNumber) = studentID;
	//if the student was already present in the database, the function returns
	  //with -1
    return seatNumber;
}
