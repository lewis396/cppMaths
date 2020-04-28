// -------------------------------------------------------------------------
// DISCLAIMER
// -------------------------------------------------------------------------
// The code in the files "BaseTest.hpp", "utest.hpp", the corresponding .cpp
// files and this file, "BaseVectorTest.hpp" closely follows the design and
// implementation of a unit testing framework by Crickett Software Limited,
// 2001. The code presented here is adapted from Crickett's and will
// hopefully diverge further from the original in future versions. However,
// the code created by Crickett was essential in building my understanding
// of unit testing and for that I extend my gratitude.
// Please find the article by Crickett Software Limited at
//    https://accu.org/index.php/journals/368
// and observe the copyright below.
// -------------------------------------------------------------------------
// Copyright Crickett Software Limited, 2001. All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives, and that no
// charge may be made for the software and its documentation except to cover
// cost of distribution.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
// -------------------------------------------------------------------------


#include "BaseTest.hpp"
#include "Vector.hpp"

#include <iostream>

using namespace mathtypes;


/* All test inherit from the BaseTest */
class BaseVectorTest : public ut::BaseTest
{
public:

  /* Pass the test name to the base class */
  explicit BaseVectorTest(const std::string& name)
   : ut::BaseTest(name) { }
  
  /* setUp, run and tearDown must be overwritten */
  virtual bool setUp() {
    try
    {
      /* Testing all constructors */
      _vect1 = new BaseVector;
      _vect2 = new BaseVector(5);
      _vect3 = new BaseVector(*_vect2);
      BaseVector rval(5);
      _vect4 = new BaseVector(std::move(rval));
    }
    catch(std::bad_alloc& e)
    {
      std::cerr << "Error setting up test: " << e.what() << std::endl;
      return false;
    }
    return true;
  }

  virtual void run() {
    /* Test Default Object (Degenerate case) */
    testDefualts();
    testDefaultIterators();
    testDefaultConstIterators();
    /* Check consistency across the constructors */
    testSzCpyCtor();
    //testCpyMvCtor();
    testMvSzCtor();
    
  }
  
  void testGetters() {
    IS_TRUE(_vect2->dim()==5);
  }
  
  virtual bool tearDown() {
    delete _vect1;
    delete _vect2;
    delete _vect3;
    delete _vect4;
    return true;
  }
  
  void testDefualts() {
    size_t dim = _vect1->dim();
    double* result = _vect1->begin();
    IS_TRUE(dim == 0 && nullptr == result);
  }
  
  void testDefaultIterators() {
    BaseVector::iterator begin = _vect1->begin();
    BaseVector::iterator end = _vect1->end();
    IS_TRUE(begin == end);
  }
  
  void testDefaultConstIterators() {
    BaseVector::iterator begin = _vect1->begin();
    BaseVector::iterator end = _vect1->end();
    IS_TRUE(begin == end);
  }
  
  void testSzCpyCtor(){
    size_t sz2 = _vect2->dim(), sz3 = _vect3->dim();
    printf("%d %d\n", _vect2->dim(), _vect3->dim());
    IS_TRUE(sz2 == sz3);
  }
  
  void testMvSzCtor(){
    size_t sz2 = _vect2->dim(), sz4 = _vect4->dim();
    printf("%d %d\n", _vect2->dim(), _vect4->dim());
    IS_TRUE(sz2 == sz4);
  }
  
  void testCpyMvCtor() {
    
  }

private:
  mathtypes::BaseVector* _vect1;
  mathtypes::BaseVector* _vect2;
  mathtypes::BaseVector* _vect3;
  mathtypes::BaseVector* _vect4;
};

static BaseVectorTest the_test("BaseVector Test");
