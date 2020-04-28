//
//  Vector.hpp
//  InterestRateModels
//
//  Created by Lewis Brown on 28/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <algorithm>
#include <stdio.h>

namespace mathtypes {

  class BaseVector {
  public:
    
    using iterator = double*;
    using const_iterator = const double*;
    
    BaseVector();
    BaseVector(int dimension);
    BaseVector(const BaseVector& other);
    BaseVector(BaseVector&& other) noexcept;
    ~BaseVector();
    
    BaseVector& operator=(const BaseVector& rhs);
    BaseVector& operator=(BaseVector&& rhs) noexcept;
    
    /* Iterators */
    iterator begin();
    const_iterator cbegin() const noexcept;
    iterator end();
    const_iterator cend() const noexcept;
    
    virtual int dim() const;
    
    void swap(BaseVector& other) noexcept;
    
    friend void swap(BaseVector& lhs, BaseVector& rhs);
    
  private:
    size_t _dimension;
    double * _data;
    
  };
  
}

#endif /* Vector_hpp */

