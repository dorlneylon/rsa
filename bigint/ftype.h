//
// Created by nylon on 02.08.2023.
//

#ifndef FTYPE_H
#define FTYPE_H

struct ftype {
    double re, im;
    ftype(): re(0), im(0) {}
    ftype(double re, double im): re(re), im(im) {}
    ftype(double re): re(re), im(0) {}
    ftype operator+(const ftype& a);
    ftype operator-(const ftype& a);
    ftype operator*(const ftype& a);
    ftype& operator*=(const ftype& a);
    ftype& operator+=(const ftype& a);
    ftype operator/(const ftype& a);
    ftype& operator/=(const ftype& a);
};


#endif //FTYPE_H
