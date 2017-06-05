package com.heytz.smartband;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import com.yc.pedometer.utils.GlobalVariable;

/**
 * Created by chendongdong on 2017/5/10.
 */
public class HeytzBroadcastReceiver extends BroadcastReceiver {
    private final String TAG = "=====HeytzBroadcastReceiver======";
    private HeytzSmartApp app;

    HeytzBroadcastReceiver(HeytzSmartApp app) {
        this.app = app;
    }

    /**
     * @param context
     * @param intent
     */
    @Override
    public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();
        Log.d(TAG, action);
        if (action.equals(GlobalVariable.READ_BLE_VERSION_ACTION)) {
            String version = intent
                    .getStringExtra(GlobalVariable.INTENT_BLE_VERSION_EXTRA);
            Log.w(TAG, "version=" + version);
            if (app.getCallbackContext(Operation.SENDTOREADBLEVERSION.getMethod()) != null) {
                app.getCallbackContext(Operation.SENDTOREADBLEVERSION.getMethod()).success(version);
            }
        } else if (action.equals(GlobalVariable.READ_BATTERY_ACTION)) {
            int battery = intent.getIntExtra(
                    GlobalVariable.INTENT_BLE_BATTERY_EXTRA, -1);
            Log.w(TAG, "battery=" + battery);
            if (app.getCallbackContext(Operation.SENDTOREADBLEBATTERY.getMethod()) != null) {
                app.getCallbackContext(Operation.SENDTOREADBLEBATTERY.getMethod()).success(battery);
            }
        }
    }
}
