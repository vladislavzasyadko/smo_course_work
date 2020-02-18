#include <qrandom.h>
#include "device.hpp"
#include "ctime"

Device::Device(){
}
Device::Device(const unsigned int number, const double lambda){
	this->servedRequests = 0;
    this->number = number;
    this->lambda = lambda;
    this->busyTime = 0;
    this->workTime = 0;
    this->currentProcessTime = 0;
}

Device::~Device(){}

void Device::serve(const Request& request){
    double work  = (log(qrand() + 1) - log(RAND_MAX)) / -(this->lambda);
    currentProcessTime = work;
    std::cout << this->getNumber() << " device FORMULA GENERATED THIS TIME AS SERVE TIME " << work << std::endl;
    workTime+=work;
    std::cout << "busytime was " << busyTime << " work time is " << work << std::endl;
    busyTime = request.getTime() > busyTime? request.getTime() + work : busyTime + work;
    std::cout << "now busytime is " << busyTime << std::endl;
    std::cout << "request num: " << request.getGenNumber() << " is served " << std::endl;

	servedRequests++;
    currentRequest.clear();
    currentRequest.push_back(request);
}

double Device::getProcessTime(){
    return currentProcessTime;
}

bool Device::isBusy(const Request& request){
	std::cout << "req time " << request.getTime()
	 << " im busy until " << busyTime << std::endl; 
	return request.getTime() < busyTime;
}

double Device::getWorkTime(){
    return workTime;
}

double Device::getBusyTime(){
	return busyTime;
}

int Device::getServedNumber(){
	return servedRequests;
}

unsigned int Device::getNumber(){
    return number;
}

void Device::freeDevice(){
    currentRequest.clear();
}

std::string Device::getState(){
    if(!currentRequest.empty()){
        return currentRequest[0].toString() + " " + std::to_string(busyTime);
    }else {
        return "free";
    }
}



