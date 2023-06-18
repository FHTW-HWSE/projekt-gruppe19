# Projekt Gruppe 19
Hardwarenahe Softwareentwicklung 2

Sommersemester 2023
# Members
- Markus Genner (ic22b039)
- Laszlo Magocsi (ic22x001)
- Jakob Reinelt (ic22b112)
- Alexander Zink (ic22b118)

# Requirements

## Functional:

- A user interface must be implemented
- The seating chart is created according to the number of rows and columns entered by the user
- A seat is assigned when a student ID is entered
- A seat cannot be assigned to a student ID twice
- The student ID and the assigned seat is saved in a logfile
- The direct neighbours of a student can be recalled
- The indirect neighbours of a student can be recalled
- Logfiles are saved in a user defined path
- Logfiles contain the current time and date
- Logfiles need to be accessible even after the program is closed
- The program must compile and run on the predefined system (lecturer PC)
- The biggest room has a maximum of 20 rows and 20 columns, and can accept 400 persons at most, without taking social distancing into account.

## Non-functional requirements:

- Performance: The program must run quickly and efficiently.
- Scalability: The program should be able to handle a large number of requests. It should be able to scale up or down based on the demand. Maximum set as per functionals 400 persons (20x20).
- Reliability: The program should be reliable and able to handle errors or failures gracefully. It should be able to recover from errors and ensure that all allocated seats are properly assigned, and the same student ID cannot be entered twice.
- Usability: The program should be easy to use and user-friendly. The interface should be intuitive and simple, allowing users to navigate quickly and easily. The source code contains detailed documentation in German or English.
- Maintainability: The program should be easy to maintain and update. The code should be modular, well-documented, and designed to be easily modified or extended. (Use of GitHub)
- Compatibility: The program should be compatible with Linux and Windows.
- Availability: The program should be available 24/7 with minimal downtime or disruptions. (GitHub)




## Constraints (quality criteria):

- The program is written in C
- The program should be finished and presented at the given date of 13.06.2023
- No additional costs should arise when using the program 


# User stories and acceptance criteria

## **User Story: Generating seating chart**

As a professor, I want to be able to input the dimensions of the classroom and select a seating arrangement pattern, so that I can generate
a seating chart that ensures social distancing.

### Test cases:

- TEST CASE: Input of classroom dimensions
  - GIVEN: there should be an element in the user interface that receives data about the classroom
  - WHEN: the professor enters the room's count of rows and columns (correct values: [1:20], integer)
  - THEN: the program stores the data and proceeds to the input of the amount of examinated students

- TEST CASE: Incorrect values for dimension
  - GIVEN: the professor should be only able to enter positive numbers ([1:20], integer)
  - WHEN: the professor enters an incorrect number
  - THEN: the program gives back an error message and asks for a correct number (by telling the professor explicitly, what is correct ([1:20], integer))

- TEST CASE: Input of the count of students
  - GIVEN: the professor must be able to ensure that the students taking the exam will fit in the classroom
  - WHEN: the professor specifies a positive integer as the count of examinated students, after entering valid values for the classroom's dimensions
  - THEN: the program stores it and searches options to arrange the students in the room with the given dimensions

- TEST CASE: No half students accepted
  - GIVEN: for the count of students, only a positive integer can be entered
  - WHEN: something else is received from the professor as the count of students
  - THEN: the program gives back an error message, specifying the problem and the domain of valid numbers and waits for the professor to enter a new value

- TEST CASE: Displaying the seating arrangement pattern
  - GIVEN: the program should show how the earlier selected seating arrangement pattern would look like in reality in the classroom
  - WHEN: the seating arrangement pattern is generated in the program
  - THEN: the program displays the seating chart generated from the given count of rows and columns and based on the selected seating arrangement pattern

## **User Story: Indirect neighbours**

As a professor, I want to be able to view a list of all indirect neighbors of a particular student.


### Test cases:

- TEST CASE: Displaying the indirect neighbours
  - GIVEN: the professor must be able to query the indirect neighbours of a specific student
  - WHEN: the professor enters a student ID existing in the current exam's database
  - THEN: the program gives back the list of the specified student's indirect neighbours

- TEST CASE: Student not found
  - GIVEN: the program should handle if information the indirect neighbours of a non-examinated students are queried
  - WHEN: the professor enters a student name or ID not existing in the current exam's database
  - THEN: the program gives back and error message

## **User Story: Direct neighbours**

As a professor, I want to be able to view a list of all direct neighbors of a particular student.

### Test cases:

- TEST CASE: Neighbors are checkable
  - GIVEN: a Professor wants to see the direct neighbors of a student
  - WHEN: the Student ID is entered into the system
  - THEN: a list of direct neighbors is put out

- TEST CASE: Student not found
  - GIVEN: the program should handle if information the indirect neighbours of a non-examinated students are queried
  - WHEN: the professor enters a student name or ID not existing in the current exam's database
  - THEN: the program gives back and error message

## **User Story: Seat Assignment**

As a professor, I want to be able to assign a specific seat for every student.

### Test cases:

- Test Case: Seat assignment
  - GIVEN: a professor wants to assign an available seat to a student that is not yet assigned
  - WHEN: the non-assigned student ID and the available seat's row and column are entered
  - THEN: a seat is assigned

- Test Case: Unavailable seat
  - GIVEN: a professor wants to assign an unavailable seat to a student that is not yet assigned
  - WHEN: the non-assigned student ID and the unavailable seat's row and column are entered
  - THEN: an error message will be put out

- Test Case: Student ID already assigned
  - GIVEN: a professor wants to assign a seat to a student that is already assigned
  - WHEN: the assigned student ID is entered
  - THEN: an error message will be put out

## **User Story: Social distancing**

As a professor, I want to ensure that the social distancing regulations are taken into account when assigning a seat.

- Test Case: Social distacing norms upheld
  - GIVEN: the professor can't assign a seat in a full classroom
  - WHEN: the professor wants to assign a seat, but the room is already full
  - THEN: an error message will be put out informing the professor that new people cannot be added
