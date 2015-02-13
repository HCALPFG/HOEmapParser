#include "box_tools.h"

int box_tools::getHash( const int & ring, 
		  const int & sector, 
		  const int & rm,
		  const int & rm_fib ){
  
  int hash = 0;
  hash += ((ring + 2) * 10000);
  hash += (sector     * 100  );
  hash += (rm         * 10   );
  hash += (rm_fib     * 1    );
  
  return hash;
}


int box_tools::getHash( const std::string & ring, 
		  const std::string & sector, 
		  const int & rm,
		  const int & rm_fib ){
  
  int i_sector = std::stoi(sector.substr( sector.find_first_of("S", 0) + 1, sector.size()));
  int i_ring;

  if      ( ring.compare ("M2" ) == 0 ) i_ring = -2;
  else if ( ring.compare ("M1" ) == 0 ) i_ring = -1;
  else if ( ring.compare ("YB0") == 0 ) i_ring =  0;
  else if ( ring.compare ("P1" ) == 0 ) i_ring =  1;
  else if ( ring.compare ("P2" ) == 0 ) i_ring =  2;
  
  int hash = 0;
  hash += ((i_ring + 2) * 10000);
  hash += (i_sector     * 100  );
  hash += (rm           * 10   );
  hash += (rm_fib       * 1    );
  
  return hash;
}
