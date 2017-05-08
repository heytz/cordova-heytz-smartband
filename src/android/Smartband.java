package com.heytz.smartband;

import android.bluetooth.BluetoothDevice;
import android.os.Handler;
import android.util.Log;
import com.yc.pedometer.sdk.BLEServiceOperate;
import com.yc.pedometer.sdk.DeviceScanInterfacer;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;

import java.util.ArrayList;

/**
 * This class echoes a string called from JavaScript.
 */
public class Smartband extends CordovaPlugin {
    private ArrayList<BluetoothDevice> mLeDevices;
    private boolean mScanning;
    private Handler mHandler;
    private String TAG = "\n=========SmartBand=========\n";
    private final int REQUEST_ENABLE_BT = 1;
    // Stops scanning after 10 seconds.
    private final long SCAN_PERIOD = 10000;

    private BLEServiceOperate mBLEServiceOperate;
    private DeviceScanInterfacer deviceScanInterfacer = new DeviceScanInterfacer() {
        @Override
        public void LeScanCallback(BluetoothDevice bluetoothDevice, int i) {
            if (!mLeDevices.contains(bluetoothDevice))
                mLeDevices.add(bluetoothDevice);
        }
    };

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        mHandler = new Handler();
        mLeDevices = new ArrayList<BluetoothDevice>();
        mBLEServiceOperate = BLEServiceOperate
                .getInstance(cordova.getActivity().getBaseContext());// 用于BluetoothLeService实例化准备,必须
        // Checks if Bluetooth is supported on the device.
        if (!mBLEServiceOperate.isSupportBle4_0()) {
            return;
        }
        mBLEServiceOperate.setDeviceScanListener(deviceScanInterfacer);//for DeviceScanInterfacer
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if (action.equals("scanDevice")) {
            this.scanDevice(true);
            Log.w(TAG, "scanDevice");
            callbackContext.success();
            return true;
        }
        return false;
    }

    /**
     * 扫描附近设备 默认十秒以后停止
     *
     * @param enable
     */
    private void scanDevice(final boolean enable) {
        if (enable) {
            // Stops scanning after a pre-defined scan period.
            mHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mScanning = false;
                    mBLEServiceOperate.stopLeScan();
                }
            }, SCAN_PERIOD);

            mScanning = true;
            mBLEServiceOperate.startLeScan();
        } else {
            mScanning = false;
            mBLEServiceOperate.stopLeScan();
        }
    }
}