//
//  HeytzOperation.h
//  xbracelet-App
//
//  Created by KevinChen on 2017/5/25.
//
//

#ifndef HeytzOperation_h
#define HeytzOperation_h

typedef enum heytzMethods {
    INIT = 1, //初始化
    SCAN,//扫描
    STOP, //停止扫描
    ISSUPPORTED,//是否支持BLE4.0
    ISENABLED,//判断蓝牙是否打开
    CONNECT,//连接
    DISCONNECT,//断开设备
    UNBINDSERVICE, //解绑服务
    WRITE,//写入
    SYNCBLETIME,    //同步时间
    SENDTOREADBLEVERSION, //请求蓝牙版本信息
    SENDTOREADBLEBATTERY,  //请求蓝牙电池电量指令
    SYNCRUNDATA,//同步运动数据
    SYNCSLEEPDATA,//同步睡眠数据
    SENDSTEPLENANDWEIGHTTOBLE, //设置 BEL 端步长;体重;灭屏时间;目标步数;抬手亮屏开关 true 为开，false 为关;最高心率 醒，true 为开，false 为关;最后一个参数为最高心率 醒 的值。 醒:修改身高体重后，需要同步一次计步数据，应用上的距离和卡 路里才会按照新修改的身高体重进行计算并更新。
    SYNALLSTEPDATA, //同步计步数据= @连上设备后，请同步一次步数= @实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
    UPDATESTEPSQL, //新一天初始化计步数据库
    QUERYSTEPDATE, //查询一天的总步数
    QUERYSTEPDINFO, //查询一天的步数、距离、卡路里
    QUERYONEHOURSTEPSQL, //查询某一天各小时步数
    SYNCALLSLEEPDATA, //同步睡眠数据= @同步完成前，请不要进行其他任何的通信工作)
    QUERYSLEEPDATE, //查询一天的睡眠总时间
    QUERYSLEEPINFO, //查询一天的睡眠详情
    SHAKEMODE,  //打开摇摇功能= @之后发现设备被摇一摇时，会在 ICallback 中返回状态， ICallbackStatus.DISCOVERY_DEVICE_SHAKE)，常用于摇摇拍照等功能的实 现。
    CLOSESHAKEMODE,//关闭摇摇功能
    DELETEDEVICEALLDATA, //清除设备所有数据，即设备恢复出厂设置
    SENDSEDENTARYREMINDCOMMAND,  //发送久坐 醒功能开启/关闭指令以及 醒周期
    SENDTOSETALARMCOMMAND, //发送设置闹钟指令
    FINDBAND,  //查找手环
    SYNCALLRATEDATA,   //同步数据
    SYNCALLDATA, //同步所有数据
    QUERYDEVICEFEARTURE,//查询设备升级属性 = @升级前必须调用查询)
    READRSSI,//读取线损值
    ISRKPLATFORM,    //判断平台
    GETSERVERBTIMGVERSION,
    GETSERVERPATCHVERSION,
    BEGINUPDATEFIRMWARE,
    UPDATEFIRMWARE,
    OPENREMIND
} HeytzMethods;
#endif /* HeytzOperation_h */
