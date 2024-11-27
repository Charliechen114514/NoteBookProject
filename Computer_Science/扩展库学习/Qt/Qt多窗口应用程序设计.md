# Qt MDI与Splash介绍

## QMdiSubWindow

​	QMdiSubWindow 表示 QMdiArea 中的顶层窗口，由带有窗口装饰的标题栏、内部小部件以及（取决于当前样式）窗口框架和大小控制柄组成。QMdiSubWindow 有自己的布局，由标题栏和内部小部件的中心区域组成。

​	构造 QMdiSubWindow 的最常见方法是调用 QMdiArea::addSubWindow()，并将内部小部件作为参数。您还可以自己创建子窗口，并通过调用 setWidget() 设置内部小部件。使用子窗口编程时，您可以使用与常规顶层窗口相同的 API（例如，您可以调用 show()、hide()、showMaximized() 和 setWindowTitle() 等函数）。

### 子窗口处理

QMdiSubWindow 还支持特定于 MDI 区域中子窗口的行为。默认情况下，每个 QMdiSubWindow 在移动时在 MDI 区域视口内可见，但也可以指定透明窗口移动和调整大小行为，在这些操作期间仅更新子窗口的轮廓。setOption() 函数用于启用此行为。isShaded() 函数检测子窗口当前是否处于阴影状态（即，窗口折叠，因此只有标题栏可见）。要进入阴影模式，请调用 showShaded()。**每当窗口状态发生变化时（例如，当窗口最小化或恢复时），QMdiSubWindow 都会发出 windowStateChanged() 信号。它还会在激活之前发出 aboutToActivate()。**

​	在键盘交互模式下，窗口使用键盘移动和调整大小。您可以通过窗口的系统菜单进入此模式。 keyboardSingleStep 和 keyboardPageStep 属性控制小部件在每次按键事件中移动或调整大小的距离。按下 shift 时，使用向下翻页步进；否则使用单步。您还可以使用键盘更改活动窗口。通过同时按下 control 和 tab 键，将激活下一个（使用当前 WindowOrder）子窗口。通过按下 control、shift 和 tab，您将激活上一个窗口。这相当于调用 activateNextSubWindow() 和 activatePreviousSubWindow()。请注意，这些快捷键会覆盖全局快捷键，但不会覆盖 QMdiAreas 快捷键。

### API

| **分类**                              | **成员/方法**                                                | **说明**                                         |
| ------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------ |
| **Public Types**                      | `enum SubWindowOption { RubberBandResize, RubberBandMove }`  | 枚举类型，定义了窗口的选项：可调整大小或可移动。 |
|                                       | `flags SubWindowOptions`                                     | 用于标记选项的标志类型。                         |
| **Properties**                        | `keyboardPageStep : int`                                     | 定义页面滚动步长。                               |
|                                       | `keyboardSingleStep : int`                                   | 定义单步滚动步长。                               |
| **Public Functions**                  | `QMdiSubWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())` | 构造函数，初始化一个 `QMdiSubWindow` 实例。      |
|                                       | `virtual ~QMdiSubWindow()`                                   | 析构函数，销毁 `QMdiSubWindow` 实例。            |
|                                       | `bool isShaded() const`                                      | 返回窗口是否已被遮蔽（最小化）状态。             |
|                                       | `int keyboardPageStep() const`                               | 获取页面滚动步长的值。                           |
|                                       | `int keyboardSingleStep() const`                             | 获取单步滚动步长的值。                           |
|                                       | `QMdiArea *mdiArea() const`                                  | 获取关联的 `QMdiArea` 对象。                     |
|                                       | `void setKeyboardPageStep(int step)`                         | 设置页面滚动步长的值。                           |
|                                       | `void setKeyboardSingleStep(int step)`                       | 设置单步滚动步长的值。                           |
|                                       | `void setOption(QMdiSubWindow::SubWindowOption option, bool on = true)` | 设置窗口选项。                                   |
|                                       | `void setSystemMenu(QMenu *systemMenu)`                      | 设置窗口的系统菜单。                             |
|                                       | `void setWidget(QWidget *widget)`                            | 设置窗口中显示的小部件。                         |
|                                       | `QMenu *systemMenu() const`                                  | 获取系统菜单。                                   |
|                                       | `bool testOption(QMdiSubWindow::SubWindowOption option) const` | 测试窗口选项是否被启用。                         |
|                                       | `QWidget *widget() const`                                    | 获取窗口中显示的小部件。                         |
| **Reimplemented Public Functions**    | `virtual QSize minimumSizeHint() const override`             | 重写，返回窗口的最小尺寸建议值。                 |
|                                       | `virtual QSize sizeHint() const override`                    | 重写，返回窗口的尺寸建议值。                     |
| **Public Slots**                      | `void showShaded()`                                          | 显示遮蔽状态（最小化窗口）。                     |
|                                       | `void showSystemMenu()`                                      | 显示系统菜单。                                   |
| **Signals**                           | `void aboutToActivate()`                                     | 信号：窗口即将激活。                             |
|                                       | `void windowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState)` | 信号：窗口状态变化。                             |
| **Reimplemented Protected Functions** | `virtual void changeEvent(QEvent *changeEvent) override`     | 重写，处理窗口状态变化的事件。                   |
|                                       | `virtual void childEvent(QChildEvent *childEvent) override`  | 重写，处理子窗口事件。                           |
|                                       | `virtual void closeEvent(QCloseEvent *closeEvent) override`  | 重写，处理窗口关闭事件。                         |
|                                       | `virtual void contextMenuEvent(QContextMenuEvent *contextMenuEvent) override` | 重写，处理右键菜单事件。                         |
|                                       | `virtual bool event(QEvent *event) override`                 | 重写，处理窗口事件。                             |
|                                       | `virtual bool eventFilter(QObject *object, QEvent *event) override` | 重写，事件过滤器。                               |
|                                       | `virtual void focusInEvent(QFocusEvent *focusInEvent) override` | 重写，处理窗口获得焦点事件。                     |
|                                       | `virtual void focusOutEvent(QFocusEvent *focusOutEvent) override` | 重写，处理窗口失去焦点事件。                     |
|                                       | `virtual void hideEvent(QHideEvent *hideEvent) override`     | 重写，处理窗口隐藏事件。                         |
|                                       | `virtual void keyPressEvent(QKeyEvent *keyEvent) override`   | 重写，处理键盘按下事件。                         |
|                                       | `virtual void leaveEvent(QEvent *leaveEvent) override`       | 重写，处理鼠标离开窗口事件。                     |
|                                       | `virtual void mouseDoubleClickEvent(QMouseEvent *mouseEvent) override` | 重写，处理鼠标双击事件。                         |
|                                       | `virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override` | 重写，处理鼠标移动事件。                         |
|                                       | `virtual void mousePressEvent(QMouseEvent *mouseEvent) override` | 重写，处理鼠标按下事件。                         |
|                                       | `virtual void mouseReleaseEvent(QMouseEvent *mouseEvent) override` | 重写，处理鼠标释放事件。                         |
|                                       | `virtual void moveEvent(QMoveEvent *moveEvent) override`     | 重写，处理窗口移动事件。                         |
|                                       | `virtual void paintEvent(QPaintEvent *paintEvent) override`  | 重写，处理窗口绘制事件。                         |
|                                       | `virtual void resizeEvent(QResizeEvent *resizeEvent) override` | 重写，处理窗口大小调整事件。                     |
|                                       | `virtual void showEvent(QShowEvent *showEvent) override`     | 重写，处理窗口显示事件。                         |
|                                       | `virtual void timerEvent(QTimerEvent *timerEvent) override`  | 重写，处理定时器事件。                           |

## QMdiArea

​	QMdiArea 的功能本质上类似于 MDI 窗口的窗口管理器。例如，它在自身上绘制它所管理的窗口，并以层叠或平铺模式排列它们。QMdiArea 通常用作 QMainWindow 中的中心窗口小部件来创建 MDI 应用程序，但也可以放置在任何布局中。以下代码将一个区域添加到主窗口：

```
QMainWindow *mainWindow = new QMainWindow;
mainWindow->setCentralWidget(mdiArea);
```

​	与顶层窗口的窗口管理器不同，只要当前窗口小部件样式支持所有窗口标志 (Qt::WindowFlags)，QMdiArea 便支持这些标志。如果样式不支持特定标志（例如 WindowShadeButtonHint），您仍然可以使用 showShaded() 为窗口着色。

​	QMdiArea 中的子窗口是 QMdiSubWindow 的实例。它们通过 addSubWindow() 添加到 MDI 区域。通常将设置为内部窗口小部件的 QWidget 传递给此函数，但也可以直接传递 QMdiSubWindow。该类继承 QWidget，编程时可以使用与普通顶层窗口相同的 API。QMdiSubWindow 还具有特定于 MDI 窗口的行为。有关更多详细信息，请参阅 QMdiSubWindow 类描述。

​	当子窗口获得键盘焦点或调用 setFocus() 时，子窗口变为活动窗口。用户通过以通常的方式移动焦点来激活窗口。当活动窗口发生变化时，MDI 区域会发出 subWindowActivated() 信号，activeSubWindow() 函数返回活动子窗口。

​	便利函数 subWindowList() 返回所有子窗口的列表。例如，此信息可用于包含窗口列表的弹出菜单。

​	子窗口按当前 WindowOrder 排序。这用于 subWindowList() 以及 activateNextSubWindow() 和 activatePreviousSubWindow()。此外，它还用于使用 cascadeSubWindows() 和 tileSubWindows() 级联或平铺窗口。

​	QMdiArea 为子窗口提供了两种内置布局策略：cascadeSubWindows() 和 tileSubWindows()。两者都是插槽，可轻松连接到菜单项。

### API

| **类别**                              | **成员/函数**                                                | **说明**                                               |
| ------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------ |
| **Public Types**                      | `enum AreaOption { DontMaximizeSubWindowOnActivation }`      | 枚举类型，定义区域选项：激活子窗口时不最大化。         |
|                                       | `flags AreaOptions`                                          | 区域选项的标志类型。                                   |
|                                       | `enum ViewMode { SubWindowView, TabbedView }`                | 视图模式的枚举类型：子窗口视图或标签视图。             |
|                                       | `enum WindowOrder { CreationOrder, StackingOrder, ActivationHistoryOrder }` | 窗口顺序的枚举类型：创建顺序、堆叠顺序或激活历史顺序。 |
| **Properties**                        | `activationOrder : WindowOrder`                              | 获取或设置窗口的激活顺序。                             |
|                                       | `background : QBrush`                                        | 获取或设置背景刷子。                                   |
|                                       | `documentMode : bool`                                        | 获取或设置是否启用文档模式。                           |
|                                       | `tabPosition : QTabWidget::TabPosition`                      | 获取或设置标签的位置。                                 |
|                                       | `tabShape : QTabWidget::TabShape`                            | 获取或设置标签的形状。                                 |
|                                       | `tabsClosable : bool`                                        | 获取或设置标签是否可关闭。                             |
|                                       | `tabsMovable : bool`                                         | 获取或设置标签是否可移动。                             |
|                                       | `viewMode : ViewMode`                                        | 获取或设置视图模式。                                   |
| **Public Functions**                  | `QMdiArea(QWidget *parent = nullptr)`                        | 构造函数，初始化 `QMdiArea` 实例。                     |
|                                       | `virtual ~QMdiArea()`                                        | 析构函数，销毁 `QMdiArea` 实例。                       |
|                                       | `QMdiArea::WindowOrder activationOrder() const`              | 获取当前的窗口激活顺序。                               |
|                                       | `QMdiSubWindow *activeSubWindow() const`                     | 获取当前激活的子窗口。                                 |
|                                       | `QMdiSubWindow *addSubWindow(QWidget *widget, Qt::WindowFlags windowFlags = Qt::WindowFlags())` | 添加子窗口，并返回该子窗口对象。                       |
|                                       | `QBrush background() const`                                  | 获取当前背景刷子的值。                                 |
|                                       | `QMdiSubWindow *currentSubWindow() const`                    | 获取当前的子窗口。                                     |
|                                       | `bool documentMode() const`                                  | 获取当前是否处于文档模式。                             |
|                                       | `void removeSubWindow(QWidget *widget)`                      | 移除指定的子窗口。                                     |
|                                       | `void setActivationOrder(QMdiArea::WindowOrder order)`       | 设置窗口的激活顺序。                                   |
|                                       | `void setBackground(const QBrush &background)`               | 设置背景刷子。                                         |
|                                       | `void setDocumentMode(bool enabled)`                         | 设置是否启用文档模式。                                 |
|                                       | `void setOption(QMdiArea::AreaOption option, bool on = true)` | 设置区域选项。                                         |
|                                       | `void setTabPosition(QTabWidget::TabPosition position)`      | 设置标签的位置。                                       |
|                                       | `void setTabShape(QTabWidget::TabShape shape)`               | 设置标签的形状。                                       |
|                                       | `void setTabsClosable(bool closable)`                        | 设置标签是否可关闭。                                   |
|                                       | `void setTabsMovable(bool movable)`                          | 设置标签是否可移动。                                   |
|                                       | `void setViewMode(QMdiArea::ViewMode mode)`                  | 设置视图模式。                                         |
|                                       | `QList<QMdiSubWindow *> subWindowList(QMdiArea::WindowOrder order = CreationOrder) const` | 获取子窗口列表，按指定顺序排列。                       |
|                                       | `QTabWidget::TabPosition tabPosition() const`                | 获取标签位置。                                         |
|                                       | `QTabWidget::TabShape tabShape() const`                      | 获取标签形状。                                         |
|                                       | `bool tabsClosable() const`                                  | 获取标签是否可关闭。                                   |
|                                       | `bool tabsMovable() const`                                   | 获取标签是否可移动。                                   |
|                                       | `bool testOption(QMdiArea::AreaOption option) const`         | 测试指定的区域选项是否启用。                           |
|                                       | `QMdiArea::ViewMode viewMode() const`                        | 获取视图模式。                                         |
| **Reimplemented Public Functions**    | `virtual QSize minimumSizeHint() const override`             | 重写，返回最小尺寸提示。                               |
|                                       | `virtual QSize sizeHint() const override`                    | 重写，返回建议的尺寸。                                 |
| **Public Slots**                      | `void activateNextSubWindow()`                               | 激活下一个子窗口。                                     |
|                                       | `void activatePreviousSubWindow()`                           | 激活上一个子窗口。                                     |
|                                       | `void cascadeSubWindows()`                                   | 子窗口层叠显示。                                       |
|                                       | `void closeActiveSubWindow()`                                | 关闭当前激活的子窗口。                                 |
|                                       | `void closeAllSubWindows()`                                  | 关闭所有子窗口。                                       |
|                                       | `void setActiveSubWindow(QMdiSubWindow *window)`             | 设置指定的子窗口为当前激活窗口。                       |
|                                       | `void tileSubWindows()`                                      | 子窗口平铺显示。                                       |
| **Signals**                           | `void subWindowActivated(QMdiSubWindow *window)`             | 信号：当某个子窗口被激活时发出。                       |
| **Reimplemented Protected Functions** | `virtual void childEvent(QChildEvent *childEvent) override`  | 重写，处理子窗口事件。                                 |
|                                       | `virtual bool event(QEvent *event) override`                 | 重写，处理事件。                                       |
|                                       | `virtual bool eventFilter(QObject *object, QEvent *event) override` | 重写，事件过滤器。                                     |
|                                       | `virtual void paintEvent(QPaintEvent *paintEvent) override`  | 重写，处理绘制事件。                                   |
|                                       | `virtual void resizeEvent(QResizeEvent *resizeEvent) override` | 重写，处理尺寸调整事件。                               |
|                                       | `virtual void scrollContentsBy(int dx, int dy) override`     | 重写，处理内容滚动事件。                               |
|                                       | `virtual void showEvent(QShowEvent *showEvent) override`     | 重写，处理显示事件。                                   |
|                                       | `virtual void timerEvent(QTimerEvent *timerEvent) override`  | 重写，处理定时器事件。                                 |
|                                       | `virtual bool viewportEvent(QEvent *event) override`         | 重写，处理视口事件。                                   |
| **Protected Slots**                   | `virtual void setupViewport(QWidget *viewport) override`     | 重写，设置视口。                                       |

## QSplashScreen

​	启动画面是通常在应用程序启动时显示的小部件。启动画面通常用于启动时间较长的应用程序（例如需要时间建立连接的数据库或网络应用程序），以向用户提供应用程序正在加载的反馈。

​	启动画面出现在屏幕中央。如果您想让启动画面小部件保持在桌面上所有其他窗口之上，将 Qt::WindowStaysOnTopHint 添加到启动画面小部件的窗口标志可能会很有用。

​	某些 X11 窗口管理器不支持“保持在最上面”标志。解决方案是设置一个计时器，定期在启动画面上调用 raise() 来模拟“保持在最上面”效果。

​	最常见的用法是在屏幕上显示主小部件之前显示启动画面。以下代码片段说明了这一点，其中显示了启动画面，并在显示应用程序的主窗口之前执行了一些初始化任务：

```
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QPixmap pixmap(":/splash.png");
	QSplashScreen splash(pixmap);
	splash.show();
	app.processEvents();
	...
	QMainWindow window;
	window.show();
	splash.finish(&window);
	return app.exec();
}
```

​	用户可以通过使用鼠标单击来隐藏启动画面。要使鼠标处理正常工作，请在启动期间定期调用 QApplication::processEvents()。

​	有时使用消息更新启动画面很有用，例如，在应用程序启动时宣布已建立连接或已加载模块：

```
QPixmap pixmap(":/splash.png");
QSplashScreen *splash = new QSplashScreen(pixmap);
splash->show();
... // 加载一些项目
splash->showMessage("Loaded modules");
QCoreApplication::processEvents();
... // 建立连接
splash->showMessage("Established connections");
QCoreApplication::processEvents();
```

QSplashScreen 通过 showMessage() 函数支持此功能。如果您希望自己进行绘制，可以使用 pixmap() 获取启动画面中使用的像素图的指针。或者，您可以子类化 QSplashScreen 并重新实现 drawContents()。

​	如果有多个屏幕，也可以在主屏幕以外的其他屏幕上显示启动画面。例如：

```
QScreen *screen = QGuiApplication::screens().at(1);
QPixmap pixmap(":/splash.png");
QSplashScreen splash(screen，pixmap);
splash.show();
```

| **类别**                              | **成员/函数**                                                | **说明**                                         |
| ------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------ |
| **Public Functions**                  | `QSplashScreen(const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags())` | 构造函数，使用指定的图片和窗口标志初始化。       |
|                                       | `QSplashScreen(QScreen *screen, const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags())` | 构造函数，使用指定的屏幕、图片和窗口标志初始化。 |
|                                       | `virtual ~QSplashScreen()`                                   | 析构函数，销毁 `QSplashScreen` 实例。            |
|                                       | `void finish(QWidget *mainWin)`                              | 显示完成，通常在主窗口显示时调用。               |
|                                       | `QString message() const`                                    | 获取当前显示的消息文本。                         |
|                                       | `const QPixmap pixmap() const`                               | 获取当前显示的图片。                             |
|                                       | `void repaint()`                                             | 重新绘制 splash 屏幕。                           |
|                                       | `void setPixmap(const QPixmap &pixmap)`                      | 设置要显示的图片。                               |
| **Public Slots**                      | `void clearMessage()`                                        | 清除当前显示的消息。                             |
|                                       | `void showMessage(const QString &message, int alignment = Qt::AlignLeft, const QColor &color = Qt::black)` | 显示指定的消息文本，并设置对齐方式和颜色。       |
| **Signals**                           | `void messageChanged(const QString &message)`                | 信号：当显示的消息内容发生变化时发出。           |
| **Protected Functions**               | `virtual void drawContents(QPainter *painter)`               | 重写，绘制 splash 屏幕内容。                     |
| **Reimplemented Protected Functions** | `virtual bool event(QEvent *e) override`                     | 重写，处理事件。                                 |
|                                       | `virtual void mousePressEvent(QMouseEvent *) override`       | 重写，处理鼠标按下事件。                         |