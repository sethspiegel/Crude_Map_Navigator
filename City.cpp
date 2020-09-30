//
/* @file City.hpp */
//Description: A base class that contains the values for a given
//             City's name, all available connections between 
//             that city and another, and whether it has been
//             visited before.
//
// Created by Seth Spiegel on 6/23/20.

#include "City.hpp"

/* Parameterized constructor
     @param name : the City's unique name (#duh)
*/
City::City(string name) : name_(name){}  //end parameterized constructor   


//***************** MUTATOR FUNCTIONS ******************//


/* @param: name will be the value of name_ */
void City::setName(string name){
    name_ = name;
}

/* @param: add a new place to the end of connections_*/
void City::addConnection(City* place){
    City::connections_.push_back(place);
    connection_counter_++;
}

/* marks as been visited */
void City::setAsVisited(){
    visited_ = true;
}


//******************ACCESSOR FUNCTIONS******************//


/* @return: name_*/
string City::getName() const{
    return name_;
}

/* @return: all connections in connections_*/
std::string City::getAllConnections(){
    if (connection_counter_ > 0)
    {
        std::string connection_list_ = connections_[0] -> getName();
        for (int i = 1; i < connections_.size(); i++)
        {
            connection_list_ += ", ";
            connection_list_ += connections_[i] -> getName();
        }
        return connection_list_;    
    }
    else
    {
        return "";
    }
        
}







