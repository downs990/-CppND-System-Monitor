#include "ncurses_display.h"
#include "system.h"


// How to run the program  ??

//1,    make build 
//2,    ./build/monitor 

int main() {
  System system;
  system.MemoryUtilization();
  NCursesDisplay::Display(system);  // MY_TODO: Uncomment after testing  
}