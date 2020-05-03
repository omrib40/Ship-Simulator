
#include "outputHandler.h"

/**
 * This function saves the results info of a certain travel route in a data structure
 * @param results_map - the data structure to save on the information
 * @param algVec - the algorithms that been tested in the simulation
 */
void saveResultsInfo(std::map<string,list<int>> &results_map,vector<std::unique_ptr<AbstractAlgorithm>> &algVec){
    for(auto& alg : algVec){
        //int num = alg->getInstructionsCounter(); //no such thing
        string name = typeid(*alg).name();
        if(results_map.find(name) != results_map.end()){
            //results_map.at(name).emplace_back(num);
        }
        else{
            std::list<int> ls;
            //ls.emplace_back(num);
            results_map.emplace(make_pair(name, ls));
        }
    }
}
//TODO: need to not rely on alg data such as route or functions & change to unique_ptr of AbsAlg
/**
// * This function saves all the error occurred in an algorithm into a list and returns it
// * errors exists in all ports that have containers left in their dock, and on the ship
// * @param alg - the algorithm to extract the errors from
// * @return - list of strings , each string is an informative error message
// */
//list<string> createAlgListOfErrors(Algorithm* alg){
//    auto route = alg->getShip()->getRoute();
//    std::set<string> visitedPorts;
//    list<string> res;
//    string msg;
//    /*Iterate on every port in the travel route, on each port check for any container left in it's dock*/
//    for(Port* p : route){
//        if(visitedPorts.find(p->get_name()) != visitedPorts.end()) continue;
//        visitedPorts.emplace(p->get_name());
//        vector<Container> containers_vec = *(p->getContainerVec('L'));
//        for(Container &cont : containers_vec){
//            msg = "Error: container id: " + cont.getId();
//            if(cont.getDest()->get_name() == "NOT_IN_ROUTE")
//                msg += " is not in ship's route";
//            else
//                msg += ", destPort: " + cont.getDest()->get_name() + ", currPort: " + p->get_name();
//            res.emplace_back(msg);
//        }
//    }
//    /*Iterate over the containers that left on the shipMap at the end of the travel*/
//    for(const auto &pair: alg->getShip()->getContainersByPort()){
//        vector<Container> vec = pair.second;
//        for(Container &cont : vec){
//            msg = "Error: container id: " + cont.getId() + ", destPort: " + cont.getDest()->get_name()
//                  + " on ship";
//            res.emplace_back(msg);
//        }
//    }
//    return res;
//
//}
//
///**
// * This function stores the Errors information
// */
//void saveErrorsInfo(vector<pair<string,list<pair<string,list<string>>>>> &errors_vec,
//                    vector<Algorithm *> &algVec,string &travelName){
//    list<pair<string,list<string>>> list_errors;
//    for(Algorithm* alg : algVec){
//        string name = alg->getTypeName();
//        list<string> alg_errorsList = createAlgListOfErrors(alg);
//        list_errors.emplace_back(make_pair(name,alg_errorsList));
//    }
//    errors_vec.emplace_back(make_pair(travelName,list_errors));
//}
/**
 * This function manges to save the errors and the results information in below data structures
 * @param results_map - stores results information
 * @param errors_vec - stores errors information
 * @param algVec - list of algorithms tested on
 * @param travelName - list of travel names tested on
 */
void saveOutputInformation(std::map<string,list<int>> &results_map,
                           vector<std::unique_ptr<AbstractAlgorithm>> &algVec, string &travelName){

    //saveResultsInfo(results_map,algVec);
}


///**
// * This function creates the outPutDirectories from list of paths.
// * @param paths
// * @param mainDirectory
// */
//void createOutputDirectories(std::vector<std::vector<fs::path>> &paths,char* mainDirectory){
//    string outputDir(mainDirectory);
//    outputDir.append(PATH_SEPARATOR);
//    outputDir.append(OP_MAIN_DIRECTORY);
//    fs::path dir(outputDir);
//    fs::path root_path(mainDirectory);
//    if(!fs::exists(dir) && !fs::create_directory(dir,root_path)){//Case we failed to create output directory.
//        std::cerr << "Error: failed to create output directory, exits program" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    for(auto const &list : paths) {
//        if (!list.empty()) {
//            string currOutputDir = outputDir + PATH_SEPARATOR + list[0].parent_path().filename().string() + "Out";
//            fs::path dir(currOutputDir);
//            fs::path root_path(outputDir);
//            if (!fs::exists(dir)) {
//                fs::create_directory(currOutputDir, outputDir);
//            }
//        }
//    }

//}
