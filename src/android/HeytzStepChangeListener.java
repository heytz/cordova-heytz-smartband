package com.heytz.smartband;

import android.util.Log;
import com.yc.pedometer.sdk.StepChangeListener;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by chendongdong on 2017/5/12.
 */
public class HeytzStepChangeListener implements StepChangeListener {
    private final String TAG = "==========HeytzStepChangeListener===========\n";
    private HeytzSmartApp app;

    HeytzStepChangeListener(HeytzSmartApp app) {
        this.app = app;
    }
    @Override
    public void onStepChange(int steps, float distance, int calories) {
        Log.d("onStepHandler", "steps =" + steps + ",distance =" + distance
                + ",calories =" + calories);
        JSONObject data = new JSONObject();
        try {
            data.put("steps", steps);
            data.put("distance", distance);
            data.put("calories", calories);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        String format = "cordova.plugins.SmartBand.openOnStepChange(%s);";
        final String js = String.format(format, data.toString());
        app.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                app.getSmartBand().webView.loadUrl("javascript:" + js);
            }
        });

    }
}
