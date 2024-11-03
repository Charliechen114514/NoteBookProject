# Qt 一些常见的部件类（II）

## QListWidget

​	`QListWidget` 是一个便利类，提供了类似于 `QListView` 的列表视图，但采用经典的基于项的接口来添加和移除项。`QListWidget` 使用内部模型来管理列表中的每个 `QListWidgetItem`。列表控件的构造方式与其他控件相同：

```
QListWidget *listWidget = new QListWidget(this);
```

​	列表控件的选择模式决定了可以同时选择列表中的多少项，以及是否可以创建复杂的选择。这可以通过 `setSelectionMode()` 函数设置。有两种方法可以将项添加到列表中：它们可以在构造时指定列表控件作为父级控件，或者可以在没有父级控件的情况下构造并稍后添加到列表中。如果在构造项时已经存在列表控件，第一种方法更容易使用：

```
new QListWidgetItem(tr("Oak"), listWidget);
new QListWidgetItem(tr("Fir"), listWidget);
new QListWidgetItem(tr("Pine"), listWidget);
```

​	如果需要在特定位置插入新项，则应在没有父级控件的情况下构造该项。然后应使用 `insertItem()` 函数将其放置在列表中。列表控件将拥有该项。

```
QListWidgetItem *newItem = new QListWidgetItem;
newItem->setText(itemText);
listWidget->insertItem(row, newItem);
```

​	对于多个项，可以使用 `insertItems()`。可以使用 `count()` 函数找到列表中的项数。要从列表中移除项，请使用 `takeItem()`。可以使用 `currentItem()` 查找列表中的当前项，并通过 `setCurrentItem()` 更改当前项。用户还可以通过键盘导航或点击不同的项来更改当前项。当当前项变化时，会发出 `currentItemChanged()` 信号，带有新的当前项和之前的当前项



### API 

| 函数签名                                                     | 用途说明                                             |
| ------------------------------------------------------------ | ---------------------------------------------------- |
| `QListWidget(QWidget *parent = nullptr)`                     | 构造函数，创建一个 `QListWidget`，可以指定父级窗口。 |
| `virtual ~QListWidget()`                                     | 析构函数，释放 `QListWidget` 使用的资源。            |
| `void addItem(QListWidgetItem *item)`                        | 添加一个 `QListWidgetItem` 对象到列表中。            |
| `void addItem(const QString &label)`                         | 使用字符串标签添加一个新项。                         |
| `void addItems(const QStringList &labels)`                   | 批量添加多个项，使用字符串列表。                     |
| `void closePersistentEditor(QListWidgetItem *item)`          | 关闭指定项的持久编辑器。                             |
| `int count() const`                                          | 返回列表中项的数量。                                 |
| `QListWidgetItem *currentItem() const`                       | 获取当前选中的项。                                   |
| `int currentRow() const`                                     | 获取当前选中项的行号。                               |
| `void editItem(QListWidgetItem *item)`                       | 进入指定项的编辑模式。                               |
| `QList<QListWidgetItem *> findItems(const QString &text, Qt::MatchFlags flags) const` | 根据文本查找项，返回匹配的项列表。                   |
| `QModelIndex indexFromItem(const QListWidgetItem *item) const` | 从项获取其对应的模型索引。                           |
| `void insertItem(int row, QListWidgetItem *item)`            | 在指定行插入 `QListWidgetItem` 对象。                |
| `void insertItem(int row, const QString &label)`             | 在指定行插入一个新项，使用字符串标签。               |
| `void insertItems(int row, const QStringList &labels)`       | 在指定行批量插入多个项。                             |
| `bool isPersistentEditorOpen(QListWidgetItem *item) const`   | 检查指定项的持久编辑器是否打开。                     |
| `bool isSortingEnabled() const`                              | 检查列表是否启用排序。                               |
| `QListWidgetItem *item(int row) const`                       | 获取指定行的项。                                     |
| `QListWidgetItem *itemAt(const QPoint &p) const`             | 根据点位置获取对应的项。                             |
| `QListWidgetItem *itemAt(int x, int y) const`                | 根据坐标获取对应的项。                               |
| `QListWidgetItem *itemFromIndex(const QModelIndex &index) const` | 根据模型索引获取对应的项。                           |
| `QWidget *itemWidget(QListWidgetItem *item) const`           | 获取指定项关联的自定义小部件。                       |
| `QList<QListWidgetItem *> items(const QMimeData *data) const` | 从 `QMimeData` 中提取项。                            |
| `void openPersistentEditor(QListWidgetItem *item)`           | 打开指定项的持久编辑器。                             |
| `void removeItemWidget(QListWidgetItem *item)`               | 移除指定项关联的自定义小部件。                       |
| `int row(const QListWidgetItem *item) const`                 | 获取指定项的行号。                                   |
| `QList<QListWidgetItem *> selectedItems() const`             | 获取当前选中的所有项。                               |
| `void setCurrentItem(QListWidgetItem *item)`                 | 设置当前选中的项。                                   |
| `void setCurrentItem(QListWidgetItem *item, QItemSelectionModel::SelectionFlags command)` | 设置当前选中项，带选择标志。                         |
| `void setCurrentRow(int row, QItemSelectionModel::SelectionFlags command)` | 设置当前行，带选择标志。                             |
| `void setCurrentRow(int row)`                                | 设置当前行。                                         |
| `void setItemWidget(QListWidgetItem *item, QWidget *widget)` | 为指定项设置一个自定义小部件。                       |
| `void setSortingEnabled(bool enable)`                        | 启用或禁用列表排序功能。                             |
| `void sortItems(Qt::SortOrder order = Qt::AscendingOrder)`   | 根据指定顺序排序列表项。                             |
| `QListWidgetItem *takeItem(int row)`                         | 移除并返回指定行的项。                               |
| `QRect visualItemRect(const QListWidgetItem *item) const`    | 获取指定项的可视矩形区域。                           |
| `virtual void setSelectionModel(QItemSelectionModel *selectionModel) override` | 设置选择模型。                                       |
| `void clear()`                                               | 清空列表中的所有项。                                 |
| `void scrollToItem(const QListWidgetItem *item, QAbstractItemView::ScrollHint hint = EnsureVisible)` | 滚动到指定项。                                       |



| 信号签名                                                     | 触发条件                     |
| ------------------------------------------------------------ | ---------------------------- |
| `void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)` | 当前项变化时触发。           |
| `void currentRowChanged(int currentRow)`                     | 当前行变化时触发。           |
| `void currentTextChanged(const QString &currentText)`        | 当前文本变化时触发。         |
| `void itemActivated(QListWidgetItem *item)`                  | 项被激活时触发。             |
| `void itemChanged(QListWidgetItem *item)`                    | 项状态变化时触发。           |
| `void itemClicked(QListWidgetItem *item)`                    | 项被点击时触发。             |
| `void itemDoubleClicked(QListWidgetItem *item)`              | 项被双击时触发。             |
| `void itemEntered(QListWidgetItem *item)`                    | 项进入时触发（如鼠标悬停）。 |
| `void itemPressed(QListWidgetItem *item)`                    | 项被按下时触发。             |
| `void itemSelectionChanged()`                                | 选中项变化时触发。           |

| 函数签名                                                     | 用途说明                   |
| ------------------------------------------------------------ | -------------------------- |
| `virtual bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action)` | 处理拖放数据。             |
| `virtual QMimeData *mimeData(const QList<QListWidgetItem *> &items) const` | 生成项的 MIME 数据。       |
| `virtual QStringList mimeTypes() const`                      | 返回支持的 MIME 类型列表。 |
| `virtual Qt::DropActions supportedDropActions() const`       | 返回支持的拖放操作。       |
| `virtual void dropEvent(QDropEvent *event) override`         | 处理拖放事件。             |
| `virtual bool event(QEvent *e) override`                     | 处理其他事件。             |

## QTableWidget

​	表格小部件为应用程序提供标准的表格显示功能。`QTableWidget` 中的项由 `QTableWidgetItem` 提供。如果你希望使用自定义数据模型的表格，应使用 `QTableView` 而不是这个类。表格小部件可以通过指定所需的行数和列数进行构造：

```
tableWidget = new QTableWidget(12, 3, this);
```

​	另外，表格也可以在没有指定大小的情况下构造，并在之后调整大小：

```
tableWidget = new QTableWidget(this);
tableWidget->setRowCount(10);
tableWidget->setColumnCount(5);
```

​	项是在表格外部创建的（没有父级小部件），然后通过 `setItem()` 插入表格中：

```
QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row + 1) * (column + 1)));
tableWidget->setItem(row, column, newItem);
```

​	如果想要在表格小部件中启用排序，请在填充项之后进行，否则排序可能会干扰插入顺序（详见 `setItem()` 的说明）。表格可以有水平和垂直的表头。创建表头的最简单方法是向 `setHorizontalHeaderLabels()` 和 `setVerticalHeaderLabels()` 函数提供字符串列表。这将为表格的列和行提供简单的文本表头。更复杂的表头可以通过现有的表格项来创建，通常这些项是在表格外部构造的。例如，我们可以构造一个带有图标和对齐文本的表格项，并将其用作特定列的表头：

```
QTableWidgetItem *cubesHeaderItem = new QTableWidgetItem(tr("Cubes"));
cubesHeaderItem->setIcon(QIcon(QPixmap(":/Images/cubed.png")));
cubesHeaderItem->setTextAlignment(Qt::AlignVCenter);
```

​	可以通过 `rowCount()` 获取表格的行数，通过 `columnCount()` 获取列数。表格可以通过 `clear()` 函数进行清空。

### API

| 函数签名                                                     | 用途说明                                              |
| ------------------------------------------------------------ | ----------------------------------------------------- |
| `QTableWidget(QWidget *parent = nullptr)`                    | 构造函数，创建一个 `QTableWidget`，可以指定父级窗口。 |
| `QTableWidget(int rows, int columns, QWidget *parent = nullptr)` | 构造函数，创建一个指定行数和列数的 `QTableWidget`。   |
| `virtual ~QTableWidget()`                                    | 析构函数，释放 `QTableWidget` 使用的资源。            |
| `QWidget *cellWidget(int row, int column) const`             | 获取指定单元格的自定义小部件。                        |
| `void closePersistentEditor(QTableWidgetItem *item)`         | 关闭指定项的持久编辑器。                              |
| `int column(const QTableWidgetItem *item) const`             | 获取指定项所在的列号。                                |
| `int columnCount() const`                                    | 返回表格的列数。                                      |
| `int currentColumn() const`                                  | 获取当前单元格的列号。                                |
| `QTableWidgetItem *currentItem() const`                      | 获取当前单元格的项。                                  |
| `int currentRow() const`                                     | 获取当前单元格的行号。                                |
| `void editItem(QTableWidgetItem *item)`                      | 进入指定项的编辑模式。                                |
| `QList<QTableWidgetItem *> findItems(const QString &text, Qt::MatchFlags flags) const` | 根据文本查找项，返回匹配的项列表。                    |
| `QTableWidgetItem *horizontalHeaderItem(int column) const`   | 获取指定列的水平表头项。                              |
| `QModelIndex indexFromItem(const QTableWidgetItem *item) const` | 从项获取其对应的模型索引。                            |
| `bool isPersistentEditorOpen(QTableWidgetItem *item) const`  | 检查指定项的持久编辑器是否打开。                      |
| `QTableWidgetItem *item(int row, int column) const`          | 获取指定行列的项。                                    |
| `QTableWidgetItem *itemAt(const QPoint &point) const`        | 根据点位置获取对应的项。                              |
| `QTableWidgetItem *itemAt(int ax, int ay) const`             | 根据坐标获取对应的项。                                |
| `QTableWidgetItem *itemFromIndex(const QModelIndex &index) const` | 根据模型索引获取对应的项。                            |
| `const QTableWidgetItem *itemPrototype() const`              | 获取项的原型。                                        |
| `QList<QTableWidgetItem *> items(const QMimeData *data) const` | 从 `QMimeData` 中提取项。                             |
| `void openPersistentEditor(QTableWidgetItem *item)`          | 打开指定项的持久编辑器。                              |
| `void removeCellWidget(int row, int column)`                 | 移除指定单元格关联的自定义小部件。                    |
| `int row(const QTableWidgetItem *item) const`                | 获取指定项的行号。                                    |
| `int rowCount() const`                                       | 返回表格的行数。                                      |
| `QList<QTableWidgetItem *> selectedItems() const`            | 获取当前选中的所有项。                                |
| `QList<QTableWidgetSelectionRange> selectedRanges() const`   | 获取当前选中范围的列表。                              |
| `void setCellWidget(int row, int column, QWidget *widget)`   | 为指定单元格设置一个自定义小部件。                    |
| `void setColumnCount(int columns)`                           | 设置表格的列数。                                      |
| `void setCurrentCell(int row, int column)`                   | 设置当前单元格。                                      |
| `void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command)` | 设置当前单元格，带选择标志。                          |
| `void setCurrentItem(QTableWidgetItem *item)`                | 设置当前单元格的项。                                  |
| `void setCurrentItem(QTableWidgetItem *item, QItemSelectionModel::SelectionFlags command)` | 设置当前项，带选择标志。                              |
| `void setHorizontalHeaderItem(int column, QTableWidgetItem *item)` | 设置指定列的水平表头项。                              |
| `void setHorizontalHeaderLabels(const QStringList &labels)`  | 设置水平表头的标签。                                  |
| `void setItem(int row, int column, QTableWidgetItem *item)`  | 设置指定单元格的项。                                  |
| `void setItemPrototype(const QTableWidgetItem *item)`        | 设置项的原型。                                        |
| `void setRangeSelected(const QTableWidgetSelectionRange &range, bool select)` | 设置选中范围。                                        |
| `void setRowCount(int rows)`                                 | 设置表格的行数。                                      |
| `void setVerticalHeaderItem(int row, QTableWidgetItem *item)` | 设置指定行的垂直表头项。                              |
| `void setVerticalHeaderLabels(const QStringList &labels)`    | 设置垂直表头的标签。                                  |
| `void sortItems(int column, Qt::SortOrder order = Qt::AscendingOrder)` | 根据指定列排序表格项。                                |
| `QTableWidgetItem *takeHorizontalHeaderItem(int column)`     | 移除并返回指定列的水平表头项。                        |
| `QTableWidgetItem *takeItem(int row, int column)`            | 移除并返回指定行列的项。                              |
| `QTableWidgetItem *takeVerticalHeaderItem(int row)`          | 移除并返回指定行的垂直表头项。                        |
| `QTableWidgetItem *verticalHeaderItem(int row) const`        | 获取指定行的垂直表头项。                              |
| `int visualColumn(int logicalColumn) const`                  | 获取逻辑列在视图中的视觉列索引。                      |
| `QRect visualItemRect(const QTableWidgetItem *item) const`   | 获取指定项的可视矩形区域。                            |
| `int visualRow(int logicalRow) const`                        | 获取逻辑行在视图中的视觉行索引。                      |

| 槽函数签名                                                   | 用途说明                                 |
| ------------------------------------------------------------ | ---------------------------------------- |
| `void clear()`                                               | 清空表格中的所有项。                     |
| `void clearContents()`                                       | 清空表格中的所有项内容，但保留行列结构。 |
| `void insertColumn(int column)`                              | 在指定列位置插入新列。                   |
| `void insertRow(int row)`                                    | 在指定行位置插入新行。                   |
| `void removeColumn(int column)`                              | 移除指定列。                             |
| `void removeRow(int row)`                                    | 移除指定行。                             |
| `void scrollToItem(const QTableWidgetItem *item, QAbstractItemView::ScrollHint hint = EnsureVisible)` | 滚动到指定项。                           |

| 信号签名                                                     | 触发条件                     |
| ------------------------------------------------------------ | ---------------------------- |
| `void cellActivated(int row, int column)`                    | 单元格被激活时触发。         |
| `void cellChanged(int row, int column)`                      | 单元格内容变化时触发。       |
| `void cellClicked(int row, int column)`                      | 单元格被点击时触发。         |
| `void cellDoubleClicked(int row, int column)`                | 单元格被双击时触发。         |
| `void cellEntered(int row, int column)`                      | 鼠标进入单元格时触发。       |
| `void cellPressed(int row, int column)`                      | 单元格被按下时触发。         |
| `void currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)` | 当前单元格变化时触发。       |
| `void currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)` | 当前项变化时触发。           |
| `void itemActivated(QTableWidgetItem *item)`                 | 项被激活时触发。             |
| `void itemChanged(QTableWidgetItem *item)`                   | 项状态变化时触发。           |
| `void itemClicked(QTableWidgetItem *item)`                   | 项被点击时触发。             |
| `void itemDoubleClicked(QTableWidgetItem *item)`             | 项被双击时触发。             |
| `void itemEntered(QTableWidgetItem *item)`                   | 项进入时触发（如鼠标悬停）。 |
| `void itemPressed(QTableWidgetItem *item)`                   | 项被按下时触发。             |
| `void itemSelectionChanged()`                                | 选中项变化时触发。           |

| 函数签名                                                     | 用途说明                   |
| ------------------------------------------------------------ | -------------------------- |
| `virtual bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)` | 处理拖放操作。             |
| `virtual QMimeData *mimeData(const QList<QTableWidgetItem *> &items) const` | 创建可放置项的数据。       |
| `virtual QStringList mimeTypes() const`                      | 返回支持的 MIME 类型列表。 |
| `virtual Qt::DropActions supportedDropActions() const`       | 返回支持的拖放操作类型。   |

| 函数签名                                             | 用途说明       |
| ---------------------------------------------------- | -------------- |
| `virtual void dropEvent(QDropEvent *event) override` | 处理拖放事件。 |
| `virtual bool event(QEvent *e) override`             | 处理其他事件。 |

## QTreeWidget

​	`QTreeWidget` 类是一个方便的类，提供了一个标准的树形小部件，其经典的基于项目的接口类似于 Qt 3 中的 `QListView` 类。该类基于 Qt 的模型/视图架构，使用默认模型来保存项目，每个项目都是一个 `QTreeWidgetItem`。开发者如果不需要模型/视图框架的灵活性，可以使用这个类非常简单地创建层次结构列表。更灵活的方法是将 `QTreeView` 与标准项目模型结合使用，这样可以将数据的存储与其表示分开。

最简单的树形小部件可以通过以下方式构造：

```
QTreeWidget *treeWidget = new QTreeWidget();
treeWidget->setColumnCount(1);
QList<QTreeWidgetItem *> items;
for (int i = 0; i < 10; ++i)
    items.append(new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("item: %1").arg(i))));
treeWidget->insertTopLevelItems(0, items);
```

在将项目添加到树形小部件之前，必须使用 `setColumnCount()` 设置列数。这允许每个项目具有一个或多个标签或其他装饰。可以通过 `columnCount()` 函数获取当前使用的列数。

树形小部件可以有一个头部，为每一列提供一个部分。最简单的方法是通过 `setHeaderLabels()` 提供一个字符串列表来设置每个部分的标签，但也可以使用 `QTreeWidgetItem` 构造自定义头部，并通过 `setHeaderItem()` 函数插入到树中。

树中的项目可以根据预定义的排序顺序按列进行排序。如果启用了排序，用户可以通过点击列标题来对项目进行排序。排序可以通过调用 `setSortingEnabled()` 来启用或禁用。使用 `isSortingEnabled()` 函数可以检查排序是否启用。

### API

| 函数签名                                 | 用途说明                                   |
| ---------------------------------------- | ------------------------------------------ |
| `QTreeWidget(QWidget *parent = nullptr)` | 构造一个树形小部件，可选择指定父级小部件。 |
| `virtual ~QTreeWidget()`                 | 析构函数，释放资源。                       |

| 函数签名                                                     | 用途说明                       |
| ------------------------------------------------------------ | ------------------------------ |
| `void addTopLevelItem(QTreeWidgetItem *item)`                | 添加顶级项目。                 |
| `void addTopLevelItems(const QList<QTreeWidgetItem *> &items)` | 添加多个顶级项目。             |
| `void closePersistentEditor(QTreeWidgetItem *item, int column = 0)` | 关闭持久编辑器。               |
| `int columnCount() const`                                    | 获取列数。                     |
| `int currentColumn() const`                                  | 获取当前列。                   |
| `QTreeWidgetItem *currentItem() const`                       | 获取当前项目。                 |
| `void editItem(QTreeWidgetItem *item, int column = 0)`       | 编辑指定项目。                 |
| `QList<QTreeWidgetItem *> findItems(const QString &text, Qt::MatchFlags flags, int column = 0) const` | 查找匹配的项目。               |
| `QTreeWidgetItem *headerItem() const`                        | 获取头部项目。                 |
| `QModelIndex indexFromItem(const QTreeWidgetItem *item, int column = 0) const` | 从项目获取模型索引。           |
| `int indexOfTopLevelItem(QTreeWidgetItem *item) const`       | 获取顶级项目的索引。           |
| `void insertTopLevelItem(int index, QTreeWidgetItem *item)`  | 在指定位置插入顶级项目。       |
| `void insertTopLevelItems(int index, const QList<QTreeWidgetItem *> &items)` | 在指定位置插入多个顶级项目。   |
| `QTreeWidgetItem *invisibleRootItem() const`                 | 获取不可见的根项目。           |
| `bool isPersistentEditorOpen(QTreeWidgetItem *item, int column = 0) const` | 判断持久编辑器是否打开。       |
| `QTreeWidgetItem *itemAbove(const QTreeWidgetItem *item) const` | 获取指定项目上方的项目。       |
| `QTreeWidgetItem *itemAt(const QPoint &p) const`             | 获取指定位置的项目。           |
| `QTreeWidgetItem *itemAt(int x, int y) const`                | 获取指定坐标的项目。           |
| `QTreeWidgetItem *itemBelow(const QTreeWidgetItem *item) const` | 获取指定项目下方的项目。       |
| `QTreeWidgetItem *itemFromIndex(const QModelIndex &index) const` | 从模型索引获取项目。           |
| `QWidget *itemWidget(QTreeWidgetItem *item, int column) const` | 获取项目的自定义小部件。       |
| `void openPersistentEditor(QTreeWidgetItem *item, int column = 0)` | 打开持久编辑器。               |
| `void removeItemWidget(QTreeWidgetItem *item, int column)`   | 移除项目的小部件。             |
| `QList<QTreeWidgetItem *> selectedItems() const`             | 获取所选项目列表。             |
| `void setColumnCount(int columns)`                           | 设置列数。                     |
| `void setCurrentItem(QTreeWidgetItem *item)`                 | 设置当前项目。                 |
| `void setCurrentItem(QTreeWidgetItem *item, int column)`     | 设置当前项目及其列。           |
| `void setCurrentItem(QTreeWidgetItem *item, int column, QItemSelectionModel::SelectionFlags command)` | 设置当前项目及其列和选择标志。 |
| `void setHeaderItem(QTreeWidgetItem *item)`                  | 设置头部项目。                 |
| `void setHeaderLabel(const QString &label)`                  | 设置单个头部标签。             |
| `void setHeaderLabels(const QStringList &labels)`            | 设置多个头部标签。             |
| `void setItemWidget(QTreeWidgetItem *item, int column, QWidget *widget)` | 为项目设置自定义小部件。       |
| `int sortColumn() const`                                     | 获取当前排序列。               |
| `void sortItems(int column, Qt::SortOrder order)`            | 按指定列排序。                 |
| `QTreeWidgetItem *takeTopLevelItem(int index)`               | 移除并返回指定索引的顶级项目。 |
| `QTreeWidgetItem *topLevelItem(int index) const`             | 获取指定索引的顶级项目。       |
| `int topLevelItemCount() const`                              | 获取顶级项目的数量。           |
| `QRect visualItemRect(const QTreeWidgetItem *item) const`    | 获取项目的可视区域。           |

| 函数签名                                                     | 用途说明       |
| ------------------------------------------------------------ | -------------- |
| `virtual void setSelectionModel(QItemSelectionModel *selectionModel) override` | 设置选择模型。 |

| 函数签名                                                     | 用途说明                   |
| ------------------------------------------------------------ | -------------------------- |
| `void clear()`                                               | 清空树形小部件的所有项目。 |
| `void collapseItem(const QTreeWidgetItem *item)`             | 折叠指定项目。             |
| `void expandItem(const QTreeWidgetItem *item)`               | 展开指定项目。             |
| `void scrollToItem(const QTreeWidgetItem *item, QAbstractItemView::ScrollHint hint = EnsureVisible)` | 滚动到指定项目。           |

| 函数签名                                                     | 用途说明           |
| ------------------------------------------------------------ | ------------------ |
| `void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)` | 当前项目改变信号。 |
| `void itemActivated(QTreeWidgetItem *item, int column)`      | 项目激活信号。     |
| `void itemChanged(QTreeWidgetItem *item, int column)`        | 项目变化信号。     |
| `void itemClicked(QTreeWidgetItem *item, int column)`        | 项目点击信号。     |
| `void itemCollapsed(QTreeWidgetItem *item)`                  | 项目折叠信号。     |
| `void itemDoubleClicked(QTreeWidgetItem *item, int column)`  | 项目双击信号。     |
| `void itemEntered(QTreeWidgetItem *item, int column)`        | 项目进入信号。     |
| `void itemExpanded(QTreeWidgetItem *item)`                   | 项目展开信号。     |
| `void itemPressed(QTreeWidgetItem *item, int column)`        | 项目按下信号。     |
| `void itemSelectionChanged()`                                | 项目选择变化信号。 |

| 函数签名                                                     | 用途说明                   |
| ------------------------------------------------------------ | -------------------------- |
| `virtual bool dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action)` | 处理拖放数据。             |
| `virtual QMimeData *mimeData(const QList<QTreeWidgetItem *> &items) const` | 创建可放置项的数据。       |
| `virtual QStringList mimeTypes() const`                      | 返回支持的 MIME 类型列表。 |
| `virtual Qt::DropActions supportedDropActions() const`       | 返回支持的拖放操作类型。   |

| 函数签名                                             | 用途说明       |
| ---------------------------------------------------- | -------------- |
| `virtual void dropEvent(QDropEvent *event) override` | 处理拖放事件。 |
| `virtual bool event(QEvent *e) override`             | 处理其他事件。 |