#ifndef HOX_BOX_H
#define HOX_BOX_H

#include "box.h"

class hox_box : public box { 

 public:

  // constructor 
  hox_box ( const std::vector<std::vector<std::string> > & data, 
	    const box_side & side, const int& row  , const int & column );
  
 protected:

  // Member data
  
  // Strings taken from raw data
  const std::string m_str_crate_slot_htr_fib;  
  const std::string m_str_crate;    
  const std::string m_str_slot;	    
  const std::string m_str_htr_fib;  

  // Processed integers derived from strings
  int m_int_crate;

};

#endif
