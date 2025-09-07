# 深入理解Qt的SetWindowsFlags函数

​	我们接下来来仔细了解一下Qt当中一个非常重要的函数：SetWindowsFlags。

```
void QWidget::setWindowFlags(Qt::WindowFlags flags)
```

​	`setWindowFlags()`用于设置窗口的系统标志，这些标志决定了窗口如何与窗口管理器交互以及它的外观表现。我们重点主要了解的是`Qt::WindowFlags`

- **窗口类型（type）**：一个窗口只能有一种类型，如 `Qt::Window`, `Qt::Dialog` 等。
- **提示标志（hints）**：可以添加多个提示，如 `Qt::FramelessWindowHint`, `Qt::WindowStaysOnTopHint` 等，用来控制窗口的显示方式和行为。
- **更改后需重新显示**：调用后原窗口将被隐藏，修改后的 flags 会在下一次 `show()` 时生效。

​	这是上面这个函数一些比较重要的点。

我已为您生成完整的 `enum WindowType` 中文教学文档，涵盖每个枚举值的含义与用途。您可以在右侧的文档视图中阅读与编辑该文档，如需导出 PDF、添加示例代码或生成表格版对比内容，也可以继续告诉我！

#### `WindowType` 枚举详解📘

用于在 Qt 中通过 `QWidget::setWindowFlags()` 或 `QWindow::setFlags()` 设置窗口类型和行为。

```cpp
    enum WindowType {
        Widget = 0x00000000,
        Window = 0x00000001,
        Dialog = 0x00000002 | Window,
        Sheet = 0x00000004 | Window,
        Drawer = Sheet | Dialog,
        Popup = 0x00000008 | Window,
        Tool = Popup | Dialog,
        ToolTip = Popup | Sheet,
        SplashScreen = ToolTip | Dialog,
        Desktop = 0x00000010 | Window,
        SubWindow = 0x00000012, // Note QTBUG-115729 before using
        ForeignWindow = 0x00000020 | Window,
        CoverWindow = 0x00000040 | Window,

        WindowType_Mask = 0x000000ff,
        MSWindowsFixedSizeDialogHint = 0x00000100,
        MSWindowsOwnDC = 0x00000200,
        BypassWindowManagerHint = 0x00000400,
        X11BypassWindowManagerHint = BypassWindowManagerHint,
        FramelessWindowHint = 0x00000800,
        WindowTitleHint = 0x00001000,
        WindowSystemMenuHint = 0x00002000,
        WindowMinimizeButtonHint = 0x00004000,
        WindowMaximizeButtonHint = 0x00008000,
        WindowMinMaxButtonsHint = WindowMinimizeButtonHint | WindowMaximizeButtonHint,
        WindowContextHelpButtonHint = 0x00010000,
        WindowShadeButtonHint = 0x00020000,
        WindowStaysOnTopHint = 0x00040000,
        WindowTransparentForInput = 0x00080000,
        WindowOverridesSystemGestures = 0x00100000,
        WindowDoesNotAcceptFocus = 0x00200000,
        MaximizeUsingFullscreenGeometryHint = 0x00400000,

        CustomizeWindowHint = 0x02000000,
        WindowStaysOnBottomHint = 0x04000000,
        WindowCloseButtonHint = 0x08000000,
        MacWindowToolBarButtonHint = 0x10000000,
        BypassGraphicsProxyWidget = 0x20000000,
        NoDropShadowWindowHint = 0x40000000,
        WindowFullscreenButtonHint = 0x80000000
    };
```



##### 一、基础窗口类型

| 枚举值          | 十六进制     | 说明                                                   |
| --------------- | ------------ | ------------------------------------------------------ |
| `Widget`        | `0x00000000` | 普通控件，无特殊类型。常用于嵌入式子控件。             |
| `Window`        | `0x00000001` | 独立窗口，拥有顶部标题栏和边框。                       |
| `Dialog`        | `0x00000003` | 对话框类型，有独立窗口属性，适合模态/非模态对话。      |
| `Sheet`         | `0x00000005` | macOS 风格的下拉式对话，附加于窗口上方。               |
| `Drawer`        | `0x00000007` | 抽屉式面板，结合 Sheet 与 Dialog 特性。                |
| `Popup`         | `0x00000009` | 弹出式窗口，如菜单或工具提示。                         |
| `Tool`          | `0x0000000B` | 工具窗口，用于辅助工具浮动面板。                       |
| `ToolTip`       | `0x0000000D` | 工具提示窗口，支持嵌入式提示。                         |
| `SplashScreen`  | `0x0000000F` | 启动屏幕窗口，在应用启动时显示。                       |
| `Desktop`       | `0x00000011` | 桌面窗口，覆盖整个屏幕。                               |
| `SubWindow`     | `0x00000012` | 子窗口，用于多文档界面（MDI）。QTBUG-115729 注意事项。 |
| `ForeignWindow` | `0x00000021` | 嵌入非 Qt 创建的外部窗口。                             |
| `CoverWindow`   | `0x00000041` | 覆盖式窗口，如全屏遮罩层。                             |

##### 二、类型掩码

| 枚举值            | 十六进制     | 说明                       |
| ----------------- | ------------ | -------------------------- |
| `WindowType_Mask` | `0x000000ff` | 提取窗口基本类型所用掩码。 |

##### 三、Windows 特定提示

| 枚举值                         | 十六进制     | 说明                             |
| ------------------------------ | ------------ | -------------------------------- |
| `MSWindowsFixedSizeDialogHint` | `0x00000100` | 固定大小的对话框，不可调整。     |
| `MSWindowsOwnDC`               | `0x00000200` | 独立的设备上下文（HDC）。        |
| `BypassWindowManagerHint`      | `0x00000400` | 绕过窗口管理器，由应用控制窗口。 |
| `X11BypassWindowManagerHint`   | `0x00000400` | 在 X11 下作用等同于上。          |

##### 四、标题栏/边框控制

| 枚举值                        | 十六进制     | 说明                         |
| ----------------------------- | ------------ | ---------------------------- |
| `FramelessWindowHint`         | `0x00000800` | 无边框窗口，适合自定义界面。 |
| `WindowTitleHint`             | `0x00001000` | 显示窗口标题栏。             |
| `WindowSystemMenuHint`        | `0x00002000` | 提供窗口系统菜单。           |
| `WindowMinimizeButtonHint`    | `0x00004000` | 显示最小化按钮。             |
| `WindowMaximizeButtonHint`    | `0x00008000` | 显示最大化按钮。             |
| `WindowMinMaxButtonsHint`     | `0x0000C000` | 同时显示最大化和最小化按钮。 |
| `WindowContextHelpButtonHint` | `0x00010000` | 显示上下文帮助按钮（问号）。 |
| `WindowShadeButtonHint`       | `0x00020000` | 显示卷帘按钮。               |

##### 五、行为提示

| 枚举值                                | 十六进制     | 说明                     |
| ------------------------------------- | ------------ | ------------------------ |
| `WindowStaysOnTopHint`                | `0x00040000` | 窗口总在最上层。         |
| `WindowTransparentForInput`           | `0x00080000` | 不接收鼠标或键盘输入。   |
| `WindowOverridesSystemGestures`       | `0x00100000` | 覆盖系统手势（如滑动）。 |
| `WindowDoesNotAcceptFocus`            | `0x00200000` | 不接收焦点。             |
| `MaximizeUsingFullscreenGeometryHint` | `0x00400000` | 最大化时使用全屏大小。   |

##### 六、自定义/特殊提示

| 枚举值                       | 十六进制     | 说明                             |
| ---------------------------- | ------------ | -------------------------------- |
| `CustomizeWindowHint`        | `0x02000000` | 开启窗口自定义行为配置。         |
| `WindowStaysOnBottomHint`    | `0x04000000` | 窗口总在最底层。                 |
| `WindowCloseButtonHint`      | `0x08000000` | 显示关闭按钮。                   |
| `MacWindowToolBarButtonHint` | `0x10000000` | macOS 工具栏按钮支持。           |
| `BypassGraphicsProxyWidget`  | `0x20000000` | 绕过 QGraphicsProxyWidget 限制。 |
| `NoDropShadowWindowHint`     | `0x40000000` | 去除窗口阴影。                   |
| `WindowFullscreenButtonHint` | `0x80000000` | 显示全屏切换按钮（macOS）。      |

### 一些提示

- **建议使用位或组合已有 flags**，这样不会覆盖原有设置：

  ```
  w->setWindowFlags(w->windowFlags() | Qt::FramelessWindowHint);
  ```

- 而不是直接覆盖全部 flags，避免意外丢失已有设置，保持窗口行为的正确性。

- **在某些平台**（如 Windows、X11），需 `show()` 之后，才会看到 flags 的实际效果。

- **特定组合注意**：

- `FramelessWindowHint` 取消边框、标题，使窗口更灵活但可影响拖动等功能。
- `WindowStaysOnTopHint` 强制置顶，不分应用可以使用户体验出现问题，需结合 parent 参数使用。

