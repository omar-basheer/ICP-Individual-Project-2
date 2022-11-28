//
//  read_write_h.h
//  ReadWrite
//
//  Created by omar on 11/27/22.
//

#ifndef read_write_h_h
#define read_write_h_h

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

#include "airports_h.h"
#include "routes_h.h"

using namespace std;


class ReadWrite{
    
private:
    
    static string StartCity;
    static string StartCountry;
    static string Destination_City;
    static string Destination_Country;
    
public:
    
    static const string getStartCity(){
        return StartCity;
    }
    
    static const string getStartCountry(){
        return StartCountry;
    }
    
    static const string getDestination_City(){
        return Destination_City;
    }
    
    static const string getDestination_Country(){
        return Destination_Country;
    }
    
    static void setStartCity(string city){
        StartCity = city;
    }
    
    static void setStartCountry(string country){
        StartCountry = country;
    }
    
    static void setDestinationCity(string city){
        Destination_City = city;
    }
    
    static void setDestinationCountry(string country){
        Destination_Country = country;
    }
    

    static void inputFileReader(const string &input_filename){
        
        fstream inputStream;
        inputStream.open(input_filename);
        if(inputStream){
            cout << endl;
            cout << "> Reading input file..."<<endl;
            vector<string> splitline;
            string streamline, streamword, temp;
            
            while(getline(inputStream, streamline)){
                stringstream line_of(streamline);
                
                while(getline(line_of, streamword, ',')){
                    splitline.push_back(streamword);
//                    cout << streamword << endl;
                }
            }
            inputStream.close();
            cout << "> File read!"<<endl;

            
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

            for(auto const &pair : Airport::AirportMap){
                if(pair.first[1] == getStartCity() && pair.first[2] == getStartCountry()){
                    start_iata = pair.first[0];
                }
                if(pair.first[1] == Destination_City && pair.first[2] == Destination_Country){
                    goal_iata = pair.first[0];
                }
            }
        cout << endl;
        cout << "> Starting search..."<<endl;
        string flight_path;
        flight_path = Route::findRoute(start_iata, goal_iata);
        outputFileWriter(flight_path);
    }
    
    
    static void outputFileWriter(string flight_path){
        
        string file = "/Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/flight plan";
        ofstream outputStream (file);
        cout << endl;
        cout << "> Writing to output file..." << endl;
        
        vector<string> output;
        string delimiter = ", ";
        string substring;
        size_t pos = 0;
        while((pos = flight_path.find(delimiter)) != std::string::npos){
            substring = flight_path.substr(0, pos);
//            cout << substring << endl;
            output.emplace_back(substring);
            flight_path.erase(0, pos + delimiter.length());
        }
        output.emplace_back(flight_path);
        
        // print to file
        outputStream << " >> Flight Plan <<" << endl;
        for(int i = 1; i < output.size() - 1; i++){
            for(auto &pair : Route::AirlineRoutesMap){
//                cout<<"test2"<<endl;
                if(pair.first[1] == output[i]){
//                    cout<<pair.first[0] << " ";
                    string airline = pair.first[0];
                    outputStream << "flight "<< airline << " from " << output[i] << " to " << output[i+1] << endl;
                    break;
                }
            }
            
        }
        cout << "> Written to file!" << endl;


    }
    
};

string ReadWrite::StartCity;
string ReadWrite::StartCountry;
string ReadWrite::Destination_City;
string ReadWrite::Destination_Country;


#endif /* read_write_h_h */
