package com.heytz.smartband;

import android.bluetooth.BluetoothGattCharacteristic;
import com.yc.pedometer.sdk.onBleServiceUpdateListener;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzOnBleServiceUpdateListener implements onBleServiceUpdateListener {
    private HeytzSmartApp heytzSmartApp;

    HeytzOnBleServiceUpdateListener(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    @Override
    public void onSuotaServiceStatusChange(BluetoothGattCharacteristic bluetoothGattCharacteristic) {

    }

    @Override
    public void onCharacteristicWriteStatus(int i) {

    }

    @Override
    public void onReadRemoteRssi(int i) {

    }

    @Override
    public void onCharacteristicRead(BluetoothGattCharacteristic bluetoothGattCharacteristic) {

    }

    @Override
    public void onConnectionStateChange(boolean b) {

    }

    @Override
    public void onServicesReady(boolean b) {

    }
}
