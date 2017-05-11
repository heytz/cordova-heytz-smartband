package com.heytz.smartband;

import android.util.Log;
import com.yc.pedometer.sdk.OnServerCallbackListener;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzOnServerCallbackListener implements OnServerCallbackListener {
    private final String TAG = "==========HeytzOnServerCallbackListener===========\n";
    private HeytzSmartApp heytzSmartApp;

    HeytzOnServerCallbackListener(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    @Override
    public void OnServerCallback(int i) {
        Log.d(TAG, "OnServerCallback:" + i);
    }
}
