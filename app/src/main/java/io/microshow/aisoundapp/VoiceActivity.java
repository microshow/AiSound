package io.microshow.aisoundapp;

import android.Manifest;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.tbruyelle.rxpermissions2.RxPermissions;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import io.microshow.aisound.AiSound;
import io.reactivex.disposables.CompositeDisposable;
import io.reactivex.functions.Consumer;

/**
 * Created by Super on 2019/8/4.
 */
public class VoiceActivity extends AppCompatActivity {

    String path = "file:///android_asset/alipay.mp3";

    private CompositeDisposable mCompositeDisposable = new CompositeDisposable();

    //权限
    private RxPermissions rxPermissions = null;

    //需要申请的权限，必须先在AndroidManifest.xml有声明，才可以动态获取权限
    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE};

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //初始化AiSound
        AiSound.init(this);

        //权限申请
        rxPermissions = new RxPermissions(this);
        mCompositeDisposable.add(rxPermissions.request(PERMISSIONS_STORAGE).subscribe(new Consumer<Boolean>() {
            @Override
            public void accept(Boolean aBoolean) throws Exception {
                if (aBoolean) {// 用户同意了权限
//                    doLogic();
                } else {//用户拒绝了权限
                    Toast.makeText(VoiceActivity.this, "您拒绝了权限，请往设置里开启权限", Toast.LENGTH_LONG).show();
                    finish();
                }
            }
        }));
    }

    private int type = AiSound.TYPE_NORMAL;

    public void clickFix(View view) {
        if (view.getId() == R.id.btn_normal) {
            type = AiSound.TYPE_NORMAL;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_luoli) {
            type = AiSound.TYPE_LOLITA;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_dashu) {
            type = AiSound.TYPE_UNCLE;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_jingsong) {
            type = AiSound.TYPE_THRILLER;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_gaoguai) {
            type = AiSound.TYPE_FUNNY;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_kongling) {
            type = AiSound.TYPE_ETHEREAL;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_gaoguai2) {
            type = AiSound.TYPE_CHORUS;
            playSound(path, type);

        } else if (view.getId() == R.id.btn_kongling2) {
            type = AiSound.TYPE_TREMOLO;
            playSound(path, type);

        } else if (view.getId() == R.id.save) {//保存
            Toast.makeText(VoiceActivity.this, "开始合成", Toast.LENGTH_SHORT).show();
            AiSound.saveSoundAsync(path, "/storage/emulated/0/1/1_voice.wav"
                    , type, new AiSound.IAiSoundListener() {
                        @Override
                        public void onFinish(String inputSoundPath, String outputSoundPath, int type) {
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    Toast.makeText(VoiceActivity.this, "成功: " + outputSoundPath, Toast.LENGTH_SHORT).show();
                                    //合成成功 试听
                                    playSound(outputSoundPath, AiSound.TYPE_NORMAL);
                                }
                            });
                        }

                        @Override
                        public void onError(String msg) {
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    Toast.makeText(VoiceActivity.this, "出错了: " + msg, Toast.LENGTH_SHORT).show();
                                }
                            });
                        }
                    });
        }
    }

    public void playSound(String path, int type) {
        AiSound.playSoundAsync(path, type);
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
        if (mCompositeDisposable != null) {
            mCompositeDisposable.clear();
        }
        AiSound.close();
    }
}
