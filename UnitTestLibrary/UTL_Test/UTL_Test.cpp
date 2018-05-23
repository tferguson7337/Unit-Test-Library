
#include <chrono>
#include <UnitTestRunner.h>

#include "TestFunctions.hpp"

int main( )
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
    std::chrono::duration<uint64, std::nano> delta;

    {
        UnitTestRunner<char> utr("UTL_Tests_Narrow");

        t1 = std::chrono::high_resolution_clock::now( );

        std::list<std::function<UnitTestResult(void)>> testList =
        {
            SkippedTest,
            PositiveTest,
            SetupFailureTest,
            SetupExceptionTest,
            RunFailureTest,
            RunExceptionTest,
            CleanupFailureTest,
            CleanupExceptionTest,
            UnhandledExceptionTest
        };

        utr.AddUnitTests(std::move(testList));

        t2 = std::chrono::high_resolution_clock::now( );

        delta = std::chrono::duration_cast<std::chrono::duration<uint64, std::nano>>(t2 - t1);

        printf("\n\n\tTime to build and queue tests: %llu nanoseconds\n\n", delta.count( ));

        utr.RunUnitTests( );

        utr.PrintTestLogs( );
    }

    {
        UnitTestRunner<wchar_t> utr(L"UTL_Tests_Wide");

        t1 = std::chrono::high_resolution_clock::now( );

        std::list<std::function<UnitTestResult(void)>> testList =
        {
            SkippedTest,
            PositiveTest,
            SetupFailureTest,
            SetupExceptionTest,
            RunFailureTest,
            RunExceptionTest,
            CleanupFailureTest,
            CleanupExceptionTest,
            UnhandledExceptionTest
        };

        utr.AddUnitTests(std::move(testList));

        t2 = std::chrono::high_resolution_clock::now( );

        delta = std::chrono::duration_cast<std::chrono::duration<uint64, std::nano>>(t2 - t1);

        printf("\n\n\tTime to build and queue tests: %llu nanoseconds\n\n", delta.count( ));

        utr.RunUnitTests( );

        utr.PrintTestLogs( );
    }

    std::cin.get( );

    return 0;
}

