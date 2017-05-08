var exec = require('cordova/exec');

exports.scanDevice = function (arg0, success, error) {
  exec(success, error, "Smartband", "scanDevice", [arg0]);
};

/**
 *
 * @param time      扫描时间
 * @param success  返回 device
 * @param error
 */
exports.scan = function (time, success, error) {
  exec(success, error, "YoikScreenOrientation", "screenOrientation", time);
};
exports.stopScan = function (success, error) {
  exec(success, error);
};
/**
 *  设置闹钟数据模型
 * @param timeInfo {time:"",week:[0,1,2,3,4],num:1}
 * @param success
 * @param error
 */
exports.setAlarm = function (timeInfo, success, error) {

};
exports.setUTEOption = function (type, success, error) {

};
//SDK 对固件发送命令，如固件接收到值， 则将发送返回值给 SDK，如 SDK 接收到值将 回调方法 uteManageUTEOptionCallBack:， 否则无
exports.setUTECallBack = function (success, error) {

};
exports.registrationDeviceCallBack = function () {
  crodva.fireDocumetEven()
};
/**
 * 同步数据
 * @param success
 * @param error
 */
exports.syncRunData = function (success, error) {

};
exports.syncSleepData = function (success, error) {

};


device = {
  name: "设备名称",//NSString
  version: "设备版本：连接状态才有值",
  identifier: "设备唯一标识",
  isConnected: "设备连接状态",//BOOL
  battery: "设备电量",// ：连接状态才有值
  isHasExtra: flase,//设备额外功能支持： 来电、 QQ、微信、 SMS  连接上设备才有值， 也可具体咨询我司人员 BOOL
  isHasHRM: "设备是否支持心率， 具体咨询我司人员",//BOOL
  rssi: 90,// 设备信号强度 NSInteger
  address: "设备蓝牙地址",// NSData
  featureAnother: "",// 设备另外特性，只有连上设备才有实际值：不同的特性支持不同的功能， 请看 UTEDeviceFeature 枚举
  advertisementData: "设备未被连接时， 此属性有值， 否则为空" //UTEModelDevices
};

SmartBandOptions = {
  UTEOptionSyncAllStepsData: 0,        //同步设备所有步数
  UTEOptionSyncAllSleepData: 1,        //同步设备所有睡眠
  UTEOptionSyncAllData: 2,             //同步设备所有数据（ 步数+睡眠）
  UTEOptionSyncAllHRMData: 3,          //同步设备所有心率
  UTEOptionHeartDetectingStart: 4,     //开始测试心率
  UTEOptionHeartDetectingStop: 5,      //停止测试心率
  UTEOptionUnitInch: 6,                  //设置设备计量单位为 英制 磅
  UTEOptionUnitMeter: 7,               //设置设备计量单位为 公制 千克
  UTEOptionUnitInch_12: 8,             //设置设备计量单位为 英制 磅 时间 12 小时制 （ AM/PM）  如固件支持， 则带屏设备时间将显示 AM/PM
  UTEOptionUnitInch_24: 9,             //设置设备计量单位为 英制 磅 时间 24 小时制
  UTEOptionUnitMeter_12: 10,           //设置设备计量单位为 公制 千克 时间 12 制（ AM/PM）    如固件支持， 则带屏设备时间将显示 AM/PM
  UTEOptionUnitMeter_24: 11,           //设置设备计量单位为 公制 千克 时间 24 小时制
  UTEOotionTodaySteps: 12,//获取今天到现在为止的总步数
  UTEOptionIncall: 13,//来电指令：手机来电时可发送此枚举值,则设备震动
  UTEOptionHangup: 14,//挂断/接通： 可发送此枚举值,则设备立即停止震动
  UTEOptionSyncTime: 15,//同步当前手机时间
  UTEOptionFindBand: 16,//查找设备指令
  UTEOptionOpenRemindIncall: 17,//打开设备来电提醒 前提 isHasExtra = YES
  UTEOptionOpenRemindQQ: 18,//打开设备 QQ 提醒 前提 isHasExtra = YES
  UTEOptionOpenRemindWeixin: 19,//打开设备微信提醒 前提 isHasExtra = YES
  UTEOptionOpenRemindSms: 20,//打开设备 SMS 提醒 前提 isHasExtra = YES
  UTEOptionOpenRemindMore: 21,//打开设备更多提醒 前提 isHasExtra = YES 除了以上提醒， 手机里面所有允许系统通知的 App， 都 可以使得手环震动提醒(手环屏幕出现一个邮件图标
  UTEOptionCloseRemindIncall: 22,//关闭设备来电提醒 前提 isHasExtra = YES
  UTEOptionCloseRemindQQ: 23,//关闭设备 QQ 提醒 前提 isHasExtra = YES
  UTEOptionCloseRemindWeixin: 24,//关闭设备微信提醒 前提 isHasExtra = YES
  UTEOptionCloseRemindSms: 25,//关闭设备 SMS 提醒 前提 isHasExtra = YES
  UTEOptionOpenRemindMore: 26,//关闭设备更多提醒 前提 isHasExtra = YES
  UTEOptionOpenCameraMode: 27,//打开设备摇一摇拍照模式
  UTEOptionCloseCameraMode: 28,//关闭设备摇一摇拍照模式
  UTEOptionDeleteDevicesAllData: 29,// 清除设备所有数据
  UTEOptionReadDevicesBattery: 30,//读取设备电量
};
/*
 1） 如已连接设备 isHasExtra = NO，请使用 UTEOptionHangup/ UTEOptionHangup 设置，即
 自行监听来电， 但是 iOS9 系统以上已经不支持后台监听来电状态；
 2） 如已连接设备 isHasExtra = YES，请使用 UTEOptionOpenRemindIncall/
 UTEOptionCloseRemindIncall 设置设备属性，即无需监听来电。 设备 isHasExtra 属性， 在连
 接上设备才有值， 或请在申请 SDK 时候，向开发人员询问是否支持。
 注意：当 isHasExtra = YES， 且第一次打开提醒功能提醒时， 是需要用户允许绑定设备（系
 统自动弹出对话框要求系统绑定）； 如果需要解绑设备（系统已绑定的设备）， 请提醒用户手
 动去“系统设置”蓝牙选项里面找对应的设备点击“忽略设备”，否则下次 App 无法扫描到此设
 备， 而且来电或 iPhone 推送信息时， 设备可能仍然会震动提醒。
 当已经绑定了的手环（ 以前打开过来电/微信/QQ/SMS/更多提醒功能），会有几率在连
 接手环时候连接不上， 且此方法被重复调用 uteManagerDevicesSate: error: userInfo: 其中
 state= UTEDevicesSateDisconnected， error.code= UTEErrorCodeDisconnect（异常断开）， 如果被连续重复调用 3 次倍数以上，请开发者一定要提示用户手动去系统设置的蓝牙界面忽略手
 环（蓝牙名字会显示为之前已连接 UTEModelDevices 的 name 属性字符）， 否则会永远连接
 不上。
 3）当连接上设备时， SDK 会自动第一次读取设备电量。 之后如需要，请开发者自行调用查
 询电量 API， 查询更新当前电量。
 */