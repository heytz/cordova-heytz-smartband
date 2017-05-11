package com.heytz.smartband;

import android.util.Log;
import com.yc.pedometer.sdk.ICallbackStatus;
import com.yc.pedometer.sdk.ServiceStatusCallback;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzServiceStatusCallback implements ServiceStatusCallback {
    private final String TAG = "==========HeytzServiceStatusCallback===========\n";
    private HeytzSmartApp heytzSmartApp;

    HeytzServiceStatusCallback(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    //    如果没在搜索界面提前实例BLEServiceOperate的话，下面这4行需要放到OnServiceStatuslt
    @Override
    public void OnServiceStatuslt(int status) {
        Log.w(TAG, String.valueOf(status));
        if (status == ICallbackStatus.BLE_SERVICE_START_OK) {
//            if (mBluetoothLeService == null) {
//                mBluetoothLeService = mBLEServiceOperate.getBleService();
//                mBluetoothLeService.setICallback(this);
//            }
        }
        final String js = "cordova.plugins.SmartBand.openOnServiceStatuslt(" + status + ");";
        heytzSmartApp.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                heytzSmartApp.getSmartBand().webView.loadUrl("javascript:" + js);
            }
        });
    }
}
