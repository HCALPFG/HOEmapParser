#ifndef BOX_H
#define BOX_H

#include <vector>
#include <string>

class box { 
  
 public:
  
  // Define sides
  enum box_side { NONE, TOP, BOTTOM };

  // Constructors
  box();
  box( const std::vector<std::vector<std::string> > & data,
       const box_side & side, const int & row , const int  & column );
       
  
  // Getter functions 
  int      getRing()      { return m_int_ring;       }
  int      getSector()    { return m_int_sector;     }
  int      getRM()        { return m_int_rm;         }
  int      getRMFib()     { return m_int_rm_fib;     }
  box_side getSide()      { return m_side;           }
  int      getSlot()      { return m_int_slot;       }
  int      getHTRFiber()  { return m_int_htr_fiber;  }
  bool     isHOX()        { return m_is_hox;         }
  int      getCoupler()   { return m_int_coupler;    } 
  int      getBlock()     { return m_int_block;      }
  int      getCrate()     { return m_int_crate;      }
  
  // Setter functions
  void     setBlock(int b){ m_int_block = b;         }
  void     setCrate(int c){ m_int_crate = c;         }

  // Hash
  int getHash();

 protected:
  
  // Member info

  // Raw integers from constructor
  box_side m_side;
  int      m_row;
  int      m_column;

  // Strings taken from raw data
  std::string m_str_ring;
  std::string m_str_sector;
  std::string m_str_rm_rm_fib;
  
  // Processed integers derived from strings
  int m_int_slot;
  int m_int_ring;
  int m_int_sector;
  int m_int_rm;
  int m_int_rm_fib;
  int m_int_sign;
  int m_int_htr_fiber;
  int m_int_crate;
  int m_int_block;
  int m_int_coupler;
  
  // Is this HOX?
  bool m_is_hox;

  
};

#endif
