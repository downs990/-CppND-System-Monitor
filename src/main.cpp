#include "ncurses_display.h"
#include "system.h"


// How to run the program  ??

//1,    make build 
//2,    ./build/monitor 

int main() {
  System system;
//   system.Cpu().Utilization();     // Testing 
//   system.TotalProcesses();
  NCursesDisplay::Display(system);  // MY_TODO: Uncomment after testing  
}