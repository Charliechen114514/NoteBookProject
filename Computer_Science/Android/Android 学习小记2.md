# Android学习小记2

## Android Manifest文件分析

​	笔者打算进一步详细的分析一下这个Manifest文件，请看下文：

`AndroidManifest.xml`文件，包含了应用的基本配置信息和声明。下面是逐行的详细分析：

​	XML 的格式就是要求一个属性的内容要被包含在一堆标签内部

##### 1. XML声明

```
<?xml version="1.0" encoding="utf-8"?>
```

这是XML声明，表示该文件使用UTF-8编码格式，符合XML 1.0规范。

##### 2. `<manifest>`元素

```
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
          xmlns:tools="http://schemas.android.com/tools">
```

- `xmlns:android` 定义了Android命名空间的URI，用于在文件中引用Android的属性。
- `xmlns:tools` 定义了`tools`命名空间的URI，常用于开发工具属性（如`tools:targetApi`）来影响构建工具和IDE行为，但不会影响应用的运行时行为。

##### 3. `<application>`元素

```
<application
    android:allowBackup="true"
    android:dataExtractionRules="@xml/data_extraction_rules"
    android:fullBackupContent="@xml/backup_rules"
    android:icon="@mipmap/ic_launcher"
    android:label="@string/app_name"
    android:roundIcon="@mipmap/ic_launcher_round"
    android:supportsRtl="true"
    android:theme="@style/Theme.DemoOfMyFirstApplication"
    tools:targetApi="31">
```

​	下面的内容就分别对应了res文件夹下的内容了。

- `android:allowBackup="true"`: 允许应用备份数据。这意味着用户卸载并重新安装应用时，可以恢复数据。
- `android:dataExtractionRules="@xml/data_extraction_rules"`: 指定一个XML文件，定义数据提取规则，通常与备份和恢复数据相关。
- `android:fullBackupContent="@xml/backup_rules"`: 指定一个XML文件，定义全量备份的内容。
- `android:icon="@mipmap/ic_launcher"`: 定义应用的图标，引用了一个位于`mipmap`目录下的资源。
- `android:label="@string/app_name"`: 应用的名称，引用了一个字符串资源。
- `android:roundIcon="@mipmap/ic_launcher_round"`: 为支持圆形图标的设备指定圆形图标资源。
- `android:supportsRtl="true"`: 表示应用支持从右到左（RTL）的语言方向，通常用于阿拉伯语或希伯来语。
- `android:theme="@style/Theme.DemoOfMyFirstApplication"`: 定义应用的主题，引用了一个主题资源。
- `tools:targetApi="31"`: 指定开发工具应针对Android 12（API 31）进行构建。这个属性只会影响开发工具和编译器，运行时不会起作用。

##### 4. `<activity>`元素

```
<activity
    android:name=".MainActivity"
    android:exported="true"
    android:label="@string/app_name"
    android:theme="@style/Theme.DemoOfMyFirstApplication">
```

- `android:name=".MainActivity"`: 指定启动的活动（Activity）的名称，这里是`MainActivity`类。`"."`表示该活动是当前应用的直接子类。
- `android:exported="true"`: 表示此活动可以被外部应用启动。在Android 12及以后版本中，所有具有`intent-filter`的Activity必须声明`android:exported`属性，确保应用明确指示哪些活动是可以被外部访问的。
- `android:label="@string/app_name"`: 应用的标签，通常用于显示在UI中。它引用了字符串资源`app_name`。
- `android:theme="@style/Theme.DemoOfMyFirstApplication"`: 为该Activity指定了应用的主题。

##### 5. `<intent-filter>`元素

```
<intent-filter>
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
</intent-filter>
```

- `<action android:name="android.intent.action.MAIN" />`: 表示这是应用的主入口点，即启动Activity。
- `<category android:name="android.intent.category.LAUNCHER" />`: 指定这个Activity作为应用启动时的启动项。它告诉系统这是主界面（即启动器）。

##### 6. 关闭标签

```
</activity>
</application>
```

这些标签分别关闭了`<activity>`和`<application>`元素。

#### 7. 结束标签

```
</manifest>
```

最后，关闭了`<manifest>`元素，表示XML文档结束。

## res文件夹再探

​	我们之前就是简单的看了眼res底下有什么，下面我们仔细瞧瞧我们的res文件夹。

### drawable

​	可画的！其实就是放置一些常见的绘画资源。`drawable` 文件夹用于存储所有与绘制和显示相关的图像资源。这些资源通常用于各种UI元素，比如按钮、背景图、图标等。图像文件可以是位图（如 `.png`、`.jpg`）或矢量图形（如 `.xml` 形式的矢量文件）。此外，`drawable` 文件夹还可以存放不同密度版本的图像（如hdpi、mdpi等），以适应不同屏幕分辨率的设备。

### mipmap

​	`mipmap` 文件夹用于存储应用的启动图标（Launcher icon），这是Android应用的标志性图像，用于显示在设备的主屏幕和应用抽屉中。与`drawable`不同，`mipmap`中的图标文件有特定的用途和要求，尤其是在支持高分辨率屏幕和不同设备的情况下。

### value

​	这个文件夹存储的就是我们的常量，res/values 文件夹用于存储许多 Android 项目中使用的资源的值，包括颜色、样式、尺寸等特性。我们新建的项目下面有三个重要的xml文件。

#### color.xml

```
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <color name="purple_200">#FFBB86FC</color>
    <color name="purple_500">#FF6200EE</color>
    <color name="purple_700">#FF3700B3</color>
    <color name="teal_200">#FF03DAC5</color>
    <color name="teal_700">#FF018786</color>
    <color name="black">#FF000000</color>
    <color name="white">#FFFFFFFF</color>
</resources>
```

​	这个封装了我们对颜色的抽象，毕竟没有人喜欢咔咔写一串颜色代码来指定颜色，对于特殊的颜色我们选择封装一个字符串来进行使用。我们稍后就可以在布局文件夹中写上：

```
android:background="@color/purple_500"
```

#### strings.xml

​	strings.xml 是最重要的、使用最广泛的值文件之一，因为它适用于 Android 项目。strings.xml 的基本功能是在一个文件中定义字符串，以便于在 Android 项目的不同位置使用相同的字符串，而且它使项目看起来不那么混乱。我们也可以在此文件中定义一个数组。

```
<resources>
    <string name="app_name">DemoOfMyFirstApplication</string>
</resources>
```

#### style.xml

```
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <style name="Theme.DemoOfMyFirstApplication" parent="android:Theme.Material.Light.NoActionBar" />
</resources>
```

​	样式资源用于定义UI元素的外观和行为，比如颜色、字体、布局等。该样式名为`Theme.DemoOfMyFirstApplication`，它继承自Android内置的`android:Theme.Material.Light.NoActionBar`样式。

- `name="Theme.DemoOfMyFirstApplication"`：这是定义的样式的名称。这个名称可以在应用的其他地方引用，比如在`AndroidManifest.xml`文件中设置应用的主题。
- `parent="android:Theme.Material.Light.NoActionBar"`：这个属性指定了该样式的父样式为`android:Theme.Material.Light.NoActionBar`。`android:Theme.Material.Light.NoActionBar`是Android系统自带的一个主题，它使用了Material Design样式和浅色调（Light），并且**没有ActionBar**（即没有顶部的应用栏）。

### xml文件

#### backup_rules.xml

`backup_rules.xml` 是一个用于配置 Android 应用数据备份规则的 XML 文件。它告诉 Android 系统哪些文件或目录需要被备份，哪些文件或目录应该被排除在备份之外。

在 Android 中，备份和恢复功能由系统通过 `Auto Backup` 和 `BackupManager` 提供支持，开发者可以通过自定义规则来指定哪些数据应该被备份，哪些数据应该被排除。

> [通过自动备份功能备份用户数据  | Identity  | Android Developers](https://developer.android.com/identity/data/autobackup?hl=zh-cn)

在使用 `backup_rules.xml` 时，通常会将文件存放在 `res/xml/` 目录下，然后通过 `BackupManager` 来应用这些规则。

#### data_extraction_rules.xml

`data_extraction_rules.xml` 是一个用于定义数据提取规则的配置文件，通常在应用需要提取数据时使用。例如，它可能会用于备份数据、数据恢复、或者将特定数据发送到云端等操作。
