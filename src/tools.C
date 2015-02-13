#include "tools.h"
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


void tools::split ( const std::string & content, 
		    std::vector<std::string> & output, 
		    const char & delimiter ) {
  output.clear();
  std::istringstream ss (content);
  std::string entry;
  while ( std::getline(ss, entry, delimiter ) )
    output.push_back ( entry );
}

// trim from end
void tools::rtrim(std::string &content){
  content.erase(std::find_if(content.rbegin(), content.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), content.end());
}
