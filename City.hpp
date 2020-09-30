//
/* @file City.hpp */
// Project 5
//Description: A base class that contains the values for a given
//             City's name, all available connections between 
//             that city and another, and whether it has been
//             visited before.
//
// Created by Seth Spiegel on 6/23/20.

#ifndef City_hpp
#define City_hpp

#include <string>
#include <vector>
using namespace std;

class City
{

public:

    City() = default; //default constructor

    /* Parameterized constructor
         @param name : the City's unique name (#duh)
    */
    City(string name);   


    //***************** MUTATOR FUNCTIONS ******************//

   
    /* @param: name will be the value of name_ */
    void setName(string name);

    /* @param: coonnections will be the value of connections_*/
    void addConnection(City* connections);

    void setAsVisited();


    //******************ACCESSOR FUNCTIONS******************//

    /* @return: name_*/
    string getName() const;

    /* @return: all conections in connections_*/
    std::string getAllConnections();

string name_;
int connection_counter_ = 0;
vector<City*> connections_;
bool visited_ = false;


}; //end City

#endif /* City_hpp */
