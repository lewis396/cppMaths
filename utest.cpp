//
//  utest.cpp
//  UnitTest
//
//  Created by Lewis Brown on 26/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//

#include "utest.hpp"

const std::string seperator("------------------------------------------------------------\n");

namespace ut {

  void TestEval::recordError(const std::string& error) {
    _error = error;
  }

  void TestEval::recordExprFailure(const std::string& code,
            const char* file, size_t line) {
    _allExpr.push_back(ExprEval(code,file,line));
    
    return;
  }

  unsigned long TestEval::getTotalFailures() const {
    return _allExpr.size();
  }

  void TestEval::reportError(std::ostream& os) const {
    os<<"Error: "<< _error <<"\n";
  }

  /* Iterate through the list and display appropriate output */
  void TestEval::reportAllFailures(std::ostream& os) const {
    const_iterator currentExpr;
    for( currentExpr = _allExpr.begin(); currentExpr!=_allExpr.end();++currentExpr)
      currentExpr->report(os);
  }


  /* TestEval::ExprEval */

  TestEval::ExprEval::ExprEval
  (const std::string &code, const char* file, size_t line)
  :_code(code), _file(file), _line(line) { }

  void TestEval::ExprEval::report(std::ostream &os) const {
    os << "Test " << _code << " failed in file "
    << _file << " on line " << _line <<".\n";
  }


  /* TestSet */

  TestSet& TestSet::Instance() {
    static TestSet instance;
    return instance;
  }

  TestSet::TestSet() { }

  TestSet::~TestSet() {
    iterator currentTest;

    for (currentTest = _tests.begin(); currentTest != _tests.end(); ++currentTest) {
      ut::TestEval* test_eval = currentTest->second;
      delete test_eval;
    }
  }

  void TestSet::failure(const std::string& code, const char* file, size_t line) {
    TestSet::Instance().recordFailure(code, file, line);
  }

  void TestSet::addTest(BaseTest* test) {
    TestEval* evaluation = new TestEval();
    _tests.push_back(std::make_pair(test, evaluation));
  }

  void TestSet::handleError(const std::string& msg) {
    ++_nError;
    test_pair test_entry = _tests[_nTest];
    TestEval* result = test_entry.second;
    result->recordError(msg);
  }

  void TestSet::recordFailure(const std::string& code, const char* file, size_t line) {
    test_pair test_entry = _tests[_nTest];
    TestEval* result = test_entry.second;
    result->recordExprFailure(code, file, line);
  }

  void TestSet::report() const {
    std::cout << seperator << "\n";
    std::cout << "Ran " << _nTest << " test(s)\n\n";
    std::cout << "Passes:   " << _nPass << "\n";
    std::cout << "Failures: " << _nFail << "\n";
    std::cout << "Errors:   " << _nError << "\n\n";
    std::cout << seperator;
      
    const_iterator current;
  
    for (current = _tests.begin(); current != _tests.end(); ++current) {
      ut::BaseTest* test = current->first;
      ut::TestEval* test_result = current->second;
      std::cout << "Test: " << test->name() << "\n\n";
      reportTest(test);
      reportFailures(test_result);
      reportErrors(test_result);
      std::cout << "\n" << seperator << "\n";
    }
  
      std::cout << std::endl;
  }

  /* Sequentially run all tests */
  void TestSet::run() {
    iterator currentPair;
    _nTest = 0;

    for (currentPair = _tests.begin(); currentPair != _tests.end(); ++currentPair, ++_nTest) {
      try
      {
        BaseTest* test = currentPair->first;
        TestEval* testEval = currentPair->second;

        if( test->setUp() ) {
          test->run();
          if( testEval->getTotalFailures()==0 )
            ++_nPass;
          else
            ++_nFail;
          if( !test->tearDown() )
            // handle test teatdown error
            handleError("Error occurred while tearing down the test");
          }
        else
          // handle test setup error
          handleError("Setup failed");
      }
      catch (std::exception& e)
      {
        // handle known errors
        handleError(e.what());
      }
      catch (...)
      {
        // handle any other errors
        handleError("Unexpected error");
      }
    }
  }

  void TestSet::reportTest(BaseTest* test) const {
      std::cout << "Output:\n";
      test->writeToConsole(std::cout);
    }
  
    void TestSet::reportFailures(TestEval* test_result) const {
      std::cout << std::endl;
  
      if (_nFail > 0) {
        std::cout << "Failures:\n";
        test_result->reportAllFailures(std::cout);
      }
      else {
        std::cout << "No failures.\n";
      }
    }
  
    void TestSet::reportErrors(TestEval* test_result) const
    {
      std::cout << std::endl;
  
      if (_nError > 0)
      {
        test_result->reportError(std::cout);
      }
      else
      {
        std::cout << "No errors.\n";
      }
    }

}
