//
//  main.cpp
//  AirlinerC++
//
//  Created by omar on 11/19/22.
//

#include <iostream>
#include <map>
#include <vector>

#include "Routes/routes_h.h"
#include "Airports/airports_h.h"
#include "read_write_h.h"

using namespace std;

int main(){
    
    string airport_filename = "//Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/Airports/airports.csv";
    
    string airRoute_filename = "/Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/Airliner/routes.csv";
    
    map<vector<string>, Airport> airport_map;
    airport_map = Airport::AirportFileReader(airport_filename);
//    Airport::printMap(myAirportMap);
    
    map<string, vector<string>> airport_routemap;
    airport_routemap = Route::AirportRouteReader(airRoute_filename);
//    Route::printMap(myAirRoutesMap);
    
    map<vector<string>, vector<string>> airline_routemap;
    airline_routemap = Route::AirlineRouteReader(airRoute_filename);
//    Route::printMap(myAirRoutesMap);
    
    ReadWrite::inputFileReader("/Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/ReadWrite/myfile");
    
}
