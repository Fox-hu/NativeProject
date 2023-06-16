#include <jni.h>
#include <string>


//静态注册JNI
extern "C" JNIEXPORT jstring JNICALL
Java_com_fox_nativeproject_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//c获取java中的普通字段
extern "C"
JNIEXPORT jstring JNICALL
Java_com_fox_nativeproject_MainActivity_filedFromJNI(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/fox/nativeproject/MainActivity");
    jfieldID id = env->GetFieldID(clazz, "filed", "Ljava/lang/String;");
    jobject str = env->GetObjectField(thiz, id);
    return static_cast<jstring>(str);
}

//c获取java中的静态字段
extern "C"
JNIEXPORT jstring JNICALL
Java_com_fox_nativeproject_MainActivity_staticFiledFromJNI(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/fox/nativeproject/MainActivity");
    jfieldID id = env->GetStaticFieldID(clazz, "staticFiled", "Ljava/lang/String;");
    jobject str = env->GetStaticObjectField(clazz, id);
    return static_cast<jstring>(str);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_fox_nativeproject_MainActivity_javaToC(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/fox/nativeproject/MainActivity");
    jmethodID methodId = env->GetMethodID(clazz,"normalMethod", "()V");
    env->CallVoidMethod(thiz, methodId);

    jmethodID static_methodId = env->GetStaticMethodID(clazz,"staticMethod", "()V");
    env->CallStaticVoidMethod(clazz,static_methodId);
}