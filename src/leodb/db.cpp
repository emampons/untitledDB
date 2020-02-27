#include "db.h"
#include "entry.h"
#include "run.cpp"
#include "level.cpp"
#include "level.h"
#include <cmath>
#include <map>

// Global Variables
int INMEMORYTHRESHOLD = 10;

template<class T, class U>
DB<T, U>::DB() {
    /*
     * Function constructor: Initialize our DB
     */
    inMemoryThreshold = INMEMORYTHRESHOLD;
    runThreshold = RUNTHRESHOLD;
    levelMapping.push_back(currentLevel);
}

template<class T, class U>
bool DB<T, U>::put(Key<T> key, Value<U> value) {
    /*
     * Function put: Takes in a Key and Value and inserts into our db
     * Param Key key: Key to insert
     * Param Value value: Value to insert
     * Return: True/False if it was successful
     */
    int inserted = key.hashItem();
    if (table.count(inserted) == 0) {
        totalKeys += 1;
    }
    table[inserted] = Entry<T, U>(key, value);
    flushMemory();
    return true;
}


template<class T, class U>
bool DB<T, U>::del(Key<T> key) {
    /*
     * Function del: Delete a key from our DBMS
     * Param Key key: Key to use for lookup
     * Return: True/False if it was successful
     */
    bool ret = table.erase(key.hashItem());
    if (ret){
        totalKeys -= 1;
    }
    return ret;
}

template<class T, class U>
Value<U> DB<T, U>::get(Key<T> key) {
    /*
     * Function get: Get a Value from a Key in our DBMS
     * Param Key key: Key to use for lookup
     * Return: Value that was found or null if not found
     */
    try {
        return table[key.hashItem()].getValue();
    } catch (int e) {
        return Value<U>();
    }
}

template<class T, class U>
std::vector<Value<U> > DB<T, U>::scan(Key<T> low, Key<T> high) {
    /*
     * Function scan: Get a Value from a Key in our DBMS
     * Param Key low: Lower-bound to scan
     * Param Key high: Higher-bound to scan
     * Return: Vector of values related to Keys between low/high
     */
    std::vector<Value<U> > ret;

    for (auto pair: table)
    {
        Entry<T, U> entry = pair.second;
        //std::cout<<entry.getKey()<<"\n";
        if ((entry.getKey() >= low) && (entry.getKey() <= high))
            ret.push_back(entry.getValue());
    }
    return  ret;
}

template<class T, class U>
int DB<T, U>::min(bool keys){
    /*
     * Function min: Get the min value in our DBMS
     * Param bool key: Flag to indicate if we should search the keys or values
     * Return: Int representing the min value
     */
    int min = INT_MAX;
    if(keys){
        for(auto pair: table){
            Entry<T, U> entry = pair.second;
            if(entry.getKey() < min){
                min = entry.getKey();
            }
        }

    }else{
        for(auto pair: table){
            Entry<T, U> entry = pair.second;
            if(entry.getValue() < min){
                min = entry.getValue();
            }
        }
    }

    return min;
}

template<class T, class U>
int DB<T, U>::max(bool keys){
    /*
     * Function max: Get the max value in our DBMS
     * Param bool key: Flag to indicate if we should search the keys or values
     * Return: Int representing the max value
     */
    int max = INT_MIN;
    if(keys){
        for(auto pair: table){
            Entry<T, U> entry = pair.second;
            if(entry.getKey() > max){
                max = entry.getKey();
            }
        }

    }else{
        for(auto pair: table){
            Entry<T, U> entry = pair.second;
            if(entry.getValue() > max){
                max = entry.getValue();
            }
        }
    }

    return max;
}
//
template<class T, class U>
float DB<T, U>::avg(bool keys){
    /*
     * Function avg: Get the avg value in our DBMS
     * Param bool key: Flag to indicate if we should search the keys or values
     * Return: Float representing the average of all values
     */
    float running_sum = 0.0;
    for(auto pair: table){
        Entry<T, U> entry = pair.second;
        if (keys){
            running_sum += entry.getKey().getItem();
        } else {
            running_sum += entry.getValue().getItem();
        }
    }
    return (running_sum/ ((float) totalKeys));
}

template<class T, class U>
float DB<T, U>::stddev(bool keys){
    /*
     * Function stddev: Get the standard deviation for the data
     * Param bool key: Flag to indicate if we should search the keys or values
     * Return: Float representing the standard deviation of all values
     */
    // First get the average
    float average = avg(keys);

    // Loop over and sum the difference squared
    float running_sum = 0.0;
    for (auto pair: table) {
        Entry<T, U> entry = pair.second;
        if (keys) {
            running_sum += pow((entry.getKey().getItem() - average), 2);
        } else {
            running_sum += pow((entry.getValue().getItem() - average), 2);
        }
    }
    return sqrt(running_sum / ((float) totalKeys-1));
}

//template<class T, class U>
//bool comp() {
//
//    return a < b;
//}

template<class T, class U>
void DB<T, U>::flushMemory(){
    /*
    * Function flushMemory: Flush memory to disk if we are above inMemoryThreshold
    */
    if (totalKeys >= inMemoryThreshold) {
        struct {
            // Helper function to compare pairs
            bool operator()(const std::pair<int, Entry<T, U> > &a, const std::pair<int, Entry<T, U> > &b) const {
                return a.first < b.first;
            }
        } customLess;
        // Copy to vector and sort
        std::vector<std::pair<int, Entry<T, U> > > sorted(table.begin(), table.end());
        std::sort(sorted.begin(), sorted.end(), customLess);
        // Add to current level
        currentLevel.addRun(sorted);

        while (currentLevel.getTotalRuns() >= currentLevel.getRunThreshold()) {
            // Merge all the runs and push to next level

            // Move to the next level
            currentLevel = levelMapping[totalLevels]
        }
        // Reset our in-memory values
        table = std::unordered_map<int, Entry<T, U> >();
        totalKeys = 0;
    }
}
