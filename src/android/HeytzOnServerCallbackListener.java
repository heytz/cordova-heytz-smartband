package com.heytz.smartband;

import android.util.Log;
import com.yc.pedometer.sdk.OnServerCallbackListener;
import com.yc.pedometer.utils.GlobalVariable;

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
    public void OnServerCallback(int status) {
        Log.d(TAG, "OnServerCallback:" + status);
        switch (status) {
            case GlobalVariable.SERVER_IS_BUSY:        //访问服务器回调状态,服务器忙 = 202;
                break;
            case GlobalVariable.SERVER_CALL_BACK_SUCCESSFULL: //访问服务器回调状态, 服务连接正常, 已获取到固件版本
                break;
        }
        final String js = "cordova.plugins.SmartBand.openOnServerCallback(" + status + ");";
        heytzSmartApp.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                heytzSmartApp.getSmartBand().webView.loadUrl("javascript:" + js);
            }
        });
    }
}
