//
// Created by a404m on 7/3/21.
//

#include "Double.h"

Double::Double() : holder(0) {/*empty*/}

Double::Double(double d) : holder(d) {/*empty*/}

Double::Double(const Double &d) : holder(d.holder) {/*empty*/}

Double &Double::operator=(const Double &d) {
    this->holder = d.holder;
    return *this;
}

Double Double::operator+(const Double &d) const {
    return Double(this->holder + d.holder);
}

Double Double::operator-(const Double &d) const {
    return Double(this->holder - d.holder);
}

Double Double::operator*(const Double &d) const {
    return Double(this->holder * d.holder);
}

Double Double::operator/(const Double &d) const {
    return Double(this->holder / d.holder);
}
