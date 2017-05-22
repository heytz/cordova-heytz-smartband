/********* cordova-heytz-smartband.m Cordova Plugin Implementation *******/
#import "SmartBand.h"

@interface SmartBand ()

- (UTEModelDevices *)findDevice:(NSString *)identifier;
@end

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
//同步所有数据
NSString *SYNCALLDATA = @"syncAllData";
//查询设备升级属性 = @升级前必须调用查询)
NSString *QUERYDEVICEFEARTURE = @"queryDeviceFearture";
//读取线损值
NSString *READRSSI = @"readRssi";
//判断平台
NSString *ISRKPLATFORM = @"isRKPlatform";
NSString *GETSERVERBTIMGVERSION = @"getServerBtImgVersion";
NSString *GETSERVERPATCHVERSION = @"getServerPatchVersion";
NSString *BEGINUPDATEFIRMWARE = @"beginUpdateFirmware";
NSString *UPDATEFIRMWARE = @"updateFirmware";
NSString *OPENREMIND = @"openRemind";

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
    self.smartBandMgr = [UTESmartBandClient sharedInstance];
    //1. 实例化
    self.smartBandMgr = [UTESmartBandClient sharedInstance];
    //2. 初始化
    [self.smartBandMgr initUTESmartBandClient];
    //3. 设置代理
    self.smartBandMgr.delegate = self;
    //4. 打开log
    self.smartBandMgr.debugUTELog = YES;
    //5. 设置过滤设备名称
    //    self.smartBandMgr.filterName = @"MH08";
    //5.1 设置过滤设备信号强度范围 默认为-70
    //    self.smartBandMgr.filerRSSI = -99;
    //6. 重复扫描设备(这样设备信号值才会实时变化)
    self.smartBandMgr.isScanRepeat = YES;
    self.isMustUpdate = NO;

    NSLog(@"sdk vsersion =%@", self.smartBandMgr.sdkVersion);
    if (!_nsArray) {
        _nsArray = [NSMutableArray array];
    }
    if (!_cordovaCallbackDic) {
        _cordovaCallbackDic = [NSMutableDictionary dictionary];
    }
    if (!_tempDataAll) {
        _tempDataAll = [NSMutableDictionary dictionary];
    }
}

/**
 * 初始化
 * @param command
 */
- (void)init:(CDVInvokedUrlCommand *)command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self sendPluginResult:pluginResult callbackId:command.callbackId];
}

/**
 * 扫描
 * @param command
 */
- (void)scan:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SCAN callbackId:command.callbackId];
    if (scanNsTimer) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"The last event did not stop!"];
        [self sendPluginResult:pluginResult callbackId:command.callbackId];
    } else {
        [_nsArray removeAllObjects];
        [[self smartBandMgr] startScanDevices];
        NSString *timeStr = [command.arguments objectAtIndex:0];
        double time = 10;
        if (timeStr == nil || timeStr == NULL || [timeStr isKindOfClass:[NSNull class]]) {
        } else {
            time = [timeStr doubleValue];
        }
        scanNsTimer = [NSTimer scheduledTimerWithTimeInterval:time
                                                       target:self
                                                     selector:@selector(stopScanTimer:)
                                                     userInfo:[command.callbackId copy]
                                                      repeats:NO];
    }
};

/**
 * 停止扫描
 * @param command
 */
- (void)stop:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:STOP callbackId:command.callbackId];
    [[self smartBandMgr] stopScanDevices];
    if (scanNsTimer && [scanNsTimer isValid]) {
        [scanNsTimer invalidate];
        scanNsTimer = Nil;
    }
}

/**
 * 扫描定时器
 * @param timer
 */
- (void)stopScanTimer:(NSTimer *)timer {
    NSLog(@"stopScanTimer");
    [[self smartBandMgr] stopScanDevices];
    [scanNsTimer invalidate];
    scanNsTimer = Nil;
}

/**
 * 连接设备
 * @param command
 */
- (void)connect:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:CONNECT callbackId:command.callbackId];
    NSString *identifier = [command.arguments objectAtIndex:0];
    UTEModelDevices *devices = [self findDevice:identifier];
    if (devices != nil) {
        [[UTESmartBandClient sharedInstance] connectUTEModelDevices:devices];
    } else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"device don't exist"];
        [self sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

/**
 * 断开设备
 * 蓝牙未打开、设备未连接 是可以执行；正在同步中、正在测试心率中、转化设备特性、Apdu交互中不执行
 * @param command [identifier]
 */
- (void)disConnect:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:DISCONNECT callbackId:command.callbackId];
    NSString *identifier = [command.arguments objectAtIndex:0];
    UTEModelDevices *devices = [self findDevice:identifier];
    if (devices != nil) {
        BOOL state = [self.smartBandMgr disConnectUTEModelDevices:devices];
        if (!state) {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            [self sendPluginResult:pluginResult callbackId:command.callbackId];
        }
    } else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"device don't exist"];
        [self sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}


/**
 * 久坐提醒
 * @param command
 */
- (void)sendSedentaryRemindCommand:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SENDSEDENTARYREMINDCOMMAND callbackId:command.callbackId];
    Boolean state = (Boolean) command.arguments[0];
    NSInteger remindTime = [command.arguments[1] integerValue];
    if (state) {
//        remindTime: 久坐多长时间就设备震动提醒(震动 2 秒,静止 2 秒 反复 3 次)
        [self.smartBandMgr setUTESitRemindOpenTime:remindTime];
        //设置设备特征
        [self.smartBandMgr setUTEOption:UTECallBackOpenUnitSitRemind];
    } else {
        //todo 究竟使用哪种？
        [self.smartBandMgr setUTESitRemindClose];
//        [self.smartBandMgr setUTEOption:UTECallBackCloseSitRemind];
    }
}

/**
 * 摇一摇
 * @param command
 */
- (void)shakeMode:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SHAKEMODE callbackId:command.callbackId];
    Boolean state = (Boolean) command.arguments[0];
    if (state) {
        [self.smartBandMgr setUTEOption:UTEOptionOpenCameraMode];
    } else {
        [self.smartBandMgr setUTEOption:UTEOptionCloseCameraMode];
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self sendPluginResult:pluginResult callbackId:SHAKEMODE];
    }

}

/**
 * 智能闹钟
 * @param command
 */
- (void)sendToSetAlarmCommand:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SENDTOSETALARMCOMMAND callbackId:command.callbackId];
    int timerNum = [command.arguments[0] intValue];
    NSString *week = command.arguments[1];
    NSString *hour = command.arguments[2];
    NSString *min = command.arguments[3];
    Boolean state = (Boolean) [command.arguments objectAtIndex:4];
    int shakePeriod = [[command.arguments objectAtIndex:5] intValue];
    UTEModelAlarm *model1 = [[UTEModelAlarm alloc] init];
    model1.time = [NSString stringWithFormat:@"%@:%@", hour, min];
    if ([week isEqualToString:@"everyday"]) {
        model1.week = UTEAlarmWeekMonday | UTEAlarmWeekTuesday | UTEAlarmWeekWednesday
                | UTEAlarmWeekThursday | UTEAlarmWeekFriday | UTEAlarmWeekSaturday | UTEAlarmWeekSunday;
    } else {
        NSArray *weekArr = [week componentsSeparatedByString:@","];
        for (int i = 0; i < weekArr.count; ++i) {
            if ([weekArr[i] isEqualToString:@"sunday"]) {
                model1.week |= UTEAlarmWeekSunday;
            } else if ([weekArr[i] isEqualToString:@"monday"]) {
                model1.week |= UTEAlarmWeekMonday;
            } else if ([weekArr[i] isEqualToString:@"tuesday"]) {
                model1.week |= UTEAlarmWeekTuesday;
            } else if ([weekArr[i] isEqualToString:@"wednesday"]) {
                model1.week |= UTEAlarmWeekWednesday;
            } else if ([weekArr[i] isEqualToString:@"thursday"]) {
                model1.week |= UTEAlarmWeekThursday;
            } else if ([weekArr[i] isEqualToString:@"friday"]) {
                model1.week |= UTEAlarmWeekFriday;
            } else if ([weekArr[i] isEqualToString:@"saturday"]) {
                model1.week |= UTEAlarmWeekSaturday;
            }
        }
    }
    model1.enable = state;
    model1.num = (UTEAlarmNum) timerNum;
    [self.smartBandMgr setUTEAlarmArray:@[model1] vibrate:shakePeriod];

}

/**
 * 设置身高单位
 * @param command
 */
- (void)setHeighUnit:(CDVInvokedUrlCommand *)command {

}

/**
 * 设置体重单位
 * @param command
 */
- (void)setWeightUnit:(CDVInvokedUrlCommand *)command {

}

/**
 * 设置身高体重
 * @param command
 */
- (void)sendStepLenAndWeightToBLE:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SHAKEMODE callbackId:command.callbackId];
    float heigh = [[command.arguments objectAtIndex:0] floatValue];
    NSInteger weight = [command.arguments objectAtIndex:1];
    NSInteger light = [command.arguments objectAtIndex:2];
    NSInteger sportTarget = [command.arguments objectAtIndex:3];
    Boolean handLight = (Boolean) command.arguments[4];
    NSInteger maxHeart = command.arguments[5];
//    *  @param heigh  身高 UTEOptionUnitMeter 单位cm  范围格式 <91,240>
//    *                身高 UTEOptionUnitInch 单位inch 范围格式 <3.00,7.11> 3尺00寸 ~ 7尺11寸 (小数点为11进制)
//
//            *  @param weight 体重 UTEOptionUnitMeter 单位kg 范围格式 <20,150>
//    *                体重 UTEOptionUnitInch 单位lb 范围格式 <44,333>
//    *
//            *  @param sec     亮屏时间(秒) 范围<5,60>
//            *
//                    *  @param sportTarget 有的设备支持显示一天的步数进度；如手环不支持，请填非0 值
//    *
//            *  @param handlight   抬手亮屏的开关 请查看isHasHandLight来判断是否支持此功能
//    *
//            *  @param maxHeart    超过最大心率值警报 请查看isHasMaxHeartAlert来判断是否支持此功能，关闭则填255
    [self.smartBandMgr setUTEInfoHeigh:heigh weight:weight light:light sportTarget:sportTarget
                             handlight:handLight maxHeart:maxHeart];
}

/**
 * 同步所有数据
 * @param command
 */
- (void)syncAllData:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SYNCALLDATA callbackId:command.callbackId];
    if ([self.smartBandMgr setUTEOption:UTEOptionSyncAllData]) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self sendPluginResult:pluginResult callbackId:command.callbackId];
    } else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

/**
 * 同步计步数据
 * @param command
 */
- (void)syncAllStepData:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SYNCALLRATEDATA callbackId:command.callbackId];
    if ([self.smartBandMgr setUTEOption:UTEOptionSyncAllStepsData]) {

    } else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self sendPluginResult:pluginResult callbackId:SYNCALLRATEDATA];

    }
}

/**
 * 同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
 * @param command
 */
- (void)syncAllSleepData:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SYNCALLSLEEPDATA callbackId:command.callbackId];
    [self.smartBandMgr setUTEOption:UTEOptionSyncAllSleepData];
}

/**
 * 查找手环
 * @param command
 */
- (void)findBand:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:FINDBAND callbackId:command.callbackId];
    [self.smartBandMgr setUTEOption:UTEOptionFindBand];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self sendPluginResult:pluginResult callbackId:FINDBAND];
}

/**
 * 清空所有数据
 * @param command
 */
- (void)deleteDevicesAllData:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:DELETEDEVICEALLDATA callbackId:command.callbackId];
    [self.smartBandMgr setUTEOption:UTEOptionDeleteDevicesAllData];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self sendPluginResult:pluginResult callbackId:DELETEDEVICEALLDATA];
}

/**
 * 读取电量
 * @param command
 */
- (void)sendToReadBLEBattery:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SENDTOREADBLEBATTERY callbackId:command.callbackId];
    [self.smartBandMgr setUTEOption:UTEOptionReadDevicesBattery];
    int battery = [[self.smartBandMgr connectedDevicesModel] battery];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:battery];
    [self sendPluginResult:pluginResult callbackId:SENDTOREADBLEBATTERY];
}

/**
 * 读取版本
 * @param command
 */
- (void)sendToReadBLEVersion:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SENDTOREADBLEVERSION callbackId:command.callbackId];
    NSString *version = [[self.smartBandMgr connectedDevicesModel] version];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:version];
    [self sendPluginResult:pluginResult callbackId:SENDTOREADBLEVERSION];
}

/**
 * 同步时间
 * @param command
 */
- (void)syncBLETime:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:SYNCBLETIME callbackId:command.callbackId];
    if ([self.smartBandMgr checkUTEDevicesStateIsEnable]) {
        [self.smartBandMgr setUTEOption:UTEOptionSyncTime];
    } else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self sendPluginResult:pluginResult callbackId:SYNCBLETIME];
    }
}

- (void)isEnabled:(CDVInvokedUrlCommand *)command {
}

//检查是否可以发送 UTEOption 等等对设备的设置
//设备在未打开手机蓝牙、未连接设备、正在同步中、正在测试心率/血压中、转化设备特性，返回false，设置是无效的，即设备不处理。
- (void)checkUTEDevicesStateIsEnable:(CDVInvokedUrlCommand *)command {
    BOOL enabled = [[self smartBandMgr] checkUTEDevicesStateIsEnable];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:enabled];
    [self sendPluginResult:pluginResult callbackId:command.callbackId];
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


- (void)querySleepInfo:(CDVInvokedUrlCommand *)command {
}

- (void)isSupported:(CDVInvokedUrlCommand *)command {
}

- (void)beginUpdateFirmware:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:BEGINUPDATEFIRMWARE callbackId:command.callbackId];
    [self.smartBandMgr beginUpdateFirmware];
}

/**
 * 开始升级
 * @param command
 */
- (void)updateFirmware:(CDVInvokedUrlCommand *)command {
    self.isMustUpdate = NO;
    [self setCallBackId:UPDATEFIRMWARE callbackId:command.callbackId];
    [self.smartBandMgr changeDeviveFeature:^(BOOL isSuccess, BOOL isMustUpdate) {
        //1.先检查这个属性，必须强制升级固件，因为之前升级固件把固件烧坏了
        if (isMustUpdate) {
            //开始自动后台检查环境，然后强制升级
            [self.smartBandMgr checkUTEFirmwareVersion];
            self.isMustUpdate = YES;
            NSLog(@"***必须强制升级固件，因为之前升级固件把固件烧坏了，造成一些功能无法使用");
            return;
        }//2.然后检查这个属性
        if (isSuccess) {
            NSLog(@"***打开升级功能成功，开始升级");
            [self.smartBandMgr beginUpdateFirmware];
        } else {
            NSLog(@"***是打开了升级功能，但是连接失败，超时了，可重新调用checkUTEFirmwareVersion，然后升级");
        }
    }];
}

/**
 * 设备是否为RK平台手环(可事先问相关人员,是否有这设备)，设备断开情况下为false
 * @param command
 */
- (void)isRKPlatform:(CDVInvokedUrlCommand *)command {
    BOOL isRK = [[self smartBandMgr] isRKDevices];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:isRK];
    [self sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getServerBtImgVersion:(CDVInvokedUrlCommand *)command {
    [self setCallBackId:GETSERVERBTIMGVERSION callbackId:command.callbackId];
    [[self smartBandMgr] checkUTEFirmwareVersion];
}


- (void)getServerPatchVersion:(CDVInvokedUrlCommand *)command {
}

- (void)queryDeviceFearture:(CDVInvokedUrlCommand *)command {
}

- (void)checkUTEFirmwareVersion:(CDVInvokedUrlCommand *)command {
//    [self.smartBandMgr checkUTEFirmwareVersion];
}

- (void)openRemind:(CDVInvokedUrlCommand *)command {
    BOOL *state = [command.arguments[0] pointerValue];
    NSString *type = command.arguments[0];
    if (state) {
        if (type == @"incall") {
            [self.smartBandMgr setUTEOption:UTEOptionOpenRemindIncall];
        } else if (type == @"qq") {
            [self.smartBandMgr setUTEOption:UTEOptionOpenRemindQQ];
        } else if (type == @"weixin") {
            [self.smartBandMgr setUTEOption:UTEOptionOpenRemindWeixin];
        } else if (type == @"sms") {
            [self.smartBandMgr setUTEOption:UTEOptionOpenRemindSms];
        } else if (type == @"more") {
            [self.smartBandMgr setUTEOption:UTEOptionOpenRemindMore];
        } else {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                                                messageAsBool:"This type does not exist!"];
            [self sendPluginResult:pluginResult callbackId:command.callbackId];
        }
    } else {
        if (type == @"incall") {
            [self.smartBandMgr setUTEOption:UTEOptionCloseRemindIncall];
        } else if (type == @"qq") {
            [self.smartBandMgr setUTEOption:UTEOptionCloseRemindQQ];
        } else if (type == @"weixin") {
            [self.smartBandMgr setUTEOption:UTEOptionCloseRemindWeixin];
        } else if (type == @"sms") {
            [self.smartBandMgr setUTEOption:UTEOptionCloseRemindSms];
        } else if (type == @"more") {
            [self.smartBandMgr setUTEOption:UTEOptionCloseRemindMore];
        } else {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                                                messageAsBool:"This type does not exist!"];
            [self sendPluginResult:pluginResult callbackId:command.callbackId];
        }
    }
}

//*******************************回调*************************************************

/**
 *  @discussion 每找到一个设备，就会调用一次
 *
 *  @param modelDevices 设备属性模型
 */
- (void)uteManagerDiscoverDevices:(UTEModelDevices *)modelDevices {
    BOOL sameDevices = NO;
    for (UTEModelDevices *model in self.nsArray) {
        if ([model.identifier isEqualToString:modelDevices.identifier]) {
            model.rssi = modelDevices.rssi;
            model.name = modelDevices.name;
            sameDevices = YES;
            break;
        }
    }

    if (!sameDevices) {
        NSLog(@"***扫描到的设备name=%@ id=%@", modelDevices.name, modelDevices.identifier);
        [_nsArray addObject:modelDevices];
    }
    if ([_cordovaCallbackDic valueForKey:SCAN]) {
        NSMutableArray *jsonArray = [[NSMutableArray alloc] init];
        for (UTEModelDevices *device in _nsArray) {
            [jsonArray addObject:[self deviceToDic:device]];
        }
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:jsonArray];
        [pluginResult setKeepCallbackAsBool:true];
        [self sendPluginResult:pluginResult callbackId:SCAN];
    }
}

/**
 *  @discussion 时时监听了已连接设备状态
 *
 *  @param devicesState 设备状态
 *  @param error        错误码
 */
- (void)uteManagerDevicesSate:(UTEDevicesSate)devicesState error:(NSError *)error userInfo:(NSDictionary *)info {
    if (error) {
        NSLog(@"***错误码=%ld,msg=%@", (long) error.code, error.domain);
    }
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    NSLog(@"state:%ld,error:%ld", (long) devicesState, (long) [error code]);
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.openHeytzICallback(%ld);",
                                                 (long) devicesState];
    if (info != nil) {
        jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.openHeytzICallback(%ld,%@);",
                                           (long) devicesState,
                                           [[NSString alloc] initWithData:[self toJSONData:info] encoding:NSUTF8StringEncoding]];
    }
    [self.commandDelegate evalJs:jsStr];
    switch (devicesState) {
        case UTEDevicesSateConnected: {
            //每次连上应该设置一下配置，保证App和设备的信息统一
            [self sendPluginResult:pluginResult callbackId:CONNECT];
            break;
        }
        case UTEDevicesSateDisconnected: {
            if (error) {
                //相应处理
                NSLog(@"***设备异常断开=%@", error);
            } else {
                NSLog(@"***设备正常断开connectedDevicesModel=%@", self.smartBandMgr.connectedDevicesModel);
                [self sendPluginResult:pluginResult callbackId:DISCONNECT];
            }
            break;
        }
        case UTEDevicesSateSyncBegin: {
            //相应处理
            NSLog(@"***设备在同步数据开始***");
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{state:'begin'}"];
            [pluginResult setKeepCallbackAsBool:true];
            [self sendPluginResult:pluginResult callbackId:SYNCALLRATEDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCALLSLEEPDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCSLEEPDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCALLDATA];
            break;
        }
        case UTEDevicesSateSyncSuccess: {
            NSLog(@"***设备在同步数据结束***");
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{state:'success'}"];
            [pluginResult setKeepCallbackAsBool:true];
            [self sendPluginResult:pluginResult callbackId:SYNCALLRATEDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCALLSLEEPDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCSLEEPDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCALLDATA];
            [self syncSucess:info];
            break;
        }
        case UTEDevicesSateSyncError: {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:error.domain];
            [pluginResult setKeepCallbackAsBool:true];
            [self sendPluginResult:pluginResult callbackId:SYNCALLRATEDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCALLSLEEPDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCSLEEPDATA];
            [self sendPluginResult:pluginResult callbackId:SYNCALLDATA];
            //相应处理
            break;
        }
        case UTEDevicesSateCheckFirmwareError: {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:error.domain];
            [self sendPluginResult:pluginResult callbackId:GETSERVERBTIMGVERSION];
            //相应处理
            break;
        }
        case UTEDevicesSateUpdateHaveNewVersion: {
            if (self.isMustUpdate) {
                [self.smartBandMgr beginUpdateFirmware];
            }
            //相应处理 todo 不知道如何去取版本号
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
            [self sendPluginResult:pluginResult callbackId:GETSERVERBTIMGVERSION];
            break;
        }
        case UTEDevicesSateUpdateNoNewVersion: {
            //相应处理
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"no new version"];
            [self sendPluginResult:pluginResult callbackId:GETSERVERBTIMGVERSION];
            break;
        }
        case UTEDevicesSateUpdateBegin: {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{state:'begin'}"];
            [pluginResult setKeepCallbackAsBool:true];
            [self sendPluginResult:pluginResult callbackId:UPDATEFIRMWARE];

            //相应处理
            break;
        }
        case UTEDevicesSateUpdateSuccess: {
            //相应处理
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{state:'success'}"];
            [self sendPluginResult:pluginResult callbackId:UPDATEFIRMWARE];
            [self sendPluginResult:pluginResult callbackId:BEGINUPDATEFIRMWARE];
            break;
        }
        case UTEDevicesSateUpdateError: {
            //相应处理
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:error.domain];
            [self sendPluginResult:pluginResult callbackId:UPDATEFIRMWARE];
            [self sendPluginResult:pluginResult callbackId:BEGINUPDATEFIRMWARE];
            break;
        }
        case UTEDevicesSateHeartDetectingProcess: {
            //接收到心率值
            break;
        }
        case UTEDevicesSateBloodDetectingProcess: {
            //接收到值
            break;
        }
        case UTEDevicesSateHeartDetectingStart: {
            //相应处理
            NSLog(@"***UTEOptionHeartDetectingStart 心率测试开始了");
            break;
        }
        case UTEDevicesSateHeartDetectingStop: {
            //相应处理
            NSLog(@"***UTEOptionHeartDetectingStop 心率测试停止了");
            break;
        }
        case UTEDevicesSateHeartDetectingError: {
            //相应处理
            NSLog(@"***心率测试过程中，设备断开了");
            break;
        }
        case UTEDevicesSateBloodDetectingStart: {
            //相应处理
            NSLog(@"***blood测试开始");
            break;
        }
        case UTEDevicesSateBloodDetectingStop: {
            //相应处理
            NSLog(@"***blood测试停止");
            break;
        }
        case UTEDevicesSateBloodDetectingError: {
            //相应处理
            NSLog(@"***blood测试过程中，设备断开了");
            break;
        }
        case UTEDevicesSatePasswordState: {
        }
        default: {
            break;
        }
    }
}

/**
 *  @discussion 时时监听了蓝牙连接状态
 * 手机蓝牙状态返回值，通过设置代理后，实现 uteManagerBluetoothState:方法。每当手 机蓝牙状态改变时，都会回调一次此方法。
 *  @param bluetoothState 蓝牙状态
 *  @constant UTEBluetoothSateOpen       手机蓝牙打开
 *  @constant UTEBluetoothSateClose      手机蓝牙关闭
 *  @constant UTEBluetoothSateResetting  手机蓝牙重启
 */
- (void)uteManagerBluetoothState:(UTEBluetoothSate)bluetoothState {
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.onServiceStatuslt(%ld);", (long) bluetoothState];
    [self.commandDelegate evalJs:jsStr];
    if (bluetoothState == UTEBluetoothSateClose) {//手机蓝牙关闭
//        if (self.alertView) return;
//        dispatch_async(dispatch_get_main_queue(), ^{
//            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示" message:@"请打开手机蓝牙" delegate:nil cancelButtonTitle:@"好" otherButtonTitles:nil, nil];
//            [alert show];
//            self.alertView = alert;
//        });
    } else if (bluetoothState == UTEBluetoothSateOpen) {//手机蓝牙打开
//        [self.alertView dismissWithClickedButtonIndex:0 animated:YES];
//        self.alertView = nil;

    } else if (bluetoothState == UTEBluetoothSateResetting) {//手机蓝牙重启

    }
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
    NSObject *str = @{@"time": runData.time,
//                      @"calories": runData.calories,
            @"hourSteps": [NSNumber numberWithInteger:runData.hourSteps], @"totalSteps": [NSNumber numberWithInteger:runData.totalSteps],
//            @"distances": runData.distances,
//                      @"hourCalories": runData.hourCalories,
//            @"hourDistances": runData.hourCalories
    };
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.openOnStepChange(%s);", str];
    [self.commandDelegate evalJs:jsStr];
}

/**
 *  @discussion 实时监听了设备睡眠记录变化
 *              如有新的睡眠记录，请先同步睡眠记录（因为要过滤是否在真正的睡觉），再查询历史睡眠记录
 *              最好早上同步睡眠数据，因为这时候睡眠数据才是完整的，而且同步睡眠需要时间比较久
 *
 *  @param isNewSleep 是否有新的睡眠数据
 */
- (void)uteManagerReceiveTodaySleeps:(BOOL)isNewSleep {
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.openOnSleepChange(%s);", isNewSleep ? "true" : "false"];
    [self.commandDelegate evalJs:jsStr];
}

/**
 *  @discussion 同步设备数据进度
 *
 *  @param process 进度(0到100)
 */
- (void)uteManagerSyncProcess:(NSInteger)process {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"{process:%d}", process]];
    [pluginResult setKeepCallbackAsBool:true];
    [self sendPluginResult:pluginResult callbackId:SYNCALLRATEDATA];
    [self sendPluginResult:pluginResult callbackId:SYNCALLSLEEPDATA];
    [self sendPluginResult:pluginResult callbackId:SYNCSLEEPDATA];
    [self sendPluginResult:pluginResult callbackId:SYNCALLDATA];
}

/**
 *  @discussion 升级设备进度
 *
 *  @param process 进度(0到100)
 */
- (void)uteManagerUpdateProcess:(NSInteger)process {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"{process:%d}", process]];
    [pluginResult setKeepCallbackAsBool:true];
    [self sendPluginResult:pluginResult callbackId:UPDATEFIRMWARE];
    [self sendPluginResult:pluginResult callbackId:BEGINUPDATEFIRMWARE];
}

/**
 *  @discussion 当设备UTEOptionOpenCameraMode拍照模式，每摇晃3次就回调一次
 *   退出拍照模式一定调用UTEOptionCloseCameraMode
 */
- (void)uteManagerTakePicture {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [pluginResult setKeepCallbackAsBool:true];
    [self sendPluginResult:pluginResult callbackId:SHAKEMODE];
}

/**
 *  @discussion SDK对固件发送命令，如固件接收到值，将发送返回值给SDK，如SDK接收到值将回调；否则无
 */
- (void)uteManageUTEOptionCallBack:(UTECallBack)callback {
    NSLog(@"***uteManageUTEOptionCallBack*******\ncallback=%ld\n", (long) callback);
    CDVPluginResult *pluginResult = nil;
    switch (callback) {
        case UTECallBackUnit: {
        }
            break;
        case UTECallBackInfoHeightWeight: {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:callback];
            [self sendPluginResult:pluginResult callbackId:SENDSTEPLENANDWEIGHTTOBLE];
        }
            break;
        case UTECallBackSyncTime: {//同步时间
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:callback];
            [self sendPluginResult:pluginResult callbackId:SYNCBLETIME];
        }
            break;
        case UTECallBackAlarm: {//设置闹铃的callback
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:callback];
            [self sendPluginResult:pluginResult callbackId:SENDTOSETALARMCOMMAND];
        }
            break;
        case UTECallBackOpenRemindIncall:
        case UTECallBackOpenRemindQQ:
        case UTECallBackOpenRemindWeixin:
        case UTECallBackOpenRemindSms:
        case UTECallBackOpenRemindMore:
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:YES];
            [self sendPluginResult:pluginResult callbackId:OPENREMIND];
            break;
        case UTECallBackCloseRemindIncall:
        case UTECallBackCloseRemindQQ:
        case UTECallBackCloseRemindWeixin:
        case UTECallBackCloseRemindSms:
        case UTECallBackCloseRemindMore:
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:NO];
            [self sendPluginResult:pluginResult callbackId:OPENREMIND];
            break;
            //久坐提醒开关
        case UTECallBackOpenUnitSitRemind:
        case UTECallBackCloseSitRemind: {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:callback];
            [self sendPluginResult:pluginResult callbackId:SENDSEDENTARYREMINDCOMMAND];
        }
            break;

        case UTECallBackHeartSwitchDynamic: {
        }
            break;
        case UTECallBackHeartSwitchStatic: {
        }
            break;

        case UTECallBackDevicesVersion: {
        }
            break;

        case UTECallBackDeviceHorizontal: {
        }
            break;
        case UTECallBackDeviceVertical: {
        }
            break;

        case UTECallBackDeviceSilence: {
        }
            break;

        case UTECallBackDeviceWeather: {
        }
            break;
        case UTECallBackDeviceBattery: {//读取电量
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:callback];
            [self sendPluginResult:pluginResult callbackId:SENDTOREADBLEBATTERY];
        }
            break;
        case UTECallBackSwitchHandAndDisplay: {
        }
            break;
        case UTECallBackWeatherSevenDay: {
        }
            break;
        case UTECallBackIbeaconOption: {
        }
            break;

        default: {

        }
    }
    NSString *jsStr = [NSString stringWithFormat:@"cordova.plugins.SmartBand.uteManageUTEOptionCallBack(%ld);", (long) callback];
    [self.commandDelegate evalJs:jsStr];
}


- (void)syncSucess:(NSDictionary *)info {
    _tempDataAll = info;
    NSLog(@"同步完成");
    NSArray *arrayRun = info[kUTEQueryRunData];//步数数据
    NSArray *arraySleep = info[kUTEQuerySleepData];//睡眠数据
    NSArray *arrayHRM = info[kUTEQueryHRMData];//心率数据
    NSArray *arrayBlood = info[kUTEQueryBloodData];//血压数据
//    NSMutableDictionary *d = [NSMutableDictionary dictionary];
    for (UTEModelRunData *model in arrayRun) {
        NSLog(@"***time = %@, hourStep = %ld,Total step = %ld , distance = %f ,calorie = %f", model.time, (long) model.hourSteps, (long) model.totalSteps, model.distances, model.calories);
    }
    for (UTEModelSleepData *model in arraySleep) {
        NSLog(@"***start=%@,end=%@,type=%ld", model.startTime, model.endTime, (long) model.sleepType);
    }
    for (UTEModelHRMData *model in arrayHRM) {
    }

    for (UTEModelBloodData *model in arrayBlood) {
    }
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:info];
    [pluginResult setKeepCallbackAsBool:true];
    [self sendPluginResult:pluginResult callbackId:SYNCALLRATEDATA];
    [self sendPluginResult:pluginResult callbackId:SYNCALLSLEEPDATA];
    [self sendPluginResult:pluginResult callbackId:SYNCSLEEPDATA];
    [self sendPluginResult:pluginResult callbackId:SYNCALLDATA];
}

/**
 * 设备转换成dictionary
 * @param device
 * @return
 */
- (NSDictionary *)deviceToDic:(UTEModelDevices *)device {
    NSNumber *rssi = [NSNumber numberWithInteger:[device rssi]];
    //设备蓝牙地址，只有连接上设备才有值
    NSString *address = [[NSString alloc] initWithData:device.address encoding:NSUTF8StringEncoding];
    NSString *version = [device version];
    if (version == nil) {
        version = @"";
    }
    NSMutableDictionary *d = [@{@"id": device.identifier,
            @"name": device.name,
            @"rssi": rssi,
            @"address": address, @"version": version} mutableCopy];
    return d;
}

- (NSData *)toJSONData:(NSDictionary *)theData {
    NSError *error = nil;
    if (theData == nil) {return @"{}";};
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:theData
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    if ([jsonData length] == 0 & error == nil) {
        return jsonData;
    } else {
        return nil;
    }
}

/**
 * 查找设备
 * @param identifier
 * @return
 */
- (UTEModelDevices *)findDevice:(NSString *)identifier {
    for (UTEModelDevices *devices in [self nsArray]) {
        if ([[devices identifier] isEqual:identifier]) {
            return devices;
        }
    }
    return nil;
}

- (void)sendPluginResult:(CDVPluginResult *)pluginResult callbackId:(NSString *)callbackId {
    if ([self getCallBackId:callbackId] != nil) {
        [self.commandDelegate sendPluginResult:pluginResult callbackId:[self getCallBackId:callbackId]];
    } else {
        NSLog(@"====sendPluginResult=== null method");
    }
}
@end
