#include <algorithm>
#include "BigFloat.h"

BigFloat::BigFloat(const std::string &value) {
    if (!value.length()) {
        return;
    }
    bool negative = value[0] == '-';
    if (value.find(".") == std::string::npos) {
        numerator = BigInt(value);
        denumerator = BigInt("0");
        numerator.setIsNeg(negative);
        precise();
        return;
    }
    numerator = BigInt(value.substr(negative, value.find('.') - negative));
    numerator.setIsNeg(negative);
    auto denumerator_value = value.substr(value.find('.') + 1, value.length());
    denumerator = BigInt(denumerator_value, false);
    precise();
}

BigFloat::BigFloat(const BigFloat &bigFloat) {
    this->numerator = bigFloat.numerator;
    this->denumerator = bigFloat.denumerator;
    this->precision = bigFloat.precision;
}

const std::string &BigFloat::getNumeratorValue() const {
    return numerator.getValue();
}

const std::string &BigFloat::getDenumeratorValue() const {
    return denumerator.getValue();
}

const bool BigFloat::getIsNeg() const {
    return numerator.getIsNeg();
}

void BigFloat::setIsNeg(bool isNeg) {
    numerator.setIsNeg(isNeg);
}

int BigFloat::sign() const {
    return numerator.sign();
}

const bool BigFloat::isEven() const {
    return (denumerator.getValue() == "0" && numerator.isEven());
}

void BigFloat::setPrecision(unsigned long long int newPrecision) {
    precision = newPrecision;
}

const bool BigFloat::operator==(const BigFloat &bigFloat) const {
    return (numerator == bigFloat.numerator && denumerator == bigFloat.denumerator);
}

const bool BigFloat::operator!=(const BigFloat &bigFloat) const {
    return !(*this == bigFloat);
}

const bool BigFloat::operator<(const BigFloat &bigFloat) const {
    return (numerator < bigFloat.numerator ||
            (numerator == bigFloat.numerator && denumerator < bigFloat.denumerator));
}

const bool BigFloat::operator>(const BigFloat &bigFloat) const {
    return !(*this < bigFloat || *this == bigFloat);
}

const bool BigFloat::operator<=(const BigFloat &bigFloat) const {
    return *this < bigFloat || *this == bigFloat;
}

const bool BigFloat::operator>=(const BigFloat &bigFloat) const {
    return *this > bigFloat || *this == bigFloat;
}

BigFloat &BigFloat::operator=(const BigFloat &bigFloat) {
    numerator = bigFloat.numerator;
    denumerator = bigFloat.denumerator;
    precision = bigFloat.precision;
    return *this;
}

BigFloat BigFloat::operator+() {
    return BigFloat(*this);
}

BigFloat BigFloat::operator-() {
    return BigFloat(numerator.getIsNeg() ? getNumeratorValue() + "." + getDenumeratorValue() :
                    "-" + getNumeratorValue() + "." + getDenumeratorValue());
}

void BigFloat::precise() {
    if (getDenumeratorValue().length() < precision) {
        denumerator = BigInt(getDenumeratorValue() + std::string(precision - getDenumeratorValue().length(), '0'),
                             false);
    } else {
        denumerator = BigInt(getDenumeratorValue().substr(0, precision), false);
    }
}

BigFloat BigFloat::operator+(BigFloat bigFloat) {
    BigInt v1(getNumeratorValue() + getDenumeratorValue());
    v1.setIsNeg(getIsNeg());
    BigInt v2(bigFloat.getNumeratorValue() + bigFloat.getDenumeratorValue());
    v2.setIsNeg(bigFloat.getIsNeg());
    auto max_digits_in_numerator = std::max(getNumeratorValue().length(), bigFloat.getNumeratorValue().length());
    if (max_digits_in_numerator == 1 && getNumeratorValue()[0] == '0' && bigFloat.getNumeratorValue()[0] == '0')
        max_digits_in_numerator--;
    auto max_len = std::max(v1.getValue().length(), v2.getValue().length());  // Максимальное количество цифр
    BigInt res = v1 + v2;
    const auto &res_value = res.getValue();
    bool shift = res_value.length() > max_len; // Был перенос на 1 символ, например 82 + 30 = 110
    auto new_numerator = res_value.substr(0, max_digits_in_numerator + shift); // До точки
    auto new_denumerator = res_value.substr(max_digits_in_numerator + shift); // До конца
    std::string res_str = res.getIsNeg() ? "-" : "";
    res_str += new_numerator + "." + new_denumerator;
    BigFloat result(res_str);
    return result;
}

BigFloat BigFloat::operator-(BigFloat bigFloat) {
    BigInt v1(getNumeratorValue() + getDenumeratorValue());
    v1.setIsNeg(getIsNeg());
    BigInt v2(bigFloat.getNumeratorValue() + bigFloat.getDenumeratorValue());
    v2.setIsNeg(bigFloat.getIsNeg());
    auto max_digits_in_numerator = std::max(getNumeratorValue().length(), bigFloat.getNumeratorValue().length());
    auto max_len = std::max(v1.getValue().length(), v2.getValue().length());  // Максимальное количество цифр
    BigInt res = v1 - v2;
    std::string res_str = res.getIsNeg() ? "-" : "";
    bool zeroValue = max_len - res.getValue().length() == max_digits_in_numerator;
    std::string new_numerator;
    std::string new_denumerator;
    if (zeroValue) {
        new_numerator = "0";
        new_denumerator = res.getValue();
    } else {
        const auto &res_value = res.getValue();
        bool shift = res_value.length() < max_len; // Был перенос на 1 символ, например 82 - 80 = 2
        new_numerator = res_value.substr(0, max_digits_in_numerator - shift); // До точки
        new_denumerator = res_value.substr(max_digits_in_numerator - shift); // До конца
    }
    res_str += new_numerator + "." + new_denumerator;
    BigFloat result(res_str);
    return result;
}

std::ostream &operator<<(std::ostream &stream, const BigFloat &bigFloat) {
    if (bigFloat.getIsNeg())
        stream << "-";
    return stream << bigFloat.getNumeratorValue() << "." << bigFloat.getDenumeratorValue();
}

BigFloat BigFloat::operator*(BigFloat bigFloat) {
    if ((getNumeratorValue() == "0" && getDenumeratorValue() == std::string(precision, '0'))
        || (bigFloat.getNumeratorValue() == "0" && bigFloat.getDenumeratorValue() == std::string(precision, '0')))
        return BigFloat("0");
    BigInt v1(getNumeratorValue() + getDenumeratorValue());
    v1.setIsNeg(getIsNeg());
    BigInt v2(bigFloat.getNumeratorValue() + bigFloat.getDenumeratorValue());
    v2.setIsNeg(bigFloat.getIsNeg());
    auto max_digits_in_numerator = std::max(getNumeratorValue().length(), bigFloat.getNumeratorValue().length());
    auto max_len = std::max(v1.getValue().length(), v2.getValue().length());  // Максимальное количество цифр
    BigInt res = v1 * v2;
    const auto &res_value = res.getValue();
    int shift = res_value.length() - max_len - precision; // Был перенос на 1 символ, например 82 + 30 = 110
    auto new_numerator = res_value.substr(0, max_digits_in_numerator + shift); // До точки
    auto new_denumerator = res_value.substr(max_digits_in_numerator + shift); // До конца
    std::string res_str = res.getIsNeg() ? "-" : "";
    res_str += new_numerator + "." + new_denumerator;
    BigFloat result(res_str);
    return result;
}

long long count_backward_zeros(const std::string &str) {
    long long cnt = 0;
    for (int i = str.length() - 1; i >= 0 && str[i] == '0'; --i) {
        cnt++;
    }
    return cnt;
}

BigFloat BigFloat::operator/(BigFloat bigFloat) {
    if (getNumeratorValue() == "0" && getDenumeratorValue() == std::string(precision, '0'))
        return BigFloat("0");
    if (bigFloat.getNumeratorValue() == "0" && bigFloat.getDenumeratorValue() == std::string(precision, '0')) {
        std::cerr << "Division by zero error!" << std::endl;
        throw std::string("Division by zero!");
    }
//
    BigInt v1(getNumeratorValue() + getDenumeratorValue());
    v1.setIsNeg(getIsNeg());
    BigInt v2(bigFloat.getNumeratorValue() + bigFloat.getDenumeratorValue());
    v2.setIsNeg(bigFloat.getIsNeg());
    BigInt res1 = v1 / v2;
    BigInt res2 = (v1 % v2);
    BigInt res3 = res2 * BigInt('1' + std::string(precision, '0')) / v2;
    auto v1_val = v1.getValue().substr(0, std::min(v1.getValue().length(), res2.getValue().length()));
    auto res2_val = res2.getValue().substr(0, std::min(v1.getValue().length(), res2.getValue().length()));
//    auto shift = count_backward_zeros(res2_val) - count_backward_zeros(v1_val);
    auto shift = v2.getValue().length() - res3.getValue().length() - 1;
    if (shift > 0) {
        BigFloat result(
                res1.getValue() + "." + std::string(shift, '0') +
                res3.getValue());
        result.setIsNeg(res1.getIsNeg());
        return result;
    } else {
        BigFloat result(
                res1.getValue() + "." +
                res3.getValue());
        result.setIsNeg(res1.getIsNeg());
        return result;
    }
}

BigFloat BigFloat::pow(long n) const {
    if (n == 0)
        return BigFloat("1");
    if (n < 0)
        return (BigFloat("1") / BigFloat(*this)).pow(-n);
    if (n == 1)
        return *this;
    if (n == -1)
        return (BigFloat("-1") / (*this));
    BigInt v1(getNumeratorValue() + getDenumeratorValue());
    v1.setIsNeg(getIsNeg());
    auto max_digits_in_numerator = getNumeratorValue().length();
    if (max_digits_in_numerator == 1 && getNumeratorValue()[0] == '0')
        max_digits_in_numerator--;
    auto max_len = v1.getValue().length();
    BigInt res = v1.pow(n);
    const auto &res_value = res.getValue();
    int shift = res_value.length() - max_len - precision * (n - 1); // Был перенос на 1 символ, например 82 + 30 = 110
    std::string res_str = res.getIsNeg() ? "-" : "";
    if (shift < 0) {
        res_str = "0." + std::string(-shift, '0') + res_value;
    } else {
        auto new_numerator = res_value.substr(0, max_digits_in_numerator + shift); // До точки
        auto new_denumerator = res_value.substr(max_digits_in_numerator + shift); // До конца
        res_str += new_numerator + "." + new_denumerator;
    }
    BigFloat result(res_str);
    return result;
}




