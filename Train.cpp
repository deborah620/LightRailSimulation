/*File: Train.cpp
**Name: Deborah Miller
**Email: d169@umbc.edu
**Section: 10/14
**Date: 10/25
**Description: the .cpp for the Train.h header file
        includes 11 functions to help run proj3, 
        (builds the train and adds and deletes passengers)
*/

#include "Train.h"

//Train()
//train class constructor
Train::Train(Route* route){
  m_route = route;
  m_totalCars = 1;
  m_head = new Car(CAR_CAPACITY, m_totalCars);

}

//~Train()
//train class destructor
Train::~Train(){
  Car* current = m_head;

  //dealocates and removes every passenger
  while (current) {
    for (unsigned int i = 0; i < current->m_passengers.size(); i++) {
      delete current->m_passengers.at(i);
    }
    for (unsigned int i = 0; i < current->m_passengers.size(); i++) {
      current->m_passengers.erase(current->m_passengers.begin() + i);
    }
    current = current->m_next;
  }

  //dealocate every car
  current = m_head;
  while (current) {
    m_head = current;
    current = current->m_next;
    delete m_head;
  }
  
  m_head = nullptr;
  m_totalCars = 0;
  m_route = nullptr;
  
}

//AddCar()
//if the train is full,
//adds a car node to the back of the train
void Train::AddCar(){
  Car *current = m_head;
  while(current->m_next != nullptr) {
    current = current->m_next;
  }
  m_totalCars++;
  current->m_next = new Car(CAR_CAPACITY, m_totalCars);

}

//TrainStatus()
//displays the number of passenger in every car
//also displays this stop and the next stop
void Train::TrainStatus(){  
  cout << "Number of cars: " << m_totalCars << endl;

  Car *current = m_head;

  //displays number of passengers in which car
  while(current) {
    cout << "Car " << current->m_carNumber << ": " << "Number of passengers: " \
	 << current->m_passengers.size() << endl;
    current = current->m_next;
  }

  cout << "Current Stop: " << m_route->GetCurrentStop()->GetName() <<\
    " (" << m_route->GetCurrentStop()->GetNumber() << ")" << endl;

  //if the next stop is the last stop, it'll inform the user
  if(m_route->GetCurrentStop()->GetNextStop() != nullptr)
    cout << "Next Stop is: " <<  m_route->GetCurrentStop()->GetNextStop()->GetName() <<	\
    " (" <<  m_route->GetCurrentStop()->GetNextStop()->GetNumber() << ")" << endl;
  else
    cout << "End of the line" << endl;
}

//LoadPassengers(string)
//loads passengers from a given file
void Train::LoadPassengers(string passName){
  string fName;
  string lName;
  string fullName;
  string age;
  string start;
  string destination;
  int count = 0;
  ifstream passengers(passName);
  
  while(getline(passengers, fName, ',')){
    getline(passengers, lName, ',');
    fullName = fName + " " + lName;
    getline(passengers, age, ',');
    getline(passengers, start, ',');
    getline(passengers, destination);

    //if this is where the passenger boards, they get added to a car
    if(start == m_route->GetCurrentStop()->GetName()){
      Passenger* newPassenger = new Passenger(fullName, stoi(age), start, destination);
      BoardPassenger(newPassenger);
      count++;

    }
  }
  passengers.close();
  
  cout << "Boarded " << count << " passengers" << endl;
  cout << endl;
}

//BoardPassenger(Passenger)
//"boards" passenger to an empty spot in a car
//checking the car capacity from front to back
//if the train is full, it calls AddCar()
void Train::BoardPassenger(Passenger* newPassenger){
  Car* current = m_head;
  bool keepGoing = true;

  while(current && keepGoing) {

    if(current->IsFull()){
      if(IsTrainFull()){
	AddCar();
      }
      current = current->m_next;
    }
    else{
      current->AddPassenger(newPassenger);
      keepGoing = false;
    }
  }
  
  cout << newPassenger->GetName() << " Boards the Train (Destination: " <<\
    newPassenger->GetFinalDestination() << ")" << endl;

}

//DisembarkPassengers()
//when it's the passengers stop, they "disembark"
//(dealocated and erased fom the vector)
void Train::DisembarkPassengers() {
  Car *current = m_head;
  int count = 0;
  
  while (current) {
    
    for (unsigned int i = 0; i < current->m_passengers.size(); i++) {

      if (current->m_passengers.at(i)->GetFinalDestination() == m_route->GetCurrentStop()->GetName()) {

	cout << current->m_passengers.at(i)->GetName() << " Disembark the Train (Destination: " << \
	  current->m_passengers.at(i)->GetFinalDestination() << ")" << endl;
	
	delete current->m_passengers.at(i);
	current->m_passengers.erase(current->m_passengers.begin() + i);
	count++;

	//if the passenger is removed, i has to minus by one so the next passenger doesn't get skipped
	i--;
      }
    }

    current = current->m_next;

  }

  cout << count << " passengers disembarked" << endl;
  cout << endl;

}

//TravelToNextStop()
//moves the train to the next stop on the route
//if it's the last stop on the line, it lets the user know
void Train::TravelToNextStop(){
  if(m_route->GetCurrentStop()->GetNextStop() == nullptr) {
    cout << "You're at the end of line" << endl;
    cout << "Why don't you turn this train around" << endl;
    cout << endl;
  }

  else{
    m_route->SetCurrentStop(m_route->GetCurrentStop()->GetNextStop());
    m_route->PrintRouteDetails();

  }
}

//TurnTrainAround()
//calls ReverseRoute() if the train is at the last stop on the route
void Train::TurnTrainAround(){
  if(m_route->GetCurrentStop()->GetNextStop() != nullptr)
    cout << "You can only reverse the route when at the end of the route" << endl;

  else
    m_route->ReverseRoute();
}

//IsTrainFull()
//return true if the train is full
//(all cars have 16 passengers)
bool Train::IsTrainFull(){
  Car* current = m_head;

  while(current) {

    if(current->IsFull())
      current = current->m_next;

    else{
      return false;  
    }
  }
 return true;
}

