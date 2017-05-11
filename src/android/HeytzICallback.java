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

    /**
     * ICallback 回调结果
     *
     * @param result true 通信完成
     * @param status 如 ICallbackStatus 类中描述
     */
    @Override
    public void OnResult(boolean result, int status) {
        Log.i(TAG, "result=" + result + ",status=" + status);
        switch (status) {
            case ICallbackStatus.OFFLINE_STEP_SYNCING:
                Log.d(TAG, "步数同步中");
                // step snyc complete
                if (heytzSmartApp.getCallbackContext(Operation.SYNALLSTEPDATA.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, "syncing");
                    pluginResult.setKeepCallback(true);
                    heytzSmartApp.getCallbackContext(Operation.SYNALLSTEPDATA.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.OFFLINE_STEP_SYNC_OK:
                Log.d(TAG, "步数同步完成");
                // step snyc complete
                if (heytzSmartApp.getCallbackContext(Operation.SYNALLSTEPDATA.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, "ok");
                    heytzSmartApp.getCallbackContext(Operation.SYNALLSTEPDATA.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.OFFLINE_SLEEP_SYNCING:
                Log.d(TAG, "睡眠同步中");
                if (heytzSmartApp.getCallbackContext(Operation.SYNCALLSLEEPDATA.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, "syncing");
                    pluginResult.setKeepCallback(true);
                    heytzSmartApp.getCallbackContext(Operation.SYNCALLSLEEPDATA.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.OFFLINE_SLEEP_SYNC_OK:
                // sleep snyc complete
                Log.d(TAG, "睡眠同步完成");
                if (heytzSmartApp.getCallbackContext(Operation.SYNCALLSLEEPDATA.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, "ok");
                    heytzSmartApp.getCallbackContext(Operation.SYNCALLSLEEPDATA.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.SYNC_TIME_OK: // after set time
                // finish, then(or
                // delay 20ms) send
                // to read
                // localBleVersion
                // mWriteCommand.sendToReadBLEVersion();
                if (heytzSmartApp.getCallbackContext(Operation.SYNCBLETIME.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, result);
                    heytzSmartApp.getCallbackContext(Operation.SYNCBLETIME.getMethod()).sendPluginResult(pluginResult);
                }
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
            case ICallbackStatus.SEDENTARY_REMIND_OPEN:
            case ICallbackStatus.SEDENTARY_REMIND_CLOSE:
                Log.d(TAG, "久坐提醒");
                if (heytzSmartApp.getCallbackContext(Operation.SENDSEDENTARYREMINDCOMMAND.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, status);
                    heytzSmartApp.getCallbackContext(Operation.SENDSEDENTARYREMINDCOMMAND.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case ICallbackStatus.SET_STEPLEN_WEIGHT_OK:
                if (heytzSmartApp.getCallbackContext(Operation.SENDSTEPLENANDWEIGHTTOBLE.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, status);
                    heytzSmartApp.getCallbackContext(Operation.SENDSTEPLENANDWEIGHTTOBLE.getMethod()).sendPluginResult(pluginResult);
                }
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
        String format = "cordova.plugins.SmartBand.openHeytzICallback(%s);";
        final String js = String.format(format, data.toString());
        heytzSmartApp.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                heytzSmartApp.getSmartBand().webView.loadUrl("javascript:" + js);
            }
        });
    }

    /**
     * OnDataResult 交通卡接口回调结果
     *
     * @param result 通信完成
     * @param status 如 ICallbackStatus 类中 述
     * @param data   BLE 返回的数据
     */
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

    /**
     * 写入操作状态的系统回调，status = 0 为写入成功，其他或无回 调表示失败
     *
     * @param status
     */
    @Override
    public void onCharacteristicWriteCallback(int status) {
        // 写入操作的系统回调，status = 0为写入成功，其他或无回调表示失败
        Log.d(TAG, "Write System callback status = " + status);
    }

    /**
     * Ibeacon 功能设置和读取回调
     *
     * @param result
     * @param ibeaconSetOrGet
     * @param ibeaconType
     * @param data
     */
    @Override
    public void onIbeaconWriteCallback(boolean result, int ibeaconSetOrGet, int ibeaconType, String data) {

    }

    /**
     * 查询表盘方式的回调，请参考 MainActivity 使用
     *
     * @param result
     * @param screenWith
     * @param screenHeight
     * @param screenCount
     */
    @Override
    public void onQueryDialModeCallback(boolean result, int screenWith, int screenHeight, int screenCount) {

    }

    /**
     * 控制表盘切换和左右手切换回调，请参考 MainActivity 使用
     *
     * @param result
     * @param leftRightHand
     * @param dialType
     */
    @Override
    public void onControlDialCallback(boolean result, int leftRightHand, int dialType) {

    }
}
