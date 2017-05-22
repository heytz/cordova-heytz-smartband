# cordova-heytz-smartband
黑子智能手环插件

android版本要求 sdk 最低18 

###IOS

加入  BLUETOOTH_USAGE_DESCRIPTION 默认 " "

#功能列表
    
   [1.初始化](1.初始化) 
    
   [2.扫描](2.扫描)
  
   [3.停止扫描](3.停止扫描)
  
   [4.连接](4.连接)
  
   [5.久坐提醒](5.久坐提醒)
  
   [6.摇一摇](6.摇一摇)
  
   [7.智能闹钟](7.智能闹钟)
  
   [8.固件升级](8.固件升级) （未实现）
  
   [9.设置身高体重](9.设置身高体重)
  
   [10.同步计步数据](10.同步计步数据) (Android IOS(未测试))
  
   [11.同步睡眠数据](11.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)) (Android  IOS(未测试))
  
   [12.查找手环](12.查找手环)   (Android无效)
  
   [13.短信提醒](13.短信提醒)   （未实现）
  
   [14.来电提醒](14.来电提醒)   （未实现）
  
   [15.QQ提醒](15.QQ提醒)   （未实现）
  
   [16.微信提醒](16.微信提醒)   （未实现）
  
   [17.更多提醒](17.更多提醒)   （未实现）
  
   [18.智能防丢](18.智能防丢)   （未实现）
  
   [19.恢复出厂设置](19.恢复出厂设置)
   
   [20.获取电量](20.获取电量)
   
   [21.获取版本号](21.获取版本号)
   
   [22.同步时间](22.同步时间)
   
   [23.判断蓝牙是否打开](23.判断蓝牙是否打开)   (Android)
   
   [24.查询睡眠详情](24.查询一天的睡眠总时间) (Android)
   
   [25.新一天初始化计步数据库](25.新一天初始化计步数据库) (Android)
   
   [26.查询一天的总步数](26.查询一天的总步数) (Android)
   
   [27.查询步数详情](27.查询一天步数、距离、卡路里的集合) (Android)
   
   [28.查询某一天各小时步数](28.查询某一天各小时步数) (Android)
   
   [29.读取线损值](29.读取线损值，每读一次，即监听一次) (Android)
   
   [30.断开设备](30.断开设备)
   
   [31.解绑服务](31.解绑服务) （未实现）
   
   [32.查询一天的睡眠详情](32.查询一天的睡眠详情) (Android)
   
   [33.是否支持蓝牙4.0](33.是否支持蓝牙4.0)  (Android)
   
   [34.判断平台](34.判断平台)  设备是否为RK平台手环(可事先问相关人员,是否有这设备)，设备断开情况下为false
   
   [35.获取新版本的版本号](35.获取新版本的版本号) (Android)
   
   [36.获取新版本的版本号](36.获取新版本的版本号) (Android)
   
   [37.查询设备升级属性](37.查询设备升级属性)
   
   [38.同步所有数据](38.同步所有数据)    (IOS(未测试))
   
   [39.检查是否可以发送](39.检查是否可以发送)    (IOS(未测试))
     
   [40.打开提醒](40.打开提醒)    (IOS(未测试))
   
    

 
##1.初始化

    cordova.plugins.Smartband.init(success,error)
     
##2.扫描

    cordova.plugins.Smartband.scan(time,success,error)
    
##3.停止扫描

    cordova.plugins.Smartband.stop(success,error)
   
##4.连接
  
    cordova.plugins.Smartband.connect(address,success,error)
    
##5.久坐提醒
  
    cordova.plugins.Smartband.sendSedentaryRemindCommand(flag,miuntes,success,error)
     
##6.摇一摇
  
    cordova.plugins.Smartband.shakeMode(state,success,error)
      
##7.智能闹钟
  
    * whichClock   FIRST_CLOCK: 1,//第一个闹钟 SECOND_CLOCK: 2,//第二个闹钟 THIRD_CLOCK: 3,//第三个闹钟
    * weekPeroid   sunday monday tuesday wednesday thursday saturday  everyday
    * hour         闹铃小时(24 小时制，如下午 1 点，hour=13)
    * minute       闹铃分钟
    * isOpen       true 打开闹钟;false 关闭闹钟
    * shakePeriod  手环振动次数，之前直接写死 5 次，现在改为可设 置次数。
    cordova.plugins.Smartband.sendToSetAlarmCommand(whichClock, weekPeroid, hour, minute, isOpen, shakePeriod, success, error)
      
##9.设置身高体重

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
    cordova.plugins.Smartband.sendStepLenAndWeightToBLE(height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate, success, error)

##10.同步计步数据
  
    cordova.plugins.Smartband.syncAllStepData(success, error)
 
##11.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
  
    cordova.plugins.Smartband.syncAllSleepData(success, error)
 
##12.查找手环
    * ios 没有vibrationCount 设置
    cordova.plugins.Smartband.findBand(vibrationCount, success, error)
    
##19.恢复出厂设置
    
     cordova.plugins.Smartband.deleteDevicesAllData(success,error)
    
##20.获取电量
    
     cordova.plugins.Smartband.sendToReadBLEBattery(success,error)
     
##21.获取版本
    
     cordova.plugins.Smartband.sendToReadBLEVersion(success,error)
   
##22.同步时间
    
     cordova.plugins.Smartband.syncBLETime(success,error)
     
##23.判断蓝牙是否打开
    
     cordova.plugins.Smartband.isEnabled(success,error)

##24.查询一天的睡眠总时间
    
     cordova.plugins.Smartband.querySleepDate(queryDate,success,error)
     
##25.新一天初始化计步数据库
    
     cordova.plugins.Smartband.updateStepSQL(success,error)
     
##26.查询一天的总步数
    
     cordova.plugins.Smartband.queryStepDate(queryDate,success,error)
     
##27.查询一天的步数、距离、卡路里
    
     cordova.plugins.Smartband.queryStepInfo(queryDate,success,error)
     
##28.查询某一天各小时步数
    
     cordova.plugins.Smartband.queryOneHourStepSQL(Calendar,success,error)
     
##29.读取线损值rssi
    
     cordova.plugins.Smartband.readRssi(success,error)
     
##30.断开设备
    
     cordova.plugins.Smartband.disConnect(success,error)
     
##32.查询一天的睡眠详情
    
     cordova.plugins.Smartband.querySleepInfo(calendar,success,error)
          
##33.是否支持蓝牙4.0
    
     cordova.plugins.Smartband.isSupported(success,error)
          
##34.判断平台
    
     cordova.plugins.Smartband.isRKPlatform(success,error)
          
##35.获取新版本的版本号
    
     cordova.plugins.Smartband.getServerBtImgVersion(success,error)
          
##36.获取新版本的版本号
    
     cordova.plugins.Smartband.getServerPatchVersion(success,error)
          
##37.查询设备升级属性
    
     cordova.plugins.Smartband.queryDeviceFearture(success,error)
          
##38.同步所有数据
    
     cordova.plugins.Smartband.syncAllData(success,error)
          
##39.检查是否可以发送
    
     cordova.plugins.Smartband.checkUTEDevicesStateIsEnable(success,error)

##40.打开提醒
    
     cordova.plugins.Smartband.openRemind(open,type,success,error)
          
    
  
#监听接口
   
   [1.监听设备通讯](1.监听设备通讯)
   
   [2.监听步数变化](2.监听步数变化)
   
   [3.查询睡眠详情](3.查询睡眠详情)
   
   [4.查询睡眠详情](4.查询睡眠详情)
   
##1.监听设备通讯  

    document.addEventListener("SmartBand.heytzICallback", success(data), false);

##2.监听步数变化

    document.addEventListener("SmartBand.onStepChange", success(data), false);

##3.监听睡眠
   
    document.addEventListener("SmartBand.onSleepChange", success(), false);

##4.监听IOS option设置，（仅IOS）
   
    document.addEventListener("SmartBand.onUTEOptionCallBack", success(callback), false);

     
     
    
    