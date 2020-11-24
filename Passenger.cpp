/*File: Passenger.cpp
**Name: Deborah Miller
**Email: d169@umbc.edu
**Section: 10/14
**Date: 10/25
**Description: the .cpp for the Passenger.h header file
        includes 3 functions to help run proj3, builds a new passenger
*/

#include "Passenger.h"

//Passenger(string, int, string, string)
//overloaded constructor
Passenger::Passenger(string full_name, int age, string start, string destination) {
  m_fullName = full_name;
  m_age = age;
  m_startLocation = start;
  m_finalDestination = destination;
}

//GetName()
//return the passengers full name
string Passenger::GetName() {
  return m_fullName;
}

//GetStartLocation()
//returns which stop the passenger boards
string Passenger::GetStartLocation() {
  return m_startLocation;
}

//GetFinalDestination()
//returns which stop the passenger disembarks
string Passenger::GetFinalDestination() {
  return m_finalDestination;
}
