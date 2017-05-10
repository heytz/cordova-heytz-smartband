package com.heytz.smartband;

/**
 * Created by chendongdong on 2017/5/10.
 */
public enum Operation {

    SCAN("scan"),           //扫描
    STOPSCAN("stopScan"),           //停止扫描
    ISSUPPORTED("isSupported"),                   //
    ISENABLED("isEnabled"),                         //判断蓝牙是否打开
    CONNECT("connect"),                    //绑定
    WRITE("write"),                       //写入
    SYNCBLETIME("syncBLETime"),                          //同步时间
    SENDTOREADBLEVERSION("sendToReadBLEVersion"),                  //请求蓝牙版本信息
    SENDTOREADBLEBATTERY("sendToReadBLEBattery"),          //请求蓝牙电池电量指令
    SYNCRUNDATA("syncRunData"),              //同步运动数据
    SYNCSLEEPDATA("syncSleepData"),          //同步睡眠数据
    SENDSTEPLENANDWEIGHTTOBLE("sendStepLenAndWeightToBLE"),            //设置 BEL 端步长;体重;灭屏时间;目标步数;抬手亮屏开关 true 为开，false 为关;最高心率 醒，true 为开，false 为关;最后一个参数为最高心率 醒 的值。 醒:修改身高体重后，需要同步一次计步数据，应用上的距离和卡 路里才会按照新修改的身高体重进行计算并更新。
    SYNALLSTEPDATA("syncAllStepData"),                    //同步计步数据(连上设备后，请同步一次步数(实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
    SYNCALLSLEEPDATA("syncAllSleepData"),                                    //同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
    SHAKEMODE("shakeMode"),//打开摇摇功能(之后发现设备被摇一摇时，会在 ICallback 中返回状态， ICallbackStatus.DISCOVERY_DEVICE_SHAKE)，常用于摇摇拍照等功能的实 现。
    CLOSESHAKEMODE("closeShakeMode"),//关闭摇摇功能
    DELETEDEVICEALLDATA("deleteDevicesAllData"),//清除设备所有数据，即设备恢复出厂设置
    SENDSEDENTARYREMINDCOMMAND("sendSedentaryRemindCommand"),//发送久坐 醒功能开启/关闭指令以及 醒周期
    SENDTOSETALARMCOMMAND("sendToSetAlarmCommand"),//发送设置闹钟指令
    FINDBAND("findBand"),//查找手环
    SYNCALLRATEDATA("syncAllRateData"),//查找手环
    QUERYDEVICEFEARTURE("queryDeviceFearture");//查询设备升级属性 (升级前必须调用查询)

    private String method;

    private Operation(String method) {
        this.method = method;
    }

    public Operation getOpervation(String method) {
        for (Operation o : Operation.values()) {
            if (o.method.equals(method)) {
                return o;
            }
        }
        return null;
    }

    public String getMethod() {
        return this.method;
    }
}

