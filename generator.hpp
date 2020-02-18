#ifndef GENERATOR_H
#define GENERATOR_H

#include "request.hpp"
#include <cstdlib>
#include <qrandom.h>
#include <ctime>
#include <cmath>
#include <stdlib.h>

class Generator
{
public:
    Generator();
    Generator(const int number, const double alpha, const double beta);
    int getNumber();
    void incrementProcessedRequests();
    void incrementFailedRequests();
    void incrementTimeOfWait(double time);
    void incrementTimeOfProcess(double time);
    unsigned int getProcessedRequests();
    unsigned int getFailedRequests();
    unsigned int getNumberOfRequests();
    double getProbabilityOfFailure();
    double getWaitTime();
    double getProcessTime();
    Request& generate();
    ~Generator();
    
private:
    int genNumber;
    double currentTime;
    double alpha;
    double beta;

    unsigned int numberOfProcessedRequests;
    unsigned int numberOfFailedRequests;
    unsigned int numberOfRequests;

    double timeOfWait;
    double timeOfProcess;

};
#endif
