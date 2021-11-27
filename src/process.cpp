#include <unistd.h>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::cout;

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
  
  // 2. Inside getProcessStats(pid)
  // 						= [utime, stime, cutime, cstime, starttime]
  vector<long> processStats = LinuxParser::getProcessStats(myPID);
  
  //   3. Hertz (number of clock ticks per second) of your system.
  // 		- In most cases, getconf CLK_TCK can be used to return the number of clock ticks.
  // 		- The sysconf(_SC_CLK_TCK) C function call may also be used to return the hertz value.
  float hertz = sysconf(_SC_CLK_TCK); 
  
  // Calculation 
  // First we determine the total time spent for the process:
  //		-	 total_time = utime + stime
  long totalTime = processStats[0] + processStats[1];
  // We also have to decide whether we want to include the time from children processes. 
  // 	If we do, then we add those values to total_time:
  // 				-	total_time = total_time + cutime + cstime
  totalTime = totalTime + processStats[2] + processStats[3];
  // Next we get the total elapsed time in seconds since the process started:
  // 		-	seconds = uptime - (starttime / Hertz)
  long startTime = processStats[4];

  float seconds = systemUpTimeSeconds - (startTime / hertz);
  // Finally we calculate the CPU usage percentage:
  // 			cpu_usage = 100 * ((total_time / Hertz) / seconds)
  float cpuUsage = 100 * ((totalTime / hertz) / seconds);
   
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
	return LinuxParser::UpTime(myPID);  
}
 
bool Process::operator<(Process &argProcess){ // TODO: ???? [[maybe_unused]] ??? add const back ????
  
  // Compare based on CPU Utilization. 
  float thisProcessCpuUtilization = CpuUtilization();
  float argumentsProcessCpuUtilization = argProcess.CpuUtilization();
  bool result = thisProcessCpuUtilization < argumentsProcessCpuUtilization; 
  return result;
}
