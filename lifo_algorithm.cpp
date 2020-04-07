#include "lifo_algorithm.h"
#include "port.h"

void  Lifo_algorithm::get_instructions_for_crane(std::ofstream& output)  {
    //port->import_containers(ship);
    std::vector<Container> unload = port->get_containers_to(UNLOAD);
    std::vector<Container> priority_to_load;
    for (auto & it : unload) {
        if (*(it.get_dest()) == *port && it.is_on_board() == ON_BOARD) {
            port->import_container(ship, it, output, priority_to_load);
        }
    }

    //port->load_priority_containers(ship)
    for(auto& con : priority_to_load){
        ship->add_container(con,ship->find_first_free_spot());
        Port::write_instruction_to_file(output, LOAD, con.get_id(), ship->get_coordinate(con));
    }

    //port->load_containers(ship);
    //stack method
    std::vector<Container> load = port->get_containers_to(LOAD);
    std::vector<Port*> route = ship->get_route();
    std::stack<Container> stack;
    for (auto & route_it : route) {
        for (auto load_it = load.begin(); load_it != load.end(); ++load_it) {
            if (load_it->get_dest() == route_it) {
                stack.push(*load_it);
                load.erase(load_it);
            }
        }
    }
    // load to ship in order
    while (!stack.empty() && ship->has_space() && !(ship->has_weight_prob())) {
        Port::write_instruction_to_file(output, LOAD, stack.top().get_id(), ship->get_coordinate(stack.top()));
        port->load_to_ship(stack, ship);
    }

    //rejected containers
    while (!stack.empty()) {
        load.emplace_back(stack.top());
        Port::write_instruction_to_file(output, REJECT, stack.top().get_id(), ship->get_coordinate(stack.top()));
        stack.pop();
    }

}

const std::string Lifo_algorithm::getTypeName() const {
    return this->name;
}
