//
//  Vector.cpp
//  InterestRateModels
//
//  Created by Lewis Brown on 28/04/2020.
//  Copyright © 2020 Lewis Brown. All rights reserved.
//

#include "Vector.hpp"

namespace mathtypes {

  /* Base Vector */

  BaseVector::BaseVector(): _dimension(0) {
    printf("ctor\n");
    _data = nullptr;
  }

  BaseVector::BaseVector(int dimension) :
  _dimension(0), _data(new double[dimension]) {
    while(_dimension<dimension)
      _data[_dimension++]=0;
  }

  BaseVector::BaseVector(const BaseVector& other) :
  _dimension(other._dimension), _data(new double[other._dimension]) {
    printf("cpy ctor\n");
    std::copy(other._data, other._data+other._dimension, _data);
  }

  BaseVector::BaseVector(BaseVector&& other) noexcept :
  _dimension(0), _data(nullptr) {
    printf("move ctor\n");
    other.swap(*this);
  }

  BaseVector::~BaseVector() {
    delete[] _data;
  }
  
  BaseVector& BaseVector::operator=(const BaseVector &rhs) {
    BaseVector tmp(rhs);
    tmp.swap(*this);
    return *this;
  }
  
  BaseVector& BaseVector::operator=(BaseVector&& rhs) noexcept {
    rhs.swap(*this);
    return *this;
  }
  
  BaseVector::iterator BaseVector::begin() {
    return _data;
  }
  
  BaseVector::const_iterator BaseVector::cbegin() const noexcept {
    return _data;
  }
  
  BaseVector::iterator BaseVector::end() {
    return _data + _dimension*sizeof(double);
  }
  
  BaseVector::const_iterator BaseVector::cend() const noexcept {
    return _data + _dimension*sizeof(double);
  }
  
  int BaseVector::dim() const {
    printf("Dimension is %d\n", _dimension);
    return _dimension;
  }
  
  void BaseVector::swap(BaseVector& other) noexcept {
      std::swap(_dimension, other._dimension);
      std::swap(_data, other._data);
  }
  
  void swap(BaseVector& lhs, BaseVector& rhs) {
    lhs.swap(rhs);
  }
  
} /* namespace mathtypes */

