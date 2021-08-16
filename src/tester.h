#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <cstdlib>

inline bool fileExists(const std::string &name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

class ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) = 0;
};

using ITaskPtr = std::unique_ptr<ITask>;

class Tester {
public:
    Tester() = delete;

    Tester(ITaskPtr &task, const std::string &path) {
        this->task = std::move(task);
        this->path = path;
    }

    void RunTests(bool verbose = false, bool assertOnError = false, double tolerance = 0.0) {
        this->verbose = verbose;
        this->assertOnError = assertOnError;
        this->tolerance = tolerance;
        int testNumber = 0;
        std::cout << "Tester started: " << std::endl;
        while (true) {
            std::cout << "_______________________________" << std::endl;
            std::string inFile = path + "/test." + std::to_string(testNumber) + ".in";
            std::string outFile = path + "/test." + std::to_string(testNumber) + ".out";
            if (!fileExists(inFile) || !fileExists(outFile))
                break;
            auto start = std::chrono::high_resolution_clock::now();
            bool result = RunTest(inFile, outFile);
            auto stop = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            std::string testResult = "Passed";
            if (!result) {
                testResult = "Failed";
            }
            std::cout << "Test#" << testNumber << "\t" << testResult << "\t" << elapsed << "ms"
                      << std::endl;
            testNumber++;
        }
    }

private:
    bool RunTest(std::string &infile,
                 std::string &outfile) {
        try {
            auto inputData = readFile(infile);
            auto outputData = readFile(outfile);
            std::vector<std::string> actual = task->Run(inputData);
            assert(actual.size() == outputData.size());
            return processResults(inputData, outputData, actual);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

private:
    std::vector<std::string> readFile(std::string &filename) {
        std::string line;
        std::vector<std::string> data;
        std::ifstream file(filename);
        while (std::getline(file, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            data.push_back(line);
        }
        return data;
    }

    std::string vectorToString(std::vector<std::string> &data) {
        std::stringstream result;
        for (const auto &value: data) {
            result << value << " ";
        }
        return result.str();
    }

    bool isNumber(const std::string &s) {
        char *end = nullptr;
        [[maybe_unused]] double val = strtod(s.c_str(), &end);
        return end != s.c_str() && *end == '\0';
    }

    bool processResults(std::vector<std::string> &inputData,
                        std::vector<std::string> &outputData,
                        std::vector<std::string> &actual) {
        if (verbose) {
            std::cout << "Input:\t\t" << vectorToString(inputData) << std::endl;
            std::cout << "Expected:\t" << vectorToString(outputData) << std::endl;
            std::cout << "Actual:\t\t" << vectorToString(actual) << std::endl;
        }
        bool result = true;
        for (int i = 0; i < actual.size(); ++i) {
            if (tolerance > 0 && isNumber(actual.at(i)) && isNumber(outputData.at(i))) {
                long double expectedValue = std::strtod(outputData.at(i).c_str(), nullptr);
                long double actualValue = std::strtod(actual.at(i).c_str(), nullptr);
                result &= std::abs(expectedValue - actualValue) < tolerance;
            } else {
                result &= actual.at(i) == outputData.at(i);
            }
        }
        if (assertOnError) {
            assert(result == true);
        }
        return result;
    }

    ITaskPtr task;
    std::string path;
    bool verbose = false;
    bool assertOnError = false;
    double tolerance = 0;
};