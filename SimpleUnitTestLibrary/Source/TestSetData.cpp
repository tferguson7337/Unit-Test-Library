#include <TestSetData.h>

// Explicit Template Instantiation
template class TestSetData<utf8>;
template class TestSetData<utf16>;

template <class T>
TestSetData<T>::TestSetData(const std::basic_string<T>& testSetName) noexcept :
    mTotalTests(0),
    mTestPassCount(0),
    mTotalFailureCount(0),
    mSetupFailureCount(0),
    mTestFailureCount(0),
    mCleanupFailureCount(0),
    mSetupExceptionCount(0),
    mTestExceptionCount(0),
    mCleanupExceptionCount(0),
    mUnhandledExceptionCount(0),
    mTestSkipCount(0),
    mTestSetName(testSetName)
{ }

template <class T>
TestSetData<T>::TestSetData(std::basic_string<T>&& testSetName) noexcept :
    mTotalTests(0),
    mTestPassCount(0),
    mTotalFailureCount(0),
    mSetupFailureCount(0),
    mTestFailureCount(0),
    mCleanupFailureCount(0),
    mSetupExceptionCount(0),
    mTestExceptionCount(0),
    mCleanupExceptionCount(0),
    mUnhandledExceptionCount(0),
    mTestSkipCount(0),
    mTestSetName(std::move(testSetName))
{ }

template <class T>
TestSetData<T>::TestSetData(const TestSetData<T>& src) noexcept :
    TestSetData( )
{
    *this = src;
}

template <class T>
TestSetData<T>::TestSetData(TestSetData<T>&& src) noexcept :
    TestSetData( )
{
    *this = std::move(src);
}

template <class T>
TestSetData<T>& TestSetData<T>::operator=(const TestSetData<T>& src) noexcept
{
    mTotalTests = src.mTotalTests;
    mTestPassCount = src.mTestPassCount;
    mTotalFailureCount = src.mTotalFailureCount;
    mSetupFailureCount = src.mSetupFailureCount;
    mTestFailureCount = src.mTestFailureCount;
    mCleanupFailureCount = src.mCleanupFailureCount;
    mSetupExceptionCount = src.mSetupExceptionCount;
    mTestExceptionCount = src.mTestExceptionCount;
    mCleanupExceptionCount = src.mCleanupExceptionCount;
    mUnhandledExceptionCount = src.mUnhandledExceptionCount;
    mTestSkipCount = src.mTestSkipCount;

    mTestSetName = src.mTestSetName;

    return *this;
}

template <class T>
TestSetData<T>& TestSetData<T>::operator=(TestSetData<T>&& src) noexcept
{
    mTotalTests = src.mTotalTests;
    mTestPassCount = src.mTestPassCount;
    mTotalFailureCount = src.mTotalFailureCount;
    mSetupFailureCount = src.mSetupFailureCount;
    mTestFailureCount = src.mTestFailureCount;
    mCleanupFailureCount = src.mCleanupFailureCount;
    mSetupExceptionCount = src.mSetupExceptionCount;
    mTestExceptionCount = src.mTestExceptionCount;
    mCleanupExceptionCount = src.mCleanupExceptionCount;
    mUnhandledExceptionCount = src.mUnhandledExceptionCount;
    mTestSkipCount = src.mTestSkipCount;

    mTestSetName = std::move(src.mTestSetName);

    src.ClearAll( );

    return *this;
}

template <class T>
uint32 TestSetData<T>::GetTotalTestCount( ) const noexcept
{
    return mTotalTests;
}

template <class T>
uint32 TestSetData<T>::GetTestPassCount( ) const noexcept
{
    return mTestPassCount;
}

template <class T>
uint32 TestSetData<T>::GetTotalFailureCount( ) const noexcept
{
    return mTotalFailureCount;
}

template <class T>
uint32 TestSetData<T>::GetSetupFailureCount( ) const noexcept
{
    return mSetupFailureCount;
}

template <class T>
uint32 TestSetData<T>::GetTestFailureCount( ) const noexcept
{
    return mTestFailureCount;
}

template <class T>
uint32 TestSetData<T>::GetCleanupFailureCount( ) const noexcept
{
    return mCleanupFailureCount;
}

template <class T>
uint32 TestSetData<T>::GetSetupExceptionCount( ) const noexcept
{
    return mSetupExceptionCount;
}

template <class T>
uint32 TestSetData<T>::GetTestExceptionCount( ) const noexcept
{
    return mTestExceptionCount;
}

template <class T>
uint32 TestSetData<T>::GetCleanupExceptionCount( ) const noexcept
{
    return mCleanupExceptionCount;
}

template <class T>
uint32 TestSetData<T>::GetUnhandledExceptionCount( ) const noexcept
{
    return mUnhandledExceptionCount;
}

template <class T>
uint32 TestSetData<T>::GetTestSkipCount( ) const noexcept
{
    return mTestSkipCount;
}

template<class T>
const std::basic_string<T>& TestSetData<T>::GetTestSetName( ) const noexcept
{
    return mTestSetName;
}

template <class T>
void TestSetData<T>::IncrementResultCounter(ResultType r)
{
    switch ( r )
    {
    case ResultType::NotRun:
        mTestSkipCount++;
        break;

    case ResultType::Success:
        mTestPassCount++;
        break;

    case ResultType::SetupFailure:
        mSetupFailureCount++;
        mTotalFailureCount++;
        break;

    case ResultType::SetupException:
        mSetupExceptionCount++;
        mTotalFailureCount++;
        break;

    case ResultType::TestFailure:
        mTestFailureCount++;
        mTotalFailureCount++;
        break;

    case ResultType::TestException:
        mTestExceptionCount++;
        mTotalFailureCount++;
        break;

    case ResultType::CleanupFailure:
        mCleanupFailureCount++;
        mTotalFailureCount++;
        break;

    case ResultType::CleanupException:
        mCleanupExceptionCount++;
        mTotalFailureCount++;
        break;

    case ResultType::UnhandledException:
        mUnhandledExceptionCount++;
        mTotalFailureCount++;
        break;

    default:
        return;
    }
}

template <class T>
void TestSetData<T>::SetTotalTestCount(uint32 c) noexcept
{
    mTotalTests = c;
}

template<class T>
void TestSetData<T>::SetTestSetName(const std::basic_string<T>& name)
{
    mTestSetName = name;
}

template<class T>
void TestSetData<T>::SetTestSetName(std::basic_string<T>&& name) noexcept
{
    mTestSetName = std::move(name);
}

template <class T>
void TestSetData<T>::ResetCounters( ) noexcept
{
    mTotalTests = 0;
    mTestPassCount = 0;
    mTotalFailureCount = 0;
    mSetupFailureCount = 0;
    mTestFailureCount = 0;
    mCleanupFailureCount = 0;
    mSetupExceptionCount = 0;
    mTestExceptionCount = 0;
    mCleanupExceptionCount = 0;
    mUnhandledExceptionCount = 0;
    mTestSkipCount = 0;
}

template <class T>
void TestSetData<T>::ClearAll( ) noexcept
{
    ResetCounters( );
    mTestSetName.clear( );
}

template <class T>
long double TestSetData<T>::GetTestSetGrade( ) const noexcept
{
    const uint32 testRunCount = mTotalTests - mTestSkipCount;
    return (testRunCount > 0) ? 100.0L * static_cast<long double>(mTestPassCount) / static_cast<long double>(testRunCount) : 0.0L;
}