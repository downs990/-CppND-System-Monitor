#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <regex>


#include "linux_parser.h"

using std::cout;
using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::unordered_map;
using std::regex;
using std::sregex_token_iterator;

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
//     float buff = ::atof(buffers.c_str());
//     float cach = ::atof(cached.c_str());
//     float green = (totalmem - freemem) - (buff + cach);
  
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
long LinuxParser::ActiveJiffies(int pid = 0) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }  

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
   
  //user_str, nice_str, system_str, idle_str, iowait_str, irq_str, softirq_str, steal_str, guest_str, guest_nice_str  
  vector<string> cpuPropertyValues = {"", "", "", "", "", "", "", "", "", ""};
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    
    string cpu_title = "";
    linestream >> cpu_title 
      			>> cpuPropertyValues[0] >> cpuPropertyValues[1] >> cpuPropertyValues[2] >> cpuPropertyValues[3] 
      			>> cpuPropertyValues[4] >> cpuPropertyValues[5] >> cpuPropertyValues[6] >> cpuPropertyValues[7] 
      			>> cpuPropertyValues[8] >> cpuPropertyValues[9];   
  }
    
  return cpuPropertyValues;
}  


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {   
  
  	string line, name;
  	int value; 
    std::ifstream stream(kProcDirectory + kStatFilename);
  
    if (stream.is_open()) {
      while(name != "processes"){ 
        std::getline(stream, line);
        std::istringstream linestream(line);
        
        linestream >> name >> value; 
      } 
    }
   
  	return value; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
   
  	string line, name;
  	int value; 
    std::ifstream stream(kProcDirectory + kStatFilename);
  
    if (stream.is_open()) {
      while(name != "procs_running"){ 
        std::getline(stream, line);
        std::istringstream linestream(line);
        
        linestream >> name >> value; 
      } 
    }
   
  return value; 

}


// TODO: Read and return the command associated with a process 
string LinuxParser::Command(int pid = 0) { 
  
  // Linux stores the command used to launch the function in the /proc/[pid]/cmdline file. 
  string line, command; 
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename );
  
  if (stream.is_open()) { 
    
    std::getline(stream, line);
    std::istringstream linestream(line);
         
    linestream >> command; 

  }
  return command; 
} 

// TODO: Read and return the memory used by a process 
string LinuxParser::Ram(int pid = 0) {  
  
  //    /proc/[pid]/status
  // ...
  // VmSize: 93264 kB
  //            ^
  //          RAM (conver to MB by dividing by 1,000)
  
  
   	string line, name, value; 
    std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
    if (stream.is_open()) {
      while(name != "VmSize:"){ 
        std::getline(stream, line);
        std::istringstream linestream(line);
        
        linestream >> name >> value; 
      } 
    }
  
  long ramLong = stol(value, nullptr, 10);
  long ramMB = ramLong / 1000; 
  
  return to_string(ramMB); 
}  




// TODO: Read and return the user ID associated with a process 
string LinuxParser::Uid(int pid = 0) { 
// !
   
//   The UID for a process is stored in /proc/[PID]/status. (on line 9)
//  
//   Uid:      0         0         0         0
//   		  ^
//        Uid for PID
  
  	string line, name, value; 
    std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
    if (stream.is_open()) {
      while(name != "Uid:"){ 
        std::getline(stream, line);
        std::istringstream linestream(line);
        
        linestream >> name >> value; 
      } 
    }
  
//   	cout << "name: " << name << " Pid: " << value;
//     long uid = stol(value, nullptr, 10);

  return value; 
}

// TODO: Read and return the user associated with a process 
string LinuxParser::User(int pid = 0) {
  
  string uid = Uid(pid);
  
  // /etc/passwd     is used to match "Uid" to "Username"
  
//   usbmux    :x:117:46:usbmux daemon,,,:/var/lib/usbmux:/bin/false
//   hplip     :x:118:7:HPLIP system user,,,:/var/run/hplip:/bin/false
//   postgres  :x:119:126:PostgreSQL administrator,,,:/var/lib/postgresql:/bin/bash
//   redis     :x:120:127::/var/lib/redis:/bin/false
  // ^             ^   
  // Username      Uid 
  
  
  string line, username, currentUid; 
  std::ifstream stream2(kPasswordPath);
  
  if (stream2.is_open()) {
    while(currentUid != uid){ 
      std::getline(stream2, line);
      std::istringstream linestream(line);
 
      
      // Source: https://stackoverflow.com/questions/9435385/split-a-string-using-c11/27511119        
      // Java like string split() on  delimiter :
      const string& input = line;
      const string& regex = ":";
      std::regex re(regex);
      sregex_token_iterator
          first{input.begin(), input.end(), re, -1},
          last;
      vector<string> splits = {first,last};
      
      
      username = splits[0];
      currentUid = splits[2];

//       cout << "usename: " << username << " uid: " << currentUid;
    } 
  }
   
  
  return username; 
}
 

// TODO: Read and return the uptime of a process 
long LinuxParser::UpTime(int pid = 0) { 
  
  //   /proc/[pid]/stat 
  
  // Example: 
  // cat /proc/2141/stat  
  // 2141 (code) S 2054 1 1 0 -1 1077936128 39501 0 2 0 212 60 0 0 20 0 16 0 632214   ... many more values
  //                                                                          ^
  // 																"UpTime" is 22nd  
   
  string line, value; 
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  
  if (stream.is_open()) { 
    
    std::getline(stream, line);
    std::istringstream linestream(line);
        
    // Gets the 22nd value from /proc/[pid]/stat 
    linestream >> value >> value >> value >>  value >>  value >>  value 
      >> value >>  value >>  value >>  value >>  value >>  value 
      >> value >>  value >>  value >>  value >>  value >>  value 
      >>  value >>  value >>  value >>  value;  

  }
  	
  long uptimeLong = stol(value, nullptr, 10);
//   cout << "VALUEEE: " << uptimeLong << "\n";
  
  return uptimeLong; 
}