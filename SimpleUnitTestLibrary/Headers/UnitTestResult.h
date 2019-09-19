#pragma once

#include "ResultType.h"

#include <string>

///
//
//  Class:      UnitTestResult (final)
//
//  Purpose:    Encapsulates the result of a unit test.
//
///
class UnitTestResult final
{
private:
    /// Private Data Members \\\

    uint32_t mLTGTCounter = 0;

    ResultType mResult;
    uint32_t mLineNum;
    std::string mFuncName;
    std::string mFileName;
    std::string mResultInfo;

    using ExtractPredicate = bool(*)(const char&, uint32_t&);
    constexpr const char* ExtractNameCommon(_In_ const char*, _In_ const size_t&, _In_ ExtractPredicate) noexcept;
    constexpr const char* ExtractFileName(_In_ const char*, _In_ const size_t&) noexcept;
    constexpr const char* ExtractFuncName(_In_ const char*, _In_ const size_t&) noexcept;
    static constexpr bool IsPathSeparator(_In_ const char&, _Inout_ uint32_t&) noexcept;
    static constexpr bool IsWhitespace(_In_ const char&, _Inout_ uint32_t&) noexcept;

public:
    /// Ctors \\\

    UnitTestResult() noexcept;

    UnitTestResult(
        _In_ ResultType result,
        _In_ const char* func, _In_ const size_t& funcLen,
        _In_ const char* file, _In_ const size_t& fileLen, _In_ const uint32_t& line,
        _In_ const std::string& info = ""
    );

    // Move Ctor
    UnitTestResult(_In_ UnitTestResult&&) noexcept;

    /// Dtor \\\

    ~UnitTestResult() = default;

    /// Operator Overloads \\\

    UnitTestResult& operator=(_In_ UnitTestResult&&) noexcept;
    explicit operator bool() const noexcept;

    /// Getters \\\

    const ResultType& GetResult() const noexcept;
    const std::string& GetFunctionName() const noexcept;
    const std::string& GetFileName() const noexcept;
    const uint32_t& GetLineNumber() const noexcept;
    const std::string& GetResultInfo() const noexcept;

    /// Setters \\\

    void SetResult(_In_ const ResultType&) noexcept;
    void SetFunctionName(_In_ const std::string&);
    void SetFileName(_In_ const std::string&);
    void SetLineNumber(_In_ const uint32_t&) noexcept;
    void SetResultInfo(_In_ const std::string&);

    /// Unit Test Return Macros \\\

// Success
#define SUTL_TEST_SUCCESS( )        return UnitTestResult(ResultType::Success, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__)

// Failures - No Exception Thrown
#define SUTL_SETUP_FAILURE(str)     return UnitTestResult(ResultType::SetupFailure, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)
#define SUTL_TEST_FAILURE(str)      return UnitTestResult(ResultType::TestFailure, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)
#define SUTL_CLEANUP_FAILURE(str)   return UnitTestResult(ResultType::CleanupFailure, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)

// Failures - Exception Caught
#define SUTL_SETUP_EXCEPTION(str)   return UnitTestResult(ResultType::SetupException, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)
#define SUTL_TEST_EXCEPTION(str)    return UnitTestResult(ResultType::TestException, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)
#define SUTL_CLEANUP_EXCEPTION(str) return UnitTestResult(ResultType::CleanupException, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)

#define ___SUTL_STRINGIFY___(s)   #s
#define __SUTL_STRINGIFY__(s)    ___SUTL_STRINGIFY___(s)

// Test Asserts
#define SUTL_SETUP_ASSERT(cond)     if (!!(cond) == false) SUTL_SETUP_FAILURE(__SUTL_STRINGIFY__(cond))
#define SUTL_TEST_ASSERT(cond)      if (!!(cond) == false) SUTL_TEST_FAILURE(__SUTL_STRINGIFY__(cond))
#define SUTL_CLEANUP_ASSERT(cond)   if (!!(cond) == false) SUTL_CLEANUP_FAILURE(__SUTL_STRINGIFY__(cond))

// Skip Test
#define SUTL_SKIP_TEST(str)         return UnitTestResult(ResultType::NotRun, __FUNCSIG__, _countof(__FUNCSIG__), __FILE__, _countof(__FILE__), __LINE__, str)
};
