//
//  SmartBand.h
//  xbracelet-App
//
//  Created by KevinChen on 2017/5/15.
//
//
#import <Cordova/CDV.h>
#import "UTESmartBandClient.h"
@interface SmartBand : CDVPlugin <UTEManagerDelegate> {
    // Member variables go here.
    NSMutableArray *nsArray;
    NSMutableDictionary *_cordovaCallbackDic;
//     UTEModelDevices *uteModelDevices;
}

- (void)coolMethod:(CDVInvokedUrlCommand *)command;

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

- (void)getServerPatchVersion:(CDVInvokedUrlCommand *)command;

- (void)queryDeviceFearture:(CDVInvokedUrlCommand *)command;
@end
