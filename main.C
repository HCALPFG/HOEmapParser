#include <iostream>
#include "emap.h"

int main(){
  
  emap my_emap ( "HOremap_Feb2015_crate7.txt");
  
  int htr       = my_emap.getHTR      ( "P2", "S05", 4, 7 );
  int fpga      = my_emap.getFPGA     ( "P2", "S05", 4, 7 );
  int htr_fiber = my_emap.getHTRFiber ( "P2", "S05", 4, 7 );

  std::cout << "HTR  = " << htr << std::endl;
  std::cout << "FPGA = " << fpga << std::endl;
  std::cout << "htr_fiber = " << htr_fiber << std::endl;

}
