#include "emap.h"
#include "tools.h"
#include "box_tools.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
emap::emap():
  m_max_hash ( 50000 ),
  m_hash_table(new std::vector<box> ( m_max_hash, box())),
  m_raw_data_n_columns ( 45 )
{}

emap::~emap(){
  if ( m_hash_table ) delete m_hash_table;
}

// Get values

int emap::getHTR( const int & ring, const int & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSlot();
}

int emap::getHTR( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSlot();
}

int emap::getHTRFiber( const int & ring, const int & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getHTRFiber();
}

int emap::getHTRFiber( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getHTRFiber();
}


int emap::getFPGA( const int & ring, const int & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide();
}

int emap::getFPGA( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide();
}


bool emap::isHOX( const int & ring, const int & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].isHOX();
}

bool emap::isHOX( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib ){
  if ( (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].getSide() == box::NONE ) {
    std::cout << "ERROR: INVALID COORDINATES!"  << std::endl;
    return -1;
  }
  return (*m_hash_table)[box_tools::getHash ( ring, sector, rm, rm_fib )].isHOX();
}


// Add a new 

// Process the data from the file (from constructor)

void emap::addFile(const char* file_path){
  std::ifstream file (file_path);
  int i_line = 0;
  std::string line, entry;
  std::vector<std::string> tmp_v;
  std::vector<std::vector<std::string> > raw_data;
  while ( getline ( file, line ) ){
    // Clear white space from the end of the line
    tools::rtrim( line );
    tmp_v.clear();
    std::stringstream line_ss ( line );
    while ( std::getline ( line_ss, entry, '\t' ))
      tmp_v.push_back ( entry ) ;
    // Only save the vector if it has the right number of entries
    if ( tmp_v.size() != m_raw_data_n_columns ) continue;
    raw_data.push_back ( tmp_v );
  }
  
  processRawData ( raw_data );
}

// Make boxes from raw data

void emap::processRawData( const std::vector<std::vector<std::string> > & raw_data ){

  const int n_small_rows_per_big_row = 4;
  const int n_small_rows = raw_data.size();
  const int n_big_rows = n_small_rows / n_small_rows_per_big_row;

  for (int i_big_row = 0; i_big_row < n_big_rows; ++i_big_row){
    bool is_top ( i_big_row % 2 == 0 );
    box::box_side side = is_top ? box::TOP : box::BOTTOM;

    // "row" refers to the top row of a 4-row "big row"
    int row = i_big_row * n_small_rows_per_big_row;
    int ho_slot = std::atoi(raw_data[row][0].c_str());
    int n_columns = raw_data[row].size();
    for (int i_column = 0; i_column < n_columns; ++i_column){
      
      // Skip empty columns
      if ( raw_data[row][i_column].empty() ) continue;

      // If this is a number, it describes the slot for HO boxes (not HOX boxes)
      // Take note of the slot and then move to the next column
      if ( tools::is_number ( raw_data[row][i_column] )) {
	ho_slot = std::atoi ( raw_data[row][i_column].c_str() );
	continue;
      }
      
      // This is a box.  Is it an HO box or an HOX box?
      // The third row of an HOX box has a "/" in it.
      // The third row of an HO box does not.
      
      bool is_hox ( raw_data[row + 2][i_column].find('/') != std::string::npos );
      
      // If this is an HOX box, use the HOX class to add an entry to the hash table

      if ( is_hox ) { 
	hox_box box ( raw_data, side, row, i_column);
	(*m_hash_table)[box.getHash()] = box;
      }

      // If this is an HO box, use the HO class to add an entry to the hash table

      else { 
	ho_box box ( raw_data, side, row, i_column);
	box.setSlot(ho_slot);
	(*m_hash_table)[box.getHash()] = box;
      }
    }
  }
}
