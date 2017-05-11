package com.heytz.smartband;

import com.yc.pedometer.sdk.SleepChangeListener;

/**
 * Created by chendongdong on 2017/5/12.
 */
public class HeytzSleepChangeListener implements SleepChangeListener {
    private final String TAG = "==========HeytzSleepChangeListener===========\n";
    private HeytzSmartApp heytzSmartApp;

    HeytzSleepChangeListener(HeytzSmartApp app) {
        this.heytzSmartApp = app;
    }

    @Override
    public void onSleepChange() {
        //睡眠数据发现改变可以去查询当天的睡眠数据querySleepInfo
        final String js = "cordova.plugins.SmartBand.openOnSleepChange();";
        heytzSmartApp.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                heytzSmartApp.getSmartBand().webView.loadUrl("javascript:" + js);
            }
        });
    }
}
