//
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


// Airport class: reads airports file and creates airport objects
class Airport{

/**
 Instance variables/fields
 */
private:
    
    string AirportName; // name of an airport
    string AirportCity;
    string Country;
    string IATA_Code;
    string ICAO_Code;
    string Airport_ID;
    

public:
    
    Airport(){
        this->AirportName = "";
        this->AirportCity = "";
        this->Country = "";
        this->IATA_Code = "";
        this->ICAO_Code = "";
        this->Airport_ID = "";
    }

    Airport(string airportName, string airportCity, string country, string iataCode, string icaoCode, string
    airportID){
        this->AirportName = airportName;
        this->AirportCity = airportCity;
        this->Country = country;
        this->IATA_Code = iataCode;
        this->ICAO_Code = icaoCode;
        this->Airport_ID = airportID;
    }



//    Airport(const string &airportName, const string &airportCity, const string &country, const string &iataCode,
//            const string &icaoCode, const string &airportId) : AirportName(airportName), AirportCity(airportCity),
//                                                               Country(country), IATA_Code(iataCode),
//                                                               ICAO_Code(icaoCode), Airport_ID(airportId) {}

    const string getAirportName() const {
        return AirportName;
    }

    const string getAirportCity() const {
        return AirportCity;
    }

    const string getCountry() const {
        return Country;
    }

    const string getIataCode() const {
        return IATA_Code;
    }

    const string getIcaoCode() const {
        return ICAO_Code;
    }

    const string getAirportId() const {
        return Airport_ID;
    }


    string const toString() const{
        return "Airport - [" + getAirportName() + ", " + getAirportCity() + ", " + getCountry() + ", " + getIataCode() + ", "
        + getIcaoCode() + ", " + getAirportId() + "]";
    }

    
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
    
    
    static map<vector<string>, Airport> AirportMap;

    static map<vector<string>, Airport>  AirportFileReader(const string &filename){

//        map<vector<string>, Airport> AirportMap;

        fstream inputStream;
        inputStream.open(filename);
        
        if(inputStream){
//            cout << "> file opened" << endl;
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

                if(!(splitline[4] == "\\N")){
//                    cout << "   >>>IATA not null: " << splitline[4] << endl;
                    vector<string> airportKey;
                    airportKey.emplace_back(splitline[4]);
                    airportKey.emplace_back(splitline[2]);
//                    cout << splitline[2] << endl;
                    airportKey.emplace_back(splitline[3]);
//                    cout << splitline[3] << endl;

                    Airport airport = Airport(splitline[1], splitline[2], splitline[3], splitline[4],
                                                   splitline[5], splitline[0]);
//                    cout << airport.toString() << endl;
//                    cout << endl;
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
    
    
    static void printMap(map<vector<string>, Airport> thisMap){
        for(auto const &pair : thisMap){
            cout << vecToString(pair.first) << " >> " << pair.second.toString() << endl;
        }
    }
    
};

map<vector<string>, Airport> Airport::AirportMap;


#endif /* airports_h_h */


//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <map>
//#include <sstream>
//
//using namespace std;
//
//
//// Airport class: reads airports file and creates airport objects
//class Airport{
//
///**
// Instance variables/fields
// */
//private:
//
//    string AirportName; // name of an airport
//    string AirportCity;
//    string Country;
//    string IATA_Code;
//    string ICAO_Code;
//    string Airport_ID;
//
//
//public:
//
//    Airport(){
//        this->AirportName = "";
//        this->AirportCity = "";
//        this->Country = "";
//        this->IATA_Code = "";
//        this->ICAO_Code = "";
//        this->Airport_ID = "";
//    }
//
//    Airport(string airportName, string airportCity, string country, string iataCode, string icaoCode, string
//    airportID){
//        this->AirportName = airportName;
//        this->AirportCity = airportCity;
//        this->Country = country;
//        this->IATA_Code = iataCode;
//        this->ICAO_Code = icaoCode;
//        this->Airport_ID = airportID;
//    }
//
////    Airport(const string &airportName, const string &airportCity, const string &country, const string &iataCode,
////            const string &icaoCode, const string &airportId) : AirportName(airportName), AirportCity(airportCity),
////                                                               Country(country), IATA_Code(iataCode),
////                                                               ICAO_Code(icaoCode), Airport_ID(airportId) {}
//
//    const string getAirportName() const {
//        return AirportName;
//    }
//
//    const string getAirportCity() const {
//        return AirportCity;
//    }
//
//    const string getCountry() const {
//        return Country;
//    }
//
//    const string getIataCode() const {
//        return IATA_Code;
//    }
//
//    const string getIcaoCode() const {
//        return ICAO_Code;
//    }
//
//    const string getAirportId() const {
//        return Airport_ID;
//    }
//
//
//    string const toString() const{
//        return "Airport - [" + getAirportName() + ", " + getAirportCity() + ", " + getCountry() + ", " + getIataCode() + ", "
//        + getIcaoCode() + ", " + getAirportId() + "]";
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
//
//
//    static map<vector<string>, Airport> AirportFileReader(const string &filename){
//
//        map<vector<string>, Airport> AirportMap;
////        cout << "> map created" << endl;
//
//        try{
//            fstream inputStream;
//            inputStream.open(filename);
//            inputStream.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
////            cout << "> file opened" << endl;
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
//                if(!(splitline[4] == "\\N")){
////                    cout << "   >>>IATA not null: " << splitline[4] << endl;
//                    vector<string> airportKey;
//                    airportKey.emplace_back(splitline[4]);
//                    airportKey.emplace_back(splitline[2]);
////                    cout << splitline[2] << endl;
//                    airportKey.emplace_back(splitline[3]);
////                    cout << splitline[3] << endl;
//
//                    Airport airport = Airport(splitline[1], splitline[2], splitline[3], splitline[4],
//                                                   splitline[5], splitline[0]);
////                    cout << airport.toString() << endl;
////                    cout << endl;
//                    AirportMap.insert(pair<vector<string>, Airport> (airportKey, airport));
//                }
//            }
//            inputStream.close();
//
//        }
//        catch(const exception &e) {
//            cout << "error opening/reading file" << e.what() << endl;
//        }
//
//        return AirportMap;
//    }
//
//    static void printMap(map<vector<string>, Airport> thisMap){
//        for(auto const &pair : thisMap){
//            cout << vecToString(pair.first) << " >> " << pair.second.toString() << endl;
//        }
//    }
//
//};
//
//
//
//
////int main() {
////
////    map<vector<string>, Airport> myAirportMap;
////    string airport_filename = "//Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/Airports/airports.csv";
////    myAirportMap = Airport::AirportFileReader(airport_filename);
////    Airport::printMap(myAirportMap);
////
////
////    return 0;
////}
