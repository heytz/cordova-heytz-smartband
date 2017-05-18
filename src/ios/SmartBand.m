/********* cordova-heytz-smartband.m Cordova Plugin Implementation *******/
#import "SmartBand.h"

@implementation SmartBand
//初始化
NSString *INIT = @"init";
//扫描
NSString *SCAN = @"scan";
//停止扫描
NSString *STOP = @"stop";
//是否支持BLE4.0
NSString *ISSUPPORTED = @"isSupported";
//判断蓝牙是否打开
NSString *ISENABLED = @"isEnabled";
//连接
NSString *CONNECT = @"connect";
//断开设备
NSString *DISCONNECT = @"disConnect";
//解绑服务
NSString *UNBINDSERVICE = @"unBindService";
//写入
NSString *WRITE = @"write";
//同步时间
NSString *SYNCBLETIME = @"syncBLETime";
//请求蓝牙版本信息
NSString *SENDTOREADBLEVERSION = @"sendToReadBLEVersion";
//请求蓝牙电池电量指令
NSString *SENDTOREADBLEBATTERY = @"sendToReadBLEBattery";
//同步运动数据
NSString *SYNCRUNDATA = @"syncRunData";
//同步睡眠数据
NSString *SYNCSLEEPDATA = @"syncSleepData";
//设置 BEL 端步长;体重;灭屏时间;目标步数;抬手亮屏开关 true 为开，false 为关;最高心率 醒，true 为开，false 为关;最后一个参数为最高心率 醒 的值。 醒:修改身高体重后，需要同步一次计步数据，应用上的距离和卡 路里才会按照新修改的身高体重进行计算并更新。
NSString *SENDSTEPLENANDWEIGHTTOBLE = @"sendStepLenAndWeightToBLE";
//同步计步数据= @连上设备后，请同步一次步数= @实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
NSString *SYNALLSTEPDATA = @"syncAllStepData";
//新一天初始化计步数据库
NSString *UPDATESTEPSQL = @"updateStepSQL";
//查询一天的总步数
NSString *QUERYSTEPDATE = @"queryStepDate";
//查询一天的步数、距离、卡路里
NSString *QUERYSTEPDINFO = @"queryStepInfo";
//查询某一天各小时步数
NSString *QUERYONEHOURSTEPSQL = @"queryOneHourStepSQL";
//同步睡眠数据= @同步完成前，请不要进行其他任何的通信工作)
NSString *SYNCALLSLEEPDATA = @"syncAllSleepData";
//查询一天的睡眠总时间
NSString *QUERYSLEEPDATE = @"querySleepDate";
//查询一天的睡眠详情
NSString *QUERYSLEEPINFO = @"querySleepInfo";
//打开摇摇功能= @之后发现设备被摇一摇时，会在 ICallback 中返回状态， ICallbackStatus.DISCOVERY_DEVICE_SHAKE)，常用于摇摇拍照等功能的实 现。
NSString *SHAKEMODE = @"shakeMode";
//关闭摇摇功能
NSString *CLOSESHAKEMODE = @"closeShakeMode";
//清除设备所有数据，即设备恢复出厂设置
NSString *DELETEDEVICEALLDATA = @"deleteDevicesAllData";
//发送久坐 醒功能开启/关闭指令以及 醒周期
NSString *SENDSEDENTARYREMINDCOMMAND = @"sendSedentaryRemindCommand";
//发送设置闹钟指令
NSString *SENDTOSETALARMCOMMAND = @"sendToSetAlarmCommand";
//查找手环
NSString *FINDBAND = @"findBand";
//同步数据
NSString *SYNCALLRATEDATA = @"syncAllRateData";
//查询设备升级属性 = @升级前必须调用查询)
NSString *QUERYDEVICEFEARTURE = @"queryDeviceFearture";
//读取线损值
NSString *READRSSI = @"readRssi";
//判断平台
NSString *ISRKPLATFORM = @"isRKPlatform";
NSString *GETSERVERBTIMGVERSION = @"getServerBtImgVersion";
NSString *GETSERVERPATCHVERSION = @"getServerPatchVersion";

- (void)setCallBackId:(NSString *)method callbackId:(NSString *)callbackId {
    _cordovaCallbackDic[method] = callbackId;
}

- (NSString *)getCallBackId:(NSString *)method {
    return _cordovaCallbackDic[method];
}

#ifdef __CORDOVA_4_0_0

- (void)pluginInitialize {
    NSLog(@"### pluginInitialize ");
    [self initPlugin];
}

#else

- (CDVPlugin*)initWithWebView:(UIWebView*)theWebView{
    NSLog(@"### initWithWebView ");
    if (self=[super initWithWebView:theWebView]) {
    }
    [self initPlugin];
    return self;
}

#endif

- (void)initPlugin {
    if ([UTESmartBandClient sharedInstance].delegate) {
        [UTESmartBandClient sharedInstance].delegate = self;
    }
    [[UTESmartBandClient sharedInstance] debugUTELog];
    nsArray = [NSMutableArray array];
    _cordovaCallbackDic = [NSMutableDictionary dictionary];

}

- (void)init:(CDVInvokedUrlCommand *)command {
    [[UTESmartBandClient sharedInstance] initUTESmartBandClient];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)scan:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SCAN callbackId:command.callbackId];
    [nsArray removeAllObjects];
    int time = [command.arguments objectAtIndex:0];
    [[UTESmartBandClient sharedInstance] startScanDevices];
};


- (void)stop:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:STOP callbackId:command.callbackId];
    [[UTESmartBandClient sharedInstance] stopScanDevices];
}

- (void)connect:(CDVInvokedUrlCommand *)command {
    BOOL isExist = NO;
    [self setCallBackId:CONNECT callbackId:command.callbackId];
    NSString *address = [command.arguments objectAtIndex:0];
    for (UTEModelDevices *devices in nsArray) {
        if ([[devices address] isEqual:address]) {
            isExist = YES;
            [[UTESmartBandClient sharedInstance] connectUTEModelDevices:devices];
        }
    }
    if (!isExist) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"device don't exist"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command];
    }
}

- (void)sendSedentaryRemindCommand:(CDVInvokedUrlCommand *)command {
}

- (void)shakeMode:(CDVInvokedUrlCommand *)command {
}

- (void)sendToSetAlarmCommand:(CDVInvokedUrlCommand *)command {
}

- (void)sendStepLenAndWeightToBLE:(CDVInvokedUrlCommand *)command {
}

- (void)syncAllStepData:(CDVInvokedUrlCommand *)command {
}

- (void)syncAllSleepData:(CDVInvokedUrlCommand *)command {
}

- (void)findBand:(CDVInvokedUrlCommand *)command {
}

- (void)deleteDevicesAllData:(CDVInvokedUrlCommand *)command {
}

- (void)sendToReadBLEBattery:(CDVInvokedUrlCommand *)command {
}

- (void)sendToReadBLEVersion:(CDVInvokedUrlCommand *)command {
}

- (void)syncBLETime:(CDVInvokedUrlCommand *)command {
}

- (void)isEnabled:(CDVInvokedUrlCommand *)command {
}

- (void)querySleepDate:(CDVInvokedUrlCommand *)command {
}

- (void)updateStepSQL:(CDVInvokedUrlCommand *)command {
}

- (void)queryStepDate:(CDVInvokedUrlCommand *)command {
}

- (void)queryStepInfo:(CDVInvokedUrlCommand *)command {
}

- (void)queryOneHourStepSQL:(CDVInvokedUrlCommand *)command {
}

- (void)readRssi:(CDVInvokedUrlCommand *)command {
}

- (void)disConnect:(CDVInvokedUrlCommand *)command {
}

- (void)querySleepInfo:(CDVInvokedUrlCommand *)command {
}

- (void)isSupported:(CDVInvokedUrlCommand *)command {
}

- (void)isRKPlatform:(CDVInvokedUrlCommand *)command {
}

- (void)getServerBtImgVersion:(CDVInvokedUrlCommand *)command {
}

- (void)getServerPatchVersion:(CDVInvokedUrlCommand *)command {
}

- (void)queryDeviceFearture:(CDVInvokedUrlCommand *)command {
}

//*******************************回调*************************************************

/**
 *  @discussion 每找到一个设备，就会调用一次
 *
 *  @param modelDevices 设备属性模型
 */
- (void)uteManagerDiscoverDevices:(UTEModelDevices *)modelDevices {
    for (UTEModelDevices *devices in nsArray) {
        if ([[devices address] isEqual:[modelDevices address]]) {
            [nsArray removeObject:modelDevices];
        }
    }
    [nsArray arrayByAddingObject:modelDevices];
    if ([_cordovaCallbackDic valueForKey:@"scan"]) {
        CDVPluginResult *pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:nsArray];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:[_cordovaCallbackDic valueForKey:@"scan"]];
    }
}

/**
 *  @discussion 时时监听了已连接设备状态
 *
 *  @param devicesState 设备状态
 *  @param error        错误码
 */
- (void)uteManagerDevicesSate:(UTEDevicesSate)devicesState error:(NSError *)error userInfo:(NSDictionary *)info {
    NSLog(@"state:%ld,error:%ld", (long) devicesState, (long) [error code]);
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.openHeytzICallback(%ld);", (long) devicesState];
    [self.commandDelegate evalJs:jsStr];
}

/**
 *  @discussion 时时监听了蓝牙连接状态
 *
 *  @param bluetoothState 蓝牙状态
 */
- (void)uteManagerBluetoothState:(UTEBluetoothSate)bluetoothState {
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.openHeytzICallback(%ld);", (long) bluetoothState];
    [self.commandDelegate evalJs:jsStr];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"device don't exist"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:[self getCallBackId:CONNECT]];
}

/**
 *  @discussion 当第一次打开来电 QQ 微信 sms提醒功能时，系统会弹出对话框要求绑定（系统绑定）
 *   1.如设备已经绑定，系统是不会弹出对话框，且SDK无返回值
 *   2.如设备未绑定过，用户点击绑定（则设备与系统绑定），则返回YES：来电 QQ 微信 sms相对应的提醒有效；否则返回NO，全部无效，且硬件设备会主动断开，请开发者主动调用连接。
 *
 *  @param isAble 设备来电 QQ 微信 sms提醒是否有效
 */
- (void)uteManagerExtraIsAble:(BOOL)isAble {

}

/**
 *  @discussion 实时监听了设备步数变化 会频繁被调用
 *
 *  @param UTEModelRunData 今天总步数
 */
- (void)uteManagerReceiveTodaySteps:(UTEModelRunData *)runData {

}

/**
 *  @discussion 实时监听了设备睡眠记录变化
 *              如有新的睡眠记录，请先同步睡眠记录（因为要过滤是否在真正的睡觉），再查询历史睡眠记录
 *              最好早上同步睡眠数据，因为这时候睡眠数据才是完整的，而且同步睡眠需要时间比较久
 *
 *  @param isNewSleep 是否有新的睡眠数据
 */
- (void)uteManagerReceiveTodaySleeps:(BOOL)isNewSleep {

}

/**
 *  @discussion 同步设备数据进度
 *
 *  @param process 进度(0到100)
 */
- (void)uteManagerSyncProcess:(NSInteger)process {

}

/**
 *  @discussion 升级设备进度
 *
 *  @param process 进度(0到100)
 */
- (void)uteManagerUpdateProcess:(NSInteger)process {

}

/**
 *  @discussion 当设备UTEOptionOpenCameraMode拍照模式，每摇晃3次就回调一次
 *   退出拍照模式一定调用UTEOptionCloseCameraMode
 */
- (void)uteManagerTakePicture {

}

/**
 *  @discussion SDK对固件发送命令，如固件接收到值，将发送返回值给SDK，如SDK接收到值将回调；否则无
 */
- (void)uteManageUTEOptionCallBack:(UTECallBack)callback {

}
@end
