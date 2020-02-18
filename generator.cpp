#include "generator.hpp"
#include "request.hpp"

Generator::Generator(){

}

Generator::Generator(const int number, const double alpha, const double beta){
    this->genNumber = number;
    this->currentTime = 0.0;
    this->beta = beta;
    this->alpha = alpha;
    this->numberOfProcessedRequests = 0;
    this->numberOfFailedRequests = 0;
    this->numberOfRequests = 0;
    this->timeOfWait = 0;
    this->timeOfProcess = 0;
    std::cout << "generator  numberr " << genNumber << std::endl;
}

Request& Generator::generate(){
    currentTime += (double(qrand()) / double(RAND_MAX))*(this->beta - this->alpha) + this->alpha;
    numberOfRequests++;
    Request *req = new Request(genNumber, currentTime);
	return *req;
}

//INCREMENTS NUMBER OF PROCESSED OR FAILED REQUESTS
void Generator::incrementProcessedRequests(){
    this->numberOfProcessedRequests++;
}
void Generator::incrementFailedRequests(){
    this->numberOfFailedRequests++;
}

void Generator::incrementTimeOfWait(double time){
    this->timeOfWait+=time;
}
void Generator::incrementTimeOfProcess(double time){
    this->timeOfProcess+=time;
}
//GETTER FOR NUMBER OF PROCESSED/FAILED REQUESTS

unsigned int Generator::getProcessedRequests(){
    return numberOfProcessedRequests;
}
unsigned int Generator::getFailedRequests(){
    return numberOfFailedRequests;
}
unsigned int Generator::getNumberOfRequests(){
    return numberOfRequests;
}

int Generator::getNumber(){
    return genNumber;
}

double Generator::getProbabilityOfFailure(){
    return static_cast<double>(numberOfFailedRequests)/static_cast<double>(numberOfRequests);
}

double Generator::getWaitTime(){
    if(timeOfWait>0){
        return timeOfWait/static_cast<double>(numberOfProcessedRequests);
   }
   return 0;
}

double Generator::getProcessTime(){
     return timeOfProcess/static_cast<double>(numberOfProcessedRequests);
}

Generator::~Generator(){

}

	
