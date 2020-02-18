#ifndef SMO_MANAGER_H
#define SMO_MANAGER_H
#include "generator.hpp"
#include "buffer.hpp"
#include "device.hpp"
#include "data.h"
#include "results.h"
#include "request.hpp"
#include "step.h"

class SMOManager
{
public:
    SMOManager(struct Data input);
    void initialize();
    void generateRequests();
    void start();
    ~SMOManager();

private:
    Buffer* buffer;
    Request* request;
    bool allChecked();
    void check();
    void renewCheckedStatus();
    void setSystemTime(const double time);

    typedef std::vector<Device>::iterator deviceIterator;

    void putRequestToServe();//будет передвигать указатель на свободный девайс

    std::vector<Request> requests;
    std::vector<Generator> generators;
    std::vector<Device> devices;

    std::vector<unsigned int> processedRequests;
    std::vector<unsigned int> failedRequests;
    std::vector<double> waitTimes;
    std::vector<double> processTimes;
    std::vector<double> failureProb;
    std::vector<double> dispOfWait;
    std::vector<double> dispOfProc;
    std::vector<double> deviceWorkPercent;

    int numberOfRequests;
    int numberOfGenerators;
    int numberOfDevices;
    int bufferSize;
    int checkedNumber;

    deviceIterator currentDevice;

    double maxSystemTime;
    double alpha;
    double beta;
    double lambda;
    double systemTime;

    bool foundFreeDevice;

    Results results;
    Step *steps;
public:
    Results returnResults();
    Step& returnSteps();
};

#endif // SMO_MANAGER_H
