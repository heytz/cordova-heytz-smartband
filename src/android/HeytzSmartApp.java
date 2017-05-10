package com.heytz.smartband;

import android.bluetooth.BluetoothDevice;
import org.apache.cordova.CallbackContext;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzSmartApp {
    public final String TAG = "\n=========HeytzSmartApp=========\n";

    private ArrayList<BluetoothDevice> leDeviceList;
    private boolean mScanning;
    private final int REQUEST_ENABLE_BT = 1;
    // Stops scanning after 10 seconds.
    private final long SCAN_PERIOD = 10000;
    private Map<String, CallbackContext> callbackContextMap;

    HeytzSmartApp() {
        super();
        leDeviceList = new ArrayList<BluetoothDevice>();
        callbackContextMap = new HashMap<String, CallbackContext>();
    }

    /**
     * 获取callback,指定某个方法
     *
     * @param key
     * @return
     */
    CallbackContext getCallbackContext(String key) {
        if (callbackContextMap.containsKey(key))
            return callbackContextMap.get(key);
        else
            return null;
    }

    /**
     * 设置callback,方法名为键
     *
     * @param key             方法名
     * @param callbackContext
     */
    void setCallbackContext(String key, CallbackContext callbackContext) {
        callbackContextMap.put(key, callbackContext);
    }

    void addLeDevice(BluetoothDevice bluetoothDevice) {
        boolean repeat = false;
        for (int i = 0; i < this.leDeviceList.size(); i++) {
            if (this.leDeviceList.get(i).getAddress().equals(bluetoothDevice.getAddress())) {
                this.leDeviceList.remove(i);
                repeat = true;
                this.leDeviceList.add(i, bluetoothDevice);
            }
        }
        if (!repeat) {
            this.leDeviceList.add(bluetoothDevice);
        }
    }

    void clearLeDeviceList() {
        this.leDeviceList.clear();
    }

    ArrayList<BluetoothDevice> getLeDeviceList() {
        return this.leDeviceList;
    }

    /**
     * 删除指定的callback
     *
     * @param key
     */
    public void removeCallbackContext(String key) {
        callbackContextMap.remove(key);
    }
}
