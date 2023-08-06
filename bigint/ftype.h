//
// Created by nylon on 02.08.2023.
//

#ifndef FTYPE_H
#define FTYPE_H

struct ftype {
    long double re, im;
    ftype(): re(0), im(0) {}
    ftype(long double re, long double im=0): re(re), im(im) {}
    ftype operator+(const ftype& a);
    ftype operator-(const ftype& a);
    ftype operator*(const ftype& a);
    ftype& operator*=(const ftype& a);
    ftype& operator+=(const ftype& a);
    ftype operator/(const ftype& a);
    ftype& operator/=(const ftype& a);
};


#endif //FTYPE_H
