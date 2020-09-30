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

#include "RouteMap.hpp"


/**placeholder inputs*/
string name_line_, connection_line_, temp_string_;
int name_count_, connection_count_;
City* temp_city_ptr;

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
bool RouteMap::readMap(std::string input_file_name)
{
    std::ifstream read_(input_file_name); //open file

    /*check that the file is able to opened. if not, print error 
    message and exit the program*/
    if(!read_)
    {
        std::cout << "unable to read file";
        exit(1);
    }

    /*reads the file and extracts the 2 lines as substrings*/    
    std::getline(read_, name_line_); std::getline(read_, connection_line_);
    
    /*count how many names and connections there are*/
    for (size_t i = 0; i < name_line_.size(); i++)
    {
        if (name_line_[i] == ',')
        {
            name_count_++;
        }
    }

    for (size_t i = 0; i < connection_line_.size(); i++)
    {
        if (connection_line_[i] == ',')
        {
            connection_count_++;
        }
    }

    /*should take each name, create a class with that name, add
    add that class to the vector*/
    for (int i = 0; i < name_count_; i++)
    {
        std::size_t break_ = name_line_.find(',');
        std::string name_ = name_line_.substr(0, break_);
        addCity(name_);
        name_line_ = name_line_.substr(break_+1);
    }
    addCity(name_line_); //add last city after last comma
       

    /*should take each connection, find the City with the name 
    before the '-', add the name of the City after to its
    connection*/
    for (int i = 0; i < connection_count_; i++)
    {        
        std::size_t break_full_ = connection_line_.find(',');
        std::string full_ = connection_line_.substr(0, break_full_);
        std::size_t break_part_ = full_.find('-');
        std::string city_name_ = full_.substr(0, break_part_);
        std::string connection_name_ = full_.substr(break_part_+1);
        connection_line_ = connection_line_.substr(break_full_+1);

        int og_place_, cn_place_;
        bool og = false;
        bool cn = false;

        /**need to find name in vector, access it through pointer
        add connectin to vector
        */
        for(int i = 0; i < cities_.size(); i++)
        {
           if(cities_[i].getName() == city_name_)
           {
                og = true;
                og_place_ = i;
           }
            else if (cities_[i].getName() == connection_name_)
            {
                cn = true;
                cn_place_ = i;
            }
        }

        if(og && cn) //if both names actually exist in cities_
        {
            cities_[og_place_].addConnection(&cities_[cn_place_]);
        }
    }
    
    /**do again for last entry after last comma*/
    std::size_t break_part_ = connection_line_.find('-');
    std::string city_name_ = connection_line_.substr(0, break_part_);
    std::string connection_name_ = connection_line_.substr(break_part_+1);

    int og_place_, cn_place_;
    bool og = false;
    bool cn = false;

    /**need to find name in vector, access it through pointer
    add connectin to vector
    */
    for(int i = 0; i < cities_.size(); i++)
    {
        if(cities_[i].getName() == city_name_)
        {
            og = true;
            og_place_ = i;
        }
        else if (cities_[i].getName() == connection_name_)
        {
            cn = true;
            cn_place_ = i;
        }
    }

    if(og && cn)
    {
        cities_[og_place_].addConnection(&cities_[cn_place_]);
    }
    
    return true;
}

/**
@param a name of a new city
@post creates that city and adds it to cities_
*/
void RouteMap::addCity(std::string name)
{
    City temp_city_;
    temp_city_.setName(name);
    cities_.push_back(temp_city_);
}




/**
@post takes the top City in the places_ stack, if there as an 
attached, non-visited city, add it to the top of the 
stack. If not, remove current top City.
*/
bool RouteMap::travel()
{
    for (int i = 0; i < places_.top() -> connection_counter_; i++)
    {
        if(places_.top() -> connections_[i] -> visited_ == false)
        {
            places_.push(places_.top() -> connections_[i]);
            places_.top() -> setAsVisited();
            return true;
        }        
    }

    //if no non-visited connections were found
    places_.pop();
    return true;
}



    
//******************ACCESSOR FUNCTIONS******************//


/**
@return a pointer to the city found at position, where
0 <= position <= n-1, and n is the number of cities,
and cities are stored in the same order in which they appear
in the input file. Returns nullptr if city not found at position.
**/
City* RouteMap::getCity(size_t position)
{
    if(position <= cities_.size())
    {
        temp_city_ptr = &cities_[position];
        return temp_city_ptr;
    }
    else
    {
        //std::cout << "selected city position is too large" << std::endl;
        return nullptr;
    }
    
}

/**
@return true if there is a route from origin to destination, false otherwise
@post if a route is found from origin to destination, it will print it to
standard output in the form “ORIGIN -> ... -> DESTINATION\n”
**/
bool RouteMap::isRoute(City* origin, City* destination)
{
    /**check that both the origin and the destination exist within
    the vector*/
    bool og_exists = false;
    bool dn_exists = false;
    for (int i = 0; i < cities_.size(); i++)
    {
        if (origin -> getName() == cities_[i].getName())
        {
            og_exists = true;
        }
        else if (destination -> getName() == cities_[i].getName())
        {
            dn_exists = true;
        }   
    }
    
    /**push the name of the origin into the stack*/
    if (og_exists == true && dn_exists == true)
    {
        origin -> setAsVisited();
        places_.push(origin);

        /**stop if the stack is ever empty or the destination is 
        reached*/
        while (!places_.empty())
        {
            /**if the destination is reached*/
            if (places_.top() -> getName() == destination -> getName())
            {
                /**reverse order for printing*/
                stack<string> print_stack_;
                while (!places_.empty())
                {
                    print_stack_.push(places_.top()->getName());
                    places_.pop();
                }

                string print_string_ = print_stack_.top();
                print_stack_.pop();
                while (!print_stack_.empty())
                {
                    print_string_ += " -> ";
                    print_string_ += print_stack_.top();
                    print_stack_.pop();
                }
                std::cout << print_string_ << std::endl;
                return true;
            }
            else
            {
                travel();
            }      
        }

        /**if stack is empty*/
        //std::cout << "no route found" << std::endl;
        return false;    
    }

    else if (og_exists == false)
    {
        //std::cout << "origin does not exist" << std::endl;
        return false;
    }
    else if (dn_exists == false)
    {
        //std::cout << "destination does not exist" << std::endl;
        return false;
    } 
    else
    {
        //std::cout << "error in isRoute" << std::endl;
        return false;
    }
}

