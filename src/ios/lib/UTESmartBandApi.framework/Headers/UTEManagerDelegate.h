//
//  UTEManagerDelegate.h
//  UTESmartBandApi
//
//  Created by VV on 2017/4/24.
//  Copyright © 2017年 vv. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "UTEDefine.h"

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
 *   2.如设备未绑定过，用户点击绑定（则设备与系统绑定），则返回YES：来电 QQ 微信 sms相对应的提醒有效；
 *                                             否则返回NO，全部无效，且硬件设备会主动断开，请开发者主动调用连接。但是RK平台设备不会断开
 *
 *  @param isAble 设备来电 QQ 微信 sms提醒是否有效
 */
- (void)uteManagerExtraIsAble:(BOOL)isAble;

/**
 *  @discussion 实时监听了设备步数变化 会频繁被调用
 *  当为运动模式的属性 isHasWalkRun=YES 时，将不会调用此方法，请用uteManagerReceiveTodaySport方法监听
 *
 *  @param runData 今天总步数模型
 */
- (void)uteManagerReceiveTodaySteps:(UTEModelRunData *)runData;

/**
 *  @discussion 实时监听了设备具有运动模式的步数变化 会频繁被调用
 *
 *  @param dict 只有2个键值:kUTEQuerySportWalkData kUTEQuerySportRunData
 */
- (void)uteManagerReceiveTodaySport:(NSDictionary *)dict;

/**
 *  @discussion 实时监听了设备睡眠记录变化
 *              如有新的睡眠记录，请先同步睡眠记录（因为要过滤是否在真正的睡觉），再查询历史睡眠记录
 *              最好早上同步睡眠数据，因为这时候睡眠数据才是完整的，而且同步睡眠需要时间比较久
 *
 *  @param isNewSleep 是否有新的睡眠数据
 */
- (void)uteManagerReceiveTodaySleeps:(BOOL)isNewSleep NS_DEPRECATED_IOS(2_0, 4_0,"deprecated UTE_SDK version 1.24 above");

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
 *  @discussion 通过UTEOptionReadDisplaySize 查询 回调此方法
 *
 *  @param width   设备屏分辨率 宽
 *  @param height  设备屏分辨率 高
 *  @param count   能切换的个数
 */
- (void)uteManagerDisplaySizeWidth:(NSInteger)width height:(NSInteger)height count:(NSInteger)count;

/**
 *  @discussion 通过readUTEIbeacon 读取ibeacon信息的回调
 */
- (void)uteManagerUTEIbeaconOption:(UTEIbeaconOption)option value:(NSString *)value;

/**
 *  @discussion SDK对固件发送命令，如固件接收到值，将发送返回值给SDK，如SDK接收到值将回调；否则无
 */
- (void)uteManageUTEOptionCallBack:(UTECallBack)callback;

@end
