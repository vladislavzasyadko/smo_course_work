#ifndef STEP_H
#define STEP_H

#include<algorithm>

#include <buffer.hpp>
#include <generator.hpp>
#include <device.hpp>

#include "bufferstate.h"
#include "devicestate.h"

class Step
{
public:
    Step();
    Step(const Step &step);
    ~Step();
    void addBufferState(std::vector<std::string> buffstate);
    void addBufferAfterState(std::vector<std::string> buffstate);
    void addGenState(std::string genState);
    void addDeviceState(std::vector<std::string> devicestate);
    void addDeniedRequest(std::string denRequest);

    void increaseIndex();
    void decreaseIndex();
    void setIndex(int index);
    void updateSystemTime();
    int getSize();

    std::vector<std::string>& getBufferState();
    std::vector<std::string>& getBufferAfterState();
    std::string& getGenState();
    std::vector<std::string>& getDeviceState();
    std::string getDeniedRequest();



private:
    //double systemTime;
    int index;
    int size;
    std::vector<std::string> genState;
    std::vector<std::string> deniedRequests;
    std::vector<std::vector<std::string>> bufferState;
    std::vector<std::vector<std::string>> bufferAfterState;
    std::vector<std::vector<std::string>> deviceState;
};

#endif // STEP_H
