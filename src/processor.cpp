#include <iostream>
#include <string>
#include "processor.h"
#include "linux_parser.h"
 

using std::string;
using std::cout;

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
  
  
  
  string user = "", nice = "", system = "", idle = "", iowait = "", 
  		 irq = "", softirq = "", steal = "", guest = "", guest_nice = "";
   
  
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    
    string cpu_title = "";
    linestream >> cpu_title >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
     
  }
  
  
//  ************  ALGORITHM TO IMPLEMENT FOR CPU USAGE %  ***************
//   
// PrevIdle = previdle + previowait
// Idle = idle + iowait
// PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
// NonIdle = user + nice + system + irq + softirq + steal
// PrevTotal = PrevIdle + PrevNonIdle
// Total = Idle + NonIdle
//   
// # differentiate: actual value minus the previous one
// totald = Total - PrevTotal
// idled = Idle - PrevIdle

// CPU_Percentage = (totald - idled)/totald
  
  
  //   long uptimeLong = stol(uptime, nullptr, 10); // Converts string to long 
  cout << user << " " << nice << " " << system << " " << idle << " " << iowait << " " 
       << irq << " " << softirq << " " << steal << " " << guest << " " << guest_nice ; 
  
  // string = property name    vector<size = 2> [prevValue, currentValue]   
  // unordered_list<string, vector<int> >  statMap = [];
  
 
  
  return 0.0; 
}