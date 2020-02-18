#ifndef BUFFER_H
#define BUFFER_H

#include "request.hpp"
#include <cstdlib>
#include <list>
#include<algorithm>


class Buffer
{
public:
    Buffer(const unsigned int size);
    bool isFull();
    bool isEmpty();

    void put(const Request& request);
    int putToFull(const Request& request);
    Request give();
    Request lookInto();
    void sortBuffer();
    void print();
    void createPackage();
    bool isPackageEmpty();
    void setMaxPriority();
    std::vector<std::string> getState();
    std::string getLastRejected();

    Request getLastToCome();
    void printStatus();
    struct Comparator{
    // Compare 2 objects using time
    bool operator ()(const Request & request1, const Request & request2)
	{
        if(request1.getTime() == request2.getTime())
            return request1.getGenNumber() < request2.getGenNumber();
        return request1.getTime() < request2.getTime();
	}
	};
    ~Buffer();
    
private:
    typedef std::vector<Request>::iterator requestIterator;
    std::vector<Request> requests;
    std::string lastRejected;

    unsigned int size;
    unsigned int maxPriority;
    unsigned int packageSize;

};
#endif
