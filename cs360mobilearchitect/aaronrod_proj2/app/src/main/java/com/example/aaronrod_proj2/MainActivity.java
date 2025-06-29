package com.example.aaronrod_proj2;

import android.os.Bundle;
import android.view.View;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // This links to your XML layout
    }

    public void onLoginClick(View view) {
        // TODO: Handle login logic
    }

    public void onCreateAccountClick(View view) {
        // TODO: Handle create account logic
    }
}