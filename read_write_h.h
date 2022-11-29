//
//  read_write_h.h
//  ReadWrite
//
//  Created by omar on 11/27/22.
//

#ifndef read_write_h_h
#define read_write_h_h


#include "airports_h.h"
#include "routes_h.h"
#include "haversine_h.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

/**
 * # This class contains functions that read a user's input file and write a flight plan into a new file after a search.
 */
class ReadWrite{
    
private:
    
    static string StartCity;
    static string StartCountry;
    static string Destination_City;
    static string Destination_Country;
    
public:
    
    /**
     * Return the start city
     * @return  the start city
     */
    static const string getStartCity(){
        return StartCity;
    }
    
    /**
     * Return the start country
     * @return  the start country
     */
    static const string getStartCountry(){
        return StartCountry;
    }
    
    /**
     * Return the destination city
     * @return the destination city
     */
    static const string getDestination_City(){
        return Destination_City;
    }
    
    /**
     * Return the destination country
     * @return the destination country
     */
    static const string getDestination_Country(){
        return Destination_Country;
    }
    
    /**
     * Set the start city
     * @param city  the city of the start airport
     */
    static void setStartCity(string city){
        StartCity = city;
    }
    
    /**
     * Set the start country
     * @param country  the country of the start airport
     */
    static void setStartCountry(string country){
        StartCountry = country;
    }
    
    /**
     * Set the destination city
     * @param city  the city of the destination airport
     */
    static void setDestinationCity(string city){
        Destination_City = city;
    }
    
    /**
     * Set the destination country
     * @param country  the country of the destination airport
     */
    static void setDestinationCountry(string country){
        Destination_Country = country;
    }
    
    
    /**
     * Read user input file containing start city and country, and destination city and country
     * @param input_filename  the file name of the users input file
     */
    static void inputFileReader(const string &input_filename){
        
        string filename = input_filename;
        fstream inputStream;
        inputStream.open(input_filename);
        // check if file exists
        if(inputStream){
            cout << endl;
            cout << "> Reading input file..."<<endl;
            
            
            // split input file lines by ", " to get city and country values and store them in a vector
            vector<string> splitline;
            string delimiter = ", ";
            string substring;
            size_t pos = 0;
            string streamline;
            
            while(getline(inputStream, streamline)){
                stringstream line_of(streamline);
                
                while((pos = streamline.find(delimiter)) != std::string::npos){
                    substring = streamline.substr(0, pos);
                    // cout << substring << endl;
                    splitline.emplace_back(substring);
                    streamline.erase(0, pos + delimiter.length());
                }
                splitline.emplace_back(streamline);
                
            }
            inputStream.close();
            cout << "> File read!"<<endl;
            
            // set vector elements to respective variables
            setStartCity(splitline[0]);
            setStartCountry(splitline[1]);
            setDestinationCity(splitline[2]);
            setDestinationCountry(splitline[3]);
            
        }
        else{
            cout << "error opening/reading your file: check that input file is in right directory and the given file name matches" << endl;
        }
        
        
        string start_iata;
        string goal_iata;
        vector<string> all_starts;  // iata codes of all start airports in given start city
        vector<string> all_goals;   // iata codes of all destination airports in given destination city
        Airport tempair1;
        Airport tempair2;
        
        // get airport iata code from AirportMap associated with given city and country pair from user's input file
        for(auto const &pair : Airport::AirportMap){
            if(pair.first[1] == getStartCity() && pair.first[2] == getStartCountry()){
                start_iata = pair.first[0];
                all_starts.emplace_back(start_iata);
            }
            if(pair.first[1] == getDestination_City() && pair.first[2] == getDestination_Country()){
                goal_iata = pair.first[0];
                all_goals.emplace_back(goal_iata);
            }
        }
        cout << endl;
        cout << "> Starting search..."<<endl;
        
        haversineHelper(all_starts, all_goals, filename);
               
    }
    
    
    /**
     * Calculates haversine distance between airports in a solution path and accumulates the values to obtain the total distance between the start and goal airports given a particular solution path. Passes solution path with lowest distance to outputFileWriter for file writing
     *@param all_starts a string vector of the iata codes of all airports in the given start city
     *@param all_goals a string vector of the iata codes of all airports in the given goal city
     */
    static void haversineHelper(vector<string> all_starts, vector<string> all_goals, string filename){
        
        Airport tempair1;
        Airport tempair2;
        string flight_path;
        vector<string> flight_vec;
        map<double, string> all_paths;
        
        // find route for every airport within the start city]
        for(int j=0; j<all_goals.size(); j++){
            
            if(Route::AirportRoutesMap.count(all_goals[j]) == 0)
                continue;
            
            for(int i=0; i<all_starts.size(); i++){
                
                if(Route::AirportRoutesMap.count(all_starts[i]) == 0)
                    continue;
                
                cout << "  >> start number: " << all_starts.size() << endl;
                cout << "  >> goal number: " << all_goals.size() << endl;
                cout << "  * path " << i+1 << " *" << endl;
                // flight_path = Route::findRoute(all_starts[i], all_goals[all_goals.size()-1]);
                flight_path = Route::findRoute(all_starts[i], all_goals[j]);
                flight_vec = Route::stringToVec(flight_path);
                
                // calculate haversine
                double haversine_distance = 0;
                for(int i=1; i<flight_vec.size()-1; i++){
                    for(auto const &pair : Airport::AirportMap){
                        if(pair.first[0] == flight_vec[i]){
                            vector<string> temp1 {pair.first[0], pair.first[1], pair.first[2]};
                            tempair1 = Airport::AirportMap[temp1];
                        }
                        if(pair.first[0] == flight_vec[i+1]){
                            vector<string> temp2 {pair.first[0], pair.first[1], pair.first[2]};
                            tempair2 = Airport::AirportMap[temp2];
                        }
                    }
                    double latitude1 = stod(tempair1.getLatitude());
                    double latitude2 = stod(tempair2.getLatitude());
                    double longitude1 = stod(tempair1.getLongitude());
                    double longitude2 = stod(tempair2.getLongitude());
                    
                    double distance = haversine(latitude1, longitude1, latitude2, longitude2);
                    haversine_distance = haversine_distance + distance;
                    
                }
                all_paths.insert(pair<double, string> (haversine_distance, flight_path));
                cout << "      >>>> haversine distance: " << haversine_distance << " km"<<endl;
                cout << endl;
                
            }
            
        }
        // write solution to file
        outputFileWriter(all_paths.begin()->second, all_paths.begin()->first, filename);
    }
    
    
    
    /**
     * Write search output into file
     * @param flight_path the flight path to be written in the file
     * @param haversine the haversine for the shortest path
     * @param filename the filename of the input file
     */
         static void outputFileWriter(string flight_path, double haversine, string filename){
             
             string file = "/Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/flight plan";
             //string file = "flight plan";
             ofstream outputStream (file);
             cout << endl;
             cout << "> Writing to output file..." << endl;
             
             vector<string> output;
             output = Route::stringToVec(flight_path);
             
             // write to file
             outputStream << " >> Flight Plan <<" << endl;
             for(int i = 1; i < output.size() - 1; i++){
                 for(auto &pair : Route::AirlineRoutesMap){
                     if(pair.first[0] == output[i] && pair.first[1] == output[i+1]){

                         vector<string> airlines = Route::AirlineRoutesMap[pair.first];
                         string airline = airlines[0];
                         string stops = pair.first[2];
                         outputStream << "     " << i <<". flight "<< airline << " from " << output[i] << " to " << output[i+1] << " " << stops << " stops" << endl;
                         break;
                     }
                 }
                 
             }
             outputStream << "Total Flights: " << output.size()-2 << endl;
             outputStream << "Total Additional Stops: " << "0" << endl;
             outputStream << "Total Distance: " << haversine << " km" << endl;
             cout << "> Written to file!" << endl;
         }
    
};

string ReadWrite::StartCity;
string ReadWrite::StartCountry;
string ReadWrite::Destination_City;
string ReadWrite::Destination_Country;

#endif /* read_write_h_h */
