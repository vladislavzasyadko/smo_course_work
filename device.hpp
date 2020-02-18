#ifndef DEVICE_H
#define DEVICE_H

#include "request.hpp"
#include <cstdlib>
#include<algorithm>


class Device
{
public:
    Device();
    Device(const unsigned int number, const double lambda);

    void serve(const Request& request);
    bool isBusy(const Request& request);
    double getBusyTime();
    unsigned int getNumber();
    int getServedNumber();
    double getProcessTime();
    double getWorkTime();
    ~Device();
    
    std::string getState();
    void freeDevice();

private:
    int servedRequests;
    int checkedNumber;
    unsigned int number;
    double busyTime;
    double lambda;
    double workTime;
    double currentProcessTime;
    std::vector<Request> currentRequest;
};
#endif
