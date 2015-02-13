#include "hox_box.h" 
#include "tools.h"
#include <iostream>

hox_box::hox_box( const std::vector<std::vector<std::string> > & data, 
		  const int& slot , const box_side & side, 
		  const int& row  , const int & column ):
  box ( data, slot, side , row, column ),
  m_str_crate_slot_htr_fib ( data[row+2][column] )
{
  std::vector<std::string> entries;
  tools::split(m_str_crate_slot_htr_fib, entries, '/');
  
  m_int_crate   = std::stoi ( entries[0] );
  m_int_slot    = std::stoi ( entries[1] );
  m_int_htr_fbr = std::stoi ( entries[2] );
}
