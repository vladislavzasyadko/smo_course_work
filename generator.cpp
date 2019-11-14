#include "generator.hpp"
#include <ctime>
#include <qrandom.h>
#include "request.hpp"

Generator::Generator(const unsigned int number, const double alpha, const double beta){
	genNumber = number;
    currentTime = 0.0;
    this->beta = beta;
    this->alpha = alpha;
}

Request& Generator::generate(){
    double currentTime = (double(qrand()) / double(RAND_MAX)) * (this->beta - this->alpha) + this->alpha;
    Request *req = new Request(genNumber, currentTime);
	
	return *req;
}
	
