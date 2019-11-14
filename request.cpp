#include "request.hpp"

Request::Request(const unsigned int genNumber, const double time){
	this->genNumber = genNumber;
	this->time = time;
	this->inPriorityPackage = false;
}

bool Request::isFirstToGo(const Request& request){
	if(genNumber > request.genNumber){
		std::cout << "first is by gen number" << std::endl;
		return false;
	} else if(genNumber == request.genNumber && time > request.time){
		std::cout << "first is by time" << std::endl;
		return false;
	}
	return true;
}

void Request::print(){
	std::cout << "request from Gen: " << genNumber
	<< " request time: " << time << "in package: "<< inPriorityPackage << std::endl;
}

double Request::getTime() const{
	return time;
}

unsigned int Request::getGenNumber() const{
	return genNumber;
}

bool Request::isInPackage(){
	return inPriorityPackage;
}

void Request::putInPriorityPackage(){
	this->inPriorityPackage = true;
	std::cout << "req " << genNumber << ":"<< time <<" is " << inPriorityPackage << std::endl;
}

bool Request::operator< (const Request& other){
	if(genNumber == other.genNumber){
		return time < other.time;
	}else {
		return genNumber < other.genNumber;
	}
}

bool Request::compareByTime(const Request& first, const Request& second){ 
	return first.time < second.time; 
}
    

Request::~Request(){}
