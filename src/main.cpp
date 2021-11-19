#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"   // TODO: Remove after testing

// How to run the program  ??

//1,    make build 
//2,    ./build/monitor 

int main() {
  System system; 
//   system.UpTime(1); // Testing: ProcessID 1 = UpTime 3891
//   LinuxParser::UpTime(1);
  LinuxParser::User(1); 
//   NCursesDisplay::Display(system);  // MY_TODO: Uncomment after testing  
}