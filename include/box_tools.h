#ifndef BOX_TOOLS_H
#define BOX_TOOLS_H

#include <string>

namespace box_tools { 
  
  int getHash( const int & ring, 
	       const int & sector, 
	       const int & rm,
	       const int & rm_fib );
  
  int getHash( const std::string & ring,
	       const std::string & sector,
	       const int & rm,
	       const int & rm_fib );

};

#endif 
