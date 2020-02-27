#include <iostream>
#include "key.h"
#include "db.h"
#include "value.h"
#include "value.cpp"
#include "db.cpp"
#include "entry.h"
#include "entry.cpp"

int main() {
    Key<int> one (5);
    Value<int> val (4);
    Key<int> two (6);
    Entry<int, int> hello(one,val);

    DB<int, int> db;
    for (int x = 0; x <= 22; x++){
        if (x % 2 == 0) {
            db.put(Key<int>(x), Value<int>(3));
        } else {
            db.put(Key<int>(x*2), Value<int>(3));
        }

    }
//    db.flushMemory();
//    std::cout << db.get(Key<int>(0)).getItem();

    return 0;
}