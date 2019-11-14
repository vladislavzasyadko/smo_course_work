#ifndef GENERATOR_H
#define GENERATOR_H

#include "request.hpp"
#include <cstdlib>


class Generator
{
public:
    Generator(const unsigned int number, const double alpha, const double beta);
    Request& generate();
    ~Generator();
    
private:
    unsigned int genNumber;
    double currentTime;
    double alpha;
    double beta;
};
#endif
