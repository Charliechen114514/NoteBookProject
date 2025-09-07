# QML速学笔记

## 前言

​	笔者最近正在学习QML（粗浅的了解一下），所以这里是笔者的相关的一个检查笔记，大部分笔记是AI整理的，不保证正确性，这里更多的是存个档，需要的时候看一眼！

## QML的开始：Window

#### 什么是 `Window`？

`Window` 是一个**不可见的容器**，它代表了操作系统中的一个顶级窗口。它不直接显示内容，而是作为您所有可见 QML 元素的承载者。当您创建一个 QML 应用程序时，通常会从一个 `Window` 开始，并将您的用户界面内容（如按钮、文本、图片等）放置在其中。

#### `Window` 的常见属性

##### 1. `visible: bool`

- **作用**: 控制窗口是否可见。

- **示例**:

  ```
  Window {
      visible: true // 窗口一开始就显示
      // ...
  }
  ```

- **解释**: 这是最基本的属性。通常您会将其设置为 `true`，否则您的窗口将不会显示出来。这个就相当于我们的setVisible了，我们自己写窗口也会在最后调用一个show，这里实际上就是声明式的陈述她所应该的状态是true，可见的！这在我们之后的QML学习中要转变思维（实际上更加简单的了一些）

##### 2. `width: int` 和 `height: int`（长和宽）

- **作用**: 设置窗口的宽度和高度（以像素为单位）。

- **示例**:

  ```
  Window {
      width: 800
      height: 600
      // ...
  }
  ```

- **解释**: 这决定了您的应用程序窗口的大小。您可以根据需要调整这些值。

##### 3. `title: string`

- **作用**: 设置窗口的标题栏文本。

- **示例**:

  ```
  Window {
      title: "我的第一个 QML 应用"
      // ...
  }
  ```

- **解释**: 这个标题通常显示在操作系统的窗口顶部，用于标识您的应用程序。

#### 4. `minimumWidth: int` 和 `minimumHeight: int`

- **作用**: 设置窗口可以缩小的最小宽度和高度。

- **示例**:

  ```
  Window {
      minimumWidth: 300
      minimumHeight: 200
      // ...
  }
  ```

- **解释**: 这可以防止用户将窗口缩小到无法使用的程度。

##### 5. `maximumWidth: int` 和 `maximumHeight: int`

- **作用**: 设置窗口可以放大的最大宽度和高度。

- **示例**:

  ```
  Window {
      maximumWidth: 1200
      maximumHeight: 900
      // ...
  }
  ```

- **解释**: 如果您不希望用户将窗口放大得太大，可以使用这些属性。

##### 6. `flags: Qt.WindowFlags`

- **作用**: 控制窗口的各种标志，例如是否显示边框、是否是工具窗口等。这是一个比较高级的属性，通常通过位或 (`|`) 操作来组合多个标志。

- **常见标志**:

  - `Qt.Window`: 普通的顶级窗口（默认）。
  - `Qt.FramelessWindowHint`: 无边框窗口。
  - `Qt.Tool`: 工具窗口（通常没有任务栏图标，并且在某些系统上可能表现不同）。
  - `Qt.WindowStaysOnTopHint`: 窗口始终置顶。

- **示例**:

  ```
  Window {
      // 创建一个无边框且始终置顶的窗口
      flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
      // ...
  }
  ```

- **解释**: 这个属性非常强大，但使用时需要注意，因为它会改变窗口与操作系统的交互方式。

##### 7. `color: color`

- **作用**: 设置窗口的背景颜色。

- **示例**:

  ```
  Window {
      color: "lightblue" // 设置窗口背景为浅蓝色
      // ...
  }
  ```

- **解释**: 如果您的窗口中没有内容填充整个区域，或者您希望设置一个默认背景色，这个属性就很有用。

------



#### 8. `x: int` 和 `y: int`

- **作用**: 设置窗口在屏幕上的 X 和 Y 坐标。（这里说的就是我们的窗口相对于您的物理屏幕的位置）

- **示例**:

  ```
  Window {
      x: 100 // 距离屏幕左边缘100像素
      y: 100 // 距离屏幕上边缘100像素
      // ...
  }
  ```

- **解释**: 这允许您在应用程序启动时精确控制窗口的位置。

------



##### 9. `modality: Qt.WindowModality` (通常用于对话框)

- **作用**: 定义窗口的模态类型，即它如何阻止其他窗口的交互。通常用于对话框。

- **常见类型**:

  - `Qt.NonModal`: 非模态，不阻止其他窗口。
  - `Qt.WindowModal`: 窗口模态，阻止父窗口，但不阻止其他顶级窗口。
  - `Qt.ApplicationModal`: 应用程序模态，阻止整个应用程序中的所有窗口。

- **示例**:

  ```
  Window {
      modality: Qt.ApplicationModal // 这是一个应用程序模态对话框
      // ...
  }
  ```

- **解释**: 当您需要一个弹出窗口（如确认框或设置面板）来强制用户在继续之前进行交互时，这个属性非常有用。

## 一个超级简单的示例

```
// main.qml
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15 // 引入一些控件，比如 Button

Window {
    width: 400
    height: 300
    visible: true
    title: "我的演示窗口"
    minimumWidth: 200
    minimumHeight: 150
    color: "lightgray" // 窗口背景色

    // 在窗口中放置一些内容
    // 这里就是说放置一个矩形，他的位置由anchors.centerIn描述
    Rectangle {
        width: 100
        height: 100
        color: "teal"
        anchors.centerIn: parent // 居中显示在窗口中

        Text { // 文本信息
            text: "Hello QML!"
            color: "white"
            font.pointSize: 18
            anchors.centerIn: parent
        }
    }

    Button {
        text: "点击我"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        onClicked: {
            console.log("按钮被点击了！")
        }
    }
}
```

​	上面是笔者开始写的一个小demo，具体的内容我们会在之后进行进一步深入的理解

## Rectangle：标准图形 与 Item 视觉组件

------

### 🟥 `Rectangle` 常见属性

`Rectangle` 是 QML 中最常用的可视化组件之一，用于创建彩色矩形、背景容器、按钮等视觉元素。

##### `width` / `height`

- 类型：`int`
- 作用：设置矩形的宽度和高度。

```qml
Rectangle {
    width: 100
    height: 50
}
```

##### `color`

- 类型：`color`
- 作用：设置矩形的填充颜色。

```qml
Rectangle {
    color: "skyblue"
}
```

##### `radius`

- 类型：`int`
- 作用：设置圆角半径，值越大，角越圆。

```qml
Rectangle {
    radius: 10
}
```

##### `border.width` / `border.color`

- 类型：`int` / `color`
- 作用：设置边框的宽度和颜色。

```qml
Rectangle {
    border.width: 2
    border.color: "black"
}
```

##### `anchors` 系列

- 类型：`AnchorLine`
- 作用：用于定位和布局，例如居中、对齐父组件等。

```qml
Rectangle {
    anchors.centerIn: parent
}
```

------

### 🧱 `Item` 常见属性

`Item` 是 QML 中所有视觉组件的基类，不能直接看到它的样子，但它用于构建布局、容器、逻辑结构等。

##### `x` / `y`

- 类型：`int`
- 作用：设置 Item 的坐标（相对于父组件的左上角）。

```qml
Item {
    x: 50
    y: 100
}
```

##### `width` / `height`

- 同 `Rectangle`，用于设置尺寸。

##### `visible`

- 类型：`bool`
- 作用：控制组件是否可见。

```qml
Item {
    visible: false  // 不显示该组件
}
```

##### `opacity`

- 类型：`real`（0.0 ~ 1.0）
- 作用：设置不透明度。

```qml
Item {
    opacity: 0.5  // 半透明
}
```

##### `parent`

- 类型：`Item`
- 作用：表示该组件的父对象，通常用于动态创建或引用父布局。

------

### 🔁 共通属性提示

| 属性名         | Rectangle | Item | 说明         |
| -------------- | --------- | ---- | ------------ |
| width / height | ✅         | ✅    | 设置大小     |
| x / y          | ✅         | ✅    | 控制位置     |
| anchors        | ✅         | ✅    | 用于自动布局 |
| visible        | ✅         | ✅    | 控制可见性   |
| opacity        | ✅         | ✅    | 控制透明度   |
| rotation       | ✅         | ✅    | 控制旋转角度 |

------

## 🧩 QML中的 `states` 和 `transitions` 简介

​	我们知道，**组件的各个状态可以被描述为各个分立的状态，和描述我从一个状态到达另一个状态的时候，控件需要做什么**，QML在这里就提供了两个如下的抽象：

- `states`（状态）用于**描述组件的多种可能状态**（例如折叠 / 展开、激活 / 禁用等）。
- `transitions`（过渡）用于定义**状态之间切换的动画效果**。

------

### 🔀 `states` —— 定义多种状态

##### `name`

- 类型：`string`
- 说明：状态的名字，用于切换。

```qml
states: [
    State {
        name: "expanded"
        PropertyChanges { target: rect; width: 300 }
    }
]
```

##### `when`

- 类型：`bool`
- 说明：定义状态何时自动激活（布尔条件触发）。

```qml
State {
    name: "highlighted"
    when: mouseArea.containsMouse
}
```

##### `PropertyChanges`

- 类型：特殊 QML 类型
- 说明：用于声明状态激活后，要**修改哪些属性的值**。

```qml
State {
    name: "collapsed"
    PropertyChanges {
        target: rect
        width: 100
        color: "gray"
    }
}
```

##### `StateGroup`（可选，进阶）

- 类型：容器
- 说明：如果需要在一个组件内**管理多个状态组**，可以使用它。

------

### 🧮 状态切换示例

```qml
Rectangle {
    id: rect
    width: 100; height: 100
    color: "blue"

    MouseArea {
        anchors.fill: parent
        onClicked: rect.state = rect.state === "big" ? "" : "big"
    }

    states: State {
        name: "big"
        PropertyChanges {
            target: rect
            width: 300
            color: "red"
        }
    }
}
```

------

### 🎞️ `transitions` —— 定义状态切换动画

##### `from` / `to`

- 类型：`string`
- 说明：指定**哪些状态切换**时应用此动画。

```qml
Transition {
    from: "*"
    to: "big"
    NumberAnimation { properties: "width,color"; duration: 500 }
}
```

##### `reversible`

- 类型：`bool`
- 说明：动画是否可逆（从 `to` 到 `from` 同样生效）。

```qml
Transition {
    from: "small"; to: "big"
    reversible: true
    NumberAnimation { properties: "width"; duration: 200 }
}
```

##### 动画类型（常见）

- `NumberAnimation`：用于数值属性，如 `width`, `opacity`, `x`, `rotation` 等。
- `ColorAnimation`：用于颜色属性。
- `PropertyAnimation`：通用型。
- `SequentialAnimation` / `ParallelAnimation`：串行动画 / 并行动画。

------

### 💡 示例：加上 `transition` 动画

```qml
Rectangle {
    id: rect
    width: 100; height: 100
    color: "blue"

    MouseArea {
        anchors.fill: parent
        onClicked: rect.state = rect.state === "big" ? "" : "big"
    }

    states: State {
        name: "big"
        PropertyChanges {
            target: rect
            width: 300
            color: "orange"
        }
    }

    transitions: Transition {
        from: "*"; to: "big"
        reversible: true
        ParallelAnimation {
            NumberAnimation { properties: "width"; duration: 400 }
            ColorAnimation { property: "color"; duration: 400 }
        }
    }
}
```

------

### 📌 进阶 Tips

##### 动态绑定 + 状态组合

```qml
Rectangle {
    // 自动根据条件切换状态
    state: isLoggedIn ? "authenticated" : "guest"
}
```

##### 同时改变多个组件状态

```qml
State {
    name: "focused"
    PropertyChanges { target: rect1; color: "red" }
    PropertyChanges { target: rect2; opacity: 1.0 }
}
```

| 特性     | `states`                   | `transitions`                          |
| -------- | -------------------------- | -------------------------------------- |
| 用途     | 定义多种属性组合的“状态”   | 定义从一种状态到另一种的“动画”         |
| 结构     | State + PropertyChanges    | Transition + 动画元素                  |
| 响应方式 | 赋值 `state` 或设置 `when` | 自动触发，无需手动调用                 |
| 配合方式 | 多状态配合使用             | 可为每对状态指定动画，或使用通配符 `*` |

------

## 🧱 `Component` 与 `Loader` 在 QML 中的作用

​	这个的应用场景在于，我们可能希望一些UI组件是被按照给定的条件创建出来的，我们知道QML是声明式的，写上了就会有，但是我们的确存在一些天然的场景——只有一些条件满足的时候，我们的界面上才会产生一些组件，这个时候，我们就需要请出来下面两个：

- `Component`：定义**可复用的 UI 模板**（逻辑上存在，未实际创建）。
- `Loader`：用于**动态加载**这些组件（或者任何 QML 对象），并在运行时插入到界面中。

两者配合使用，能够实现**延迟加载、按需创建、动态界面切换**等复杂应用逻辑。

------

## 🧩 `Component` —— 定义组件模板

##### `Component` 是什么？

`Component` 是一种**不立即创建实例**的 QML 容器，常用于定义**可复用或延迟实例化的 UI 模板**。

```qml
Component {
    id: redBox
    Rectangle {
        width: 100; height: 100
        color: "red"
    }
}
```

------

### ✅ `Component` 常见用法

##### `id`

- 类型：`string`
- 说明：给这个组件一个唯一标识，可被 `Loader` 或 `createObject()` 引用。

##### 用于 `Loader.sourceComponent`

```qml
Loader {
    id: myLoader
    sourceComponent: redBox  // 引用上面定义的 Component
}
```

##### 用于 `Component.createObject(parent)`

- 动态创建一个实例，传入父对象：

```qml
Component.onCompleted: {
    var item = redBox.createObject(parent, { x: 100, y: 200 });
}
```

##### 用于 `ListView` / `Repeater` 的 delegate

```qml
ListView {
    model: 3
    delegate: Component {
        Rectangle {
            width: 50; height: 50
            color: "blue"
        }
    }
}
```

------

### 🧱 `Component` 使用注意事项

| 特性           | 描述                                                        |
| -------------- | ----------------------------------------------------------- |
| 不自动渲染     | 只有在被引用（如 Loader、ListView）时才实例化               |
| 可定义多个组件 | 每个 `Component` 只能定义一个顶层对象（如 Rectangle、Item） |
| 支持动态创建   | 搭配 `createObject()` 和 `Loader` 可实现高级动态 UI         |

------

## 📦 `Loader` —— 延迟与动态加载组件

##### `Loader` 是什么？

`Loader` 是 QML 的动态装载器，可在运行时根据需要**加载外部 QML 文件、Component、对象实例**等。

------

### ✅ `Loader` 常见属性

##### `source`

- 类型：`url`
- 说明：加载一个 `.qml` 文件

```qml
Loader {
    source: "MyComponent.qml"
}
```

##### `sourceComponent`

- 类型：`Component`
- 说明：加载一个内联定义的组件

```qml
Loader {
    sourceComponent: redBox
}
```

##### `active`

- 类型：`bool`
- 说明：是否立即加载组件（可实现懒加载）

```qml
Loader {
    source: "HeavyView.qml"
    active: false
}
```

##### `item`

- 类型：`Item`（只读）
- 说明：指向加载出来的实例对象，可用于访问其属性或方法。

```qml
Component.onCompleted: {
    myLoader.item.width = 200
}
```

##### `onLoaded`

- 说明：在组件加载完成后执行（常用于初始化）

```qml
Loader {
    id: myLoader
    onLoaded: console.log("Loaded:", item)
}
```

------

### 🧪 `Loader` 使用示例

#### 使用 `sourceComponent` 加载内联组件

```qml
Component {
    id: greenBox
    Rectangle {
        width: 100; height: 100
        color: "green"
    }
}

Loader {
    id: dynamicLoader
    anchors.centerIn: parent
    sourceComponent: greenBox
}
```

#### 使用 `source` 加载外部文件

```qml
// main.qml
Loader {
    source: "Dialog.qml"
}
// Dialog.qml
Rectangle {
    width: 300; height: 200
    color: "lightgray"
}
```

------

### 🔄 `Loader` 常用技巧

##### 延迟加载大组件

```qml
Loader {
    source: "BigPage.qml"
    active: pageVisible
}
```

##### 卸载组件释放内存

```qml
Loader {
    id: dynamicView
    source: "Chart.qml"
}

Button {
    text: "卸载"
    onClicked: dynamicView.source = ""
}
```

##### 动态切换不同组件

```qml
Loader {
    id: switcher
    sourceComponent: state === "edit" ? editBox : viewBox
}
```

------

### 🔧 `Loader` 与 `Component` 配合逻辑图

```
[Component { id: myComp }]  --> 引用 -->  [ Loader { sourceComponent: myComp } ]
                                  \--> createObject() 手动实例化
```

------

### 📌 总结对比

| 特性         | `Component`                      | `Loader`                                  |
| ------------ | -------------------------------- | ----------------------------------------- |
| 类型         | 模板（未实例化）                 | 控件（动态创建实例）                      |
| 是否可见     | 不可见（逻辑层）                 | 可见（加载后有 UI）                       |
| 使用场景     | 提供延迟模板、委托、可复用结构   | 实时加载、按需创建/销毁组件               |
| 支持外部 QML | ❌                                | ✅ 使用 `source: "xx.qml"`                 |
| 与动画联动   | 常与 `State`、`ListView` 配合    | 可与 `Behavior`、状态切换配合实现动态加载 |
| 动态参数绑定 | createObject(parent, properties) | 可通过 `Loader.item` 修改                 |

当然可以！以下是对 **QML 中各种动画机制的深入全面讲解**，内容涵盖常见动画类型、使用场景、语法细节与进阶技巧，适用于初学者到进阶开发者的全面了解。依然使用你要求的 **Markdown五级标题（#####）**。

------

## 🌀 QML 动画体系总览

QML 的动画是基于属性驱动的，核心理念是：**属性发生变化时，可定义其变化过程（插值）为动画**。你无需手动插值帧数，只需声明属性如何随时间变化。

------

## 🎯 QML 动画的分类

| 动画类型              | 说明                                                 | 使用方式               |
| --------------------- | ---------------------------------------------------- | ---------------------- |
| `NumberAnimation`     | 对数值属性（如 `x`, `width`, `opacity`）进行插值动画 | 最常见                 |
| `ColorAnimation`      | 对颜色属性（如 `color`）进行平滑变换                 | 过渡色彩、状态变化     |
| `PropertyAnimation`   | 更通用，适用于任意支持插值的属性                     | 用于动态选择类型的场景 |
| `RotationAnimation`   | 用于旋转角度动画                                     | 对 `rotation` 属性使用 |
| `ScaleAnimator`       | 对 `scale` 属性执行动画                              | Qt 6.5+ 支持           |
| `Behavior`            | 属性变化时自动应用某种动画                           | 自动触发，适合精细过渡 |
| `SequentialAnimation` | 一系列动画顺序执行                                   | 动画脚本流程           |
| `ParallelAnimation`   | 一系列动画并行执行                                   | 同步多个属性变化       |
| `PauseAnimation`      | 插入动画暂停（延时）                                 | 常配合顺序动画使用     |
| `SmoothedAnimation`   | 类似惯性动画，自动调节速度                           | Qt Quick Controls 常见 |
| `SpringAnimation`     | 模拟弹簧回弹行为                                     | 适合交互后过渡动画     |
| `PathAnimation`       | 沿路径运动                                           | 高级运动轨迹动画       |

------

### 🔢 `NumberAnimation`

##### 作用：对数值类属性（如 `x`, `opacity`, `width`）进行线性或非线性动画插值。

```qml
Rectangle {
    id: box
    width: 100; height: 100; color: "blue"

    MouseArea {
        anchors.fill: parent
        onClicked: anim.running = true
    }

    NumberAnimation {
        id: anim
        target: box
        property: "x"
        to: 300
        duration: 1000
        easing.type: Easing.InOutQuad
    }
}
```

##### 常用属性：

- `duration`: 动画时长（毫秒）
- `from`, `to`: 起始与结束值
- `easing`: 缓动函数，支持 `Easing.InQuad`、`Easing.OutElastic` 等

------

### 🎨 `ColorAnimation`

##### 作用：对颜色类属性进行平滑渐变。

```qml
ColorAnimation {
    target: rect
    property: "color"
    from: "red"
    to: "green"
    duration: 800
}
```

------

### 🧱 `PropertyAnimation`

##### 作用：通用动画类型，可自动推断动画类型（颜色、数字等）

```qml
PropertyAnimation {
    target: item
    property: "opacity"
    to: 1.0
    duration: 500
}
```

------

### 🔄 `RotationAnimation`

##### 作用：让物体围绕某个轴旋转。

```qml
RotationAnimation {
    target: image
    property: "rotation"
    from: 0; to: 360
    loops: Animation.Infinite
    duration: 3000
}
```

------

### 🤖 `Behavior` —— 自动动画绑定

##### 作用：为某个属性定义默认动画，在属性值变化时自动执行。

```qml
Rectangle {
    width: 100; height: 100; color: "blue"

    Behavior on x {
        NumberAnimation { duration: 400; easing.type: Easing.InOutCubic }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.x += 200
    }
}
```

------

### ⛓️ `SequentialAnimation` & `ParallelAnimation`

##### 顺序执行多个动画：

```qml
SequentialAnimation {
    NumberAnimation { target: box; property: "x"; to: 300; duration: 300 }
    PauseAnimation { duration: 200 }
    NumberAnimation { target: box; property: "y"; to: 300; duration: 300 }
}
```

##### 并行执行多个动画：

```qml
ParallelAnimation {
    NumberAnimation { target: box; property: "x"; to: 300; duration: 500 }
    NumberAnimation { target: box; property: "y"; to: 200; duration: 500 }
}
```

------

### 🌠 `SpringAnimation`（弹性回弹）

##### 作用：模拟弹簧拉伸后回弹的惯性动画（物理系）

```qml
Rectangle {
    id: box
    width: 100; height: 100; color: "red"
    SpringAnimation on x {
        spring: 3
        damping: 0.2
        to: 400
    }
}
```

------

### 🚶‍♂️ `PathAnimation`（路径动画）

##### 作用：让元素按路径（如圆形轨迹）移动。

```qml
PathAnimation {
    duration: 4000
    target: circle
    path: Path {
        startX: 0; startY: 0
        PathQuad { x: 300; y: 100; controlX: 150; controlY: -100 }
        PathLine { x: 0; y: 0 }
    }
    loops: Animation.Infinite
}
```

------

### ⛏️ 动画控制属性通用表

| 属性名        | 说明                                 |
| ------------- | ------------------------------------ |
| `duration`    | 动画持续时间（单位 ms）              |
| `loops`       | 动画循环次数（`Animation.Infinite`） |
| `running`     | 当前是否正在运行动画                 |
| `paused`      | 是否暂停                             |
| `from` / `to` | 起始值 / 目标值                      |
| `easing`      | 缓动函数控制变化节奏                 |
| `target`      | 动画目标元素                         |
| `property`    | 作用的属性名称                       |

------

### ✨ 实战技巧与建议

##### 动画响应状态变化（推荐方式）：

```qml
states: [
    State {
        name: "expanded"
        PropertyChanges { target: box; width: 300 }
    }
]

transitions: Transition {
    NumberAnimation { properties: "width"; duration: 300 }
}
```

##### 动画完结回调：

```qml
NumberAnimation {
    onStopped: console.log("动画已结束")
}
```

##### 动画控制（start/stop）：

```qml
MouseArea {
    onClicked: anim.running ? anim.stop() : anim.start()
}
```

------

### 🧭 小结：QML 动画选择建议

| 目的             | 推荐类型                                |
| ---------------- | --------------------------------------- |
| 改变数字、坐标   | `NumberAnimation`                       |
| 改变颜色         | `ColorAnimation`                        |
| 同时动画多个属性 | `ParallelAnimation`                     |
| 动画绑定属性变化 | `Behavior`                              |
| 复杂动画组合     | `SequentialAnimation`                   |
| 惯性 / 物理效果  | `SpringAnimation` / `SmoothedAnimation` |
| 沿轨迹移动       | `PathAnimation`                         |

## 🖱️ MouseArea

`MouseArea` 是 QML 中最常用的交互区域组件，用于处理鼠标事件，比如点击、按下、释放、悬停、拖动等。

它本身是**不可见的区域**，通常放在视觉组件（如 `Rectangle`）上，用于添加用户交互功能。

------

### ✅ 常见用途

- 实现按钮点击响应
- 拖动组件
- 鼠标悬停变色
- 长按检测
- 多点触控处理（进阶）

------

## 🛠️ 常用属性与信号

### 常用属性

##### `anchors.fill`

- 用于让 `MouseArea` 填满其父组件，常见写法：

```qml
MouseArea {
    anchors.fill: parent
}
```

##### `enabled`

- 控制是否启用该区域，`false` 表示不响应事件：

```qml
MouseArea {
    enabled: false
}
```

##### `hoverEnabled`

- 默认是 `false`，设置为 `true` 才能捕捉 `onEntered` / `onExited` 悬停事件。

```qml
hoverEnabled: true
```

##### `cursorShape`

- 控制鼠标指针样式（如手型、十字等）：

```qml
cursorShape: Qt.PointingHandCursor
```

### 常用信号

#### `onClicked`

- 鼠标**按下并释放**（点击）后触发：

```qml
onClicked: console.log("Clicked at:", mouse.x, mouse.y)
```

#### `onPressed` / `onReleased`

- `onPressed`：鼠标按下
- `onReleased`：鼠标松开

```qml
onPressed: console.log("Mouse Down")
onReleased: console.log("Mouse Up")
```

#### `onDoubleClicked`

- 鼠标**双击**触发（需要设置 `acceptedButtons` 支持左键）：

```qml
onDoubleClicked: console.log("Double click!")
```

#### `onEntered` / `onExited`

- 鼠标进入 / 离开区域，需开启 `hoverEnabled: true`：

```qml
hoverEnabled: true
onEntered: rect.color = "yellow"
onExited: rect.color = "blue"
```

#### `onPositionChanged`

- 鼠标移动时触发，可用于实现拖拽、绘图等：

```qml
onPositionChanged: console.log("x:", mouse.x, "y:", mouse.y)
```

------

### 🧰 拖动示例：使用 `MouseArea` 拖动组件

```qml
Rectangle {
    width: 100; height: 100
    color: "orange"

    MouseArea {
        anchors.fill: parent
        drag.target: parent
    }
}
```

> 💡 注意：设置 `drag.target` 可以让指定元素跟随鼠标拖动。

------

### 🎯 限定点击键位：`acceptedButtons`

```qml
MouseArea {
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onClicked: console.log("Clicked with:", mouse.button)
}
```

> 支持常用值：
>
> - `Qt.LeftButton`
> - `Qt.RightButton`
> - `Qt.MiddleButton`

------

### 📦 综合示例：按钮效果 + 悬停反馈

```qml
Rectangle {
    width: 150; height: 50
    color: mouseArea.containsMouse ? "lightgreen" : "lightgray"
    border.color: "black"

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: console.log("Button clicked")
    }

    Text {
        anchors.centerIn: parent
        text: "Click Me"
    }
}
```

------

### 🧠 小技巧与建议

- `MouseArea` 本身不可见，调试时可暂时设置 `Rectangle` 包裹以查看。
- 鼠标拖拽可以配合 `drag.target`、`drag.axis`、`drag.minimumX/Y` 限制方向或范围。
- 如果多个 `MouseArea` 重叠，最上层的优先响应。
- 想屏蔽事件传递，可设置 `preventStealing: true`。

------

## 🧩 什么是 QML 的 Property？

在 QML 中，**`property` 是组件之间通信和状态同步的核心机制**。QML 组件的几乎所有特性（如 `width`、`color`、`opacity`）都是属性。你也可以通过 `property` 关键字声明**自定义属性**，用于数据绑定、状态控制、动画等功能。

------

## ✍️ Property 的声明方式

QML 中声明属性的基本语法如下：

```qml
property <type> <name>: <defaultValue>
```

### 示例

```qml
Rectangle {
    width: 200; height: 200
    color: customColor

    property color customColor: "skyblue"
}
```

------

## 🛠️ Property 常见类型

| 类型     | 描述                     | 示例值               |
| -------- | ------------------------ | -------------------- |
| `int`    | 整数                     | `42`                 |
| `real`   | 浮点数                   | `3.14`               |
| `bool`   | 布尔值                   | `true` / `false`     |
| `string` | 字符串                   | `"hello"`            |
| `color`  | 颜色（可用英文或 HEX）   | `"red"`, `"#ffaa00"` |
| `url`    | 文件或资源路径           | `"file.txt"`         |
| `var`    | 动态类型（任何类型）     | `[1, 2, 3]`，`{} `   |
| `alias`  | 属性别名（指向其他属性） | `alias x: rect.x`    |

------

## 🧠 Property 的特点与行为

### 1. **支持双向绑定（自动响应）**

属性可自动响应其他属性的变化（数据绑定）：

```qml
Rectangle {
    width: 200; height: 200
    property int boxSize: 100

    Rectangle {
        width: parent.boxSize
        height: parent.boxSize
        color: "orange"
    }
}
```

当 `boxSize` 改变时，子矩形会自动跟随更新。

------

### 2. **支持信号机制（用于属性变化监听）**

每个属性自动生成一个 `on<PropertyName>Changed` 信号：

```qml
property string username: "guest"

onUsernameChanged: console.log("Username is now:", username)
```

------

### 3. **可以设置为动态表达式（带计算）**

```qml
property int doubleWidth: width * 2
```

> 注意：这种属性是「只读的表达式」，不是可赋值变量。

------

### 4. **可定义在任意组件内**

你可以在任何 Item、Rectangle、Button 等组件中定义自定义属性，来简化传值和逻辑分离。

------

### 🔄 `property alias`（属性别名）

#### 用法

用于**将内部组件的属性暴露到外部组件**，便于封装和复用。

```qml
Item {
    Rectangle {
        id: innerRect
        width: 100
    }

    property alias innerWidth: innerRect.width
}
```

这样外部就可以通过 `myItem.innerWidth` 访问或控制 `innerRect` 的宽度。

------

### 💼 `property var`（动态类型属性）

- `var` 表示动态类型，可以绑定任意值（数组、对象、组件等）
- 用于灵活存储动态数据

```qml
property var info: { name: "Charlie", age: 22 }
```

你可以这样访问：

```qml
Text { text: "Name: " + info.name }
```

------

### 📦 使用场景汇总

| 使用目的     | 示例说明                                              |
| ------------ | ----------------------------------------------------- |
| 数据传递     | 父子组件传递属性值                                    |
| 动态 UI 响应 | 绑定属性，实现状态驱动 UI                             |
| 封装组件参数 | 使用 `alias` 将内部属性暴露出来                       |
| 监听属性变更 | 使用 `on<Property>Changed` 处理事件逻辑               |
| 动画绑定     | 属性 + `Behavior`/`states`/`transitions` 实现平滑过渡 |

------

### 📌 示例：自定义控件封装参数

```qml
// MyButton.qml
Rectangle {
    property string label: "Click Me"

    width: 100; height: 40
    color: "lightblue"

    Text {
        anchors.centerIn: parent
        text: label
    }
}
// main.qml
MyButton {
    label: "确定"
}
```

------

## 🔘 Button 简介

`Button` 是 QML 提供的基础 UI 控件之一，属于 `QtQuick.Controls` 模块，用于接收用户点击操作，常见于表单、对话框、工具栏等场景。

你可以使用默认样式，也可以完全自定义它的外观。

> 使用前需导入：

```qml
import QtQuick.Controls 2.15
```

------

## ⚙️ 常用属性

### `text`

- 显示在按钮上的文本内容。

```qml
Button {
    text: "确定"
}
```

### `enabled`

- 是否可用，设置为 `false` 将禁用按钮（变灰）。

```qml
Button {
    text: "提交"
    enabled: isFormValid
}
```

### `visible`

- 控制按钮是否可见。

### `checked`

- 如果按钮是可选型（CheckBox / ToggleButton），该属性表示选中状态。

```qml
Button {
    text: checked ? "已开启" : "已关闭"
    checkable: true
}
```

### `checkable`

- 是否可以被“选中”或“切换”状态（像开关一样）。

------

## 📡 常用信号

### `onClicked`

- 当用户点击按钮（按下+释放）时触发。

```qml
Button {
    text: "登录"
    onClicked: console.log("按钮被点击")
}
```

### `onPressed` / `onReleased`

- `onPressed`：鼠标按下
- `onReleased`：鼠标松开

### `onCheckedChanged`

- 当按钮选中状态发生改变（在 `checkable: true` 时）

------

## 🎨 样式和外观定制

你可以通过 `contentItem`、`background` 等方式自定义按钮外观。

### 简单改颜色：

```qml
Button {
    text: "高亮"
    background: Rectangle {
        color: control.pressed ? "#66ccff" : "#99ccff"
        radius: 6
    }
}
```

### 自定义文字样式：

```qml
Button {
    contentItem: Text {
        text: control.text
        font.bold: true
        color: "white"
        anchors.centerIn: parent
    }
}
```

------

## 🧰 使用场景示例

### 切换按钮状态：

```qml
Button {
    id: toggleBtn
    text: checked ? "开启中" : "关闭中"
    checkable: true
    checked: false

    onCheckedChanged: {
        console.log("开关状态变化:", checked)
    }
}
```

### 禁用按钮直到数据加载完成：

```qml
Button {
    text: "提交"
    enabled: dataReady
}
```

------

## 📦 组合使用建议

### 搭配 `Dialog` 弹窗：

```qml
Button {
    text: "打开对话框"
    onClicked: myDialog.open()
}

Dialog {
    id: myDialog
    title: "确认操作"
    modal: true
}
```

### 搭配 `Loader` 切换页面：

```qml
Button {
    text: "进入下一页"
    onClicked: loader.source = "NextPage.qml"
}
```

------

### 🧠 小贴士

| 场景                 | 建议用法                                   |
| -------------------- | ------------------------------------------ |
| 多态按钮 / 切换按钮  | 使用 `checkable: true` 和 `checked` 状态   |
| 自定义按钮样式       | 使用 `background` 和 `contentItem` 自定义  |
| 禁用按钮防止重复点击 | `enabled: false` + 条件判断                |
| 图标按钮（带图）     | 自定义 `contentItem` 添加 `Image` + `Text` |

------

### 🧪 Button vs MouseArea

| 比较项          | `Button`          | `MouseArea`                        |
| --------------- | ----------------- | ---------------------------------- |
| 是否视觉组件    | ✅ 自带视觉样式    | ❌ 需要外层包裹组件（如 Rectangle） |
| 支持焦点 / 键盘 | ✅（Tab 焦点）     | ❌                                  |
| 是否可被主题化  | ✅（支持控件样式） | ❌                                  |
| 拓展性          | 可封装 + 扩展     | 更自由，适合自定义交互逻辑         |

