package com.heytz.smartband;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import com.yc.pedometer.utils.GlobalVariable;
import org.apache.cordova.PluginResult;

/**
 * Created by chendongdong on 2017/5/12.
 */
public class HeytzHandler extends Handler {
    private final String TAG = "==========HeytzHandler===========\n";
    private HeytzSmartApp app;

    HeytzHandler(HeytzSmartApp app) {
        this.app = app;
    }

    @Override
    public void handleMessage(Message msg) {
        super.handleMessage(msg);
        switch (msg.what) {
            case GlobalVariable.GET_RSSI_MSG:
                Bundle bundle = msg.getData();
                if (app.getCallbackContext(Operation.READRSSI.getMethod()) != null) {
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, bundle.getInt(GlobalVariable.EXTRA_RSSI));
                    app.getCallbackContext(Operation.READRSSI.getMethod()).sendPluginResult(pluginResult);
                }
                break;
            case GlobalVariable.START_PROGRESS_MSG:
                Log.i(TAG, "(Boolean) msg.obj=" + (Boolean) msg.obj);
                break;
            case GlobalVariable.DOWNLOAD_IMG_FAIL_MSG:

                break;
            case GlobalVariable.DISMISS_UPDATE_BLE_DIALOG_MSG:
                Log.i(TAG, "(Boolean) msg.obj=" + (Boolean) msg.obj);
                break;
            case GlobalVariable.SERVER_IS_BUSY_MSG:
                break;
            case GlobalVariable.UPDATE_BLE_PROGRESS_MSG: // (新) 增加固件升级进度
                int schedule = msg.arg1;
                Log.i("zznkey", "schedule =" + schedule);
                break;
        }
    }
}
