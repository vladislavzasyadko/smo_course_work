#include "step.h"

Step::Step()
{
    this->index = 0;
    this->size = 0;
}

Step::Step(const Step &step) :
        index(0),
        size(step.size),
        genState(step.genState),
        deniedRequests(step.deniedRequests),
        bufferState(step.bufferState),
        bufferAfterState(step.bufferAfterState),
        deviceState(step.deviceState)
{

}

Step::~Step()
{
    genState.clear();
    deniedRequests.clear();
    bufferState.clear();
    bufferAfterState.clear();
    deviceState.clear();
}

void Step::addGenState(std::string state)
{
    this->size++;
    genState.push_back(state);
}

void Step::addBufferState(std::vector<std::string> buffstate)
{
    bufferState.push_back(buffstate);
}

void Step::addBufferAfterState(std::vector<std::string> buffafterstate)
{
    bufferAfterState.push_back(buffafterstate);
}

void Step::addDeviceState(std::vector<std::string> devicestate)
{
    deviceState.push_back(devicestate);
}

void Step::addDeniedRequest(std::string denRequest)
{
    deniedRequests.push_back(denRequest);
}

void Step::increaseIndex()
{
    index++;
}

void Step::decreaseIndex()
{
    index--;
}

void Step::setIndex(int index)
{
    if(index < size){
        this->index = index;
    }else{
        this->index = 0;
    }
}

std::vector<std::string>& Step::getBufferState()
{
    return bufferState[index];
}

std::vector<std::string>& Step::getBufferAfterState()
{
    return bufferAfterState[index];
}

std::vector<std::string>& Step::getDeviceState()
{
    return deviceState[index];
}

std::string Step::getDeniedRequest()
{
    return deniedRequests[index];
}

std::string& Step::getGenState()
{
    return genState[index];
}

int Step::getSize(){
    return this->size;
}
