#ifndef REQUEST_H
#define REQUEST_H
#include "iostream"

class Request
{
public:
    Request(const unsigned int genNumber, const double time);
    bool isFirstToGo(const Request& request);
    void print();
    double getTime() const;
    unsigned int getGenNumber() const;
    void putInPriorityPackage();
    bool isInPackage();
    bool operator< (const Request& other);
    bool compareByTime(const Request& first, const Request& second);
    ~Request();
    
private:
    unsigned int genNumber;
    double time;
    bool inPriorityPackage;
};
#endif 
