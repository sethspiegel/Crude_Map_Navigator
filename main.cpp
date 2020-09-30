//this main tests the Crude_MaP_Navigator program with both manual input and file input
#include "RouteMap.hpp"
#include "City.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{

RouteMap map;

//tests the program through manual input of cities and connections
/*
map.addCity("p"); //0
//map.addCity("q"); //1
//map.addCity("r"); //2
//map.addCity("s"); //3
//map.addCity("t"); //4
//map.addCity("w"); //5
//map.addCity("x"); //6
//map.addCity("y"); //7
//map.addCity("z"); //8
//
//map.getCity(0) -> addConnection(map.getCity(2));
//map.getCity(0) -> addConnection(map.getCity(5));
//map.getCity(1) -> addConnection(map.getCity(6));
//map.getCity(2) -> addConnection(map.getCity(6));
//map.getCity(3) -> addConnection(map.getCity(4));
//map.getCity(4) -> addConnection(map.getCity(5));
//map.getCity(5) -> addConnection(map.getCity(3));
//map.getCity(5) -> addConnection(map.getCity(7));
//map.getCity(7) -> addConnection(map.getCity(2));
//map.getCity(7) -> addConnection(map.getCity(8));
//
//map.isRoute(map.getCity(5), map.getCity(2));
*/

//tests the program with given CSV file
map.readMap("map.csv");
//std::cout << map.cities_.size() << std::endl;
//std::cout << map.cities_[0].getName() << std::endl;


map.isRoute(test_map.getCity(5), map.getCity(8));

//std::cout << map.cities_.size() << std::endl;
}
