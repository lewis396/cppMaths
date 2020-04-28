//
//  BaseTest.cpp
//  UnitTest
//
//  Created by Lewis Brown on 26/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//

#include "BaseTest.hpp"
#include "utest.hpp"


namespace ut
{
  namespace
  {
    void fail(const char* message, const char* file, size_t line) {
      TestSet::failure(message, file, line);
    }
  }

  BaseTest::BaseTest(const std::string& name)
   : _name(name)
  {
    TestSet::Instance().addTest(this);
  }
    
  BaseTest::~BaseTest(){}

  bool BaseTest::setUp()
  {
    return true;
  }

  void BaseTest::run()
  {
     fail("run() member function has not been implemented for this test", __FILE__, __LINE__);
  }

  bool BaseTest::tearDown()
  {
    return true;
  }

  std::string BaseTest::name()
  {
    return _name;
  }

  void BaseTest::writeToConsole(std::ostream& os) const
  {
    os << _test_out.str();
  }

  bool isTrue(bool val, const char* code, const char* file, size_t line)
  {
    if (!val)
    {
      std::string str = "IS_TRUE(" + std::string(code) + ")";
      TestSet::failure(str, file, line);
    }
    return !val;
  }

  bool isFalse(bool val, const char* code, const char* file, size_t line)
  {
    if (val)
    {
      std::string str = "IS_FALSE(" + std::string(code) + ")";
      TestSet::failure(str, file, line);
    }
    return val;
  }

} // namespace ut
