//
// Created by robosam2003 on 30/06/2022.
//
#include "VectorOld.h"

// constructors
template<typename T>
Vector<T>::Vector(int size) {
    if (size<0) size = 0; /// minimum Vector length is 0
    elem = new T[size];
    sz = size;
    for (int i=0;i<sz;i++) elem[i] = 0;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> lst) { // usage: Vector<int> vec {1, 2 ,3} // creates a vector vec of size 3
    elem = new T[lst.size()];
    sz = static_cast<int>(lst.size());
    std::copy(lst.begin(), lst.end(), elem); // copy from lst to elem
}

// default constructor - defaults to size 3 - needed for implementations like e.g. Fifo<Vector<double>>
template<typename T>
Vector<T>::Vector() {
    elem = new T[3]; // default to 3
    sz = 3;
    for (int i=0;i<sz;i++) elem[i] = 0;
}

// operators
template<typename T>
T &Vector<T>::operator[](int i) const {
//    if (i<0) return 0;
//    if (i>=sz) return 0;
    return elem[i];
}

template<typename T>
int Vector<T>::size() const {
    return sz;
}

template<typename T>
Vector<T> Vector<T>::operator*(double scalar) const {
    Vector<T> v(sz);
    for (int i=0; i<sz; i++) {
        v[i] = elem[i] * scalar;
    }
    return v;

}

template<typename T>
Vector<T> Vector<T>::operator/(double scalar) const {
    Vector<T> v(sz);
    for (int i=0; i<sz; i++) {
        v[i] = elem[i] / scalar;
    }
    return v;
}

template<typename T>
Vector<T>& Vector<T>::operator/=(double scalar) {
    for (int i=0; i<sz; i++) {
        elem[i] /= scalar;
    }
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator*=(double scalar) {
    for (int i=0; i<sz; i++) {
        elem[i] *= scalar;
    }
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator+=(Vector<T> v)  {
    for (int i=0; i<sz; i++) {
        elem[i] += v[i];
    }
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator-=(Vector<T> v) {
    for (int i=0; i<sz; i++) {
        elem[i] -= v[i];
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(Vector<T> v) const{
    Vector<T> rv(sz);
    for (int i=0; i<sz; i++) {
        rv[i] = elem[i] + v[i];
    }
    return rv;
}

template<typename T>
Vector<T> Vector<T>::operator-(Vector<T> v) {
    Vector<T> rv(sz);
    for (int i=0; i<sz; i++) {
        rv[i] = elem[i] - v[i];
    }
    return rv;
}


// Vector operations
template<typename T>
double Vector<T>::norm() const {
    double sum = 0;
    for (int i=0; i<sz; i++) {
        sum += elem[i] * elem[i];
    }
    return sqrt(sum);
}

template<typename T>
double Vector<T>::dot(Vector<T> v) const {
    double sum = 0;
    for (int i=0; i<sz; i++) {
        sum += elem[i] * v[i];
    }
    return sum;
}

template<typename T>
Vector<T> &Vector<T>::normalize() {
    double norm = this->norm();
    this /= norm;
    return *this;
}

template<typename T>
Vector<T> Vector<T>::normalized() const {
    double norm = this->norm();
    Vector<T> v(sz);
    v /= norm;
    return v;
}

template<typename T>
Vector<T> Vector<T>::cross(Vector<T> v) const {
    /// only works for 3D vectors
    Vector<T> rv = {0, 0, 0};
    rv[0] = elem[1] * v[2] - elem[2] * v[1]; // i
    rv[1] = elem[2] * v[0] - elem[0] * v[2]; // j
    rv[2] = elem[0] * v[1] - elem[1] * v[0]; // k
    return rv;
}

template<typename T>
Vector<T> Vector<T>::directionCosines() const {
    /// Note that: l^2 + m^2 + n^2 = 1
    Vector<T> rv = {0, 0, 0};
    double norm = this->norm();
    rv[0] = elem[0] / norm; /// l = cos(alpha) = x/r
    rv[1] = elem[1] / norm; /// m = cos(beta) = y/r
    rv[2] = elem[2] / norm; /// n = cos(gamma) = z/r
    return rv;
}



// copy constructor
template<typename T>
Vector<T>::Vector(const Vector &a) {
    elem = new T[sz];
    sz = a.sz;
    // copy elements
    for (int i=0;i<sz;i++) {
        elem[i] = a.elem[i];
    }
}

// copy assignment
template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &a) {
    T* p = new T[a.sz];
    for (int i=0;i<a.sz;i++){
        p[i] = a.elem[i];
    }
    delete[] elem; // delete old elems
    elem = p;
    return *this;
}


// move constructor
template<typename T>
Vector<T>::Vector(Vector &&a) noexcept {
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
}

// move assignment
template<typename T>
Vector<T>& Vector<T>::operator=(Vector &&a)  noexcept {
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}


