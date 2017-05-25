//
//  SmartBand.h
//  xbracelet-App
//
//  Created by KevinChen on 2017/5/15.
//
//
#import <Cordova/CDV.h>
@import UTESmartBandApi;

@interface SmartBand : CDVPlugin <UTEManagerDelegate> {
    // Member variables go here.
    NSMutableDictionary *_cordovaCallbackDic;
//     UTEModelDevices *uteModelDevices;
    NSTimer *scanNsTimer;
}
@property(nonatomic, strong) UTESmartBandClient *smartBandMgr;
@property(nonatomic, strong) NSMutableArray *nsArray;
@property(nonatomic, strong) NSDictionary *tempDataAll;
@property(nonatomic) BOOL isMustUpdate;


- (void)scan:(CDVInvokedUrlCommand *)command;

- (void)stop:(CDVInvokedUrlCommand *)command;

- (void)connect:(CDVInvokedUrlCommand *)command;

- (void)sendSedentaryRemindCommand:(CDVInvokedUrlCommand *)command;

- (void)shakeMode:(CDVInvokedUrlCommand *)command;

- (void)sendToSetAlarmCommand:(CDVInvokedUrlCommand *)command;

- (void)sendStepLenAndWeightToBLE:(CDVInvokedUrlCommand *)command;

- (void)syncAllStepData:(CDVInvokedUrlCommand *)command;

- (void)syncAllSleepData:(CDVInvokedUrlCommand *)command;

- (void)findBand:(CDVInvokedUrlCommand *)command;

- (void)deleteDevicesAllData:(CDVInvokedUrlCommand *)command;

- (void)sendToReadBLEBattery:(CDVInvokedUrlCommand *)command;

- (void)sendToReadBLEVersion:(CDVInvokedUrlCommand *)command;

- (void)syncBLETime:(CDVInvokedUrlCommand *)command;

- (void)isEnabled:(CDVInvokedUrlCommand *)command;

- (void)querySleepDate:(CDVInvokedUrlCommand *)command;

- (void)updateStepSQL:(CDVInvokedUrlCommand *)command;

- (void)queryStepDate:(CDVInvokedUrlCommand *)command;

- (void)queryStepInfo:(CDVInvokedUrlCommand *)command;

- (void)queryOneHourStepSQL:(CDVInvokedUrlCommand *)command;

- (void)readRssi:(CDVInvokedUrlCommand *)command;

- (void)disConnect:(CDVInvokedUrlCommand *)command;

- (void)querySleepInfo:(CDVInvokedUrlCommand *)command;

- (void)isSupported:(CDVInvokedUrlCommand *)command;

- (void)isRKPlatform:(CDVInvokedUrlCommand *)command;

- (void)getServerBtImgVersion:(CDVInvokedUrlCommand *)command;

- (void)beginUpdateFirmware:(CDVInvokedUrlCommand *)command;

//- (void)changeDeviveFeature:(CDVInvokedUrlCommand *)command;

- (void)updateFirmware:(CDVInvokedUrlCommand *)command;

- (void)getServerPatchVersion:(CDVInvokedUrlCommand *)command;

- (void)queryDeviceFearture:(CDVInvokedUrlCommand *)command;

- (void)checkUTEDevicesStateIsEnable:(CDVInvokedUrlCommand *)command;

- (void)syncAllData:(CDVInvokedUrlCommand *)command;

- (void)openRemind:(CDVInvokedUrlCommand *)command;
@end
