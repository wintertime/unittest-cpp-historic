#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"


namespace UnitTest {


#ifdef UNITTEST_VISUALSTUDIO
#   pragma warning(push)
#   pragma warning(disable:4800) // forcing value to bool true/false, performance warning
#endif
template< typename Value >
bool Check(Value const value)
{
    return value;
}
#ifdef UNITTEST_VISUALSTUDIO
#   pragma warning(pop)
#endif

template< typename Value >
bool CheckNull(Value const value)
{
    return (value == (void*)(0));
}

template< typename Expected, typename Actual >
bool CheckEqual(Expected const expected, Actual const actual)
{
    return (expected == actual);
}
bool CheckEqual(char const* expected, char const* actual);
bool CheckEqual(char* expected, char const* actual);
bool CheckEqual(char const* expected, char* actual);
bool CheckEqual(char* expected, char* actual);

template< typename Expected, typename Actual >
bool CheckArrayEqual(Expected const expected, Actual const actual, int const count)
{
    for (int i = 0; i < count; ++i)
    {
        if (!(expected[i] == actual[i]))
            return false;
    }

    return true;
}

template< typename Expected, typename Actual, typename Tolerance >
bool CheckClose(Expected const expected, Actual const actual, Tolerance const tolerance)
{
    return ((actual >= expected - tolerance) && (actual <= expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
bool CheckArrayClose(Expected const expected, Actual const actual, int const count, Tolerance const tolerance)
{
    for (int i = 0; i < count; ++i)
    {
        if (!CheckClose(expected[i], actual[i], tolerance))
            return false;
    }

    return true;
}


}


#endif 

