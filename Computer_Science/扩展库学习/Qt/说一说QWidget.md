# 说一说QWidget

​	写Qt快两年了，也写过一些规模偏大的软件，但是依旧觉得对QWidget的类比较陌生，这里整理一下笔者看到的一些笔记。供以参考翻阅！

## 关于QWidget

​	关于QWidget，他是大部分Ui控件的爹。几乎所有的常用控件都是直接或者是间接的继承了QWidget。也就是说，它实际上定义了控件的最基础属性。我们很多时候聊Ui布局感官可能就需要从这里开始顺藤摸瓜。

### 作为界面组件时，你需要有印象的

​	属性很多，我委托GPT帮助我整理了一下，下面是我审核后认为无误的部分：

#### 1. 控制属性

​	这里则是说Widget大小属性的部分，其实跟下面的外观分不开来，更多的是说Widget自身的属性。比如说窗体自身的大小策略

| 属性名称      | 类型      | 功能说明                     | 使用示例                            | 注意事项                                   |
| ------------- | --------- | ---------------------------- | ----------------------------------- | ------------------------------------------ |
| `windowTitle` | `QString` | 设置或获取窗口的标题。       | `setWindowTitle("My Application");` | 窗口标题通常在窗口的标题栏中显示。         |
| `geometry`    | `QRect`   | 设置或获取窗口的位置和大小。 | `setGeometry(100, 100, 800, 600);`  | 参数依次为窗口的x坐标、y坐标、宽度和高度。 |
| `size`        | `QSize`   | 设置或获取窗口的大小。       | `resize(800, 600);`                 | 仅修改窗口的大小，不改变位置。             |
| `minimumSize` | `QSize`   | 设置窗口的最小大小。         | `setMinimumSize(400, 300);`         | 当用户调整窗口时，不能小于该大小。         |
| `maximumSize` | `QSize`   | 设置窗口的最大大小。         | `setMaximumSize(1200, 800);`        | 当用户调整窗口时，不能大于该大小。         |
| `isVisible`   | `bool`    | 获取窗口是否可见。           | `bool visible = isVisible();`       | 该属性通常在运行时动态变化。               |

#### 2. 组件状态与交互属性

| 属性名称         | 类型              | 功能说明                               | 使用示例                                               | 注意事项                                       |
| ---------------- | ----------------- | -------------------------------------- | ------------------------------------------------------ | ---------------------------------------------- |
| `enabled`        | `bool`            | 设置或获取组件是否启用。               | `setEnabled(false);`                                   | 禁用后组件无法接收用户输入。（只能看不能用）   |
| `focusPolicy`    | `Qt::FocusPolicy` | 设置焦点策略，决定该组件如何获得焦点。 | `setFocusPolicy(Qt::StrongFocus);`                     | 可选值包括：`Qt::NoFocus`, `Qt::TabFocus`等。  |
| `toolTip`        | `QString`         | 设置或获取组件的工具提示。             | `setToolTip("This is a button.");`                     | 鼠标悬停时显示，通常用于提供附加信息。         |
| `statusTip`      | `QString`         | 设置或获取组件的状态提示。             | `setStatusTip("Click to perform action.");`            | 通常在状态栏显示，提供操作的简短描述。         |
| `whatsThis`      | `QString`         | 设置“这是什么”提示。                   | `setWhatsThis("This button starts the application.");` | 提供更详细的说明，可以通过帮助系统访问。       |
| `mouseTracking`  | `bool`            | 设置或获取组件是否跟踪鼠标移动。       | `setMouseTracking(true);`                              | 启用后，可以在`mouseMoveEvent`中处理鼠标移动。 |
| `acceptDrops`    | `bool`            | 设置组件是否接受拖放操作。             | `setAcceptDrops(true);`                                | 需要重载`dragEnterEvent`和`dropEvent`。        |
| `tabletTracking` | `bool`            | 设置或获取组件是否跟踪平板输入。       | `setTabletTracking(true);`                             | 启用后，可以在`tabletEvent`中处理平板输入。    |

#### 3. 外观和样式属性

| 属性名称             | 类型       | 功能说明                                 | 使用示例                                                     | 注意事项                                   |
| -------------------- | ---------- | ---------------------------------------- | ------------------------------------------------------------ | ------------------------------------------ |
| `styleSheet`         | `QString`  | 设置组件的样式表，定义组件的外观。       | `setStyleSheet("background-color: yellow;");`                | 使用CSS样式表语法，可用于复杂的样式设置。  |
| `autoFillBackground` | `bool`     | 设置是否自动填充背景。                   | `setAutoFillBackground(true);`                               | 使背景颜色填充组件的整个区域。             |
| `palette`            | `QPalette` | 获取或设置组件的调色板，控制颜色和样式。 | `QPalette palette; palette.setColor(QPalette::Window, Qt::blue); setPalette(palette);` | 颜色可针对不同状态（如禁用、悬停等）设置。 |
| `font`               | `QFont`    | 设置或获取组件的字体。                   | `setFont(QFont("Arial", 12));`                               | 字体设置会影响文本的显示效果。             |

#### 4. 布局与子组件管理属性

| 属性名称   | 类型              | 功能说明                     | 使用示例                                                     | 注意事项                                       |
| ---------- | ----------------- | ---------------------------- | ------------------------------------------------------------ | ---------------------------------------------- |
| `layout`   | `QLayout*`        | 设置或获取组件的布局管理器。 | `QVBoxLayout *layout = new QVBoxLayout(this); setLayout(layout);` | 只能有一个布局管理器，设置后会删除之前的布局。 |
| `parent`   | `QWidget*`        | 设置或获取组件的父对象。     | `QWidget *child = new QWidget(this);`                        | 父对象负责管理子对象的生命周期。               |
| `children` | `QList<QWidget*>` | 获取组件的子对象列表。       | `QList<QWidget*> children = this->findChildren<QWidget*>();` | 可以使用模板过滤特定类型的子对象。             |

#### 5. 图标和光标属性

​	这是用在widget显示icon的

| 属性名称   | 类型      | 功能说明                                 | 使用示例                             | 注意事项                                   |
| ---------- | --------- | ---------------------------------------- | ------------------------------------ | ------------------------------------------ |
| `iconSize` | `QSize`   | 设置图标的显示大小（在某些组件中有效）。 | `setIconSize(QSize(32, 32));`        | 适用于如QToolButton等需要图标的组件。      |
| `cursor`   | `QCursor` | 设置或获取鼠标光标。                     | `setCursor(Qt::PointingHandCursor);` | 可以使用Qt预定义的光标类型，或自定义光标。 |

#### 6. 大小策略属性

​	控制了控件的大小对于外部布局时的行为。比如说Agressive的占据尽可能大的空间或者选择保守的策略。

| 属性名称     | 类型          | 功能说明                               | 使用示例                                                     | 注意事项                       |
| ------------ | ------------- | -------------------------------------- | ------------------------------------------------------------ | ------------------------------ |
| `sizePolicy` | `QSizePolicy` | 设置组件的大小策略，决定如何调整大小。 | `setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);` | 影响组件在布局中的表现和调整。 |

​	很多都很好理解，但是这个sizePolicy可能会在后面的布局的时候会用到，这里说一下：

| sizeType属性说明 | 值                               | 说明                                                         |
| ---------------- | -------------------------------- | ------------------------------------------------------------ |
| Fixed            | 0                                | 固定值策略: Qwidget.sizeHint()对应的缺省大小就是部件的固定不变大小,因此部件不能放大也不能缩小。 |
| Minimum          | GrowFlag                         | 指定最小值策略: Qwidget. sizeHint()对应的缺省大小是最小值，不能调整部件大小到比缺省大小更小的尺寸，并且该值应该足够满足部件的展现。部件允许扩展，但是Qt并不建议扩展(例如:水平方向上的按钮)。 |
| Maximum          | ShrinkFlag                       | 指定最大值策略: Qwidget. sizeHint()对应的缺省大小是最大值,假如其它部件需要空间并且不会破坏该部件,那么该部件允许被缩小(例如:-个分割线)。 |
| Perferred        | GrowFlag\|ShrinkFlag             | 首选项策略: Qwidget sizeHint()对应的缺省大小是最佳效果，部件允许放大或缩小，但不建议扩展比sizeHint()大,该策略是缺省策略。 |
| Expanding        | GrowFlag\|ShrinkFlag\|ExpandFlag | 扩展策略: Qwidget. sizeHint()对应的缺省大小是合理的大小,但部件允许缩小并且可用。部件可以利用额外的空间,因此它将会得到尽可能多的空间(例如:水平方向上的滑块)。 |
| MinimumExpanding | GrowFlag\|ExpandFlag             | 最小可扩展策略: Qwidget. sizeHint()对应的缺省大小是最小值，并且大小足够。部件允许使用额外空间，因此它将会得到尽可能多的空间(例如:水平方向上的滑块)。 |
| Ignored          | ShrinkFlag\|GrowFlag\|IgnoreFlag | Qwidget.sizeHint()对应的缺省大小将会被忽略,部件将会获取尽可能多的空间。 |

​	感谢[qt 如何设计好布局和漂亮的界面。_qt 界面-CSDN博客](https://blog.csdn.net/Fdog_/article/details/107522283)的大佬，这里引用一下：

- Fixed：控件不能放大或者缩小，控件的大小就是它的sizeHint。
- Minimum：控件的sizeHint为控件的最小尺寸。控件不能小于这个sizeHint，但是可以放大。
- Maximum：控件的sizeHint为控件的最大尺寸，控件不能放大，但是可以缩小到它的最小的允许尺寸。
- Preferred**：控件的sizeHint是它的sizeHint，但是可以放大或者缩小**。
- Expanding：控件可以自行增大或者缩小。（原文这里的Expanding打错了，打成了Expandint）
- MinimumExpanding：控件的sizeHint是它的sizeHint，但是可以使用额外的空间，**也就是它会尽可能得到更多的空间**。
- Ignored：控件的sizeHint不起作用，它会尽可能得到更多的空间。

​	这里就把常见的必备属性说完了，下面聊一聊当QWidget是一个单独的窗体的时候的行为。

### 作为单独的窗体的属性

| 属性名称         | 类型                 | 功能说明                                                     |
| ---------------- | -------------------- | ------------------------------------------------------------ |
| `windowTitle`    | `QString`            | 设置或获取窗口的标题。                                       |
| `windowIcon`     | `QIcon`              | 设置或获取窗口的图标。                                       |
| `windowOpacity`  | `qreal`              | 设置窗口的不透明度，值范围为0.0（完全透明）到1.0（完全不透明）。 |
| `windowFilePath` | `QString`            | 获取或设置窗口相关的文件路径（在某些应用程序中使用）。当然Windows Meaningful Only |
| `windowModified` | `bool`               | 设置或获取窗口是否被修改过，通常用于指示文件是否已更改。     |
| `windowModality` | `Qt::WindowModality` | 设置窗口的模态性，决定是否阻塞其他窗口的输入。               |
| `windowState`    | `Qt::WindowState`    | 设置或获取窗口的状态（如最小化、最大化）。                   |
| `windowFlags`    | `Qt::WindowFlags`    | 设置窗口的标志，决定窗口的行为和外观。                       |