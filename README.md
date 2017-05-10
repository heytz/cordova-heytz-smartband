# cordova-heytz-smartband
黑子智能手环插件

android版本要求 sdk 最低18 

功能列表
  
   [1.扫描](1.扫描)
  
   [2.停止扫描](2.停止扫描)
  
   [3.连接](3.连接)
  
   [4.久坐提醒](4.久坐提醒)
  
   [5.摇一摇](5.摇一摇)
  
   [6.智能闹钟](6.智能闹钟)
  
   [7.固件升级](7.固件升级)
  
   [8.设置身高体重](8.设置身高体重)
  
   [9.同步计步数据](9.同步计步数据)
  
   [10.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)](10.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作))
  
   [11.查找手环](11.查找手环)
  
   [12.短信提醒](12.短信提醒)
  
   [13.来电提醒](13.来电提醒)
  
   [14.QQ提醒](14.QQ提醒)
  
   [15.微信提醒](15.微信提醒)
  
   [16.更多提醒](16.更多提醒)
  
   [17.智能防丢](17.智能防丢)
  
   [18.恢复出厂设置](18.恢复出厂设置)
   
   [19.获取电量](19.获取电量)
   
   [20.获取版本号](20.获取版本号)
   
   [21.同步时间](21.同步时间)
   
   [22.判断蓝牙是否打开](22.判断蓝牙是否打开)
   
   
##1.扫描

    cordova.plugins.Smartband.scan(time,success,error)
    
##2.停止扫描

    cordova.plugins.Smartband.stop(success,error)
   
##3.连接
  
    cordova.plugins.Smartband.connect(address,success,error)
    
##4.久坐提醒
  
    cordova.plugins.Smartband.sendSedentaryRemindCommand(flag,miuntes,success,error)
     
##5.摇一摇
  
    cordova.plugins.Smartband.shakeMode(state,success,error)
      
##6.智能闹钟
  
    cordova.plugins.Smartband.sendToSetAlarmCommand(whichClock, weekPeroid, hour, minute, isOpen, shakePeriod, success, error)
      
##8.设置身高体重
  
    cordova.plugins.Smartband.sendStepLenAndWeightToBLE(height, weight, offScreenTime, stepTask, isRraisHandbrightScreenSwitchOpen, isHighestRateOpen, highestRate, success, error)

##9.同步计步数据
  
    cordova.plugins.Smartband.syncAllStepData(success, error)
 
##10.同步睡眠数据(同步完成前，请不要进行其他任何的通信工作)
  
    cordova.plugins.Smartband.syncAllSleepData(success, error)
 
##11.查找手环
  
    cordova.plugins.Smartband.findBand(vibrationCount, success, error)
    
##18.恢复出厂设置
    
     cordova.plugins.Smartband.deleteDevicesAllData(success,error)
    
##19.获取电量
    
     cordova.plugins.Smartband.sendToReadBLEBattery(success,error)
     
##20.获取版本
    
     cordova.plugins.Smartband.sendToReadBLEVersion(success,error)
   
##21.同步时间
    
     cordova.plugins.Smartband.syncBLETime(success,error)
     
##22.判断蓝牙是否打开
    
     cordova.plugins.Smartband.isEnabled(success,error)
  
  
     
    
    