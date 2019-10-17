#include <jni.h>
#include <string>
#include "aisound.h"
#include <fmod.hpp>
#include <android/log.h>
#include <unistd.h>
#include <cstring>

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"AiSound",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"AiSound",FORMAT,##__VA_ARGS__);
#define TYPE_NORMAL  0
#define TYPE_LOLITA  1
#define TYPE_UNCLE   2
#define TYPE_THRILLER  3
#define TYPE_FUNNY  4
#define TYPE_ETHEREAL  5
#define TYPE_CHORUS  6
#define TYPE_TREMOLO  7

using namespace FMOD;


Channel *channel;

JNIEXPORT jint JNICALL Java_io_microshow_aisound_AiSound_saveSound
        (JNIEnv *env, jclass jcls, jstring path_jstr, jstring path2_jstr, jint type) {

    System *system;
    Sound *sound;
    DSP *dsp;
    Channel *channel;
    float frequency;
    bool isPlaying = true;

    JNIEnv *mEnv;

    System_Create(&system);
    system->setSoftwareFormat(8000, FMOD_SPEAKERMODE_MONO, 0); //设置采样率为8000，channel为1
    mEnv = env;
    const char *path_cstr = mEnv->GetStringUTFChars(path_jstr, NULL);//输入音频路径
    const char *path_cstr2 = mEnv->GetStringUTFChars(path2_jstr, NULL);//输出音频路径

    if (true) {
        char cDest[200];
        strcpy(cDest, path_cstr2);
        system->setOutput(FMOD_OUTPUTTYPE_WAVWRITER); //保存文件格式为WAV
        system->init(32, FMOD_INIT_NORMAL | FMOD_INIT_PROFILE_ENABLE, cDest);
    } else {
        system->init(32, FMOD_INIT_NORMAL, NULL);
    }
    try {
        //创建声音
        system->createSound(path_cstr, FMOD_DEFAULT, NULL, &sound);
        system->playSound(sound, 0, false, &channel);
        switch (type) {
            case TYPE_NORMAL:
                LOGI("%s", path_cstr);
                LOGI("%s", "fix normal");
                break;
            case TYPE_LOLITA:
                system->createDSPByType(FMOD_DSP_TYPE_NORMALIZE, &dsp);
                channel->getFrequency(&frequency);
                frequency = frequency * 1.6;
                channel->setFrequency(frequency);
                break;
            case TYPE_UNCLE:
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                channel->addDSP(0, dsp);
                break;
            case TYPE_THRILLER:
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,
                                       1.8);
                channel->addDSP(0, dsp);
                break;
            case TYPE_FUNNY:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 50);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 60);
                channel->addDSP(0, dsp);
                break;
            case TYPE_ETHEREAL:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                channel->addDSP(0, dsp);
                break;
            case TYPE_CHORUS:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 100);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 50);
                channel->addDSP(0, dsp);
                break;
            case TYPE_TREMOLO:
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8);
                channel->addDSP(0, dsp);
                break;
            default:
                break;
        }

    } catch (...) {
        LOGE("%s", "发生异常");
        goto end;
    }
    system->update();
    while (isPlaying) {
        usleep(1000);
        channel->isPlaying(&isPlaying);
    }
    goto end;
    end:
    mEnv->ReleaseStringUTFChars(path_jstr, path_cstr);
    sound->release();
    system->close();
    system->release();

    return 1;

}

JNIEXPORT void JNICALL Java_io_microshow_aisound_AiSound_playSound
        (JNIEnv *env, jclass jcls, jstring path_jstr, jint type) {
    LOGI("%s", "--> start");

    System *system;
    Sound *sound;
    DSP *dsp;
//    Channel *channel;
    float frequency;
    bool isPlaying = true;

    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, NULL);
    const char *path_cstr = env->GetStringUTFChars(path_jstr, NULL);

    try {
        system->createSound(path_cstr, FMOD_DEFAULT, NULL, &sound);
        switch (type) {
            case TYPE_NORMAL:  // 普通
                LOGI("%s", path_cstr)
                system->playSound(sound, 0, false, &channel);
                LOGI("%s", "fix normal");
                break;
            case TYPE_LOLITA:  // 萝莉
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);    // 可改变音调
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 8.0);     // 8.0 为一个八度
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            case TYPE_UNCLE:  // 大叔
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            case TYPE_THRILLER:   // 惊悚
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);       //可改变颤音
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 5);           // 时间偏移低频振荡周期
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case TYPE_FUNNY:  // 搞怪
                system->createDSPByType(FMOD_DSP_TYPE_NORMALIZE, &dsp);    //放大声音
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);

                channel->getFrequency(&frequency);
                frequency = frequency * 2;                                  //频率*2
                channel->setFrequency(frequency);
                break;
            case TYPE_ETHEREAL: // 空灵
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);          // 控制回声
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);           // 延时
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);         // 回波衰减的延迟

                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case TYPE_CHORUS:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 100);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 50);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case TYPE_TREMOLO:
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
        }
    } catch (...) {
        LOGE("%s", "catch exception...")
        goto end;
    }

//    system->update();

    // 每隔一秒检测是否播放结束
    while (isPlaying) {
        channel->isPlaying(&isPlaying);
        usleep(1000 * 1000);
    }

    goto end;

    //释放资源
    end:
    env->ReleaseStringUTFChars(path_jstr, path_cstr);
    sound->release();
    system->close();
    system->release();
}


JNIEXPORT void JNICALL Java_io_microshow_aisound_AiSound_stopSound
        (JNIEnv *env, jclass jcls) {
    LOGI("%s", "--> start");

    channel->stop();

}

JNIEXPORT void JNICALL Java_io_microshow_aisound_AiSound_resumeSound
        (JNIEnv *env, jclass jcls) {
    LOGI("%s", "--> start");

    channel->setPaused(false);

}

JNIEXPORT void JNICALL Java_io_microshow_aisound_AiSound_pauseSound
        (JNIEnv *env, jclass jcls) {
    LOGI("%s", "--> start");

    channel->setPaused(true);

}

JNIEXPORT jboolean JNICALL Java_io_microshow_aisound_AiSound_isPlay
        (JNIEnv *env, jclass jcls) {
    LOGI("%s", "--> start");
    bool isPlaying = true;
    return !channel->isPlaying(&isPlaying);

}
