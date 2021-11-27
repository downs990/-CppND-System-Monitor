#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <unordered_map>
#include <string>
#include <vector>

using std::unordered_map;
using std::string;
using std::vector;


class Processor {
 public:
  	float Utilization();  // TODO: See src/processor.cpp

 
 // TODO: Declare any necessary private members
 private:
  	unordered_map<string, vector<int>> valuesMap;
  	void UpdateValuesMap(string valueName, string value);
  
   
};

#endif