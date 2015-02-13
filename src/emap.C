#include "emap.h"
#include "tools.h"
#include "box_tools.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
emap::emap( const char * file_path ):
  m_file_path ( file_path ),
  m_raw_data_n_columns ( 45 ),
  m_max_hash ( 50000 ),
  m_hash_table(new std::vector<ho_box> ( m_max_hash, ho_box()))
{
  getRawData(); 
  processData();
}

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


// Process the data from the file (from constructor)

void emap::getRawData(){
  std::ifstream file (m_file_path);
  int i_line = 0;
  std::string line, entry;
  std::vector<std::string> tmp_v;
  while ( getline ( file, line ) ){
    // Clear white space from the end of the line
    tools::rtrim( line );
    tmp_v.clear();
    std::stringstream line_ss ( line );
    while ( std::getline ( line_ss, entry, '\t' ))
      tmp_v.push_back ( entry ) ;
    // Only save the vector if it has the right number of entries
    if ( tmp_v.size() != m_raw_data_n_columns ) continue;
    m_raw_data.push_back ( tmp_v );
  }
}

// Make boxes from raw data

void emap::processData(){
  const int n_all_rows = m_raw_data.size();
  const int n_big_rows = n_all_rows / 8;
  const int n_sides = 2; // top and bottom
  const int n_rows_per_big_row = 8;
  const int n_slots_per_big_row = 4;
  const int slot_starting_columns [n_slots_per_big_row] = { 0, 10, 25, 35 };
  const int n_columns_per_slot = 10;
  const int n_rows_per_box = 4;

  int top_row, bottom_row, slot, column;
  
  // Loop over big rows (3 slots each)
  for (int i_big_row = 0; i_big_row < n_big_rows; ++i_big_row ){
    top_row    = i_big_row * n_rows_per_big_row;
    bottom_row = top_row + n_rows_per_box;
    
    // Loop over the slots in the big row
    for (int i_slot = 0; i_slot < n_slots_per_big_row; ++i_slot){
      slot = std::stoi(m_raw_data[top_row][slot_starting_columns[i_slot]]);

      // Loop over FPGAs in the big row (top and bottom)
      for (int i_side = 0; i_side < n_sides; ++i_side ){
	
	// Loop over columns in the big row
	for (int i_column = 0; i_column < n_columns_per_slot; ++i_column){
	  
	  // What is the actual column number?
	  column = slot_starting_columns[i_slot] + i_column ;
	  if ( i_column == 0  || i_column == 5  ) continue; // these are empty
	  if ( column   >= 16 && column   <= 20 ) continue; // Skip HOX boxes for now
	  
	  // Make the boxes
	  ho_box top_box    ( m_raw_data, slot, box::TOP   , top_row   , column );
	  ho_box bottom_box ( m_raw_data, slot, box::BOTTOM, bottom_row, column );

	  // Fill the hash table
	  (*m_hash_table)[top_box.getHash()   ] = top_box;
	  (*m_hash_table)[bottom_box.getHash()] = bottom_box;
	}
      }
    }
  }
}
