//
//  HeyaldaJNIHelper.h
//  Motocross
//
//  Created by James Range on 7/13/14.
//
//

#ifndef __Motocross__HeyaldaJNIHelper__
#define __Motocross__HeyaldaJNIHelper__
#include <string>

class HeyaldaJNIHelper
{
public:
    static void callStaticVoidMethod(const char* className, const char* methodName);
    static std::string callStaticStringMethod(const char* className, const char* methodName);
    static bool callStaticBoolMethod(const char* className, const char* methodName);
    static void callStaticVoidMethodWithString(const char* className, const char* methodName, const char* string1);
    static void callStaticVoidMethodWithLong(const char* className, const char* methodName, int64_t longValue);

    static void callStaticVoidMethodWithBool(const char* className, const char* methodName, const bool boolValue);
    static void callStaticVoidMethodWithStringAndLong(const char* className, const char* methodName, const char* string1, const int64_t longValue);
    static void callStaticVoidMethodWithStringString(const char* className, const char* methodName, const char* string1, const char* string2);
    static void callStaticVoidMethodWithStringLongString(const char* className, const char* methodName, const char* string1, const int64_t longValue, const char* string2);
};
#endif /* defined(__Motocross__HeyaldaJNIHelper__) */
