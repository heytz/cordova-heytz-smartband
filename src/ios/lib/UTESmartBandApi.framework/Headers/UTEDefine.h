//
//  UTEDefine.h
//  UTESmartBandApi
//
//  Created by VV on 2017/4/22.
//  Copyright © 2017年 vv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UTEDefine : NSObject
/**
 *  NSDictionary 同步数据完 - 步数键值,value:NSArray
 */
extern NSString *const kUTEQueryRunData;
/**
 *  NSDictionary 同步数据完 - 睡眠键值,value:NSArray
 */
extern NSString *const kUTEQuerySleepData;
/**
 *  NSDictionary 同步数据完/测试心率完 - 心率键值,value:NSArray
 */
extern NSString *const kUTEQueryHRMData;
/**
 *  NSDictionary 同步数据完/测试血压完 - 血压键值,value:NSArray
 */
extern NSString *const kUTEQueryBloodData;
/**
 *  NSDictionary 设备密码状态 键值,value:NSString 转为NSInteger 对应UTEPasswordState枚举
 */
extern NSString *const kUTEPasswordState;
/**
 *  NSDictionary 具有运动模式的设备 走路模式的键值
 */
extern NSString *const kUTEQuerySportWalkData;
/**
 *  NSDictionary 具有运动模式的设备 跑步模式的键值
 */
extern NSString *const kUTEQuerySportRunData;
/**
 *  NSDictionary 具有运动模式的设备 骑车模式的键值
 */
extern NSString *const kUTEQuerySportBicycleData;
/**
 *  NSDictionary 具有运动模式的设备 游泳模式的键值
 */
extern NSString *const kUTEQuerySportSwimData;
/**
 *  NSDictionary 具有运动模式的设备 跳绳模式的键值
 */
extern NSString *const kUTEQuerySportSkipData;



/*!
 *  @enum UTEOption
 *
 *  @discussion 设置设备特性
 *
 *
 *  @constant UTEOptionSyncAllStepsData      同步设备所有步数（包括运动模式的走路和跑步数据）
 *  @constant UTEOptionSyncAllSleepData      同步设备所有睡眠
 *  @constant UTEOptionSyncAllHRMData        同步设备所有心率
 *  @constant UTEOptionSyncAllBloodData      同步设备所有血压
 *  @constant UTEOptionSyncAllData           同步设备所有数据 （步数和睡眠）
 *  @constant UTEOotionTodaySteps            获取今天总步数
 *  @constant UTEOptionIncall                来电指令 :当手机来电时，调用此值则设备会震动10次 1秒1次
 
 *  @constant UTEOptionHangup                挂断/接通:调用此值则设备会立即停止震动
 *  @constant UTEOptionFindBand              查找设备 :设备震动2次 1秒1次
 *  @constant UTEOptionSyncTime              同步当前手机时间
 *  @constant UTEOptionReadDevicesBattery    读取设备电量
 
 *  @constant UTEOptionHeartDetectingStart   开始测试心率
 *  @constant UTEOptionHeartDetectingStop    停止测试心率
 *  @constant UTEOptionHeartSwitchDynamic    切换为动态心率模式
 *  @constant UTEOptionHeartSwitchStatic     切换为静态心率模式
 
 *  @constant UTEOptionUnitInch              设置设备计量单位为 英制 磅(lbs) (RK 平台暂时无效)
 *  @constant UTEOptionUnitMeter             设置设备计量单位为 公制 千克    (RK 平台暂时无效)
 *  @constant UTEOptionUnitInch_12           设置设备计量单位为 英制 磅   时间12小时制(AM,PM) 需固件支持
 *  @constant UTEOptionUnitInch_24           设置设备计量单位为 英制 磅   时间24小时制        需固件支持
 *  @constant UTEOptionUnitMeter_12          设置设备计量单位为 公制 千克 时间12小时制(AM,PM) 需固件支持
 *  @constant UTEOptionUnitMeter_24          设置设备计量单位为 公制 千克 时间24小时制        需固件支持
 
 （RK平台 支持以下所有提醒，无需考虑isHasExtra值）
 *  @constant UTEOptionOpenRemindIncall      打开设备 来电提醒 震动1次  前提isHasExtra = YES
 *  @constant UTEOptionOpenRemindQQ          打开设备 QQ 提醒  震动1次   前提isHasExtra = YES
 *  @constant UTEOptionOpenRemindWeixin      打开设备 微信提醒 震动1次   前提isHasExtra = YES
 *  @constant UTEOptionOpenRemindSms         打开设备 SMS提醒  震动1次   前提isHasExtra = YES
 *  @constant UTEOptionOpenRemindMore        打开设备 更多提醒  震动1次   前提isHasExtra = YES
 *  @constant UTEOptionCloseRemindIncall     关闭设备 来电提醒           前提isHasExtra = YES
 *  @constant UTEOptionCloseRemindQQ         关闭设备 QQ提醒             前提isHasExtra = YES
 *  @constant UTEOptionCloseRemindWeixin     关闭设备 微信提醒           前提isHasExtra = YES
 *  @constant UTEOptionCloseRemindSms        关闭设备 SMS提醒            前提isHasExtra = YES
 *  @constant UTEOptionCloseRemindMore       关闭设备 更多提醒           前提isHasExtra = YES
 
 *  @constant UTEOptionOpenCameraMode        打开设备摇一摇拍照模式:接着用户每摇晃3次设备左右
 代理uteManagerTakePicture方法就被调用
 *  @constant UTEOptionCloseCameraMode       关闭设备摇一摇拍照模式:退出拍照模式 一定要调用此值
 否则设备可能不计步
 *
 *  @constant UTEOptionDeleteDevicesAllData  清除设备所有数据
 
 (横竖屏功能需要固件支持,请看isHasOrientation属性)
 *  @constant UTEOptionDeviceHorizontal      设置设备横屏
 *  @constant UTEOptionDeviceVertical        设置设备竖屏
 *
 *  @constant UTEOptionBloodDetectingStart   开始测试血压
 *  @constant UTEOptionBloodDetectingStop    停止测试血压
 *
 *  @constant UTEOptionReadDisplaySize       查询表盘分辨率和能切换的个数
 *
 *  @constant UTEOptionSyncSkipData          同步跳绳所有数据
 *  @constant UTEOptionSyncSwimData          同步游泳所有数据
 *
 *  @constant UTEOptionReadBaseStatus        只能读取设备当前 监听计步 还是 监听睡眠 状态
 *
 */
typedef NS_ENUM(NSInteger, UTEOption) {
    
    UTEOptionSyncAllStepsData,
    UTEOptionSyncAllSleepData,
    UTEOptionSyncAllHRMData,
    UTEOptionSyncAllBloodData,
    UTEOptionSyncAllData,
    UTEOotionTodaySteps,
    UTEOptionIncall,
    UTEOptionHangup,
    UTEOptionFindBand,
    UTEOptionSyncTime,
    UTEOptionReadDevicesBattery,
    
    UTEOptionHeartDetectingStart,
    UTEOptionHeartDetectingStop,
    UTEOptionHeartSwitchDynamic,
    UTEOptionHeartSwitchStatic,
    
    UTEOptionUnitInch,
    UTEOptionUnitMeter,
    UTEOptionUnitInch_12,
    UTEOptionUnitInch_24,
    UTEOptionUnitMeter_12,
    UTEOptionUnitMeter_24,
    
    UTEOptionOpenRemindIncall,
    UTEOptionOpenRemindQQ,
    UTEOptionOpenRemindWeixin,
    UTEOptionOpenRemindSms,
    UTEOptionOpenRemindMore,
    UTEOptionCloseRemindIncall,
    UTEOptionCloseRemindQQ,
    UTEOptionCloseRemindWeixin,
    UTEOptionCloseRemindSms,
    UTEOptionCloseRemindMore,
    
    UTEOptionOpenCameraMode,
    UTEOptionCloseCameraMode,
    
    UTEOptionDeleteDevicesAllData,
    
    UTEOptionDeviceHorizontal,
    UTEOptionDeviceVertical,
    
    UTEOptionBloodDetectingStart,
    UTEOptionBloodDetectingStop,
    UTEOptionReadDisplaySize,
    
    UTEOptionSyncSkipData,
    UTEOptionSyncSwimData,
    
    UTEOptionReadBaseStatus,
};


/*!
 *  @enum UTECallBack
 
 *
 *  @discussion SDK对固件发送命令以下对应，如固件接收到值，将发送返回值给SDK，如SDK接收到值将回调；否则无。
 *
 *  @constant UTECallBackUnit                     设置设备计量单位
 *  @constant UTECallBackInfoHeightWeight         设置设备里面身高、体重
 *  @constant UTECallBackSyncTime                 同步当前时间
 *  @constant UTECallBackAlarm                    设置闹钟
 
 *  @constant UTECallBackOpenRemindIncall         打开设备 来电提醒
 *  @constant UTECallBackOpenRemindQQ             打开设备 QQ 提醒
 *  @constant UTECallBackOpenRemindWeixin         打开设备 微信提醒
 *  @constant UTECallBackOpenRemindSms            打开设备 SMS提醒
 *  @constant UTECallBackOpenRemindMore           打开设备 更多提醒（除以上提醒，所有的App允许系统打开了的通知提示）
 
 *  @constant UTECallBackCloseRemindIncall        关闭设备 来电提醒
 *  @constant UTECallBackCloseRemindQQ            关闭设备 QQ提醒
 *  @constant UTECallBackCloseRemindWeixin        关闭设备 微信提醒
 *  @constant UTECallBackCloseRemindSms           关闭设备 SMS提醒
 *  @constant UTECallBackCloseRemindMore          关闭设备 更多提醒
 
 *  @constant UTECallBackOpenUnitSitRemind        打开久坐提醒
 *  @constant UTECallBackCloseSitRemind           关闭久坐提醒
 
 *  @constant UTECallBackHeartSwitchDynamic       切换动态心率
 *  @constant UTECallBackHeartSwitchStatic        切换静态心率
 
 *  @constant UTECallBackDevicesVersion           获取到了设备版本号
 *
 *  @constant UTECallBackDeviceHorizontal         设备横屏
 *  @constant UTECallBackDeviceVertical           设备竖屏
 
 *  @constant UTECallBackDeviceSilence            设备勿打扰
 *
 *  @constant UTECallBackDeviceWeather            设置2天内的天气
 *
 *  @constant UTECallBackDeviceBattery            获取到电量
 *  @constant UTECallBackSwitchHandAndDisplay     切换佩戴方式和表盘显示模式
 *  @constant UTECallBackWeatherSevenDay          设置7天内的天气
 *  @constant UTECallBackIbeaconOption            设置ibeacon数据
 *
 */
typedef NS_ENUM(NSInteger, UTECallBack) {
    
    UTECallBackUnit,
    UTECallBackInfoHeightWeight,
    UTECallBackSyncTime,
    UTECallBackAlarm,
    
    UTECallBackOpenRemindIncall,
    UTECallBackOpenRemindQQ,
    UTECallBackOpenRemindWeixin,
    UTECallBackOpenRemindSms,
    UTECallBackOpenRemindMore,
    
    UTECallBackCloseRemindIncall,
    UTECallBackCloseRemindQQ,
    UTECallBackCloseRemindWeixin,
    UTECallBackCloseRemindSms,
    UTECallBackCloseRemindMore,
    
    UTECallBackOpenUnitSitRemind,
    UTECallBackCloseSitRemind,
    
    UTECallBackHeartSwitchDynamic,
    UTECallBackHeartSwitchStatic,
    
    UTECallBackDevicesVersion,
    
    UTECallBackDeviceHorizontal,
    UTECallBackDeviceVertical,
    
    UTECallBackDeviceSilence,
    
    UTECallBackDeviceWeather,
    UTECallBackDeviceBattery,
    UTECallBackSwitchHandAndDisplay,
    UTECallBackWeatherSevenDay,
    UTECallBackIbeaconOption,
};

/*!
 *  @enum UTEDevicesSate
 *
 *  @discussion 设备状态
 *
 *  @constant UTEDevicesSateConnected             设备已经连接状态
 *  @constant UTEDevicesSateDisconnected          设备已经断开状态，如有错误码，请查看UTEErrorCode
 
 *  @constant UTEDevicesSateSyncBegin             设备在同步数据开始
 *  @constant UTEDevicesSateSyncSuccess           设备同步成功完毕
 *  @constant UTEDevicesSateSyncError             设备同步错误，请查看UTEErrorCode
 
 *  @constant UTEDevicesSateHeartDetectingStart   设备心率开始检测
 *  @constant UTEDevicesSateHeartDetectingProcess 设备心率检测中（带有值）
 *  @constant UTEDevicesSateHeartDetectingStop    设备心率停止检测
 *  @constant UTEDevicesSateHeartDetectingError   设备心率检测中错误， 请查看UTEErrorCode
 
 *  @constant UTEDevicesSateBloodDetectingStart   设备血压开始检测
 *  @constant UTEDevicesSateBloodDetectingProcess 设备血压检测中（带有值）
 *  @constant UTEDevicesSateBloodDetectingStop    设备血压停止检测
 *  @constant UTEDevicesSateBloodDetectingError   设备血压检测中错误， 请查看UTEErrorCode
 
 *  @constant UTEDevicesSateCheckFirmwareError    设备检查错误，请查看UTEErrorCode
 
 *  @constant UTEDevicesSateUpdateHaveNewVersion  设备有新版本
 *  @constant UTEDevicesSateUpdateNoNewVersion    设备没有新版本
 *  @constant UTEDevicesSateUpdateBegin           设备升级开始
 *  @constant UTEDevicesSateUpdateSuccess         设备升级成功，设备会自动断开，请重新连接
 *  @constant UTEDevicesSateUpdateError           设备升级失败，请查看UTEErrorCode
 *
 *  @constant UTEDevicesSateCardApduError         设备Apdu数据交互失败，请查看UTEErrorCode
 *
 *  @constant UTEDevicesSatePasswordState         设备密码验证状态 请看UTEPasswordState 请询问相关人员：设备是否有连接的密码验证过程
 *
 *  @constant UTEDevicesSateStep                  设备处于监听计步状态
 *  @constant UTEDevicesSateSleep                 设备处于监听睡眠状态
 */
typedef NS_ENUM(NSInteger, UTEDevicesSate) {
    UTEDevicesSateConnected = 0,
    UTEDevicesSateDisconnected,
    
    UTEDevicesSateSyncBegin,
    UTEDevicesSateSyncSuccess,
    UTEDevicesSateSyncError,
    
    UTEDevicesSateHeartDetectingStart,
    UTEDevicesSateHeartDetectingProcess,
    UTEDevicesSateHeartDetectingStop,
    UTEDevicesSateHeartDetectingError,
    
    UTEDevicesSateBloodDetectingStart,
    UTEDevicesSateBloodDetectingProcess,
    UTEDevicesSateBloodDetectingStop,
    UTEDevicesSateBloodDetectingError,
    
    UTEDevicesSateCheckFirmwareError,
    
    UTEDevicesSateUpdateHaveNewVersion,
    UTEDevicesSateUpdateNoNewVersion,
    UTEDevicesSateUpdateBegin,
    UTEDevicesSateUpdateSuccess,
    UTEDevicesSateUpdateError,
    
    UTEDevicesSateCardApduError,
    
    UTEDevicesSatePasswordState,
    
    UTEDevicesSateStep,
    UTEDevicesSateSleep,
};

/*!
 *  @enum UTEPasswordState
 *
 *  @discussion 密码状态
 *
 *  @constant UTEPasswordStateNew               设备需要设置一个新的密码(设备从未被连接过,密码是空的)
 *  @constant UTEPasswordStateNeed              设备需要密码输入(设备已设置过密码)
 *  @constant UTEPasswordStateCorrect           输入、验证或者修改的密码成功
 *  @constant UTEPasswordStateError             输入、验证或者修改的密码失败
 */
typedef NS_ENUM(NSInteger, UTEPasswordState) {
    
    UTEPasswordStateNew    = 1,
    UTEPasswordStateNeed,
    UTEPasswordStateCorrect,
    UTEPasswordStateError,
};

/*!
 *  @enum UTEPasswordType
 *
 *  @discussion 密码类型
 *
 *  @constant UTEPasswordTypeConnect           用于连接设备的时候
 *  @constant UTEPasswordTypeConfirm           用于修改密码时候必须验证
 *  @constant UTEPasswordTypeReset             用于修改密码时候验证成功后 重新设置密码
 */
typedef NS_ENUM(NSInteger, UTEPasswordType) {
    
    UTEPasswordTypeConnect    = 1,
    UTEPasswordTypeConfirm,
    UTEPasswordTypeReset,
};

/*!
 *  @enum UTEErrorCode
 *
 *  @discussion 设备错误码
 *
 *  @constant UTEErrorCodeDisconnect          设备远离手机断开，或没电了
 
 *  @constant UTEErrorCodeSyncDisconnect      同步数据时，设备异常断开
 *  @constant UTEErrorCodeHeartingDisconnect  心率测试时，设备异常断开
 *  @constant UTEErrorCodeBloodDisconnect     血压测试时，设备异常断开
 
 *  @constant UTEErrorCodeCheckTimeout        检查设备超时，一般网络超时
 *  @constant UTEErrorCodeCheckChara          检查设备时，固件不完整
 *  @constant UTEErrorCodeCheckAddress        检查设备时，固件不完整
 
 *  @constant UTEErrorCodeUpdateDownload      升级设备时，下载固件错误
 *  @constant UTEErrorCodeUpdateDisconnect    升级设备时，设备断开
 
 *  @constant UTEErrorCodeApduDisconnect      设备Apdu数据交互时，设备断开了
 */
typedef NS_ENUM(NSInteger, UTEErrorCode) {
    UTEErrorCodeDisconnect = 1,
    
    UTEErrorCodeSyncDisconnect,
    UTEErrorCodeHeartingDisconnect,
    UTEErrorCodeBloodDisconnect,
    
    UTEErrorCodeCheckTimeout,
    UTEErrorCodeCheckChara,
    UTEErrorCodeCheckAddress,
    
    UTEErrorCodeUpdateDownload,
    UTEErrorCodeUpdateDisconnect,
    
    UTEErrorCodeApduDisconnect,
};

/*!
 *  @enum UTEBluetoothSate
 *
 *  @discussion 手机蓝牙状态
 *
 *  @constant UTEBluetoothSateOpen       手机蓝牙打开
 *  @constant UTEBluetoothSateClose      手机蓝牙关闭
 *  @constant UTEBluetoothSateResetting  手机蓝牙重启
 */
typedef NS_ENUM(NSInteger, UTEBluetoothSate) {
    UTEBluetoothSateOpen = 0,
    UTEBluetoothSateClose,
    UTEBluetoothSateResetting,
};

/*!
 *  @enum UTEQueryType
 *
 *  @discussion 查找数据类型
 *
 *  @constant UTEQueryTypeRun        步数数据
 *  @constant UTEQueryTypeSleep      睡眠数据
 *  @constant UTEQueryTypeHRM        心率数据
 *  @constant UTEQueryTypeAll        所有数据(步数+睡眠)
 */
typedef NS_ENUM(NSInteger, UTEQueryType) {
    UTEQueryTypeRun = 0,
    UTEQueryTypeSleep,
    UTEQueryTypeHRM,
    UTEQueryTypeAll,
};

/*!
 *  @enum UTESleepType
 *
 *  @discussion 睡眠状况
 *
 *  @constant UTESleepTypeAwake          清醒
 *  @constant UTESleepTypeDeepSleep      深睡
 *  @constant UTESleepTypeLightSleep     浅睡
 */
typedef NS_ENUM(NSInteger, UTESleepType) {
    UTESleepTypeAwake = 0,
    UTESleepTypeDeepSleep,
    UTESleepTypeLightSleep,
};

/*!
 *  @enum UTEHRMType
 *
 *  @discussion 睡眠状况
 *
 *  @constant UTEHRMTypeNormal      心率数据正常（用于同步心率数据、正在测试心率时）
 *  @constant UTEHRMTypeSuccess     测试心率成功（用于测试心率完毕后返回，成功）
 *  @constant UTEHRMTypeFail        测试心率失败（用于测试心率完毕后返回，失败）
 *  @constant UTEHRMTypeTimeout     测试心率超时（用于测试心率完毕后返回，超时）
 */
typedef NS_ENUM(NSInteger, UTEHRMType) {
    UTEHRMTypeNormal = 0,
    UTEHRMTypeSuccess,
    UTEHRMTypeFail,
    UTEHRMTypeTimeout,
};

/*!
 *  @enum UTEBloodType
 *
 *  @discussion 血压状况
 *
 *  @constant UTEHRMTypeNormal      血压数据正常（用于同步数据的血压）
 *  @constant UTEHRMTypeSuccess     血压数据成功（用于测试血压完毕后返回，成功）
 *  @constant UTEHRMTypeFail        血压数据失败（用于测试血压完毕后返回，失败）
 *  @constant UTEHRMTypeTimeout     血压数据超时（用于测试血压完毕后返回，超时）
 */
typedef NS_ENUM(NSInteger, UTEBloodType) {
    UTEBloodTypeNormal = 0,
    UTEBloodTypeSuccess,
    UTEBloodTypeFail,
    UTEBloodTypeTimeout,
};

/*!
 *  @enum UTEAlarmWeek
 *
 *  @discussion 星期
 *
 *  @constant UTEAlarmWeekSunday       星期天
 *  @constant UTEAlarmWeekMonday       星期一
 *  @constant UTEAlarmWeekTuesday      星期二
 *  @constant UTEAlarmWeekWednesday    星期三
 *  @constant UTEAlarmWeekThursday     星期四
 *  @constant UTEAlarmWeekFriday       星期五
 *  @constant UTEAlarmWeekSaturday     星期六
 */
typedef NS_ENUM(NSInteger, UTEAlarmWeek) {
    UTEAlarmWeekSunday    = 0x01,
    UTEAlarmWeekMonday    = 0x02,
    UTEAlarmWeekTuesday   = 0x04,
    UTEAlarmWeekWednesday = 0x08,
    UTEAlarmWeekThursday  = 0x10,
    UTEAlarmWeekFriday    = 0x20,
    UTEAlarmWeekSaturday  = 0x40,
};

/*!
 *  @enum UTEAlarmNum
 *
 *  @discussion 闹钟序列号
 *
 *  @constant UTEAlarmNum1       第一个闹钟
 *  @constant UTEAlarmNum2       第二个闹钟
 *  @constant UTEAlarmNum3       第三个闹钟
 */
typedef NS_ENUM(NSInteger, UTEAlarmNum) {
    UTEAlarmNum1 = 1,
    UTEAlarmNum2,
    UTEAlarmNum3,
};

/*!
 *  @enum UTEDeviceFeature
 *
 *  @discussion 设备特性 （RK平台无此信息，无需考虑此属性）
 *
 *  @constant UTEDeviceFeatureNone             默认模式
 *  @constant UTEDeviceFeatureWechat           微信模式(微信排行)
 *  @constant UTEDeviceFeatureMessage          消息推送模式
 *  @constant UTEDeviceFeatureWechatMessage    消息推送与微信模式
 *  @constant UTEDeviceFeatureUpdate           升级模式
 *  @constant UTEDeviceFeatureUpdateWechat     升级模式与微信模式(微信排行)
 */
typedef NS_ENUM(NSInteger, UTEDeviceFeature) {
    UTEDeviceFeatureNone,
    UTEDeviceFeatureWechat,
    UTEDeviceFeatureMessage,
    UTEDeviceFeatureWechatMessage,
    UTEDeviceFeatureUpdate,
    UTEDeviceFeatureUpdateWechat,
};

/*!
 *  @enum UTESilenceType
 *
 *  @discussion 勿打扰模式 （需要固件支持）
 *
 *  @constant UTESilenceTypeNone             打开所有功能(不需要手环勿打扰)
 *  @constant UTESilenceTypeScreen           关闭手环屏幕，屏幕将永不亮屏
 *  @constant UTESilenceTypeVibration        关闭手环马达震动，手环将永不震动
 *  @constant UTESilenceTypeMessage          关闭手环任何信息提醒（QQ/Wechat/短信/电话）
 *  @constant UTESilenceTypePhone            关闭手环上一键挂电话功能
 */
typedef NS_ENUM(NSInteger, UTESilenceType) {
    UTESilenceTypeNone              = 0x00,
    UTESilenceTypeScreen            = 0x01,
    UTESilenceTypeVibration         = 0x02,
    UTESilenceTypeMessage           = 0x04,
    UTESilenceTypePhone             = 0x08,
};

/*!
 *  @enum UTEDeviceFeature
 *
 *  @discussion 天气类型 (固件支持的天气类型)
 *
 *  @constant UTEWeatherTypeSunny         //晴朗
 *  @constant UTEWeatherTypeCloudy        //多云
 *  @constant UTEWeatherTypeOvercast      //阴天
 *  @constant UTEWeatherTypeShower        //阵雨
 *  @constant UTEWeatherTypeThunderStorm  //雷阵雨
 *  @constant UTEWeatherTypeRainSnow      //雨夹雪
 *  @constant UTEWeatherTypeLightRain     //小雨
 *  @constant UTEWeatherTypePouring       //大雨
 *  @constant UTEWeatherTypeSnow          //下雪
 *  @constant UTEWeatherTypeSandstorm     //沙尘暴
 *  @constant UTEWeatherTypeMistHaze      //雾霾
 *  @constant UTEWeatherTypeWind          //有风
 */
typedef NS_ENUM(NSInteger, UTEWeatherType) {
    UTEWeatherTypeSunny         = 1,
    UTEWeatherTypeCloudy,
    UTEWeatherTypeOvercast,
    UTEWeatherTypeShower,
    UTEWeatherTypeThunderStorm,
    UTEWeatherTypeRainSnow,
    UTEWeatherTypeLightRain,
    UTEWeatherTypePouring,
    UTEWeatherTypeSnow,
    UTEWeatherTypeSandstorm,
    UTEWeatherTypeMistHaze,
    UTEWeatherTypeWind,
};

/*!
 *  @enum UTEDeviceSreenDisplayType
 *
 *  @discussion 表盘显示方式
 *
 *  @constant UTEDeviceSreenDisplayTypeHorizontal        //横屏
 *  @constant UTEDeviceSreenDisplayTypeVerticalEN        //竖屏 英文显示
 *  @constant UTEDeviceSreenDisplayTypeVerticalCH        //竖屏 中文显示
 */
typedef NS_ENUM(NSInteger, UTEDeviceSreenDisplayType) {
    UTEDeviceSreenDisplayTypeHorizontal,
    UTEDeviceSreenDisplayTypeVerticalEN,
    UTEDeviceSreenDisplayTypeVerticalCH,
};

/*!
 *  @enum UTEWearType
 *
 *  @discussion 佩戴方式
 *
 *  @constant UTEWearTypeLeft         //左手
 *  @constant UTEWearTypeRight        //右手
 */
typedef NS_ENUM(NSInteger, UTEWearType) {
    UTEWearTypeLeft,
    UTEWearTypeRight,
};

/*!
 *  @enum UTEIbeaconOption
 *
 *  @discussion ibeacon 设置类型
 *
 *  @constant UTEIbeaconOptionUUID                 //uuid
 *  @constant UTEIbeaconOptionMajor                //major
 *  @constant UTEIbeaconOptionMinor                //minor
 *  @constant UTEIbeaconOptionName                 //device name
 *  @constant UTEIbeaconOptionTXPower              //TX Power
 *  @constant UTEIbeaconOptionAdvertisingInterval  //Advertising Interval
 */
typedef NS_ENUM(NSInteger, UTEIbeaconOption) {
    UTEIbeaconOptionUUID,
    UTEIbeaconOptionMajor,
    UTEIbeaconOptionMinor,
    UTEIbeaconOptionName,
    UTEIbeaconOptionTXPower,
    UTEIbeaconOptionAdvertisingInterval,
};

@end

/*!
 *  UTEModelDevices 设备属性模型
 */
@interface UTEModelDevices : NSObject
/**
 *  设备版本
 */
@property (nonatomic,copy  ) NSString *version;
/**
 *  设备名称
 */
@property (nonatomic,copy  ) NSString *name;
/**
 *  设备唯一标示
 */
@property (nonatomic,copy  ) NSString *identifier;
/**
 *  设备电量 只有连接上设备才有值
 */
@property (nonatomic,assign) NSInteger battery;
/**
 *  设备连接状态
 */
@property (nonatomic,assign) BOOL     isConnected;
/**
 *  设备是否具有此属性（连接上才有值） （RK平台无此信息，无需考虑此属性）
 */
@property (nonatomic,assign) BOOL     isHasExtra;
/**
 *  设备是否具心率功能
 */
@property (nonatomic,assign) BOOL     isHasHRM;
/**
 *  设备是否具血压功能
 */
@property (nonatomic,assign) BOOL     isHasBlood;
/**
 *  设备是否具天气功能 设备支持2天内的天气
 */
@property (nonatomic,assign) BOOL     isHasWeather;
/**
 *  设备是否具天气功能 设备支持7天内的天气
 */
@property (nonatomic,assign) BOOL     isHasWeatherSeven;
/**
 *  设备是否具横竖屏幕切换功能
 */
@property (nonatomic,assign) BOOL     isHasOrientation;
/**
 *  设备是否具勿打扰功能
 */
@property (nonatomic,assign) BOOL     isHasSilence;
/**
 *  设备是否可以使能抬手亮屏
 */
@property (nonatomic,assign) BOOL     isHasHandLight;
/**
 *  设备是否具备最大心率警报功能
 */
@property (nonatomic,assign) BOOL     isHasMaxHeartAlert;
/**
 *  设备是否支持动静态切换功能
 *  这个值只在扫描设备时有值,连接之后无效
 */
@property (nonatomic,assign) BOOL     isSwitchHeart;
/**
 *  设备是否支持表盘切换 和 左右手切换
 */
@property (nonatomic,assign) BOOL     isHasSwitchHand;
/**
 *  设备是否支持ibeacon 功能
 */
@property (nonatomic,assign) BOOL     isHasIbeacon;
/**
 *  设备是否支持 走路和跑步区分 功能
 */
@property (nonatomic,assign) BOOL     isHasWalkRun;
/**
 *  设备是否支持 跳绳 功能
 */
@property (nonatomic,assign) BOOL     isHasSkip;
/**
 *  设备是否支持 游泳 功能
 */
@property (nonatomic,assign) BOOL     isHasSwim;
/**
 *  设备是否支持 骑车 功能
 */
@property (nonatomic,assign) BOOL     isHasBicycle;
/**
 *  设备是否支持 多个闹钟(三个) 功能  仅新的固件支持
 */
@property (nonatomic,assign) BOOL     isHasMulClock;
/**
 *  设备是否支持 久坐提醒 功能 仅新的固件支持
 */
@property (nonatomic,assign) BOOL     isHasRemindSit;
/**
 *  设备是否支持 事务提醒 功能 仅新的固件支持
 */
@property (nonatomic,assign) BOOL     isHasRemindTask;
/**
 *  设备信号强度 （如_isScanRepeat=true，则在扫描过程中会实时变化,被连上的设备不被赋值）
 */
@property (nonatomic,assign) NSInteger rssi;
/**
 *  设备蓝牙地址，只有连接上设备才有值
 */
@property (nonatomic,strong) NSData   *address;
/**
 *  设备另外特性，只有连接上设备才有实际值：不同的特性支持不同的功能（具体请看文档说明）
 */
@property (nonatomic,assign) UTEDeviceFeature   featureAnother;
/**
 *  设备广播里面包含的内容(4个key):
 *
 *    kCBAdvDataServiceUUIDs
 *    kCBAdvDataLocalName
 *    kCBAdvDataManufacturerData
 *    kCBAdvDataIsConnectable
 *
 *  备注:如设备连上了，此值将变为空.
 */
@property (nonatomic,strong) NSDictionary       *advertisementData;
@end

/*!
 *  UTEModelAlarm 设备闹钟模型
 */
@interface UTEModelAlarm : NSObject
/**
 *  闹钟时间24进制 格式: @"09:30" @"21:05"
 */
@property (nonatomic,copy  ) NSString      *time;
/**
 *  闹钟星期(七位数) 格式:详细请看文档
 */
@property (nonatomic,assign) UTEAlarmWeek  week;
/**
 *  闹钟使能
 */
@property (nonatomic,assign) BOOL          enable;
/**
 *  闹钟序列号,第几个闹钟
 */
@property (nonatomic,assign) UTEAlarmNum   num;

@end

/*!
 *  UTEModelRunData 历史步数模型
 */
@interface UTEModelRunData : NSObject
/**
 *  时间格式: @"2015-08-08-13"
 */
@property (nonatomic,copy  ) NSString     *time;
/**
 *  一天的总卡路里 单位千卡
 */
@property (nonatomic,assign) CGFloat      calories;
/**
 *  一小时内的卡路里 单位千卡
 */
@property (nonatomic,assign) CGFloat      hourCalories;
/**
 *  一小时内步数
 */
@property (nonatomic,assign) NSInteger    hourSteps;
/**
 *  一天的总步数
 */
@property (nonatomic,assign) NSInteger    totalSteps;
/**
 *  一天的总距离 单位米
 */
@property (nonatomic,assign) CGFloat      distances;
/**
 *  一小时内的距离 单位米
 */
@property (nonatomic,assign) CGFloat      hourDistances;

@end

/*!
 *  UTEModelSleepData 历史睡眠模型
 */
@interface UTEModelSleepData : NSObject
/**
 *  开始时间格式: @"2015-08-08-23-30"
 */
@property (nonatomic,copy  ) NSString     *startTime;
/**
 *  结束时间格式: @"2015-08-09-07-30"
 */
@property (nonatomic,copy  ) NSString     *endTime;
/**
 *  睡眠状况
 */
@property (nonatomic,assign) UTESleepType sleepType;

@end

/*!
 *  UTEModelHRMData 心率模型
 */
@interface UTEModelHRMData : NSObject

/**
 *  心率时间格式: @"2015-08-08-23-30"
 */
@property (nonatomic,copy  ) NSString  *heartTime;
/**
 *  心率每分钟跳动次数
 */
@property (nonatomic,copy  ) NSString  *heartCount;
/**
 *  UTEHRMType 心率测试数据是否 正常、成功、超时、失败
 */
@property (nonatomic,assign) UTEHRMType heartType;

@end

/*!
 *  UTEModelBloodData 血压模型
 */
@interface UTEModelBloodData : NSObject

/**
 *  时间格式: @"2015-08-08-23-30"
 */
@property (nonatomic,copy) NSString  *bloodTime;
/**
 *  收缩压
 */
@property (nonatomic,copy) NSString  *bloodSystolic;
/**
 *  舒张压
 */
@property (nonatomic,copy) NSString  *bloodDiastolic;
/**
 *  血压状态
 */
@property (nonatomic,assign) UTEBloodType  bloodType;

@end

/*!
 *  UTEWeather 天气模型
 */
@interface UTEModelWeather : NSObject
/**
 *  城市 设备仅支持显示最多中文4个字，其他语言请填@"00"
 */
@property (nonatomic,copy  ) NSString   *city;
/**
 *  今天的PM2.5
 */
@property (nonatomic,assign) NSInteger  pm25;
/**
 *  今天的AQI
 */
@property (nonatomic,assign) NSInteger  aqi;
/**
 *  今天的当前温度
 */
@property (nonatomic,assign) NSInteger  temperatureCurrent;
/**
 *  最高气温
 */
@property (nonatomic,assign) NSInteger  temperatureMax;
/**
 *  最低气温
 */
@property (nonatomic,assign) NSInteger  temperatureMin;
/**
 *  天气类型
 */
@property (nonatomic,assign) UTEWeatherType  type;

@end

/*!
 *  UTEModelSportWalk 运动模式 走路模型
 */
@interface UTEModelSportWalk : NSObject
/**
 *  走路的步数
 */
@property (nonatomic,assign) NSInteger    steps;
/**
 *  时间格式: @"2015-08-08-13"
 */
@property (nonatomic,copy  ) NSString     *time;
/**
 *  走路开始时间 格式:@"05" 如当前 2015-08-08-13 的 05 分
 */
@property (nonatomic,copy  ) NSString     *timeStart;
/**
 *  走路结束时间 格式:@"59" 如当前 2015-08-08-13 的 59 分
 */
@property (nonatomic,copy  ) NSString     *timeEnd;
/**
 *  走路时长 单位分钟
 */
@property (nonatomic,assign) NSInteger    duration;
/**
 *  距离 单位米
 */
@property (nonatomic,assign) CGFloat      distances;
/**
 *  卡路里 单位千卡
 */
@property (nonatomic,assign) CGFloat      calories;

@end

/*!
 *  UTEModelSportRun 运动模式 跑步模型
 */
@interface UTEModelSportRun : NSObject
/**
 *  跑步的步数
 */
@property (nonatomic,assign) NSInteger    steps;
/**
 *  时间格式: @"2015-08-08-13"
 */
@property (nonatomic,copy  ) NSString     *time;
/**
 *  跑步开始时间 格式:@"05" 如当前 2015-08-08-13 的 05 分
 */
@property (nonatomic,copy  ) NSString     *timeStart;
/**
 *  跑步结束时间 格式:@"59" 如当前 2015-08-08-13 的 59 分
 */
@property (nonatomic,copy  ) NSString     *timeEnd;
/**
 *  跑步时长 单位分钟
 */
@property (nonatomic,assign) NSInteger    duration;

@end

/*!
 *  UTEModelSportSwim 运动模式 游泳模型
 */
@interface UTEModelSportSwim : NSObject

/**
 *  时间格式: @"2015-08-08"
 */
@property (nonatomic,copy  ) NSString     *time;
/**
 *  游泳开始时间格式: @"08-15" 时-分 只记录一天中的第一次
 */
@property (nonatomic,copy  ) NSString     *timeStart;
/**
 *  游泳结束时间格式: @"20-15" 时-分 只记录一天中的最后一次
 */
@property (nonatomic,copy  ) NSString     *timeEnd;
/**
 *  游泳时长 单位秒 累计一天总共时长
 */
@property (nonatomic,assign) NSInteger    duration;
/**
 *  游泳划臂力次数  累计一天总共次数
 */
@property (nonatomic,assign) NSInteger    count;

@end

/*!
 *  UTEModelSportSkip 运动模式 跳绳模型
 */
@interface UTEModelSportSkip : NSObject

/**
 *  时间格式: @"2015-08-08"
 */
@property (nonatomic,copy  ) NSString     *time;
/**
 *  跳绳开始时间格式: @"08-15" 时-分 只记录一天中的第一次
 */
@property (nonatomic,copy  ) NSString     *timeStart;
/**
 *  跳绳结束时间格式: @"20-15" 时-分 只记录一天中的最后一次
 */
@property (nonatomic,copy  ) NSString     *timeEnd;
/**
 *  跳绳时长 单位秒 累计一天总时长
 */
@property (nonatomic,assign) NSInteger    duration;
/**
 *  跳绳次数  累计一天总共次数
 */
@property (nonatomic,assign) NSInteger    count;

@end






