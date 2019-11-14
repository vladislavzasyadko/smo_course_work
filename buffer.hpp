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
    void put(const Request& request);
    void sortBuffer();
    void sortByTime();
    bool compareByTime(const Request& first, const Request& second);
    void take();
    Request give();
    Request lookInto();
    void print();
    void createPackage();
    bool isPackageEmpty();
    void setMaxPriority();
    Request getLastToCome();
    void printStatus();
    struct Comparator{
	// Compare 2 Player objects using name
	bool operator ()(const Request & player1, const Request & player2)
	{
		if(player1.getTime() == player2.getTime())
			return player1.getGenNumber() < player2.getGenNumber();
		return player1.getTime() < player2.getTime();
 
	}
	};
    ~Buffer();
    
private:
	std::list<Request> requests;
    unsigned int size;
    unsigned int counter;
    unsigned int maxPriority;
    unsigned int packageSize;
    std::list<Request> lastToCome;
};
#endif
