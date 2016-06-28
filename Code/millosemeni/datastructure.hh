// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <stack>
#include <algorithm>
#include <map>

const std::string NO_ROUTE = "Error: No route!";
const std::string NO_SUCH_STOP = "Error: No such stop!";

class Datastructure
{
public:
    Datastructure();

    ~Datastructure();

    // Add a new bus stop
    void add_stop(int stop_id, std::string stop_name);

    // Add a new bus route
    void add_route(int route_id, std::string route_name);

    // Add a new stop to a route (both the route and the stop have already been added
    // using add_route and add_stop)
    void add_stop_to_route(int route_id, int stop_id, unsigned int minutes);

    // Add a new bus driving a route (the route has already been added using add_route) leaving at a certain
    // time from the terminus (first stop on route)
    void add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes);

    // Empty the datastructure
    void empty();

    // Print information on a bus stop
    void print_stop(int stop_id);

    // Print buses leaving from a stop
    void print_buses(int stop_id);

    // Print the number of stops, bus routes, and buses
    void print_statistics();

    // Print out the fastest journey leaving from stop start_stop to stop end_stop. Journey starts at the given time
    // and the whole journey must be done within the same day (before midnight).
    void print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes);
    
    //returns the time at which the bus would leave the first stop of that particular Route.
    //this time depends upon the startTime, at which the user arrives at that stop. 
    int getCurrentBusTime(int routeId, int startTime, int stopMinutes);

    void makeGraph();
    // Copy constructor is forbidden
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden
    Datastructure& operator=(const Datastructure&) = delete;

private:
    
  int totalBuses=0;
  int totalRoutes=0;  
  int totalStops=0;  
  typedef std::pair<int, int> myKey;    //Not being used now.
    
//This Struct is used to save the index of the neighbor stops, thus saving time to find them.  
 struct neighborSpec {
  int neighborStopIndex;
  int  neighborRouteId;
  int weight;

} ;   
    
//This is the main Struct that is keeping all the information regarding a Stop.
struct routeSpecs {
  
  int cfsId = -1;           //not being used now.
  std::string  stopName;    
  std::string  routeName;    
  int routeId;  
  int stopId;
  int  minutes;
  bool isVisited = false;
  int distance = 10000000; //This is the dynamic weight, this is initially set to infinity.
  std::vector<neighborSpec> neighborRoutes;  //it will contain the next stops a particular Stop could reach.
} ;

std::map<myKey, routeSpecs> myMainMap;  //Not being used now.

struct busStops {
  int stopId;
  std::string  stopName;
} ;

struct routes {
  int routeId;
  std::string  routeName;
} ;

struct buses {
  int busId;
  int routeId;
  int start_hours;
  int start_minutes;  
} ;

struct routeStops {
  int routeId;
   std::vector<routeSpecs> nodes;

} ;


struct displayInfo {
  int stopId;
  int time;
  int routeId;
  std::string  stopName;    
  std::string  routeName;     
} ;

std::vector<busStops> data_busStops; 
std::vector<routes> data_routes;
std::vector<buses> data_buses;
std::vector<routeStops> data_routeStops;    //Main Vector which will contain all the connections.


};

#endif // DATASTRUCTURE_HH
