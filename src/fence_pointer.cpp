#include <fence_pointer.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#define countof(ARRAY) (sizeof (ARRAY) / sizeof *(ARRAY))

//void initRootFile() {
//    /*
//     * Function Status initRootFile: Initialize first level when we start up our database
//     */
//    // Path to Level and Run: .database/Level.Run.leodb
//    // Data in file: CurrentLevel$CurrentLevel$CurrentRun$
//    std::string init = "0$0$";
//    std::ofstream initLevel;
//    root_file.open (pathToRoot + "0.0.leodb");
//    // Build and push the info for the first level
//    initLevel << init;
//    initLevel.close();
//}


template <class T, class U>
FencePointer<T, U>::FencePointer() {
    /*
     * Function constructor: Pull/create our data from our database
     * Param string pathToFile
     */
    // Create pathToDatabase if it doesn't exists
    if (!std::filesystem::exists(pathToDatabase)) {
        int dir_err = mkdir(pathToDatabase, 0777);
        if (dir_err == -1 ) {
            std::cout << "[ERROR] Unable to make .database folder";
            throw 200;
        }
    }
    if (!std::filesystem::exists(std::string(pathToDatabase) + "/root.leodb")) {
        // We have to create our root file
        currentLevel = 0;
        std::ofstream root_file(std::string(pathToDatabase) + "/root.leodb", std::ios_base::binary);
        // Build and push the info for the first level
        for (float value : initRoot) {
            // Allocate a float size, copy over the values from our initRoot as a reference (i.e. &)
            std::cout << std::to_string(value);
            root_file << ((float *) &value, sizeof(float));
        }
        root_file.close();
    }
}

template <class T, class U>
void FencePointer<T, U>::flushRun(Entry<T, U> data) {
    /*
     * Function flushRun: Flush a vector is entries to memory
     * Param Entry data: Entry object to be processed
     */
    // Read root.leodb and create a new run
    float temp[8];
    FILE *root = fopen(pathToRoot, "rb");
    float *out;
    fread(out, 8, 1, root);
    float *num = (float) out;
//    size_t n = fread(data, sizeof(float), countof(temp), root);
    std::cout << num;


//    std::ifstream source(std::string(pathToDatabase) + "/root.leodb", std::ios_base::binary);
    // Get current level and metadata offset
//    float v;
//    fread((void*)(&v), sizeof(v), 1, std::string(pathToDatabase) + "/root.leodb")
//    float f;
//    std::cout << (float *) source.read(0, 8);
//    while (source.read(reinterpret_cast<char*>(&f), sizeof(float)))
//        std::cout << f << '\n';
    totalEntries++;
};

template <class T, class U>
void FencePointer<T, U>::flushToFile() {
    /*
     *  Function flushToFile: Flush our mapping to memory
     *  Param char pathToDatabase: Path to our database
     */

};

template <class T, class U>
void FencePointer<T, U>::pullFromFile(){
    /*
     *  Function flushToFile: Pull our mapping from memory. Assumes root.leodb exists
     *  Param char pathToDatabase: Path to root of our database, defaults to .database
     */


};

template <class T, class U>
float FencePointer<T, U>::getSize(){
    /*
     *  Function getSize: Return size of our database
     *  Returns float size: Size of our database
     */
    return totalEntries;
};
