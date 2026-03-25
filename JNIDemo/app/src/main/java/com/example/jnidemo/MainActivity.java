package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public native String getNativeMessage();
    public native int computeFactorial(int value);
    public native String flipText(String input);
    public native int calculateSum(int[] numbers);

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvMsg = findViewById(R.id.tvMsg);
        TextView tvCalc = findViewById(R.id.tvCalc);
        TextView tvText = findViewById(R.id.tvText);
        TextView tvSum = findViewById(R.id.tvSum);

        tvMsg.setText(getNativeMessage());

        int res = computeFactorial(8);
        if (res >= 0) {
            tvCalc.setText("Factoriel de 8 = " + res);
        } else {
            tvCalc.setText("Erreur calcul (code " + res + ")");
        }

        String output = flipText("JNI avec C++");
        tvText.setText("Resultat : " + output);

        int[] data = {5, 15, 25, 35};
        int total = calculateSum(data);
        tvSum.setText("Total = " + total);
    }
}