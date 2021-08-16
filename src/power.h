#pragma once

#include "tester.h"
#include <cmath>
#include <iomanip>

class SimplePower : public ITask {
    std::pair<double, unsigned long long> convertData(std::vector<std::string> data) {
        long double value_1 = std::strtod(data.at(0).c_str(), nullptr);
        unsigned long long value_2 = std::strtol(data.at(1).c_str(), nullptr, 10);
        return {value_1, value_2};
    }

public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        auto[number, targetPower] = convertData(data);
        double result = 1.0;
        for (double i = 1; i <= targetPower; ++i) {
            result *= number;
        }
        return {std::to_string(result)};
    }
};

class PowerOfTwo : public ITask {
    std::pair<double, unsigned long long> convertData(std::vector<std::string> data) {
        long double value_1 = std::strtod(data.at(0).c_str(), nullptr);
        unsigned long long value_2 = std::strtol(data.at(1).c_str(), nullptr, 10);
        return {value_1, value_2};
    }

public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        auto[number, targetPower] = convertData(data);
        if (targetPower == 0) {
            return {"1"};
        }
        double result = number;
        unsigned long long currentPower = 1;
        while (currentPower << 1 <= targetPower) {
            result *= result;
            currentPower <<= 1;
        }
        while (currentPower < targetPower) {
            result *= number;
            currentPower++;
        }
        return {std::to_string(result)};
    }
};

class BinaryPower : public ITask {
    std::pair<double, unsigned long long> convertData(std::vector<std::string> data) {
        long double value_1 = std::strtod(data.at(0).c_str(), nullptr);
        unsigned long long value_2 = std::strtol(data.at(1).c_str(), nullptr, 10);
        return {value_1, value_2};
    }

public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        auto[number, targetPower] = convertData(data);
        double result = 1;
        double a = number;
        while (targetPower > 0) {
            auto lastBit = targetPower % 2;
            if (lastBit > 0)
                result *= a;
            targetPower /= 2;
            a *= a;
        }
        return {std::to_string(result)};
    }
};