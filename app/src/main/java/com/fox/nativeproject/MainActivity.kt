package com.fox.nativeproject

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.TextView
import android.widget.Toast
import com.fox.nativeproject.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    var filed = "我是成员变量"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        binding.filed.text = filedFromJNI()

        binding.staticFiled.text = staticFiledFromJNI()

        javaToC()

        //动态注册
        Toast.makeText(this,"${loadAdd(1f,2f)}",Toast.LENGTH_LONG).show()
    }

    fun normalMethod(){
        Log.i(TAG,"normal method invoke")
    }

    /**
     * A native method that is implemented by the 'nativeproject' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun filedFromJNI():String

    external fun staticFiledFromJNI():String

    external fun javaToC()

    external fun loadAdd(a:Float,b:Float):Float

    companion object {
        const val TAG = "MainActivity"
        // Used to load the 'nativeproject' library on application startup.
        var staticFiled = "我是静态变量"

        init {
            System.loadLibrary("nativeproject")
        }

        //这里一定要加这个注解 否则jni调用就会非常的麻烦
        @JvmStatic
        fun staticMethod(){
            Log.i(TAG,"static method invoke")
        }
    }

}