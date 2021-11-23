#include "ncurses_display.h"
#include "system.h"
// #include "linux_parser.h"   // TODO: Remove after testing
// #include <iostream>

// How to run the program  ??

//1,    make build 
//2,    ./build/monitor 

int main() {
  System system; 
  
  // Testing: ProcessID 1 = UpTime 3891
//   system.UpTime(1);  
//   LinuxParser::UpTime(1);
//   LinuxParser::User(1); 
//   std::cout << "Process Count: " << system.Processes().size() << "\n";
  NCursesDisplay::Display(system);  
}