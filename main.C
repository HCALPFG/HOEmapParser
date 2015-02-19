#include <iostream>
#include "emap.h"

int main(){
  
  emap my_emap;
  my_emap.addFile ("data/HOremap_Feb2015_crate3.txt", 3);
  my_emap.addFile ("data/HOremap_Feb2015_crate6.txt", 6);
  my_emap.addFile ("data/HOremap_Feb2015_crate7.txt", 7);
  my_emap.addFile ("data/HOremap_Feb2015_crate13.txt", 13);
  // my_emap.printHash();

  int htr       = my_emap.getHTR      ( "P2", "S01", 2, 6 );
  int fpga      = my_emap.getFPGA     ( "P2", "S01", 2, 6 );
  int htr_fiber = my_emap.getHTRFiber ( "P2", "S01", 2, 6 );
  bool is_hox   = my_emap.isHOX       ( "P2", "S01", 2, 6 );
  
  std::cout << "HTR  = " << htr << std::endl;
  std::cout << "FPGA = " << fpga << std::endl;
  std::cout << "htr_fiber = " << htr_fiber << std::endl;
  std::cout << "Is HOX? ";
  if ( is_hox ) std::cout << "YES!" << std::endl;
  else          std::cout << "NO!"  << std::endl;

}
