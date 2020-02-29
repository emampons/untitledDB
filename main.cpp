//#include <iostream>
//#include <db.cpp>
//#include <data/entry.cpp>
//#include <data/key.cpp>
//#include <data/value.cpp>
#include <fence_pointer.cpp>


int main() {
    FencePointer<int, int> fp = FencePointer<int, int>();
    fp.flushRun(Entry<int, int>(Key<int>(1), Value(1)));
//    std::cout << fp.getSize();
}