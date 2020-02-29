#ifndef LEODB_FENCE_POINTERS_H
#define LEODB_FENCE_POINTERS_H

#include <unordered_map>
#include <data/entry.cpp>

// When we initialize our root.leodb file insert the following:
// [Current level, metadata offset, level 0, run 0
//int initRootValues = 4;
float initRoot[] = {0.0, 16.0, 0.0, 0.0};


template <class T, class U>
class FencePointer {
public:
    FencePointer();
    ~FencePointer() = default;
    void flushRun(Entry<T, U> data);
    void flushToFile();
    void pullFromFile();
    float getSize();
private:
//    void FencePointer<T, U>::createLevel();
    std::unordered_map<int, std::string> mapping;
    std::vector<Entry<T, T> > temp_flush;
    float totalEntries;
    int currentLevel;
    const char *pathToDatabase=".database";
    const char *pathToRoot=".database/root.leodb";
};


#endif //LEODB_FENCE_POINTERS_H
