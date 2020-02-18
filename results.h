#ifndef RESULTS_H
#define RESULTS_H

#include<algorithm>

struct Results {
    int numberOfGenerators;
    int numberOfDevices;
    int bufferSize;
    std::vector<unsigned int> processed;
    std::vector<unsigned int> failed;
    std::vector<double> waitTimes;
    std::vector<double> processTimes;
    std::vector<double> failureProb;
    std::vector<double> dispOfWait;
    std::vector<double> dispOfProc;
    std::vector<double> deviceBusy;
};

#endif // RESULTS_H
