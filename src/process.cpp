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

// TODO: Return this process's ID
int Process::Pid() { 
  return myPID; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
	return 0; // ??? How to calculate a process CPU Utilization ??? Not LinuxParser::CpuUtilization() returns Vector<string>
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
bool Process::operator<(Process const& a = Process() ) const {  // ??? Do I need to create a no-arg constructor ??
  //									^^^ Trying to make this arg optional. 
  
  
  return true; 
}