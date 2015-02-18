#ifndef HO_BOX_H
#define HO_BOX_H

#include "box.h"

class ho_box : public box { 

 public:

  // constructors
  ho_box ( const std::vector<std::vector<std::string> > & data, 
	   const box_side & side, const int& row  , const int & column );
	   
  ho_box ();

  // Setter functions
  void setSlot(const int& s){ m_int_slot = s; }

 protected:

  // Member data
  
  // Strings taken from raw data
  std::string m_str_phi;
  std::string m_str_htr_fiber;
  
  // Processed integers derived from strings
  int m_int_phi_min;
  int m_int_phi_max;

};

#endif
