#ifndef DEVICE_H
#define DEVICE_H

#include "request.hpp"
#include <cstdlib>


class Device
{
public:
	Device();
    void serve(const Request& request);
    bool isBusy(const Request& request);
    double getBusyTime();
    int getServedNumber();
    ~Device();
    
private:
    int servedRequests;
    double busyTime;
    double lambda;
};
#endif
