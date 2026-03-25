#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define TAG_LOG "NDK_SAMPLE"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, TAG_LOG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, TAG_LOG, __VA_ARGS__)

// 1) Message natif simple
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_getNativeMessage(
        JNIEnv* env,
        jobject /* instance */) {

    LOG_INFO("Execution de getNativeMessage");
    return env->NewStringUTF("Message depuis le code natif C++ !");
}

// 2) Calcul de produit factoriel
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_computeFactorial(
        JNIEnv* env,
        jobject /* instance */,
        jint value) {

    if (value < 0) {
        LOG_ERROR("Valeur negative interdite");
        return -10;
    }

    long long result = 1;
    for (int i = 2; i <= value; i++) {
        result *= i;

        if (result > INT_MAX) {
            LOG_ERROR("Depassement detecte pour value=%d", value);
            return -20;
        }
    }

    LOG_INFO("Resultat factoriel (%d) = %lld", value, result);
    return static_cast<jint>(result);
}

// 3) Renverser une chaine
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_flipText(
        JNIEnv* env,
        jobject /* instance */,
        jstring inputStr) {

    if (inputStr == nullptr) {
        LOG_ERROR("Entree vide");
        return env->NewStringUTF("Erreur : texte vide");
    }

    const char* rawChars = env->GetStringUTFChars(inputStr, nullptr);
    if (rawChars == nullptr) {
        LOG_ERROR("Lecture impossible");
        return env->NewStringUTF("Erreur interne JNI");
    }

    std::string text(rawChars);
    env->ReleaseStringUTFChars(inputStr, rawChars);

    std::reverse(text.begin(), text.end());

    LOG_INFO("Texte apres inversion : %s", text.c_str());
    return env->NewStringUTF(text.c_str());
}

// 4) Addition des elements d'un tableau
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_calculateSum(
        JNIEnv* env,
        jobject /* instance */,
        jintArray dataArray) {

    if (dataArray == nullptr) {
        LOG_ERROR("Array null");
        return -100;
    }

    jsize size = env->GetArrayLength(dataArray);
    jint* values = env->GetIntArrayElements(dataArray, nullptr);

    if (values == nullptr) {
        LOG_ERROR("Acces aux donnees impossible");
        return -200;
    }

    long long total = 0;
    for (jsize i = 0; i < size; i++) {
        total += values[i];
    }

    env->ReleaseIntArrayElements(dataArray, values, 0);

    if (total > INT_MAX) {
        LOG_ERROR("Overflow somme");
        return -300;
    }

    LOG_INFO("Somme calculee = %lld", total);
    return static_cast<jint>(total);
}