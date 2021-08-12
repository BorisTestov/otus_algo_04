#pragma once

#include "tester.h"
#include <cmath>
#include <iomanip>

class Power : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        double result = 1.0;
        auto[number, targetPower] = convertData(data);
        for (double i = 1; i <= targetPower; ++i) {
            result *= number;
        }
        return {std::to_string(result)};
    };
private:
    std::pair<double, unsigned long long> convertData(std::vector<std::string> data) {
        long double value_1 = std::strtod(data.at(0).c_str(), nullptr);
        unsigned long long value_2 = std::strtol(data.at(1).c_str(), nullptr, 10);
        return {value_1, value_2};
    }
};