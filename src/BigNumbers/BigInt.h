#pragma once

#include <iostream>
#include <string>

class BigInt {
    std::string value; // значение числа
    bool isNeg; // флаг отрицательности

    static BigInt karatsuba_mul(const BigInt &a, const BigInt &b); // умножение методом Карацубы

public:
    BigInt();

    BigInt(long x);

    BigInt(const std::string &value, bool removeLeadingZeros = true);

    BigInt(const BigInt &bigInt);

    const std::string &getValue() const;

    const bool getIsNeg() const;

    void setIsNeg(bool isNeg);

    int sign() const;

    const bool isEven() const;

    BigInt abs() const;

    BigInt pow(long n) const;

    BigInt sqrt(long n = 2) const;

    // операции сравнения
    const bool operator==(const BigInt &bigInt) const;

    const bool operator!=(const BigInt &bigInt) const;

    const bool operator<(const BigInt &bigInt) const;

    const bool operator>(const BigInt &bigInt) const;

    const bool operator<=(const BigInt &bigInt) const;

    const bool operator>=(const BigInt &bigInt) const;

    // операция присваивания
    BigInt &operator=(const BigInt &bigInt);

    // унарные плюс и минус
    BigInt operator+() const &&;

    BigInt operator-() const &&;

    // арифметические операции
    BigInt operator+(const BigInt &bigInt) const;

    BigInt operator-(const BigInt &bigInt) const;

    BigInt operator*(const BigInt &bigInt) const;

    BigInt operator/(const BigInt &bigInt) const;

    BigInt operator%(const BigInt &bigInt) const;

    BigInt operator<<(size_t n) const;

    BigInt operator>>(size_t n) const;

    // краткая форма операций
    BigInt &operator+=(const BigInt &bigInt);

    BigInt &operator-=(const BigInt &bigInt);

    BigInt &operator*=(const BigInt &bigInt);

    BigInt &operator/=(const BigInt &bigInt);

    BigInt &operator%=(const BigInt &bigInt);

    BigInt &operator<<=(size_t n);

    BigInt &operator>>=(size_t n);

    // префиксная форма
    BigInt &operator++(); // ++v
    BigInt &operator--(); // --v

    // постфиксная форма
    BigInt operator++(int); // v++
    BigInt operator--(int); // v--


    friend std::ostream &operator<<(std::ostream &stream, const BigInt &bigInt); // вывод числа в выходной поток
    friend std::istream &operator>>(std::istream &stream, BigInt &bigInt); // ввод числа из входного потока
};