var cordova = require('cordova');
var exec = require('cordova/exec');
var SmartBand = function () {
};
SmartBand.prototype.onServerCallback = {};
/**
 * 手机server监听
 * @type {{}}
 */
SmartBand.prototype.onServiceStatuslt = {};
SmartBand.prototype.heytzICallback = {};
SmartBand.prototype.onStepChange = {};
/**
 * IOS 下 实时监听了设备睡眠记录变化 只会返回true 或者 false
 * 如有新的睡眠记录，请先同步睡眠记录（因为要过滤是否在真正的睡觉），再查询历史睡眠记录
 * 最好早上同步睡眠数据，因为这时候睡眠数据才是完整的，而且同步睡眠需要时间比较久
 * @type {{}}
 */
SmartBand.prototype.onSleepChange = {};
SmartBand.prototype.onUTEOptionCallBack = {};

/**
 * 固件升级访问服务器回调类
 * @param data
 */
SmartBand.prototype.openOnServerCallback = function (data) {
  this.onServerCallback = data;
  cordova.fireDocumentEvent('SmartBand.onServerCallback', this.onServerCallback)
};
/**
 * 监听设备通讯
 * @param data
 */
SmartBand.prototype.openOnServiceStatuslt = function (data) {
  this.onServiceStatuslt = data;
  cordova.fireDocumentEvent('SmartBand.onServiceStatuslt', this.onServiceStatuslt)
};
/**
 * 监听设备通讯
 * @param data
 */
SmartBand.prototype.openHeytzICallback = function (data) {
  data = JSON.stringify(data);
  this.heytzICallback = JSON.parse(data);
  cordova.fireDocumentEvent('SmartBand.heytzICallback', this.heytzICallback)
};
/**
 * 监听步数变化
 * @param data
 */
SmartBand.prototype.openOnStepChange = function (data) {
  data = JSON.stringify(data);
  this.onStepChange = JSON.parse(data);
  cordova.fireDocumentEvent('SmartBand.onStepChange', this.onStepChange)
};
/**
 * 监听睡眠
 */
SmartBand.prototype.openOnSleepChange = function () {
  cordova.fireDocumentEvent('SmartBand.onSleepChange', this.onSleepChange)
};
/**
 * 设备Option设置的CallBack，只在IOS上面存在
 */
SmartBand.prototype.uteManageUTEOptionCallBack = function () {
  cordova.fireDocumentEvent('SmartBand.onUTEOptionCallBack', this.onUTEOptionCallBack)
};

SmartBand.prototype.errorCallback = function (msg) {
  console.log('Javascript Callback Error: ' + msg)
};

SmartBand.prototype.callNative = function (name, args, successCallback, errorCallback) {
  exec(successCallback, errorCallback, 'SmartBand', name, args);
};
/**
 * 初始化，初始化方法只是为了实现类的初始化。
 * @param success
 * @param error
 */
SmartBand.prototype.init = function (success, error) {
  this.callNative("init", [], success, error);
};
/**
 * 检查蓝牙是否开启
 * @param success
 * @param error
 */
SmartBand.prototype.isEnabled = function (success, error) {
  this.callNative("isEnabled", [], success, error);
};
/**
 * 检查是否可以发送 UTEOption 等等对设备的设置
 * @param success 设备在未打开手机蓝牙、未连接设备、正在同步中、正在测试心率/血压中、转化设备特性，返回false，设置是无效的，即设备不处理。
 * @param error
 */
SmartBand.prototype.checkUTEDevicesStateIsEnable = function (success, error) {
  this.callNative("checkUTEDevicesStateIsEnable", [], success, error);
};
/**
 * 是否支持BLE4.0
 * @param success
 * @param error
 */
SmartBand.prototype.isSupported = function (success, error) {
  this.callNative("isSupported", [], success, error);
};
/**
 * 扫描设备
 * @param time      扫描时间
 * @param success  返回 device
 * @param error
 */
SmartBand.prototype.scan = function (time, success, error) {
  this.callNative("scan", [time], success, error);
};
/**
 * 停止扫描
 * @param success
 * @param error
 */
SmartBand.prototype.stop = function (success, error) {
  this.callNative("stop", [], success, error);
};
/**
 * 连接设备
 * @param address
 * @param success
 * @param error
 */
SmartBand.prototype.connect = function (address, success, error) {
  this.callNative("connect", [address], success, error);
};
/**
 * 断开设备
 * @param success
 * @param error
 */
SmartBand.prototype.disConnect = function (success, error) {
  this.callNative("disConnect", [], success, error);
};
/**
 * 同步时间
 * @param success
 * @param error
 */
SmartBand.prototype.syncBLETime = function (success, error) {
  this.callNative("syncBLETime", [], success, error);
};
/**
 * 获取版本号
 * @param success
 * @param error
 */
SmartBand.prototype.sendToReadBLEVersion = function (success, error) {
  this.callNative("sendToReadBLEVersion", [], success, error);
};
/**
 * 读取电量
 * @param success
 * @param error
 */
SmartBand.prototype.sendToReadBLEBattery = function (success, error) {
  this.callNative("sendToReadBLEBattery", [], success, error);
};
/**
 *  设置闹钟数据模型
 * @param whichClock
 * @param weekPeroid
 * @param hour
 * @param minute
 * @param isOpen
 * @param shakePeriod
 * @param success
 * @param error
 */
SmartBand.prototype.sendToSetAlarmCommand = function (whichClock, weekPeroid, hour, minute, isOpen, shakePeriod, success, error) {
  this.callNative("sendToSetAlarmCommand", [whichClock, weekPeroid, hour, minute, isOpen, shakePeriod], success, error);
};
/**
 * 设置身高体重
 * @param height 身高(cm)
 * @param weight 体重（kg）
 * @param offScreenTime 灭屏时间(秒)
 * @param stepTask  目标步数
 * @param isRraisHandbrightScreenSwitchOpen//抬手亮屏开关 true 为开，false 为关
 * @param isHighestRateOpen //最高心率 醒，true 为开，false 为关
 * @param highestRate       //最后一个参数为最高心率 醒 的值。
 * @param success
 * @param error
 */
SmartBand.prototype.sendStepLenAndWeightToBLE = function (height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate, success, error) {
  this.callNative("sendStepLenAndWeightToBLE", [height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate], success, error);
};
/**
 * 久坐提醒
 * @param success
 * @param error
 */
SmartBand.prototype.sendSedentaryRemindCommand = function (flag, miuntes, success, error) {
  this.callNative("sendSedentaryRemindCommand", [flag, miuntes], success, error);
};
/**
 * 摇摇功能(之后发现设备被摇一摇时，会在 ICallback 中返回状态， ICallbackStatus.DISCOVERY_DEVICE_SHAKE)，常用于摇摇拍照等功能的实 现。
 * @param success
 * @param error
 */
SmartBand.prototype.shakeMode = function (state, success, error) {
  this.callNative("shakeMode", [state], success, error);
};
/**
 * 查找手环
 * @param vibrationCount  手环震动次数
 * @param success
 * @param error
 */
SmartBand.prototype.findBand = function (vibrationCount, success, error) {
  this.callNative("findBand", [vibrationCount], success, error);
};
/**
 * 清除设备所有数据，即设备恢复出厂设置
 * @param success
 * @param error
 */
SmartBand.prototype.deleteDevicesAllData = function (success, error) {
  this.callNative("deleteDevicesAllData", [], success, error);
};
/**
 * 同步计步数据(连上设备后，请同步一次步数(实际是在设置时间后，同步步 数);同步完成前，请不要进行其他任何的通信工作)
 * @param success
 * @param error
 */
SmartBand.prototype.syncAllStepData = function (success, error) {
  this.callNative("syncAllStepData", [], success, error);
};
/**
 * 新一天初始化计步数据库
 * @param success
 * @param error
 */
SmartBand.prototype.updateStepSQL = function (success, error) {
  this.callNative("updateStepSQL", [], success, error);
};
/**
 * 查询一天的总步数
 * @param queryDate String queryDate 查询的日期 如 20150603
 * @param success int
 * @param error
 */
SmartBand.prototype.queryStepDate = function (queryDate, success, error) {
  this.callNative("queryStepDate", [queryDate], success, error);
};
/**
 * 查询一天的步数、距离、卡路里
 * @param queryDate String queryDate 查询的日期 如 20150603
 * @param success StepInfo 返回步数、距离、卡路里的集合
 * @param error
 */
SmartBand.prototype.queryStepInfo = function (queryDate, success, error) {
  this.callNative("queryStepInfo", [queryDate], success, error);
};
/**
 * 查询某一天各小时步数(请参考 StepOneHourInfo 类)
 * @param Calendar Calendar 查询的日期
 * @param success List<StepOneHourInfo> ，返回各小时和步数集合
 * @param error
 */
SmartBand.prototype.queryOneHourStepSQL = function (Calendar, success, error) {
  this.callNative("queryOneHourStepSQL", [Calendar], success, error);
};
/**
 * 同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
 * @param success
 * @param error
 */
SmartBand.prototype.syncAllSleepData = function (success, error) {
  this.callNative("syncAllSleepData", [], success, error);
};
/**
 * 查询一天的睡眠总时间
 * @param queryDate queryDate 查询的日期
 * @param success int 返回睡眠时间，单位为分钟
 * @param error
 */
SmartBand.prototype.querySleepDate = function (queryDate, success, error) {
  this.callNative("querySleepDate", [queryDate], success, error);
};
/**
 * 查询一天的睡眠详情(请参考 SleepTimeInfo 类)
 * @param calendar calendar 某 天日期(日期格式:如“20150101”)
 * @param success SleepTimeInfo 返回某天睡眠时间、深睡、浅睡、清醒时间、睡眠状态、睡眠 状态下持续时间、睡眠状态结束时间点集合
 * @param error
 * @constructor
 */
SmartBand.prototype.querySleepInfo = function (calendar, success, error) {
  this.callNative("querySleepInfo", [calendar], success, error);
};
/**
 * 读取线损值
 * @param success
 * @param error
 */
SmartBand.prototype.readRssi = function (success, error) {
  this.callNative("readRssi", [], success, error);
};
/**
 * 判断平台
 * @param success true :RK平台;false:dialog平台
 * @param error
 */
SmartBand.prototype.isRKPlatform = function (success, error) {
  this.callNative("isRKPlatform", [], success, error);
};
/**
 * 获取新版本的版本号
 * @param success 返回“no new version”或者返回从服务器获取到的固件版本号(升级的版本)
 * @param error
 */
SmartBand.prototype.getServerBtImgVersion = function (success, error) {
  this.callNative("getServerBtImgVersion", [], success, error);
};
/**
 * 获取新版本的版本号。 示:RK 平台才有 patch 版本号。
 * @param success 返回“no new version”或者返回从服务器获取到的 patch 版本号(升级的版本)
 * @param error
 */
SmartBand.prototype.getServerPatchVersion = function (success, error) {
  this.callNative("getServerPatchVersion", [], success, error);
};
/**
 * 查询设备升级属性 (升级前必须调用查询)
 * @param success
 * @param error
 */
SmartBand.prototype.queryDeviceFearture = function (success, error) {
  this.callNative("queryDeviceFearture", [], success, error);
};
/**
 * 同步所有数据   仅 IOS
 * @param success
 * @param error
 */
SmartBand.prototype.syncAllData = function (success, error) {
  this.callNative("syncAllData", [], success, error);
};
/**
 * 检查是否可以发送   仅 IOS
 * @param success
 * @param error
 */
SmartBand.prototype.checkUTEDevicesStateIsEnable = function (success, error) {
  this.callNative("checkUTEDevicesStateIsEnable", [], success, error);
};

//-------------------------下面接口暂时不实现----------------------
/**
 * 设置闹铃震动次数，暂时不实现
 * @param success
 * @param error
 */
SmartBand.prototype.setUTEAlarmArray = function (success, error) {
  this.callNative("setUTEAlarmArray", [], success, error);
};
/**
 * 设置身高单位
 * @param success
 * @param error
 */
SmartBand.prototype.setHeighUnit = function (success, error) {
  this.callNative("setHeighUnit", [], success, error);
};
/**
 * 设置体重单位
 * @param success
 * @param error
 */
SmartBand.prototype.setWeightUnit = function (success, error) {
  this.callNative("setWeightUnit", [], success, error);
};

var device = {
  name: "设备名称",//NSString
  version: "设备版本：连接状态才有值",
  identifier: "设备唯一标识",
  isConnected: "设备连接状态",//BOOL
  battery: "设备电量",// ：连接状态才有值
  isHasExtra: false,//设备额外功能支持： 来电、 QQ、微信、 SMS  连接上设备才有值， 也可具体咨询我司人员 BOOL
  isHasHRM: "设备是否支持心率， 具体咨询我司人员",//BOOL
  rssi: 90,// 设备信号强度 NSInteger
  address: "设备蓝牙地址",// NSData
  featureAnother: "",// 设备另外特性，只有连上设备才有实际值：不同的特性支持不同的功能， 请看 UTEDeviceFeature 枚举
  advertisementData: "设备未被连接时， 此属性有值， 否则为空" //UTEModelDevices
};
//仅IOS 返回设备 options的操作状态
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
  UTEOptionCloseRemindMore: 26,//关闭设备更多提醒 前提 isHasExtra = YES
  UTEOptionOpenCameraMode: 27,//打开设备摇一摇拍照模式
  UTEOptionCloseCameraMode: 28,//关闭设备摇一摇拍照模式
  UTEOptionDeleteDevicesAllData: 29,// 清除设备所有数据
  UTEOptionReadDevicesBattery: 30,//读取设备电量
};
GlobalVariable = {
  //发送久坐提醒功能开启/关闭指令以及 醒周期 begin
  CLOSE_SEDENTARY_REMIND: 0,
  OPEN_SEDENTARY_REMIND: 1,
  //发送久坐 醒功能开启/关闭指令以及 醒周期 end
  FIRST_CLOCK: 1,//第一个闹钟
  SECOND_CLOCK: 2,//第二个闹钟
  THIRD_CLOCK: 3,//第三个闹钟


  // 轻型数据库名字
  SettingSP: "SettingSP",
  //蓝牙连接状态 ，SharedPreferences KEY值
  BLE_CONNECTED_SP: "ble_connected",
  // 上一次连接的蓝牙地址 ，SharedPreferences KEY值
  LAST_CLICK_DEVICE_ADDRESS_SP: "last_click_device_address", //当天已保存的步数，SharedPreferences KEY值
  CURRENT_DAY_SAVED_STEP_COUNT: "current_day_saved_step_count",
  // 今天的步数，临时存储而已方便更新今天界面而已，步数一更新就变了，SharedPreferences KEY值
  YC_PED_CURRENT_HOUR_STEPS_SP: "current_hour_steps", //今天的步数，临时存储而已方便更新今天界面而已，步数一更新就变了，SharedPreferences KEY值
  YC_PED_STEPS_SP: "steps",
  //没用到，SharedPreferences KEY值
  YC_PED_PACE_SP: "pace",
  // 今天的路程，临时存储而已方便更新今天界面而已，步数一更新就变了，SharedPreferences KEY值
  YC_PED_DISTANCE_SP: "distance",
  //没用到，SharedPreferences KEY值
  YC_PED_SPEED_SP: "speed",
  // 今天的卡路里，临时存储而已方便更新今天界面而已，步数一更新就变了，SharedPreferences KEY 值
  //当前小时的步数，如当前时间是10:42分，则表示10:00~10:42分的步数，SharedPreferences KEY 值
  YC_PED_UNFINISH_HOUR_STEP_SP: "unfinish_hour_step",
  // 当前小时值，SharedPreferences KEY值
  YC_PED_UNFINISH_HOUR_VALUE_SP: "unfinish_hour_value", // 实时计步时，上一条计步数据来时的步数，SharedPreferences KEY值
  YC_PED_LAST_HOUR_STEP_SP: "last_hour_step", //实时计步时，上一条计步数据来时的小时数，SharedPreferences KEY值
  YC_PED_LAST_HOUR_VALUE_SP: "last_hour_value", //设置BLE步长和体重的广播ACTION
  SET_BLE_STEP_LENGTH_WEIGHT: "set_ble_step_length_weight",
  BLE_DISCONNECT_BINDDEVICE_ACTION: "ble_disconnect_binddevice_action",
  CIRCLE_BTN_TYPE: "circle_btn_type", // 个人信息 年龄，SharedPreferences KEY值
  PERSONAGE_AGE: "personage_age_sp", //个人信息 步长，SharedPreferences KEY值
  PERSONAGE_STEP_LENGTH: "step_length", // 个人信息 身高，SharedPreferences KEY值
  PERSONAGE_HEIGHT: "personage_height", //个人信息 体重，SharedPreferences KEY值
  PERSONAGE_WEIGHT: "body_weight", //上一次同步计步数据结束帧的日期，SharedPreferences KEY值
  B2FD_CALENDAR_SP: "b2fd_calendar_sp", //上一次同步睡眠数据结束帧的日期，SharedPreferences KEY值
  B3FD_CALENDAR_SP: "b3fd_calendar_sp",
  RSSI_SP: "rssi_sp",
  BEL_BATTERY_VALUE_SP: "ble_battery_value",
  BLE_STEP_STATUS_SP: "ble_step_status",
  BLE_SLEEP_STATUS_SP: "ble_sleep_status",
  STEP_MODE_SP: "step_mode",
  IMG_LOCAL_VERSION_NAME_SP: "img_local_version_name",
  BLE_CALENDAR_SP: "ble_step_calendar",
// 同步睡眠数据广播
  SLEEP_ALL_DATA_ACTION: "sleep_all_data_action",
// 同步计步数据广播
  STEP_ALL_DATA_ACTION: "step_all_data_action",
  ONLY_SET_OFF_SCREEN_TIME: "only_set_off_screen_time",
  OFF_SCREEN_TIME: "off_screen_time",
  LAST_DAY_NUMBER_SP: "last_day_number",
  LAST_DAY_CALLENDAR_SP: "last_day_calendar",
  FIRST_OPEN_APK: "first_open_apk",
  LAST_REFRESH_TIME: "last_refresh_time", //运动详情 上一次刷新时间
  LAST_REFRESH_PHONE_MINUTE: "last_refresh_phone_minute",//上一次刷 新时的手机分钟数
  LAST_REFRESH_STEP: "last_refresh_step",//上一次刷新时的步数
  READ_BATTERY_ACTION: "read_battery_action",
  READ_BLE_VERSION_ACTION: "read_ble_version_action",
  SEND_DEVICE_INFO_ACTION: "send_device_info_action",
  QQType: 1,
  WeChatType: 2,
  PhoneType: 2,
  SmsType: 3,
  EXTRA_RSSI: "RSSI",
  EXTRA_RSSI_STATUS: "RSSI_STATUS",
  INTENT_BLE_VERSION_EXTRA: "get_ble_version",
  INTENT_BLE_BATTERY_EXTRA: "get_ble_battery",
  /**
   * Handler Message * */
  GET_RSSI_MSG: 10,
  REFRESH_UI_MSG: 11,
  NEEDLESS_REFRESH_UI_MSG: 12,
  /**
   * Alarm clock */
//peroid
  ALARM_INVALID: 0x00,
  SUNDAY: 0x01,
  MONDAY: 0x02,
  TUESDAY: 0x04,
  WEDNESDAY: 0x08,
  THURSDAY: 0x10,
  FRIDAY: 0x20,
  SATURDAY: 0x40,
  EVERYDAY: 0x7F, //which clock
  // FIRST_CLOCK: 1,
  // SECOND_CLOCK: 2,
  // THIRD_CLOCK: 3,

  //update status
  OLD_VERSION_STATUS: 1,//当前是旧版本状态，允许升级
  FREQUENT_ACCESS_STATUS: 2,//频繁访问服务器状态
  NEWEST_VERSION_STATUS: 3,//当前已是最新版本状态
  ACCESS_VERSER_STATUS: 4,//正在访问服务器
  //rate
  RATE_TESTING: 0,//心率测试中
  RATE_TEST_FINISH: 1,//心率测试完成
  RATE_TEST_START: 2,//开始心率测试
  RATE_TEST_STOP: 3,//停止心率测试
  //sedentary remind
//   OPEN_SEDENTARY_REMIND: 1,//打开久坐 醒
//   CLOSE_SEDENTARY_REMIND: 0,//关闭久坐 醒


  DEVICE_FEATURE_MSEEAGE: "device_feature_message",//设备升级属性是 推送功能
  DEVICE_FEATURE_UPDATE: "device_feature_update",//设备升级属性是升 级功能
  DEVICE_FEATURE_WECHAT: "device_feature_wechat",//设备升级属性是微 信排行
  DEVICE_FEATURE_KEY: "device_feature_key",
  CHANGE_DEVICE_FEATURE_SUCCESS_ACTION: "change_device_feature_success_action",
  BLUETOOTH_REBOOT_SUCCESS_KEY: "bluetooth_reboot_success_key",
  BLUETOOTH_REBOOT_SUCCESS_ACTION: "bluetooth_reboot_success_action",
  DEVICE_FEATURE_IS_INVALID: "device_feature_is_invalid",
  FIRST_FEATURE: 1,
  SECOND_FEATURE: 2,
  UPDATE_BLE_PROGRESS_MSG: 103,//固件升级进度百分比
  ACTION_GATT_CONNECT_FAILURE: "bluetooth.le.ACTION_GATT_FAILURE",
  IS_METRIC_UNIT_SP: "is_metric_unit_sp",//公英制单位KEY
  UV_VALUE_SP: "uv_value_sp",//UV紫外线KEY
  RATE_STATIC: 1, //静态心率
  RATE_DYNAMIC: 2,//动态心率
  TYPE_PHONE: 0,//消息内容类型 推送来电名字和号码
  TYPE_QQ: 1,//消息内容类型 昵称和内容
  TYPE_WECHAT: 2,//消息内容类型
  TYPE_SMS: 3,//消息内容类型 来短信名字、号码、内容
// RK 固件升级
// patchDownLaodAddresses,
  patchServiceVersionCode: "",
  BleAndPatchAllHasNews: false,
  BleHasNews: false,
  PatchHasNews: false,
  updateCount: 0,
  BLE_UPDATE_AGAIN: "ble_update_again",
  BLE_PATCH_DOWNLOAD_ADDR_SP: "ble_patch_download_addr",
  PATH_LOCAL_VERSION_NAME_SP: "path_local_version_name",
  PASSWORD_TYPE_SET: 1,//设置密码
  PASSWORD_TYPE_INPUT: 2,//输入密码
  PASSWORD_TYPE_INPUT_AGAIN: 3,//重新输入密码
//IS_SUPPORT_FULL_FONT : false,//是否是全字库(删除，用GetFunctionList.isSupportFunction 判断)


  SMS_RECEIVED_NUMBER: "sms_received_number",
  /*
   * 个人信息 性别，SharedPreferences KEY 值，boolean true 为男，false 为女
   */
  publicstaticfinalStringPERSONAGE_GENDER: "personage_gender_sp",//个人信息 性别
  LAST_BLOOD_PRESSURE_CALENDAR_SP: "last_blood_pressure_calendar_sp",
  BLOOD_PRESSURE_TEST_STOP: 0,//停止血压测试
  BLOOD_PRESSURE_TEST_START: 1,//开始血压测试
  BLOOD_PRESSURE_TESTING: 3,//血压测试中
  BLOOD_PRESSURE_TEST_FINISH: 4,//血压测试完成
  CHARACTERISTIC_FUNCTION_LIST_SP: "characteristic_function_list_sp",
  IS_SUPPORT_PASS_WORD_PAIR: 0x01, // 密码配对
  IS_SUPPORT_WEATHER_FORECAST: 0x02, // 天气预报
  IS_SUPPORT_MULTIPLE_LANGUAGE: 0x04, // 多国语言
  IS_SUPPORT_Do_NOT_DISTURB: 0x08, // 勿扰
  IS_SUPPORT_SWIMMING: 0x10, // 游泳
  IS_SUPPORT_HOR_VER: 0x20, // 横竖屏
  IS_SUPPORT_RAISE_HAND_BRIGHT: 0x40, // 抬手亮屏开关
  SCREEN_VERTICAL: 1,//竖屏
  SCREEN_HORIZONTAL: 2,//横屏
  WEATHER_FORECAST_SWITCH_SP: "weather_forecast_switch_sp",
  WEATHER_FORECAST_ACTION: "weather_forecast_action",
  WEATHER_FORECAST_TODAY_WEATHER: "todayWeather",
  WEATHER_FORECAST_TODAY_CURRENT_TMP: "todayCurrentTmp",
  WEATHER_FORECAST_TODAY_TMP_MAX: "todayTmpMax",
  WEATHER_FORECAST_TODAY_TMP_MIN: "todayTmpMin",
  WEATHER_FORECAST_TODAY_PM25: "todayPM25",
  WEATHER_FORECAST_TODAY_AQI: "todayAqi",
  WEATHER_FORECAST_TOMORROW_WEATHER: "tommorrowWeather",
  WEATHER_FORECAST_TOMORROW_TMP_MAX: "tommorrowTmpMax",
  WEATHER_FORECAST_TOMORROW_TMP_MIN: "tommorrowTmpMin",//(新)
  SERVER_IS_BUSY: 201,//访问服务器回调状态,服务器忙
  SERVER_CALL_BACK_SUCCESSFULL: 202,//访问服务器回调状态,服 务连接正常,已获取到固件版本
  UNIT_TYPE_METRICE: 1,// 公制单位 UNIT_TYPE_IMPERIAL : 2,// 英制单位

  HOUR_FORMAT_24: 1,// 24小时制
  HOUR_FORMAT_12: 2,// 12 小时制
  IS_SUPPORT_DIAL_SWITCH: 0x800, // 判断是否支持表盘切换和 左右手切换功能
  IS_SUPPORT_IBEACON: 0x1000, // 判断是否支持ibeacon这个功 能
  IS_SUPPORT_SEVEN_DAYS_WEATHER: 0x2000, // 判断是否支持 七 天天气(新)
  IS_SUPPORT_SEDENTARY_REMINDER: 0x10000, // 支持久坐 醒 功能Support sedentary reminder
  IS_SUPPORT_THREE_ALARM_CLOCK: 0x20000, // 支持多个闹钟(三 个)
  IS_SUPPORT_TRANSACTION_REMINDER: 0x40000, // 支持事务  醒 Support for transaction reminders
  publicstaticfinalintIBEACON_TYPE_UUID: 1,//Ibeacon 指令类型,设置UUID/获取UUID
  IBEACON_TYPE_MAJOR: 2,// Ibeacon 指令类型,设置major/获取 major
  IBEACON_TYPE_MINOR: 4,// Ibeacon 指令类型,设置minor/获取 minor
  IBEACON_TYPE_DEVICE_NAME: 8,// Ibeacon 指令类型,设置蓝牙 device name/获取蓝牙device name(新)
  IBEACON_TYPE_TX_POWER: 16,// Ibeacon 指令类型,设置蓝牙 TX_POWER/获取蓝牙TX_POWER
  IBEACON_TYPE_ADVERTISING_INTERVAL: 32,// Ibeacon 指令类 型,设置蓝牙 advertising interval/获取蓝牙 advertising interval
  IBEACON_SET: 0,// Ibeacon 设置(设置UUID/设置major,设置 minor,设置蓝牙device name)
  IBEACON_GET: 1,// Ibeacon 获取(设置UUID/设置major,设置 minor,设置蓝牙device name)
  LEFT_HAND_WEAR: 0,// 左手佩戴 Left hand wear
  RIGHT_HAND_WEAR: 1,// 右手佩戴 Right hand wear
  NOT_SET_UP: 0xff,// 不设置
  SHOW_HORIZONTAL_SCREEN: 0,// 显示横屏 Show horizontal screen
  SHOW_VERTICAL_ENGLISH_SCREEN: 1,// 显示竖屏英文界面
  SHOW_VERTICAL_CHINESE_SCREEN: 2,// 显示竖屏中文界面
};
//仅Android 返回设备的操作状态
ICallBackSatatus = {
  REAL_TIME_STEP: 0,//当前属于实时步数操作
  OFFLINE_STEP_SYNCING: 1,//离线步数同步中
  OFFLINE_STEP_SYNC_OK: 2,//离线步数同步完成
  REAL_TIME_SLEEP: 3,//当前属于实时睡眠操作
  OFFLINE_SLEEP_SYNCING: 4,//离线睡眠同步中
  OFFLINE_SLEEP_SYNC_OK: 5,//离线睡眠同步完成
  SYNC_TIME_OK: 6,//设置时间操作完成
  SION_OK: 7,//获取设备版本号操作完成
  SET_STEPLEN_WEIGHT_OK: 8,//设置身高体重操作完成
  GET_SPORT_STATUS_OK: 9,//获取运动状态(计步或睡眠)操作完成
  GET_BLE_BATTERY_OK: 10,//获取电量操作完成
  PRESS_DEVICE_BUTTON: 11,//按下设备按钮操作
  SEND_INCALL_OR_SMS_NAME_OK: 12,//发送来电或短信用户名字操作完成
  SEND_INCALL_NUMBER_OK: 13,//发送来电号码操作完成
  SEND_SMS_NUMBER_OK: 14,//发送短信号码操作完成
  SEND_OFFHOOK_OK: 15,//挂断/接听电话操作完成
  SEND_QQ_COMMAND_OK: 16,//发送QQ指令操作完成
  SEND_WECHAT_COMMAND_OK: 17,//发送微信指令操作完成
  OPERATION_FAILE: 18,//操作失败
  DISCONNECT_STATUS: 19,//未连接/连接失败/断开连接
  CONNECTED_STATUS: 20,//已连接
  DISCOVERY_DEVICE_SHAKE: 21,//发现设备摇一摇(常用于摇摇拍照)

  OFFLINE_RATE_SYNCING: 22,//离线心率同步中
  OFFLINE_RATE_SYNC_OK: 23,//离线心率同步完成
  RATE_TEST_FAILE: 24,//心率测试失败
  SEDENTARY_REMIND_OPEN: 25,//久坐 醒已打开
  SEDENTARY_REMIND_CLOSE: 26,//久坐 醒已关闭
  SET_METRICE_OK: 27,//设置公制单位成功
  SET_INCH_OK: 28,//设置英制单位成功
  SET_FIRST_ALARM_CLOCK_OK: 29,//设置第1个闹钟OK
  SET_SECOND_ALARM_CLOCK_OK: 30,//设置第2个闹钟OK
  SET_THIRD_ALARM_CLOCK_OK: 31,//设置第 3 个闹钟 OK

  OPEN_CHANNEL_OK: 32,//打开通道OK
  CLOSE_CHANNEL_OK: 33,//关闭通道OK
  BLE_DATA_BACK_OK: 34, //测试通道 OK，通道正常
  GET_UV_BACK_OK: 35, //读取UV紫外线OK
  SEND_QQ_WHAT_SMS_CONTENT_OK: 36, //发送QQ、微信、短信内容OK
  SEND_PHONE_NAME_NUMBER_OK: 37, //发送来电名字和号码 OK
  IS_SUPPOERT_PUSH_CONTENT: 38, //调用sendKeyReadIsHasContentPush查询是否支持内容推送后，如果有这个返回值，则表示支持内容推送

  BLE_SERVICE_START_OK: 39, //BluetoothLeService 服务开启完 成后回调.前 是:需在 BluetoothLeService 服务开启完成前设置监听，否则无回调
  PASSWORD_SET: 40, //没设置过密码，请设置 4 位数字密码
  PASSWORD_INPUT: 41, //已设置过密码，请输入已设置的 4 位数字 密码
  PASSWORD_AUTHENTICATION_OK: 42, //验证成功或者设置密码成 功
  PASSWORD_INPUT_AGAIN: 43, //验证失败或者设置密码失败，请重 新输入 4 位数字密码，如果已设置过密码，请输入已设置的密码
  OFFLINE_SWIM_SYNCING: 44,//游泳数据同步中
  OFFLINE_SWIM_SYNC_OK: 45,//游泳数据同步完成
  OFFLINE_BLOOD_PRESSURE_SYNCING: 46,//血压数据同步中
  OFFLINE_BLOOD_PRESSURE_SYNC_OK: 47,//血压数据同步完成
  BLOOD_PRESSURE_TEST_TIME_OUT: 48,//血压检测超时
  BLOOD_PRESSURE_TEST_ERROR: 49,//血压检测错误
  BLOOD_PRESSURE_TEST_STAT: 50,//血压检测开始
  SEVEN_DAY_WEATHER_SYNC_SUCCESS: 51,//7天天气同步完成
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

if (!window.plugins) {
  window.plugins = {}
}

if (!window.plugins.SmartBand) {
  window.plugins.SmartBand = new SmartBand()
}
// cordova.fireDocumentEvent('SmartBand.HeytzICallback', window.plugins.SmartBand.HeytzICallback);
module.exports = new SmartBand();