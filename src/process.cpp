#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
  myPID = pid;
}

// TODO: Return this process's ID
int Process::Pid() { 
  return myPID; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  
    //   To calculate CPU usage for a specific process you'll need the following:
    //   1.    /proc/uptime
    // 				#1 uptime of the system (seconds)
  	long systemUpTimeSeconds = LinuxParser::UpTime();
  
    //   2.    /proc/[PID]/stat
    // 				#14 utime - CPU time spent in user code, measured in clock ticks
    // 				#15 stime - CPU time spent in kernel code, measured in clock ticks
    // 				#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
    //				#17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
    // 				#22 starttime - Time when the process started, measured in clock ticks
  
    //                        = [#14 , #15, #16, #17, #22]
  	vector<long> processStats = LinuxParser::getProcessStats(myPID);
  
    //   3. Hertz (number of clock ticks per second) of your system.
    // 			- In most cases, getconf CLK_TCK can be used to return the number of clock ticks.
    // 			- The sysconf(_SC_CLK_TCK) C function call may also be used to return the hertz value.
	long hertz = 0; 
  
  	// Calculation 
    // First we determine the total time spent for the process:
    //		-	 total_time = utime + stime
  	long totalTime = processStats[0] + processStats[1];
    // We also have to decide whether we want to include the time from children processes. If we do, then we add those values to total_time:
    // 		-	total_time = total_time + cutime + cstime
  	totalTime = totalTime + processStats[2] + processStats[3];
    // Next we get the total elapsed time in seconds since the process started:
    // 		-	seconds = uptime - (starttime / Hertz)
  	long startTime = 0; // ??? where at 
  
  	long seconds = systemUpTimeSeconds - ();
    // Finally we calculate the CPU usage percentage:
    // 			cpu_usage = 100 * ((total_time / Hertz) / seconds)
  	long cpuUsage = 100 * ((totalTime / hertz) / seconds);
  
	return cpuUsage;
}

// TODO: Return the command that generated this process
string Process::Command() {
	return LinuxParser::Command(myPID);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
	return LinuxParser::Ram(myPID);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
	return LinuxParser::User(myPID);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
	return LinuxParser::UpTime(myPID); // ??? Is this in seconds??
}

// TODO: Overload the "less than" comparison operator for Process objects 
bool Process::operator<(Process const& a[[maybe_unused]]) const { 
  // Compare based on CPU Utilization. 
  return true; 
}
