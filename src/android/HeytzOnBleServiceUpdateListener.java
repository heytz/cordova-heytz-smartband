package com.heytz.smartband;

import android.bluetooth.BluetoothGattCharacteristic;
import android.util.Log;
import com.yc.pedometer.sdk.onBleServiceUpdateListener;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzOnBleServiceUpdateListener implements onBleServiceUpdateListener {
    private final String TAG = "==========HeytzOnBleServiceUpdateListener===========\n";
    private HeytzSmartApp heytzSmartApp;


    HeytzOnBleServiceUpdateListener(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    @Override
    public void onSuotaServiceStatusChange(BluetoothGattCharacteristic bluetoothGattCharacteristic) {
        Log.d(TAG, "onSuotaServiceStatusChange" + bluetoothGattCharacteristic.getValue());
    }

    @Override
    public void onCharacteristicWriteStatus(int i) {
        Log.d(TAG, "onCharacteristicWriteStatus" + i);
    }

    @Override
    public void onReadRemoteRssi(int i) {
        Log.d(TAG, "onReadRemoteRssi" + i);
    }

    @Override
    public void onCharacteristicRead(BluetoothGattCharacteristic bluetoothGattCharacteristic) {
        Log.d(TAG, "onCharacteristicRead" + bluetoothGattCharacteristic.getValue());
    }

    @Override
    public void onConnectionStateChange(boolean b) {
        Log.d(TAG, "onConnectionStateChange" + b);
    }

    @Override
    public void onServicesReady(boolean b) {
        Log.d(TAG, "onServicesReady" + b);
    }
}
