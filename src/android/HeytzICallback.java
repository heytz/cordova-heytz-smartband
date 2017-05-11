package com.heytz.smartband;

import android.util.Log;
import com.yc.pedometer.sdk.ICallback;
import com.yc.pedometer.sdk.ICallbackStatus;
import org.apache.cordova.PluginResult;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by chendongdong on 2017/5/9.
 */
public class HeytzICallback implements ICallback {
    private final String TAG = "======HeytzICallback======\n";
    private HeytzSmartApp heytzSmartApp;

    public HeytzICallback(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    @Override
    public void OnResult(boolean result, int status) {
// TODO Auto-generated method stub
        Log.i(TAG, "result=" + result + ",status=" + status);
        switch (status) {
            case ICallbackStatus.OFFLINE_STEP_SYNC_OK:
                // step snyc complete
                break;
            case ICallbackStatus.OFFLINE_SLEEP_SYNC_OK:
                // sleep snyc complete
                break;
            case ICallbackStatus.SYNC_TIME_OK: // after set time
                // finish, then(or
                // delay 20ms) send
                // to read
                // localBleVersion
                // mWriteCommand.sendToReadBLEVersion();
                break;
            case ICallbackStatus.GET_BLE_VERSION_OK: // after read
                // localBleVersion
                // finish,
                // then sync
                // step
                // mWriteCommand.syncAllStepData();
                break;
            case ICallbackStatus.DISCONNECT_STATUS:
                break;
            case ICallbackStatus.CONNECTED_STATUS:

                break;
            case ICallbackStatus.DISCOVERY_DEVICE_SHAKE://摇一摇
                // Discovery device Shake
                if (heytzSmartApp.getCallbackContext(Operation.SHAKEMODE.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, result);
                    pluginResult.setKeepCallback(true);
                    heytzSmartApp.getCallbackContext(Operation.SHAKEMODE.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.OFFLINE_RATE_SYNC_OK:
                break;
            case ICallbackStatus.SET_METRICE_OK: // 设置公制单位成功
                break;
            case ICallbackStatus.SET_INCH_OK: // 设置英制单位成功
                break;
            case ICallbackStatus.SET_FIRST_ALARM_CLOCK_OK: // 设置第1个闹钟OK
            case ICallbackStatus.SET_SECOND_ALARM_CLOCK_OK: // 设置第2个闹钟OK
            case ICallbackStatus.SET_THIRD_ALARM_CLOCK_OK: // 设置第3个闹钟OK
                if (heytzSmartApp.getCallbackContext(Operation.SENDTOSETALARMCOMMAND.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, status);
                    pluginResult.setKeepCallback(true);
                    heytzSmartApp.getCallbackContext(Operation.SENDTOSETALARMCOMMAND.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.SEND_PHONE_NAME_NUMBER_OK: //
                Log.d(TAG, "发送来电名字和号码 OK");
                break;
            case ICallbackStatus.SEND_QQ_WHAT_SMS_CONTENT_OK: //
                Log.d(TAG, "发送QQ、微信、短信内容OK");
                break;
            case ICallbackStatus.PASSWORD_SET:
                Log.d(TAG, "没设置过密码，请设置4位数字密码");
                break;
            case ICallbackStatus.PASSWORD_INPUT:
                Log.d(TAG, "已设置过密码，请输入已设置的4位数字密码");
                break;
            case ICallbackStatus.PASSWORD_AUTHENTICATION_OK:
                Log.d(TAG, "验证成功或者设置密码成功");
                break;
            case ICallbackStatus.PASSWORD_INPUT_AGAIN:
                Log.d(TAG, "验证失败或者设置密码失败，请重新输入4位数字密码，如果已设置过密码，请输入已设置的密码");
                break;
            case ICallbackStatus.OFFLINE_SWIM_SYNCING:
                Log.d(TAG, "游泳数据同步中");
                break;
            case ICallbackStatus.OFFLINE_SWIM_SYNC_OK:
                Log.d(TAG, "游泳数据同步完成");
                break;
            case ICallbackStatus.OFFLINE_BLOOD_PRESSURE_SYNCING:
                Log.d(TAG, "血压数据同步中");
                break;
            case ICallbackStatus.OFFLINE_BLOOD_PRESSURE_SYNC_OK:
                Log.d(TAG, "血压数据同步完成");
                break;
        }
        if (this.heytzSmartApp.getSmartBand() == null) {
            return;
        }
        JSONObject data = new JSONObject();
        try {
            data.put("result", result);
            data.put("status", status);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        String format = "cordova.plugins.SmartBand.HeytzICallback(%s);";
        final String js = String.format(format, data.toString());
        heytzSmartApp.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                heytzSmartApp.getSmartBand().webView.loadUrl("javascript:" + js);
            }
        });
    }

    @Override
    public void OnDataResult(boolean result, int status, byte[] data) {
        StringBuilder stringBuilder = null;
        if (data != null && data.length > 0) {
            stringBuilder = new StringBuilder(data.length);
            for (byte byteChar : data) {
                stringBuilder.append(String.format("%02X", byteChar));
            }
            Log.i("testChannel",
                    "BLE---->APK data =" + stringBuilder.toString());
        }
        if (status == ICallbackStatus.OPEN_CHANNEL_OK) {// 打开通道OK
        } else if (status == ICallbackStatus.CLOSE_CHANNEL_OK) {// 关闭通道OK
        } else if (status == ICallbackStatus.BLE_DATA_BACK_OK) {// 测试通道OK，通道正常
        }
    }

    @Override
    public void onCharacteristicWriteCallback(int status) {
        // 写入操作的系统回调，status = 0为写入成功，其他或无回调表示失败
        Log.d(TAG, "Write System callback status = " + status);
    }

    @Override
    public void onIbeaconWriteCallback(boolean b, int i, int i1, String s) {

    }

    @Override
    public void onQueryDialModeCallback(boolean b, int i, int i1, int i2) {

    }

    @Override
    public void onControlDialCallback(boolean b, int i, int i1) {

    }
}
