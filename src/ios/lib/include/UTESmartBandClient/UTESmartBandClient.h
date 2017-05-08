//
//  UTESmartBandClient.h
//  UTESmartBandClient
//
//  Created by VV on 14/11/28.
//  Copyright © 2014年 vv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>

/**
 *  NSDictionary 同步数据完 - 步数键值
 */
extern NSString *const kUTEQueryRunData;
/**
 *  NSDictionary 同步数据完 - 睡眠键值
 */
extern NSString *const kUTEQuerySleepData;
/**
 *  NSDictionary 同步数据完/测试心率完 - 心率键值
 */
extern NSString *const kUTEQueryHRMData;

/*!
 *  @enum UTEOption
 *
 *  @discussion 设置设备特性
 *  
 *  
 *  @constant UTEOptionSyncAllStepsData      同步设备所有步数
 *  @constant UTEOptionSyncAllSleepData      同步设备所有睡眠
 *  @constant UTEOptionSyncAllHRMData        同步设备所有心率
 *  @constant UTEOptionSyncAllData           同步设备所有数据
 *  @constant UTEOotionTodaySteps            获取今天总步数
 *  @constant UTEOptionIncall                来电指令 :当手机来电时，调用此值则设备会震动10次 1秒1次
 
 *  @constant UTEOptionHangup                挂断/接通:调用此值则设备会立即停止震动
 *  @constant UTEOptionFindBand              查找设备 :设备震动2次 1秒1次
 *  @constant UTEOptionSyncTime              同步当前手机时间
 *  @constant UTEOptionReadDevicesBattery    读取设备电量
 
 *  @constant UTEOptionHeartDetectingStart   开始测试心率
 *  @constant UTEOptionHeartDetectingStop    停止测试心率
 
 *  @constant UTEOptionUnitInch              设置设备计量单位为 英制 磅(lbs)
 *  @constant UTEOptionUnitMeter             设置设备计量单位为 公制 千克
 *  @constant UTEOptionUnitInch_12           设置设备计量单位为 英制 磅   时间12小时制(AM,PM) 需固件支持
 *  @constant UTEOptionUnitInch_24           设置设备计量单位为 英制 磅   时间24小时制        需固件支持
 *  @constant UTEOptionUnitMeter_12          设置设备计量单位为 公制 千克 时间12小时制(AM,PM) 需固件支持
 *  @constant UTEOptionUnitMeter_24          设置设备计量单位为 公制 千克 时间24小时制        需固件支持
 
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
 */
typedef NS_ENUM(NSInteger, UTEOption) {
    
    UTEOptionSyncAllStepsData,
    UTEOptionSyncAllSleepData,
    UTEOptionSyncAllHRMData,
    UTEOptionSyncAllData,
    UTEOotionTodaySteps,
    UTEOptionIncall,
    UTEOptionHangup,
    UTEOptionFindBand,
    UTEOptionSyncTime,
    UTEOptionReadDevicesBattery,
    
    UTEOptionHeartDetectingStart,
    UTEOptionHeartDetectingStop,
    
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
 
 *  @constant UTEDevicesSateCheckFirmwareError    设备检查错误，请查看UTEErrorCode
 
 *  @constant UTEDevicesSateUpdateHaveNewVersion  设备没有新版本
 *  @constant UTEDevicesSateUpdateNoNewVersion    设备有新版本
 *  @constant UTEDevicesSateUpdateBegin           设备升级开始
 *  @constant UTEDevicesSateUpdateSuccess         设备升级成功，设备会自动断开，请重新连接
 *  @constant UTEDevicesSateUpdateError           设备升级失败，请查看UTEErrorCode
 *
 *  @constant UTEDevicesSateCardApduError         设备Apdu数据交互失败，请查看UTEErrorCode
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
    
    UTEDevicesSateCheckFirmwareError,
    
    UTEDevicesSateUpdateHaveNewVersion,
    UTEDevicesSateUpdateNoNewVersion,
    UTEDevicesSateUpdateBegin,
    UTEDevicesSateUpdateSuccess,
    UTEDevicesSateUpdateError,
    
    UTEDevicesSateCardApduError,
};

/*!
 *  @enum UTEErrorCode
 *
 *  @discussion 设备错误码
 *
 *  @constant UTEErrorCodeDisconnect          设备远离手机断开，或没电了
 
 *  @constant UTEErrorCodeSyncDisconnect      同步数据时，设备异常断开
 *  @constant UTEErrorCodeHeartingDisconnect  心率测试时，设备异常断开
 
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
 *  @discussion 设备特性
 *
 *  @constant UTEDeviceFeatureNone             默认模式
 *  @constant UTEDeviceFeatureWechat           微信模式(微信排行)
 *  @constant UTEDeviceFeatureMessage          消息推送模式
 *  @constant UTEDeviceFeatureWechatMessage    消息推送与微信模式
 *  @constant UTEDeviceFeatureUpdate           升级模式
 */
typedef NS_ENUM(NSInteger, UTEDeviceFeature) {
    UTEDeviceFeatureNone,
    UTEDeviceFeatureWechat,
    UTEDeviceFeatureMessage,
    UTEDeviceFeatureWechatMessage,
    UTEDeviceFeatureUpdate,
};

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
 *  设备是否具有此属性（连接上才有值） 也可向SDK开发人员询问
 */
@property (nonatomic,assign) BOOL     isHasExtra;
/**
 *  设备是否具心率功能 可向SDK开发人员询问
 */
@property (nonatomic,assign) BOOL     isHasHRM;
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
 *  一小时步数
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

#pragma mark - UTEManagerDelegate 代理

/*!
 *  UTEManagerDelegate 代理
 */
@protocol UTEManagerDelegate;

@protocol UTEManagerDelegate <NSObject>

@optional

/**
 *  @discussion 每找到一个设备，就会调用一次
 *
 *  @param modelDevices 设备属性模型
 */
- (void)uteManagerDiscoverDevices:(UTEModelDevices *)modelDevices;

/**
 *  @discussion 时时监听了已连接设备状态
 *
 *  @param devicesState 设备状态
 *  @param error        错误码
 */
- (void)uteManagerDevicesSate:(UTEDevicesSate)devicesState error:(NSError *)error userInfo:(NSDictionary *)info;

/**
 *  @discussion 时时监听了蓝牙连接状态
 *
 *  @param bluetoothState 蓝牙状态
 */
- (void)uteManagerBluetoothState:(UTEBluetoothSate)bluetoothState;

/**
 *  @discussion 当第一次打开来电 QQ 微信 sms提醒功能时，系统会弹出对话框要求绑定（系统绑定）
 *   1.如设备已经绑定，系统是不会弹出对话框，且SDK无返回值
 *   2.如设备未绑定过，用户点击绑定（则设备与系统绑定），则返回YES：来电 QQ 微信 sms相对应的提醒有效；否则返回NO，全部无效，且硬件设备会主动断开，请开发者主动调用连接。
 *
 *  @param isAble 设备来电 QQ 微信 sms提醒是否有效
 */
- (void)uteManagerExtraIsAble:(BOOL)isAble;

/**
 *  @discussion 实时监听了设备步数变化 会频繁被调用
 *
 *  @param UTEModelRunData 今天总步数
 */
- (void)uteManagerReceiveTodaySteps:(UTEModelRunData *)runData;

/**
 *  @discussion 实时监听了设备睡眠记录变化
 *              如有新的睡眠记录，请先同步睡眠记录（因为要过滤是否在真正的睡觉），再查询历史睡眠记录
 *              最好早上同步睡眠数据，因为这时候睡眠数据才是完整的，而且同步睡眠需要时间比较久
 *
 *  @param isNewSleep 是否有新的睡眠数据
 */
- (void)uteManagerReceiveTodaySleeps:(BOOL)isNewSleep;

/**
 *  @discussion 同步设备数据进度
 *
 *  @param process 进度(0到100)
 */
- (void)uteManagerSyncProcess:(NSInteger)process;

/**
 *  @discussion 升级设备进度
 *
 *  @param process 进度(0到100)
 */
- (void)uteManagerUpdateProcess:(NSInteger)process;

/**
 *  @discussion 当设备UTEOptionOpenCameraMode拍照模式，每摇晃3次就回调一次
 *   退出拍照模式一定调用UTEOptionCloseCameraMode
 */
- (void)uteManagerTakePicture;

/**
 *  @discussion SDK对固件发送命令，如固件接收到值，将发送返回值给SDK，如SDK接收到值将回调；否则无
 */
- (void)uteManageUTEOptionCallBack:(UTECallBack)callback;
@end

#pragma mark - UTESmartBandClient 属性

typedef void(^cardApduResponseBlock)(NSData *data,BOOL success);

/*!
 *  UTESmartBandClient
 */
@interface UTESmartBandClient : NSObject

/**
*   SDK调试Log 默认false
*/
@property (nonatomic,assign ) BOOL  debugUTELog;
/**
 *  UTEManagerClient代理
 */
@property (nonatomic,weak   ) id<UTEManagerDelegate> delegate;
/**
 *  设备是否在同步数据（步数、睡眠、心率）
 */
@property (nonatomic,assign,readonly) BOOL  isSyncDevices;
/**
 *  设备是否在升级
 */
@property (nonatomic,assign,readonly) BOOL  isUpdateDevices;
/**
 *  设备是否在测试心率中
 */
@property (nonatomic,assign,readonly) BOOL  isHeartDetecting;
/** 
 *  是否正在改变设备特性
 */
@property (nonatomic,assign,readonly) BOOL  isChangeFeature;
/**
 *  已连接上设备模型,断开状态为 nil
 */
@property (nonatomic,strong,readonly) UTEModelDevices  *connectedDevicesModel;
/**
 *  设置要扫描指定的设备(蓝牙)名称,区分大小写,默认为 nil,扫描所有
 */
@property (nonatomic,copy  ) NSString    *filterName;
/**
 *  设置要扫描的设备信号范围强度以内（0 > filerRSSI > -100，默认-70）
 */
@property (nonatomic,assign) NSInteger    filerRSSI;
/** 
 *  设置是否重复扫描设备 默认NO
 */
@property (nonatomic,assign) BOOL         isScanRepeat;
/**
 *   设置为设备为交通卡手环
 */
@property (nonatomic,assign) BOOL         isCardDevices;
/** 
 *   Apdu通道是否打开 
 */
@property (nonatomic,assign,readonly) BOOL isOpenApdu;
/**
 *  Apdu通道返回的数据
 */
@property (nonatomic,copy) cardApduResponseBlock  cardApduResponseBlock;

#pragma mark - UTESmartBandClient 方法

/**
 *  @discussion 实例化
 *
 *  @return UTESmartBandClient实例
 */
+ (UTESmartBandClient *)sharedInstance;

/**
 *  @discussion 初始化UTESmartBandClient
 */
-(void)initUTESmartBandClient;

/**
 *  @discussion 扫描周围设备
 */
- (void)startScanDevices;

/**
 *  @discussion 停止扫描设备
 */
- (void)stopScanDevices;

/**
 *  @discussion 连接设备
 *
 *  @param model 要连接的设备属性模型 identifier 一定不为nil就行
 */
- (void)connectUTEModelDevices:(UTEModelDevices *)model;

/**
 *  @discussion 断开设备
 *
 *  @param model 要断开的设备属性模型 identifier 一定不为nil就行
 *
 *  @return 返回此方法是否真正被执行了
 *（蓝牙未打开、设备未连接 是可以执行；正在同步中、正在测试心率中、转化设备特性、Apdu交互中不执行）
 */
- (BOOL)disConnectUTEModelDevices:(UTEModelDevices *)model;

/**
 *  @discussion 设置设备特征
 *
 *  @param option 特征类型
 *
 *  @return 返回是否可以发送option, 或可先调用checkUTEDevicesStateIsEnable方法 检查此时是否给设置特征
 */
- (BOOL)setUTEOption:(UTEOption)option;

/**
 *  @discussion 设置设备闹钟
 *
 *  @param array 装有UTEModelAlarm 模型 最多3个
 *  @param count 闹钟震动次数 0-9次
 */
- (void)setUTEAlarmArray:(NSArray *)array vibrate:(NSInteger)count;

/**
 *  @discussion 设置打开设备久坐提醒 （设备自动识别如中午12点~14点与晚上睡眠 时间是不会提醒的）
 *
 *  @param remindTime 久坐多长时间就震动提醒 单位分钟 范围<10,180>
 */
- (void)setUTESitRemindOpenTime:(NSInteger)remindTime;

/**
 *  @discussion 设置关闭设备久坐提醒
 */
- (void)setUTESitRemindClose;

/**
 *  @discussion 设置设备里面身高、体重、亮屏时间
 *
 *  @param heigh  身高 UTEOptionUnitMeter 单位cm  范围格式 <91,240>
 *                身高 UTEOptionUnitInch 单位inch 范围格式 <3.00,7.11> 3尺00寸 ~ 7尺11寸 (小数点为11进制)
 
 *  @param weight 体重 UTEOptionUnitMeter 单位kg 范围格式 <20,150>
 *                体重 UTEOptionUnitInch 单位lb 范围格式 <44,333>
 *
 *  @param light  亮屏时间(秒) 范围<5,60>
 */
- (void)setUTEInfoHeigh:(CGFloat)heigh weight:(NSInteger)weight light:(NSInteger)sec;

/**
 *  @discussion 检查是否有新版本 回调uteManagerDevicesSate:error: 
 *              调试阶段运行一次App运行连续访问服务器5次
 */
- (void)checkUTEFirmwareVersion;

/**
 *  检查是否可以发送 UTEOption 设置
 *  设备在 未打开手机蓝牙、未连接设备、正在同步中、正在测试心率中、转化设备特性，返回false，设置是无效的，即设备不处理。
 *  例外：1.当设备是正在测试心率过程中，可以直接关闭心率UTEOptionHeartDetectingStop ，无需理会此返回值。
 *  注意：交通卡apdu信息交互中，以上UTEOption指令都无效，此方法返回false。
 *
 *  @return 返回值
 */
- (BOOL)checkUTEDevicesStateIsEnable;

/**
 *  @discussion 开始升级 升级中回调 uteManagerUpdateProcess:
 *                       升级失败或者成功回调 uteManagerDevicesSate:error:
 */
- (void)beginUpdateFirmware;

/**
 *  @discussion 改变设备特性
 *
 *  @param isSuccess 转换成功与否
 *
 *  @param isMustUpdate 是否必须强制升级（如果不升级，那么原来的功能将无法使用）
 *
 */
- (void)changeDeviveFeature:(void(^)(BOOL isSuccess,BOOL isMustUpdate))isSucess;

/**
 *  @discussion 获取当前SDK 版本
 *
 *  @return 版本号
 */
- (NSString *)sdkVersion;

#pragma mark - UTESmartBandClient 交通卡 方法
/**
 *  @discussion 关闭通道
 */
- (void)cardCloseApduChannel;
/**
 *  @discussion 发送数据到设备端
 *
 *  @param data 发送的数据
 */
- (void)cardApduSendData:(NSData *)data;


#pragma mark - 过时API,兼容以前版本,勿用
/*********************** 已过时(兼容以前版本) 勿用 ***********************/

- (void)allocateUTEData:(NSData *)data userInfo:(id)userInfo response:(BOOL)response;
@property (nonatomic,assign) BOOL  isOpenPhoneCall;

/******************************* 分割线  *********************************/



@end
