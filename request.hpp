#ifndef REQUEST_H
#define REQUEST_H
#include "iostream"

class Request
{
public:
    Request(const int genNumber, const double time);
    bool isFirstToGo(const Request& request);
    void print();
    double getTime() const;
    int getGenNumber() const;
    void putInPriorityPackage();
    bool isInPackage() const;
    std::string toString() const;
    bool operator< (const Request& other);
    bool compareByTime(const Request& first, const Request& second);
    ~Request();
    
private:
    int genNumber;
    double time;
    bool inPriorityPackage;
};
#endif 
