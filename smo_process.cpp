#include <iostream>
#include "generator.cpp"
#include "request.cpp"
#include "device.cpp"
#include "buffer.cpp"

//int main()
//{
//  Device *dev = new Device();
//  Buffer *buff = new Buffer(5);
//  Generator *gen = new Generator(1);
//  Generator *gen2 = new Generator(2);
//  Generator *gen3 = new Generator(3);
//  std::list<Request> reqs;
//  while ( reqs.size() < 20 ){
//	  reqs.push_back(gen->generate());
//	  if (reqs.size() == 20){
//		  break;
//		  }
//	  reqs.push_back(gen2->generate());
//	  if (reqs.size() == 20){
//		  break;
//		  }
//	  reqs.push_back(gen3->generate());
//  }
//  reqs.sort();
  
//  std::cout << "reqs size " <<reqs.size() << std::endl;
  
//  while(!reqs.empty()){
//	  Request request = reqs.front();
//	  request.print();
//	  reqs.pop_front();
//	  if(!buff->isFull()){
//		buff->put(request);
//		buff->printStatus();
//      }else {
//		  std::cout << "request denied" << std::endl;
//		  request.print();
//	  }
	  
//	  if(!dev->isBusy(buff->getLastToCome())){
//		  dev->serve(buff->give());
//	  }
//  }
//  std::cout << " device served " << dev->getServedNumber() << std::endl;
  //buff->printStatus();
  //buff->sortByTime();
  //buff->print();
	  
  
  //for(int i = 0; i < 10; i++)
  //{
	  //Request req1 = gen->generate();
	  //Request req2 = gen2->generate();
	  
	  //if(!buff->isFull()){
			//buff->put(req2);
	  //}else{
		  //std::cout << "buffer is full" << std::endl;
		  //}
	  
	  //std::cout << req1.isFirstToGo(req2) << std::endl;
	  //if(!dev->isBusy(req1)){
		  //dev->serve(req1);
		  
	  //} else{
		  //std::cout << "Busy until: " << dev->getBusyTime() << "req time: " << req1.getTime() << std::endl;
		  //continue;
	  //}
	  
  //}
	//Request req1 = gen->generate();
	//Request req2 = gen2->generate();
	//Request req3 = gen->generate();
	//Request req4 = gen2->generate();
	//Request req5 = gen->generate();
	//Request req6 = gen2->generate();
	
	//buff->put(req1);
	//buff->put(req2);
	//buff->put(req5);
	//buff->put(req4);
	//buff->put(req3);
	

  
  //std::cout<< "buff size" << std::endl;
  //buff->print();
//  return 0;
//}
