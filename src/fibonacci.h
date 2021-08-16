#pragma once

#include <cinttypes>
#include <map>
#include "BigNumbers/BigInt.h"
#include "BigNumbers/BigFloat.h"
#include "matrix.h"

class SimpleFibonacciBigInt : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long fib_number = convertData(data);
        std::cout << fib_number << std::endl;
        return {f(fib_number).getValue()};
    }

private:
    BigInt f(unsigned long long n) {
        if (n == 0) {
            t[0] = BigInt("0");
            return BigInt("0");
        } else if (n == 1) {
            t[1] = BigInt("1");
            return BigInt("1");
        } else {
            BigInt res = t[n - 1] + t[n - 2];
            t[n] = res;
            std::cout << "F(" << n << ")=" << res << std::endl;
            return res;
        }
    }

    std::map<unsigned long long, BigInt> t;

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class GoldFibonacciBigInt : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long fib_number = convertData(data);
        return {f(fib_number)};
    }

private:
    std::string f(unsigned long long n) {
        BigFloat teta = std::to_string((1 + std::sqrt(5)) / 2);
        teta = teta.pow(n);
        teta = teta / BigFloat(std::to_string(std::sqrt(5)));
        teta = teta + BigFloat(std::to_string(0.5));
        return teta.getNumeratorValue();
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class SimpleFibonacciDynamic : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long fib_number = convertData(data);
        return {std::to_string(f(fib_number))};
    }

private:
    unsigned long long f(unsigned long long n) {
        if (n == 0) {
            t[0] = 0;
            return 0;
        } else if (n == 1) {
            t[1] = 1;
            return 1;
        } else {
            unsigned long long k = 1;
            while (k != n) {
                ++k;
                t[k] = t[k - 1] + t[k - 2];
            }
            return t[n];
        }
    }

    std::map<unsigned long long, unsigned long long> t;

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class SimpleFibonacci : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long fib_number = convertData(data);
        return {std::to_string(f(fib_number))};
    }

private:
    unsigned long long f(unsigned long long n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        } else {
            return f(n - 1) + f(n - 2);
        }
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class GoldFibonacci : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long fib_number = convertData(data);
        return {f(fib_number)};
    }

private:
    std::string f(unsigned long long n) {
        long double teta = (1 + std::sqrt(5)) / 2;
        long double res = std::pow(teta, n);
        res /= std::sqrt(5);
        res += 0.5;
        return std::to_string((unsigned long long) res);
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class MatrixFibonacci : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long fib_number = convertData(data);
        return {f(fib_number)};
    }

private:
    std::string f(unsigned long long n) {
        matrix base;
        base.value[0][0] = 1;
        base.value[0][1] = 1;
        base.value[1][0] = 1;
        base.value[1][1] = 0;
        matrix res = pow(base, n);
        return std::to_string(res.value[1][1]);
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};