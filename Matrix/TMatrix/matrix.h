// Copyright (c) ������� �.�.
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <vector>
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
        pMem = new T[sz]();
    }

    TVector(T* data, size_t sz) : _size(sz) {
        // ��� ���� ������ ����� ����������
        assert(data != nullptr && "TVector constructor requires non-nullptr argument.");
        pMem = new T[sz];
        // ��� �������� ����� ������������ std-������� � ��������, ��� �� ������ ��� ��� ��� �����������!
        std::copy(data, data + sz, pMem);
    }

    /*~TVector() {
        delete[]pMem;
    };

    TVector(const TVector& v);

      TVector(TVector&& v) noexcept;

      ~TVector() {
          delete[]pMem;
      };

      TVector& operator=(const TVector& v);

      TVector& operator=(TVector&& v) noexcept;

      size_t size() const noexcept;

    // ����������
      T& operator[](size_t ind);
      const T& operator[](size_t ind) const;

    // ���������� � ��������� - �������� � ��� ������� � ��������� ��� ����� ������
      T& at(size_t ind);
      const T& at(size_t ind) const;

    // ���������
      bool operator==(const TVector& v) const noexcept;
      bool operator!=(const TVector& v) const noexcept;

      TVector operator+(double val);
      TVector operator-(double val);
      TVector operator*(double val);

      TVector operator+(T val);
      TVector operator-(T val);
      TVector operator*(T val);

      TVector operator+(const TVector& v);
      TVector operator-(const TVector& v);

      // �������� � noexcept(noexcept(T())) - ��������� ���������� ��� �����
      T operator*(const TVector& v) noexcept(noexcept(T()));*/

    friend void swap(TVector& lhs, TVector& rhs) noexcept;

    // ����/�����
    friend std::istream& operator>> <T>(std::istream& istr, TVector<T>& v);
    friend std::ostream& operator<< <T>(std::ostream& ostr, const TVector<T>& v);
};
template <typename T>
void swap(TVector<T>& lhs, TVector<T>& rhs) noexcept {
    std::swap(lhs._size, rhs._size);
    std::swap(lhs.pMem, rhs.pMem);
}

// ����/�����
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
    TMatrix(size_t s = 1) : TVector<TVector<T>>(s) {
        for (size_t i = 0; i < s; i++)
            pMem[i] = TVector<T>(s);
    }
    /*
    // ������ ����� ������� ���? ���������.
    using TVector<TVector<T>>::operator[];

    // ���������
    bool operator==(const TMatrix& m) const noexcept;
    bool operator!=(const TMatrix& m) const noexcept;

    // ��������-��������� ��������
    TMatrix operator*(const T& val);

    // ��������-��������� ��������
    TVector<T> operator*(const TVector<T>& v);

    // ��������-��������� ��������
    TMatrix operator+(const TMatrix& m);
    TMatrix operator-(const TMatrix& m);
    TMatrix operator*(const TMatrix& m);

    // ����/�����
    friend std::istream& operator>>(std::istream& istr, TMatrix& v);
    friend std::ostream& operator<<(std::ostream& ostr, const TMatrix& v);
    */
};

#endif  // INCLUDE_MATRIX_H_