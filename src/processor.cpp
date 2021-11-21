#include <iostream>
#include <string>
#include "processor.h"
#include "linux_parser.h"
 

using std::string;
using std::cout;


void Processor::UpdateValuesMap(string valueName, string value){
     
    long newValue = stol(value, nullptr, 10); // Converts string to long  
  
    if(valuesMap[valueName].size() == 0){ 
       valuesMap[valueName].push_back(0);
       valuesMap[valueName].push_back(newValue);
    }else{
      
      	// Only update vector if new value if different from current
      	if(newValue != valuesMap[valueName][1]){
           valuesMap[valueName][0] = valuesMap[valueName][1];
           valuesMap[valueName][1] = newValue;     
        }
    }
 
//   	cout << "Name " << valueName << "            values: " << valuesMap[valueName][0] << " " << valuesMap[valueName][1] << "\n";
}
  


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  
//   /proc/stat    
//   
//   contains 10 integer values for each processor. 
  
//   The very first "cpu" line aggregates the numbers in all of the other "cpuN" lines. 
//   These numbers identify the amount of time the CPU has spent performing different kinds 
//   of work. Time units are in USER_HZ (typically hundredths of a second). The meanings of
//   the columns are as follows, from left to right:

// 1.  user: normal processes executing in user mode
// 2.  nice: niced processes executing in user mode
// 3.  system: processes executing in kernel mode
// 4.  idle: twiddling thumbs
// 5.  iowait: In a word, iowait stands for waiting for I/O to complete. But there are several problems:
//   
//          - Cpu will not wait for I/O to complete, iowait is the time that a 
//             task is waiting for I/O to complete. When cpu goes into idle state 
//             for outstanding task io, another task will be scheduled on this CPU.
//          - In a multi-core CPU, the task waiting for I/O to complete is not running
//             on any CPU, so the iowait of each CPU is difficult to calculate.
//          - The value of iowait field in /proc/stat will decrease in certain conditions. 
//             So, the iowait is not reliable by reading from /proc/stat.
//  6.  irq: servicing interrupts
//  7.  softirq: servicing softirqs
//  8.  steal: involuntary wait
//  9.  guest: running a normal guest
//  10. guest_nice: running a niced guest
  
  	vector<string> cpuPropertyValues = LinuxParser::CpuUtilization();
      
   
	// Keeps track of current and previous values.
 	UpdateValuesMap("user", cpuPropertyValues[0]);
    UpdateValuesMap("nice", cpuPropertyValues[1]);
    UpdateValuesMap("system", cpuPropertyValues[2]);
    UpdateValuesMap("idle", cpuPropertyValues[3]);
    UpdateValuesMap("iowait", cpuPropertyValues[4]);
    UpdateValuesMap("irq", cpuPropertyValues[5]);
    UpdateValuesMap("softirq", cpuPropertyValues[6]);
    UpdateValuesMap("steal", cpuPropertyValues[7]);
    UpdateValuesMap("guest", cpuPropertyValues[8]);
    UpdateValuesMap("guest_nice", cpuPropertyValues[9]);
 
//   	TODO: Check if this still works ^^^
  
  
  
  
//  ************  ALGORITHM TO IMPLEMENT FOR CPU USAGE %  ***************
//   	[0] = previous      [1] = current 
  
	// PrevIdle = previdle + previowait
  	float prevIdle = valuesMap["idle"][0] + valuesMap["iowait"][0];
  
	// Idle = idle + iowait
    float idle = valuesMap["idle"][1] + valuesMap["iowait"][1]; 
  	// TODO: Update idle in dictionary with this idle ???
//   	valuesMap["idle"][0] = valuesMap["idle"][1];
//   	valuesMap["idle"][1] = idle;
      
	// PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
    float prevNonIdle = valuesMap["user"][0] + valuesMap["nice"][0] + valuesMap["system"][0] + 
      				   valuesMap["irq"][0] + valuesMap["softirq"][0] + valuesMap["steal"][0]; 
      
	// NonIdle = user + nice + system + irq + softirq + steal
  	float nonIdle = valuesMap["user"][1] + valuesMap["nice"][1] + valuesMap["system"][1] + 
      				   valuesMap["irq"][1] + valuesMap["softirq"][1] + valuesMap["steal"][1];
  
	// PrevTotal = PrevIdle + PrevNonIdle
  	float prevTotal = valuesMap["idle"][0] + prevNonIdle;
      
	// Total = Idle + NonIdle
  	float total = idle + nonIdle;
  

	// # differentiate: actual value minus the previous one
	// totald = Total - PrevTotal
  	float totald = total - prevTotal;
  
	// idled = Idle - PrevIdle
  	float idled = idle - prevIdle;

	// CPU_Percentage = (totald - idled)/totald
  	float cpuPercentage = (totald - idled) / totald;
      
  
  return cpuPercentage; 
}