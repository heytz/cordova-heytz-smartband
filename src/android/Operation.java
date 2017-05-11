package com.heytz.smartband;

/**
 * Created by chendongdong on 2017/5/10.
 */
public enum Operation {

    //初始化
    INIT("init"),
    //扫描
    SCAN("scan"),
    //停止扫描
    STOPSCAN("stopScan"),
    //是否支持BLE4.0
    ISSUPPORTED("isSupported"),
    //判断蓝牙是否打开
    ISENABLED("isEnabled"),
    //连接
    CONNECT("connect"),
    //断开设备
    DISCONNECT("disConnect"),
    //解绑服务
    UNBINDSERVICE("unBindService"),
    //写入
    WRITE("write"),
    //同步时间
    SYNCBLETIME("syncBLETime"),
    //请求蓝牙版本信息
    SENDTOREADBLEVERSION("sendToReadBLEVersion"),
    //请求蓝牙电池电量指令
    SENDTOREADBLEBATTERY("sendToReadBLEBattery"),
    //同步运动数据
    SYNCRUNDATA("syncRunData"),
    //同步睡眠数据
    SYNCSLEEPDATA("syncSleepData"),
    //设置 BEL 端步长;体重;灭屏时间;目标步数;抬手亮屏开关 true 为开，false 为关;最高心率 醒，true 为开，false 为关;最后一个参数为最高心率 醒 的值。 醒:修改身高体重后，需要同步一次计步数据，应用上的距离和卡 路里才会按照新修改的身高体重进行计算并更新。
    SENDSTEPLENANDWEIGHTTOBLE("sendStepLenAndWeightToBLE"),
    //同步计步数据(连上设备后，请同步一次步数(实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
    SYNALLSTEPDATA("syncAllStepData"),
    //新一天初始化计步数据库
    UPDATESTEPSQL("updateStepSQL"),
    //查询一天的总步数
    QUERYSTEPDATE("queryStepDate"),
    //查询一天的步数、距离、卡路里
    QUERYSTEPDINFO("queryStepInfo"),
    //查询某一天各小时步数
    QUERYONEHOURSTEPSQL("queryOneHourStepSQL"),
    //同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
    SYNCALLSLEEPDATA("syncAllSleepData"),
    //查询一天的睡眠总时间
    QUERYSLEEPDATE("querySleepDate"),
    //查询一天的睡眠详情
    QUERYSLEEPINFO("querySleepInfo"),
    //打开摇摇功能(之后发现设备被摇一摇时，会在 ICallback 中返回状态， ICallbackStatus.DISCOVERY_DEVICE_SHAKE)，常用于摇摇拍照等功能的实 现。
    SHAKEMODE("shakeMode"),
    //关闭摇摇功能
    CLOSESHAKEMODE("closeShakeMode"),
    //清除设备所有数据，即设备恢复出厂设置
    DELETEDEVICEALLDATA("deleteDevicesAllData"),
    //发送久坐 醒功能开启/关闭指令以及 醒周期
    SENDSEDENTARYREMINDCOMMAND("sendSedentaryRemindCommand"),
    //发送设置闹钟指令
    SENDTOSETALARMCOMMAND("sendToSetAlarmCommand"),
    //查找手环
    FINDBAND("findBand"),
    //同步数据
    SYNCALLRATEDATA("syncAllRateData"),
    //查询设备升级属性 (升级前必须调用查询)
    QUERYDEVICEFEARTURE("queryDeviceFearture"),
    //读取线损值
    READRSSI("readRssi"),
    //判断平台
    ISRKPLATFORM("isRKPlatform"),
    GETSERVERBTIMGVERSION("getServerBtImgVersion"),
    GETSERVERPATCHVERSION("getServerPatchVersion");

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

