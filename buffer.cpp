#include "buffer.hpp"

Buffer::Buffer(const unsigned int size){
	this->size = size;
	this->counter = 0;
	this->maxPriority = 10;
	this->packageSize = 0;
}

Buffer::~Buffer(){}

bool Buffer::isFull(){
	return counter == size;
}

void Buffer::put(const Request& request){
	requests.push_back(request);
	lastToCome.push_back(request);
	sortBuffer();
	counter++;
}

Request Buffer::give(){
	Request chosen = requests.front();
	requests.pop_front();
	counter--;
	return chosen;
}

void Buffer::print(){
	for (auto v : requests){
        std::cout << "in buffer " << "\n";
        v.print();
	}
	std::cout << packageSize << std::endl;
	for (auto v : requests){
        std::cout << "in buffer sorted" << "\n";
        v.print();
	}
	setMaxPriority();
	createPackage();
	for (auto v : requests){
        std::cout << "in buffer package sorted" << "\n";
        v.print();
	}

}

void Buffer::setMaxPriority(){
	for(auto req : requests){
		if(req.getGenNumber() < maxPriority){
			maxPriority = req.getGenNumber();
		}
	}
	std::cout << "max priority: " << maxPriority << std::endl;
}

void Buffer::createPackage(){
	if (isFull()) {
		for(auto &req : requests){
			if (req.getGenNumber() == maxPriority){
				req.putInPriorityPackage();
				packageSize++;
			}
		}
	}
}

bool Buffer::isPackageEmpty(){
	return packageSize == 0;
}

void Buffer::sortBuffer(){
	requests.sort();
}


void Buffer::sortByTime(){
	requests.sort(Comparator());
}

void Buffer::printStatus(){
	std::cout << "size " << requests.size() << std::endl;
}

Request Buffer::lookInto(){
	return requests.front();
}

Request Buffer::getLastToCome(){
	return lastToCome.back();
}