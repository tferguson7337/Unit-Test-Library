
#include <chrono>
#include <UnitTestRunner.h>

#include "TestFunctions.hpp"

int main( )
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
    std::chrono::duration<uint64, std::nano> delta;

    // Test with list of UnitTests.
    {
        UnitTestRunner<char> utr("UTL_Tests_Helper_Lambda");

        t1 = std::chrono::high_resolution_clock::now( );

        std::list<UnitTest> testList;

        // Helper Lambda
        static const auto add = [&testList] (UnitTestResult(*func)())->void
        { 
            testList.emplace_back(func);
        };

        add(ErroneousTest);
        add(PositiveTest);
        add(SetupFailureTest);
        add(SetupExceptionTest);
        add(RunFailureTest);
        add(RunExceptionTest);
        add(CleanupFailureTest);
        add(CleanupExceptionTest);

        utr.AddUnitTests(std::move(testList));

        t2 = std::chrono::high_resolution_clock::now( );

        delta = std::chrono::duration_cast<std::chrono::duration<uint64, std::nano>>(t2 - t1);

        printf("\tTime to build and queue tests: %llu nanoseconds\n\n", delta.count( ));

        utr.RunUnitTests( );
    }

    // Test with list of std::function<UnitTestResult(void)>
    {
        UnitTestRunner<char> utr("UTL_Tests_Init_Func_List");

        t1 = std::chrono::high_resolution_clock::now( );

        std::list<std::function<UnitTestResult(void)>> testList =
        {
            ErroneousTest,
            PositiveTest,
            SetupFailureTest,
            SetupExceptionTest,
            RunFailureTest,
            RunExceptionTest,
            CleanupFailureTest,
            CleanupExceptionTest
        };

        utr.AddUnitTests(std::move(testList));

        t2 = std::chrono::high_resolution_clock::now( );

        delta = std::chrono::duration_cast<std::chrono::duration<uint64, std::nano>>(t2 - t1);

        printf("\n\n\tTime to build and queue tests: %llu nanoseconds\n\n", delta.count( ));

        utr.RunUnitTests( );
    }

    std::cin.get( );

    return 0;
}

