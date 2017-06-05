package com.heytz.smartband;

import android.bluetooth.BluetoothDevice;
import com.yc.pedometer.sdk.DeviceScanInterfacer;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by chendongdong on 2017/5/10.
 * 设备扫描回调接口
 */
public class HeytzDeviceScanInterfacer implements DeviceScanInterfacer {
    private HeytzSmartApp app;

    public HeytzDeviceScanInterfacer(HeytzSmartApp hApp) {
        this.app = hApp;
    }

    /**
     * 要获取扫 到的设备，需实现 DeviceScanInterfacer 接口，
     * 当扫 到设备时，在 LeScanCallback 中返回结果
     *
     * @param bluetoothDevice   设备(包含设备所有信息，如设备名、设备地址等)
     * @param rssi 线损值
     */
    @Override
    public void LeScanCallback(BluetoothDevice bluetoothDevice, int rssi) {
        app.addLeDevice(bluetoothDevice);
        if (app.getCallbackContext(Operation.SCAN.getMethod()) != null) {
            JSONArray jsonArray = new JSONArray();
            for (int i = 0; i < app.getLeDeviceList().size(); i++) {
                JSONObject device = HeytzUtil.deviceToJSONObject(app.getLeDeviceList().get(i));
                try {
                    device.put("rssi", rssi);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                jsonArray.put(device);
            }
            PluginResult result = new PluginResult(PluginResult.Status.OK, jsonArray);
            result.setKeepCallback(true);
            app.getCallbackContext(Operation.SCAN.getMethod()).sendPluginResult(result);
        }
    }
}
