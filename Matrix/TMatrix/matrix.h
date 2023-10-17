// Copyright (c) ‘амили€ ».ќ.
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <assert.h>
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template <typename T> class TVector;

template <typename T> std::istream& operator>>(std::istream& istr, TVector<T>& v);

template <typename T> std::ostream& operator<<(std::ostream& out, const TVector<T>& vec);


template<typename T>
class TVector {
protected:
    size_t _size;
    T* pMem;
public:
    TVector() : pMem(nullptr), _size(0) {}
    TVector(size_t sz) : _size(sz) {
        if (sz == 0)
            throw std::length_error("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Vector size cannot be greater than MAX_VECTOR_SIZE = 100000000");
        if (sz < 0)
            throw std::length_error("Vector size cannot be less than zero");
        pMem = new T[sz]();
    }

    TVector(T* data, size_t sz) : _size(sz) {
        // еще один способ ввода исключений
        assert(data != nullptr && "TVector constructor requires non-nullptr argument.");
        pMem = new T[sz];
        // дл€ массивов можно использовать std-функции с условием, что вы знаете как они там реализованы!
        std::copy(data, data + sz, pMem);
    }

    // индексаци€
    T& operator[](size_t ind) {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const {
        return pMem[ind];
    }

    ~TVector() {
        delete[] pMem;
    }
    
    TVector(const TVector& v) : _size(v._size) {
        pMem = new T[v._size];
        std::copy(v.pMem, v.pMem + _size, pMem);
    }
    
      
    TVector(TVector&& v) noexcept:pMem(nullptr), _size(0) {
        std::swap(v.pMem, pMem);
        std::swap(v._size, _size);
      }

    size_t size() const noexcept {
        return _size;
    }
      
      TVector& operator=(const TVector& v){
          if (this == &v){ 
              return *this;
          }
          _size = v._size;
          if (pMem != nullptr) {
              delete[]pMem;
          }
          pMem = new T[_size];
          std::copy(v.pMem, v.pMem + _size, pMem);
          return *this;
      }
      TVector& operator=(TVector&& v) noexcept {
          if (this == &v) {
              return *this; 
          }
          delete[] pMem;
          pMem = nullptr;
          _size = 0;
          std::swap(pMem, v.pMem);
          std::swap(_size, v._size);
          return *this;
      }
      


    // индексаци€ с контролем - почитать в чЄм разница и объ€снить при сдаче работы
      T& at(size_t ind) {
          if ((ind > _size - 1) || (ind < 0)) {
              throw std::out_of_range("Impossible to use a non-existent index");
          }
          return pMem[ind];
      }
      const T& at(size_t ind) const {
          if ((ind > _size - 1) || (ind < 0)) {
              throw std::out_of_range("Impossible to use a non-existent index");
          }
          return pMem[ind];
      }
      
    // сравнение
      bool operator==(const TVector& v) const noexcept {
          if (_size != v._size) {
              return false;
          }
          for (int i = 0; i < _size; i++) {
              if (pMem[i] != v.pMem[i]) {
                  return false;
              }
          }
          return true;
      }
      bool operator!=(const TVector& v) const noexcept {
          return not(*this == v);
      }
      /*
      TVector operator+(double val) {

      }
      TVector operator-(double val) {

      }
      TVector operator*(double val) {

      }
      */
      TVector operator+(T val) {
          TVector<T> l(*this);
          for (int i = 0; i < _size; i++) {
              l[i] = l[i] + val;
          }
          return l;
      }
      TVector operator-(T val) {
          TVector<T> l(*this);
          for (int i = 0; i < _size; i++) {
              l[i] = l[i] - val;
          }
          return l;
      }
      TVector operator*(T val) {
          TVector<T> l(*this);
          for (int i = 0; i < _size; i++) {
              l[i] = l[i] * val;
          }
          return l;
      }

      TVector operator+(const TVector& v) {
          if (_size != v._size){ 
              throw std::logic_error("Unequal dimensions"); 
          }
          TVector<T> l(*this);
          for (int i = 0; i < _size; i++) {
              l[i] = l[i] + v[i];
          }
          return l;
      }
      TVector operator-(const TVector& v) {
          if (_size != v._size) {
              throw std::logic_error("Unequal dimensions");
          }
          TVector<T> l(*this);
          for (int i = 0; i < _size; i++) {
              l[i] = l[i] - v[i];
          }
          return l;
      }

      // почитать о noexcept(noexcept(T())) - объ€снить назначение при сдаче. конструктор перемещени€ и оператор присваивани€ с перемещением следует определ€ть с ключевым словом noexcept, ведь он может генерировать исключени€
      T operator*(const TVector& v) noexcept(T()) {
          if (_size != v._size) { 
              throw std::logic_error("Unequal dimensions"); 
          }
          T l = 0;
          for (int i = 0; i < _size; i++) {
              l = l + v[i] * (*this)[i];
          }
          return l;
      }

    friend void swap(TVector& lhs, TVector& rhs) noexcept;

    // ввод/вывод
    friend std::istream& operator>> <T>(std::istream& istr, TVector<T>& v);
    friend std::ostream& operator<< <T>(std::ostream& ostr, const TVector<T>& v);
};
template <typename T>
void swap(TVector<T>& lhs, TVector<T>& rhs) noexcept {
    std::swap(lhs._size, rhs._size);
    std::swap(lhs.pMem, rhs.pMem);
}

// ввод/вывод
template <typename T>
std::istream& operator>>(std::istream& istr, TVector<T>& v) {
    for (size_t i = 0; i < v._size; i++)
        istr >> v.pMem[i];
    return istr;
}
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v) {
    for (size_t i = 0; i < v._size; i++)
        ostr << v.pMem[i] << ' ';
    return ostr;
}

template<typename T>
class TMatrix : private TVector<TVector<T>> {
    using TVector<TVector<T>>::pMem;
    using TVector<TVector<T>>::_size;
public:
    
    TMatrix(size_t s) : TVector<TVector<T>>(s) {
        if (s == 0)
            throw std::length_error("Matrix size should be greater than zero");
        if (s > MAX_MATRIX_SIZE)
            throw std::length_error("Matrix size cannot be greater than MAX_MATRIX_SIZE = 10000");
        for (size_t i = 0; i < s; i++)
            pMem[i] = TVector<T>(s);
    }
    
    // почему можно сделать так? ќбъ€снить.
    using TVector<TVector<T>>::operator[];
    /*
    // сравнение
    bool operator==(const TMatrix& m) const noexcept;
    bool operator!=(const TMatrix& m) const noexcept;

    // матрично-скал€рные операции
    TMatrix operator*(const T& val);

    // матрично-векторные операции
    TVector<T> operator*(const TVector<T>& v);

    // матрично-матричные операции
    TMatrix operator+(const TMatrix& m);
    TMatrix operator-(const TMatrix& m);
    TMatrix operator*(const TMatrix& m);

    // ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TMatrix& v);
    friend std::ostream& operator<<(std::ostream& ostr, const TMatrix& v);
    */
};

#endif  // INCLUDE_MATRIX_H_