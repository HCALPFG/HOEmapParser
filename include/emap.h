#ifndef EMAP_H
#define EMAP_H

#include <vector>
#include <string>

#include "ho_box.h"
#include "hox_box.h"

class emap { 
  
 public:

  // Constructor
  emap ( const char * file_path );
  ~emap();
  
  // Getter functions

  int getHTR     ( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  int getHTR     ( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );
  
  int getHTRFiber( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  int getHTRFiber( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );

  int getFPGA    ( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  int getFPGA    ( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );
  
 private:

  // Private functions
  void getRawData();
  void processData();
  
  // Member items
  
  // Hash table info
  const int m_max_hash;
  std::vector<ho_box> * m_hash_table;

  // Input txt file path
  const char * m_file_path;
 
  // Raw data
  const int m_raw_data_n_columns;
  std::vector<std::vector<std::string> > m_raw_data;

};

#endif
