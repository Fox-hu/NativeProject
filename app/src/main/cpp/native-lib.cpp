#include <jni.h>
#include <string>

#define ARRAY_ELEMS(a)  (sizeof(a) / sizeof(a[0]))

const char *NATIVE_CLASS_MAIN_ACTIVITY = "com/fox/nativeproject/MainActivity";

//静态注册JNI
extern "C" JNIEXPORT jstring JNICALL
Java_com_fox_nativeproject_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//c获取java中的普通字段 并修改
extern "C"
JNIEXPORT jstring JNICALL
Java_com_fox_nativeproject_MainActivity_filedFromJNI(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass(NATIVE_CLASS_MAIN_ACTIVITY);
    jfieldID id = env->GetFieldID(clazz, "filed", "Ljava/lang/String;");
    //获取java的普通字段
    jobject str = env->GetObjectField(thiz, id);
    jstring  name = env->NewStringUTF("C修改后的普通字段");
    env->SetObjectField(thiz,id,name);
    return name;
}

//c获取java中的静态字段 并修改
extern "C"
JNIEXPORT jstring JNICALL
Java_com_fox_nativeproject_MainActivity_staticFiledFromJNI(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass(NATIVE_CLASS_MAIN_ACTIVITY);
    jfieldID id = env->GetStaticFieldID(clazz, "staticFiled", "Ljava/lang/String;");
    //获取java的静态字段
    jobject str = env->GetStaticObjectField(clazz, id);
    jstring  name = env->NewStringUTF("C修改后的静态字段");
    env->SetStaticObjectField(clazz,id,name);
    return name;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_fox_nativeproject_MainActivity_javaToC(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass(NATIVE_CLASS_MAIN_ACTIVITY);
    jmethodID methodId = env->GetMethodID(clazz, "normalMethod", "()V");
    env->CallVoidMethod(thiz, methodId);

    jmethodID static_methodId = env->GetStaticMethodID(clazz, "staticMethod", "()V");
    env->CallStaticVoidMethod(clazz, static_methodId);
}

jfloat loadAdd(JNIEnv *env, jobject thiz, jfloat a, jfloat b) {
    return a + b;
}

JNINativeMethod nativeMethod[] = {
        {"loadAdd", "(FF)F", (void *) loadAdd}
};

jint registerNative(JNIEnv *env) {
    jclass clazz = env->FindClass(NATIVE_CLASS_MAIN_ACTIVITY);
    if (env->RegisterNatives(clazz, nativeMethod, ARRAY_ELEMS(nativeMethod)) != JNI_OK) {
        return JNI_ERR;
    }
    return JNI_OK;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *unused) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    if(registerNative(env) != JNI_OK){
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}


JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *unused) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return ;
    }
    jclass clazz = env->FindClass(NATIVE_CLASS_MAIN_ACTIVITY);
    if(env->UnregisterNatives(clazz) != JNI_OK){
        return ;
    }
}
