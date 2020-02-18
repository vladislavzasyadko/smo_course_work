#include "request.hpp"

Request::Request(const int genNumber, const double time){
	this->genNumber = genNumber;
	this->time = time;
	this->inPriorityPackage = false;
    std::cout << "request gen number " << genNumber << std::endl;
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

int Request::getGenNumber() const{
	return genNumber;
}

bool Request::isInPackage() const{
	return inPriorityPackage;
}

void Request::putInPriorityPackage(){
	this->inPriorityPackage = true;
	std::cout << "req " << genNumber << ":"<< time <<" is " << inPriorityPackage << std::endl;
}

bool Request::operator< (const Request& other){
//    сортируем сначала по приоритетному пакету,
//            потом по номеру источника, тк он влияет на выборку в
//            приоритетный пакет
//            потом уже сортируем по времени заявки от одного источника
    if(isInPackage()&&!other.inPriorityPackage){
        return true;
    }else if(!isInPackage()&&other.inPriorityPackage) {
        return false;
    }else{
	if(genNumber == other.genNumber){
		return time < other.time;
	}else {
		return genNumber < other.genNumber;
	}
    }
}

bool Request::compareByTime(const Request& first, const Request& second){ 
	return first.time < second.time; 
}

std::string Request::toString() const{
    if(this->isInPackage()){
        return std::to_string(genNumber) + " " + std::to_string(time) + " +";
    }else{
        return std::to_string(genNumber) + " " + std::to_string(time);
    }
}
    

Request::~Request(){}
