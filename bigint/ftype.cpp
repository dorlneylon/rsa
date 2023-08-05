//
// Created by nylon on 02.08.2023.
//

#include "ftype.h"

ftype ftype::operator+(const ftype &a) {
    return ftype(this->re+a.re, this->im+a.im);
}

ftype ftype::operator-(const ftype &a) {
    return (*this)+ftype(-a.re,-a.im);
}

ftype ftype::operator*(const ftype &a) {
    return ftype(this->re*a.re-this->im*a.im,this->re*a.im+this->im*a.re);
}

ftype& ftype::operator*=(const ftype &a) {
    return *this=*this*a;
}

ftype& ftype::operator+=(const ftype &a) {
    return *this=*this+a;
}

ftype ftype::operator/(const ftype &a) {
    return ftype((this->re*a.re+this->im*a.im)/(a.re*a.re+a.im*a.im),(this->im*a.re-this->re*a.im)/(a.re*a.re+a.im*a.im));
}

ftype& ftype::operator/=(const ftype &a) {
    return *this=*this/a;
}