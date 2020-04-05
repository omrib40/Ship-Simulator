/**
* This module represents a port
* each port has a:
* -name
* -containers:
*	# to load
*	# to unload
* -Instructions:
*	the number of crane moves executed at this port
*
*
*      *******      Functions      ******
*
* add_container - adds a container to port's list mentioned (containers to load / unload)
* remove_container - removes a container from port's list mentioned (containers to load / unload)
* print_containers - print all containers to load & unload assigned to this port
* add_instruction - adds +1 to instructions counter for crane move
* * get_name - returns the name of the port
* get_containers - returns a list of all the containers assigned to a port
*
*/
#ifndef PORT_HEADER
#define PORT_HEADER


#include <iostream>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include<stack>
#include "container.h"

#define REJECT "R"
#define UNLOAD "U"
#define LOAD "L"
#define MOVE "M"

class Container;
class Ship;

class Port {
    std::string name;
    std::vector<Container> load;
    std::vector<Container> unload;
    int instructions;
public:

    /*C'tor*/
    Port(const std::string& name) : name(name), instructions(0){}

    int add_container(const Container& container, const std::string& command);
    int remove_container(const Container& container, const std::string& command);
    void print_containers();
    void add_instruction();
    const std::string & get_name();
    std::vector<Container> get_containers_to(const std::string& command);
    bool operator==(const Port& p);
    void import_container(Ship* ship, Container& container, std::ofstream& output, std::vector<Container>& priority_to_load);
    static void load_to_ship(std::stack<Container>& stack, Ship* ship); //TODO crane management
    static void write_instruction_to_file(std::ofstream& output , const std::string& command, const std::string& id, const std::tuple<int,int,int>& pos);

    };
#endif