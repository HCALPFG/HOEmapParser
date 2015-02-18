#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

namespace tools { 
  
  // Split a string into a vector of strings that are split by a delimiter
  void split ( const std::string & content, 
	       std::vector<std::string> & output, 
	       const char & delimiter );
  
  // Clean white space from end of line
  void rtrim (std::string &content);

  // Is this string a number?
  bool is_number(const std::string & content);
};

#endif
