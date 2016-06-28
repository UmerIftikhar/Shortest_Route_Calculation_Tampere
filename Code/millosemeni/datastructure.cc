// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106
/*
 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
 Working Test Cases:
 *(For these four files, all commands are executed properly) 
 1) 1-route
 2) 2-routes
 3) tyoohje-esimerkki
 4) zz-final_bus_liteN 
 
 Partially Working Cases:
 *For these Two files, All commands are executed fine, except for the shortest path calculations, where some how
 *my program gets stuck in a loop.
 1) zzz-final_bus_full (Only T 07:00 70 5018,  works)
 2) 3-bidirectional-routes
 * For 3-bidirectional-routes my algorithm works fine till Dijkstra's algorithm,but when I use
 * my Map to print the stops, my Map actually gets stuck in a loop, And the reason for that is:
 * myMap[nextStop] = previousStop.
 * So while traversing my Map, I some how reaches the situation where, myMap[nextStop] = previousStop
 * and myMap[previousStop] = nextStop. Therefore, never exiting the condition.
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
 //In order to make the code efficient, I have stored the indexes of the neighboring stops/routes rather then
 //their actual stopId and routeId. Therefore I could access the neighbor routes directly. 
 
 //Firstly I make the graph(when add_stop_to_route is called).
//When a stop is added along with its corresponding route, I check all of the routes to check whether
//that stop exists there or not. If that stop does exist in the other routes, I add the next stop of that route(if that stop exists),
//to its neighbor as well. Therefore I know how my whole graph is now connected.
 
 /////////////////////////////////////////////////////////////////
//Function => getCurrentBusTime
//This function helps me assigning dynamic weights to the edges at run time.
//Hence whenever a route is changed I call this function to adjust the weights accordingly.
//Weights are stored in a .distance property of Structure routeSpecs.
/////////////////////////////////////////////////////////////////
 
 //I made copy of my Graph, so that the changes made here are not affected in the original Graph.    

//First I search for the index of my starting stop and the corresponding route.
//index_start_r, index_end_r, index_start_s and index_end_s are set to -1 at the start.
//So if any of the stops are not found at the end of the traversing, I exit the function and print the corresponding message.
 
//As soon as the stops are found, I will break the loop and start off the calculation.

//If any of the input stops are not found, exit the function and print this message.    


//A custom Class is set to push relevant data in to the Queue.   
////////////////////////////////////////////////////////////////////////////
//myMap => stores the path as the graph is traversed from source to the destination.
//myDisplayInfo => would be later used to print the journey
//Q => Queue for pushing and popping stops, while performing Dijkstra's algorithm.

//Firstly I perform the calculation to check whether any bus leaves the stop, at the time entered by the User.
//getCurrentBusTime is used to accomplish the task.

//After that I have the startTime at which the bus would arrive at the given bus stop.-------------------
 
//And now I will start making further calculations.
//After that the weight of the starting node is set.
//I then push the starting Stop in to the Queue, just before starting the Dijkstra's algorithm.

//If there is no bus leaving at the time given by the User, I simply exit the function and print NO_SUCH_STOP.

//////////////////////////////////////////////////////////////////////
//Just to clear, .distance property contains the Weight of  Edges and not the .weight property.
//It was difficult to change, as I already wrote a lot of Code.
//////////////////////////////////////////////////////////////////////
//u will contain the current stop that would be popped out of the Queue.

 //Because routeIdOfPrevRoute is used to check whether I am traveling on the same route or the route has been changed.
 
 //As soon as I found the destination Stop I will exit Dijkstra's algorithm. 


 //This last check means that if the time has exceeded above 23:59, simply exit the function.

//u.neighborRoutes contains all the neighbors of the current Stop.
//curr_Neigb contains information of the Stop.     
//Now the current Stop could have multiple neighbors, I iterate through all of them.
//curr_Neigb holds the information of the current Neighbor being processed.
//v_r and v_s are the index of this curr_Neigb, so I could access them straight away.
//v_r is the index of the route, v_s is the index of the stop.  

//Do not confuse  curr_Neigb.weight with the Weight of the Dijkstra's algorithm, It only contains the
//information of the time it takes the bus to reach this particular stop(Starting from the start stop of this route).

//curr_Neigb_Dis is set to 10000000 initially(Conceptually this is infinity in terms of 24 hrs clock).


//Now this is the main check which is deciding and allocating the dynamic weights to the edges at run time.
//This algorithm uses a function  getCurrentBusTime() => declared above.
//Hence as long as the route remains the same, I am not changing the bus and the time is simply added
//as I move from one Stop to the Other(in the same route).
//But as soon as I need to change the route, it is evident that I must change the bus as well.
//Therefore, I perform a small calculation to check when would the bus reach this particular stop of the new route.
//getCurrentBusTime(routeIdOfCurrRoute,dis,stopMinutes) => tells me when is the bus that I would catch will leave the
//first station of that route, and then I add the time of this current Stop(.minutes property).
//Therefore I have a count of exact time Always.
//Rest is simple, where I add the stop to the Queue, to perform further processing.


//If the destination path exist and there exist a path to that Stop, I will now
//print my journey here.


//Now I traverse my Map, from destination to the source, and save that information into a
//vector myDisplayInfo.
//I cannot print this information right now as the route is yet not clear.  


//Now that I have myDisplayInfo, I would traverse this information in reverse order.
//Actually in order to avoid Stack I used vector and then traversed it in the reverse order
//to print my journey.

//Now previousRouteName is used to check whether the new route is different from the previous one,
//and if so, I will now print the "->", as shown in the test cases.
//printDash is used to check whether I should print "->" this or not. 

//Rest of the code is simple traversing.



 
 */


#include <sstream>
#include <limits>
#include <queue>


#include "datastructure.hh"


Datastructure::Datastructure()
{
}

Datastructure::~Datastructure()
{
    empty();
    //data_buses.clear();
    //data_routeStops.clear();
    //data_routes.clear();
    //data_busStops.clear();
}

void Datastructure::add_stop(int stop_id, std::string stop_name)
{
 
    totalStops++; 
    busStops newBusStop;
    newBusStop.stopId = stop_id;
    newBusStop.stopName  = stop_name;
    data_busStops.push_back(newBusStop);

    
}

void Datastructure::add_route(int route_id, std::string route_name)
{
    totalRoutes++;  //increment totalRoutes to keep the count.
    routes newRoute;
    newRoute.routeId = route_id;
    newRoute.routeName = route_name;
    data_routes.push_back(newRoute); 
}


//Now I will make the graph here.
//When a stop is added along with its corresponding route, I check all of the route to check whether
//that stop exists there or not. If that stop does exist in the other routes, I add the next stop of that route,
//to its neighbor as well. Therefore I know how my whole graph is now connected.
void Datastructure::add_stop_to_route(int route_id, int stop_id, unsigned int minutes)
{

/*    
   routeStops newRouteStop1;
   routeSpecs newRouteSpecs1; 
   newRouteSpecs1.minutes = minutes; //make it => coming from previous.
   newRouteSpecs1.stopId = stop_id;
   newRouteSpecs1.routeId = route_id;
   myMainMap[std::make_pair(route_id,stop_id)] = newRouteSpecs1;
*/     
 
/////////////////////////////////////////////////////////////////// 
//In order to save the name of routes and stop names.
///////////////////////////////////////////////////////////////////    
    std::string rrrRouteName;
    std::string rrrStopName;    
    for(int j=0;j<data_routes.size();j++){
        if(data_routes.at(j).routeId == route_id){
            rrrRouteName = data_routes.at(j).routeName;
            break;
        }
    }
    
    for(int j=0;j<data_busStops.size();j++){
        if(data_busStops.at(j).stopId == stop_id){
            rrrStopName = data_busStops.at(j).stopName;
            break;
        }
    }
/////////////////////////////////////////////////////////////////// 
//In order to save the name of routes and stop names.
/////////////////////////////////////////////////////////////////    
/*
ROUTEADDSTOP;11;1;0
ROUTEADDSTOP;11;2;5
ROUTEADDSTOP;11;3;15
ROUTEADDSTOP;11;4;30
ROUTEADDSTOP;11;5;60

ROUTEADDSTOP;12;5;0
ROUTEADDSTOP;12;4;20
ROUTEADDSTOP;12;3;30
ROUTEADDSTOP;12;2;40
ROUTEADDSTOP;12;1;60      
*/  
       
   
   
    
   
   bool found=false;
   routeStops newRouteStop;
   routeSpecs newRouteSpecs; 
   newRouteSpecs.minutes = minutes; //make it => coming from previous.
   newRouteSpecs.stopId = stop_id;
   newRouteSpecs.routeId = route_id;
   newRouteSpecs.routeName = rrrRouteName;
   newRouteSpecs.stopName = rrrStopName;
   int curr_route_index;
   int curr_stop_index;
   int prev_StopId;
   bool stop_found=false;

      for(int i=0;i<data_routeStops.size();i++){
                 if(data_routeStops.at(i).routeId == route_id){
                     curr_route_index = i;
                     curr_stop_index = data_routeStops.at(i).nodes.size();
                     
                            neighborSpec currNeighborRoutes_new;   
                            //currNeighborRoutes_new.neighborRouteId = route_id;
                            currNeighborRoutes_new.neighborRouteId = curr_route_index;
                            currNeighborRoutes_new.neighborStopIndex = curr_stop_index;
                            currNeighborRoutes_new.weight = minutes;
                     prev_StopId = data_routeStops.at(i).nodes.at(curr_stop_index - 1).stopId;
                     data_routeStops.at(i).nodes.at(curr_stop_index - 1).neighborRoutes.push_back(currNeighborRoutes_new);
                     found=true;
                     break;
                 } 
      }
   
if(!found){
       curr_route_index=data_routeStops.size();        //new route will be added on this index.
       curr_stop_index = 0;
}   
   

neighborSpec currNeighborRoutes_new;   
//currNeighborRoutes_new.neighborRouteId = route_id;
currNeighborRoutes_new.neighborRouteId = curr_route_index;
currNeighborRoutes_new.neighborStopIndex = curr_stop_index+1;   
currNeighborRoutes_new.weight =  minutes;   //test.

/////////////////////////////////////////////////////////////////////
//This checks for the input StopId in other routes, and connect the neighbors accordingly.
/////////////////////////////////////////////////////////////////////
    for(int i=0;i<data_routeStops.size();i++){
               //stop_found = false; 
        if(data_routeStops.at(i).routeId != route_id ){
        
               //When the bus changes the route, we must update the route Info accordingly.
                //Single Stop can be linked to multiple routes as well.
                    for(int j=0;j<data_routeStops.at(i).nodes.size();j++){
  
                           if( data_routeStops.at(i).nodes.at(j).stopId == stop_id){
                                    neighborSpec currNeighborRoutes;    
                                    //currNeighborRoutes.neighborRouteId = data_routeStops.at(i).routeId;
                                    currNeighborRoutes.neighborRouteId = i;
                                    //currNeighborRoutes.neighborStopIndex = j;
                                    currNeighborRoutes.neighborStopIndex = j+1; //because j is the same stop.
                                    currNeighborRoutes.weight = data_routeStops.at(i).nodes.at(j).minutes;//test.
                                    data_routeStops.at(i).nodes.at(j).neighborRoutes.push_back(currNeighborRoutes_new);
                                    newRouteSpecs.neighborRoutes.push_back(currNeighborRoutes);                                     
                                    //update information in both the nodes.
                                    //data_routeStops.at(i).nodes.at(j).neighborRoutes.push_back(currNeighborRoutes_new);
/*                                    
                                  if(data_routeStops.at(i).nodes.size() > j+1){
                                     if(prev_StopId != data_routeStops.at(i).nodes.at(j+1).stopId ){
                                        data_routeStops.at(i).nodes.at(j).neighborRoutes.push_back(currNeighborRoutes_new);
                                        newRouteSpecs.neighborRoutes.push_back(currNeighborRoutes);   
                                        stop_found = true;
                                    }                                                                         
                                     
                                  }  
*/
                                    
                           }
                           //if(stop_found){break; stop_found = false;}

                    }              
            
        
        }

        
    }
/////////////////////////////////////////////////////////////////////
//This checks for the input StopId in other routes, and connect the neighbors accordingly.
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//If the stop or route, does not exist,create a new one.
/////////////////////////////////////////////////////////////////////
if(!found){
//new node is added.    
        newRouteStop.routeId = route_id;       
        newRouteStop.nodes.push_back(newRouteSpecs);
        data_routeStops.push_back(newRouteStop);       

}
else{

        data_routeStops.at(curr_route_index).nodes.push_back(newRouteSpecs);
}
/////////////////////////////////////////////////////////////////////
//If the stop or route, does not exist,create a new one.
/////////////////////////////////////////////////////////////////////    

        
        
        
        
        
    
}

void Datastructure::add_bus(int bus_id, int route_id, unsigned int start_hours, unsigned int start_minutes)
{
    totalBuses++;   //increment totalBuses to keep the count.
    buses newBus;
    newBus.busId = bus_id;
    newBus.routeId = route_id;
    newBus.start_hours = start_hours;
    newBus.start_minutes = start_minutes;
    data_buses.push_back(newBus);     
}

void Datastructure::empty()
{
    data_buses.clear();
    data_routeStops.clear();
    data_routes.clear();
    data_busStops.clear();
    totalBuses=0;
    totalRoutes=0;  
    totalStops=0; 
}

void Datastructure::print_stop(int stop_id)
{
  //Error: No such stop!
     bool doesExit = false;   
          for(int i=0;i<data_busStops.size();i++){
              
              if(data_busStops.at(i).stopId == stop_id){
                     doesExit = true;                 
                  std::cout<<data_busStops.at(i).stopName<<"\n";
                  //break;
              }
          
          }  

            if(!doesExit){
                 std::cout<<"Error: No such stop!"<<"\n";
            }
    
}

void Datastructure::print_buses(int stop_id)
{
     //first find the stopId in    data_routeStops, then use its RouteId to print info from data_routes.
    bool doesExit = false;
        for(int i=0;i<data_routeStops.size();i++){

            //doesExit = false;
            
            for(int j=0;j<data_routeStops.at(i).nodes.size();j++){
            
                    if(data_routeStops.at(i).nodes.at(j).stopId == stop_id){
                            doesExit = true;
                          
			  if(j<data_routeStops.at(i).nodes.size() -1){


			   
			   int routeId = data_routeStops.at(i).routeId;
                            std::cout<<data_routes.at(i).routeName<<"\n";  
                       }


                    }              

                    if(doesExit){
                        //break;
                    }
                    
            }
                         
       }
    
            if(!doesExit){
                 std::cout<<"Error: No such stop!"<<"\n";
            }    
            
}


void Datastructure::print_statistics()
{

/*    
    for(int i=0;i<data_routeStops.size();i++){
        
        std::cout<<"Route:  ";
        std::cout<<data_routeStops.at(i).routeId<<"\n";
                for(int j=0;j<data_routeStops.at(i).nodes.size();j++){
                            
                    std::cout<<"Stop:  "<<data_routeStops.at(i).nodes.at(j).stopId<<"\n";
                                 std::cout<<"Neighbors:  ";                   
                    for(int k=0;k<data_routeStops.at(i).nodes.at(j).neighborRoutes.size();k++){
                        int rr = data_routeStops.at(i).nodes.at(j).neighborRoutes.at(k).neighborRouteId;
                        //std::cout<<"RR: "<<rr<<"\n";
                        int ss = data_routeStops.at(i).nodes.at(j).neighborRoutes.at(k).neighborStopIndex;
                        //std::cout<<"SS: "<<ss<<"\n";
                          if(data_routeStops.at(rr).nodes.size() == ss)continue;
                         std::cout<<data_routeStops.at(rr).nodes.at(ss).stopId<<", ";
                    }
                    
                                 std::cout<<"\n";

                }
                std::cout<<"======================"<<"\n";
        }
*/
    
    std::cout<<totalStops<<" stops, "<<totalRoutes<<" routes, "<<totalBuses<<" buses."<<"\n";
    //std::cout<<data_busStops.size()<<"stops , "<<data_routes.size()<<"routes, "<<data_buses.size()<<"buses."<<"\n";
}

/////////////////////////////////////////////////////////////////
//This function helps me assigning dynamic weights to the edges at run time.
//Hence whenever a route is changed I call this function to adjust the weights accordingly.
/////////////////////////////////////////////////////////////////
int Datastructure::getCurrentBusTime(int routeId, int startTime, int stopMinutes){

    int departureTime = startTime;
    int busTime;
    int returnTime = -1;
    //since we only have the start hours of the starting stop, therefore I calculate the 
    //time at which the bus will arrive at the given stop.
    for(int i=0;i<data_buses.size();i++){
        
        if(data_buses.at(i).routeId == routeId){
//busTime + stopMinutes => is the time at which the bus would arrive at the given statiion.            
            busTime = 60*(data_buses.at(i).start_hours) + data_buses.at(i).start_minutes;
            if( busTime + stopMinutes -departureTime >= 0 ){
                        returnTime = busTime;
                        break;
            }
        
        }
    
    }
    
   return returnTime;
    
}
/////////////////////////////////////////////////////////////////
//This function helps me assigning dynamic weights to the edges at run time.
//Hence whenever a route is changed I call this function to adjust the weights accordingly.
/////////////////////////////////////////////////////////////////


//This function logic is now merged into the function=> add_stop_to_route.
//Therefore currently its not being used.
void Datastructure::makeGraph(){

/*
ROUTEADDSTOP;11;1;0
ROUTEADDSTOP;11;2;5
ROUTEADDSTOP;11;3;15
ROUTEADDSTOP;11;4;30
ROUTEADDSTOP;11;5;60

ROUTEADDSTOP;12;5;0
ROUTEADDSTOP;12;4;20
ROUTEADDSTOP;12;3;30
ROUTEADDSTOP;12;2;40
ROUTEADDSTOP;12;1;60      
*/  
    int currRouteId;
    int previousRouteId;
    int nextRouteId;
    
    int currStopId;
    int previousStopId;
    int nextStopId;    

      for(int i=0;i<data_routeStops.size();i++){
          //std::cout<<"\n";
        currStopId=0;
        previousStopId=0;
        nextStopId=0;        
            currRouteId = data_routeStops.at(i).routeId;

            for(int j=0;j<data_routeStops.at(i).nodes.size();j++){

                currStopId = data_routeStops.at(i).nodes.at(j).stopId;
                                       //std::cout<<"RouteID:  "<<currRouteId<<"\n";
                                        //std::cout<<"StopID:  "<<currStopId<<"\n";
                
                if( j-1 >= 0){
                    previousStopId = data_routeStops.at(i).nodes.at(j-1).stopId;                
                }
                if(data_routeStops.at(i).nodes.size() > j+1 ){
                    //std::cout<<"In here."<<"\n";
                    nextStopId = data_routeStops.at(i).nodes.at(j+1).stopId;                
                    //std::cout<<"Out here."<<"\n";
                          neighborSpec currNeighborRoutes_new;                      
                          currNeighborRoutes_new.neighborRouteId = i;                   
                          currNeighborRoutes_new.neighborStopIndex = j+1;                    
                          currNeighborRoutes_new.weight = data_routeStops.at(i).nodes.at(j+1).minutes;                          
                          data_routeStops.at(i).nodes.at(j).neighborRoutes.push_back(currNeighborRoutes_new);                         
                          
                }
                   
               
                
                    for(int k=0;k<data_routeStops.size();k++){

                        if(data_routeStops.at(k).routeId != currRouteId){
                                
                            for(int l=0;l<data_routeStops.at(k).nodes.size();l++){
                            
                                if(currStopId == data_routeStops.at(k).nodes.at(l).stopId){
                                
                                    neighborSpec currNeighborRoutes;    
                                    currNeighborRoutes.neighborRouteId = k;
                                    currNeighborRoutes.neighborStopIndex = l+1; //because j is the same stop.
                                    currNeighborRoutes.weight = data_routeStops.at(k).nodes.at(l).minutes;//test.

                                   if(data_routeStops.at(k).nodes.size() > l+1){
                                      if(previousStopId != data_routeStops.at(k).nodes.at(l+1).stopId ){
                                        data_routeStops.at(i).nodes.at(j).neighborRoutes.push_back(currNeighborRoutes);
 
                                        //std::cout<<"Inserting Neighbor: ";      
                                        //std::cout<<data_routeStops.at(k).nodes.at(l+1).stopId<<"\n";                                         
                                      }                                       
                                   
                                   }
                                     
                                        
                                
                                }
                                
                                
                            
                            }

                        }


                    }
                //std::cout<<"============================"<<"\n";


            }
             
          
      }


  /*  
          for(int i=0;i<data_routeStops.size();i++){
                  //std::cout<<"RouteID:  "<<data_routeStops.at(i).routeId<<"\n";        
                    for(int j=0;j<data_routeStops.at(i).nodes.size();j++){
                 // std::cout<<"StopID:  "<<data_routeStops.at(i).nodes.at(j).stopId<<"\n";
                   //std::cout<<"Neighbors:  "<<"\n";                 
                         for(int k=0;k<data_routeStops.at(i).nodes.at(j).neighborRoutes.size();k++){
                         
                             int rr1=data_routeStops.at(i).nodes.at(j).neighborRoutes.at(k).neighborRouteId;
                             int ss1=data_routeStops.at(i).nodes.at(j).neighborRoutes.at(k).neighborStopIndex;                             
                                //std::cout<<data_routeStops.at(rr1).nodes.at(ss1).stopId;
                                 //std::cout<<"\n";                        
                         }
                    
                    }
                          //std::cout<<"============================"<<"\n";
          }
  */  
    
    
}


void Datastructure::print_fastest_journey(int start_stop, int end_stop, unsigned int hours, unsigned int minutes)
{

    
    //makeGraph();
    //std::cout<<"Graph Created"<<"\n";
    bool found=false;
    bool do_change_route = false;
    std::string destinationRoute;
    bool found_destinationRoute=false;
    std::string sourceRoute;
    bool found_sourceRoute=false; 
    int index_start_r=-1;
    int index_end_r=-1;
    int index_start_s=-1;
    int index_end_s=-1;    
  
//I made copy of my Graph, so that the changes made here are not affected in the original Graph.    
    std::vector<routeStops> data_routeStopsCopy = data_routeStops;

//In this loop I search for the index of my starting stop and the corresponding route.
//index_start_r, index_end_r, index_start_s and index_end_s are set to -1 at the start.
//So if any of the stops are not found at the end of the traversing, I exit the function and print the corresponding message.    
    for(int i=0;i<data_routeStopsCopy.size();i++){
        
        
            for(int j=0;j<data_routeStopsCopy.at(i).nodes.size();j++){
            
                    if(data_routeStopsCopy.at(i).nodes.at(j).stopId == start_stop && !found_sourceRoute){
                            sourceRoute = data_routeStopsCopy.at(i).routeId;
                            found_sourceRoute = true;
                            index_start_r = i;
                            index_start_s = j;                            
                    }
                    else if(data_routeStopsCopy.at(i).nodes.at(j).stopId == end_stop && !found_destinationRoute){
                            destinationRoute = data_routeStopsCopy.at(i).routeId; 
                            found_destinationRoute = true;
                            index_end_r=i;
                            index_end_s=j;                            
                    }
//As soon as the stops are found, break the loop and start off the calculation.
                    if(found_destinationRoute && found_sourceRoute){
                               found = true;                        
                                break;

                    }            
                        
            }        
 
                    if(found){
                        break;
                    }            
            
     
       }

//If any of the input stops are not found, exit the function and print this message.    
    if(index_start_s == -1 || index_end_s==-1){
    
        std::cout<<NO_SUCH_STOP<<"\n";
        return;    
    }
    

//Class set to push relevant data in to the Queue.    
///////////////////////////////////////////////////////////////////////////
class Comparator
{
public:
int operator() ( const std::pair<routeSpecs,int>& p1, const std::pair<routeSpecs,int> &p2)
{
return p1.second>p2.second;
}
};     
////////////////////////////////////////////////////////////////////////////
//myMap stores the path as the graph is traversed from source to the destination.
std::map<int,displayInfo > myMap;
//myDisplayInfo would be later used to print the journey.
std::vector<displayInfo> myDisplayInfo;
//Queue for pushing and popping stops, while performing Dijkstra's algorithm.
std::priority_queue<std::pair<routeSpecs,float>, std::vector<std::pair<routeSpecs,float> >, Comparator> Q; 

//Now I perform the calculation to check whether any bus leaves the stop, at the time entered by the User.
//stopMinutes is the time at which bus reaches that particular stop(Starting from the initial stop).
int userTime = 60*hours+minutes;
int stopMinutes = data_routeStopsCopy.at(index_start_r).nodes.at(index_start_s).minutes;
int startTime = getCurrentBusTime(data_routeStopsCopy.at(index_start_r).routeId,userTime,stopMinutes) + stopMinutes;
int routeIdOfPrevRoute = data_routeStopsCopy.at(index_start_r).routeId;
int routeIdOfCurrRoute;
//Now I have the startTime at which the bus would arrive at the given bus stop.
//And now I will start making further calculations.
int initTime = startTime;
int currTime = startTime;
//Now the weight of the starting node is set.
data_routeStopsCopy.at(index_start_r).nodes.at(index_start_s).distance = startTime;
int dis = data_routeStopsCopy.at(index_start_r).nodes.at(index_start_s).distance;
//Here I have pushed the starting Stop in to the Queue, just before starting the Dijkstra's algorithm. 
Q.push(std::make_pair(data_routeStopsCopy.at(index_start_r).nodes.at(index_start_s),dis));  //push into Queue.

//Check that is set to true, if there exists a path from source to destination stop.
bool pathFound=false;

//std::cout<<"Initial Start Time:  "<<   startTime <<"\n"<<"\n";
//If there is no bus leaving at the time given by the User, I simply exit the function and print NO_SUCH_STOP.
    if(startTime == -1){
    
        std::cout<<NO_ROUTE<<"\n";
        return;    
    }

//////////////////////////////////////////////////////////////////////
//Just to clear, .distance property contains the Weight of  Edges and not the .weight property.
//It was difficult to change, as I already wrote a lot of Code.
//////////////////////////////////////////////////////////////////////
//u will contain the current stop that would be popped out of the Queue.
routeSpecs u;
while(!Q.empty())
{
    
    
 u = Q.top().first;     //get the Node.
 dis = Q.top().second;  //get the weight of this particular Node.
 currTime = Q.top().second;
 routeIdOfPrevRoute = u.routeId;    //I also need to save the routeId of the previous Node.
 //Because routeIdOfPrevRoute is used to check whether I am traveling on the same route or the route has been changed.
 //std::cout<<"StopId:  "<<u.stopId<<"   RouteID:   "<<u.routeId<<"\n";
 //As soon as I found the destination Stop I will exit Dijkstra's algorithm. 
 if(u.stopId==end_stop){
     pathFound=true;
     break;
 }
 else if(u.distance < initTime){
     
 }
 else if(u.distance > 1438 ){
     break; //If the time exceeds 24hrs.
 }
 //This last check means that if the time has exceeded above 23:59, simply exit the function.
 
 Q.pop();

 
 for(unsigned int i=0; i < u.neighborRoutes.size(); i++)
 {
     
//u.neighborRoutes contains all the neighbors of the current Stop.
//curr_Neigb contains information of the Stop.     
//Now the current Stop could have multiple neighbors, I iterate through all of them.
//curr_Neigb holds the information of the current Neighbor being processed.
//v_r and v_s are the index of this curr_Neigb, so I could access them straight away.
//v_r is the index of the route, v_s is the index of the stop.   
  neighborSpec curr_Neigb = u.neighborRoutes.at(i);        
  int v_r= curr_Neigb.neighborRouteId;
  int v_s = curr_Neigb.neighborStopIndex;
  int w = curr_Neigb.weight;  //minutes.
     //std::cout<<"Children "<<i<<":  ";
          
     //std::cout<<data_routeStopsCopy.at(v_r).nodes.at(v_s).stopId<<"\n";  
//Do not confuse  curr_Neigb.weight with the Weight of the Dijkstra's algorithm, It only contains the
//information of the time it takes the bus to reach this particular stop(Starting from the start stop of this route).
//This condition is simply used to skip the Assumption I made while adding the neighbors(add_stop_to_route function).  
  if(data_routeStopsCopy.at(v_r).nodes.size() == v_s)continue;
  //if(data_routeStopsCopy.at(v_r).nodes.at(v_s).stopId == u.cfsId )continue;
  //if(data_routeStopsCopy.at(v_r).nodes.at(v_s).stopId == u.stopId)continue;
//This is the routeId of the the neighbor(curr_Neigb).  
  routeIdOfCurrRoute = data_routeStopsCopy.at(v_r).routeId;
//curr_Neigb_Dis is set to 10000000 initially(Conceptually this is infinity in terms of 24 hrs clock).
  int curr_Neigb_Dis = data_routeStopsCopy.at(v_r).nodes.at(v_s).distance;  
//Hence   I will update the weight 
  if(curr_Neigb_Dis > dis )
  {

//Now this is the main check which is deciding and allocating the dynamic weights to the edges at run time.
//This algorithm uses a function  getCurrentBusTime() => declared above.
//Hence as long as the route remains the same, I am not changing the bus and the time is simply added
//as I move from one Stop to the Other(in the same route).
//But as soon as I need to change the route, it is evident that I must change the bus as well.
//Therefore, I perform a small calculation to check when would the bus reach this particular stop of the new route.
//getCurrentBusTime(routeIdOfCurrRoute,dis,stopMinutes) => tells me when is the bus that I would catch will leave the
//first station of that route, and then I add the time of this current Stop(.minutes property).
//Therefore I have a count of exact time Always.
//Rest is simple, where I add the stop to the Queue, to perform further processing.
      
  if(routeIdOfPrevRoute != routeIdOfCurrRoute){
      
      
      stopMinutes = data_routeStopsCopy.at(v_r).nodes.at(v_s).minutes;
      if(getCurrentBusTime(routeIdOfCurrRoute,dis,stopMinutes) != -1 ){
 
       startTime = getCurrentBusTime(routeIdOfCurrRoute,dis,stopMinutes) + stopMinutes;
 
                data_routeStopsCopy.at(v_r).nodes.at(v_s).distance = startTime; 
                initTime = startTime;                
                displayInfo newDisplayInfo;
                newDisplayInfo.stopId = u.stopId;
                newDisplayInfo.time = u.distance;      
                newDisplayInfo.routeId = u.routeId;
                newDisplayInfo.stopName = u.stopName;
                newDisplayInfo.routeName = u.routeName;
                //data_routeStopsCopy.at(v_r).nodes.at(v_s).cfsId = u.stopId;

                myMap[data_routeStopsCopy.at(v_r).nodes.at(v_s).stopId] = newDisplayInfo;   //parent[v] = u;
                
Q.push(std::make_pair(data_routeStopsCopy.at(v_r).nodes.at(v_s),data_routeStopsCopy.at(v_r).nodes.at(v_s).distance));         
 
  
      }

  }
  else{
   data_routeStopsCopy.at(v_r).nodes.at(v_s).distance = dis + data_routeStopsCopy.at(v_r).nodes.at(v_s).minutes - u.minutes;
   //data_routeStopsCopy.at(v_r).nodes.at(v_s).cfsId = u.stopId;   
   initTime = dis + w - u.minutes;
  displayInfo newDisplayInfo;
  newDisplayInfo.stopId = u.stopId;
  newDisplayInfo.time = u.distance;    
  newDisplayInfo.routeId = u.routeId;
  newDisplayInfo.stopName = u.stopName;
  newDisplayInfo.routeName = u.routeName;  

   myMap[data_routeStopsCopy.at(v_r).nodes.at(v_s).stopId] = newDisplayInfo;   //parent[v] = u;
Q.push(std::make_pair(data_routeStopsCopy.at(v_r).nodes.at(v_s),data_routeStopsCopy.at(v_r).nodes.at(v_s).distance));      

  }
   
  }  
  
  
 }
}

//for (std::map<int,displayInfo>::iterator it=myMap.begin(); it!=myMap.end(); ++it)
//    std::cout<<"first:  " << it->first << " => "<<"Second:  " << it->second.stopId <<"   Time:  " <<it->second.time <<'\n';


//std::cout<<"Last Stop:  "<<u.stopId<<"\n";
//std::cout<<"Out of Loop."<<"\n";
//If the destination path exist and there exist a path to that Stop, I will now
//print my journey here.
if(pathFound){
    //std::cout<<"Path Found."<<"\n";
        int currStopId;  
        displayInfo currStop;
        currStop.stopId = end_stop;
        currStop.time = u.distance;
        currStop.routeName = u.routeName;
        currStop.stopName = u.stopName;        
        currStop.routeId = u.routeId;
	currStopId = end_stop;
	
        
        //std::cout<<"Last Stop:  "<<u.stopId<<"\n";
//Now I traverse my Map, from destination to the source, and save that information into a
//vector myDisplayInfo.
//I cannot print this information right now as the route is yet not clear.        
        while(currStopId ){
    //std::cout<<"Curr Stop."<<"\n";
           myDisplayInfo.push_back(currStop);  
                //std::cout<<currStop<<"\n";
            currStop = myMap[currStopId];
            currStopId = currStop.stopId;
            //if(currStop.stopId ==start_stop )break;
                    
            //std::cout<<currStopId<<"\n";
        }
//Now that I have myDisplayInfo, I would traverse this information in reverse order.
//Actually in order to avoid Stack I used vector and then traversed it in the reverse order
//to print my journey.

//Now previousRouteName is used to check whether the new route is different from the previous one,
//and if so, I will now print the "->", as shown in the test cases.
//printDash is used to check whether I should print "->" this or not. 

//Rest of the code is simple traversing.
        
        std::string previousRouteName="";
        bool printDash=false;
        bool routeChange=false;
        
            for(int i=myDisplayInfo.size()-1;i>=0;i--){
                
                printDash = false;
                //routeChange = false;
                
                if( myDisplayInfo[i].routeName != previousRouteName){
                      std::cout<<myDisplayInfo[i].routeName<<"\n";
                }
  
////////////////////////////////////////////////////////////////////////////////////////////
//This condition is just to print the stop twice, when the route changes.                
                if(routeChange){
                    
                    myDisplayInfo[i].routeId;
                    myDisplayInfo[i+1].stopId;                    
                    myDisplayInfo[i+1].time;
                    int prvMinutes;
                    int prvTime;
                    for(int count=0;count<data_routeStops.size();count++){
                        if(data_routeStops.at(count).routeId == myDisplayInfo[i].routeId){
                                    
                            for(int count2=0;count2<data_routeStops.at(count).nodes.size();count2++){
                                if(data_routeStops.at(count).nodes.at(count2).stopId == myDisplayInfo[i+1].stopId){
                                            prvMinutes = data_routeStops.at(count).nodes.at(count2).minutes;
                                }
                            }
                        }
                    
                    }
      
                    prvTime = getCurrentBusTime(myDisplayInfo[i].routeId, myDisplayInfo[i+1].time, prvMinutes) + prvMinutes;
                    //std::cout<<"  "<<prvTime/60<<":"<<prvTime%60<<" "; 
                    //std::cout<<myDisplayInfo[i+1].stopId<<", ";
                    //std::cout<<myDisplayInfo[i+1].stopName<<"\n";                     
                    if(prvTime/60 < 10){
                          std::cout<<"  "<<"0"<<prvTime/60<<":"; 
                        //std::cout<<"  "<<"0"<<myDisplayInfo[i].time/60<<":";
                     }
                     else{
                            std::cout<<"  "<<prvTime/60<<":";
                     }
                     
                     if(prvTime%60 < 10){
                         std::cout<<"0"<<prvTime%60<<" ";
                     }
                     else{
                         std::cout<<prvTime%60<<" ";                     
                     }  
                     std::cout<<myDisplayInfo[i+1].stopId<<", ";
                     std::cout<<myDisplayInfo[i+1].stopName<<"\n";                     
                    routeChange = false;
                }
////////////////////////////////////////////////////////////////////////////////////////////                

                if( i-1 >= 0 ){
                
                    if(myDisplayInfo[i-1].routeName != myDisplayInfo[i].routeName){
                                    printDash = true;
                                    routeChange = true;
                                    //std::cout<<"->";    
                    } 
                            
                            
                }
                
                if( i == 0){
                    printDash = true;
                    //std::cout<<"->";
                }
                
                    previousRouteName = myDisplayInfo[i].routeName;
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Information would be printed here.                    
                if(!printDash){

                     if(myDisplayInfo[i].time/60 < 10){
                         std::cout<<"  "<<"0"<<myDisplayInfo[i].time/60<<":";
                     }
                     else{
                            std::cout<<"  "<<myDisplayInfo[i].time/60<<":";
                     }
                     
                     if(myDisplayInfo[i].time%60 < 10){
                         std::cout<<"0"<<myDisplayInfo[i].time%60<<" ";
                     }
                     else{
                         std::cout<<myDisplayInfo[i].time%60<<" ";                     
                     }                    
                    //std::cout<<"  "<<myDisplayInfo[i].time/60<<":"<<myDisplayInfo[i].time%60<<" ";                     
                }
                else{
                    
                     std::cout<<"->";
                     
                     if(myDisplayInfo[i].time/60 < 10){
                         std::cout<<"0"<<myDisplayInfo[i].time/60<<":";
                     }
                     else{
                            std::cout<<myDisplayInfo[i].time/60<<":";
                     }
                     
                     if(myDisplayInfo[i].time%60 < 10){
                         std::cout<<"0"<<myDisplayInfo[i].time%60<<" ";
                     }
                     else{
                         std::cout<<myDisplayInfo[i].time%60<<" ";                     
                     }                     
                     
                     //std::cout<<myDisplayInfo[i].time/60<<":"<<myDisplayInfo[i].time%60<<" ";                
                }
                    //std::cout<<"  "<<myDisplayInfo[i].time/60<<":"<<myDisplayInfo[i].time%60<<" ";      
                    std::cout<<myDisplayInfo[i].stopId<<", ";
                    std::cout<<myDisplayInfo[i].stopName<<"\n";                
////////////////////////////////////////////////////////////////////////////////////////////////////////
                        

            }
        
}
else{

    std::cout<<NO_ROUTE<<"\n";
}


    
}