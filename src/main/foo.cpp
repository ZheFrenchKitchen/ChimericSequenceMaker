#include <iostream>
#include <map>
#include <boost/filesystem.hpp>

//using namespace boost::filesystem;

#include "../../include/main/foo.h"


int giveMeAnInt()
{
    return 4;
}

double giveMeADouble()
{
    return 3.1;
}

bool giveMeABool()
{
    return true;
}

//This method prints the vector
void printer2(std::multimap<std::time_t,boost::filesystem::path> pN)
{
	std::cout <<"\n\nMultimap printer method"<<std::endl;
	std::cout<<"Map size = "<<pN.size()<<std::endl;
	std::multimap<std::time_t,boost::filesystem::path>::iterator it = pN.begin();
	  while(it != pN.end())
	  {
	    std::cout<<"Key = "<<it->first<<"    Value = "<<it->second<<std::endl;
	    it++;
	  }
}

