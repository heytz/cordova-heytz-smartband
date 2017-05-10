package com.heytz.smartband;

import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Handler;
import android.util.Log;
import com.yc.pedometer.sdk.*;
import com.yc.pedometer.update.Updates;
import com.yc.pedometer.utils.GlobalVariable;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;

/**
 * This class echoes a string called from JavaScript.
 */

public class Smartband extends CordovaPlugin {
    private Handler mHandler;
    private String TAG = "\n=========SmartBand=========\n";
    private final int REQUEST_ENABLE_BT = 1;
    // Stops scanning after 10 seconds.
    private final long SCAN_PERIOD = 10000;
    private CallbackContext scanCallback;

    private BLEServiceOperate mBLEServiceOperate;
    private BluetoothLeService mBluetoothLeService;
    private WriteCommandToBLE mWriteCommand;
    private HeytzICallback heytziCallback;
    private HeytzDeviceScanInterfacer heytzDeviceScanInterfacer;
    private HeytzServiceStatusCallback heytzServiceStatusCallback;
    private HeytzOnServerCallbackListener heytzOnServerCallbackListener;
    private HeytzOnBleServiceUpdateListener heytzOnBleServiceUpdateListener;
    private HeytzBroadcastReceiver heytzBroadcastReceiver;
    private Updates mUpdates;
    private DataProcessing mDataProcessing;
    private HeytzSmartApp heytzSmartApp;

    private StepChangeListener stepChangeListener = new StepChangeListener() {
        @Override
        public void onStepChange(int i, float v, int i1) {

        }
    };
    private SleepChangeListener sleepChangeListener = new SleepChangeListener() {
        @Override
        public void onSleepChange() {

        }
    };

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        Context context = cordova.getActivity().getApplicationContext();
        mBLEServiceOperate = BLEServiceOperate.getInstance(context);// 用于BluetoothLeService实例化准备,必须
        heytzSmartApp = new HeytzSmartApp();
        mHandler = new Handler();
        heytzDeviceScanInterfacer = new HeytzDeviceScanInterfacer(heytzSmartApp);
        heytziCallback = new HeytzICallback(heytzSmartApp);
        heytzServiceStatusCallback = new HeytzServiceStatusCallback(heytzSmartApp);
        heytzOnServerCallbackListener = new HeytzOnServerCallbackListener(heytzSmartApp);
        heytzOnBleServiceUpdateListener = new HeytzOnBleServiceUpdateListener(heytzSmartApp);
        heytzBroadcastReceiver = new HeytzBroadcastReceiver(heytzSmartApp);
        // Checks if Bluetooth is supported on the device.
        if (!mBLEServiceOperate.isSupportBle4_0()) {
            return;
        }
        mBLEServiceOperate.setServiceStatusCallback(heytzServiceStatusCallback);
        mBLEServiceOperate.setDeviceScanListener(heytzDeviceScanInterfacer);//for DeviceScanInterfacer
        mBluetoothLeService = mBLEServiceOperate.getBleService();
        mBluetoothLeService.setICallback(heytziCallback);
        mBluetoothLeService.setBleServiceStatusListener(heytzOnBleServiceUpdateListener);
        //写入命令
        mWriteCommand = WriteCommandToBLE.getInstance(cordova.getActivity().getApplicationContext());
        //数据监听
        mDataProcessing = DataProcessing.getInstance(context);
        mDataProcessing.setOnStepChangeListener(stepChangeListener);//步数变化监听
        mDataProcessing.setOnSleepChangeListener(sleepChangeListener);//listener 睡眠监听
//        mDataProcessing.setOnRateListener(mOnRateListener);//心率监听
//        mDataProcessing.setOnBloodPressureListener(bloodPressureChangeListener);//Listener 血压监听

        mRegisterReceiver();
        mUpdates = Updates.getInstance(context);
        mUpdates.setHandler(mHandler);// 获取升级操作信息
        mUpdates.registerBroadcastReceiver();
        mUpdates.setOnServerCallbackListener(heytzOnServerCallbackListener);
        Log.d("onServerDiscorver", "MainActivity_onCreate   mUpdates  ="
                + mUpdates);
    }

    private void mRegisterReceiver() {
        IntentFilter mFilter = new IntentFilter();
        mFilter.addAction(GlobalVariable.READ_BATTERY_ACTION);
        mFilter.addAction(GlobalVariable.READ_BLE_VERSION_ACTION);
        cordova.getActivity().registerReceiver(heytzBroadcastReceiver, mFilter);
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        heytzSmartApp.setCallbackContext(action, callbackContext);
        if (action.equals(Operation.SCAN.getMethod())) {
            heytzSmartApp.clearLeDeviceList();
            scanDevice(true, 0);
            scanCallback = callbackContext;
            return true;
        }
        if (action.equals(Operation.STOPSCAN.getMethod())) {
            this.scanDevice(false, 0);
            callbackContext.success();
            return true;
        }
        if (action.equals(Operation.ISSUPPORTED.getMethod())) {
            if (mBLEServiceOperate.isSupportBle4_0()) {
                callbackContext.success();
            } else {
                callbackContext.error("nonsupport");
            }
            return true;
        }
        if (action.equals(Operation.CONNECT.getMethod())) {
            boolean isExist = false;
            String address = args.getString(0);
            for (int i = 0; i < heytzSmartApp.getLeDeviceList().size(); i++) {
                if (heytzSmartApp.getLeDeviceList().get(i).getAddress().equals(address)) {
                    isExist = true;
                    if (mBLEServiceOperate.connect(heytzSmartApp.getLeDeviceList().get(i).getAddress())) {
                        callbackContext.success();
                    } else {
                        callbackContext.error("connect error!");
                    }
                }
            }
            if (!isExist) {
                callbackContext.error("device don't exist");
            }
            return true;
        }
        if (action.equals(Operation.ISENABLED.getMethod())) {
            if (mBLEServiceOperate.isBleEnabled()) {
                callbackContext.success();
            } else {
                Intent enableBtIntent = new Intent(
                        BluetoothAdapter.ACTION_REQUEST_ENABLE);
                cordova.getActivity().startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
                callbackContext.error("Bluetooth is disabled.");
            }
            return true;
        }
//        if (action.equals(Operation.WRITE.getMethod())) {
//            int type = args.getInt(0);
//            boolean value = args.getBoolean(1);
//            switch (type) {
//                case 0:
//                    mWriteCommand.sendToSetAlarmCommand(1, GlobalVariable.EVERYDAY,
//                            16, 25, value, 5);// 新增最后一个参数，振动次数//2.2.1版本修改
//                    break;
//                case 1:
//                    mWriteCommand.syncBLETime();
//                    break;
//
//            }
//            return true;
//        }
        //同步时间
        if (action.equals(Operation.SYNCBLETIME.getMethod())) {
            mWriteCommand.syncBLETime();
            callbackContext.success();
        }
        //读取电量
        if (action.equals(Operation.SENDTOREADBLEBATTERY.getMethod())) {
            mWriteCommand.sendToReadBLEBattery();
        }
        //读取版本号
        if (action.equals(Operation.SENDTOREADBLEVERSION.getMethod())) {
            mWriteCommand.sendToReadBLEVersion();
        }
        //发送久坐 醒功能开启/关闭指令以及 醒周期
        if (action.equals(Operation.SENDSEDENTARYREMINDCOMMAND.getMethod())) {
            int flag = args.getInt(0);
            int minutes = args.getInt(1);
            mWriteCommand.sendSedentaryRemindCommand(flag, minutes);
            callbackContext.success();
        }
        //摇一摇
        if (action.equals(Operation.SHAKEMODE.getMethod())) {
            Boolean state = args.getBoolean(0);
            if (state) {
                mWriteCommand.openShakeMode();
            } else {
                mWriteCommand.closeShakeMode();
                callbackContext.success();
            }
        }
        //发送设置闹钟指令
        if (action.equals(Operation.SENDTOSETALARMCOMMAND.getMethod())) {
            int whichClock = args.getInt(0);
            String weekPeroidString = args.getString(1);
            int hour = args.getInt(2);
            int minute = args.getInt(3);
            boolean isOpen = args.getBoolean(4);
            int shakePeriod = args.getInt(5);
            byte weekPeroid = 0;
            if (weekPeroidString.contains("everyday")) {
                weekPeroid = GlobalVariable.EVERYDAY;
            } else {
                String[] dayList = weekPeroidString.split(",");
                for (String value : dayList) {
                    if (value.equals("sunday")) {
                        weekPeroid |= GlobalVariable.SUNDAY;
                    } else if (value.equals("monday")) {
                        weekPeroid |= GlobalVariable.MONDAY;
                    } else if (value.equals("tuesday")) {
                        weekPeroid |= GlobalVariable.TUESDAY;
                    } else if (value.equals("wednesday")) {
                        weekPeroid |= GlobalVariable.WEDNESDAY;
                    } else if (value.equals("thursday")) {
                        weekPeroid |= GlobalVariable.THURSDAY;
                    } else if (value.equals("saturday")) {
                        weekPeroid |= GlobalVariable.SATURDAY;
                    }
                }
            }
            mWriteCommand.sendToSetAlarmCommand(whichClock, weekPeroid,
                    hour, minute, isOpen, shakePeriod);// 新增最后一个参数，振动次数//2.2.1版本修改
        }
        //发身高体重和灭屏时间、目标步数、抬手亮屏
        // 醒:修改身高体重后，需要同步一次计步数据，应用上的距离和卡 路里才会按照新修改的身高体重进行计算并更新。
        if (action.equals(Operation.SENDSTEPLENANDWEIGHTTOBLE.getMethod())) {
            int height = args.getInt(0);//身高(cm)
            int weight = args.getInt(1);//体重(kg)
            int offScreenTime = args.getInt(2);//灭屏时间(秒)
            int stepTask = args.getInt(3);//目标步数
            boolean isRraisHandbrightScreenSwitchOpen = args.getBoolean(4);//抬手亮屏开关 true 为开，false 为关
            boolean isHighestRateOpen = args.getBoolean(5);//最高心率 醒，true 为开，false 为关
            int highestRate = args.getInt(6);//最后一个参数为最高心率 醒 的值。
            mWriteCommand.sendStepLenAndWeightToBLE(height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate);// 新增最后一个参数，振动次数//2.2.1版本修改
        }
        //查找手环
        if (action.equals(Operation.FINDBAND.getMethod())) {
            int vibrationCount = args.getInt(0);
            mWriteCommand.findBand(vibrationCount);
        }
        //清除设备所有数据，即设备恢复出厂设置
        if (action.equals(Operation.DELETEDEVICEALLDATA.getMethod())) {
            mWriteCommand.deleteDevicesAllData();
        }
        //同步计步数据(连上设备后，请同步一次步数(实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
        if (action.equals(Operation.SYNALLSTEPDATA.getMethod())) {
            mWriteCommand.syncAllStepData();
        }
        //同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
        if (action.equals(Operation.SYNCALLSLEEPDATA.getMethod())) {
            mWriteCommand.syncAllSleepData();
        }
        //查询设备升级属性 (升级前必须调用查询
        if (action.equals(Operation.QUERYDEVICEFEARTURE.getMethod())) {
            mWriteCommand.queryDeviceFearture();
        }
        return false;
    }

    /**
     * 扫描附近设备 默认十秒以后停止
     *
     * @param enable
     */
    private void scanDevice(boolean enable, int scanSeconds) {
        if (mBLEServiceOperate == null) {
            scanCallback.error("mBLEServiceOperate is null!");
            return;
        }
        if (enable) {
            mHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mBLEServiceOperate.stopLeScan();
                }
            }, scanSeconds <= 0 ? SCAN_PERIOD : scanSeconds * 1000);
            mBLEServiceOperate.startLeScan();
        } else {
            mBLEServiceOperate.stopLeScan();
        }
    }


}