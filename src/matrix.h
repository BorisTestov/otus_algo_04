#pragma once

class matrix {
public:
    matrix() = default;

    // операция присваивания (copy assignment)
    matrix &operator=(const matrix &newValue) {
        this->value[0][0] = newValue.value[0][0];
        this->value[0][1] = newValue.value[0][1];
        this->value[1][0] = newValue.value[1][0];
        this->value[1][1] = newValue.value[1][1];
        return (*this);
    }

    unsigned long long value[2][2];
};

matrix operator*(const matrix &left, const matrix &right) {
    matrix res;
    res.value[0][0] = left.value[0][0] * right.value[0][0] + left.value[0][1] * right.value[1][0];
    res.value[0][1] = left.value[0][0] * right.value[0][1] + left.value[0][1] * right.value[1][1];
    res.value[1][0] = left.value[1][0] * right.value[0][0] + left.value[1][1] * right.value[1][0];
    res.value[1][1] = left.value[1][0] * right.value[0][1] + left.value[1][1] * right.value[1][1];
    return res;
}

matrix pow(matrix &m, unsigned long long n) {
    matrix res = m;
    while (n > 0) {
        res = res * m;
        --n;
    }
    return res;
}


