# QMainWindow, QDialog, QWidget特辑

​	这是大伙可能最熟悉的几个类了，笔者打算严肃的对待一下。

## QMainWindow

​	QMainWindow是大部分人的桌面Application的首选，他就是一个主窗口。程序的主逻辑一般放在主窗口的位置上。

​	先看看API：

### API

| 成员/槽/信号/函数                                            | 类型         | 说明                                           |
| ------------------------------------------------------------ | ------------ | ---------------------------------------------- |
| `QMainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())` | 构造函数     | 创建一个 `QMainWindow` 对象。                  |
| `virtual ~QMainWindow()`                                     | 析构函数     | 释放 `QMainWindow` 对象。                      |
| `void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget)` | 成员         | 在指定区域添加一个停靠窗口。                   |
| `void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget, Qt::Orientation orientation)` | 成员         | 在指定区域以特定方向添加一个停靠窗口。         |
| `void addToolBar(Qt::ToolBarArea area, QToolBar *toolbar)`   | 成员         | 在指定区域添加工具栏。                         |
| `void addToolBar(QToolBar *toolbar)`                         | 成员         | 添加工具栏。                                   |
| `QToolBar *addToolBar(const QString &title)`                 | 成员         | 根据标题添加工具栏。                           |
| `void addToolBarBreak(Qt::ToolBarArea area = Qt::TopToolBarArea)` | 成员         | 在指定区域添加工具栏断点。                     |
| `QWidget *centralWidget() const`                             | 成员         | 返回中央Widget。                               |
| `Qt::DockWidgetArea corner(Qt::Corner corner) const`         | 成员         | 返回指定角落的停靠窗口区域。                   |
| `virtual QMenu *createPopupMenu()`                           | 成员         | 创建弹出菜单。                                 |
| `QMainWindow::DockOptions dockOptions() const`               | 成员         | 返回当前的停靠选项。                           |
| `Qt::DockWidgetArea dockWidgetArea(QDockWidget *dockwidget) const` | 成员         | 返回指定停靠窗口的区域。                       |
| `bool documentMode() const`                                  | 成员         | 判断文档模式是否启用。                         |
| `QSize iconSize() const`                                     | 成员         | 返回图标大小。                                 |
| `void insertToolBar(QToolBar *before, QToolBar *toolbar)`    | 成员         | 在指定工具栏之前插入工具栏。                   |
| `void insertToolBarBreak(QToolBar *before)`                  | 成员         | 在指定工具栏之前插入工具栏断点。               |
| `bool isAnimated() const`                                    | 成员         | 判断是否启用动画。                             |
| `bool isDockNestingEnabled() const`                          | 成员         | 判断停靠嵌套是否启用。                         |
| `QMenuBar *menuBar() const`                                  | 成员         | 返回菜单栏。                                   |
| `QWidget *menuWidget() const`                                | 成员         | 返回菜单Widget。                               |
| `void removeDockWidget(QDockWidget *dockwidget)`             | 成员         | 移除指定的停靠窗口。                           |
| `void removeToolBar(QToolBar *toolbar)`                      | 成员         | 移除指定的工具栏。                             |
| `void removeToolBarBreak(QToolBar *before)`                  | 成员         | 移除指定工具栏之前的断点。                     |
| `void resizeDocks(const QList<QDockWidget *> &docks, const QList<int> &sizes, Qt::Orientation orientation)` | 成员         | 调整停靠窗口的大小。                           |
| `bool restoreDockWidget(QDockWidget *dockwidget)`            | 成员         | 恢复指定的停靠窗口。                           |
| `bool restoreState(const QByteArray &state, int version = 0)` | 成员         | 恢复窗口状态。                                 |
| `QByteArray saveState(int version = 0) const`                | 成员         | 保存窗口状态。                                 |
| `void setCentralWidget(QWidget *widget)`                     | 成员         | 设置中央Widget。                               |
| `void setCorner(Qt::Corner corner, Qt::DockWidgetArea area)` | 成员         | 设置角落和停靠窗口区域的关系。                 |
| `void setDockOptions(QMainWindow::DockOptions options)`      | 成员         | 设置停靠选项。                                 |
| `void setDocumentMode(bool enabled)`                         | 成员         | 启用或禁用文档模式。                           |
| `void setIconSize(const QSize &iconSize)`                    | 成员         | 设置图标大小。                                 |
| `void setMenuBar(QMenuBar *menuBar)`                         | 成员         | 设置菜单栏。                                   |
| `void setMenuWidget(QWidget *menuBar)`                       | 成员         | 设置菜单Widget。                               |
| `void setStatusBar(QStatusBar *statusbar)`                   | 成员         | 设置状态栏。                                   |
| `void setTabPosition(Qt::DockWidgetAreas areas, QTabWidget::TabPosition tabPosition)` | 成员         | 设置停靠窗口的选项卡位置。                     |
| `void setTabShape(QTabWidget::TabShape tabShape)`            | 成员         | 设置选项卡的形状。                             |
| `void setToolButtonStyle(Qt::ToolButtonStyle toolButtonStyle)` | 成员         | 设置工具按钮样式。                             |
| `void splitDockWidget(QDockWidget *first, QDockWidget *second, Qt::Orientation orientation)` | 成员         | 分割两个停靠窗口。                             |
| `QStatusBar *statusBar() const`                              | 成员         | 返回状态栏。                                   |
| `QTabWidget::TabPosition tabPosition(Qt::DockWidgetArea area) const` | 成员         | 返回指定区域的选项卡位置。                     |
| `QTabWidget::TabShape tabShape() const`                      | 成员         | 返回选项卡的形状。                             |
| `QList<QDockWidget *> tabifiedDockWidgets(QDockWidget *dockwidget) const` | 成员         | 返回与指定停靠窗口一起选项卡化的停靠窗口列表。 |
| `void tabifyDockWidget(QDockWidget *first, QDockWidget *second)` | 成员         | 将两个停靠窗口选项卡化。                       |
| `QWidget *takeCentralWidget()`                               | 成员         | 移除并返回中央Widget。                         |
| `Qt::ToolBarArea toolBarArea(const QToolBar *toolbar) const` | 成员         | 返回指定工具栏的区域。                         |
| `bool toolBarBreak(QToolBar *toolbar) const`                 | 成员         | 判断指定工具栏是否存在断点。                   |
| `Qt::ToolButtonStyle toolButtonStyle() const`                | 成员         | 返回工具按钮样式。                             |
| `bool unifiedTitleAndToolBarOnMac() const`                   | 成员         | 判断在 Mac 上是否统一标题和工具栏。            |
| `void setAnimated(bool enabled)`                             | 公共槽       | 启用或禁用动画。                               |
| `void setDockNestingEnabled(bool enabled)`                   | 公共槽       | 启用或禁用停靠嵌套。                           |
| `void setUnifiedTitleAndToolBarOnMac(bool set)`              | 公共槽       | 在 Mac 上设置统一标题和工具栏。                |
| `void contextMenuEvent(QContextMenuEvent *event) override`   | 重写保护函数 | 处理上下文菜单事件。                           |
| `bool event(QEvent *event) override`                         | 重写保护函数 | 处理事件。                                     |

### 进一步的详细阐述

​	`QMainWindow` 类为构建应用程序用户界面提供了框架。它的布局允许添加工具栏、停靠窗口、菜单栏和状态栏，中心区域可以放置任意Widget。在构建主窗口组件时，中心Widget通常是标准的 Qt Widget，如 `QTextEdit` 或 `QGraphicsView`。可以通过 `setCentralWidget()` 设置中心Widget。**主窗口支持单文档（SDI）或多文档（MDI）界面，使用 `QMdiArea` 作为中心Widget来创建 MDI 应用程序。**

​	在菜单创建方面，Qt 使用 `QMenu` 来实现菜单，`QMainWindow` 将其保存在 `QMenuBar` 中。可以通过 `menuBar()` 获取菜单栏，并使用 `QMenuBar::addMenu()` 添加新菜单。也可以通过 `setMenuBar()` 设置自定义的菜单栏。

​	工具栏通过 `QToolBar` 实现，使用 `addToolBar()` 将其添加到主窗口。工具栏的位置由 `Qt::ToolBarArea` 指定，可以通过 `addToolBarBreak()` 或 `insertToolBarBreak()` 插入工具栏分隔符。

​	停靠窗口使用 `QDockWidget` 实现，可以通过 `addDockWidget()` 添加到主窗口。可以定义停靠区域（左、右、上、下），并通过 `setCorner()` 指定重叠区域的停靠位置。

​	状态栏可以通过 `setStatusBar()` 设置。主窗口的布局状态可以通过 `saveState()` 保存，并通过 `restoreState()` 恢复。

```
void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
}
```

​	这样就可以快速的取到部件加以使用。



#### 枚举 QMainWindow::DockOption

`QMainWindow::DockOption` 枚举包含标志，用于指定 `QMainWindow` 的停靠行为。

| 常量                            | 值   | 描述                                                         |
| ------------------------------- | ---- | ------------------------------------------------------------ |
| `QMainWindow::AnimatedDocks`    | 0x01 | 与 `animated` 属性相同。                                     |
| `QMainWindow::AllowNestedDocks` | 0x02 | 与 `dockNestingEnabled` 属性相同。                           |
| `QMainWindow::AllowTabbedDocks` | 0x04 | 用户可以将一个停靠窗口放在另一个上方，两个窗口叠加并显示选项卡。 |
| `QMainWindow::ForceTabbedDocks` | 0x08 | 每个停靠区域仅包含一个堆叠的选项卡停靠窗口，无法并排放置。   |
| `QMainWindow::VerticalTabs`     | 0x10 | 两侧的垂直停靠区域显示垂直选项卡。若未设置，则所有停靠区域的选项卡在底部。 |
| `QMainWindow::GroupedDragging`  | 0x20 | 拖动停靠窗口的标题栏时，所有与之关联的选项卡都将一起拖动。   |

​	这些选项仅控制停靠窗口在 `QMainWindow` 中的放置方式，并不会重新排列停靠窗口。因此应在添加停靠窗口之前设置这些选项。

### QMainWindow中存在的属性

- **animated : bool**
  - 控制停靠窗口和工具栏的动画效果。
  - 默认值为 `true`。可以通过 `setAnimated()` 设置。
- **dockNestingEnabled : bool**
  - 控制停靠窗口是否可以嵌套。
  - 默认值为 `false`。可以通过 `setDockNestingEnabled()` 设置。
- **dockOptions : DockOptions**
  - 控制 `QMainWindow` 的停靠行为。
  - 默认值为 `AnimatedDocks | AllowTabbedDocks`。可以通过 `setDockOptions()` 设置。
- **documentMode : bool**
  - 控制选项卡停靠窗口的选项卡是否为文档模式。
  - 默认值为 `false`。可以通过 `setDocumentMode()` 设置。
- **iconSize : QSize**
  - 控制工具栏图标的大小。
  - 默认值为 GUI 风格的默认工具栏图标大小。可以通过 `setIconSize()` 设置。
- **tabShape : QTabWidget::TabShape**
  - 控制选项卡停靠窗口的选项卡形状。
  - 默认值为 `QTabWidget::Rounded`。可以通过 `setTabShape()` 设置。
- **toolButtonStyle : Qt::ToolButtonStyle**
  - 控制工具栏按钮的样式。
  - 默认值为 `Qt::ToolButtonIconOnly`。可以通过 `setToolButtonStyle()` 设置。
- **unifiedTitleAndToolBarOnMac : bool**
  - 控制窗口是否在 macOS 上使用统一的标题和工具栏外观。
  - 可以通过 `setUnifiedTitleAndToolBarOnMac()` 设置。

​	从上面的笔记就可以看到，QMainWindow本身就是一个Maintainer，维护主要逻辑组件之间的关系的。关于窗口本身的API不需要全部记住，只需要有一个大致映像（有Icon，有ToolBar，有MenuBar），处理总逻辑组件蔟的事件的。这样就OK了。

## QWidget Widget组件的爹

​	Widget是用户界面的基本单位：它接收来自窗口系统的鼠标、键盘和其他事件，并在屏幕上绘制自己的表示。每个Widget都是矩形的，并按照 Z 轴顺序排列。Widget被其父Widget和前面的其他Widget裁剪。未嵌入父Widget的Widget称为窗口。通常，窗口具有边框和标题栏，尽管也可以使用适当的窗口标志创建没有这些装饰的窗口。在 Qt 中，`QMainWindow` 和各种 `QDialog` 的子类是最常见的窗口类型。

每个Widget的构造函数接受一个或两个标准参数：

- `QWidget *parent = nullptr`：新Widget的父Widget。如果为 `nullptr`（默认），则新Widget将成为一个窗口。如果不是，它将成为父Widget的子Widget，并受到父Widget几何形状的约束（除非您指定 `Qt::Window` 作为窗口标志）。
- `Qt::WindowFlags f = {}`（如果可用）：设置窗口标志；默认适用于大多数Widget，但例如，要获得没有窗口系统框架的窗口，您必须使用特殊标志。

​	`QWidget` 具有许多成员函数，但其中一些的直接功能较小；例如，`QWidget` 具有字体属性，但自身从不使用它。有许多子类提供了实际功能，例如 `QLabel`、`QPushButton`、`QListWidget` 和 `QTabWidget`。

#### 顶层和子Widget

​	没有父Widget的Widget始终是独立窗口（顶层Widget）。对于这些Widget，`setWindowTitle()` 和 `setWindowIcon()` 分别设置标题栏和图标。非窗口Widget是子Widget，在其父Widget内显示。Qt 中的大多数Widget主要用作子Widget。例如，可以将按钮显示为顶层窗口，但大多数人更愿意将按钮放在其他Widget内部，例如 `QDialog` 中。父Widget包含各种子Widget的示例。如果要使用 `QWidget` 来容纳子Widget，通常希望为父 `QWidget` 添加布局。

#### 复合Widget

​	当Widget用作容器以组合多个子Widget时，它被称为复合Widget。这可以通过构造一个具有所需视觉属性的Widget（例如 `QFrame`）并将子Widget添加到其中，通常由布局管理。复合Widget也可以通过子类化标准Widget（例如 `QWidget` 或 `QFrame`）来创建，并在子类的构造函数中添加必要的布局和子Widget。Qt 提供的许多示例使用这种方法，这在 Qt Widget教程中也有介绍。

#### 自定义Widget和绘制

由于 `QWidget` 是 `QPaintDevice` 的子类，子类可以用于显示通过一系列绘制操作与 `QPainter` 类的实例组成的自定义内容。这种方法与图形视图框架使用的画布风格方法形成对比，在这种方法中，应用程序将项目添加到场景中，而框架本身进行渲染。

每个Widget从其 `paintEvent()` 函数内部执行所有绘制操作。每当Widget需要重绘时（无论是由于某些外部更改，还是由应用程序请求），该函数都会被调用。

模拟时钟示例展示了一个简单Widget如何处理绘制事件。

#### 尺寸提示和尺寸策略

​	在实现新Widget时，几乎总是需要重写 `sizeHint()` 以提供Widget的合理默认大小，并通过 `setSizePolicy()` 设置正确的大小策略。默认情况下，不提供尺寸提示的复合Widget将根据其子Widget的空间需求进行调整。

​	**大小策略让您为布局管理系统提供良好的默认行为**，以便其他Widget可以轻松包含和管理您的Widget。默认大小策略表示尺寸提示代表Widget的首选大小，这通常对于许多Widget来说已经足够好。顶层Widget的大小被限制为桌面高度和宽度的 2/3。如果这些边界不够，您可以手动调用 `resize()` 进行调整。

#### 事件

​	Widget响应通常由用户操作引发的事件。Qt 通过调用特定事件处理函数，向Widget传递事件，这些函数接收包含每个事件信息的 `QEvent` 子类实例。

​	如果您的Widget仅包含子Widget，则通常不需要实现任何事件处理程序。如果您想检测子Widget中的鼠标点击，请在Widget的 `mousePressEvent()` 中调用子Widget的 `underMouse()` 函数。涂鸦示例实现了一组更广泛的事件，以处理鼠标移动、按钮按下和窗口调整大小。您需要为自己的Widget提供行为和内容，但以下是与 `QWidget` 相关的一些常见事件的简要概述：

- `paintEvent()` 在Widget需要重绘时调用。每个显示自定义内容的Widget必须实现此函数。使用 `QPainter` 进行绘制只能在 `paintEvent()` 或由 `paintEvent()` 调用的函数中进行。
- `resizeEvent()` 在Widget调整大小时调用。
- `mousePressEvent()` 在鼠标按钮在Widget内部被按下时调用，或者当Widget通过 `grabMouse()` 抓住鼠标时。按下鼠标而不释放等同于调用 `grabMouse()`。
- `mouseReleaseEvent()` 在鼠标按钮释放时调用。Widget接收鼠标释放事件的前提是它已收到相应的鼠标按下事件。这意味着，如果用户在您的Widget内按下鼠标，然后在释放鼠标按钮之前将鼠标拖到其他地方，则您的Widget会接收释放事件。有一个例外：如果在按住鼠标按钮时弹出菜单出现，这个弹出菜单会立即抢走鼠标事件。
- `mouseDoubleClickEvent()` 在用户双击Widget时调用。如果用户双击，Widget会接收到鼠标按下事件、鼠标释放事件、（鼠标点击事件）、第二个鼠标按下事件、此事件和最后的第二个鼠标释放事件。（如果鼠标在此操作过程中没有保持静止，可能还会收到一些鼠标移动事件。）在第二次点击到达之前，无法区分单击和双击。（这就是为什么大多数 GUI 书籍建议双击是单击的扩展，而不是触发不同的操作的原因。）
- 接受键盘输入的Widget需要重写更多的事件处理程序：
  - `keyPressEvent()` 在按下键时调用，并且在按住键足够长的时间以使其自动重复时再次调用。Tab 和 Shift+Tab 键只有在未被焦点变化机制使用时才会传递给Widget。要强制这些键由Widget处理，必须重写 `QWidget::event()`。
  - `focusInEvent()` 在Widget获得键盘焦点时调用（假设您已调用 `setFocusPolicy()`）。行为良好的Widget以清晰但不引人注目的方式指示它们拥有键盘焦点。
  - `focusOutEvent()` 在Widget失去键盘焦点时调用。

您可能还需要重写一些较不常见的事件处理程序：

- `mouseMoveEvent()` 在按住鼠标按钮时鼠标移动时调用。这在拖放操作期间可能会很有用。如果您调用 `setMouseTracking(true)`，即使没有按下按钮，也会收到鼠标移动事件。（另请参阅拖放指南。）
- `keyReleaseEvent()` 在键释放时调用，并且在按住的情况下（如果该键正在自动重复）。在这种情况下，Widget将为每次重复接收一对键释放和键按下事件。Tab 和 Shift+Tab 键只有在未被焦点变化机制使用时才会传递给Widget。要强制这些键由Widget处理，必须重写 `QWidget::event()`。
- `wheelEvent()` 在用户在Widget上获得焦点时转动鼠标滚轮时调用。
- `enterEvent()` 当鼠标进入Widget的屏幕空间时调用。（这不包括Widget的任何子Widget所拥有的屏幕空间。）
- `leaveEvent()` 当鼠标离开Widget的屏幕空间时调用。如果鼠标进入子Widget，则不会引发 `leaveEvent()`。
- `moveEvent()` 当Widget相对于其父Widget移动时调用。
- `closeEvent()` 当用户关闭Widget时调用（或者当调用 `close()` 时）。

`QWidget` 提供了许多有用的函数，具体如下：

- **窗口函数**：如 `show()`、`hide()` 和 `close()`。
- **几何函数**：如 `pos()`、`size()` 和 `resize()` 等。可以通过 `move()` 设置Widget在其父Widget中的位置。
- **焦点函数**：如 `setFocus()` 和 `clearFocus()`。

除了这些函数外，`QWidget` 还具有多种属性，许多属性会影响Widget的外观和行为。Widget的外观可以通过样式表自定义。通过设置特定的样式表，可以自定义Widget的外观，而不仅限于 Qt 默认样式。默认情况下，QWidget 自动执行双缓冲以避免闪烁。这在很多情况下会产生更流畅的视觉效果。在支持合成的窗口系统中，您可以使用 `Qt::WA_TranslucentBackground` 属性来创建具有透明区域的窗口。可以使用 `setAttribute()` 设置该属性。外来Widget没有与窗口系统相关联的原生窗口句柄，因此绘制速度更快且不会闪烁。这可以提高渲染的性能，尤其是在需要更新大量Widget时。

### API

#### 主要的Public方法

| 函数声明                                                     | 说明                                               |
| ------------------------------------------------------------ | -------------------------------------------------- |
| **QWidget(QWidget \*parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())** | 构造函数，创建一个 QWidget，指定父窗口和窗口标志。 |
| **virtual ~QWidget()**                                       | 析构函数，销毁Widget。                             |
| **bool acceptDrops() const**                                 | 返回Widget是否接受拖放事件。                       |
| **QString accessibleDescription() const**                    | 返回Widget的可访问描述。                           |
| **QString accessibleName() const**                           | 返回Widget的可访问名称。                           |
| **QList<QAction \*> actions() const**                        | 返回Widget的所有动作列表。                         |
| **void activateWindow()**                                    | 激活Widget窗口。                                   |
| **void addAction(QAction \*action)**                         | 将指定动作添加到Widget。                           |
| **QAction \* addAction(const QString &text)**                | 添加一个带有文本的动作。                           |
| **QAction \* addAction(const QIcon &icon, const QString &text)** | 添加一个带有图标和文本的动作。                     |
| **QAction \* addAction(const QString &text, const QKeySequence &shortcut)** | 添加一个带有文本和快捷键的动作。                   |
| **QAction \* addAction(const QIcon &icon, const QString &text, const QKeySequence &shortcut)** | 添加一个带有图标、文本和快捷键的动作。             |
| **QAction \* addAction(const QString &text, Args &&... args)** | 添加一个带有文本和额外参数的动作。                 |
| **void addActions(const QList<QAction \*> &actions)**        | 添加一组动作。                                     |
| **void adjustSize()**                                        | 调整Widget大小以适应其内容。                       |
| **bool autoFillBackground() const**                          | 返回Widget是否自动填充背景。                       |
| **QPalette::ColorRole backgroundRole() const**               | 返回Widget的背景角色。                             |
| **QBackingStore \* backingStore() const**                    | 返回Widget的后备存储。                             |
| **QSize baseSize() const**                                   | 返回Widget的基本大小。                             |
| **QWidget \* childAt(int x, int y) const**                   | 返回指定坐标处的子Widget。                         |
| **QWidget \* childAt(const QPoint &p) const**                | 返回指定点处的子Widget。                           |
| **QRect childrenRect() const**                               | 返回所有子Widget的矩形区域。                       |
| **QRegion childrenRegion() const**                           | 返回所有子Widget的区域。                           |
| **void clearFocus()**                                        | 清除Widget的焦点。                                 |
| **void clearMask()**                                         | 清除Widget的遮罩。                                 |
| **QMargins contentsMargins() const**                         | 返回Widget内容的边距。                             |
| **QRect contentsRect() const**                               | 返回Widget内容的矩形区域。                         |
| **Qt::ContextMenuPolicy contextMenuPolicy() const**          | 返回Widget的上下文菜单策略。                       |
| **QCursor cursor() const**                                   | 返回Widget的当前光标。                             |
| **WId effectiveWinId() const**                               | 返回Widget的有效窗口标识符。                       |
| **void ensurePolished() const**                              | 确保Widget已被处理和更新。                         |
| **Qt::FocusPolicy focusPolicy() const**                      | 返回Widget的焦点策略。                             |
| **QWidget \* focusProxy() const**                            | 返回Widget的焦点代理。                             |
| **QWidget \* focusWidget() const**                           | 返回当前获得焦点的Widget。                         |
| **const QFont & font() const**                               | 返回Widget的字体。                                 |
| **QFontInfo fontInfo() const**                               | 返回Widget的字体信息。                             |
| **QFontMetrics fontMetrics() const**                         | 返回Widget的字体度量。                             |
| **QPalette::ColorRole foregroundRole() const**               | 返回Widget的前景角色。                             |
| **QRect frameGeometry() const**                              | 返回Widget的框架几何形状。                         |
| **QSize frameSize() const**                                  | 返回Widget的框架大小。                             |
| **const QRect & geometry() const**                           | 返回Widget的几何形状。                             |
| **QPixmap grab(const QRect &rectangle = QRect(QPoint(0, 0), QSize(-1, -1)))** | 捕获Widget的指定区域并返回为 QPixmap。             |
| **void grabGesture(Qt::GestureType gesture, Qt::GestureFlags flags = Qt::GestureFlags())** | 捕获指定的手势。                                   |
| **void grabKeyboard()**                                      | 捕获键盘输入。                                     |
| **void grabMouse()**                                         | 捕获鼠标输入。                                     |
| **int grabShortcut(const QKeySequence &key, Qt::ShortcutContext context = Qt::WindowShortcut)** | 捕获指定的快捷键。                                 |
| **QGraphicsEffect \* graphicsEffect() const**                | 返回Widget的图形效果。                             |
| **QGraphicsProxyWidget \* graphicsProxyWidget() const**      | 返回Widget的图形代理。                             |
| **bool hasEditFocus() const**                                | 返回Widget是否具有编辑焦点。                       |
| **bool hasFocus() const**                                    | 返回Widget是否具有焦点。                           |
| **virtual bool hasHeightForWidth() const**                   | 返回Widget是否可以根据宽度计算高度。               |
| **bool hasMouseTracking() const**                            | 返回Widget是否启用鼠标追踪。                       |
| **bool hasTabletTracking() const**                           | 返回Widget是否启用平板追踪。                       |
| **int height() const**                                       | 返回Widget的高度。                                 |
| **virtual int heightForWidth(int w) const**                  | 根据给定宽度返回Widget的高度。                     |
| **Qt::InputMethodHints inputMethodHints() const**            | 返回输入法提示。                                   |
| **virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const** | 返回输入法查询结果。                               |
| **void insertAction(QAction *before, QAction \*action)**     | 在指定动作之前插入动作。                           |
| **bool isActiveWindow() const**                              | 返回Widget是否为活动窗口。                         |
| **bool isAncestorOf(const QWidget \*child) const**           | 检查Widget是否为指定子Widget的祖先。               |
| **bool isEnabled() const**                                   | 返回Widget是否启用。                               |
| **bool isEnabledTo(const QWidget \*ancestor) const**         | 检查Widget是否对指定祖先启用。                     |
| **bool isFullScreen() const**                                | 返回Widget是否为全屏模式。                         |
| **bool isHidden() const**                                    | 返回Widget是否隐藏。                               |
| **bool isMaximized() const**                                 | 返回Widget是否最大化。                             |
| **bool isMinimized() const**                                 | 返回Widget是否最小化。                             |
| **bool isModal() const**                                     | 返回Widget是否为模态窗口。                         |
| **bool isVisible() const**                                   | 返回Widget是否可见。                               |
| **bool isWindow() const**                                    | 返回Widget是否为窗口。                             |
| **bool isWindowModified() const**                            | 返回Widget是否已修改。                             |
| **QLayout \* layout() const**                                | 返回Widget的布局。                                 |
| **Qt::LayoutDirection layoutDirection() const**              | 返回Widget的布局方向。                             |
| **QLocale locale() const**                                   | 返回Widget的区域设置。                             |
| **QPoint mapFrom(const QWidget \*parent, const QPoint &pos) const** | 将坐标从父Widget映射到当前Widget。                 |
| **QPoint mapFromGlobal(const QPoint &pos) const**            | 将全局坐标映射到Widget坐标。                       |
| **QPoint mapTo(const QWidget \*parent, const QPoint &pos) const** | 将当前Widget的坐标映射到父Widget。                 |
| **QPoint mapToGlobal(const QPoint &pos) const**              | 将Widget坐标映射到全局坐标。                       |
| **QRegion mask() const**                                     | 返回Widget的遮罩。                                 |
| **int maximumHeight() const**                                | 返回Widget的最大高度。                             |
| **QSize maximumSize() const**                                | 返回Widget的最大大小。                             |
| **int minimumHeight() const**                                | 返回Widget的最小高度。                             |
| **virtual QSize minimumSizeHint() const**                    | 返回Widget的最小尺寸提示。                         |
| **void move(int x, int y)**                                  | 移动Widget到指定坐标。                             |
| **QWidget \* nativeParentWidget() const**                    | 返回Widget的本地父Widget。                         |
| **QRect normalGeometry() const**                             | 返回Widget的正常几何形状。                         |
| **void overrideWindowFlags(Qt::WindowFlags flags)**          | 覆盖Widget的窗口标志。                             |
| **const QPalette & palette() const**                         | 返回Widget的调色板。                               |
| **QWidget \* parentWidget() const**                          | 返回Widget的父Widget。                             |
| **QPoint pos() const**                                       | 返回Widget的位置。                                 |
| **QRect rect() const**                                       | 返回Widget的矩形区域。                             |
| **void releaseKeyboard()**                                   | 释放键盘输入。                                     |
| **void releaseMouse()**                                      | 释放鼠标输入。                                     |
| **void removeAction(QAction \*action)**                      | 从Widget中移除指定动作。                           |
| **void render(QPainter *painter, const QPoint &targetOffset = QPoint(), const QRegion &sourceRegion = QRegion(), QWidget::RenderFlags renderFlags = RenderFlags(DrawWindowBackgroundDrawChildren))** | 渲染组件                                           |
| **void resize(int w, int h)**                                | 调整Widget的大小。                                 |
| **bool restoreGeometry(const QByteArray &geometry)**         | 恢复Widget的几何形状。                             |
| **QByteArray saveGeometry() const**                          | 保存Widget的几何形状。                             |
| **QScreen \* screen() const**                                | 返回Widget所在的屏幕。                             |
| **void scroll(int dx, int dy)**                              | 滚动Widget的内容。                                 |
| **void setAcceptDrops(bool on)**                             | 设置Widget是否接受拖放事件。                       |
| **void setAccessibleDescription(const QString &description)** | 设置Widget的可访问描述。                           |
| **void setAccessibleName(const QString &name)**              | 设置Widget的可访问名称。                           |
| **void setAttribute(Qt::WidgetAttribute attribute, bool on = true)** | 设置Widget的属性。                                 |
| **void setAutoFillBackground(bool enabled)**                 | 启用或禁用自动填充背景。                           |
| **void setBackgroundRole(QPalette::ColorRole role)**         | 设置Widget的背景角色。                             |
| **void setBaseSize(const QSize &)**                          | 设置Widget的基本大小。                             |
| **void setContentsMargins(int left, int top, int right, int bottom)** | 设置Widget的内容边距。                             |
| **void setContextMenuPolicy(Qt::ContextMenuPolicy policy)**  | 设置Widget的上下文菜单策略。                       |
| **void setCursor(const QCursor &)**                          | 设置Widget的光标。                                 |
| **void setEditFocus(bool enable)**                           | 设置Widget的编辑焦点状态。                         |
| **void setFixedHeight(int h)**                               | 设置Widget的固定高度。                             |
| **void setFixedSize(const QSize &s)**                        | 设置Widget的固定大小。                             |
| **void setFocus(Qt::FocusReason reason)**                    | 设置Widget的焦点。                                 |
| **void setFont(const QFont &)**                              | 设置Widget的字体。                                 |
| **void setGraphicsEffect(QGraphicsEffect \*effect)**         | 设置Widget的图形效果。                             |
| **void setLayout(QLayout \*layout)**                         | 设置Widget的布局。                                 |
| **void setLocale(const QLocale &locale)**                    | 设置Widget的区域设置。                             |
| **void setMask(const QBitmap &bitmap)**                      | 设置Widget的遮罩为位图。                           |
| **void setMaximumHeight(int maxh)**                          | 设置Widget的最大高度。                             |
| **void setMinimumHeight(int minh)**                          | 设置Widget的最小高度。                             |
| **void setMouseTracking(bool enable)**                       | 启用或禁用鼠标追踪。                               |
| **void setPalette(const QPalette &)**                        | 设置Widget的调色板。                               |
| **void setParent(QWidget \*parent)**                         | 设置Widget的父Widget。                             |
| **void setScreen(QScreen \*screen)**                         | 设置Widget所在的屏幕。                             |
| **void setSizePolicy(QSizePolicy)**                          | 设置Widget的大小策略。                             |
| **void setStatusTip(const QString &)**                       | 设置Widget的状态提示。                             |
| **void setToolTip(const QString &)**                         | 设置Widget的工具提示。                             |
| **void setWindowFilePath(const QString &filePath)**          | 设置Widget的窗口文件路径。                         |
| **void setWindowFlags(Qt::WindowFlags type)**                | 设置Widget的窗口标志。                             |
| **void setWindowIcon(const QIcon &icon)**                    | 设置Widget的窗口图标。                             |
| **void setWindowState(Qt::WindowStates windowState)**        | 设置Widget的窗口状态。                             |
| **QSize size() const**                                       | 返回Widget的大小。                                 |
| **virtual QSize sizeHint() const**                           | 返回Widget的大小提示。                             |
| **bool testAttribute(Qt::WidgetAttribute attribute) const**  | 测试Widget的指定属性。                             |
| **QString toolTip() const**                                  | 返回Widget的工具提示。                             |
| **int width() const**                                        | 返回Widget的宽度。                                 |
| **WId winId() const**                                        | 返回Widget的窗口标识符。                           |
| **QString windowFilePath() const**                           | 返回Widget的窗口文件路径。                         |
| **Qt::WindowFlags windowFlags() const**                      | 返回Widget的窗口标志。                             |
| **QWindow \* windowHandle() const**                          | 返回Widget的窗口句柄。                             |
| **QIcon windowIcon() const**                                 | 返回Widget的窗口图标。                             |
| **QString windowTitle() const**                              | 返回Widget的窗口标题。                             |
| **int x() const**                                            | 返回Widget的 X 坐标。                              |
| **int y() const**                                            | 返回Widget的 Y 坐标                                |

​	非常的丰富！还是一样，用到哪些再查！

​	Widget自身是用来继续创造属于自己的小部件的。所以当我们需要批量的生成我们自己定义的部件的时候，请继承并定义我们感兴趣的行为。

## QDialog

​	Dialog自身是Widget的延伸。实际上就是用来完成与用户交互的功能的！对话窗口是一个顶层窗口，主要用于短期任务和与用户进行简短的沟通。`QDialog` 可以是模态或非模态的。`QDialog` 可以提供返回值，并且可以具有默认按钮。`QDialog` 的右下角可以有一个大小调整手柄，通过 `setSizeGripEnabled()` 方法设置。

​	`QDialog`（以及任何其他类型为 `Qt::Dialog` 的窗口小部件）与 Qt 中其他类使用父窗口的方式略有不同。对话框始终是顶层窗口，但如果它有一个父窗口，则其默认位置是在父窗口的顶层窗口上居中（如果父窗口本身不是顶层窗口）。它还会共享父窗口的任务栏条目。使用 `QWidget::setParent()` 函数的重载可以更改 `QDialog` 小部件的所有权。该函数允许您显式设置重新父化小部件的窗口标志；使用重载的函数将清除指定小部件窗口系统属性的窗口标志（特别是将重置 `Qt::Dialog` 标志）。注意：对话框的父子关系并不意味着对话框总是堆叠在父窗口之上。为了确保对话框始终在上面，您需要使对话框为模态。这同样适用于对话框本身的子窗口。为了确保对话框的子窗口保持在对话框之上，也需要使子窗口为模态。

#### 模态对话框

​	模态对话框是一种**阻止其他可见窗口输入的对话框**。用于请求用户输入文件名或设置应用程序首选项的对话框通常是模态的。对话框可以是应用程序模态（默认）或窗口模态。

​	当应用程序模态对话框打开时，用户必须完成与对话框的交互并关闭它，才能访问应用程序中的其他窗口。窗口模态对话框仅阻止对与对话框关联的窗口的访问，允许用户继续使用应用程序中的其他窗口。显示模态对话框的最常见方式是调用其 `exec()` 函数。当用户关闭对话框时，`exec()` 将提供一个有用的返回值。要关闭对话框并返回适当的值，您必须将默认按钮（例如“确定”按钮）连接到 `accept()` 槽，并将“取消”按钮连接到 `reject()` 槽。或者，您可以使用 `done()` 槽与 `Accepted` 或 `Rejected` 一起调用。

​	另一种方法是调用 `setModal(true)` 或 `setWindowModality()`，然后调用 `show()`。与 `exec()` 不同，`show()` 立即将控制权返回给调用者。调用 `setModal(true)` 对于进度对话框尤其有用，用户必须能够与对话框交互，例如取消长时间运行的操作。如果您结合使用 `show()` 和 `setModal(true)` 执行长时间操作，您必须在处理过程中定期调用 `QCoreApplication::processEvents()` 以使用户能够与对话框交互（参见 `QProgressDialog`）。

#### 非模态对话框

​	非模态对话框是与同一应用程序中的其他窗口独立操作的对话框。在文字处理程序中，查找和替换对话框通常是非模态的，以允许用户与应用程序的主窗口和对话框进行交互。非模态对话框使用 `show()` 显示，该函数立即将控制权返回给调用者。

​	如果在隐藏对话框后调用 `show()` 函数，对话框将以其原始位置显示。这是因为窗口管理器决定未被程序员明确放置的窗口的位置。要保留已被用户移动的对话框的位置，请在 `closeEvent()` 处理程序中保存其位置，然后在再次显示之前将对话框移动到该位置。

#### 默认按钮

对话框的默认按钮是在用户按下 Enter（回车）键时被按下的按钮。此按钮用于表示用户接受对话框的设置并希望关闭对话框。使用 `QPushButton::setDefault()`、`QPushButton::isDefault()` 和 `QPushButton::autoDefault()` 来设置和控制对话框的默认按钮。

#### Escape 键

如果用户在对话框中按下 Esc 键，将调用 `QDialog::reject()`。这将导致窗口关闭：关闭事件无法被忽略。

#### 可扩展性

可扩展性是指以两种方式显示对话框的能力：部分对话框显示最常用的选项，完整对话框显示所有选项。通常，一个可扩展的对话框最初会作为部分对话框出现，但带有一个“更多”切换按钮。如果用户按下“更多”按钮，对话框将展开。

#### 返回值（模态对话框）

模态对话框通常用于需要返回值的情况，例如指示用户是否按下 OK 或 Cancel。可以通过调用 `accept()` 或 `reject()` 槽来关闭对话框，并且 `exec()` 将返回 `Accepted` 或 `Rejected` 作为相应的结果。`exec()` 调用返回对话框的结果。如果对话框尚未被销毁，结果也可以通过 `result()` 方法获得。

为了修改对话框的关闭行为，您可以重写 `accept()`、`reject()` 或 `done()` 函数。仅在保存对话框位置或覆盖标准关闭或拒绝行为时，才应重写 `closeEvent()` 函数。

### 代码示例

模态对话框：

```
void EditorWindow::countWords()
{
    WordCountDialog dialog(this);
    dialog.setWordCount(document().wordCount());
    dialog.exec();
}
```

非模态对话框：

```
void EditorWindow::find()
{
    if (!findDialog) {
        findDialog = new FindDialog(this);
        connect(findDialog, &FindDialog::findNext,
                this, &EditorWindow::findNext);
    }

    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}
```

带有扩展的对话框：

```
mainLayout->setSizeConstraint(QLayout::SetFixedSize);

findButton = new QPushButton(tr("&Find"));
moreButton = new QPushButton(tr("&More..."));
moreButton->setCheckable(true);

extension = new ExtendedControls;
mainLayout->addWidget(extension);
extension->hide();

connect(moreButton, &QAbstractButton::toggled, extension, &QWidget::setVisible);
```

通过将对话框布局的 `sizeConstraint` 属性设置为 `SetFixedSize`，对话框将不会被用户调整大小，并将在扩展隐藏时自动缩小。

### API

| **功能**                     | **描述**                                                     |
| ---------------------------- | ------------------------------------------------------------ |
| **构造函数**                 | `QDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())` 创建一个对话框，可以指定父窗口和窗口标志。 |
| **析构函数**                 | `virtual ~QDialog()` 释放对话框的资源。                      |
| **isSizeGripEnabled()**      | `bool isSizeGripEnabled() const` 检查是否启用了大小调整手柄（在窗口的右下角）。 |
| **result()**                 | `int result() const` 获取对话框的结果代码，通常用于判断用户的操作（如接受或拒绝）。 |
| **setModal(bool modal)**     | `void setModal(bool modal)` 设置对话框为模态或非模态。模态对话框阻止用户与其他窗口交互。 |
| **setResult(int i)**         | `void setResult(int i)` 设置对话框的结果代码，以便在关闭对话框时返回给调用者。 |
| **setSizeGripEnabled(bool)** | `void setSizeGripEnabled(bool)` 启用或禁用大小调整手柄。     |
| **minimumSizeHint()**        | `virtual QSize minimumSizeHint() const override` 重写该函数以返回对话框的最小建议大小。 |
| **setVisible(bool visible)** | `virtual void setVisible(bool visible) override` 重写该函数以控制对话框的可见性。 |
| **sizeHint()**               | `virtual QSize sizeHint() const override` 重写该函数以返回对话框的建议大小。 |
| **accept()**                 | `virtual void accept()` 处理接受操作，通常在用户点击“确定”按钮时调用。 |
| **done(int r)**              | `virtual void done(int r)` 关闭对话框并返回结果代码 r。      |
| **exec()**                   | `virtual int exec()` 以模态方式执行对话框，并返回结果代码。  |
| **open()**                   | `virtual void open()` 打开对话框，并允许用户与其他窗口交互（非模态）。 |
| **reject()**                 | `virtual void reject()` 处理拒绝操作，通常在用户点击“取消”按钮时调用。 |
| **accepted()**               | `void accepted()` 当用户接受对话框时发出的信号。             |
| **finished(int result)**     | `void finished(int result)` 当对话框关闭时发出的信号，包含结果代码。 |
| **rejected()**               | `void rejected()` 当用户拒绝对话框时发出的信号。             |