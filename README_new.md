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
- A seat cannot be assigned with a student ID twice
- The student ID and the assigned seat is saved in a logfile
- The direct neighbours of a student can be recalled
- The indirect neighbours of a student can be recalled
- Logfiles are saved in a user defined path
- Logfiles contain the current time and date
- Logfiles are saved in a common file format
- Logfiles need to be accessible even after the program is closed
- Data in a source file can not be changed after each use (read only)
- The program must compile and run on the predefined system (lecturer PC)
- The biggest room has a maximum of 20 rows x 20 columns without taking social distancing in account respectively 400 persons.

## Non-functional requirements:

- Performance: The program must run quickly and efficiently.
- Scalability: The program should be able to handle a large number of requests. It should be able to scale up or down based on the demand. Maximum set as per functionals 400 persons 20x20.
- Reliability: The program should be reliable and able to handle errors or failures gracefully. It should be able to recover from errors and ensure that all allocated seats are properly assigned, and the same student ID cannot be entered twice.
- Security: The program should ensure the security and privacy of the data. It should have proper access controls and authentication mechanisms to prevent unauthorized access or manipulation of the data.
- Usability: The program should be easy to use and user-friendly. The interface should be intuitive and simple, allowing users to navigate quickly and easily. The source code contains detailed documentation in German or English.
- Maintainability: The program should be easy to maintain and update. The code should be modular, well-documented, and designed to be easily modified or extended. (Use of GitHub)
- Compatibility: The program should be compatible with Linux and Windows.
- Availability: The program should be available 24/7 with minimal downtime or disruptions. It should have a robust backup and disaster recovery plan to ensure that it can quickly recover from any outages or failures. (GitHub)




## Constraints (quality criteria):

- The program is written in C
- The program should be finished and handed in at the given deadline of 13.06.2023
- No additional costs should arise when using the program 
- A student ID can not be entered twice in the same session


# User stories and acceptance criteria

### **User Story 1**

As a student, I want to be able to input my student ID and be assigned a seat in the classroom, so that I can know where to sit during 
in-person exams and feel safe in my designated seat.

### Acceptance criteria US1

-	The program must allow students to input their student ID and receive an assigned seat.
-	The assigned seat must be recorded and saved in the system.
-	The assigned seat must be displayed on the seating chart.
-	The assigned seat should be taking any social distancing requirements into account.


### **User Story 2**

As a professor, I want to be able to input the dimensions of the classroom and select a seating arrangement pattern, so that I can generate
a seating chart that ensures social distancing.

### Acceptance criteria US2

-	The program must allow professors to input the dimensions of the classroom and select a seating arrangement pattern.
-	The seating arrangement pattern must be generated and displayed on the seating chart.
-	The program must take into account social distancing guidelines when generating the seating chart.
-	The program must ensure that each student has a designated seat.


### User Story 3

As a professor, I want to be able to view the names of direct neighbors during an exam, so that I can easily identify who is sitting next to 
each other.

### Acceptance criteria US3

-	The program must allow professors to view the names of direct neighbors during an exam.
-	The names of the direct neighbors must be displayed on the seating chart for easy reference.
-	The program must allow professors to input a student's name or ID and generate a list of their direct neighbors.
-	The program must ensure that the names of the direct neighbors are accurate and up-to-date.


### **User Story 4**

As a professor, I want to be able to view a list of all indirect neighbors of a particular student.

  ### Acceptance criteria US4

-	The program must allow professors to input a student's name or ID and generate a list of their indirect neighbors.
-	The list of indirect neighbors must be accurate and up-to-date.

# Test cases

### Test Case 1

Input: Student ID: 123456

Expected Output:

-	A seat is assigned and recorded in the system
-	The assigned seat is saved in a logfile
-	The assigned seat complies to social distancing requirements
-	The direct neighbours’ names of student ID 987654 are displayed on the seating chart and saved in a logfile
-	The indirect neighbours’ names of student ID 987654 are displayed and saved in a logfile
-	If the neighbour changes, the new neighbour will also be displayed and saved in the same logfile

### Test Case 2

Input: rows and columns

Expected Output:

-	A seating chart is generated and available seats are displayed.
-	The seating chart complies to social distancing guidelines.
-	Each seat can be assigned to a student
-	The arrangement of the seating chart is saved in a logfile


### Test Case 3

Input: student name: Jürgen Brenner

Expected Output:

-	The direct neighbours’ names of Jürgen Brenner are displayed on the seating chart.
-	The indirect neighbours’ names of Jürgen Brenner are displayed.
-	The direct neighbours’ names are accurate and up to date.


### Test Case 4

Input: file path

Expected Output:

-	A new logfile is created in the given path
-	If the path is unavailable the system reads back an error
-	The logfile is saved as read only after the program is closed 
