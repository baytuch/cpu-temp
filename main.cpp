
#include <iostream>
#include "cpu-temp.h"

int main(){
  cpu_temp temp = cpu_temp();
  if (temp.getStatus()){
    std::cout << temp.getTemp() << "°C" << std::endl;
  } else {
    std::cout << "sensor not found" << std::endl;
  }
  return 0;
}
