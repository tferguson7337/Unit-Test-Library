#ifndef _UNIT_TEST_RESULT_H
#define _UNIT_TEST_RESULT_H

#include <Uncopyable.h>

#include <Interface\UnitTestResultInterface.h>

///
//
//  Class:      UnitTestResult (final)
//
//  Purpose:    Encapsulates the result of a unit test.
//
///
class UnitTestResult final : public virtual UnitTestResultInterface, public Uncopyable
{
private:
    /// Private Data Members \\\

    Result mResult;
    uint64 mLineNum;
    std::string mFuncName;
    std::string mFileName;
    std::string mResultInfo;

    constexpr const char* ExtractFileName(const char*, const uint64) const noexcept;
    constexpr bool IsPathSeparator(const char) const noexcept;

public:
    /// Ctors \\\

    UnitTestResult(Result = Result::NotRun, const std::string& = "", const std::string& = "", uint64 = 0, const std::string& = "") noexcept;

    // Move Ctor
    UnitTestResult(UnitTestResult&&) noexcept;

    /// Dtor \\\

    ~UnitTestResult( ) = default;

    /// Operator Overloads \\\

    UnitTestResult& operator=(UnitTestResult&&) noexcept;
    explicit operator bool( ) const noexcept;

    /// Getters \\\

    Result GetResult( ) const noexcept;
    const std::string& GetFunctionName( ) const noexcept;
    const std::string& GetFileName( ) const noexcept;
    uint64 GetLineNumber( ) const noexcept;
    const std::string& GetResultInfo( ) const noexcept;

    /// Setters \\\

    void SetResult(Result) noexcept;
    void SetFunctionName(const std::string&);
    void SetFileName(const std::string&);
    void SetLineNumber(uint64) noexcept;
    void SetResultInfo(const std::string&);

    /// Unit Test Return Macros \\\

// Success
#define UTL_TEST_SUCCESS()          return UnitTestResult(Result::Success, __func__, __FILE__, __LINE__)

// Failures - No Exception Thrown
#define UTL_SETUP_FAILURE()         return UnitTestResult(Result::SetupFailure, __func__, __FILE__, __LINE__)
#define UTL_TEST_FAILURE()          return UnitTestResult(Result::TestFailure, __func__, __FILE__, __LINE__)
#define UTL_CLEANUP_FAILURE()       return UnitTestResult(Result::CleanupFailure, __func__, __FILE__, __LINE__)

// Failures - Exception Caught
#define UTL_SETUP_EXCEPTION(str)    return UnitTestResult(Result::SetupException, __func__, __FILE__, __LINE__, str)
#define UTL_TEST_EXCEPTION(str)     return UnitTestResult(Result::TestException, __func__, __FILE__, __LINE__, str)
#define UTL_CLEANUP_EXCEPTION(str)  return UnitTestResult(Result::CleanupException, __func__, __FILE__, __LINE__, str)

// Test Asserts
#define UTL_SETUP_ASSERT(cond)      if (!!(cond) == false) UTL_SETUP_FAILURE()
#define UTL_TEST_ASSERT(cond)       if (!!(cond) == false) UTL_TEST_FAILURE()
#define UTL_CLEANUP_ASSERT(cond)    if (!!(cond) == false) UTL_CLEANUP_FAILURE()

// Skip Test
#define UTL_SKIP_TEST(str)          return UnitTestResult(Result::NotRun, __func__, __FILE__, __LINE__, str)
};

#endif // _UNIT_TEST_RESULT_H