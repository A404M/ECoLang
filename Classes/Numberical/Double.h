//
// Created by a404m on 7/3/21.
//

#ifndef ECOLANG_DOUBLE_H
#define ECOLANG_DOUBLE_H


class Double {
private:
    double holder;
public:
    Double();
    Double(double);

    [[maybe_unused]] Double(const Double&);

    Double& operator=(const Double&);

    Double operator+(const Double&) const;
    Double operator-(const Double&) const;
    Double operator*(const Double&) const;
    Double operator/(const Double&) const;
};


#endif //ECOLANG_DOUBLE_H
