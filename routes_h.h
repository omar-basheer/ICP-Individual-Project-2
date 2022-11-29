//
//  routes_h.h
//  Routes
//
//  Created by omar on 11/20/22.
//

#ifndef routes_h_h
#define routes_h_h

#include "airports_h.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <deque>

using namespace std;

/**
 * # This class contains functions that read the routes.csv file and utilize its data. 
 * The functions within create two maps. The first stores the iata code of a source airport and the iata codes 
 * of all destination airports that can be reached from that source. The second stores all the airlines that go from 
 * a particular source airport to a particular destination airport.
 */
class Route{
    
private:
    
    static string Source_AirportCode;
    static string Destination_AirportCode;
    static string AirlineCode;
    static string Stops;
    

    
public:
    
    
    /**
     * AirportRoutesMap - map with string keys and string vector values that stores the iata codes of all airports that can be reached from a particular source airport
     */
    static map<string, vector<string>> AirportRoutesMap;
    

    /**
     * AirlineRoutesMap - map with string vector keys and string vector values that stores the airline codes of all the airline that goes from one source airport to all destination airports
     */
    static map<vector<string>, vector<string>> AirlineRoutesMap;
    
    
    /**
     * Return the iata code of a source airport
     * @return source airport iata code
     */
    static string const getSA_Code(){
        return Source_AirportCode;
    }
    
    /**
     * Return the iata code of a destination airport
     * @return destination airport iata
     */
    string const getDA_Code(){
        return Destination_AirportCode;
    }
    
    /**
     * Return the airline code of an airline leaving that source airport
     * @return airline code of flight
     */
    static string const getAirline_Code(){
        return AirlineCode;
    }

    /**
     * Return the number of stops made by an airline levaing the source aiport
     * @return number of in-flight stops
     */
    static string const getStops(){
        return Stops;
    }
    

    /**
     * Split a string by a delimiter and store values into a vector
     * @param vector_string  a single string vlaue
     * @return vector of strings
     */
    static vector<string> stringToVec(string vector_string){
        vector<string> output;
        string delimiter = ", ";
        string substring;
        size_t pos = 0;
        while((pos = vector_string.find(delimiter)) != std::string::npos){
            substring = vector_string.substr(0, pos);
            // cout << substring << endl;
            output.emplace_back(substring);
            vector_string.erase(0, pos + delimiter.length());
        }
        output.emplace_back(vector_string);
        return output;
    }
    
    
    /**
     * Convert values in a vector into a single string
     * @param string_vector  a vector of strings
     * @return a single concatenated string of the vector values
     */
    static string const vecToString(vector<string> string_vector){
        stringstream stream;
        stream << "[";
        for(auto it = string_vector.begin(); it != string_vector.end(); it++){
            if(it != string_vector.begin()){
                stream << ", ";
            }
            stream << *it;
        }
        // stream << "]";
        return stream.str();
    }
    
    
    /**
     * Read Route.csv file
     * @param filename  a csv file
     * @return a map with string keys of an airport iata code and values of the iata codes of all destination airports that can be reached from a particular key
     */
    static map<string, vector<string>> AirportRouteReader(string const &filename){

        fstream inputStream;
        inputStream.open(filename);
        
        if(inputStream){
            // cout << "> file opened"<<endl;
            vector<string> splitline;
            string streamline, streamword, temp;

            while(getline(inputStream, streamline)){
                splitline.clear();
                stringstream line_of(streamline);
                //cout << "  >> got streamline" << endl;
                //cout << "   >> streamline: " << streamline << endl;

                while(getline(line_of, streamword, ',')){
                    splitline.push_back(streamword);
                   // cout << "   >> got streamword: " << streamword << endl;
                }

                // read into AirRoutesMap first
                string routekey = splitline[2];  //source airport iata
                // cout << endl;
                // cout << " >> key - " << routekey << endl;
                if (AirportRoutesMap.count(routekey) > 0){
                    // key found
                    vector<string> routelist = AirportRoutesMap[splitline[2]];
                    // cout << "  current list - " << vecToString(routelist) << endl;
                    routelist.emplace_back(splitline[4]);  // destination airport iata
                    AirportRoutesMap.erase(splitline[2]);
                    // cout << "  updated list - " << vecToString(routelist) << endl;
                    // cout << endl;
                    AirportRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
                }
                else{
                    // key not found
                    vector<string> routelist;
                    routelist.emplace_back(splitline[4]);  // destination airport iata
                    // cout << "  new current list - " << vecToString(routelist) << endl;
                    AirportRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
                }
                
            }
            inputStream.close();
            cout << "> Airport-Route map created..."<<endl;
            
        }
        else{
            cout << "error opening/reading data file: check that the input file is in right directory and the given file name matches" << endl;
            }
        
        return AirportRoutesMap;
        
    }
    
    /**
     * Read Route.csv file
     * @param filename  a csv file
     * @return a map with string vector keys of a route's airline and start aiport iata code, and values of the iata codes of all destination airports that can be reached from a particular key
     */
    static map<vector<string>, vector<string>> AirlineRouteReader(string const &filename){

        fstream inputStream;
        inputStream.open(filename);
        // cout << "> file opened"<<endl;
        // check if file exists
        if(inputStream){
            vector<string> splitline;
            string streamline, streamword, temp;
            
            while(getline(inputStream, streamline)){
                splitline.clear();
                stringstream line_of(streamline);
                  //  cout << "  >> got streamline" << endl;
                  //  cout << "   >> streamline: " << streamline << endl;

                while(getline(line_of, streamword, ',')){
                    splitline.push_back(streamword);
                  //cout << "   >> got streamword: " << streamword << endl;
                }
                // read into RouteAirlineMap
                // Route routekey = Route(splitline[2], splitline[0],splitline[7]);
                vector<string> routekey2;
                routekey2.emplace_back(splitline[2]); // source airport
                routekey2.emplace_back(splitline[4]); // destination airport
                routekey2.emplace_back(splitline[7]); // stops
                // cout << endl;
                // cout << " >> key - " << vecToString(routekey2) << endl;
                
                if (AirlineRoutesMap.contains(routekey2)){
                    // key found
                    vector<string> routelist = AirlineRoutesMap[routekey2];
                    // cout << "  current list - " << vecToString(routelist) << endl;
                    routelist.emplace_back(splitline[0]);  // airline code
                    AirlineRoutesMap.erase(routekey2);
                    AirlineRoutesMap.insert(::pair<vector<string>, vector<string>> (routekey2, routelist));
                }
                else{
                    // key not found
                    vector<string> routelist;
                    routelist.emplace_back(splitline[0]);// airline code
                    // cout << "  new current list - " << vecToString(routelist) << endl;
                    AirlineRoutesMap.insert(::pair<vector<string>, vector<string>> (routekey2, routelist));
                }
            }
            inputStream.close();
            cout << "> Airline-Route map created..."<<endl;
        }
        else{
            cout << "error opening/reading data file: check that the input file is in right directory and the given file name matches" << endl;
        }
        
        return AirlineRoutesMap;
    }
    

    /**
     * Print out the key value pairs of a given map
     * @param thisMap  a map of string keys and string vector values
     */
    static void printMap(map<string, vector<string>> thisMap){
        for(auto &pair : thisMap){
            cout << "[" << pair.first << "]" << " >> " << vecToString(pair.second) << endl;
            cout << endl;
        }
    }
    
    /**
     * Print out the key value pairs of a given map
     * @overload
     */
    static void printMap(map<vector<string>, vector<string>> thisMap){
        for(auto &pair : thisMap){
            cout << vecToString(pair.first) << "] >> " << vecToString(pair.second) << "]" << endl;
        }
    }
    
    
    /**
     * Check if a given string deque conatins a given string
     * @param deq a deque of strings
     * @param value a string
     * @return true if deque contains element and false if otherwise
     */
    static bool contains(deque<string> deq, string value){
        deque<string>:: iterator itr;
        itr = find(deq.begin(), deq.end(), value);
        if(itr != deq.end()){
            return true;
        }
        else
            return false;
    }

    /**
     * Check if a given string vector conatins a given string
     * @param vec a vector of strings
     * @param value a string
     * @return true if vector contains element and false if otherwise
     */
    static bool contains(vector<string> vec, string value){
        if(std::find(vec.begin(), vec.end(), value) != vec.end()) {
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /**
     * Find a given goal airport from a start airport using airport iata codes
     * @param start_airport the iata code of a start airport
     * @param goal_airport the iata code of a goal airport
     * @return string of iata codes of found solution path containing all connected airports between start airport and goal airport
     */
    static string findRoute(string start_airport, string goal_airport){
        
        map<string, string> child_parent;
        cout << "  >> start airport: " << start_airport << endl;
        cout << "  >> goal airport: " << goal_airport << endl;
        cout << "     >>> searching..." << endl;

        deque<string> frontier;
        frontier.emplace_back(start_airport);
        // cout << "added parent " << start_airport << " to frontier " << endl;
        vector<string> explored_set;
        // cout << "explored set: " << vecToString(explored_set) << endl;
        child_parent.insert(pair<string, string> (start_airport, ""));

        while(!frontier.empty()){
            string parent = frontier.front();
            frontier.pop_front();
            // cout << "popped parent, " << parent << endl;
            explored_set.emplace_back(parent);
            // cout << "added node to explored set, explored set: " << vecToString(explored_set) << endl;
            
            vector<string> successors = AirportRoutesMap[parent];
            if(!successors.empty()){
                for (int i = 0; i < successors.size(); i++){
                    string child = successors[i];
                    child_parent.insert(pair<string, string> (child, parent));
                    // cout << "generated successor: " << child << endl;
                    if (!contains(explored_set, child) && (!contains(frontier, child))){
                        if(child.compare(goal_airport) == 0){
                            cout << "      >>> found goal: " << child << endl;
                            string solution = solution_path(child_parent, child);
                            return solution;
                        }
                    }
                    frontier.emplace_back(child);
                }
            }
//            cout << "no route from this airport: " << parent << endl;
//            continue;
            else{
                cout << "no route from this airport: " << endl;
                break;
            }
        }
        return NULL;
        
    }
    
    /**
     * Find solution path by connecting each airport iata code to its given parent
     * @param solution_map  a map of parent-child relationships between all airports explored during the search. keys are iata codes of child states and values are iata codes of parent states.
     * @param child  the goal airport iata code, the last child discovered during the search
     * @return concatenated string of all connected nodes from start aiport to goal airport
     */
    static string solution_path(map<string, string> solution_map, string child){
        vector<string> solution_path;
        solution_path.emplace_back(child);
        // cout << vecToString(solution_path) << endl;
        string parent = solution_map[child];
        solution_path.emplace_back(parent);
        // cout << vecToString(solution_path) << endl;
        while(parent != ""){
            child = parent;
            parent = solution_map[child];
            solution_path.emplace_back(parent);
        }
        reverse(solution_path.begin(), solution_path.end());
        cout << "      >>>> solution path: "<< vecToString(solution_path) << " ]"<< endl;
        
        return vecToString(solution_path);
    }

};

map<string, vector<string>> Route::AirportRoutesMap;
map<vector<string>, vector<string>> Route::AirlineRoutesMap;



#endif /* routes_h_h */
