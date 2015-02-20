#ifndef EMAP_H
#define EMAP_H

#include <map>
#include <vector>
#include <string>

#include "box.h"

class emap { 
  
 public:

  // Constructor + destructor
  emap ();
  ~emap();

  // Build the emap
  void addFile(const char* file_path, const int & crate_number);

  // Print the hash / map
  void printHash();
  void printMap ();
  
  // Getter functions

  int getHTR     ( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  int getHTR     ( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );
  
  int getHTRFiber( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  int getHTRFiber( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );

  int getFPGA    ( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  int getFPGA    ( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );

  bool isHOX     ( const int &         ring, const int &         sector, const int & rm, const int & rm_fib );
  bool isHOX     ( const std::string & ring, const std::string & sector, const int & rm, const int & rm_fib );
  
 private:

  // Private functions
  void processRawData(const std::vector<std::vector<std::string> > & raw_data, const int & crate_number);
  
  // Member items
  
  // Hash table info
  const int m_max_hash;
  std::vector<box> * m_hash_table;
  std::vector<int> m_hashes;

  // Map info
  std::multimap<int, box> m_map;
  
  // Raw data info
  const int m_raw_data_n_columns;

  //typedefs 
 public:

  typedef std::multimap<int, box>::iterator it_single;
  typedef std::pair< it_single, it_single > it_pair;
    
    
    
  

};

#endif
