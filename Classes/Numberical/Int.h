//
// Created by a404m on 7/3/21.
//

#ifndef ECOLANG_INT_H
#define ECOLANG_INT_H

#include "Double.h"

class Int {
private:
    int holder{};
public:
    Int();
    Int(int);
    Int(const Int&);

    Int& operator=(const Int&);

    Int operator+(const Int&) const;
    Int operator-(const Int&) const;
    Int operator*(const Int&) const;
    Int operator/(const Int&) const;
    Int operator%(const Int&) const;
};


#endif //ECOLANG_INT_H
