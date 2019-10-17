package io.microshow.aisound;

/**
 * AiSound
 */
public class AiSound {

    static {
        System.loadLibrary("fmod");
        System.loadLibrary("fmodL");
        System.loadLibrary("aisound");
    }

    public static final int TYPE_NORMAL = 0;    // 普通
    public static final int TYPE_LOLITA = 1;      // 萝莉
    public static final int TYPE_UNCLE = 2;       // 大叔
    public static final int TYPE_THRILLER = 3;    // 惊悚
    public static final int TYPE_FUNNY = 4;       // 搞怪
    public static final int TYPE_ETHEREAL = 5;    // 空灵
    public static final int TYPE_CHORUS = 6;    //合唱团
    public static final int TYPE_TREMOLO = 7;    //颤音

    /**
     * 播放音频
     *
     * @param path 音频路径
     * @param type 声音类型
     */
    public static native void playSound(String path, int type);

    /**
     * 停止播放
     */
    public static native void stopSound();

    /**
     * 暂停播放
     */
    public static native void pauseSound();

    /**
     * 恢复播放
     */
    public static native void resumeSound();

    /**
     * 判断是否是播放状态
     *
     * @return boolean
     */
    public static native boolean isPlay();

    /**
     * 保存音效
     *
     * @param inputSoundPath  输入路径
     * @param outputSoundPath 输出路径
     * @param type            音效类型
     * @return 状态
     */
    public static native int saveSound(String inputSoundPath, String outputSoundPath, int type);

}
