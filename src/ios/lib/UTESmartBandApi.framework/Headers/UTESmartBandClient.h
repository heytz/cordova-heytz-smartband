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
#import "UTEManagerDelegate.h"

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
 *  设备是否在测试血压中
 */
@property (nonatomic,assign,readonly) BOOL  isBloodDetecting;
/** 
 *  是否正在改变设备特性（RK平台无此信息，无需考虑此属性）
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
 *   设备是否为RK平台手环(可事先问相关人员,是否有这设备)，设备断开情况下为false
 */
@property (nonatomic,assign,readonly) BOOL isRKDevices;
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
 *  @return value 返回此方法是否真正被执行了
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
- (void)setUTEAlarmArray:(NSArray<UTEModelAlarm *> *)array vibrate:(NSInteger)count;

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
 *  @discussion 设置设备里面身高、体重、亮屏时间、目标步数、抬手亮屏开关、心率警报值 如不设置，则距离和卡路里 可能全部为 0
 *              请先设置设备单位:公尺或英尺，然后再调用此方法；如之前设置过，SDK 会临时保存设备单位，可以不再调用设置单位(默认为UTEOptionUnitMeter)
 *
 *  @param heigh  身高 UTEOptionUnitMeter 单位cm  范围格式 <91,240>
 *                身高 UTEOptionUnitInch 单位inch 范围格式 <3.00,7.11> 3尺00寸 ~ 7尺11寸 (小数点为11进制)
 
 *  @param weight 体重 UTEOptionUnitMeter 单位kg 范围格式 <20,150>
 *                体重 UTEOptionUnitInch 单位lb 范围格式 <44,333>
 *
 *  @param sec     亮屏时间(秒) 范围<5,60>
 *
 *  @param sportTarget 有的设备支持显示一天的步数进度；如手环不支持，请填非0 值
 *
 *  @param handlight   抬手亮屏的开关 请查看isHasHandLight来判断是否支持此功能
 *
 *  @param maxHeart    超过最大心率值警报 请查看isHasMaxHeartAlert来判断是否支持此功能，关闭则填255
 *
 *  @return 返回以上参数是否有效
 */
- (BOOL)setUTEInfoHeigh:(CGFloat)heigh
                 weight:(NSInteger)weight
                  light:(NSInteger)sec
            sportTarget:(NSInteger)sportTarget
              handlight:(BOOL)handlight
               maxHeart:(NSInteger)maxHeart;

/**
 *  @discussion   设备心率每隔多长时间自动检测一次 有动静态心率切换的功能就有此功能
 *  
 *  @param isAuto 是否自动检测
 *
 *  @param time   每隔几小时检测一次 time范围 1~23
 */
- (void)setUTEHeartAuto:(BOOL)isAuto time:(NSInteger)time;

/***
 *  @discussion 发送密码 （请事先问相关人员 是否设备支持密码校验功能）
 *
 *  @param password 必须为4位长度的数字 如 @"1234"
 *
 *  @param type 密码类型，请看UTEPasswordType枚举
 */
- (void)sendUTEPassword:(NSString *)password type:(UTEPasswordType)type;

/***
 *  @discussion 客户自己定制的key设置，如有则必须每次第一次打开App 设置一次
 *
 *  @param key 如 @"90370abc1c1adc1a7d0439fb2cb7e522"
 */
- (void)setUTESDKKey:(NSString *)key;

/***
 *  @discussion 读取紫外线指数 （请事先问相关人员 是否设备具有紫外线功能）
 *
 *  @param result 指数 范围:0~15  对应的5个等级 0~2:最弱  3~5:弱  6~8:中等  9~11:强  12以上:很强
 *               不同等级的防嗮措施，请百度"紫外线指数"
 */
- (void)readUTEDeviceUV:(void(^)(NSInteger value))result;

/**
 *  @discussion 检查是否有新版本 回调uteManagerDevicesSate:error: 
 *              调试阶段运行一次App,可连续访问服务器5次,然后请重新运行App
 */
- (void)checkUTEFirmwareVersion;

/**
 *  @discussion 检查是否可以发送 UTEOption 等等对设备的设置
 *  设备在 未打开手机蓝牙、未连接设备、正在同步中、正在测试心率/血压中、转化设备特性，返回false，设置是无效的，即设备不处理。
 *
 *  例外：1.当设备是正在测试心率过程中，可以直接关闭心率UTEOptionHeartDetectingStop ，无需理会此返回值。
 *  例外：2.当设备是正在测试血压过程中，可以直接关闭心率UTEOptionBloodDetectingStop ，无需理会此返回值。
 *
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
 *   isMustUpdate 是否必须强制升级（如果不升级，那么原来的功能将无法使用）
 *
 */
- (void)changeDeviveFeature:(void(^)(BOOL isSuccess,BOOL isMustUpdate))isSuccess;

/**
 *  @discussion 勿打扰模式
 *
 *  @param type 表示除了后面时间范围限制之外 需要进入那些勿打扰
 *
 *  @param start 开始时间 24小时制 如@"08:30"
 *
 *  @param end   结束时间 24小时制 如@"23:05"
 *
 *  @param except Yes:如在08:30~23:05范围内所有的4个type都进入勿打扰，其他时间以前面的type为准。 No:表示不需要时间范围限制的勿打扰，一整天全部以前面的type为准
 */
- (void)sendUTEAllTimeSilence:(UTESilenceType)type exceptStartTime:(NSString *)start endTime:(NSString *)end except:(BOOL)except;

/**
 *  @discussion 设置设备7天内天气的显示
 *
 *  @param weatherArray 里面装有7天的天气情况，每一天都是一个UTEModelWeather模型
    请按照顺序放置，index 0 为第一天(今天) ... index 6 为第七天
    
    @return 返回数据是否正确 或者 是否可设置(可调用checkUTEDevicesStateIsEnable查看)
 */
- (BOOL)sendUTESevenWeather:(NSArray<UTEModelWeather*> *)weatherArray;

/**
 *  @discussion 设置设备2天内天气的显示 可先调用getUTEWeatherDataFormServer方法获取天气信息，或者使用其他方法获取到天气信息进行设置
 *
 *  @param todayType    查看 UTEWeatherType
 *  @param currentTemp  当前温度
 *  @param maxTemp      今天最高气温
 *  @param minTemp      今天最低气温
 *  @param pm25         今天PM2.5
 *  @param aqi          今天空气质量
 *
 *  @param tomorrowType 请查看 UTEWeatherType
 *  @param tmrMax       明天最高气温
 *  @param tmrMin       明天最低气温
 */
- (void)sendUTETodayWeather:(UTEWeatherType)todayType
                currentTemp:(NSInteger)currentTemp
                    maxTemp:(NSInteger)maxTemp
                    minTemp:(NSInteger)minTemp
                       pm25:(NSInteger)pm25
                        aqi:(NSInteger)aqi
               tomorrowType:(UTEWeatherType)tomorrowType
                     tmrMax:(NSInteger)tmrMax
                     tmrMin:(NSInteger)tmrMin;
/**
 *  @discussion 根据天气代号code(国内天气) 获取对应的天气类型
 *
 *  @param weatherCode 天气代号 如101
 *
 *  @return 天气类型
 */
- (UTEWeatherType)getUTEWeatherType:(NSInteger)weatherCode;

/**
 *  @discussion 获取天气信息 支持国内 (虽然兼容国外,但可能会获取不到)
 *
 *  @param cityID 城市代号 如@"CN101010100"或城市名 请看http://www.heweather.com/documents/city 找对应的城市
 *
 */
- (void)getUTEWeatherDataFormServer:(NSString *)cityID success:(void (^)(id))success failure:(void (^)(NSError *))failure;

/**
 *  @discussion 设备的显示方式 和 佩戴方式
 *
 *  @param wearType  佩戴方式
 *  @param sreenType 显示方式
 */
- (void)sendUTEWearType:(UTEWearType)wearType sreenType:(UTEDeviceSreenDisplayType)sreenType;

/**
 *  @discussion 设置ibeacon
 *
 *  @param option     设置类型
 *  @param dataString 数据 格式如下:
 
    UTEIbeaconOptionUUID:  数据范围(0~9 和 不区分大小写 a~f) 数据长度必须等于32
                                如@"a2b9c738cc9d846aef90639e0e4c9562";
    
    UTEIbeaconOptionMajor: 数据范围(0~65535) 的数字 如@"55365"
 
    UTEIbeaconOptionMinor:  数据范围(0~65535) 的数字 如@"65"
    
    UTEIbeaconOptionName:   数据范围(0~9 和 区分大小写 a~Z 和键盘上的英文符号) 数据长度最长为14
                                如@"UTE_001"
    UTEIbeaconOptionTXPower: 数据范围(1~254) 的数字 如@"55"
    
    UTEIbeaconOptionAdvertisingInterval: 数据范围(1~20) 的数字 如@"5" (单位100毫秒) 表示 5*100 = 500毫秒
 
 *  return 返回数据格式是否正确 或者 是否可设置(可调用checkUTEDevicesStateIsEnable查看)
 */
- (BOOL)sendUTEIbeacon:(UTEIbeaconOption)option dataString:(NSString *)dataString;

/**
 *  @discussion 获取当前ibeacon数据
 *
 *  @param option     设置类型
 */
- (void)readUTEIbeacon:(UTEIbeaconOption)option;
/**
 *  @discussion 获取当前SDK 版本
 *
 *  @return 版本号 此版本为@"1.25"
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
