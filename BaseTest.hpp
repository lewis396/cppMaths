//
//  BaseTest.hpp
//  UnitTest
//
//  Created by Lewis Brown on 26/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//


#ifndef BaseTest_hpp
#define BaseTest_hpp


#include <stdio.h>
#include <string>
#include <sstream>


#define IS_TRUE(exp)      (void) ut::isTrue(exp, #exp, __FILE__, __LINE__)
#define IS_FALSE(exp)      (void) ut::isFalse(exp, #exp, __FILE__, __LINE__)
#define IS_TRUE_OR_STOP(exp)  if (ut::isTrue(exp, #exp, __FILE__, __LINE__)) return
#define IS_FALSE_OR_STOP(exp)  if (ut::isFalse(exp, #exp, __FILE__, __LINE__)) return
#define IS_TRUE_OR_BREAK(exp)  if (ut::isTrue(exp, #exp, __FILE__, __LINE__)) break
#define IS_FALSE_OR_BREAK(exp)  if (ut::isFalse(exp, #exp, __FILE__, __LINE__)) break


namespace ut {

  class BaseTest {
  public:
    BaseTest(const std::string& name);
    virtual ~BaseTest();
    virtual bool setUp();
    virtual void run();
    virtual bool tearDown();
    virtual std::string name();
    void writeToConsole(std::ostream& os) const;
    
  protected:
    std::ostringstream _test_out;
    
  private:
    std::string _name;
  };

  /* If expression evaluates to true, report successful test, otherwise record failure */
  bool isTrue(bool val, const char* code, const char* file, size_t line);

  /* If expression evaluates to false report successful test, otherwise record failure */
  bool isFalse(bool val, const char* code, const char* file, size_t line);

}

#endif /* BaseTest_hpp */
