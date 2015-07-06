//
//  HeyaldaJNIHelper.cpp
//  Motocross
//
//  Created by James Range on 5/13/15.
//
//

#include "HeyaldaJNIHelper.h"
#include "cocos2d.h"
#include "JniHelper.h"

void HeyaldaJNIHelper::callStaticVoidMethod(const char* className, const char* methodName)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}


std::string HeyaldaJNIHelper::callStaticStringMethod(const char* className, const char* methodName)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "()Ljava/lang/String;"))
    {
        jstring jstringResult = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);
        const char* result = t.env->GetStringUTFChars(jstringResult, NULL);
        std::string result2(result);
        t.env->ReleaseStringUTFChars(jstringResult, result);
        return result2;
    }
    else
    {
        std::string emptyString("");
        return emptyString;
    }
}


bool HeyaldaJNIHelper::callStaticBoolMethod(const char* className, const char* methodName)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "()Z"))
    {
        bool result = (t.env->CallStaticBooleanMethod(t.classID, t.methodID) == JNI_TRUE);
        t.env->DeleteLocalRef(t.classID);
        return result;
    }
    else
    {
        return false;
    }
}

void HeyaldaJNIHelper::callStaticVoidMethodWithLong(const char* className, const char* methodName, int64_t longValue)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "(J)V") )
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID, (jlong)longValue);
        t.env->DeleteLocalRef(t.classID);
    }

}

void HeyaldaJNIHelper::callStaticVoidMethodWithString(const char* className, const char* methodName, const char* string1)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "(Ljava/lang/String;)V"))
    {
        jstring jstring1 = t.env->NewStringUTF(string1);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jstring1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jstring1);
    }
}

void HeyaldaJNIHelper::callStaticVoidMethodWithBool(const char* className, const char* methodName, const bool boolValue)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "(Z)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, boolValue);
        t.env->DeleteLocalRef(t.classID);
    }
}

void HeyaldaJNIHelper::callStaticVoidMethodWithStringAndLong(const char* className, const char* methodName, const char* string1, const int64_t longValue)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "(Ljava/lang/String;J)V"))
    {
        jstring jstring1 = t.env->NewStringUTF(string1);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jstring1, (jlong)longValue);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jstring1);
    }
}

void HeyaldaJNIHelper::callStaticVoidMethodWithStringString(const char* className, const char* methodName, const char* string1, const char* string2)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring jstring1 = t.env->NewStringUTF(string1);
        jstring jstring2 = t.env->NewStringUTF(string2);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jstring1, jstring2);
        t.env->DeleteLocalRef(jstring1);
        t.env->DeleteLocalRef(jstring2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void HeyaldaJNIHelper::callStaticVoidMethodWithStringLongString(const char* className, const char* methodName, const char* string1, const int64_t longValue, const char* string2)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, "(Ljava/lang/String;JLjava/lang/String;)V"))
    {
        jstring jstring1 = t.env->NewStringUTF(string1);
        jstring jstring2 = t.env->NewStringUTF(string2);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jstring1, (jlong)longValue, jstring2);
        t.env->DeleteLocalRef(jstring1);
        t.env->DeleteLocalRef(jstring2);
        t.env->DeleteLocalRef(t.classID);
    }
}

