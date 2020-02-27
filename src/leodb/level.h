#ifndef LEODB_LEVEL_H
#define LEODB_LEVEL_H


template <class T, class U>
class Level {
public:
    Level<T, U>(int _levelNumber);
    void addRun(std::vector<std::pair<int, Entry<T, U> > > run);
    int getTotalRuns() {return totalRuns;}
    int getRunThreshold() {return runThreshold}
private:
    int runThreshold;
    int levelNumber;
    int runThreshold;
    int totalRuns = 0;
};


#endif //LEODB_LEVEL_H
