#include <iostream>
#include <fstream>
#include "level.h"

// Global Variables
std::string DIVIDER = "==========\n";
int RUNTHRESHOLD = 2;

template<class T, class U>
Level<T, U>::Level(int _levelNumber) {
    /*
     * Function constructor: Initialize our Level
     */
    levelNumber = _levelNumber;
    runThreshold = RUNTHRESHOLD;
    std::ofstream outfile ("tmp/" + std::to_string(levelNumber) + ".txt");
    outfile.close();
}

//template<class T, class U>
//void Level<T, U>::checkRuns() {
//    /*
//     * Function checkRuns: Check if we are above RUNTHRESHOLD and create new level
//     */
//    if (totalRuns >= runThreshold){
//
//    }
//}

template<class T, class U>
void Level<T, U>::addRun(std::vector<std::pair<int, Entry<T, U> > >run) {
    /*
     * Function addRun: Save run to memory and add run to our list of runs
     * Param &Run run: Sorted run to be added
     */
    // Save run to memory
    std::ofstream outfile ("tmp/" + std::to_string(levelNumber) + ".txt", std::ios_base::app);
    outfile << DIVIDER;
    for (auto pair: run) {
        outfile << std::to_string(pair.second.getKey().getItem()) + ":" + std::to_string(pair.second.getValue().getItem()) + "\n";
    }
    outfile.close();
    // Add pointer to run to our list of runs
//    runs.push_back(run);
    checkRuns();
    totalRuns++;
}