//
/* @file RouteMap.hpp */
//  Decription: A Class that reads a CSV file, creates cities 
//              out of the information, stores those cities in
//              the given pattern, can give you a route (if
//              possible) from a given starting City to a 
//              given destination City
//
// Created by Seth Spiegel on 6/23/20.
// Modified on 6/30/20

#ifndef RouteMap_hpp
#define RouteMap_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

#include "City.hpp"


class RouteMap
{

public:

    RouteMap() = default; //constructor


    //***************** MUTATOR FUNCTIONS ******************//
    
    
    /**
    @param input_file_name of a csv file representing a route map where the first
    line is a comma-separated list of city names, and the remainder is a
    comma-separated list of city-pairs of the form A-B, indicating that B
    is reachable from A
    (i.e. there is an arrow in the map going from A to B)
    @post this depends on your design, the input data representing the map must
    have been stored. Reachable cities must be stored and explored in the
    same order in which they are read from the input file
    **/
    bool readMap(std::string input_file_name);

    /**
    @param the name of a city
    @post creates a city with that name and adds it to cities_
    */
    void addCity(std::string name);

    /**
    @post takes the top City in the places_ stack, if there is 
    an attached, non-visited city, add it to the top of the 
    stack. If not, remove current top City.
    */
    bool travel();



    
    //******************ACCESSOR FUNCTIONS******************//


    /**
    @return a pointer to the city found at position, where
    0 <= position <= n-1, and n is the number of cities,
    and cities are stored in the same order in which they appear
    in the input file. Returns nullptr if city not found at position.
    **/
    City* getCity(size_t position);

    /**
    @return true if there is a route from origin to destination, 
      false otherwise
    @post if a route is found from origin to destination, it will 
      print it to standard output in the form “ORIGIN -> ... 
      -> DESTINATION\n”
    **/
    bool isRoute(City* origin, City* destination);


    vector<City> cities_;
    stack<City*> places_;
    size_t counter_;
    
}; //end RouteMap

#endif /* RouteMap_hpp */
