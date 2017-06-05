package com.heytz.smartband;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.util.Log;
import com.yc.pedometer.info.SleepTimeInfo;
import com.yc.pedometer.info.StepInfo;
import com.yc.pedometer.info.StepOneHourInfo;
import com.yc.pedometer.sdk.*;
import com.yc.pedometer.update.Updates;
import com.yc.pedometer.utils.GlobalVariable;
import org.apache.cordova.*;
import org.json.JSONArray;
import org.json.JSONException;

import java.util.ArrayList;
import java.util.List;

/**
 * This class echoes a string called from JavaScript.
 */

public class SmartBand extends CordovaPlugin {
    private HeytzHandler heytzHandler;
    private String TAG = "\n=========SmartBand=========\n";
    private final int REQUEST_ENABLE_BT = 1;
    private CallbackContext scanCallback;
    private BLEServiceOperate mBLEServiceOperate;
    private BluetoothLeService mBluetoothLeService;
    private WriteCommandToBLE mWriteCommand;
    private UTESQLOperate utesqlOperate;
    private HeytzICallback heytziCallback;
    private HeytzDeviceScanInterfacer heytzDeviceScanInterfacer;
    private HeytzServiceStatusCallback heytzServiceStatusCallback;
    private HeytzOnServerCallbackListener heytzOnServerCallbackListener;
    private HeytzOnBleServiceUpdateListener heytzOnBleServiceUpdateListener;
    private HeytzBroadcastReceiver heytzBroadcastReceiver;
    private HeytzStepChangeListener heytzStepChangeListener;
    private HeytzSleepChangeListener heytzSleepChangeListener;
    private Updates mUpdates;
    private DataProcessing mDataProcessing;
    private HeytzSmartApp app;

    // Android 23 requires new permissions for mBLEServiceOperate.startScan()
    private static final String ACCESS_COARSE_LOCATION = Manifest.permission.ACCESS_COARSE_LOCATION;
    private static final int REQUEST_ACCESS_COARSE_LOCATION = 2;
    private static final int PERMISSION_DENIED_ERROR = 20;

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        Context context = cordova.getActivity().getApplicationContext();
        mBLEServiceOperate = BLEServiceOperate.getInstance(context);// 用于BluetoothLeService实例化准备,必须
        app = new HeytzSmartApp(this);
        app.setActivity(cordova.getActivity());

        heytzHandler = new HeytzHandler(app);
        heytzDeviceScanInterfacer = new HeytzDeviceScanInterfacer(app);
        heytziCallback = new HeytzICallback(app);
        heytzServiceStatusCallback = new HeytzServiceStatusCallback(app);
        heytzOnServerCallbackListener = new HeytzOnServerCallbackListener(app);
        heytzOnBleServiceUpdateListener = new HeytzOnBleServiceUpdateListener(app);
        heytzBroadcastReceiver = new HeytzBroadcastReceiver(app);
        heytzStepChangeListener = new HeytzStepChangeListener(app);
        heytzSleepChangeListener = new HeytzSleepChangeListener(app);
        // Checks if Bluetooth is supported on the device.
        if (!mBLEServiceOperate.isSupportBle4_0()) {
            return;
        }
        mBLEServiceOperate.setServiceStatusCallback(heytzServiceStatusCallback);
        mBLEServiceOperate.setDeviceScanListener(heytzDeviceScanInterfacer);//for DeviceScanInterfacer
        mBluetoothLeService = mBLEServiceOperate.getBleService();
        mBluetoothLeService.setICallback(heytziCallback);
        mBluetoothLeService.setBleServiceStatusListener(heytzOnBleServiceUpdateListener);
        mBluetoothLeService.setRssiHandler(heytzHandler);
        //写入命令
        mWriteCommand = WriteCommandToBLE.getInstance(cordova.getActivity().getApplicationContext());
        //数据监听
        mDataProcessing = DataProcessing.getInstance(context);
        mDataProcessing.setOnStepChangeListener(heytzStepChangeListener);//步数变化监听
        mDataProcessing.setOnSleepChangeListener(heytzSleepChangeListener);//listener 睡眠监听
//        mDataProcessing.setOnRateListener(mOnRateListener);//心率监听
//        mDataProcessing.setOnBloodPressureListener(bloodPressureChangeListener);//Listener 血压监听

        mRegisterReceiver();
        mUpdates = Updates.getInstance(context);
        mUpdates.setHandler(heytzHandler);// 获取升级操作信息
        mUpdates.registerBroadcastReceiver();
        mUpdates.setOnServerCallbackListener(heytzOnServerCallbackListener);
        Log.d("onServerDiscorver", "MainActivity_onCreate   mUpdates  ="
                + mUpdates);

        //数据
        utesqlOperate = UTESQLOperate.getInstance(context);

    }

    private void mRegisterReceiver() {
        IntentFilter mFilter = new IntentFilter();
        mFilter.addAction(GlobalVariable.READ_BATTERY_ACTION);
        mFilter.addAction(GlobalVariable.READ_BLE_VERSION_ACTION);
        cordova.getActivity().registerReceiver(heytzBroadcastReceiver, mFilter);
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        app.setCallbackContext(action, callbackContext);
        if (action.equals(Operation.INIT.getMethod())) {
            callbackContext.success();
            return true;
        } else if (action.equals(Operation.SCAN.getMethod())) {
            app.clearLeDeviceList();
            scanDevice(callbackContext, true, 0);
            scanCallback = callbackContext;
            return true;
        } else if (action.equals(Operation.STOPSCAN.getMethod())) {
            this.scanDevice(callbackContext, false, 0);
            callbackContext.success();
            return true;
        } else if (action.equals(Operation.ISSUPPORTED.getMethod())) {
            if (mBLEServiceOperate.isSupportBle4_0()) {
                callbackContext.success();
            } else {
                callbackContext.error("nonsupport");
            }
            return true;
        } else if (action.equals(Operation.CONNECT.getMethod())) {
            String address = args.getString(0);
            ArrayList<BluetoothDevice> devices = app.getLeDeviceList();
            for (BluetoothDevice device : devices) {
                String currentDeviceAddress = device.getAddress();
                if (currentDeviceAddress.equals(address)) {
                    if (mBLEServiceOperate.connect(currentDeviceAddress)) {
                        callbackContext.success();
                    } else {
                        callbackContext.error("connect error!");
                    }
                    return true;
                }
            }
            callbackContext.error("device don't exist");
            return true;
        } else if (action.equals(Operation.DISCONNECT.getMethod())) {
            mBLEServiceOperate.disConnect();
            return true;
        } else if (action.equals(Operation.UNBINDSERVICE.getMethod())) {
            mBLEServiceOperate.unBindService();
            callbackContext.success();
            return true;
        } else if (action.equals(Operation.ISENABLED.getMethod())) {
            if (mBLEServiceOperate.isBleEnabled()) {
                callbackContext.success();
            } else {
                Intent enableBtIntent = new Intent(
                        BluetoothAdapter.ACTION_REQUEST_ENABLE);
                cordova.getActivity().startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
                callbackContext.error("Bluetooth is disabled.");
            }
            return true;
        } else if (action.equals(Operation.SYNCBLETIME.getMethod())) {//同步时间
            mWriteCommand.syncBLETime();
            callbackContext.success();
            return true;
        } else if (action.equals(Operation.SENDTOREADBLEBATTERY.getMethod())) {//读取电量
            mWriteCommand.sendToReadBLEBattery();
            return true;
        } else if (action.equals(Operation.SENDTOREADBLEVERSION.getMethod())) {//读取版本号
            mWriteCommand.sendToReadBLEVersion();
            return true;
        } else if (action.equals(Operation.SENDSEDENTARYREMINDCOMMAND.getMethod())) {//发送久坐 醒功能开启/关闭指令以及 醒周期
            int flag = args.getInt(0);
            int minutes = args.getInt(1);
            mWriteCommand.sendSedentaryRemindCommand(flag, minutes);
            return true;
        } else if (action.equals(Operation.SHAKEMODE.getMethod())) { //摇一摇
            Boolean state = args.getBoolean(0);
            if (state) {
                mWriteCommand.openShakeMode();
            } else {
                mWriteCommand.closeShakeMode();
                callbackContext.success();
            }
            return true;
        } else if (action.equals(Operation.SENDTOSETALARMCOMMAND.getMethod())) { //发送设置闹钟指令
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
                    } else if (value.equals("friday")) {
                        weekPeroid |= GlobalVariable.FRIDAY;
                    } else if (value.equals("saturday")) {
                        weekPeroid |= GlobalVariable.SATURDAY;
                    }
                }
            }
            mWriteCommand.sendToSetAlarmCommand(whichClock, weekPeroid,
                    hour, minute, isOpen, shakePeriod);// 新增最后一个参数，振动次数//2.2.1版本修改
            return true;
        } else if (action.equals(Operation.SENDSTEPLENANDWEIGHTTOBLE.getMethod())) {
            //发身高体重和灭屏时间、目标步数、抬手亮屏
            // 醒:修改身高体重后，需要同步一次计步数据，应用上的距离和卡 路里才会按照新修改的身高体重进行计算并更新。
            int height = args.getInt(0);//身高(cm)
            int weight = args.getInt(1);//体重(kg)
            int offScreenTime = args.getInt(2);//灭屏时间(秒)
            int stepTask = args.getInt(3);//目标步数
            boolean isRraisHandbrightScreenSwitchOpen = args.getBoolean(4);//抬手亮屏开关 true 为开，false 为关
            boolean isHighestRateOpen = args.getBoolean(5);//最高心率 醒，true 为开，false 为关
            int highestRate = args.getInt(6);//最后一个参数为最高心率 醒 的值。
            mWriteCommand.sendStepLenAndWeightToBLE(height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate);// 新增最后一个参数，振动次数//2.2.1版本修改
            return true;
        } else if (action.equals(Operation.FINDBAND.getMethod())) { //查找手环
            int vibrationCount = args.getInt(0);
            mWriteCommand.findBand(vibrationCount);
            return true;
        } else if (action.equals(Operation.DELETEDEVICEALLDATA.getMethod())) { //清除设备所有数据，即设备恢复出厂设置
            mWriteCommand.deleteDevicesAllData();
            callbackContext.success();
            return true;
        } else if (action.equals(Operation.SYNALLSTEPDATA.getMethod())) { //同步计步数据(连上设备后，请同步一次步数(实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
            mWriteCommand.syncAllStepData();
            return true;
        } else if (action.equals(Operation.UPDATESTEPSQL.getMethod())) { //新一天初始化计步数据库
            utesqlOperate.updateStepSQL();
            callbackContext.success();
            return true;
        } else if (action.equals(Operation.QUERYSTEPDATE.getMethod())) {//查询一天的总步数
            String queryDate = args.getString(0);
            int totalStep = utesqlOperate.queryStepDate(queryDate);
            callbackContext.success(totalStep);
            return true;
        } else if (action.equals(Operation.QUERYSTEPDINFO.getMethod())) {//查询一天的步数、距离、卡路里
            String queryDate = args.getString(0);
            StepInfo stepInfo = utesqlOperate.queryStepInfo(queryDate);
            callbackContext.success(HeytzUtil.stepInfoToJSONObject(stepInfo));
            return true;
        } else if (action.equals(Operation.QUERYONEHOURSTEPSQL.getMethod())) { //查询某一天各小时步数
            String queryDate = args.getString(0);
            List<StepOneHourInfo> stepList = utesqlOperate.queryOneHourStepSQL(queryDate);
            JSONArray jsonArray = new JSONArray();
            for (StepOneHourInfo aStepList : stepList) {
                jsonArray.put(HeytzUtil.stepOneHourInfoToJSONObject(aStepList));
            }
            callbackContext.success(jsonArray);
            return true;
        } else if (action.equals(Operation.SYNCALLSLEEPDATA.getMethod())) { //同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
            mWriteCommand.syncAllSleepData();
            return true;
        } else if (action.equals(Operation.QUERYSLEEPDATE.getMethod())) { //查询一天的睡眠总时间
            String queryDate = args.getString(0);
            int miuntes = utesqlOperate.querySleepDate(queryDate);
            callbackContext.success(miuntes);
            return true;
        } else if (action.equals(Operation.QUERYSLEEPINFO.getMethod())) {//查询一天的睡眠详情
            String calendar = args.getString(0);
            SleepTimeInfo sleepTimeInfo = utesqlOperate.querySleepInfo(calendar);
            callbackContext.success(HeytzUtil.sleepTimeInfoToJSONObject(sleepTimeInfo));
            return true;
        } else if (action.equals(Operation.QUERYDEVICEFEARTURE.getMethod())) { //查询设备升级属性 (升级前必须调用查询
            mWriteCommand.queryDeviceFearture();
            return true;
        } else if (action.equals(Operation.READRSSI.getMethod())) { //查询设备升级属性 (升级前必须调用查询
            mBluetoothLeService.readRssi();
            return true;
        } else if (action.equals(Operation.ISRKPLATFORM.getMethod())) { //判断平台
            boolean b = mUpdates.isRKPlatform();
            PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, b);
            callbackContext.sendPluginResult(pluginResult);
            return true;
        } else if (action.equals(Operation.GETSERVERBTIMGVERSION.getMethod())) { //获取新版本的版本号
            String version = mUpdates.getServerBtImgVersion();
            callbackContext.success(version);
            return true;
        } else if (action.equals(Operation.GETSERVERPATCHVERSION.getMethod())) {//获取新版本的版本号。 示:RK 平台才有 patch 版本号。
            String version = mUpdates.getServerPatchVersion();
            callbackContext.success(version);
            return true;
        } else if (action.equals(Operation.GETSERVERPATCHVERSION.getMethod())) {
            mWriteCommand.sendOffHookCommand();
            return true;
        }
        return false;
    }

    /**
     * 扫描附近设备 默认十秒以后停止
     *
     * @param enable
     */
    private void scanDevice(CallbackContext callbackContext, boolean enable, int scanSeconds) {
        if (!PermissionHelper.hasPermission(this, ACCESS_COARSE_LOCATION)) {
            // save info so we can call this method again after permissions are granted
            app.setCallbackContext(Operation.PermissionCallback.getMethod(), callbackContext);
            app.setEnable(enable);
            app.setScanSeconds(scanSeconds);
            PermissionHelper.requestPermission(this, REQUEST_ACCESS_COARSE_LOCATION, ACCESS_COARSE_LOCATION);
            return;
        }
        if (mBLEServiceOperate == null) {
            scanCallback.error("mBLEServiceOperate is null!");
            return;
        }
        if (enable) {
            heytzHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mBLEServiceOperate.stopLeScan();
                }
            }, scanSeconds <= 0 ? app.getScanPeriod() : scanSeconds * 1000);
            mBLEServiceOperate.startLeScan();
        } else {
            mBLEServiceOperate.stopLeScan();
        }
    }

    /* @Override */
    public void onRequestPermissionResult(int requestCode, String[] permissions,
                                          int[] grantResults) /* throws JSONException */ {
        CallbackContext callbackContext = app.getCallbackContext(Operation.PermissionCallback.getMethod());
        for (int result : grantResults) {
            if (result == PackageManager.PERMISSION_DENIED) {
                LOG.d(TAG, "User *rejected* Coarse Location Access");
                if (callbackContext != null) {
                    callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, PERMISSION_DENIED_ERROR));
                }
                return;
            }
        }
        switch (requestCode) {
            case REQUEST_ACCESS_COARSE_LOCATION:
                LOG.d(TAG, "User granted Coarse Location Access");
                if (callbackContext != null) {
                    scanDevice(callbackContext, app.getEnable(), app.getScanSeconds());
                }
                break;
        }
    }
}