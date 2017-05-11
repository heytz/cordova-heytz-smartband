package com.heytz.smartband;

import android.bluetooth.BluetoothDevice;
import com.yc.pedometer.info.SleepTimeInfo;
import com.yc.pedometer.info.StepInfo;
import com.yc.pedometer.info.StepOneHourInfo;
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

    public static JSONObject stepInfoToJSONObject(StepInfo stepInfo) {
        JSONObject json = new JSONObject();
        try {
            json.put("date",stepInfo.getDate());
            json.put("calories",stepInfo.getCalories());
            json.put("distance",stepInfo.getDistance());
            json.put("sportTime",stepInfo.getSportTime());
            json.put("step",stepInfo.getStep());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return json;
    }
    static JSONObject sleepTimeInfoToJSONObject(SleepTimeInfo sleepTimeInfo) {
        JSONObject json = new JSONObject();
        try {
            json.put("AwakeCount",sleepTimeInfo.getAwakeCount());
            json.put("awakeTime",sleepTimeInfo.getAwakeTime());
            json.put("beginTime",sleepTimeInfo.getBeginTime());
            json.put("deepTime",sleepTimeInfo.getDeepTime());
            json.put("durationTimeArray",sleepTimeInfo.getDurationTimeArray());
            json.put("endTime",sleepTimeInfo.getEndTime());
            json.put("lightTime",sleepTimeInfo.getLightTime());
            json.put("sleepStatueArray",sleepTimeInfo.getSleepStatueArray());
            json.put("sleepTotalTime",sleepTimeInfo.getSleepTotalTime());
            json.put("timePointArray",sleepTimeInfo.getTimePointArray());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return json;
    }  static JSONObject stepOneHourInfoToJSONObject(StepOneHourInfo stepOneHourInfo) {
        JSONObject json = new JSONObject();
        try {
            json.put("step",stepOneHourInfo.getStep());
            json.put("time",stepOneHourInfo.getTime());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return json;
    }
}
