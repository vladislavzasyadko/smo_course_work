#include <qrandom.h>
#include "device.hpp"

Device::Device(){
	this->servedRequests = 0;
}

Device::~Device(){}

void Device::serve(const Request& request){
    double serveTime = (log(qrand() + 1) - log(RAND_MAX) / -this -> lambda);
	busyTime += serveTime + request.getTime();
	std::cout << "request num: " << request.getGenNumber() << "served" << std::endl;
	servedRequests++;
}

bool Device::isBusy(const Request& request){
	std::cout << "req time " << request.getTime()
	 << " im busy until " << busyTime << std::endl; 
	return request.getTime() < busyTime;
}

double Device::getBusyTime(){
	return busyTime;
}

int Device::getServedNumber(){
	return servedRequests;
}

