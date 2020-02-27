#ifndef LEODB_DB_H
#define LEODB_DB_H

#include <unordered_map>
#include "key.h"
#include "value.h"
#include "entry.h"
#include "level.h"

template <class T, class U>
class DB {
public:
    DB();
    bool put(Key<T> key, Value<U> value);
    bool del(Key<T> key);
    Value<U> get(Key<T> key);
    std::vector<Value<U> > scan(Key<T> low, Key<T> high);
    int min(bool keys=true);
    int max(bool keys=true);
    float avg(bool keys=true);
    float stddev(bool keys=true);

    void flushMemory();

private:
    std::unordered_map<int, Entry<T, U> > table;
    int totalKeys;
    int inMemoryThreshold;
    int runThreshold;
    int totalLevels = 0;
    Level<T, U> currentLevel = Level<T, U>(0);
    std::vector<std::pair<int, Level<T, U> > > levelMapping;
    // maybe some more stuff...
};

#endif //LEODB_DB_H
