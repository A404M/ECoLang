//
// Created by a404m on 7/3/21.
//

#include "Int.h"

Int::Int() : holder(0) {/*empty*/}

Int::Int(int i) : holder(i) {/*empty*/}

Int::Int(const Int &i) : holder(i.holder) {/*empty*/}

Int &Int::operator=(const Int &i) {
    this->holder = i.holder;
    return *this;
}

Int Int::operator+(const Int &i) const {
    return Int(this->holder + i.holder);
}

Int Int::operator-(const Int &i) const {
    return Int(this->holder - i.holder);
}

Int Int::operator*(const Int &i) const {
    return Int(this->holder * i.holder);
}

Int Int::operator/(const Int &i) const {
    return Int(this->holder / i.holder);
}

Int Int::operator%(const Int &i) const {
    return Int(this->holder % i.holder);
}
