#include "buffer.hpp"
#include <algorithm>    // std::sort


Buffer::Buffer(const unsigned int size){
	this->size = size;
	this->maxPriority = 10;
	this->packageSize = 0;
    this->lastRejected = "";
}

Buffer::~Buffer(){
    requests.clear();
}

bool Buffer::isFull(){
    return requests.size() == size;
}

bool Buffer::isEmpty()
{
    return requests.size() == 0;
}

void Buffer::put(const Request& request){
    requests.push_back(request);
    createPackage();
    sortBuffer();
}

int Buffer::putToFull(const Request& request){
    int rejectNumber;
    if(!(requests.back()< request)){
        std::cout << "request: " << requests.back().toString() <<
                     "has been kicked out by request: " <<request.toString() << std::endl;
        rejectNumber = requests.back().getGenNumber();
        lastRejected = requests.back().toString();
        requests.pop_back();
        put(request);
    }else{
        std::cout << "request denied: " << request.toString() << std::endl;
        rejectNumber = request.getGenNumber();
        lastRejected = request.toString();
    }
    return rejectNumber;
}

Request Buffer::give(){
	Request chosen = requests.front();
    //requests.pop_front();
    requests.erase(requests.begin());
    packageSize--;
	return chosen;
}

Request Buffer::lookInto(){
    Request chosen = requests.front();
    return chosen;
}

void Buffer::print(){
	createPackage();
    sortBuffer();
    std::cout << "##########BUFFER INFO#########" << std::endl;
    std::cout << "CURRENT SIZE :" << requests.size() << std::endl;


	for (auto v : requests){
        std::cout << "in buffer package sorted" << std::endl;

        v.print();
	}
    std::cout << "###############################" << std::endl;


}

void Buffer::setMaxPriority(){
    maxPriority = requests.begin()->getGenNumber();
	for(auto req : requests){
		if(req.getGenNumber() < maxPriority){
			maxPriority = req.getGenNumber();
		}
	}
    std::cout << "max priority: " << maxPriority << std::endl;
}

std::vector<std::string> Buffer::getState()
{
    std::vector<std::string> state;
    if(!requests.empty()){
        for(Request &request : requests){
            state.push_back(request.toString());
        }
    }else{
        state.push_back("empty");
    }
    return state;
}

std::string Buffer::getLastRejected()
{
    return lastRejected;
}

void Buffer::createPackage(){
    if (isPackageEmpty()) {
        setMaxPriority();
        for(requestIterator req = requests.begin(); req != requests.end(); req++){
            if (req->getGenNumber() == maxPriority){
                req->putInPriorityPackage();
				packageSize++;
			}
		}
    }
}

bool Buffer::isPackageEmpty(){
	return packageSize == 0;
}

void Buffer::sortBuffer(){
    std::sort(requests.begin(), requests.end());
}

void Buffer::printStatus(){
	std::cout << "size " << requests.size() << std::endl;
}

Request Buffer::getLastToCome(){
    return requests.back();
}
