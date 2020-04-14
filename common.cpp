
#include "common.h"

void execute(Ship* ship, char command, Container* container, coordinate origin, coordinate dest) {
    switch (command) {
        case 'L':
            ship->addContainer(*container, origin);
            break;
        case 'U':
            ship->removeContainer(origin);
            break;
        case 'M':
            ship->moveContainer(origin, dest);
            break;
        default:
            std::cout << "Invalid command, please insert L/U/M commands." << std::endl;
    }
}

void validateAlgorithm(std::string &path,Ship* simulatorShip){
void validateAlgorithm(string &outputPath,string &inputPath, Ship* simulatorShip, int portNumber){
    std::ifstream inFile;
    string line,id,instruction;
    std::pair<string,string> idAndInstruction;
    std::map<string,string> linesFromPortFile;
    inFile.open(outputPath);
    parseDataFromPortFile(linesFromPortFile, inputPath, simulatorShip);
    if(inFile.fail()) {
        cout << FAIL_TO_READ_PATH + outputPath << endl;
        return;
    }
    while(getline(inFile,line)){
        vector<int> coordinates;
        parseInstruction(line,idAndInstruction,coordinates);
        instruction = std::get<0>(idAndInstruction);
        id = std::get<1>(idAndInstruction);
        if(validateInstruction(instruction, id, coordinates, simulatorShip, linesFromPortFile)){
            coordinate one = std::tuple<int,int>(coordinates[0],coordinates[1]);
            if(instruction == "L") {
                Container* cont = new Container(id);
                execute(simulatorShip, instruction.at(0),cont, one, std::forward_as_tuple(-1, -1));
            }
            else if(instruction == "U"){
                execute(simulatorShip, instruction.at(0),nullptr, one, std::forward_as_tuple(-1, -1));
            }
            else{
                coordinate two = std::tuple<int,int>(coordinates[3],coordinates[4]);
                execute(simulatorShip, instruction.at(0), nullptr, one, two);
            }
        }

    }

    inFile.close();
}
void parseInstruction(string &toParse,std::pair<string,string> &instruction,vector<int> &coordinates){
    auto parsedInfo = Algorithm::stringSplit(toParse,delim);
    for(int i = 0; i < parsedInfo.size(); i++){
        if(i == 0)
            std::get<0>(instruction) = parsedInfo.at(0);
        else if(i == 1)
            std::get<1>(instruction) = parsedInfo.at(1);
        else
            coordinates.emplace_back(stoi(parsedInfo.at(i)));
    }
}

bool validateInstruction(string &instruction,string &id, vector<int> &coordinates,Ship* ship,std::map<string,string>& portContainers){
    int x1 = coordinates[0],y1 = coordinates[1], z1 = coordinates[2];
    auto map = ship->getMap();
    bool error;
    if(instruction == "L")
        error =  validateLoadInstruction(x1,y1,z1,*map);
    else if(instruction == "U")
        error =  validateUnloadInstruction(x1,y1,z1,*map);
    else if(instruction == "R")
        error = validateRejectInstruction(portContainers,id,ship);
    else{
        error = validateMoveInstruction(coordinates,*map);
    }
    return error;
}

bool validateRejectInstruction(std::map<string,string>& portContainers, string& id,Ship* ship){
    string line = portContainers[id];
    VALIDATION reason = VALIDATION::Valid;/*might be used in exercise 2 to be more specific*/
    bool err = validate(line,reason,id,ship);//true == bad
    if(err){
        /*need to add the error to the error general list*/
    }
    return !err;

}

bool validateLoadInstruction(int x,int y,int z,vector<vector<vector<Container>>>& map){
    if((map).at(x).at(y).size() != z)
        /*if not in size --> either in lower level which is wrong, or floating in the air*/
        return false;
    /*else if(check weight balance)
    To exercise 2 need to check also weight*/
    return true;
}

bool validateUnloadInstruction(int x,int y,int z,vector<vector<vector<Container>>>& map){
    if((map).at(x).at(y).size() != z)
        return false;
    /*else if(check weight calculator)
     * To exercise 2 need to check also weight*/
    return true;
}

bool validateMoveInstruction(vector<int> coordinates, vector<vector<vector<Container>>>& map){
    int x1 = coordinates[0], y1 = coordinates[1], z1 = coordinates[2];
    int x2 = coordinates[3], y2 = coordinates[4], z2 = coordinates[5];
    return !validateUnloadInstruction(x1, y1, z1, map) && !validateLoadInstruction(x2, y2, z2, map);
}

bool validateContainerData(const std::string& line, VALIDATION& reason, std::string& id, Ship* ship) {
    int i=-1;
    auto data = stringSplit(line, delim);

    if(data.size() != 4)
        return false;

    std::string port_name;

    for(const std::string& item : data){
        ++i;
        if (i == 0) {
            id = item;
            bool idBool = validateId(item);
            if(!idBool){
                reason = VALIDATION::InvalidID;
                return false;
            }
            else {
                if(idExistOnShip(item, ship)){
                    reason = VALIDATION::ExistID;
                    return false;
                }
            }
        }
        if(i == 1) {
            bool weight = is_number(item);
            if(!weight){
                return false;
            }
        }
        else if (i == 2) {
            port_name = item;
        }
        else if(i == 3){
            port_name += " " + item;
        }
    }
    bool dest = isValidPortName(port_name);
    if(!dest){
        reason = VALIDATION::InvalidPort;
        return false;
    }
    return true;
}


bool isValidPortName(const std::string& name){
    std::regex reg("\\s*[A-Z]{2}\\s+[A-Z]{3}s*$");
    return std::regex_match(name,reg);
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


/**
 * util function that split strings by a given delimiter
 * @param s - string to be splitted
 * @param delimiter - delimiters to be splitted by
 * @return vector of words in s
 */
std::vector<std::string> stringSplit(std::string s, const char* delimiter) {
    size_t start = 0;
    size_t end = s.find_first_of(delimiter);

    std::vector<std::string> output;

    while (end <= std::string::npos)
    {
        output.emplace_back(s.substr(start, end - start));

        if (end == std::string::npos)
            break;

        start = end + 1;
        end = s.find_first_of(delimiter, start);

        while(start == end){
            start = end + 1;
            end = s.find_first_of(delimiter, start);
        }
    }

    return output;
}


bool validateId(const std::string& str) {
    int i = 0;
    if (str.length() != 11)
        return false;
    for(auto letter : str){
        if(i < 3){ // owner code
            if(!isupper(letter)){
                return false;
            }
        }
        else if(i == 3){ // category identifier
            if (letter != 'U' && letter != 'J' && letter != 'Z'){
                return false;
            }
        }
        else { // serial number & check digit
            if(!isdigit(letter)){
                return false;
            }
        }
        ++i;
    }
    return true;
}

bool idExistOnShip(const std::string& id, Ship* ship){
    auto map = ship->getContainersByPort();
    for(auto & pPort : map){
        for(auto con_it : pPort.second) {
            if(con_it.get_id() == id){
                return true;
            }
        }
    }
    return false;
}


bool isPortInRoute(Port *pPort, const std::vector<Port*>& route, int portNum) {
    bool found = false;
    for(auto port_it = route.begin() + portNum + 1; port_it != route.end(); ++port_it){
        if(*(*port_it) == *pPort){
            found = true;
            break;
        }
    }
    return pPort->get_name() != "NOT_IN_ROUTE" && found;
}