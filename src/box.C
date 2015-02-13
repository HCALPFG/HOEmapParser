#include "box.h"
#include "tools.h"
#include "box_tools.h"

#include <iostream>

box::box():
  m_slot(-1),
  m_side(box::NONE),
  m_row(-1),
  m_column(-1),
  m_str_ring(""),
  m_str_sector(""),
  m_str_rm_rm_fib("")
{}

box::box( const std::vector<std::vector<std::string> > & data, 
	  const int& slot , const box_side & side,
	  const int& row  , const int & column ):
  m_slot          ( slot   ),
  m_side          ( side   ),
  m_row           ( row    ),
  m_column        ( column ),
  m_str_ring      ( data[row  ][column] ),
  m_str_sector    ( data[row+1][column] ),
  m_str_rm_rm_fib ( data[row+3][column] )
{
  std::vector<std::string> entries;
  tools::split(m_str_rm_rm_fib, entries, '/');

  if      ( m_str_ring.compare ("M2" ) == 0 ) m_int_ring = -2;
  else if ( m_str_ring.compare ("M1" ) == 0 ) m_int_ring = -1;
  else if ( m_str_ring.compare ("YB0") == 0 ) m_int_ring =  0;
  else if ( m_str_ring.compare ("P1" ) == 0 ) m_int_ring =  1;
  else if ( m_str_ring.compare ("P2" ) == 0 ) m_int_ring =  2;
  
  m_int_sector = std::stoi(m_str_sector.substr( m_str_sector.find_first_of("S", 0) + 1, m_str_sector.size()));
  m_int_rm     = std::stoi ( entries[0] );
  m_int_rm_fib = std::stoi ( entries[1] );
  
}

int box::getHash(){
  return box_tools::getHash ( m_int_ring, m_int_sector, m_int_rm, m_int_rm_fib );
}
