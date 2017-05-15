/********* cordova-heytz-smartband.m Cordova Plugin Implementation *******/
#import "SmartBand.h"

@implementation SmartBand

- (void)initialize {
    if (self == [SmartBand class]) {
        [[UTESmartBandClient sharedInstance] initUTESmartBandClient];
        nsArray = [NSMutableArray array];
        _cordovaCallbackDic = [NSMutableDictionary dictionary];
    }
}

- (void)coolMethod:(CDVInvokedUrlCommand *)command {
    CDVPluginResult *pluginResult = nil;
    NSString *echo = [command.arguments objectAtIndex:0];
    if (echo != nil && [echo length] > 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)init:(CDVInvokedUrlCommand *)command {
    CDVPluginResult *pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command];
}

- (void)scan:(CDVInvokedUrlCommand *)command {
    _cordovaCallbackDic[@"init"] = command;
    [nsArray removeAllObjects];
    int time = [command.arguments objectAtIndex:0];
    [[UTESmartBandClient sharedInstance] startScanDevices];
};


- (void)stop:(CDVInvokedUrlCommand *)command {
    [[UTESmartBandClient sharedInstance] stopScanDevices];
}

- (void)connect:(CDVInvokedUrlCommand *)command {
    NSString *address = [command.arguments objectAtIndex:0];
    for (UTEModelDevices *devices in nsArray) {
        if ([[devices address] isEqual:address]) {
            [[[[UTESmartBandClient sharedInstance] connectedDevicesModel] devices]];
        }
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

}

/**
 *  @discussion 时时监听了蓝牙连接状态
 *
 *  @param bluetoothState 蓝牙状态
 */
- (void)uteManagerBluetoothState:(UTEBluetoothSate)bluetoothState {

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
