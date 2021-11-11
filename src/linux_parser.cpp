#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "linux_parser.h"

using std::cout;
using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::unordered_map;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  } 
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
 
  
    unordered_map<string, string> propertyNameAndValue;
  
  
    string trash; 
    string line;
    std::ifstream stream(kProcDirectory + kMeminfoFilename);
    if (stream.is_open()) {
      
      int index = 0;
      while(index < 48){//!stream.eof()){
        std::getline(stream, line);
        std::istringstream linestream(line);
        
        string name, value;
        linestream >> name >> value;
        name = std::regex_replace(name, std::regex("\\:"), ""); // removes colon char from name  
        propertyNameAndValue[name] = value;
        
        index++;
      } 
    }
  
  
//   Total used memory = MemTotal - MemFree
//	 Non cache/buffer memory (green) = Total used memory - (Buffers + Cached memory)
// 	 Buffers (blue) = Buffers
//   Cached memory (yellow) = Cached + SReclaimable - Shmem
//   Swap = SwapTotal - SwapFree
   
  	// Convert string to float 
  	string memtotal = propertyNameAndValue["MemTotal"];
    string memfree =  propertyNameAndValue["MemFree"];
//   	string buffers =  propertyNameAndValue["Buffers"];
//   	string cached =   propertyNameAndValue["Cached"];	
  
	float totalmem = ::atof(memtotal.c_str());
  	float freemem = ::atof(memfree.c_str());
//   	float buff = ::atof(buffers.c_str());
//     float cach = ::atof(cached.c_str());
//   	float green = (totalmem - freemem) - (buff + cach);
  
  	float totalMemUsed = (totalmem - freemem) / totalmem; // percentage % 
    return totalMemUsed;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {  
  
  string uptime = "", idletime = "";
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }
  
//   cout << "Uptime: " << uptime << " Idletime: " << idletime;
  long uptimeLong = stol(uptime, nullptr, 10);
  return uptimeLong; 
} 

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 

//   "/proc/[pid]/stat"
//   
//   (22) starttime %llu
// 		The time the process started after system boot. In kernels before Linux 2.6, 
//   this value was expressed in jiffies. Since Linux 2.6, the value is expressed
//   in clock ticks (divide by sysconf(_SC_CLK_TCK)).
  
  return 0; 
}


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid = 0) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid = 0) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid = 0) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }