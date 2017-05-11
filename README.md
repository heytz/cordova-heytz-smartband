# cordova-heytz-smartband
黑子智能手环插件

android版本要求 sdk 最低18 

#功能列表
    
   [1.初始化](1.初始化) (Android)
    
   [2.扫描](2.扫描) (Android)
  
   [3.停止扫描](3.停止扫描) (Android)
  
   [4.连接](4.连接) (Android)
  
   [5.久坐提醒](5.久坐提醒) (Android)
  
   [6.摇一摇](6.摇一摇) (Android)
  
   [7.智能闹钟](7.智能闹钟) (Android)
  
   [8.固件升级](8.固件升级)
  
   [9.设置身高体重](9.设置身高体重) (Android)
  
   [10.同步计步数据](10.同步计步数据) (Android)
  
   [11.同步睡眠数据](11.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)) (Android)
  
   [12.查找手环](12.查找手环)   (Android无效)
  
   [13.短信提醒](13.短信提醒)
  
   [14.来电提醒](14.来电提醒)
  
   [15.QQ提醒](15.QQ提醒)
  
   [16.微信提醒](16.微信提醒)
  
   [17.更多提醒](17.更多提醒)
  
   [18.智能防丢](18.智能防丢)
  
   [19.恢复出厂设置](19.恢复出厂设置)
   
   [20.获取电量](20.获取电量)   (Android)
   
   [21.获取版本号](21.获取版本号) (Android)
   
   [22.同步时间](22.同步时间)   (Android)
   
   [23.判断蓝牙是否打开](23.判断蓝牙是否打开)   (Android)
   
   [24.查询睡眠详情](24.查询一天的睡眠总时间) (Android)
   
   [25.新一天初始化计步数据库](25.新一天初始化计步数据库) (Android)
   
   [26.查询一天的总步数](26.查询一天的总步数) (Android)
   
   [27.查询步数详情](27.查询一天步数、距离、卡路里的集合) (Android)
   
   [28.查询某一天各小时步数](28.查询某一天各小时步数) (Android)
   
   [29.读取线损值](29.读取线损值，每读一次，即监听一次) (Android)
   
   [30.断开设备](30.断开设备) (Android)
   
   [31.解绑服务](31.解绑服务) （未实现）
   
   [32.查询一天的睡眠详情](32.查询一天的睡眠详情) (Android)
   
   [33.是否支持蓝牙4.0](33.是否支持蓝牙4.0)  (Android)
   
   [34.判断平台](34.判断平台) (Android)
   
   [35.获取新版本的版本号](35.获取新版本的版本号) (Android)
   
   [36.获取新版本的版本号](36.获取新版本的版本号) (Android)
   
   [37.查询设备升级属性](37.查询设备升级属性)
   


 
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
  
    cordova.plugins.Smartband.sendToSetAlarmCommand(whichClock, weekPeroid, hour, minute, isOpen, shakePeriod, success, error)
      
##9.设置身高体重
  
    cordova.plugins.Smartband.sendStepLenAndWeightToBLE(height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate, success, error)

##10.同步计步数据
  
    cordova.plugins.Smartband.syncAllStepData(success, error)
 
##11.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
  
    cordova.plugins.Smartband.syncAllSleepData(success, error)
 
##12.查找手环
  
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

     
     
    
    