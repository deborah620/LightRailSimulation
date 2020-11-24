/*File: Route.cpp
**Name: Deborah Miller
**Email: d169@umbc.edu
**Section: 10/14
**Date: 10/25
**Description: the .cpp for the Route.h header file
        includes 8 functions to help run proj3, builds a new route
*/

#include "Route.h"

//Route()
//constructor
Route::Route(){
  m_head = nullptr;
  m_tail = nullptr;
  m_currentStop = nullptr;
  m_totalStops = 0;
}

//~Route()
//destructor
Route::~Route(){
  //deallocates all the stops
  Stop* current = m_head;
  while (m_head) {
    m_head = m_head->GetNextStop();
    delete current;
    current = m_head;
  }
  
  delete m_tail;
  delete m_head;
  m_currentStop = nullptr;
  m_totalStops = 0;
}

//LoadRoute(string)
//loads the route file
//adds a Stop node for every stop on the route
void Route::LoadRoute(string routeFile){
  string name;
  string number;
  ifstream routes(routeFile);

  while(getline(routes, name, ',')){
    getline(routes, number);
    m_totalStops ++;
    AddStop(name, stoi(number));
  }
  routes.close();
    
  m_currentStop = m_head;

  cout << "Route loaded with " << m_totalStops << " stops" << endl;
}

//AddStop(string, int)
//adds a Stop node (containing a name and what number route)
//to the end of the route
void Route::AddStop(string stop_name, int stop_number){
  //head and tail initially
  if(m_head == nullptr) {
    m_head = new Stop(stop_name, stop_number);
    m_tail = new Stop(stop_name, stop_number);
  }
  
  else {
    //middle
    Stop* temp = new Stop(stop_name, stop_number);
    Stop *current = m_head;
    temp->SetNextStop(nullptr);
    
    while(current->GetNextStop() != m_tail->GetNextStop()) {
      current = current->GetNextStop();
    }
    current->SetNextStop(temp);

    //deallocate and reset tail
    delete m_tail;
    m_tail = new Stop(temp->GetName(), temp->GetNumber());
  }

}

//PrintRouteDetails()
//prints out the upcoming stop
void Route::PrintRouteDetails(){
  cout << "Arriving at " << m_currentStop->GetName() << endl;
}

//GetCurrentStop()
//return the current stop
Stop* Route::GetCurrentStop(){
  return m_currentStop;
}

//SetCurrentStop(Stop)
//updates m_currentStop to the current stop
void Route::SetCurrentStop(Stop* current_stop){
  m_currentStop = current_stop;
}

//ReverseRoute()
//turns around the train, reverses the route
void Route::ReverseRoute(){
  Stop* current = m_head;
  int counter = 1;

  //adds each Stop on the current route to the front of the route
  while(current){
    Stop* reverse = new Stop(current->GetName(), (current->GetNumber() + (m_totalStops - counter)));
    reverse->SetNextStop(m_head);
    m_head = reverse;
    counter += 2;
    current = current->GetNextStop();
  }

  delete m_tail;
  m_tail = new Stop(m_head->GetName(), m_totalStops);

  //deletes the end of the route m_totalStops times
  Stop* nextToEnd = m_head;

  for(int i = 0; i < m_totalStops; i++){

    while(nextToEnd->GetNextStop()->GetNextStop()){
      nextToEnd = nextToEnd->GetNextStop();
    }
    
    delete (nextToEnd->GetNextStop());
    nextToEnd->SetNextStop(nullptr);
    
    nextToEnd = m_head;
  }
  
  m_currentStop = m_head;

  cout << m_totalStops << " stops reversed." << endl;
}
