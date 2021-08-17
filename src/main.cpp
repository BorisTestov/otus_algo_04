#include "tester.h"
#include "power.h"
#include "primes.h"
#include "fibonacci.h"

int main() {
    ITaskPtr SimplePowerTask = std::make_unique<SimplePower>();
    Tester SimplePowerTester(SimplePowerTask, "../tests/3.Power");
    SimplePowerTester.RunTests(false, true, 0.001);
    //
    ITaskPtr PowerOfTwoTask = std::make_unique<PowerOfTwo>();
    Tester PowerOfTwoTester(PowerOfTwoTask, "../tests/3.Power");
    PowerOfTwoTester.RunTests(false, true, 0.001);
    //
    ITaskPtr BinaryPowerTask = std::make_unique<BinaryPower>();
    Tester BinaryPowerTester(BinaryPowerTask, "../tests/3.Power");
    BinaryPowerTester.RunTests(false, true, 0.001);
    //
    //
    ITaskPtr FibonacciSimpleTask = std::make_unique<SimpleFibonacci>();
    Tester FibonacciSimpleTester(FibonacciSimpleTask, "../tests/4.Fibo");
    FibonacciSimpleTester.RunTests(false, false, 0.001);
    //
    ITaskPtr GoldFibonacciTask = std::make_unique<GoldFibonacci>();
    Tester GoldFibonacciTester(GoldFibonacciTask, "../tests/4.Fibo");
    GoldFibonacciTester.RunTests(false, false, 0.001);
    //
    ITaskPtr MatrixFibonacciTask = std::make_unique<MatrixFibonacci>();
    Tester MatrixFibonacciTester(MatrixFibonacciTask, "../tests/4.Fibo");
    MatrixFibonacciTester.RunTests(false, false, 0.001);
    //
    ITaskPtr PrimesIteratorTask = std::make_unique<PrimesIterator>();
    Tester PrimesIteratorTester(PrimesIteratorTask, "../tests/5.Primes");
    PrimesIteratorTester.RunTests(false, false, 0.001);
    //
    ITaskPtr PrimesIteratorEarlyStopTask = std::make_unique<PrimesIteratorEarlyStop>();
    Tester PrimesIteratorEarlyStopTester(PrimesIteratorEarlyStopTask, "../tests/5.Primes");
    PrimesIteratorEarlyStopTester.RunTests(false, false, 0.001);
    //
    ITaskPtr PrimesIteratorEarlyStopSqrtTask = std::make_unique<PrimesIteratorEarlyStopSqrt>();
    Tester PrimesIteratorEarlyStopSqrtTester(PrimesIteratorEarlyStopSqrtTask, "../tests/5.Primes");
    PrimesIteratorEarlyStopSqrtTester.RunTests(false, false, 0.001);
    //
    ITaskPtr SieveTask = std::make_unique<Sieve>();
    Tester SieveTester(SieveTask, "../tests/5.Primes");
    SieveTester.RunTests(false, false, 0.001);
    //
    ITaskPtr SieveBitsTask = std::make_unique<SieveBits>();
    Tester SieveBitsTester(SieveBitsTask, "../tests/5.Primes");
    SieveBitsTester.RunTests(false, false, 0.001);
    //
    ITaskPtr FastSieveTask = std::make_unique<FastSieve>();
    Tester FastSieveTester(FastSieveTask, "../tests/5.Primes");
    FastSieveTester.RunTests(true, false, 0.001);
    return 0;
}
