package com.heytz.smartband;

import android.bluetooth.BluetoothDevice;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzUtil {
    /**
     * 将device 转换为json对象
     *
     * @param device
     * @return
     */
    public static JSONObject deviceToJSONObject(BluetoothDevice device) {

        JSONObject json = new JSONObject();
        try {
            json.put("id", device.getAddress()); // mac address
            json.put("uuid", device.getUuids());
            json.put("name", device.getName());
            json.put("address", device.getAddress()); // mac address
//            json.put("getBluetoothClass", device.getBluetoothClass());
//            json.put("getBondState", device.getBondState());
//            json.put("getType", device.getType());
//            json.put("getClass", device.getClass());
//            json.put("describeContents", device.describeContents());
        } catch (JSONException e) { // this shouldn't happen
            e.printStackTrace();
        }

        return json;
    }
}
