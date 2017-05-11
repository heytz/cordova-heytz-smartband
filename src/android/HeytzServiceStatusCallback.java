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

    public HeytzServiceStatusCallback(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    @Override
    public void OnServiceStatuslt(int status) {
        Log.w(TAG, String.valueOf(status));
        if (status == ICallbackStatus.BLE_SERVICE_START_OK) {
//            if (mBluetoothLeService == null) {
//                mBluetoothLeService = mBLEServiceOperate.getBleService();
//                mBluetoothLeService.setICallback(this);
//            }
        }
    }
}
