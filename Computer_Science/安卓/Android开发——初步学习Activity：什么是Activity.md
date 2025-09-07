# Android开发——初步学习Activity：什么是Activity

​	在 Android 中，Activity 是一个用于展示用户界面的组件。每个 Activity 通常对应应用中的一个屏幕，例如主界面、设置界面或详情页。Activity 负责处理用户的输入事件，更新 UI，并与其他组件（如服务、广播接收器）进行交互。如果接触过Qt开发的同志，一点不会难以想到Activity就有点像咱们的QMainWindow一样，作为UI交互大的容器。

## 🛠️创建一个Activity

​	咱们先不deep dive到Activity的基本原理，我们就先创建一个玩玩。一般而言，咱们作为快速开发者，不会自己鹿代码和在XML中自己手动改，容易出错。

#### 基本步骤（一次性的）

1. **打开项目**：启动 Android Studio，打开您的项目。
2. **右键点击包名**：在项目视图中，导航到 `app > src > main > java > com.example.yourapp`，右键点击您的包名（例如 `com.example.myapp`）。
3. **选择创建 Activity**：选择 `New > Activity`，然后选择您想要的 Activity 类型，例如 `Empty Activity`。
4. **配置 Activity**：
   - **Activity Name**：输入 Activity 的名称（如 `SecondActivity`）。
   - **Layout Name**：输入布局文件的名称（默认为 `activity_second`）。
   - **Title**：设置该 Activity 的标题。
   - **Launcher Activity**：如果您希望此 Activity 为启动 Activity，请勾选此选项。
   - **Source Language**：在今天，你只能使用Kotlin了，Java是不被支持的。
5. **完成创建**：点击 `Finish`，Android Studio 会自动生成相应的 Activity 类、布局文件，并在 `AndroidManifest.xml` 中注册该 Activity。

#### 手动创建 Activity（分步进行）

如果您希望更灵活地控制创建过程，可以手动创建 Activity。

1. **创建 Activity 类**：

   - 在项目视图中，导航到 `app > src > main > java > com.example.yourapp`。
   - 右键点击您的包名，选择 `New > Java Class` 或 `New > Kotlin Class/File`。
   - 输入类名（如 `SecondActivity`），并使其继承 `AppCompatActivity`。
   - 实现 `onCreate()` 方法，并通过 `setContentView()` 设置布局文件。

   ```java
   public class SecondActivity extends AppCompatActivity {
       @Override
       protected void onCreate(Bundle savedInstanceState) {
           super.onCreate(savedInstanceState);
           setContentView(R.layout.activity_second);
       }
   }
   ```

2. **创建布局文件**：

   - 在 `res > layout` 目录下，右键点击，选择 `New > Layout Resource File`。
   - 输入文件名（如 `activity_second.xml`），并设计您的布局。

3. **注册 Activity**：

   - 打开 `AndroidManifest.xml` 文件。
   - 在 `<application>` 标签内，添加以下代码以注册新创建的 Activity：

   ```xml
   <activity android:name=".SecondActivity" />
   ```

------

#### 在 AndroidManifest.xml 中注册 Activity（一般你不用做这个，Android Studio帮你做了）

​	`AndroidManifest.xml`是咱们的安卓APP的一个总导览，我们的Activities必须在这里被表达，所以，无论是使用向导还是手动创建 Activity，都需要在 `AndroidManifest.xml` 中注册该 Activity。通常，Android Studio 会自动为您完成此操作，但如果没有，您可以手动添加：

```xml
<activity android:name=".SecondActivity" />
```

如果您希望此 Activity 为启动 Activity（即应用启动时首先显示的界面），需要在 `<activity>` 标签中添加 `intent-filter`：

```xml
<activity android:name=".MainActivity">
    <intent-filter>
        <action android:name="android.intent.action.MAIN" />
        <category android:name="android.intent.category.LAUNCHER" />
    </intent-filter>
</activity>
```

# 准备完成我们的业务——Layout文件

​	Activities的默认代码中，就帮助我们生成好了OnCreate方法，一般而言，我们的默认代码包括但不限于：回调父类的onCreate创建方法，下一步，我们往往是要加载我们的ContentView，让我们的APP的布局文件生效。

​	在Qt中，咱们的Layout是Ui_xxx.ui搞定的，它本身是一个XML文件，声明式的说明我们的布局如何。安卓自身也是这样做的。我们会在Layout文件夹下创建layout XML文件，在代码中采用资源加载的方式联合起来搞定我们的布局加载动作。

##  什么是 Android 布局文件？

Android 布局文件是以 XML 格式编写的文件，位于项目的 `res/layout/` 目录下。它们描述了应用界面的结构和外观，包括视图组件（如按钮、文本框、图片等）及其排列方式。通过布局文件，开发者可以在不编写大量代码的情况下，快速构建出界面。

------

## 🧩 布局文件的基本结构

一个典型的布局文件通常包含以下几个部分：

1. **XML 声明和命名空间**

   ```xml
   <?xml version="1.0" encoding="utf-8"?>
   <LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
                 android:layout_width="match_parent"
                 android:layout_height="match_parent">
   ```

   - `xmlns:android`：声明 XML 命名空间，Android 系统通过它识别属性。
   - `android:layout_width` 和 `android:layout_height`：定义布局的宽度和高度，常用值有 `match_parent`、`wrap_content` 和具体的 dp 值。

2. **视图组件（Views）**

   在布局文件中，视图组件是构建 UI 的基本单元，如：

   ```xml
   <TextView android:id="@+id/textView"
             android:layout_width="wrap_content"
             android:layout_height="wrap_content"
             android:text="Hello, World!" />
   ```

   - `android:id`：为视图指定唯一标识符，供代码中引用。
   - `android:text`：设置文本内容。

3. **布局容器（ViewGroup）**

   布局容器是用于组织和排列子视图的容器类，如：

   - `LinearLayout`：线性布局，按水平或垂直方向排列子视图。
   - `RelativeLayout`：相对布局，子视图相对于父视图或其他兄弟视图定位。
   - `ConstraintLayout`：约束布局，使用约束关系定位子视图，推荐用于复杂布局。
   - `FrameLayout`：帧布局，通常用于显示单一视图或堆叠多个视图。

   示例：

   ```xml
   <LinearLayout android:orientation="vertical"
                 android:layout_width="match_parent"
                 android:layout_height="match_parent">
       <!-- 子视图 -->
   </LinearLayout>
   ```

------

## 🛠️ 如何在 Android Studio 中创建布局文件

在 Android Studio 中创建布局文件的步骤如下：

1. **使用向导创建布局文件**
   - 在项目视图中，右键点击 `res/layout` 目录，选择 `New > Layout Resource File`。
   - 输入文件名（如 `activity_main.xml`），选择根布局类型（如 `LinearLayout`）。
   - 点击 `OK`，Android Studio 会自动生成布局文件。
2. **手动编写布局文件**
   - 在 `res/layout` 目录下创建新的 XML 文件。
   - 使用上述结构和组件，手动编写布局内容。
3. **使用设计视图**
   - 打开布局文件，切换到 `Design` 视图。
   - 使用拖拽方式添加和配置视图组件，Android Studio 会自动生成相应的 XML 代码。

------

## 💡 常用布局类型及其适用场景

| 布局类型           | 描述                                           | 适用场景                                 |
| ------------------ | ---------------------------------------------- | ---------------------------------------- |
| `LinearLayout`     | 子视图按线性方向排列（水平或垂直）             | 简单的列表、表单布局                     |
| `RelativeLayout`   | 子视图相对于父视图或其他兄弟视图定位           | 复杂的布局，子视图之间有相对关系时       |
| `ConstraintLayout` | 使用约束关系定位子视图，性能优于嵌套布局       | 推荐用于复杂布局，减少嵌套层级，提高性能 |
| `FrameLayout`      | 子视图堆叠在一起，通常用于显示单一视图或覆盖层 | 显示单一内容、图片查看器、视频播放器等   |
| `TableLayout`      | 子视图按行和列排列，适用于表格布局             | 表格数据展示、日历布局                   |
| `GridLayout`       | 子视图按网格排列，支持跨行跨列                 | 图像画廊、日程安排等                     |

------

## 📐 布局属性详解

- **`android:layout_width` 和 `android:layout_height`**
  - `match_parent`：视图的大小填充父容器。
  - `wrap_content`：视图的大小适应其内容。
  - 固定值（如 `200dp`）：指定具体的尺寸。
- **`android:orientation`**
  - `horizontal`：子视图水平排列。
  - `vertical`：子视图垂直排列。
- **`android:padding` 和 `android:margin`**
  - `padding`：视图内容与边界之间的内边距。
  - `margin`：视图与其他视图之间的外边距。
- **`android:gravity` 和 `android:layout_gravity`**
  - `gravity`：控制视图内部内容的对齐方式。
  - `layout_gravity`：控制视图在父容器中的对齐方式。
- **`android:layout_weight`**
  - 在 `LinearLayout` 中，指定视图占用剩余空间的比例。

------

## 📱 响应式布局与多屏适配

为了适应不同设备和屏幕尺寸，Android 提供了多种方式进行布局适配：

1. **布局资源目录分组**

   - `res/layout/`：默认布局。
   - `res/layout-large/`：大屏设备布局。
   - `res/layout-land/`：横屏布局。
   - `res/layout-sw600dp/`：屏幕宽度大于等于 600dp 的设备布局。

   Android Studio 支持根据设备配置自动选择合适的布局资源。

2. **布局变体（Layout Variants）**

   - 在 Android Studio 中，右键点击布局文件，选择 `Create Layout Variant`。
   - 为特定设备配置创建布局变体，如平板、折叠屏等。

3. **使用 `ConstraintLayout`**

   - 通过约束关系定位视图，减少嵌套层级，提高布局性能。
   - 支持链式布局、偏移量、比例等复杂布局需求。

------

## 在布局文件中编写自己的控件排布

​	咱们说了，布局使用XML编写，我们其中的控件亦是如此。

```xml
<?xml version="1.0" encoding="utf-8"?>
<androidx.appcompat.widget.LinearLayoutCompat
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:orientation="vertical"
    android:layout_width="match_parent"
    android:layout_height="match_parent">

    <androidx.appcompat.widget.Toolbar
        android:id="@+id/toolbar"
        android:layout_width="match_parent"
        android:layout_height="?attr/actionBarSize"
        android:background="?attr/colorPrimary"/>

    <Button
        android:id="@+id/button1"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/Button1Text"
        tools:ignore="MissingConstraints" />

    <Button
        android:id="@+id/button2"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/Button2Text"
        tools:ignore="MissingConstraints" />

    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@+id/button_depatch_activity"
        android:text="@string/button_start_activity_text"
        />
</androidx.appcompat.widget.LinearLayoutCompat>
```

### 1. `android:id`

该属性为视图组件指定一个唯一的标识符。在 Java 或 Kotlin 代码中，可以通过该 ID 引用该按钮，以便设置点击事件监听器或修改其属性。

例如：

```kotlin
val button = findViewById<Button>(R.id.button_depatch_activity)
button.setOnClickListener {
    // 处理按钮点击事件
}
```

------

### 2. `android:layout_width` 和 `android:layout_height`

这两个属性定义了视图组件的宽度和高度。

- `match_parent`：视图将扩展以填充其父容器的剩余空间。
- `wrap_content`：视图将根据其内容的大小来调整自身的尺寸。

在上述示例中，`layout_width` 设置为 `match_parent`，表示按钮的宽度将与其父容器的宽度相同；`layout_height` 设置为 `wrap_content`，表示按钮的高度将根据其内容的高度来调整。

------

### 3. `android:text`

该属性设置按钮上显示的文本内容。在上述示例中，`@string/button_start_activity_text` 是一个引用字符串资源的方式，表示按钮上显示的文本内容来自于 `res/values/strings.xml` 文件中的 `button_start_activity_text` 字符串资源。

使用字符串资源的好处是可以方便地进行国际化和本地化，使应用支持多种语言。

------

### 4. 其他常用的按钮属性

- `android:background`：设置按钮的背景，可以是颜色、图片或 drawable 资源。
- `android:textColor`：设置按钮文本的颜色。
- `android:textSize`：设置按钮文本的大小。
- `android:padding`：设置按钮内容与边界之间的内边距。
- `android:layout_margin`：设置按钮与其他视图之间的外边距。

例如：

```xml
<Button
    android:id="@+id/button_example"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="Click Me"
    android:background="@drawable/button_background"
    android:textColor="@color/white"
    android:textSize="16sp"
    android:padding="10dp"
    android:layout_margin="20dp" />
```

## 在代码中使用我们的布局文件下的控件

​	在上面我们看到了layout下的所有控件都有自己的ID。这是我们访问控件的一个关键。笔者学习了两种办法搞定拿到控件这个工作

### 使用 `findViewById` 方法

`findViewById` 是 Android 中传统的控件查找方式。它通过控件的 ID 在视图层次结构中查找对应的控件。例如：

```kotlin
val textView: TextView = findViewById(R.id.textView)
```

**优点：**

- **简单直接**：对于小型项目或简单的布局，`findViewById` 足够使用。

**缺点：**

- **类型转换问题**：需要手动进行类型转换，容易出错。
- **空指针异常**：如果控件未在布局中定义，可能导致空指针异常。
- **性能问题**：每次调用都会遍历视图层次结构，可能影响性能。

------

### 使用 ViewBinding 方法

ViewBinding 是 Jetpack 提供的一种类型安全、空安全的控件访问方式。它在编译时生成绑定类，直接引用控件，避免了类型转换和空指针异常的问题。例如：

```kotlin
val binding = ActivityMainBinding.inflate(layoutInflater)
setContentView(binding.root)
val textView: TextView = binding.textView
```

**优点：**

- **类型安全**：生成的绑定类直接引用控件，避免了类型转换问题。
- **空安全**：如果控件未在布局中定义，对应的绑定属性为 `null`，避免了空指针异常。
- **性能优化**：绑定类在编译时生成，运行时无需再次查找控件，提升性能。

**缺点：**

- **需要启用 ViewBinding**：需要在 `build.gradle` 文件中启用 ViewBinding。

| 特性       | `findViewById`       | ViewBinding            |
| ---------- | -------------------- | ---------------------- |
| 类型安全   | ❌ 手动类型转换       | ✅ 自动类型匹配         |
| 空安全     | ❌ 可能导致空指针异常 | ✅ 自动处理空值         |
| 性能       | ❌ 每次查找控件       | ✅ 编译时生成绑定类     |
| 使用复杂度 | ✅ 简单               | ✅ 需要启用 ViewBinding |
| 适用场景   | 小型项目、简单布局   | 中大型项目、复杂布局   |

------

### 启用 ViewBinding（需要修改gradle文件）

在项目中启用 ViewBinding 的步骤如下：

1. 在 `build.gradle` 文件中启用 ViewBinding：

   ```gradle
   android {
       ...
       viewBinding {
           enabled = true
       }
   }
   ```

2. 在 Activity 或 Fragment 中使用 ViewBinding：

   ```kotlin
   val binding = ActivityMainBinding.inflate(layoutInflater)
   setContentView(binding.root)
   ```

   这样，您就可以通过 `binding.textView` 直接访问控件，而无需使用 `findViewById`。

## Activity使用最简单的Options Menu的办法

Options Menu 的典型流程：

1. 你在 `res/menu/*.xml` 定义菜单资源（`<menu>` + `<item>`）。
2. 系统（或 AppCompat 的框架）在需要时创建一个 `Menu` 对象并调用 Activity 的 `onCreateOptionsMenu(menu)` —— 在这里你用 `menuInflater.inflate()` 把 XML 转成 `Menu` 项。
3. 菜单显示前会调用 `onPrepareOptionsMenu(menu)`，你可以在这里做按状态修改（可见性、enable 等）。
4. 用户点击菜单项时，系统调用 `onOptionsItemSelected(item)`，你在这里处理点击逻辑。
5. 当你希望运行时刷新菜单，调用 `invalidateOptionsMenu()`（Activity 方法），系统会触发 `onPrepareOptionsMenu()`（必要时会重建）。

### 基本菜单资源（XML）

`res/menu/menu_main.xml`（示例）

```xml
<menu xmlns:android="http://schemas.android.com/apk/res/android"
      xmlns:app="http://schemas.android.com/apk/res-auto">
    <item
        android:id="@+id/action_search"
        android:title="@string/search"
        android:icon="@drawable/ic_search"
        app:showAsAction="ifRoom|collapseActionView"
        app:actionViewClass="androidx.appcompat.widget.SearchView" />
    <item
        android:id="@+id/action_settings"
        android:title="@string/settings"
        app:showAsAction="never" />
</menu>
```

- `app:showAsAction`：控制是否直接显示在 Toolbar（action）或放入 overflow。务必用 `app` 命名空间（`res-auto`）。
- 可用属性：`android:id`、`android:title`、`android:icon`、子 `<menu>`、`<group>`、`android:checkableBehavior` 等。

### 在 Activity 中 inflate 菜单

`MenuInflater.inflate(int menuRes, Menu menu)` —— 将 XML 转为 Menu 项。通常在：

```kotlin
override fun onCreateOptionsMenu(menu: Menu): Boolean {
    menuInflater.inflate(R.menu.menu_main, menu)
    // 可在这里初始化 actionView（SearchView 等）
    return true // 返回 true 表示要显示菜单
}
```

**注意**：返回 `true` 很关键——否则不会显示菜单。

### 动态更新菜单

- `onPrepareOptionsMenu(menu: Menu): Boolean`：每次菜单显示之前被调用（可以修改 `menu.findItem(id)` 的状态）。
- `invalidateOptionsMenu()`（Activity 方法）：通知系统菜单需要刷新（将触发 `onPrepareOptionsMenu()`）。

示例：

```kotlin
override fun onPrepareOptionsMenu(menu: Menu): Boolean {
    menu.findItem(R.id.action_settings)?.isVisible = isLoggedIn
    return super.onPrepareOptionsMenu(menu)
}
```

### 处理菜单点击

```kotlin
override fun onOptionsItemSelected(item: MenuItem): Boolean {
    return when (item.itemId) {
        R.id.action_search -> { /* 处理 */ true }
        R.id.action_settings -> { startActivity(...) ; true }
        else -> super.onOptionsItemSelected(item)
    }
}
```

返回 `true` 表示你处理了事件；否则交给父类或系统。

### 访问/操作 Menu 与 MenuItem（常用 API）

- `menu.findItem(R.id.some)` → `MenuItem`
- `menu.add(int groupId, int itemId, int order, CharSequence title)` → 动态添加项
- `menu.removeItem(itemId)` → 删除项
- `menu.setGroupVisible(groupId, boolean)` → 整组显示/隐藏
- `menu.setGroupCheckable(groupId, true, true)` → 设置单选/多选行为

`MenuItem` 常用方法：

- `item.setVisible(boolean)`、`item.setEnabled(boolean)`、`item.setChecked(boolean)`
- `item.getActionView()` / `item.setActionView(view or layoutRes)` —— 获取或设置当作 action view 的自定义视图（例如 SearchView）
- `item.expandActionView()` / `item.collapseActionView()` —— 展开/收起 action view（如果设置了 `collapseActionView`）

### 与 Toolbar/ActionBar 的关系

- 如果你使用 `Toolbar` 并想让 it 成为 ActionBar：

```kotlin
val toolbar: Toolbar = findViewById(R.id.toolbar)
setSupportActionBar(toolbar)
```

之后菜单回调 (`onCreateOptionsMenu` / `onOptionsItemSelected`) 不变。显示与布局由 `Toolbar` 管理（它会给 `Menu` 渲染视图）。

### SearchView / actionView 的常见用法

在 `onCreateOptionsMenu()` 初始化：

```kotlin
val searchItem = menu.findItem(R.id.action_search)
val searchView = searchItem.actionView as? SearchView
searchView?.setOnQueryTextListener(object: SearchView.OnQueryTextListener {
    override fun onQueryTextSubmit(query: String): Boolean { doSearch(query); return true }
    override fun onQueryTextChange(newText: String): Boolean = false
})
```