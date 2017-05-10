package com.heytz.smartband;

import android.bluetooth.BluetoothDevice;
import com.yc.pedometer.sdk.DeviceScanInterfacer;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzDeviceScanInterfacer implements DeviceScanInterfacer {
    private HeytzSmartApp heytzSmartApp;

    public HeytzDeviceScanInterfacer(HeytzSmartApp hApp) {
        this.heytzSmartApp = hApp;
    }

    @Override
    public void LeScanCallback(BluetoothDevice bluetoothDevice, int j) {
        heytzSmartApp.addLeDevice(bluetoothDevice);
        if (heytzSmartApp.getCallbackContext(Operation.SCAN.getMethod()) != null) {
            JSONArray jsonArray = new JSONArray();
            for (int i = 0; i < heytzSmartApp.getLeDeviceList().size(); i++) {
                jsonArray.put(HeytzUtil.deviceToJSONObject(heytzSmartApp.getLeDeviceList().get(i)));
            }
            PluginResult result = new PluginResult(PluginResult.Status.OK, jsonArray);
            result.setKeepCallback(true);
            heytzSmartApp.getCallbackContext(Operation.SCAN.getMethod()).sendPluginResult(result);
        }
    }
}
