#include "tester.h"
#include "power.h"
#include <chrono>
#include <unistd.h>

bool isPrime(int p) {
    if (p % 2 == 0)
        return p == 2;
    for (int i = 3; i <= p; i++) {
        if (p % i == 0) {
            return false;
        }
    }
    return true;
}

unsigned long f(int n) {
    if (n < 2) {
        return 1;
    } else {
        return f(n - 1) + f(n - 2);
    }
}

int main() {
    /** lesson **/
    /**
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
    {
        int a = 100300;
        int b = 6;
        while (a!=b)
        {
            if (a > b)
            {
                a -=b;
            }
            else
            {
                b -= a;
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << elapsed << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
    {
        int a = 100300;
        int b = 6;
        while (a!=0 and b!= 0)
        {
            if (a > b)
            {
                a = a%b;
            }
            else
            {
                b = b%a;
            }
        }
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << elapsed << " ms" << std::endl;
    **/
/**
    int n = 112;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
    {
        bool a[121];
        a[0] = false;
        a[1] = false;
        for (int i = 2; i < 120; ++ i)
        {
            if (not a[i])
            {
                continue;
            }
            else
            {
                a[i] = true;
                for (int j = 2*i; j < 120; ++j)
                {
                    a[j] = false;
                }
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << elapsed << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i)
    {
        isPrime(n);
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << elapsed << " ms" << std::endl;
    **/

//auto start = std::chrono::high_resolution_clock::now();
//auto stop = std::chrono::high_resolution_clock::now();
//f(1000);
//auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
//std::cout << elapsed << " ms" << std::endl;
/**
auto lambda = [](){
    int a = 1003;
    int b = 6;
    while (a!=b)
    {
        if (a > b)
        {
            a -=b;
        }
        else
        {
            b -= a;
        }
    }
};
Tester::repeat(lambda,"НОД через вычитание",9);
 **/

    ITaskPtr PowerTask = std::make_unique<Power>();
    Tester PowerTester(PowerTask, "../tests/3.Power");
    PowerTester.RunTests(false, true, 0.001);
    return 0;
}
