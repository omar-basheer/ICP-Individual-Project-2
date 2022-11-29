///
//  airports_h.h
//  Airports
//
//  Created by omar on 11/20/22.
//
#ifndef airports_h_h
#define airports_h_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;


/**
 * # This class contains functions that read the airports.csv file and create airport objects. Each airport object stores data about a particular airport, including the country and city the airport is in and the airports global coordinates.
 */
class Airport{

private:
    
    string AirportName; // name of an airport
    string AirportCity; // city in which airport is located
    string Country;     // country in which airport is located
    string IATA_Code;   // airport iata code
    string Latitude;    // airport latitude
    string Longitude;   // airport longitude
    

public:
    
    /**
     * Default Airport object constructor
     */
    Airport(){
        this->AirportName = "";
        this->AirportCity = "";
        this->Country = "";
        this->IATA_Code = "";
        this->Latitude = "";
        this->Longitude = "";
    }

    
    /**
     * Contructor for an airport object
     * @param airportName the name of an airport
     * @param airportCity the city that airport is in
     * @param country  the country that aiport is in
     * @param iataCode  the iata code of the airport
     * @param latitude  the latitude of the airport
     * @param longitude the longitude of the airport
     * */
    Airport(string airportName,
            string airportCity,
            string country,
            string iataCode,
            string latitude,
            string longitude){
        this->AirportName = airportName;
        this->AirportCity = airportCity;
        this->Country = country;
        this->IATA_Code = iataCode;
        this->Latitude = latitude;
        this->Longitude = longitude;
    }
    
    
    static map<vector<string>, Airport> AirportMap;
    
    
    /**
     * Returns the name of an airport
     * @return name
     * */
    const string getAirportName() const {
        return AirportName;
    }

    /**
     * Returns the city of an airport
     * @return city
     * */
    const string getAirportCity() const {
        return AirportCity;
    }

    /**
     * Returns the country of an airport
     * @return country
     * */
    const string getCountry() const {
        return Country;
    }

    /**
     * Returns the iata code of an airport
     * @return iata code
     * */
    const string getIataCode() const {
        return IATA_Code;
    }

    /**
     * Returns the latitude of an airport
     * @return latitude
     * */
    const string getLatitude() const {
        return Latitude;
    }

    /**
     * Returns the longitude of an airport
     * @return longitude
     * */
    const string getLongitude() const {
        return Longitude;
    }

    /**
     * To string funsction for an airport
     * */
    string const toString() const{
        return "Airport - [" + getAirportName() + ", " + getAirportCity() + ", " + getCountry() + ", " + getIataCode() + ", "
        + getLatitude() + ", " + getLongitude() + "]";
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
        stream << "]";
        return stream.str();
    }

    /**
     * Print out the key value pairs of a given map
     * @param thisMap  a map of string vector keys and airport values
     */
    static void printMap(map<vector<string>, Airport> thisMap){
        for(auto const &pair : thisMap){
            cout << vecToString(pair.first) << " >> " << pair.second.toString() << endl;
        }
    }
    
    /**
     * Read Airport.csv file
     * @param filename  a csv file
     * @return a map with string vector keys of an airport name, city and iata code, and values of airport objects
     */
    static map<vector<string>, Airport>  AirportFileReader(const string &filename){

        fstream inputStream;
        inputStream.open(filename);
        
        if(inputStream){
            // cout << "> file opened" << endl;
            vector<string> splitline;
            string streamline, streamword, temp;

            while(getline(inputStream, streamline)){

                splitline.clear();
                stringstream line_of(streamline);
                // cout << "  >> got streamline" << endl;
                // cout << "   >> streamline: " << streamline << endl;

                while(getline(line_of, streamword, ',')){
                    splitline.push_back(streamword);
                    // cout << "   >> got streamword: " << streamword << endl;
                }

                if(!(splitline[4] == "\\N")){
                    // cout << "   >>>IATA not null: " << splitline[4] << endl;
                    vector<string> airportKey;
                    airportKey.emplace_back(splitline[4]);
                    airportKey.emplace_back(splitline[2]);
                    // cout << splitline[2] << endl;
                    airportKey.emplace_back(splitline[3]);
                    // cout << splitline[3] << endl;
                    // cout << vecToString(airportKey);

                    Airport airport = Airport(splitline[1], splitline[2], splitline[3], splitline[4],
                                                   splitline[6], splitline[7]);
                    // cout << airport.toString() << endl;
                    // cout << endl;
                    AirportMap.insert(pair<vector<string>, Airport> (airportKey, airport));
                }
                
            }
            inputStream.close();
            cout << "> Airports map created..."<<endl;
            
        }
    
        else{
            cout << "error opening/reading data file: check that the input file is in right directory and the given file name matches" << endl;
            }
        
        return AirportMap;
    }
    
    
};

map<vector<string>, Airport> Airport::AirportMap;


#endif /* airports_h_h */

