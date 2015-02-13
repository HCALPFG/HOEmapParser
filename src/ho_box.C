#include "ho_box.h"
#include "tools.h"
#include <iostream>

ho_box::ho_box():
  box(),
  m_str_phi (""),
  m_str_htr_fiber("")
{}

ho_box::ho_box( const std::vector<std::vector<std::string> > & data, 
		const int& slot , const box_side & side, 
		const int& row  , const int & column ):
  box ( data, slot, side , row, column ),
  m_str_htr_fiber( data[data.size() - 1][column]),
  m_str_phi  ( data[row+2][column] )
{
  
  std::vector<std::string> entries;
  tools::split(m_str_phi, entries, '-');
  
  m_int_phi_min   = std::stoi ( entries[0] );
  m_int_phi_max   = std::stoi ( entries[1] );
  m_int_htr_fiber = std::stoi(m_str_htr_fiber);
}
