//
//  main.cpp
//  InterestRateModels
//
//  Created by Lewis Brown on 28/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//

#include <iostream>
#include "BaseTest.hpp"
#include "utest.hpp"


int main(int argc, const char * argv[]) {
  ut::TestSet& tests = ut::TestSet::Instance();
  tests.run();
  tests.report();
  
  std::cout << "Hello, World!\n";
  return 0;
}
