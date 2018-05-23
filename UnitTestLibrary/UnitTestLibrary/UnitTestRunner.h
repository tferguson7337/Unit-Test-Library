#ifndef _UNIT_TEST_RUNNER_H
#define _UNIT_TEST_RUNNER_H

#include <Uncopyable.h>
#include <UnitTestLogger.h>
#include <Interface\UnitTestRunnerInterface.h>

#include "TestSetData.h"

template <class T>
class UnitTestRunner final : public virtual UnitTestRunnerInterface<T>, public Uncopyable
{
private:
    std::list<UnitTest> mUnitTests;
    UnitTestLogger<T> mLogger;
    TestSetData<T> mTestSetData;

public:
    /// Ctors \\\

    UnitTestRunner(const std::basic_string<T>&);
    UnitTestRunner(std::basic_string<T>&&) noexcept;
    UnitTestRunner(UnitTestRunner&&) noexcept;

    /// Dtor \\\

    ~UnitTestRunner( ) = default;

    /// Operator Overloads \\\

    UnitTestRunner& operator=(UnitTestRunner&&) noexcept;

    /// Getters \\\

    const std::list<UnitTest>& GetUnitTests( ) const noexcept;
    const std::basic_string<T>& GetLogFile( ) const noexcept;
    bool GetConsoleOutput( ) const noexcept;
    const TestSetData<T>& GetTestSetData( ) const noexcept;

    /// Setters \\\

    bool SetLogFile(const std::basic_string<T>&);
    void SetConsoleOutput(bool);

    /// Public Methods \\\

    bool AddUnitTest(UnitTest&&);
    bool AddUnitTest(std::function<UnitTestResult(void)>&&);
    bool AddUnitTests(std::list<UnitTest>&&);
    bool AddUnitTests(std::list<std::function<UnitTestResult(void)>>&&);

    bool RunUnitTests( );

    bool PrintTestLogs( );
};


#endif // _UNIT_TEST_RUNNER_H