#pragma once

#include <sstream>
#include "BigInt.h"

class BigFloat {
public:
    BigInt numerator; // Целая часть
    BigInt denumerator; // Дробная часть
    unsigned long long precision = 100; // Количество выводимых цифр после "."

    BigFloat() = default; // Конструктор по-умолчанию, 0.0

    BigFloat(const std::string &value);

    BigFloat(const BigFloat &bigFloat); // Конструктор копирования

    const std::string &getNumeratorValue() const;  // Получить содержимое числителя

    const std::string &getDenumeratorValue() const;  // Получить содержимое знаменателя

    const bool getIsNeg() const; // Получить флаг отрицательности

    void setIsNeg(bool isNeg); // Установка флага отрицательности

    int sign() const; // Получение знача числа

    const bool isEven() const; // Проверка на четность

    BigFloat abs() const; // получение модуля числа
    BigFloat pow(long n) const; // получение числа в степени n
    BigFloat sqrt(long n = 2) const; // вычисление корня n-ой степени из числа

    void setPrecision(unsigned long long newPrecision);  // Установка точности при выводе

    void precise(); // Установить нужную длину знаменателя

    explicit operator std::string() const {
        std::stringstream ss;
        ss << (this->getIsNeg() ? "-" : "") << this->getNumeratorValue() << "." << this->getDenumeratorValue();
        return ss.str();
    };

    // операции сравнения
    const bool operator==(const BigFloat &bigFloat) const;

    const bool operator!=(const BigFloat &bigFloat) const;

    const bool operator<(const BigFloat &bigFloat) const;

    const bool operator>(const BigFloat &bigFloat) const;

    const bool operator<=(const BigFloat &bigFloat) const;

    const bool operator>=(const BigFloat &bigFloat) const;

    // операция присваивания
    BigFloat &operator=(const BigFloat &bigFloat);

    // унарные плюс и минус
    BigFloat operator+();

    BigFloat operator-();

    // арифметические операции
    BigFloat operator+(BigFloat bigFloat);

    BigFloat operator-(BigFloat bigFloat);

    BigFloat operator*(BigFloat bigFloat);

    BigFloat operator/(BigFloat bigFloat);

    BigFloat operator%(BigFloat bigFloat);

    BigFloat operator<<(size_t n) const;

    BigFloat operator>>(size_t n) const;

    // краткая форма операций
    BigFloat &operator+=(const BigFloat &bigFloat);

    BigFloat &operator-=(const BigFloat &bigFloat);

    BigFloat &operator*=(const BigFloat &bigFloat);

    BigFloat &operator/=(const BigFloat &bigFloat);

    BigFloat &operator%=(const BigFloat &bigFloat);

    BigFloat &operator<<=(size_t n);

    BigFloat &operator>>=(size_t n);

    // префиксная форма
    BigFloat &operator++(); // ++v
    BigFloat &operator--(); // --v

    // постфиксная форма
    BigFloat operator++(int); // v++
    BigFloat operator--(int); // v--


    friend std::ostream &operator<<(std::ostream &stream, const BigFloat &bigFloat); // вывод числа в выходной поток
    friend std::istream &operator>>(std::istream &stream, BigFloat &bigFloat); // ввод числа из входного потока
};