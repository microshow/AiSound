package io.microshow.aisoundapp;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import org.fmod.FMOD;

import io.microshow.aisound.AiSound;

/**
 * Created by Super on 2019/8/4.
 */
public class VoiceActivity extends AppCompatActivity {

    String path = "file:///android_asset/alipay.mp3";

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (!FMOD.checkInit()) {
            FMOD.init(this);
        }

    }

    public void clickFix(View view) {
        if (view.getId() == R.id.btn_normal) {
            playSound(path, AiSound.TYPE_NORMAL);

        } else if (view.getId() == R.id.btn_luoli) {
            playSound(path, AiSound.TYPE_LOLITA);

        } else if (view.getId() == R.id.btn_dashu) {
            playSound(path, AiSound.TYPE_UNCLE);

        } else if (view.getId() == R.id.btn_jingsong) {
            playSound(path, AiSound.TYPE_THRILLER);

        } else if (view.getId() == R.id.btn_gaoguai) {
            playSound(path, AiSound.TYPE_FUNNY);

        } else if (view.getId() == R.id.btn_kongling) {
            playSound(path, AiSound.TYPE_ETHEREAL);

        } else if (view.getId() == R.id.btn_gaoguai2) {
            playSound(path, AiSound.TYPE_CHORUS);

        } else if (view.getId() == R.id.btn_kongling2) {
            playSound(path, AiSound.TYPE_TREMOLO);
        }
    }

    public void playSound(String path, int type) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                AiSound.playSound(path, type);
            }
        }).start();
    }

    //保存音频 注意sd开权限
    public void saveSound(String path, int type) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                int result = AiSound.saveSound(path, "/storage/emulated/0/1/voice666.wav", AiSound.TYPE_LOLITA);
            }
        }).start();
    }

    @Override
    protected void onPause() {
        super.onPause();
        AiSound.pauseSound();
    }

    @Override
    protected void onResume() {
        super.onResume();
        AiSound.resumeSound();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (FMOD.checkInit()) {
            FMOD.close();
        }
    }
}
