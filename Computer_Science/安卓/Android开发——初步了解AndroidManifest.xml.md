# Android开发——初步了解`AndroidManifest.xml`

​	`AndroidManifest.xml` 是 Android 应用的清单文件，包含了应用的包名、组件声明、权限声明、API 版本信息等。它是 Android 应用的“说明书”，系统通过它了解应用的结构和行为。咱们的AndroidManifest文件实际上就相当于一份声明式的配置文件了

------

## AndroidManifest.xml 的主要功能

1. **声明应用的包名**
    包名是应用的唯一标识符，用于在系统中区分不同的应用。

   ```xml
   <manifest xmlns:android="http://schemas.android.com/apk/res/android"
             package="com.example.myapp">
   ```

2. **声明应用组件**
    包括 `Activity`、`Service`、`BroadcastReceiver` 和 `ContentProvider`。每个组件都需要在清单文件中进行声明。一般而言，我们不会自己重新写这个文件，会让Android Studio自动的修改这个文件

   ```xml
   <application
       android:icon="@drawable/ic_launcher"
       android:label="@string/app_name">
       <activity android:name=".MainActivity">
           <intent-filter>
               <action android:name="android.intent.action.MAIN" />
               <category android:name="android.intent.category.LAUNCHER" />
           </intent-filter>
       </activity>
   </application>
   ```

3. **声明权限**
    使用 `<uses-permission>` 声明应用需要的权限，例如访问网络、读取联系人等。

   ```xml
   <uses-permission android:name="android.permission.INTERNET" />
   ```

4. **声明应用的最小 SDK 版本**
    使用 `<uses-sdk>` 声明应用支持的最低和目标 SDK 版本。

   ```xml
   <uses-sdk
       android:minSdkVersion="16"
       android:targetSdkVersion="30" />
   ```

5. **声明应用的特性和功能**
    使用 `<uses-feature>` 声明应用所需的硬件特性，例如摄像头、蓝牙等。

   ```xml
   <uses-feature android:name="android.hardware.camera" />
   ```

------

## 例子：我写的一个迷你demo的AndroidManifest文件

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools">

    <application
        android:allowBackup="true"
        android:dataExtractionRules="@xml/data_extraction_rules"
        android:fullBackupContent="@xml/backup_rules"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.ActivityAction">
        <activity
            android:name=".SecondActivity"
            android:exported="false"
            android:label="@string/title_activity_second"
            android:theme="@style/Theme.ActivityAction" />
        <activity
            android:name=".FirstActivity"
            android:exported="true"
            android:label="@string/title_activity_first"
            android:theme="@style/Theme.ActivityAction">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />

                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>

</manifest>
```

您提供的 `AndroidManifest.xml` 文件配置了两个 Activity，并使用了多个与数据备份和安全性相关的属性。以下是对该文件的详细分析：

------

## 📁 `AndroidManifest.xml` 文件结构

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools">

    <application
        android:allowBackup="true"
        android:dataExtractionRules="@xml/data_extraction_rules"
        android:fullBackupContent="@xml/backup_rules"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.ActivityAction">

        <activity
            android:name=".SecondActivity"
            android:exported="false"
            android:label="@string/title_activity_second"
            android:theme="@style/Theme.ActivityAction" />

        <activity
            android:name=".FirstActivity"
            android:exported="true"
            android:label="@string/title_activity_first"
            android:theme="@style/Theme.ActivityAction">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>

    </application>

</manifest>
```

------

## 🧩 关键属性解析

### 1. `<application>` 元素

- **`android:allowBackup="true"`**：允许应用的数据进行备份。默认值为 `true`，但建议显式设置。
- **`android:dataExtractionRules="@xml/data_extraction_rules"`**：指定一个 XML 文件，定义在 Android 12 及以上版本中，哪些数据可以被提取用于云备份。
- **`android:fullBackupContent="@xml/backup_rules"`**：指定一个 XML 文件，定义在 Android 11 及以下版本中，哪些数据可以被备份。
- **`android:icon="@mipmap/ic_launcher"`**：设置应用的图标。
- **`android:label="@string/app_name"`**：设置应用的名称。
- **`android:roundIcon="@mipmap/ic_launcher_round"`**：设置应用的圆形图标。
- **`android:supportsRtl="true"`**：支持从右到左的布局，适用于阿拉伯语等语言。
- **`android:theme="@style/Theme.ActivityAction"`**：设置应用的主题。

### 2. `<activity>` 元素

#### `SecondActivity`

- **`android:name=".SecondActivity"`**：指定 Activity 的类名。
- **`android:exported="false"`**：该 Activity 不允许被其他应用启动。
- **`android:label="@string/title_activity_second"`**：设置 Activity 的标签。
- **`android:theme="@style/Theme.ActivityAction"`**：设置 Activity 的主题。

#### `FirstActivity`

- **`android:name=".FirstActivity"`**：指定 Activity 的类名。
- **`android:exported="true"`**：该 Activity 允许被其他应用启动。
- **`android:label="@string/title_activity_first"`**：设置 Activity 的标签。
- **`android:theme="@style/Theme.ActivityAction"`**：设置 Activity 的主题。
- **`<intent-filter>`**：定义了该 Activity 是应用的主入口，并在启动器中显示。

