#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "classroom.h"

TEST_CASE("classroomCreate") {
    classroom* myClassroom = classroomCreate();
    REQUIRE(myClassroom != nullptr);
    // Add additional assertions if necessary
}

TEST_CASE("classroomAppendLastSeat") {
    classroom* myClassroom = classroomCreate();
    REQUIRE(myClassroom != nullptr);

    classroomAppendLastSeat(myClassroom, "12345678");
    REQUIRE(myClassroom->firstSeat != nullptr);
    REQUIRE(myClassroom->lastSeat != nullptr);
    REQUIRE(strcmp(myClassroom->firstSeat->student, "12345678") == 0);

    // Add additional assertions if necessary
}

TEST_CASE("classroomSearchStudAddr") {
    classroom* myClassroom = classroomCreate();
    REQUIRE(myClassroom != nullptr);

    classroomAppendLastSeat(myClassroom, "12345678");
    classroomAppendLastSeat(myClassroom, "87654321");

    seat* searchedSeat = classroomSearchStudAddr(myClassroom, "87654321");
    REQUIRE(searchedSeat != nullptr);
    REQUIRE(strcmp(searchedSeat->student, "87654321") == 0);

    // Add additional assertions if necessary
}

// Write similar test cases for other functions

TEST_CASE("classroomAssignStudent") {
    classroom* myClassroom = classroomCreate();
    REQUIRE(myClassroom != nullptr);

    classroomAppendLastSeat(myClassroom, "12345678");
    classroomAppendLastSeat(myClassroom, "87654321");

    char result1 = classroomAssignStudent(myClassroom, "99999999", 0);
    REQUIRE(result1 == 1);
    REQUIRE(strcmp(myClassroom->firstSeat->student, "99999999") == 0);

    char result2 = classroomAssignStudent(myClassroom, "00000000", 1);
    REQUIRE(result2 == -1); // Seat already occupied

    // Add additional assertions if necessary
}
