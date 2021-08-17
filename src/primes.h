#pragma once
using ull = unsigned long long;

class PrimesIterator : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long N = convertData(data);
        return {std::to_string(countPrimes(N))};
    }

private:
    unsigned long long countPrimes(unsigned long long N) {
        ull cnt = 0;
        for (ull i = 1; i <= N; ++i) {
            if (isPrime(i)) cnt++;
        }
        return cnt;
    }

    bool isPrime(unsigned long long N) {
        ull cnt = 0;
        for (unsigned long long i = 1; i <= N; ++i) {
            if (N % i == 0) {
                cnt++;
            }
        }
        return cnt == 2;
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class PrimesIteratorEarlyStop : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long N = convertData(data);
        return {std::to_string(countPrimes(N))};
    }

private:
    unsigned long long countPrimes(unsigned long long N) {
        ull cnt = 0;
        for (ull i = 1; i <= N; ++i) {
            if (isPrime(i)) cnt++;
        }
        return cnt;
    }

    bool isPrime(unsigned long long N) {
        ull cnt = 0;
        if (N < 2) return false;
        for (unsigned long long i = 2; i < N; ++i) {
            if (N % i == 0) {
                return false;
            }
        }
        return true;
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class PrimesIteratorEarlyStopSqrt : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long N = convertData(data);
        return {std::to_string(countPrimes(N))};
    }

private:
    unsigned long long countPrimes(unsigned long long N) {
        ull cnt = 0;
        for (ull i = 1; i <= N; ++i) {
            if (isPrime(i)) cnt++;
        }
        return cnt;
    }

    bool isPrime(unsigned long long N) {
        ull cnt = 0;
        if (N < 2) return false;
        if (N % 2 == 0) return N == 2;
        for (unsigned long long i = 3; i <= std::sqrt(N); i += 2) {
            if (N % i == 0) {
                return false;
            }
        }
        return true;
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class Sieve : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long N = convertData(data);
        return {std::to_string(countPrimes(N + 1))};
    }

private:
    unsigned long long countPrimes(unsigned long long N) {
        bool *a = new bool[N];  // Not today, stackoverflow!
        for (ull i = 0; i < N; ++i) {
            a[i] = true;
        }
        a[0] = false;
        a[1] = false;
        ull cnt = 0;
        for (int i = 2; i < N; ++i) {
            if (not a[i]) {
                continue;
            } else {
                cnt++;
                for (int j = 2 * i; j < N; j += i) {
                    a[j] = false;
                }
            }
        }
        delete[] a;
        return cnt;
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class SieveBits : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long N = convertData(data);
        return {std::to_string(countPrimes(N + 1))};
    }

private:
    unsigned long long countPrimes(unsigned long long N) {
        // 32 - sizeof int
        unsigned long long arraySize = N / 32 + (N % 32 > 0);
        auto a = new uint32_t[arraySize];
//        uint32_t a[arraySize];
        for (ull i = 0; i < arraySize; ++i) {
            a[i] = UINT32_MAX;  // all set to true
        }
        a[0] &= ~(1 << 0);
        a[0] &= ~(1 << 1);
        ull cnt = 0;
        for (int i = 2; i < N; ++i) {
            if (not((a[i / 32] >> (i % 32)) & 1)) {
                continue;
            } else {
                cnt++;
                for (int j = 2 * i; j < N; j += i) {
                    a[j / 32] &= ~(1 << (j % 32));
                }
            }
        }
        delete[] a;
        return cnt;
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};

class FastSieve : public ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) override {
        unsigned long long N = convertData(data);
        return {std::to_string(countPrimes(N + 1))};
    }

private:
    unsigned long long countPrimes(unsigned long long N) {
        int *numbers = new int[N];  // Индекс - число, значение - минимальный простой делитель числа
        for (ull i = 0; i < N; ++i) numbers[i] = 0;
        std::vector<ull> primes; // Список простых чисел
        for (ull i = 2; i < N; ++i) {
            if (numbers[i] == 0)  // Если минимальный делитель установлен в 0
            {
                numbers[i] = i;
                primes.push_back(i);
            }
            for (const ull &primeNumber: primes) {
                if (primeNumber > numbers[i] || primeNumber * i > N) break;
                numbers[primeNumber * i] = primeNumber;
            }
        }
        delete[] numbers;
        return primes.size();
    }

    size_t convertData(std::vector<std::string> data) {
        unsigned long long value_1 = std::strtoull(data.at(0).c_str(), nullptr, 10);
        return value_1;
    }
};