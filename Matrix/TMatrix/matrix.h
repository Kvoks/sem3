// Copyright (c) Фамилия И.О.
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
        // для массивов можно использовать std-функции с условием, что вы знаете как они там реализованы!
        std::copy(data, data + sz, pMem);
    }

    // индексация
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
      


    // индексация с контролем - почитать в чём разница и объяснить при сдаче работы
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

      // почитать о noexcept(noexcept(T())) - объяснить назначение при сдаче. конструктор перемещения и оператор присваивания с перемещением следует определять с ключевым словом noexcept, ведь он может генерировать исключения
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
    //обязательно ли прописывать это дело по новой
    size_t size() const noexcept {
        return _size;
    }
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

    using TVector<TVector<T>>::operator[];
    
    bool operator==(const TMatrix& m) const noexcept {
        if (_size != m._size) { return false; }
        for (int i = 0; i < _size; i++) {
            if (pMem[i] != m.pMem[i]) { return false; }
        }
        return true;
    }
    bool operator!=(const TMatrix& m) const noexcept { return !(*this == m); }

    
    TMatrix operator*(const T& val) {
        TMatrix<T> tmp(*this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] * val;
        }
        return tmp;
    }

    
    TVector<T> operator*(const TVector<T>& v) {
        if (v.size() != _size) { 
            throw std::logic_error("Not equl size, operation not defined"); 
        }
        TVector<T> tmp(v);
        for (int i = 0; i < _size; i++) {
            tmp[i] = pMem[i] * v;
        }
        return tmp;
    }

    
    TMatrix operator+(const TMatrix& m) {
        if (m._size != _size) { throw std::logic_error("Not equl size, operation not defined"); }
        TMatrix<T> tmp(*this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] + m[i];
        }
        return tmp;
    }
    TMatrix operator-(const TMatrix& m) {
        if (m._size != _size) { 
            throw std::logic_error("Not equl size, operation not defined"); 
        }
        TMatrix<T> tmp(*this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] - m[i];
        }
        return tmp;
    }
    TMatrix operator*(const TMatrix& m) {
        if (m._size != _size) { 
            throw std::logic_error("Not equl size, operation not defined"); 
        }
        TMatrix<T> tmp(_size);
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                tmp[i][j] = m[j][i];
            }
        }
        TMatrix<T> res(_size);
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                res[i][j] = pMem[i] * tmp[j];
            }
        }
        return res;
    }

    friend std::istream& operator>> <T>(std::istream& istr, TMatrix& v);
    friend std::ostream& operator<< <T>(std::ostream& ostr, const TMatrix& v);
};

template<class T>
std::istream& operator>>(std::istream& istr, TMatrix<T>& m) {
    for (size_t i = 0; i < m._size; i++)
        istr >> m[i];
    return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TMatrix<T>& m) {
    for (size_t i = 0; i < m._size; i++) {
        ostr << m.pMem[i] << '\n';
    }
    return ostr;
}

#endif  // INCLUDE_MATRIX_H_

