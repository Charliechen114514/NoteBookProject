# Qt 一些常见的部件类（I）

## QComboBox

​	`QComboBox` 是一种紧凑的方式来向用户呈现选项列表。组合框是一个选择控件，显示当前项，并在点击时弹出一个可选择的项列表。如果重载了 `insertItem()` 和 `setItemText()` 函数，组合框还可以包含图像（pixmaps）以及字符串。

​	组合框可以是可编辑的，允许用户修改列表中的每个项。对于可编辑的组合框，提供了 `clearEditText()` 函数，用于在不更改组合框内容的情况下清除显示的字符串。当用户在可编辑的组合框中输入新字符串时，控件可以选择插入该字符串，并且可以在多个位置插入。默认策略为 `InsertAtBottom`，但您可以使用 `setInsertPolicy()` 进行更改。

​	可以使用 `QValidator` 来约束可编辑组合框的输入；具体请参见 `setValidator()`。默认情况下，任何输入都是被接受的。组合框可以使用插入函数填充，例如 `insertItem()` 和 `insertItems()`。可以使用 `setItemText()` 更改项。可以使用 `removeItem()` 移除单个项，并使用 `clear()` 移除所有项。当前项的文本通过 `currentText()` 返回，某个编号项的文本通过 `itemText()` 返回。可以使用 `setCurrentIndex()` 设置当前项。组合框中的项数通过 `count()` 返回；最大项数可以通过 `setMaxCount()` 设置。可以使用 `setEditable()` 允许编辑。对于可编辑的组合框，可以使用 `setCompleter()` 设置自动完成，并通过 `setDuplicatesEnabled()` 控制用户是否可以添加重复项。

| **类别**         | **函数/信号/插槽**                                           | **说明**                                       |
| ---------------- | ------------------------------------------------------------ | ---------------------------------------------- |
| **公共函数**     | `QComboBox(QWidget *parent = nullptr)`                       | 构造函数，创建一个组合框，可以指定父窗口。     |
|                  | `virtual ~QComboBox()`                                       | 析构函数，释放组合框资源。                     |
|                  | `void addItem(const QString &text, const QVariant &userData = QVariant())` | 添加文本项，允许附加用户数据。                 |
|                  | `void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant())` | 添加带图标的项。                               |
|                  | `void addItems(const QStringList &texts)`                    | 添加多个文本项。                               |
|                  | `QCompleter *completer() const`                              | 获取与组合框关联的补全器。                     |
|                  | `int count() const`                                          | 返回组合框中的项数。                           |
|                  | `QVariant currentData(int role = Qt::UserRole) const`        | 获取当前选中项的数据。                         |
|                  | `int currentIndex() const`                                   | 返回当前选中项的索引。                         |
|                  | `QString currentText() const`                                | 返回当前选中项的文本。                         |
|                  | `bool duplicatesEnabled() const`                             | 检查是否允许重复项。                           |
|                  | `int findData(const QVariant &data, int role = Qt::UserRole, Qt::MatchFlags flags = static_cast[Qt::MatchFlags](https://chatgpt.com/c/6724ba44-ad64-800e-85b8-8908b4dc5e22)(Qt::MatchExactly | Qt::MatchCaseSensitive)) const`                |
|                  | `int findText(const QString &text, Qt::MatchFlags flags = Qt::MatchExactly | Qt::MatchCaseSensitive) const`                 |
|                  | `bool hasFrame() const`                                      | 检查组合框是否有边框。                         |
|                  | `virtual void hidePopup()`                                   | 隐藏下拉列表。                                 |
|                  | `QSize iconSize() const`                                     | 获取图标的大小。                               |
|                  | `void insertItem(int index, const QString &text, const QVariant &userData = QVariant())` | 在指定索引位置插入文本项。                     |
|                  | `void insertItem(int index, const QIcon &icon, const QString &text, const QVariant &userData = QVariant())` | 在指定索引位置插入带图标的项。                 |
|                  | `void insertItems(int index, const QStringList &list)`       | 在指定索引位置插入多个项。                     |
|                  | `QComboBox::InsertPolicy insertPolicy() const`               | 获取插入策略。                                 |
|                  | `void insertSeparator(int index)`                            | 在指定索引位置插入分隔符。                     |
|                  | `bool isEditable() const`                                    | 检查组合框是否可编辑。                         |
|                  | `QVariant itemData(int index, int role = Qt::UserRole) const` | 获取指定索引项的用户数据。                     |
|                  | `QAbstractItemDelegate *itemDelegate() const`                | 获取项委托。                                   |
|                  | `QIcon itemIcon(int index) const`                            | 获取指定索引项的图标。                         |
|                  | `QString itemText(int index) const`                          | 获取指定索引项的文本。                         |
|                  | `QLineEdit *lineEdit() const`                                | 获取与组合框关联的编辑框。                     |
|                  | `int maxCount() const`                                       | 获取组合框的最大项数。                         |
|                  | `int maxVisibleItems() const`                                | 获取组合框可见项的最大数。                     |
|                  | `int minimumContentsLength() const`                          | 获取组合框内容的最小长度。                     |
|                  | `QAbstractItemModel *model() const`                          | 获取与组合框关联的数据模型。                   |
|                  | `int modelColumn() const`                                    | 获取模型中可见列的索引。                       |
|                  | `QString placeholderText() const`                            | 获取占位符文本。                               |
|                  | `void removeItem(int index)`                                 | 移除指定索引的项。                             |
|                  | `QModelIndex rootModelIndex() const`                         | 获取根模型索引。                               |
|                  | `void setCompleter(QCompleter *completer)`                   | 设置与组合框关联的补全器。                     |
|                  | `void setDuplicatesEnabled(bool enable)`                     | 启用或禁用重复项。                             |
|                  | `void setEditable(bool editable)`                            | 设置组合框是否可编辑。                         |
|                  | `void setFrame(bool)`                                        | 设置组合框的边框可见性。                       |
|                  | `void setIconSize(const QSize &size)`                        | 设置图标的大小。                               |
|                  | `void setInsertPolicy(QComboBox::InsertPolicy policy)`       | 设置插入策略。                                 |
|                  | `void setItemData(int index, const QVariant &value, int role = Qt::UserRole)` | 设置指定索引项的用户数据。                     |
|                  | `void setItemDelegate(QAbstractItemDelegate *delegate)`      | 设置项委托。                                   |
|                  | `void setItemIcon(int index, const QIcon &icon)`             | 设置指定索引项的图标。                         |
|                  | `void setItemText(int index, const QString &text)`           | 设置指定索引项的文本。                         |
|                  | `void setLineEdit(QLineEdit *edit)`                          | 设置与组合框关联的编辑框。                     |
|                  | `void setMaxCount(int max)`                                  | 设置组合框的最大项数。                         |
|                  | `void setMaxVisibleItems(int maxItems)`                      | 设置组合框可见项的最大数。                     |
|                  | `void setMinimumContentsLength(int characters)`              | 设置组合框内容的最小长度。                     |
|                  | `virtual void setModel(QAbstractItemModel *model)`           | 设置与组合框关联的数据模型。                   |
|                  | `void setModelColumn(int visibleColumn)`                     | 设置可见列的索引。                             |
|                  | `void setPlaceholderText(const QString &placeholderText)`    | 设置占位符文本。                               |
|                  | `void setRootModelIndex(const QModelIndex &index)`           | 设置根模型索引。                               |
|                  | `void setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy policy)` | 设置大小调整策略。                             |
|                  | `void setValidator(const QValidator *validator)`             | 设置输入验证器。                               |
|                  | `void setView(QAbstractItemView *itemView)`                  | 设置组合框的视图。                             |
|                  | `virtual void showPopup()`                                   | 显示下拉列表。                                 |
|                  | `QComboBox::SizeAdjustPolicy sizeAdjustPolicy() const`       | 获取大小调整策略。                             |
|                  | `const QValidator *validator() const`                        | 获取输入验证器。                               |
|                  | `QAbstractItemView *view() const`                            | 获取组合框的视图。                             |
| **重写公共函数** | `virtual bool event(QEvent *event) override`                 | 处理事件。                                     |
|                  | `virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const override` | 查询输入法信息。                               |
|                  | `virtual QSize minimumSizeHint() const override`             | 获取组合框的最小尺寸提示。                     |
|                  | `virtual QSize sizeHint() const override`                    | 获取组合框的尺寸提示。                         |
| **公共插槽**     | `void clear()`                                               | 清空组合框中的所有项。                         |
|                  | `void clearEditText()`                                       | 清空编辑框的文本。                             |
|                  | `void setCurrentIndex(int index)`                            | 设置当前选中项的索引。                         |
|                  | `void setCurrentText(const QString &text)`                   | 设置当前选中项的文本。                         |
|                  | `void setEditText(const QString &text)`                      | 设置编辑框的文本。                             |
| **信号**         | `void activated(int index)`                                  | 当选择项被激活时发射信号，返回选中项的索引。   |
|                  | `void currentIndexChanged(int index)`                        | 当当前索引发生变化时发射信号。                 |
|                  | `void currentTextChanged(const QString &text)`               | 当当前文本发生变化时发射信号。                 |
|                  | `void editTextChanged(const QString &text)`                  | 当编辑框的文本发生变化时发射信号。             |
|                  | `void highlighted(int index)`                                | 当高亮项发生变化时发射信号，返回高亮项的索引。 |
|                  | `void textActivated(const QString &text)`                    | 当文本项被激活时发射信号，返回激活的文本。     |
|                  | `void textHighlighted(const QString &text)`                  | 当高亮文本发生变化时发射信号，返回高亮的文本。 |
| **保护函数**     | `virtual void initStyleOption(QStyleOptionComboBox *option) const` | 初始化样式选项。                               |
| **重写保护函数** | `virtual void changeEvent(QEvent *e) override`               | 处理改变事件。                                 |
|                  | `virtual void contextMenuEvent(QContextMenuEvent *e) override` | 处理上下文菜单事件。                           |
|                  | `virtual void focusInEvent(QFocusEvent *e) override`         | 处理获取焦点事件。                             |
|                  | `virtual void focusOutEvent(QFocusEvent *e) override`        | 处理失去焦点事件。                             |
|                  | `virtual void hideEvent(QHideEvent *e) override`             | 处理隐藏事件。                                 |
|                  | `virtual void inputMethodEvent(QInputMethodEvent *e) override` | 处理输入法事件。                               |
|                  | `virtual void keyPressEvent(QKeyEvent *e) override`          | 处理按键按下事件。                             |
|                  | `virtual void keyReleaseEvent(QKeyEvent *e) override`        | 处理按键释放事件。                             |
|                  | `virtual void mousePressEvent(QMouseEvent *e) override`      | 处理鼠标按下事件。                             |
|                  | `virtual void mouseReleaseEvent(QMouseEvent *e) override`    | 处理鼠标释放事件。                             |
|                  | `virtual void paintEvent(QPaintEvent *e) override`           | 处理绘制事件。                                 |
|                  | `virtual void resizeEvent(QResizeEvent *e) override`         | 处理调整大小事件。                             |
|                  | `virtual void showEvent(QShowEvent *e) override`             | 处理显示事件。                                 |
|                  | `virtual void wheelEvent(QWheelEvent *e) override`           | 处理滚轮事件。                                 |

## QToolBar

​	工具栏通常通过调用 `QMainWindow::addToolBar(const QString &title)` 创建，但也可以作为 `QVBoxLayout` 中的第一个小部件添加。工具栏按钮通过添加动作来添加，使用 `addAction()` 或 `insertAction()`。按钮组可以通过 `addSeparator()` 或 `insertSeparator()` 来分隔。如果某个工具栏按钮不合适，可以使用 `addWidget()` 或 `insertWidget()` 插入一个小部件。适合的小部件的例子包括 `QSpinBox`、`QDoubleSpinBox` 和 `QComboBox`。当工具栏按钮被按下时，会发出 `actionTriggered()` 信号。

​	工具栏可以固定在特定区域（例如窗口顶部），也可以在工具栏区域之间移动；参见 `setMovable()`、`isMovable()`、`allowedAreas()` 和 `isAreaAllowed()`。当工具栏以某种方式被调整大小，以至于太小而无法显示其包含的所有项时，扩展按钮将作为工具栏中的最后一项出现。按下扩展按钮将弹出一个菜单，包含当前无法适应工具栏的项。当 `QToolBar` 不是 `QMainWindow` 的子对象时，它失去了使用 `addWidget()` 向工具栏添加小部件来填充扩展弹出窗口的能力。请使用通过继承 `QWidgetAction` 并实现 `QWidgetAction::createWidget()` 创建的控件动作。

### API

| 公共函数                                                  | 描述                                         |
| --------------------------------------------------------- | -------------------------------------------- |
| QToolBar(QWidget *parent = nullptr)                       | 构造函数，创建工具栏，指定父组件。           |
| QToolBar(const QString &title, QWidget *parent = nullptr) | 构造函数，创建带标题的工具栏，指定父组件。   |
| virtual ~QToolBar()                                       | 析构函数，销毁工具栏。                       |
| QAction *actionAt(const QPoint &p) const                  | 返回指定位置的动作（按钮）。                 |
| QAction *actionAt(int x, int y) const                     | 返回指定坐标的动作（按钮）。                 |
| QAction *addSeparator()                                   | 添加分隔符，返回创建的 QAction。             |
| QAction *addWidget(QWidget *widget)                       | 添加一个小部件到工具栏，返回创建的 QAction。 |
| Qt::ToolBarAreas allowedAreas() const                     | 返回允许的区域。                             |
| void clear()                                              | 清除工具栏中的所有动作。                     |
| QSize iconSize() const                                    | 返回图标的大小。                             |
| QAction *insertSeparator(QAction *before)                 | 在指定动作之前插入一个分隔符。               |
| QAction *insertWidget(QAction *before, QWidget *widget)   | 在指定动作之前插入一个小部件。               |
| bool isAreaAllowed(Qt::ToolBarArea area) const            | 检查指定区域是否被允许。                     |
| bool isFloatable() const                                  | 检查工具栏是否可以浮动。                     |
| bool isFloating() const                                   | 检查工具栏是否处于浮动状态。                 |
| bool isMovable() const                                    | 检查工具栏是否可以移动。                     |
| Qt::Orientation orientation() const                       | 返回工具栏的方向（水平或垂直）。             |
| void setAllowedAreas(Qt::ToolBarAreas areas)              | 设置允许的区域。                             |
| void setFloatable(bool floatable)                         | 设置工具栏是否可以浮动。                     |
| void setMovable(bool movable)                             | 设置工具栏是否可以移动。                     |
| void setOrientation(Qt::Orientation orientation)          | 设置工具栏的方向。                           |
| QAction *toggleViewAction() const                         | 返回切换视图的 QAction。                     |
| Qt::ToolButtonStyle toolButtonStyle() const               | 返回工具按钮的样式。                         |
| QWidget *widgetForAction(QAction *action) const           | 返回与指定动作关联的小部件。                 |

| 公共槽                                                       | 描述                 |
| ------------------------------------------------------------ | -------------------- |
| void setIconSize(const QSize &iconSize)                      | 设置图标的大小。     |
| void setToolButtonStyle(Qt::ToolButtonStyle toolButtonStyle) | 设置工具按钮的样式。 |

| 信号                                                         | 描述                             |
| ------------------------------------------------------------ | -------------------------------- |
| void actionTriggered(QAction *action)                        | 当某个动作被触发时发出信号。     |
| void allowedAreasChanged(Qt::ToolBarAreas allowedAreas)      | 允许的区域发生改变时发出信号。   |
| void iconSizeChanged(const QSize &iconSize)                  | 图标大小发生改变时发出信号。     |
| void movableChanged(bool movable)                            | 可移动状态发生改变时发出信号。   |
| void orientationChanged(Qt::Orientation orientation)         | 方向发生改变时发出信号。         |
| void toolButtonStyleChanged(Qt::ToolButtonStyle toolButtonStyle) | 工具按钮样式发生改变时发出信号。 |
| void topLevelChanged(bool topLevel)                          | 顶层状态发生改变时发出信号。     |
| void visibilityChanged(bool visible)                         | 可见状态发生改变时发出信号。     |



## QStatusBar

每个状态指示符属于以下三种类别之一：

- 临时 - 短暂占用状态栏的大部分空间。例如，用于解释工具提示文本或菜单项。
- 正常 - 占用状态栏的一部分，可能会被临时消息隐藏。例如，用于在文字处理器中显示页码和行号。
- 永久 - 永远不会被隐藏。例如，用于重要的模式指示，一些应用程序在状态栏中放置大写锁定指示符。

`QStatusBar` 允许您显示这三种类型的指示符。通常，状态栏功能的请求与 `QMainWindow` 对象相关。`QMainWindow` 提供一个主应用程序窗口，包含菜单栏、工具栏、停靠窗口和围绕大中央部件的状态栏。可以使用 `QMainWindow::statusBar()` 函数获取状态栏，使用 `QMainWindow::setStatusBar()` 函数替换状态栏。

​	使用 `showMessage()` 槽来显示临时消息：

```
statusBar()->showMessage(tr("Ready"));
```

​	要移除临时消息，可以使用 `clearMessage()` 槽，或者在调用 `showMessage()` 时设置时间限制。例如：

```
statusBar()->showMessage(tr("Ready"), 2000);
```

​	使用 `currentMessage()` 函数检索当前显示的临时消息。`QStatusBar` 类还提供了 `messageChanged()` 信号，该信号在临时状态消息更改时发出。正常和永久消息通过创建小部件（如 `QLabel`、`QProgressBar` 或 `QToolButton`），然后使用 `addWidget()` 或 `addPermanentWidget()` 函数将其添加到状态栏来显示。使用 `removeWidget()` 函数从状态栏中移除这些消息。

```
statusBar()->addWidget(new MyReadWriteIndication);
```

​	默认情况下，`QStatusBar` 在右下角提供一个调整大小手柄。您可以使用 `setSizeGripEnabled()` 函数禁用它。使用 `isSizeGripEnabled()` 函数确定调整大小手柄的当前状态。

### API

| 公共函数                                                     | 描述                                     |
| ------------------------------------------------------------ | ---------------------------------------- |
| `QStatusBar(QWidget *parent = nullptr)`                      | 构造函数，创建一个状态栏。               |
| `virtual ~QStatusBar()`                                      | 析构函数，销毁状态栏。                   |
| `void addPermanentWidget(QWidget *widget, int stretch = 0)`  | 添加一个永久性小部件到状态栏。           |
| `void addWidget(QWidget *widget, int stretch = 0)`           | 添加一个小部件到状态栏。                 |
| `QString currentMessage() const`                             | 返回当前显示的临时消息。                 |
| `int insertPermanentWidget(int index, QWidget *widget, int stretch = 0)` | 在指定位置插入一个永久性小部件到状态栏。 |
| `int insertWidget(int index, QWidget *widget, int stretch = 0)` | 在指定位置插入一个小部件到状态栏。       |
| `bool isSizeGripEnabled() const`                             | 判断是否启用调整大小手柄。               |
| `void removeWidget(QWidget *widget)`                         | 从状态栏移除指定的小部件。               |
| `void setSizeGripEnabled(bool)`                              | 设置是否启用调整大小手柄。               |

| 公共槽                                                      | 描述                           |
| ----------------------------------------------------------- | ------------------------------ |
| `void clearMessage()`                                       | 清除当前显示的临时消息。       |
| `void showMessage(const QString &message, int timeout = 0)` | 显示临时消息，超时后自动清除。 |

| 信号                                          | 描述                           |
| --------------------------------------------- | ------------------------------ |
| `void messageChanged(const QString &message)` | 当临时状态消息变化时发出信号。 |

| 受保护函数          | 描述                         |
| ------------------- | ---------------------------- |
| `void hideOrShow()` | 隐藏或显示状态栏的辅助函数。 |
| `void reformat()`   | 重新格式化状态栏的辅助函数。 |

| 重写的受保护函数                                       | 描述                         |
| ------------------------------------------------------ | ---------------------------- |
| `virtual bool event(QEvent *e) override`               | 处理事件的重写函数。         |
| `virtual void paintEvent(QPaintEvent *event) override` | 处理绘制事件的重写函数。     |
| `virtual void resizeEvent(QResizeEvent *e) override`   | 处理调整大小事件的重写函数。 |
| `virtual void showEvent(QShowEvent *) override`        | 处理显示事件的重写函数。     |

## QPlainTextEdit

### QPlainTextEdit 类概述

​	`QPlainTextEdit` 是一个高级的纯文本查看器/编辑器，优化用于处理大文档并快速响应用户输入。它使用与 `QTextEdit` 类似的技术和概念，但专注于纯文本处理。

- `QPlainTextEdit` 基于段落和字符进行工作。段落是格式化字符串，自动换行以适应小部件的宽度。默认情况下，读取纯文本时，一个换行符表示一个段落。文档由零个或多个段落组成，段落之间通过硬换行符分隔。段落内的每个字符都有自己的属性，例如字体和颜色。
- 默认情况下，`QPlainTextEdit` 中鼠标光标为 `Qt::IBeamCursor`，可以通过视口的光标属性进行更改。

- 使用 `setPlainText()` 设置或替换文本，该方法会删除现有文本并用传入的文本替换。
- 可以使用 `QTextCursor` 类插入文本，或使用便利函数 `insertPlainText()`、`appendPlainText()` 或 `paste()`。
- 默认情况下，文本编辑器会在空白处换行以适应小部件的宽度。使用 `setLineWrapMode()` 函数可指定换行方式，`WidgetWidth` 表示在小部件宽度内换行，`NoWrap` 表示不换行。如果使用 `WidgetWidth` 换行，可以通过 `setWordWrapMode()` 指定是在哪些地方断行。
- 使用 `find()` 函数可以查找并选择文本中的指定字符串。
- 若要限制 `QPlainTextEdit` 中段落的总数（例如用于日志查看器），可以使用 `maximumBlockCount` 属性。结合 `setMaximumBlockCount()` 和 `appendPlainText()`，`QPlainTextEdit` 可以有效地用作日志文本查看器。通过设置 `centerOnScroll()` 属性，可以进一步提高日志查看器的性能。文本可以以有限的方式格式化，或通过使用语法高亮器，或通过 `appendHtml()` 追加 HTML 格式的文本。虽然 `QPlainTextEdit` 不支持复杂的富文本渲染（如表格和浮动），但它支持基本的段落格式化。

​	在只读模式下，`QPlainTextEdit` 的键绑定限制为导航，仅可通过鼠标选择文本：

| 按键           | 动作           |
| -------------- | -------------- |
| Qt::UpArrow    | 上移一行       |
| Qt::DownArrow  | 下移一行       |
| Qt::LeftArrow  | 左移一个字符   |
| Qt::RightArrow | 右移一个字符   |
| PageUp         | 上移一页       |
| PageDown       | 下移一页       |
| Home           | 移动到文本开始 |
| End            | 移动到文本结束 |
| Alt+Wheel      | 横向滚动页面   |
| Ctrl+Wheel     | 缩放文本       |
| Ctrl+A         | 选择所有文本   |

- 在编辑模式下，文本选择由 `QTextCursor` 类处理，该类提供创建选择、检索文本内容或删除选择的功能。可以使用 `textCursor()` 方法获取与用户可见光标对应的对象。如果要在 `QPlainTextEdit` 中设置选择，只需在 `QTextCursor` 对象上创建选择，然后使用 `setCursor()` 将该光标设置为可见光标。可以使用 `copy()` 将选择复制到剪贴板，或使用 `cut()` 剪切到剪贴板。可以使用 `selectAll()` 选择全部文本。
- `QPlainTextEdit` 持有一个 `QTextDocument` 对象，可以通过 `document()` 方法获取。可以使用 `setDocument()` 设置自己的文档对象。`QTextDocument` 在文本更改时会发出 `textChanged()` 信号，并提供 `isModified()` 方法，如果文本自加载或上次调用 `setModified(false)` 以来已被修改，则返回 `true`。此外，它还提供撤销和重做的方法。

​	对于高亮：`QPlainTextEdit` 与 `QSyntaxHighlighter` 配合使用。

| 按键            | 动作                         |
| --------------- | ---------------------------- |
| Backspace       | 删除光标左侧的字符           |
| Delete          | 删除光标右侧的字符           |
| Ctrl+C          | 将选中的文本复制到剪贴板     |
| Ctrl+Insert     | 将选中的文本复制到剪贴板     |
| Ctrl+K          | 删除光标到行末的内容         |
| Ctrl+V          | 将剪贴板文本粘贴到文本编辑器 |
| Shift+Insert    | 将剪贴板文本粘贴到文本编辑器 |
| Ctrl+X          | 删除选中文本并复制到剪贴板   |
| Shift+Delete    | 删除选中文本并复制到剪贴板   |
| Ctrl+Z          | 撤销上一个操作               |
| Ctrl+Y          | 重做上一个操作               |
| LeftArrow       | 光标左移一个字符             |
| Ctrl+LeftArrow  | 光标左移一个单词             |
| RightArrow      | 光标右移一个字符             |
| Ctrl+RightArrow | 光标右移一个单词             |
| UpArrow         | 光标上移一行                 |
| Ctrl+UpArrow    | 光标上移一个单词             |
| DownArrow       | 光标下移一行                 |
| Ctrl+DownArrow  | 光标下移一个单词             |
| PageUp          | 光标上移一页                 |
| PageDown        | 光标下移一页                 |
| Home            | 光标移到行首                 |
| Ctrl+Home       | 光标移到文本开始             |
| End             | 光标移到行末                 |
| Ctrl+End        | 光标移到文本结束             |
| Alt+Wheel       | 横向滚动页面                 |
| Ctrl+Wheel      | 缩放文本                     |

要选择（标记）文本，可以在按住 Shift 键的同时按下某个移动键，例如，按 Shift+Right Arrow 将选择光标右侧的字符，按 Shift+Ctrl+Right Arrow 将选择光标右侧的单词等。

`QPlainTextEdit` 是一个轻量级类，使用了大部分支撑 `QTextEdit` 和 `QTextDocument` 的技术。它相较于 `QTextEdit` 的性能优势主要来自使用一种不同且简化的文本布局，即 `QPlainTextDocumentLayout`。该布局不支持表格或嵌入框架，并用逐行或逐段落的滚动方式替代了像素精确的高度计算。这使得它能够处理显著更大的文档，同时在启用换行的情况下实时调整编辑器大小。此外，它还使得日志查看器的性能得到了提升（见 `setMaximumBlockCount()`）。

### API

| 成员                                                         | 描述                               |
| ------------------------------------------------------------ | ---------------------------------- |
| **构造函数**                                                 |                                    |
| `QPlainTextEdit(QWidget *parent = nullptr)`                  | 创建一个空的文本编辑器。           |
| `QPlainTextEdit(const QString &text, QWidget *parent = nullptr)` | 创建一个带有初始文本的文本编辑器。 |
| **析构函数**                                                 | `virtual ~QPlainTextEdit()`        |
| **成员函数**                                                 |                                    |
| `QString anchorAt(const QPoint &pos) const`                  | 返回指定位置的锚点。               |
| `bool backgroundVisible() const`                             | 返回背景是否可见。                 |
| `int blockCount() const`                                     | 返回文本块的数量。                 |
| `bool canPaste() const`                                      | 检查是否可以粘贴内容。             |
| `bool centerOnScroll() const`                                | 返回是否在滚动时中心化光标。       |
| `QMenu *createStandardContextMenu()`                         | 创建标准上下文菜单。               |
| `QMenu *createStandardContextMenu(const QPoint &position)`   | 在指定位置创建标准上下文菜单。     |
| `QTextCharFormat currentCharFormat() const`                  | 返回当前字符格式。                 |
| `QTextCursor cursorForPosition(const QPoint &pos) const`     | 返回指定位置的光标。               |
| `QRect cursorRect() const`                                   | 返回光标的矩形区域。               |
| `QRect cursorRect(const QTextCursor &cursor) const`          | 返回指定光标的矩形区域。           |
| `int cursorWidth() const`                                    | 返回光标的宽度。                   |
| `QTextDocument *document() const`                            | 返回关联的文本文档。               |
| `QString documentTitle() const`                              | 返回文档标题。                     |
| `void ensureCursorVisible()`                                 | 确保光标可见。                     |
| `QList<QTextEdit::ExtraSelection> extraSelections() const`   | 返回额外选中的内容。               |
| `bool find(const QString &exp, QTextDocument::FindFlags options = QTextDocument::FindFlags())` | 查找指定文本。                     |
| `bool find(const QRegularExpression &exp, QTextDocument::FindFlags options = QTextDocument::FindFlags())` | 使用正则表达式查找文本。           |
| `bool isReadOnly() const`                                    | 检查是否为只读模式。               |
| `bool isUndoRedoEnabled() const`                             | 检查撤销/重做功能是否启用。        |
| `QPlainTextEdit::LineWrapMode lineWrapMode() const`          | 返回行换行模式。                   |
| `virtual QVariant loadResource(int type, const QUrl &name)`  | 加载指定类型的资源。               |
| `int maximumBlockCount() const`                              | 返回最大文本块数。                 |
| `void mergeCurrentCharFormat(const QTextCharFormat &modifier)` | 合并当前字符格式。                 |
| `void moveCursor(QTextCursor::MoveOperation operation, QTextCursor::MoveMode mode = QTextCursor::MoveAnchor)` | 移动光标。                         |
| `bool overwriteMode() const`                                 | 返回是否为覆盖模式。               |
| `QString placeholderText() const`                            | 返回占位符文本。                   |
| `void print(QPagedPaintDevice *printer) const`               | 打印文本。                         |
| `void setBackgroundVisible(bool visible)`                    | 设置背景可见性。                   |
| `void setCenterOnScroll(bool enabled)`                       | 设置滚动时中心化光标。             |
| `void setCurrentCharFormat(const QTextCharFormat &format)`   | 设置当前字符格式。                 |
| `void setCursorWidth(int width)`                             | 设置光标宽度。                     |
| `void setDocument(QTextDocument *document)`                  | 设置关联的文本文档。               |
| `void setDocumentTitle(const QString &title)`                | 设置文档标题。                     |
| `void setExtraSelections(const QList<QTextEdit::ExtraSelection> &selections)` | 设置额外选中的内容。               |
| `void setLineWrapMode(QPlainTextEdit::LineWrapMode mode)`    | 设置行换行模式。                   |
| `void setMaximumBlockCount(int maximum)`                     | 设置最大文本块数。                 |
| `void setOverwriteMode(bool overwrite)`                      | 设置覆盖模式。                     |
| `void setPlaceholderText(const QString &placeholderText)`    | 设置占位符文本。                   |
| `void setReadOnly(bool ro)`                                  | 设置为只读模式。                   |
| `void setTabChangesFocus(bool b)`                            | 设置 Tab 键是否改变焦点。          |
| `void setTabStopDistance(qreal distance)`                    | 设置 Tab 停止距离。                |
| `void setTextCursor(const QTextCursor &cursor)`              | 设置文本光标。                     |
| `void setTextInteractionFlags(Qt::TextInteractionFlags flags)` | 设置文本交互标志。                 |
| `void setUndoRedoEnabled(bool enable)`                       | 设置撤销/重做功能。                |
| `void setWordWrapMode(QTextOption::WrapMode policy)`         | 设置单词换行模式。                 |
| `bool tabChangesFocus() const`                               | 返回 Tab 键是否改变焦点的状态。    |
| `qreal tabStopDistance() const`                              | 返回 Tab 停止距离。                |
| `QTextCursor textCursor() const`                             | 返回当前文本光标。                 |
| `Qt::TextInteractionFlags textInteractionFlags() const`      | 返回文本交互标志。                 |
| `QString toPlainText() const`                                | 返回纯文本内容。                   |
| `QTextOption::WrapMode wordWrapMode() const`                 | 返回单词换行模式。                 |
| **重载函数**                                                 |                                    |
| `virtual QVariant inputMethodQuery(Qt::InputMethodQuery property) const override` | 输入法查询。                       |
| **公共槽**                                                   |                                    |
| `void appendHtml(const QString &html)`                       | 添加 HTML 内容。                   |
| `void appendPlainText(const QString &text)`                  | 添加纯文本。                       |
| `void centerCursor()`                                        | 将光标居中。                       |
| `void clear()`                                               | 清除文本。                         |
| `void copy()`                                                | 复制选中的文本。                   |
| `void cut()`                                                 | 剪切选中的文本。                   |
| `void insertPlainText(const QString &text)`                  | 插入纯文本。                       |
| `void paste()`                                               | 粘贴内容。                         |
| `void redo()`                                                | 重做操作。                         |
| `void selectAll()`                                           | 选择所有文本。                     |
| `void setPlainText(const QString &text)`                     | 设置纯文本内容。                   |
| `void undo()`                                                | 撤销操作。                         |
| `void zoomIn(int range = 1)`                                 | 放大文本。                         |
| `void zoomOut(int range = 1)`                                | 缩小文本。                         |
| **信号**                                                     |                                    |
| `void blockCountChanged(int newBlockCount)`                  | 文本块数变化时发出信号。           |
| `void copyAvailable(bool yes)`                               | 复制可用状态变化时发出信号。       |
| `void cursorPositionChanged()`                               | 光标位置变化时发出信号。           |
| `void modificationChanged(bool changed)`                     | 文本修改状态变化时发出信号。       |
| `void redoAvailable(bool available)`                         | 重做可用状态变化时发出信号。       |
| `void selectionChanged()`                                    | 选择变化时发出信号。               |
| `void textChanged()`                                         | 文本内容变化时发出信号。           |
| `void undoAvailable(bool available)`                         | 撤销可用状态变化时发出信号。       |
| `void updateRequest(const QRect &rect, int dy)`              | 更新请求时发出信号。               |
| **保护函数**                                                 |                                    |
| `QRectF blockBoundingGeometry(const QTextBlock &block) const` | 返回指定文本块的边界矩形。         |
| `QRectF blockBoundingRect(const QTextBlock &block) const`    | 返回指定文本块的边界矩形。         |
| `virtual bool canInsertFromMimeData(const QMimeData *source) const` | 检查是否可以从 MIME 数据插入。     |
| `QPointF contentOffset() const`                              | 返回内容偏移量。                   |
| `virtual QMimeData *createMimeDataFromSelection() const`     | 从选中内容创建 MIME 数据。         |
| `QTextBlock firstVisibleBlock() const`                       | 返回第一个可见的文本块。           |
| `QAbstractTextDocumentLayout::PaintContext getPaintContext() const` | 获取绘制上下文。                   |
| `virtual void insertFromMimeData(const QMimeData *source)`   | 从 MIME 数据插入内容。             |
| **重载保护函数**                                             |                                    |
| `virtual void changeEvent(QEvent *e) override`               | 事件变化时的处理。                 |
| `virtual void contextMenuEvent(QContextMenuEvent *event) override` | 上下文菜单事件处理。               |
| `virtual void dragEnterEvent(QDragEnterEvent *e) override`   | 拖放进入事件处理。                 |
| `virtual void dragLeaveEvent(QDragLeaveEvent *e) override`   | 拖放离开事件处理。                 |
| `virtual void dragMoveEvent(QDragMoveEvent *e) override`     | 拖放移动事件处理。                 |
| `virtual void dropEvent(QDropEvent *e) override`             | 放下事件处理。                     |
| `virtual void focusInEvent(QFocusEvent *e) override`         | 焦点进入事件处理。                 |
| `virtual bool focusNextPrevChild(bool next) override`        | 焦点切换事件处理。                 |
| `virtual void focusOutEvent(QFocusEvent *e) override`        | 焦点离开事件处理。                 |
| `virtual void inputMethodEvent(QInputMethodEvent *e) override` | 输入法事件处理。                   |
| `virtual void keyPressEvent(QKeyEvent *e) override`          | 按键按下事件处理。                 |
| `virtual void keyReleaseEvent(QKeyEvent *e) override`        | 按键释放事件处理。                 |
| `virtual void mouseDoubleClickEvent(QMouseEvent *e) override` | 鼠标双击事件处理。                 |
| `virtual void mouseMoveEvent(QMouseEvent *e) override`       | 鼠标移动事件处理。                 |
| `virtual void mousePressEvent(QMouseEvent *e) override`      | 鼠标按下事件处理。                 |
| `virtual void mouseReleaseEvent(QMouseEvent *e) override`    | 鼠标释放事件处理。                 |
| `virtual void paintEvent(QPaintEvent *e) override`           | 绘制事件处理。                     |
| `virtual void resizeEvent(QResizeEvent *e) override`         | 窗口大小变化事件处理。             |
| `virtual void scrollContentsBy(int dx, int dy) override`     | 内容滚动事件处理。                 |
| `virtual void showEvent(QShowEvent *) override`              | 显示事件处理。                     |
| `virtual void wheelEvent(QWheelEvent *e) override`           | 滚轮事件处理。                     |

## QTextEdit

`QTextEdit` 是一个高级 WYSIWYG （所见即所得）文本编辑器，支持富文本格式，可以使用 HTML 风格的标签或 Markdown 格式进行文本编辑。它被优化为处理大文档并快速响应用户输入。

- **段落和字符**：`QTextEdit` 处理段落和字符。段落是格式化字符串，根据小部件的宽度进行换行。默认情况下，纯文本中的换行符表示一个段落。文档由零个或多个段落组成，段落通过硬换行分隔。每个字符可以有自己的属性，例如字体和颜色。
- **支持的内容**：`QTextEdit` 可以显示图像、列表和表格，支持加载纯文本和富文本文件。

| **方法/信号**                                               | **描述**                                   |
| ----------------------------------------------------------- | ------------------------------------------ |
| **构造函数**                                                |                                            |
| `QTextEdit(QWidget *parent = nullptr)`                      | 创建一个文本编辑器，指定父级小部件。       |
| `QTextEdit(const QString &text, QWidget *parent = nullptr)` | 使用指定文本创建一个文本编辑器。           |
| `virtual ~QTextEdit()`                                      | 析构函数。                                 |
| **文本与格式**                                              |                                            |
| `void setHtml(const QString &text)`                         | 设置编辑器内容为 HTML 格式，替换现有文本。 |
| `void setPlainText(const QString &text)`                    | 设置编辑器内容为纯文本格式。               |
| `QString toHtml() const`                                    | 返回编辑器内容的 HTML 表示。               |
| `QString toPlainText() const`                               | 返回编辑器内容的纯文本表示。               |
| `void setMarkdown(const QString &markdown)`                 | 设置编辑器内容为 Markdown 格式。           |
| **光标与选择**                                              |                                            |
| `QTextCursor textCursor() const`                            | 获取当前的文本光标对象。                   |
| `void setTextCursor(const QTextCursor &cursor)`             | 设置文本光标为指定的光标对象。             |
| `void selectAll()`                                          | 选择所有文本。                             |
| **复制、剪切与粘贴**                                        |                                            |
| `bool canPaste() const`                                     | 检查是否可以粘贴文本。                     |
| `void copy()`                                               | 复制选中文本到剪贴板。                     |
| `void cut()`                                                | 剪切选中文本到剪贴板。                     |
| `void paste()`                                              | 从剪贴板粘贴文本。                         |
| **撤销与重做**                                              |                                            |
| `void undo()`                                               | 撤销上一个操作。                           |
| `void redo()`                                               | 重做上一个操作。                           |
| **信号**                                                    |                                            |
| `void textChanged()`                                        | 文本内容改变时发出信号。                   |
| `void currentCharFormatChanged(const QTextCharFormat &f)`   | 当前字符格式发生变化时发出信号。           |
| **拖放功能**                                                |                                            |
| `bool canInsertFromMimeData(const QMimeData *source) const` | 检查是否可以从 MIME 数据插入内容。         |
| `void insertFromMimeData(const QMimeData *source)`          | 从 MIME 数据插入内容。                     |
| **编辑键绑定**                                              |                                            |
| **Keypresses**                                              | **Action**                                 |
| Backspace                                                   | 删除光标左侧的字符。                       |
| Delete                                                      | 删除光标右侧的字符。                       |
| Ctrl+C                                                      | 复制选中文本到剪贴板。                     |
| Ctrl+V                                                      | 粘贴剪贴板文本到编辑器。                   |
| Ctrl+X                                                      | 删除选中文本并复制到剪贴板。               |
| Ctrl+Z                                                      | 撤销上一个操作。                           |
| Ctrl+Y                                                      | 重做上一个操作。                           |

### API

| **方法/信号**                                                | **描述**                             |
| ------------------------------------------------------------ | ------------------------------------ |
| **构造函数**                                                 |                                      |
| `QTextEdit(QWidget *parent = nullptr)`                       | 创建一个文本编辑器，指定父级小部件。 |
| `QTextEdit(const QString &text, QWidget *parent = nullptr)`  | 使用指定文本创建一个文本编辑器。     |
| `virtual ~QTextEdit()`                                       | 析构函数。                           |
| **文本与格式**                                               |                                      |
| `bool acceptRichText() const`                                | 返回是否接受富文本格式。             |
| `Qt::Alignment alignment() const`                            | 获取当前文本的对齐方式。             |
| `QString anchorAt(const QPoint &pos) const`                  | 返回指定位置的锚点。                 |
| `QTextEdit::AutoFormatting autoFormatting() const`           | 获取自动格式化选项。                 |
| `void setHtml(const QString &text)`                          | 设置编辑器内容为 HTML 格式。         |
| `void setPlainText(const QString &text)`                     | 设置编辑器内容为纯文本格式。         |
| `QString toHtml() const`                                     | 返回编辑器内容的 HTML 表示。         |
| `QString toPlainText() const`                                | 返回编辑器内容的纯文本表示。         |
| **光标与选择**                                               |                                      |
| `QTextCursor cursorForPosition(const QPoint &pos) const`     | 返回指定位置的光标。                 |
| `QRect cursorRect() const`                                   | 返回光标的矩形区域。                 |
| `QTextCursor textCursor() const`                             | 获取当前的文本光标对象。             |
| `void ensureCursorVisible()`                                 | 确保光标在视口内可见。               |
| **复制、剪切与粘贴**                                         |                                      |
| `bool canPaste() const`                                      | 检查是否可以粘贴文本。               |
| `void copy()`                                                | 复制选中文本到剪贴板。               |
| `void cut()`                                                 | 剪切选中文本到剪贴板。               |
| `void paste()`                                               | 从剪贴板粘贴文本。                   |
| `void selectAll()`                                           | 选择所有文本。                       |
| **撤销与重做**                                               |                                      |
| `bool isUndoRedoEnabled() const`                             | 检查撤销/重做功能是否启用。          |
| `void undo()`                                                | 撤销上一个操作。                     |
| `void redo()`                                                | 重做上一个操作。                     |
| **信号**                                                     |                                      |
| `void copyAvailable(bool yes)`                               | 当复制功能可用时发出信号。           |
| `void currentCharFormatChanged(const QTextCharFormat &f)`    | 当前字符格式发生变化时发出信号。     |
| `void cursorPositionChanged()`                               | 光标位置改变时发出信号。             |
| `void textChanged()`                                         | 文本内容改变时发出信号。             |
| **保护函数**                                                 |                                      |
| `virtual bool canInsertFromMimeData(const QMimeData *source) const` | 检查是否可以从 MIME 数据插入内容。   |
| `virtual void insertFromMimeData(const QMimeData *source)`   | 从 MIME 数据插入内容。               |

## QTextBrowser

### `QTextBrowser` 类概述

​	`QTextBrowser` 类扩展了 `QTextEdit`（以只读模式），增加了一些导航功能，使用户能够在超文本文档中跟随链接。如果您希望提供用户可编辑的富文本编辑器，请使用 `QTextEdit`；如果您想要一个没有超文本导航的文本浏览器，则使用 `QTextEdit` 并调用 `QTextEdit::setReadOnly()` 来禁用编辑。如果您只需要显示一小段富文本，请使用 `QLabel`。文档内容通过 `setHtml()` 或 `setPlainText()` 方法设置，但 `QTextBrowser` 还实现了 `setSource()` 函数，可以将命名文档用作源文本。文档名称将在搜索路径列表和当前文档工厂的目录中查找。如果文档名称以锚点结尾（例如 `#anchor`），文本浏览器会自动滚动到该位置（使用 `scrollToAnchor()`）。当用户点击超链接时，浏览器会使用链接的 href 值自动调用 `setSource()`。您可以通过连接到 `sourceChanged()` 信号来跟踪当前源。`QTextBrowser` 提供 `backward()` 和 `forward()` 槽，用于实现“后退”和“前进”按钮。`home()` 槽将文本设置为最初显示的文档。用户点击锚点时会发出 `anchorClicked()` 信号。要重写浏览器的默认导航行为，可以在连接到此信号的槽中调用 `setSource()` 函数，以提供新的文档文本。如果要加载存储在 Qt 资源系统中的文档，请在 URL 中使用 `qrc` 作为方案。例如，对于文档资源路径 `:/docs/index.html`，使用 `qrc:/docs/index.html` 作为 URL 调用 `setSource()`。

| **方法/信号**                                                | **描述**                             |
| ------------------------------------------------------------ | ------------------------------------ |
| **构造函数**                                                 |                                      |
| `QTextBrowser(QWidget *parent = nullptr)`                    | 创建一个文本浏览器，指定父级小部件。 |
| **历史记录管理**                                             |                                      |
| `int backwardHistoryCount() const`                           | 返回可以向后导航的历史记录数量。     |
| `int forwardHistoryCount() const`                            | 返回可以向前导航的历史记录数量。     |
| `void clearHistory()`                                        | 清空历史记录。                       |
| `QString historyTitle(int i) const`                          | 返回历史记录中第 i 个条目的标题。    |
| `QUrl historyUrl(int i) const`                               | 返回历史记录中第 i 个条目的 URL。    |
| `bool isBackwardAvailable() const`                           | 检查是否可以向后导航。               |
| `bool isForwardAvailable() const`                            | 检查是否可以向前导航。               |
| **链接处理**                                                 |                                      |
| `bool openExternalLinks() const`                             | 检查是否打开外部链接。               |
| `bool openLinks() const`                                     | 检查是否打开链接。                   |
| `void setOpenExternalLinks(bool open)`                       | 设置是否打开外部链接。               |
| `void setOpenLinks(bool open)`                               | 设置是否打开链接。                   |
| **文档源管理**                                               |                                      |
| `void setSearchPaths(const QStringList &paths)`              | 设置搜索路径。                       |
| `QUrl source() const`                                        | 返回当前文档的源 URL。               |
| `QTextDocument::ResourceType sourceType() const`             | 返回文档源的类型。                   |
| **导航功能**                                                 |                                      |
| `virtual void backward()`                                    | 向后导航到上一个文档。               |
| `virtual void forward()`                                     | 向前导航到下一个文档。               |
| `virtual void home()`                                        | 返回到第一个显示的文档。             |
| `virtual void reload()`                                      | 重新加载当前文档。                   |
| `void setSource(const QUrl &url, QTextDocument::ResourceType type = QTextDocument::UnknownResource)` | 设置文档的源。                       |
| **信号**                                                     |                                      |
| `void anchorClicked(const QUrl &link)`                       | 当用户点击锚点时发出信号。           |
| `void backwardAvailable(bool available)`                     | 向后导航可用性变化时发出信号。       |
| `void forwardAvailable(bool available)`                      | 向前导航可用性变化时发出信号。       |
| `void highlighted(const QUrl &link)`                         | 高亮显示链接时发出信号。             |
| `void historyChanged()`                                      | 历史记录变化时发出信号。             |
| `void sourceChanged(const QUrl &src)`                        | 文档源变化时发出信号。               |
| **受保护函数**                                               |                                      |
| `virtual void doSetSource(const QUrl &url, QTextDocument::ResourceType type = QTextDocument::UnknownResource)` | 设置文档源的内部实现。               |
| **重载函数**                                                 |                                      |
| `virtual bool event(QEvent *e) override`                     | 事件处理函数的重载。                 |
| `virtual bool focusNextPrevChild(bool next) override`        | 处理子控件的焦点切换。               |
| `virtual void focusOutEvent(QFocusEvent *ev) override`       | 处理失去焦点事件。                   |
| `virtual void keyPressEvent(QKeyEvent *ev) override`         | 处理按键事件。                       |
| `virtual void mouseMoveEvent(QMouseEvent *e) override`       | 处理鼠标移动事件。                   |
| `virtual void mousePressEvent(QMouseEvent *e) override`      | 处理鼠标按下事件。                   |
| `virtual void mouseReleaseEvent(QMouseEvent *e) override`    | 处理鼠标释放事件。                   |
| `virtual void paintEvent(QPaintEvent *e) override`           | 处理绘制事件。                       |



