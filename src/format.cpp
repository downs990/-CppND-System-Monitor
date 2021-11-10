#include <string>

#include "format.h"

using std::string; 
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long totalSecondsUp = 0) {
	
  string output = "";
  int SECONDS_IN_HOUR = 3600;
  int SECONDS_IN_MINUTE = 60;
  
//   totalSecondsUp = 7265; // testing 
  // 3661 => 1H 1M 1S
  // 7265 => 2H 1M 5S
  
  int hours = totalSecondsUp / SECONDS_IN_HOUR;
  int minutes = (totalSecondsUp % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE;
  int seconds = ( (totalSecondsUp % SECONDS_IN_HOUR) % SECONDS_IN_MINUTE ) ;
  
  int leadingZeros = 1;
  string hh = string(leadingZeros - (to_string(hours).length()-1), '0') + to_string(hours);
  string mm = string(leadingZeros - (to_string(minutes).length()-1), '0') + to_string(minutes);
  string ss = string(leadingZeros - (to_string(seconds).length()-1), '0') + to_string(seconds);
  
  output = "" + hh + ":" + mm + ":" + ss;
  
  return output;
  
}