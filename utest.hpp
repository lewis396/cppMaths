//
//  utest.hpp
//  UnitTest
//
//  Created by Lewis Brown on 26/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//

#ifndef utest_hpp
#define utest_hpp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "BaseTest.hpp"


using ulong = unsigned long;


namespace ut {

  class TestEval {
    
  public:
    void recordError(const std::string& error);
    void recordExprFailure(const std::string& code,
                           const char* file, ulong line);
    ulong getTotalFailures() const;
    void reportError(std::ostream& os) const;
    void reportAllFailures(std::ostream& os) const;
    
  private:
    class ExprEval {
    public:
      ExprEval(const std::string& code, const char* file, ulong line);
      void report(std::ostream& os) const;
    private:
      std::string _code;
      std::string _file;
      ulong _line;
    };
    
    using test_outcomes = std::list<ExprEval>;
    using iterator = test_outcomes::iterator;
    using const_iterator = test_outcomes::const_iterator;
    
    test_outcomes _allExpr;
    std::string _error;
  
  };

  class TestSet {
  public:
    /* Singleton */
    static TestSet& Instance();
    ~TestSet();
    
    static void failure(const std::string& code, const char* file, ulong line);
    static void success();
    
    void addTest(BaseTest* test);
    void handleError(const std::string& msg);
    void recordFailure(const std::string& code, const char* file, ulong line);
    void recordPass();
    /* Report outcome for all tests */
    void report() const;
    /* Run all tests in sequence */
    void run();
    
  private:
    TestSet();
    
    /* Non-copyable to prevent comiler generated versions */
    TestSet(const TestSet&);
    TestSet& operator=(const TestSet&);
    
    void reportTest(BaseTest* test) const;
    void reportFailures(TestEval* eval) const;
    void reportErrors(TestEval* eval) const;
    
    using test_pair = std::pair<BaseTest*,TestEval*>;
    using test_pair_list = std::vector<test_pair>;
    using iterator = test_pair_list::iterator;
    using const_iterator = test_pair_list::const_iterator;
    
    ulong _nError = 0;
    ulong _nTest = 0;
    ulong _nPass = 0;
    ulong _nFail = 0;
    test_pair_list _tests;
  };

}

#endif /* utest_hpp */
