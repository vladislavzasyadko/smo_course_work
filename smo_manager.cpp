#include "smo_manager.h"

SMOManager::SMOManager(struct Data input){
    this->steps = new Step();
    this->alpha = input.alpha;
    this->beta = input.beta;
    this->lambda = input.lambda;
    this->numberOfRequests = input.numberOfRequests;
    this->numberOfGenerators = input.numberOfGenerators;
    this->numberOfDevices = input.numberOfDevices;
    this->bufferSize = input.bufferSize;
    if(bufferSize == 0 || numberOfDevices == 0 || beta == 0.0
            || numberOfRequests == 0 || numberOfGenerators == 0){
        std::cout << "Simulation won't start, BECAUSE:" << std::endl;
        std::cout << bufferSize << " " << numberOfDevices <<
                     " " << beta << " " << alpha << " " << lambda <<
                     " " << numberOfRequests << " " << numberOfGenerators << std::endl;

    }
    this->checkedNumber = 0;
    this->systemTime = 0;
}

void SMOManager::initialize(){
    generators.resize(static_cast<unsigned long>(this->numberOfGenerators));
    processedRequests.resize(static_cast<unsigned long>(this->numberOfGenerators));
    waitTimes.resize(static_cast<unsigned long>(this->numberOfGenerators));
    failureProb.resize(static_cast<unsigned long>(this->numberOfGenerators));
    processTimes.resize(static_cast<unsigned long>(this->numberOfGenerators));
    dispOfWait.resize(static_cast<unsigned long>(this->numberOfGenerators));
    dispOfProc.resize(static_cast<unsigned long>(this->numberOfGenerators));
    deviceWorkPercent.resize(static_cast<unsigned long>(this->numberOfDevices));

    failedRequests.resize(static_cast<unsigned long>(this->numberOfGenerators));
    devices.resize(static_cast<unsigned long>(this->numberOfDevices));

    //std::cout << generators.size() << " generators.size"<< std::endl;
    unsigned int number = 1;

    for(std::vector<int>::size_type i = 0; i != generators.size(); i++){
        std::cout << number << " gen number"<< std::endl;
        generators[i] = *new Generator(number, this->alpha, this->beta);
        number++;
    }

    //std::cout << devices.size() << " devices.size" << std::endl;
    number = 1;
    for(std::vector<int>::size_type i = 0; i != devices.size(); i++){
        devices[i] = *new Device(number, this->lambda);
        number++;
    }

    buffer = new Buffer(static_cast<unsigned int>(this->bufferSize));

    foundFreeDevice = false;
    currentDevice = devices.begin();
}

void SMOManager::generateRequests(){
    //generating all requests

    int generatedRequests = 0;
    std::cout << numberOfRequests << " requestCount" << std::endl;
    while(generatedRequests < numberOfRequests){
        for(std::vector<int>::size_type i = 0; i != generators.size(); i++){
            requests.push_back(generators[i].generate());

            generatedRequests++;

            if(generatedRequests == numberOfRequests){
                break;
            }
        }
        sort(requests.begin(), requests.end(), [](Request &req1, Request &req2) {
            return req1.getTime() < req2.getTime();
        });
    }
    std::cout << numberOfRequests << " request count" << generatedRequests << " gen requests" << std::endl;
    std::cout << requests.size()<< " request.size" << std::endl;

    for(auto request : requests){
        std::cout << request.toString() << std::endl;
    }
}

void SMOManager::start(){
    for(auto &request : requests){
        setSystemTime(request.getTime());
        //Проверяем что на момент времени генерации заявки приборы освобождены если время обработки меньше
        for(int i = 0; i < numberOfDevices; i++){
            if(devices[i].getBusyTime()<systemTime){
                devices[i].freeDevice();
            }
        }
        if(!buffer->isEmpty()){
            putRequestToServe();
        }
        //СОСТОЯНИЕ ЗАЯВКА СГЕНЕРИРОВАНА
        steps->addGenState(request.toString());
        //std::cout << steps->getGenState() << " ЗАЯВКА СГЕНЕРИРОВАНА"<<std::endl;
        if(!buffer->isFull()){
            buffer->put(request);
            steps->addDeniedRequest(" ");
        }else{
            //buffer->putToFull(request);
            generators[buffer->putToFull(request)-1].incrementFailedRequests();
            steps->addDeniedRequest(buffer->getLastRejected());
        }
        buffer->print();
        //СОСТОЯНИЕ ЗАЯВКА ПОШЛА В БУФЕР ИЛИ ОТКАЗ
        steps->addBufferState(buffer->getState());
        std::cout << steps->getBufferState()[0] << " ЗАЯВКА В БУФЕРЕ"<<std::endl;
        putRequestToServe();
        //СОСТОЯНИЕ ЗАЯВКА ПОШЛА НА ПРИБОР

        renewCheckedStatus();
        foundFreeDevice = false;
        std::vector<std::string> tempState;
        for(auto device : devices){
            tempState.push_back(device.getState());//кладем состояния всех девайсов

        }
        steps->addDeviceState(tempState);
        steps->addBufferAfterState(buffer->getState());


        //указатель на текущий девайс
        //передвигается как только мы кладем в предыдущий заявку или если предыдущий занят
        //пока не найдем свободный
    }

    while(!buffer->isEmpty()){
        steps->addGenState("empty");
        steps->addDeniedRequest(" ");
        steps->addBufferState(buffer->getState());

        putRequestToServe();


        renewCheckedStatus();
        foundFreeDevice = false;
        std::vector<std::string> tempState;
        for(auto device : devices){
            tempState.push_back(device.getState());//кладем состояния всех девайсов
            if(device.getBusyTime() > systemTime){
                systemTime = device.getBusyTime();
            }
        }
        steps->addDeviceState(tempState);
        steps->addBufferAfterState(buffer->getState());

    }

    buffer->printStatus();
    buffer->print();

//    countingStuff()
    for(auto gen : generators){
        std::cout << "GENERATOR " << gen.getNumber()-1 << std::endl;
        std::cout << "ALL REQS " << gen.getNumberOfRequests() << std::endl;
        std::cout << "PROCESSED " << gen.getProcessedRequests() << std::endl;
        std::cout << "DENIED " << gen.getFailedRequests() << std::endl;
        std::cout << "TIME OF WAIT " << gen.getWaitTime() << std::endl;
        std::cout << "TIME OF PROCESS " << gen.getProcessTime() << std::endl;

        processedRequests[gen.getNumber()-1] = gen.getProcessedRequests();
        std::cout << "processed "<< gen.getProcessedRequests() << std::endl;
        failedRequests[gen.getNumber()-1] = gen.getFailedRequests();
        waitTimes[gen.getNumber()-1] = gen.getWaitTime();
        processTimes[gen.getNumber()-1] = gen.getProcessTime();
        failureProb[gen.getNumber()-1] = gen.getProbabilityOfFailure();
        double Mxx = 0;
        for(int i = 0; i < waitTimes.size(); i++){
            Mxx+=pow(waitTimes[i], 2);
        }
        double MxMx = 0;
        for(int i = 0; i < waitTimes.size(); i++){
            MxMx+=waitTimes[i];
        }

        dispOfWait[gen.getNumber()-1] = Mxx/gen.getProcessedRequests() - pow(MxMx/gen.getProcessedRequests(),2);

        Mxx = 0;
        for(int i = 0; i < processTimes.size(); i++){
            Mxx+=pow(processTimes[i], 2);
        }
        MxMx = 0;
        for(int i = 0; i < processTimes.size(); i++){
            MxMx+=processTimes[i];
        }

        dispOfProc[gen.getNumber()-1] = Mxx/gen.getProcessedRequests() - pow(MxMx/gen.getProcessedRequests(),2);


        //std::cout << "  DISPERSION OF WAIT " << Dx << std::endl;
        std::cout << "failed "<<gen.getFailedRequests() << std::endl;
        std::cout << "all "<< gen.getNumberOfRequests() << std::endl;
        std::cout << " percent processed" << static_cast<double>(gen.getProcessedRequests())/static_cast<double>(gen.getNumberOfRequests()) << std::endl;
    }
    for(auto device : devices){
        deviceWorkPercent[device.getNumber()-1] = device.getWorkTime()/systemTime;
    }

}

void SMOManager::putRequestToServe(){
    //allChecked() условие что прошли все девайсы
    if(allChecked()){
        std::cout << "All Busy trying again!" << std::endl;
    }else{
        for(deviceIterator device = currentDevice;  device != devices.end(); device++){
            checkedNumber++;
            if(device->getBusyTime() <= systemTime){

                //INFO ABOUT TAKEN REQUEST
                std::cout <<"current device: " << currentDevice->getNumber()
                          <<"device number: " << device->getNumber()
                          <<"took request: ";
                buffer->lookInto().print();

                Request request = buffer->lookInto();
                double requestTime = buffer->lookInto().getTime();
                double prevBusyTime = device->getBusyTime();

                double waitTime = prevBusyTime-requestTime > 0? prevBusyTime-requestTime : 0;

                generators[request.getGenNumber()-1].incrementProcessedRequests();
                generators[request.getGenNumber()-1].incrementTimeOfWait(waitTime);
                std::cout << "WAIT TIME is: " << waitTime << std::endl;

                device->serve(buffer->give());

                generators[request.getGenNumber()-1].incrementTimeOfProcess(device->getProcessTime());



                currentDevice = device;
                //systemTime = device->getProcessTime();
                currentDevice->getNumber() == devices.size() ? currentDevice = devices.begin() : ++currentDevice;

                foundFreeDevice = true;
                break;
            }else{
                std::cout << "device is busy until: "<< device->getBusyTime()
                          << " request time is: " << buffer->lookInto().getTime()
                          << " system time is: " << systemTime << std::endl;
            }
        }
        if(!foundFreeDevice){
            for(deviceIterator device = devices.begin(); device != currentDevice; device++){
                checkedNumber++;
                if(device->getBusyTime() <= systemTime){

                    //INFO ABOUT TAKEN REQUEST
                    std::cout <<"current device: " << currentDevice->getNumber()
                              <<"device number: " << device->getNumber()
                              <<"took request: ";
                    buffer->lookInto().print();

                    Request request = buffer->lookInto();
                    double requestTime = buffer->lookInto().getTime();
                    double prevBusyTime = device->getBusyTime();

                    double waitTime = prevBusyTime-requestTime > 0? prevBusyTime-requestTime : 0;

                    generators[request.getGenNumber()-1].incrementProcessedRequests();
                    generators[request.getGenNumber()-1].incrementTimeOfWait(waitTime);
                    std::cout << "WAIT TIME is: " << waitTime << std::endl;

                    device->serve(buffer->give());

                    generators[request.getGenNumber()-1].incrementTimeOfProcess(device->getProcessTime());



                    currentDevice = device;
                    //systemTime = device->getProcessTime();
                    currentDevice->getNumber() == devices.size() ? currentDevice = devices.begin() : ++currentDevice;

                    foundFreeDevice = true;
                    break;
                }else{
                    std::cout << "device is busy until: "<< device->getBusyTime()
                              << " request time is: " << buffer->lookInto().getTime()
                              << " system time is: " << systemTime << std::endl;
                }
            }
        }
    }
}
SMOManager::~SMOManager(){

    if(buffer)
        delete buffer;
    if(request)
        delete request;
    waitTimes.clear();
    processTimes.clear();
    failureProb.clear();
    dispOfWait.clear();
    dispOfProc.clear();
    generators.clear();
    devices.clear();
    processedRequests.clear();
    failedRequests.clear();
    deviceWorkPercent.clear();
}

void SMOManager::check(){
    checkedNumber++;
}

void SMOManager::renewCheckedStatus(){
    checkedNumber = 0;
}

bool SMOManager::allChecked(){
    return checkedNumber == static_cast<int>(devices.size());
}

void SMOManager::setSystemTime(const double time){
    systemTime = systemTime <= time ? time : systemTime;
}

Results SMOManager::returnResults(){
    Results res = {};
    res.bufferSize = bufferSize;
    res.numberOfGenerators = numberOfGenerators;
    res.numberOfDevices = numberOfDevices;
    res.failed = failedRequests;
    res.processed = processedRequests;
    res.waitTimes = waitTimes;
    res.processTimes = processTimes;
    res.failureProb = failureProb;
    res.dispOfWait = dispOfWait;
    res.dispOfProc = dispOfProc;
    res.deviceBusy = deviceWorkPercent;
    return res;
}

Step& SMOManager::returnSteps()
{
    return *steps;
}
