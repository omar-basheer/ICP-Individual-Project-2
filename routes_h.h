//
//  routes_h.h
//  Routes
//
//  Created by omar on 11/20/22.
//

#ifndef routes_h_h
#define routes_h_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <deque>
#include <set>

#include "airports_h.h"


using namespace std;

class Route{
    
private:
    
    static string Source_AirportCode;
    static string Destination_AirportCode;
    static string AirlineCode;
    static string Stops;
    
    
    Route(){
        this->Source_AirportCode = "";
//        this-> Destination_AirportCode = "";
        this-> AirlineCode = "";
        this-> Stops = "";
    }
    
    Route(string Destination_AirportCode, string airlineCode){
        this->Destination_AirportCode = Destination_AirportCode;
//        this-> Destination_AirportCode = "";
        this-> AirlineCode = airlineCode;
//        this-> Stops = "";
    }
    
public:
    
    static string const getSA_Code(){
        return Source_AirportCode;
    }
    
    string const getDA_Code(){
        return Destination_AirportCode;
    }
    
    static string const getAirline_Code(){
        return AirlineCode;
    }

    
    static string const getStops(){
        return Stops;
    }
    
    string toString(){
        return "[ " + getDA_Code() + ", " + getAirline_Code() + " ]";
    }
    
    
    static map<string, vector<string>> AirportRoutesMap;

    static map<vector<string>, vector<string>> AirlineRoutesMap;
    
    
    static string const vecToString(vector<string> string_vector){
        stringstream stream;
        stream << "[";
        for(auto it = string_vector.begin(); it != string_vector.end(); it++){
            if(it != string_vector.begin()){
                stream << ", ";
            }
            stream << *it;
        }
//        stream << "]";
        
        return stream.str();
    }
    
    
    static map<string, vector<string>> AirportRouteReader(string const &filename){

//       map<string, vector<string>> AirRoutesMap;
        fstream inputStream;
        inputStream.open(filename);
        
        if(inputStream){
//            cout << "> file opened"<<endl;
            vector<string> splitline;
            string streamline, streamword, temp;

            while(getline(inputStream, streamline)){
                splitline.clear();
                stringstream line_of(streamline);
//                cout << "  >> got streamline" << endl;
//                cout << "   >> streamline: " << streamline << endl;

                while(getline(line_of, streamword, ',')){
                    splitline.push_back(streamword);
//                    cout << "   >> got streamword: " << streamword << endl;
                }

//                read into AirRoutesMap first
                string routekey = splitline[2];
//                cout << endl;
//                cout << " >> key - " << routekey << endl;
                if (AirportRoutesMap.count(routekey) > 0){
                    // key found
                    vector<string> routelist = AirportRoutesMap[splitline[2]];
//                    cout << "  current list - " << vecToString(routelist) << endl;
                    routelist.emplace_back(splitline[4]);
                    AirportRoutesMap.erase(splitline[2]);
//                    cout << "  updated list - " << vecToString(routelist) << endl;
//                    cout << endl;
                    AirportRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
                }
                else{
//                  key not found
                    vector<string> routelist;
                    routelist.emplace_back(splitline[4]);
//                    cout << "  new current list - " << vecToString(routelist) << endl;
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
    
    
    static map<vector<string>, vector<string>> AirlineRouteReader(string const &filename){


        fstream inputStream;
        inputStream.open(filename);
//            cout << "> file opened"<<endl;
        if(inputStream){
            vector<string> splitline;
            string streamline, streamword, temp;
            
            while(getline(inputStream, streamline)){
                splitline.clear();
                stringstream line_of(streamline);
//                cout << "  >> got streamline" << endl;
//                cout << "   >> streamline: " << streamline << endl;

                while(getline(line_of, streamword, ',')){
                    splitline.push_back(streamword);
//                    cout << "   >> got streamword: " << streamword << endl;
                }
//              read into RouteAirlineMap
                vector<string> routekey2;
                routekey2.emplace_back(splitline[0]);
                routekey2.emplace_back(splitline[2]);
//                cout << endl;
//                cout << " >> key - " << vecToString(routekey2) << endl;
                
                if (AirlineRoutesMap.contains(routekey2)){
                    // key found
                    vector<string> routelist = AirlineRoutesMap[routekey2];
//                    cout << "  current list - " << vecToString(routelist) << endl;
                    routelist.emplace_back(splitline[4]);
                    AirlineRoutesMap.erase(routekey2);
                    AirlineRoutesMap.insert(::pair<vector<string>, vector<string>> (routekey2, routelist));
                }
                else{
                    // key not found
                    vector<string> routelist = AirlineRoutesMap[routekey2];
                    routelist.emplace_back(splitline[4]);
//                    cout << "  new current list - " << vecToString(routelist) << endl;
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
    

    
    static void printMap(map<string, vector<string>> thisMap){
        for(auto &pair : thisMap){
            cout << "[" << pair.first << "]" << " >> " << vecToString(pair.second) << endl;
            cout << endl;
        }
    }
    
    static void printMap(map<vector<string>, vector<string>> thisMap){
        for(auto &pair : thisMap){
            cout << vecToString(pair.first) << "] >> " << vecToString(pair.second) << "]" << endl;
        }
    }
    
    static bool contains(deque<string> deq, string value){
        deque<string>:: iterator itr;
        itr = find(deq.begin(), deq.end(), value);
        if(itr != deq.end()){
            return true;
        }
        else
            return false;
    }

    static bool contains(vector<string> vec, string value){
        if(std::find(vec.begin(), vec.end(), value) != vec.end()) {
            return true;
        }
        else {
            return false;
        }
    }
    
    
    
    static string findRoute(string start_airport, string goal_airport){
        
        map<string, string> child_parent;
        cout << "  >> start airport: " << start_airport << endl;
        cout << "  >> goal airport: " << goal_airport << endl;
        cout << "     >>> searching..."<<endl;

        
        deque<string> frontier;
        frontier.emplace_back(start_airport);
//        cout << "added parent " << start_airport << " to frontier " << endl;
        vector<string> explored_set;
//        cout << "explored set: " << vecToString(explored_set) << endl;
        
        while(!frontier.empty()){
            string parent = frontier.front();
            frontier.pop_front();
//            cout << "popped parent, " << parent << endl;
            child_parent.insert(pair<string, string> (parent, ""));
            explored_set.emplace_back(parent);
//            cout << "added node to explored set, explored set: " << vecToString(explored_set) << endl;
            
            vector<string> successors = AirportRoutesMap[parent];
            if(!successors.empty()){
                for (int i = 0; i < successors.size(); i++){
                    string child = successors[i];
                    child_parent.insert(pair<string, string> (child, parent));
//                    cout << "generated successor: " << child << endl;
                    if (!contains(explored_set, child) && (!contains(frontier, child))){
                        if(child.compare(goal_airport) == 0){
//                            cout << "found goal: " << child << endl;
//                            cout << vecToString(solution_path(child_parent, child));
                            string solution = solution_path(child_parent, child);
                            return solution;
                        }
                    }
                    frontier.emplace_back(child);
                }
            }
        }
        return NULL;
        
    }
    
    static string solution_path(map<string, string> solution_map, string child){
        vector<string> solution_path;
        solution_path.emplace_back(child);
//        cout << vecToString(solution_path) << endl;
        string parent = solution_map[child];
        solution_path.emplace_back(parent);
//        cout << vecToString(solution_path) << endl;
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



//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <map>
//#include <vector>
//#include <deque>
//#include <set>
//
//
////#include "nodes_h.h"
//#include "airports_h.h"
//
//
//using namespace std;
//
//class Route{
//
//private:
//
//    static string Source_AirportCode;
////    string Source_AirportId;
//    string Destination_AirportCode;
//    string Destination_AirportId;
//    static string AirlineCode;
//    static string Stops;
//
//
//    Route(){
//        this->Source_AirportCode = "";
////        this-> Source_AirportId = "";
////        this-> Destination_AirportCode = "";
////        this-> Destination_AirportId = "";
//        this-> AirlineCode = "";
////        this-> AirlineId = "";
//        this-> Stops = "";
//    }
//
//    Route(string Destination_AirportCode, string airlineCode){
//        this->Destination_AirportCode = Destination_AirportCode;
////        this-> Source_AirportId = "";
////        this-> Destination_AirportCode = "";
////        this-> Destination_AirportId = "";
//        this-> AirlineCode = airlineCode;
////        this-> AirlineId = "";
////        this-> Stops = "";
//    }
//
//public:
//
//
//
//    static string const getSA_Code(){
//        return Source_AirportCode;
//    }
//
////    string const getSA_Id(){
////        return Source_AirportId;
////    }
//
//    string const getDA_Code(){
//        return Destination_AirportCode;
//    }
//
//    string const getDA_Id(){
//        return Destination_AirportId;
//    }
//
//    static string const getAirline_Code(){
//        return AirlineCode;
//    }
//
////    string const getAirline_Id(){
////        return AirlineId;
////    }
//
//    static string const getStops(){
//        return Stops;
//    }
//
//    string toString(){
//        return "[ " + getDA_Code() + ", " + getAirline_Code() + " ]";
//    }
//
//
//    static map<string, vector<string>> AirRoutesMap;
//
//    static map<vector<string>, vector<string>> RouteAirlineMap;
//
//
//    static string const vecToString(vector<string> string_vector){
//        stringstream stream;
//        stream << "[";
//        for(auto it = string_vector.begin(); it != string_vector.end(); it++){
//            if(it != string_vector.begin()){
//                stream << ", ";
//            }
//            stream << *it;
//        }
////        stream << "]";
//
//        return stream.str();
//    }
//
//
//    static map<string, vector<string>> RoutesFileReader(string const &filename){
//
////       map<string, vector<string>> AirRoutesMap;
////       cout << "> map created"<<endl;
//
//        try{
//
//            fstream inputStream;
//            inputStream.open(filename);
////            cout << "> file opened"<<endl;
//            inputStream.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
//            vector<string> splitline;
//            string streamline, streamword, temp;
//
//            while(getline(inputStream, streamline)){
//
//                splitline.clear();
//                stringstream line_of(streamline);
////                cout << "  >> got streamline" << endl;
////                cout << "   >> streamline: " << streamline << endl;
//
//                while(getline(line_of, streamword, ',')){
//                    splitline.push_back(streamword);
////                    cout << "   >> got streamword: " << streamword << endl;
//                }
//
//                // read into AirRoutesMap first
//                string routekey = splitline[2];
////                cout << endl;
////                cout << " >> key - " << routekey << endl;
//                if (AirRoutesMap.count(routekey) > 0){
//                    // key found
//                    vector<string> routelist = AirRoutesMap[splitline[2]];
////                    cout << "  current list - " << vecToString(routelist) << endl;
//                    routelist.emplace_back(splitline[4]);
//                    AirRoutesMap.erase(splitline[2]);
////                    cout << "  updated list - " << vecToString(routelist) << endl;
////                    cout << endl;
//                    AirRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
//                }
//                else{
//                    // key not found
//                    vector<string> routelist;
//                    routelist.emplace_back(splitline[4]);
////                    cout << "  new current list - " << vecToString(routelist) << endl;
//                    AirRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
//                }
//            }
//            inputStream.close();
//        }
//        catch(exception &e){
//            cout << "error opening/reading file" << e.what()<< endl;
//        }
//        return AirRoutesMap;
//    }
//
//
//
//    static map<vector<string>, vector<string>> AirlineRouteReader(string const &filename){
//
//        try{
//
//            fstream inputStream;
//            inputStream.open(filename);
////            cout << "> file opened"<<endl;
//            inputStream.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
//            vector<string> splitline;
//            string streamline, streamword, temp;
//
//            while(getline(inputStream, streamline)){
//
//                splitline.clear();
//                stringstream line_of(streamline);
////                cout << "  >> got streamline" << endl;
////                cout << "   >> streamline: " << streamline << endl;
//
//                while(getline(line_of, streamword, ',')){
//                    splitline.push_back(streamword);
////                    cout << "   >> got streamword: " << streamword << endl;
//                }
////              read into RouteAirlineMap
//                vector<string> routekey2;
//                routekey2.emplace_back(splitline[0]);
//                routekey2.emplace_back(splitline[2]);
////                cout << endl;
////                cout << " >> key - " << vecToString(routekey2) << endl;
//
//                if (RouteAirlineMap.contains(routekey2)){
//                    // key found
//                    vector<string> routelist = RouteAirlineMap[routekey2];
////                    cout << "  current list - " << vecToString(routelist) << endl;
//                    routelist.emplace_back(splitline[4]);
//                    RouteAirlineMap.erase(routekey2);
//                    RouteAirlineMap.insert(::pair<vector<string>, vector<string>> (routekey2, routelist));
//                }
//                else{
//                    // key not found
//                    vector<string> routelist = RouteAirlineMap[routekey2];
//                    routelist.emplace_back(splitline[4]);
////                    cout << "  new current list - " << vecToString(routelist) << endl;
//                    RouteAirlineMap.insert(::pair<vector<string>, vector<string>> (routekey2, routelist));
//                }
//            }
//            inputStream.close();
//        }
//        catch(exception &e){
//            cout << "error opening/reading file" << e.what()<< endl;
//        }
//
//        return RouteAirlineMap;
//    }
//
//
//
//    static void printMap(map<string, vector<string>> thisMap){
//        for(auto &pair : thisMap){
//            cout << "[" << pair.first << "]" << " >> " << vecToString(pair.second) << endl;
//            cout << endl;
//        }
//    }
//
//    static bool contains(deque<string> deq, string value){
//        deque<string>:: iterator itr;
//        itr = find(deq.begin(), deq.end(), value);
//        if(itr != deq.end()){
//            return true;
//        }
//        else
//            return false;
//    }
//
//    static bool contains(vector<string> vec, string value){
//        if(std::find(vec.begin(), vec.end(), value) != vec.end()) {
//            return true;
//        }
//        else {
//            return false;
//        }
//    }
//
//
//
//    static string findRoute(string start_airport, string goal_airport){
//
//        map<string, string> child_parent;
//
//        cout << "start airport: " << start_airport << endl;
//        cout << "goal airport: " << goal_airport << endl;
//
//        deque<string> frontier;
//        frontier.emplace_back(start_airport);
////        cout << "added parent " << start_airport << " to frontier " << endl;
//        vector<string> explored_set;
////        cout << "explored set: " << vecToString(explored_set) << endl;
//
//        while(!frontier.empty()){
//            string parent = frontier.front();
//            frontier.pop_front();
////            cout << "popped parent, " << parent << endl;
//            child_parent.insert(pair<string, string> (parent, ""));
//            explored_set.emplace_back(parent);
////            cout << "added node to explored set, explored set: " << vecToString(explored_set) << endl;
//
//            vector<string> successors = AirRoutesMap[parent];
//            if(!successors.empty()){
//                for (int i = 0; i < successors.size(); i++){
//                    string child = successors[i];
//                    child_parent.insert(pair<string, string> (child, parent));
////                    cout << "generated successor: " << child << endl;
//                    if (!contains(explored_set, child) && (!contains(frontier, child))){
//                        if(child.compare(goal_airport) == 0){
////                            cout << "found goal: " << child << endl;
//                            cout << solution_path(child_parent, child)<< endl;
//                            return solution_path(child_parent, child);
//                        }
//                    }
//                    frontier.emplace_back(child);
//                }
//            }
//        }
//        return NULL;
//
//    }
//
//    static string solution_path(map<string, string> solution_map, string child){
//        vector<string> solution_path;
//        solution_path.emplace_back(child);
////        cout << vecToString(solution_path) << endl;
//        string parent = solution_map[child];
//        solution_path.emplace_back(parent);
////        cout << vecToString(solution_path) << endl;
//        while(parent != ""){
//            child = parent;
//            parent = solution_map[child];
//            solution_path.emplace_back(parent);
//        }
//        reverse(solution_path.begin(), solution_path.end());
//        return vecToString(solution_path) + "\n";
//    }
//
//};
//
//map<string, vector<string>> Route::AirRoutesMap;
//map<vector<string>, vector<string>> Route::RouteAirlineMap;


//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <map>
//#include <vector>
//#include <deque>
//#include <set>
//
//#include "airports_h.h"
//
//
//using namespace std;
//
//class Route{
//    
//private:
//    
//    string Source_AirportCode;
//    string Source_AirportId;
//    string Destination_AirportCode;
//    string Destination_AirportId;
//    string AirlineCode;
//    string AirlineId;
//    string Stops;
//    
//    
//    Route(){
//        this->Source_AirportCode = "";
//        this-> Source_AirportId = "";
//        this-> Destination_AirportCode = "";
//        this-> Destination_AirportId = "";
//        this-> AirlineCode = "";
//        this-> AirlineId = "";
//        this-> Stops = "";
//    }
//    
//    Route(string Source_AirportCode, string Source_AirportId, string Destination_AirportCode,string Destination_Airport, string AirlineCode, string AirlineId, string Stops){
//        this->Source_AirportCode = "";
//        this-> Source_AirportId = "";
//        this-> Destination_AirportCode = "";
//        this-> Destination_AirportId = "";
//        this-> AirlineCode = "";
//        this-> AirlineId = "";
//        this-> Stops = "";
//    }
//    
//public:
//    
//
//    
//    string const getSA_Code(){
//        return Source_AirportCode;
//    }
//    
//    string const getSA_Id(){
//        return Source_AirportId;
//    }
//    
//    string const getDA_Code(){
//        return Destination_AirportCode;
//    }
//    
//    string const getDA_Id(){
//        return Destination_AirportId;
//    }
//    
//    string const getAirline_Code(){
//        return AirlineCode;
//    }
//    
//    string const getAirline_Id(){
//        return AirlineId;
//    }
//    
//    string const getStops(){
//        return Stops;
//    }
//    
//    string const toString(){
//        return "[Route: (" + getSA_Code() + ", " + getSA_Id() + ") to " + "(" + getDA_Code() + ", " + getDA_Id() + ");  " + "AID: " + getAirline_Id() + ";  AC: " + getAirline_Code() + "; Stops:" + getStops() +"]";
//    }
//    
//    
//    static string const vecToString(vector<string> string_vector){
//        
//        stringstream stream;
//        stream << "[";
//        for(auto it = string_vector.begin(); it != string_vector.end(); it++){
//            if(it != string_vector.begin()){
//                stream << ", ";
//            }
//            stream << *it;
//        }
//        stream << "]";
//        return stream.str();
//    }
//    
//    
//    static map<string, vector<string>> AirRoutesMap;
//    
//    static map<string, vector<string>> RoutesFileReader(string const &filename){
//    
////       map<string, vector<string>> AirRoutesMap;
////        cout << "> map created"<<endl;
//
//        try{
//
//            fstream inputStream;
//            inputStream.open(filename);
////            cout << "> file opened"<<endl;
//            inputStream.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
//            vector<string> splitline;
//            string streamline, streamword, temp;
//
//            while(getline(inputStream, streamline)){
//
//                splitline.clear();
//                stringstream line_of(streamline);
////                cout << "  >> got streamline" << endl;
////                cout << "   >> streamline: " << streamline << endl;
//
//                while(getline(line_of, streamword, ',')){
//                    splitline.push_back(streamword);
////                    cout << "   >> got streamword: " << streamword << endl;
//                }
//                string routekey = splitline[2];
////                cout << endl;
////                cout << " >> key - " << routekey << endl;
//                if (AirRoutesMap.count(routekey) > 0){
//                    // key found
//                    vector<string> routelist = AirRoutesMap[splitline[2]];
////                    cout << "  current list - " << vecToString(routelist) << endl;
//                    routelist.emplace_back(splitline[4]);
//                    AirRoutesMap.erase(splitline[2]);
////                    cout << "  updated list - " << vecToString(routelist) << endl;
////                    cout << endl;
//                    AirRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
//                }
//                else{
//                    // key not found
//                    vector<string> routelist;
//                    routelist.emplace_back(splitline[4]);
////                    cout << "  new current list - " << vecToString(routelist) << endl;
//                    AirRoutesMap.insert(pair<string, vector<string>> (routekey, routelist));
//                }
//
//            }
//            inputStream.close();
//        }
//        catch(exception &e){
//            cout << "error opening/reading file" << e.what()<< endl;
//
//        }
//       return AirRoutesMap;
//    }
//
//
//    
//    static void printMap(map<string, vector<string>> thisMap){
//        for(auto &pair : thisMap){
//            cout << "[" << pair.first << "]" << " >> " << vecToString(pair.second) << endl;
//            cout << endl;
//        }
//    }
//    
//    static bool contains(deque<string> deq, string value){
//        deque<string>:: iterator itr;
//        itr = find(deq.begin(), deq.end(), value);
//        if(itr != deq.end()){
//            return true;
//        }
//        else
//            return false;
//    }
//
//    static bool vec_contains(vector<string> vec, string value){
//        if(std::find(vec.begin(), vec.end(), value) != vec.end()) {
//            return true;
//        }
//        else {
//            return false;
//        }
//    }
//    
//    
//    static string findRoute(string start_airport, string goal_airport){
//        
//        map<string, string> child_parent;
//        
//        cout << "start airport: " << start_airport << endl;
//        cout << "goal airport: " << goal_airport << endl;
//        
//        deque<string> frontier;
//        frontier.emplace_back(start_airport);
////        cout << "added parent " << start_airport << " to frontier " << endl;
//        vector<string> explored_set;
////        cout << "explored set: " << vecToString(explored_set) << endl;
//        
//        while(!frontier.empty()){
//            string parent = frontier.front();
//            frontier.pop_front();
////            cout << "popped parent, " << parent << endl;
//            child_parent.insert(pair<string, string> (parent, ""));
//            explored_set.emplace_back(parent);
////            cout << "added node to explored set, explored set: " << vecToString(explored_set) << endl;
//            
//            vector<string> successors = AirRoutesMap[parent];
//            if(!successors.empty()){
//                for (int i = 0; i < successors.size(); i++){
//                    string child = successors[i];
//                    child_parent.insert(pair<string, string> (child, parent));
////                    cout << "generated successor: " << child << endl;
//                    if (!vec_contains(explored_set, child) && (!contains(frontier, child))){
//                        if(child.compare(goal_airport) == 0){
////                            cout << "found goal: " << child << endl;
//                            cout << solution_path(child_parent, child);
//                            return solution_path(child_parent, child);
//                        }
//                    }
//                    frontier.emplace_back(child);
//                }
//                
//                
//            }
//            
//        }
//        return NULL;
//        
//    }
//    
//    static string solution_path(map<string, string> solution_map, string child){
//        vector<string> solution_path;
//        solution_path.emplace_back(child);
////        cout << vecToString(solution_path) << endl;
//        string parent = solution_map[child];
//        solution_path.emplace_back(parent);
////        cout << vecToString(solution_path) << endl;
//        while(parent != ""){
//            child = parent;
//            parent = solution_map[child];
//            solution_path.emplace_back(parent);
//        }
//        reverse(solution_path.begin(), solution_path.end());
//        return "flight route: " + vecToString(solution_path) + "\n";
//    }
//
//};
//
//map<string, vector<string>> Route::AirRoutesMap;

#endif /* routes_h_h */
