# Qt对话框与界面设计——常见的对话框

​	我们下面来仔细了解一下常见的特殊对话框

#### **QMessageBox** - 提供不同类型的消息对话框

`QMessageBox` 用于显示各种类型的消息框，例如信息框、警告框、错误框等。

| 静态函数        | 功能描述                                                     |
| --------------- | ------------------------------------------------------------ |
| `information()` | 显示一个信息框，通常用于提供非重要的消息。返回用户点击的按钮。 |
| `warning()`     | 显示一个警告框，通常用于警告用户可能发生的错误或潜在风险。   |
| `critical()`    | 显示一个错误框，通常用于提示严重错误或需要立即处理的情况。   |
| `question()`    | 显示一个提问框，通常用于询问用户是否继续某个操作（如“是否保存”）。返回用户点击的按钮。 |
| `about()`       | 显示一个关于框，通常用于显示应用程序或库的版本、版权信息等。 |
| `aboutQt()`     | 显示Qt库的关于框，通常用于显示Qt的版本信息及版权声明。       |

#### **QFileDialog** - 文件选择对话框

`QFileDialog` 用于显示文件或目录选择对话框，支持打开、保存文件以及选择目录。

| 静态函数                 | 功能描述                                                     |
| ------------------------ | ------------------------------------------------------------ |
| `getOpenFileName()`      | 显示一个文件打开对话框，允许用户选择一个文件。返回用户选择的文件路径。 |
| `getSaveFileName()`      | 显示一个文件保存对话框，允许用户选择一个文件路径以保存文件。返回用户选择的文件路径。 |
| `getOpenFileNames()`     | 显示一个文件选择对话框，允许用户选择多个文件。返回一个字符串列表，包含用户选择的多个文件路径。 |
| `getExistingDirectory()` | 显示一个目录选择对话框，允许用户选择一个现有目录。返回用户选择的目录路径。 |
| `setFileMode()`          | 设置对话框的文件选择模式（单文件、多文件、目录等）。         |
| `setNameFilter()`        | 设置文件过滤器，指定用户可选择的文件类型（如`.txt`, `.png`等）。 |
| `setViewMode()`          | 设置对话框的视图模式（如列表视图或图标视图）。               |

#### **QColorDialog** - 颜色选择对话框

`QColorDialog` 提供了一个颜色选择对话框，允许用户选择颜色。

| 静态函数            | 功能描述                                                     |
| ------------------- | ------------------------------------------------------------ |
| `getColor()`        | 显示颜色选择对话框，允许用户选择一个颜色。返回用户选择的颜色对象。如果用户取消选择，返回一个无效颜色。 |
| `setCurrentColor()` | 设置对话框的当前颜色（在对话框中显示的初始颜色）。           |

#### **QFontDialog** - 字体选择对话框

`QFontDialog` 提供了一个字体选择对话框，允许用户选择字体、样式和大小。

| 静态函数           | 功能描述                                                     |
| ------------------ | ------------------------------------------------------------ |
| `getFont()`        | 显示字体选择对话框，允许用户选择字体、样式、大小等。返回用户选择的字体对象。如果用户取消选择，返回一个无效字体。 |
| `setCurrentFont()` | 设置对话框的当前字体（即初始显示的字体）。                   |

#### **QInputDialog** - 输入对话框

`QInputDialog` 用于显示简单的输入对话框，支持文本、整数、浮动数值、列表项等输入。

| 静态函数      | 功能描述                                                     |
| ------------- | ------------------------------------------------------------ |
| `getText()`   | 显示一个文本输入对话框，允许用户输入一行文本。返回用户输入的文本。如果用户取消，返回空字符串。 |
| `getInt()`    | 显示一个整数输入对话框，允许用户输入一个整数值。返回用户输入的整数。如果用户取消，返回默认值。 |
| `getDouble()` | 显示一个双精度浮动数输入对话框，允许用户输入一个浮动小数值。返回用户输入的浮动值。如果用户取消，返回默认值。 |
| `getItem()`   | 显示一个项目选择对话框，允许用户从一个项目列表中选择一项。返回用户选择的项目及其索引。如果用户取消，返回空字符串。 |

#### **QPrintDialog** - 打印机选择对话框

`QPrintDialog` 用于显示打印机选择对话框，允许用户选择打印机及设置打印选项。

| 静态函数       | 功能描述                                                     |
| -------------- | ------------------------------------------------------------ |
| `getPrinter()` | 显示打印机选择对话框，允许用户选择一个打印机。返回用户选择的打印机对象。 |

#### **QProgressDialog** - 进度对话框

`QProgressDialog` 用于显示一个进度条对话框，显示任务的执行进度。

| 静态函数         | 功能描述                                                     |
| ---------------- | ------------------------------------------------------------ |
| `show()`         | 显示进度对话框。可以设置进度条的范围、当前进度、标题等。     |
| `setLabelText()` | 设置进度对话框的标签文本，通常用于显示当前正在执行的操作或任务名称。 |
| `setRange()`     | 设置进度条的范围（最小值和最大值）。                         |

#### **QMessageBox** - 异常类型提示

| 静态函数    | 功能描述                                                   |
| ----------- | ---------------------------------------------------------- |
| `about()`   | 显示一个简单的关于对话框，包含一些应用程序或库的基本信息。 |
| `aboutQt()` | 显示关于Qt库的对话框，包含Qt的版本和版权信息。             |

## QFileDialog

`QFileDialog` 类使用户能够浏览文件系统，选择一个或多个文件，或选择一个目录。

最简单的创建 `QFileDialog` 的方式是使用静态函数，例如 `getOpenFileName()`：

```
cpp复制代码fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
```

​	在上面的例子中，通过静态函数创建了一个模态 `QFileDialog` 对话框。对话框最初显示的是 `/home/jana` 目录的内容，并显示与字符串 `"Image Files (*.png *.jpg *.bmp)"` 匹配的文件类型。文件对话框的父窗口设置为 `this`，并且窗口标题设置为 `"Open Image"`。如果你想使用多个过滤器，可以使用双分号将每个过滤器分开。例如：

```
"Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"
```

​	你也可以在不使用静态函数的情况下创建自定义的 `QFileDialog`。通过调用 `setFileMode()`，你可以指定用户在对话框中必须选择什么：

```
QFileDialog dialog(this);
dialog.setFileMode(QFileDialog::AnyFile);
```

​	在上面的例子中，文件对话框的模式设置为 `AnyFile`，这意味着用户可以选择任何文件，甚至可以指定一个不存在的文件。这个模式适用于创建“另存为”文件对话框。如果用户必须选择一个已经存在的文件，可以使用 `ExistingFile`；如果只允许选择目录，可以使用 `Directory`。有关完整的模式列表，请参见 `QFileDialog::FileMode` 枚举。

​	`fileMode` 属性包含了对话框的操作模式，这决定了用户应该选择何种类型的对象。可以使用 `setNameFilter()` 来设置对话框的文件过滤器。例如：

```
dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
```

​	在上面的例子中，过滤器设置为 `"Images (*.png *.xpm *.jpg)"`，这意味着只有扩展名为 `png`、`xpm` 或 `jpg` 的文件会在 `QFileDialog` 中显示。你可以通过使用 `setNameFilters()` 来应用多个过滤器。使用 `selectNameFilter()` 可以选择给定的默认过滤器。

​	文件对话框有两种视图模式：列表视图和详细视图。列表视图将当前目录的内容呈现为文件和目录名称的列表；详细视图也显示文件和目录名称的列表，但在每个名称旁边还会显示其他信息，如文件大小和修改日期。可以通过 `setViewMode()` 来设置视图模式：

```
dialog.setViewMode(QFileDialog::Detail);
```

​	创建自定义文件对话框时，最后一个重要的函数是 `selectedFiles()`。

```
QStringList fileNames;
if (dialog.exec())
    fileNames = dialog.selectedFiles();
```

​	在上面的例子中，创建并显示了一个模态文件对话框。如果用户点击了 OK，选择的文件将被放入 `fileNames` 中。对话框的工作目录可以通过 `setDirectory()` 来设置。每个文件都可以使用 `selectFile()` 函数来选择。

​	默认情况下，如果平台有原生文件对话框，将使用平台原生对话框。在这种情况下，通常用于构造对话框的小部件不会被实例化，因此相关的访问器（如 `layout()` 和 `itemDelegate()`）将返回 `null`。另外，并不是所有平台都会显示带有标题栏的文件对话框，因此标题文本可能对用户不可见。你可以通过设置 `DontUseNativeDialog` 选项，或者设置 `AA_DontUseNativeDialogs` 应用程序属性，确保使用基于小部件的实现，而不是原生对话框。



## QColorDialog

​	颜色对话框的功能是允许用户选择颜色。例如，在绘图程序中，用户可以通过此对话框设置画笔颜色。静态函数提供了模态颜色对话框。

​	`getColor()` 静态函数显示颜色对话框，允许用户指定颜色。此函数也可以让用户选择带有透明度的颜色：通过传递 `ShowAlphaChannel` 选项作为附加参数。

​	用户可以存储最多 `customCount()` 个自定义颜色。自定义颜色在所有颜色对话框之间共享，并且在程序执行期间会被记住。可以使用 `setCustomColor()` 来设置自定义颜色，使用 `customColor()` 来获取这些颜色。

​	当按下“拾取屏幕颜色”按钮时，鼠标指针会变为十字形，屏幕上的颜色会被扫描。用户可以通过点击鼠标或按 Enter 键来选择颜色。按下 Escape 键则会恢复进入此模式之前选择的最后一个颜色。

## QFontDialog

​	`QFontDialog` 通过静态的 `getFont()` 函数来创建。

```
bool ok;
QFont font = QFontDialog::getFont(
                &ok, QFont("Helvetica [Cronyx]", 10), this);
if (ok) {
    // the user clicked OK and font is set to the font the user selected
} else {
    // the user canceled the dialog; font is set to the initial
    // value, in this case Helvetica [Cronyx], 10
}
```

​	在这个例子中，`getFont()` 函数返回一个用户选择的字体，并通过 `ok` 参数告知用户是否点击了“OK”。如果用户选择了字体并点击了 OK，那么 `font` 将是用户选定的字体；如果用户点击了 Cancel，那么 `font` 保持原始值（此处为 `Helvetica [Cronyx]`, 10）。

```
myWidget.setFont(QFontDialog::getFont(0, myWidget.font()));
```

​	在这个例子中，`getFont()` 允许你直接设置一个小部件的字体。如果用户点击了 OK，那么选择的字体会应用到 `myWidget`；如果用户点击了 Cancel，则会保持原始的字体设置。

## QProgressDialog

`QProgressDialog` 是用来给用户提供一个操作进度的可视化提示，并显示操作的进度。它通常用于较长时间的操作中，让用户知道操作还在进行，并且防止界面看起来“冻结”。此外，用户还可以通过进度对话框中提供的取消按钮来中止当前操作。

1. **设置最小和最大值**：`setMinimum()` 和 `setMaximum()` 用来设置操作的“步数”。进度条会根据这些值更新。通常可以使用操作的单位来定义步数（如文件个数、字节数等）。
2. **显示进度**：操作执行时，可以通过 `setValue()` 方法更新进度条的当前值。
3. **自动重置和关闭**：当操作完成后，进度条会自动重置并隐藏。可以通过 `setAutoReset()` 和 `setAutoClose()` 来改变这一行为。

#### 进度对话框的两种使用方式：

- **模态进度对话框**：更简单直接。程序员可以在一个循环中执行操作，定期调用 `setValue()` 更新进度，同时使用 `wasCanceled()` 检查用户是否取消了操作。例如：

```
cpp复制代码QProgressDialog progress("Copying files...", "Abort Copy", 0, numFiles, this);
progress.setWindowModality(Qt::WindowModal);

for (int i = 0; i < numFiles; i++) {
    progress.setValue(i);

    if (progress.wasCanceled())
        break;
    // ... copy one file
}
progress.setValue(numFiles);
```

在这种模式下，`QProgressDialog` 会在操作期间阻塞用户交互，直到操作完成或被用户取消。

- **无模态进度对话框**：适用于后台任务，用户可以在任务进行时继续与应用程序进行交互。这类操作通常依赖于定时器（如 `QTimer`）或在后台线程中执行。进度对话框通常也可以在主窗口的状态栏中使用 `QProgressBar` 来替代。无模态进度对话框需要事件循环来运行，并连接 `canceled()` 信号到一个槽来停止操作。例如：

```
cpp复制代码// Operation constructor
Operation::Operation(QObject *parent)
    : QObject(parent), steps(0)
{
    pd = new QProgressDialog("Operation in progress.", "Cancel", 0, 100);
    connect(pd, &QProgressDialog::canceled, this, &Operation::cancel);
    t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &Operation::perform);
    t->start(0);
}

void Operation::perform()
{
    pd->setValue(steps);
    // ... perform one percent of the operation
    steps++;
    if (steps > pd->maximum())
        t->stop();
}

void Operation::cancel()
{
    t->stop();
    // ... cleanup
}
```

这种模式通常适用于后台的长时间操作，允许用户继续与程序交互。

`QProgressDialog` 提供了一些方法来定制对话框的外观和行为，例如：

- `setLabel()`：设置显示在对话框中的标签。
- `setBar()`：设置进度条。
- `setCancelButton()`：设置取消按钮。

可以通过 `setLabelText()` 和 `setCancelButtonText()` 来修改文本内容。为了避免在硬件差异较大的环境中出现不必要的进度对话框显示，`QProgressDialog` 会根据操作所需的时间估算来决定是否显示进度对话框。只有当操作的估计时间超过了 `minimumDuration()`（默认值为 4 秒）时，进度对话框才会显示。



## QInputDialog

`QInputDialog` 提供了五个静态的便利函数，用于获取不同类型的用户输入。它们分别是：`getText()`、`getMultiLineText()`、`getInt()`、`getDouble()` 和 `getItem()`。这些函数的用法类似，允许你通过对话框获取文本、整数、浮动点数或从列表中选择一个项。

例如，使用 `getText()` 函数可以获取一个字符串输入：

```
bool ok;
QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                     tr("User name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
if (ok && !text.isEmpty()) {
    textLabel->setText(text);
}
```

# 补充

## QFileDialog

### **枚举类型 (Enums)**

| 枚举类型        | 枚举值                 | 功能描述         |
| --------------- | ---------------------- | ---------------- |
| **AcceptMode**  | `AcceptOpen`           | 打开文件模式     |
|                 | `AcceptSave`           | 保存文件模式     |
| **DialogLabel** | `LookIn`               | "浏览"标签       |
|                 | `FileName`             | "文件名"标签     |
|                 | `FileType`             | "文件类型"标签   |
|                 | `Accept`               | "接受"标签       |
|                 | `Reject`               | "拒绝"标签       |
| **FileMode**    | `AnyFile`              | 任意文件模式     |
|                 | `ExistingFile`         | 只选择现有文件   |
|                 | `Directory`            | 选择目录         |
|                 | `ExistingFiles`        | 选择多个现有文件 |
| **Option**      | `ShowDirsOnly`         | 只显示目录       |
|                 | `DontResolveSymlinks`  | 不解析符号链接   |
|                 | `DontConfirmOverwrite` | 不确认覆盖操作   |
|                 | `DontUseNativeDialog`  | 不使用原生对话框 |
|                 | `ReadOnly`             | 设置为只读模式   |
| **ViewMode**    | `Detail`               | 详细视图模式     |
|                 | `List`                 | 列表视图模式     |

### **成员函数 (Member Functions)**

| 函数名                                                       | 功能描述                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QFileDialog(QWidget *parent, Qt::WindowFlags flags)`        | 构造函数，创建文件对话框，指定父窗口和窗口标志。             |
| `QFileDialog(QWidget *parent = nullptr, const QString &caption = QString(), const QString &directory = QString(), const QString &filter = QString())` | 构造函数，创建文件对话框，指定父窗口、标题、默认目录和文件过滤器。 |
| `~QFileDialog()`                                             | 析构函数，销毁文件对话框。                                   |
| `acceptMode()`                                               | 获取对话框的接受模式（`AcceptOpen`或`AcceptSave`）。         |
| `defaultSuffix()`                                            | 获取默认文件后缀名。                                         |
| `directory()`                                                | 获取当前目录。                                               |
| `directoryUrl()`                                             | 获取当前目录的URL。                                          |
| `fileMode()`                                                 | 获取文件模式（`AnyFile`, `ExistingFile`, `Directory`, `ExistingFiles`）。 |
| `filter()`                                                   | 获取文件过滤器。                                             |
| `history()`                                                  | 获取文件对话框历史记录。                                     |
| `iconProvider()`                                             | 获取文件图标提供器。                                         |
| `itemDelegate()`                                             | 获取项目委托，用于自定义项目显示。                           |
| `labelText(QFileDialog::DialogLabel label)`                  | 获取指定标签的文本。                                         |
| `mimeTypeFilters()`                                          | 获取MIME类型过滤器。                                         |
| `nameFilters()`                                              | 获取名称过滤器（文件类型过滤器）。                           |
| `open(QObject *receiver, const char *member)`                | 打开对话框，连接信号槽。                                     |
| `options()`                                                  | 获取文件对话框的选项。                                       |
| `proxyModel()`                                               | 获取代理模型。                                               |
| `restoreState(const QByteArray &state)`                      | 恢复文件对话框的状态。                                       |
| `saveState()`                                                | 保存文件对话框的状态。                                       |
| `selectFile(const QString &filename)`                        | 选择一个文件。                                               |
| `selectMimeTypeFilter(const QString &filter)`                | 选择MIME类型过滤器。                                         |
| `selectNameFilter(const QString &filter)`                    | 选择文件名称过滤器。                                         |
| `selectUrl(const QUrl &url)`                                 | 选择一个URL。                                                |
| `selectedFiles()`                                            | 获取选择的文件路径列表。                                     |
| `selectedMimeTypeFilter()`                                   | 获取当前选择的MIME类型过滤器。                               |
| `selectedNameFilter()`                                       | 获取当前选择的名称过滤器。                                   |
| `selectedUrls()`                                             | 获取选择的URL列表。                                          |
| `setAcceptMode(QFileDialog::AcceptMode mode)`                | 设置接受模式（`AcceptOpen`或`AcceptSave`）。                 |
| `setDefaultSuffix(const QString &suffix)`                    | 设置默认文件后缀名。                                         |
| `setDirectory(const QString &directory)`                     | 设置当前目录路径。                                           |
| `setDirectory(const QDir &directory)`                        | 设置当前目录对象。                                           |
| `setDirectoryUrl(const QUrl &directory)`                     | 设置当前目录的URL。                                          |
| `setFileMode(QFileDialog::FileMode mode)`                    | 设置文件模式（如`ExistingFile`, `ExistingFiles`等）。        |
| `setFilter(QDir::Filters filters)`                           | 设置文件过滤器（如`QDir::AllEntries`）。                     |
| `setHistory(const QStringList &paths)`                       | 设置历史路径列表。                                           |
| `setIconProvider(QAbstractFileIconProvider *provider)`       | 设置文件图标提供器。                                         |
| `setItemDelegate(QAbstractItemDelegate *delegate)`           | 设置自定义项委托。                                           |
| `setLabelText(QFileDialog::DialogLabel label, const QString &text)` | 设置标签文本。                                               |
| `setMimeTypeFilters(const QStringList &filters)`             | 设置MIME类型过滤器列表。                                     |
| `setNameFilter(const QString &filter)`                       | 设置文件名称过滤器（如`*.txt`）。                            |
| `setNameFilters(const QStringList &filters)`                 | 设置多个文件名称过滤器。                                     |
| `setOption(QFileDialog::Option option, bool on = true)`      | 设置特定选项（如是否只显示目录）。                           |
| `setOptions(QFileDialog::Options options)`                   | 设置多个选项。                                               |
| `setProxyModel(QAbstractProxyModel *proxyModel)`             | 设置代理模型。                                               |
| `setSidebarUrls(const QList<QUrl> &urls)`                    | 设置侧边栏URL列表。                                          |
| `setSupportedSchemes(const QStringList &schemes)`            | 设置支持的URL协议（如`file://`、`http://`等）。              |
| `setViewMode(QFileDialog::ViewMode mode)`                    | 设置文件视图模式（`Detail`或`List`）。                       |
| `sidebarUrls()`                                              | 获取侧边栏的URL列表。                                        |
| `supportedSchemes()`                                         | 获取支持的URL协议列表。                                      |
| `testOption(QFileDialog::Option option)`                     | 测试文件对话框的特定选项是否已启用。                         |
| `viewMode()`                                                 | 获取当前视图模式（`Detail`或`List`）。                       |

### **静态函数 (Static Functions)**

| 函数名                      | 功能描述                                         |
| --------------------------- | ------------------------------------------------ |
| `getExistingDirectory()`    | 显示目录选择对话框，返回用户选择的目录路径。     |
| `getExistingDirectoryUrl()` | 显示目录选择对话框，返回用户选择的目录URL。      |
| `getOpenFileContent()`      | 打开文件并获取其内容。                           |
| `getOpenFileName()`         | 显示文件选择对话框，返回用户选择的文件路径。     |
| `getOpenFileNames()`        | 显示文件选择对话框，返回多个用户选择的文件路径。 |
| `getOpenFileUrl()`          | 显示文件选择对话框，返回用户选择的文件URL。      |
| `getOpenFileUrls()`         | 显示文件选择对话框，返回多个用户选择的文件URL。  |
| `getSaveFileName()`         | 显示文件保存对话框，返回用户选择的保存文件路径。 |
| `getSaveFileUrl()`          | 显示文件保存对话框，返回用户选择的保存文件URL。  |
| `saveFileContent()`         | 保存文件内容到指定路径。                         |

### **重写的函数 (Reimplemented Functions)**

| 函数名                     | 功能描述                     |
| -------------------------- | ---------------------------- |
| `setVisible(bool visible)` | 设置文件对话框的可见性。     |
| `accept()`                 | 接受对话框选择的文件或目录。 |
| `changeEvent(QEvent *e)`   | 处理窗口的变化事件。         |
| `done(int result)`         | 完成对话框操作并返回结果。   |

### **信号 (Signals)**

| 信号名                                       | 功能描述                     |
| -------------------------------------------- | ---------------------------- |
| `currentChanged(const QString &path)`        | 当前文件路径更改时发出信号。 |
| `currentUrlChanged(const QUrl &url)`         | 当前URL更改时发出信号。      |
| `directoryEntered(const QString &directory)` | 进入新目录时发出信号。       |
| `directoryUrlEntered(const QUrl &directory)` | 进入新目录URL时发出信号。    |
| `fileSelected(const QString &file)`          | 选择文件时发出信号。         |
| `filesSelected(const QStringList &selected)` | 选择多个文件时发出信号。     |
| `filterSelected(const QString &filter)`      | 选择文件过滤器时发出信号。   |
| `urlSelected(const QUrl &url)`               | 选择URL时发出信号。          |
| `urlsSelected(const QList<QUrl> &urls)`      | 选择多个URL时发出信号。      |

## QColorDialog

### **枚举类型 (Enums)**

| 枚举类型               | 枚举值                | 功能描述                                                     |
| ---------------------- | --------------------- | ------------------------------------------------------------ |
| **ColorDialogOption**  | `ShowAlphaChannel`    | 显示 alpha 通道（透明度）                                    |
|                        | `NoButtons`           | 不显示按钮                                                   |
|                        | `NoEyeDropperButton`  | 不显示吸管按钮                                               |
|                        | `DontUseNativeDialog` | 不使用原生对话框                                             |
| **ColorDialogOptions** | -                     | 该枚举是 `ColorDialogOption` 的标志，表示不同的颜色对话框选项。 |

### **属性 (Properties)**

| 属性名         | 类型                 | 功能描述             |
| -------------- | -------------------- | -------------------- |
| `currentColor` | `QColor`             | 获取当前选中的颜色。 |
| `options`      | `ColorDialogOptions` | 获取对话框的选项。   |

### **成员函数 (Member Functions)**

| 函数名                                                       | 功能描述                                         |
| ------------------------------------------------------------ | ------------------------------------------------ |
| `QColorDialog(QWidget *parent = nullptr)`                    | 构造函数，创建颜色对话框，指定父窗口。           |
| `QColorDialog(const QColor &initial, QWidget *parent = nullptr)` | 构造函数，创建颜色对话框，指定初始颜色和父窗口。 |
| `~QColorDialog()`                                            | 析构函数，销毁颜色对话框。                       |
| `currentColor()`                                             | 获取当前选中的颜色。                             |
| `open(QObject *receiver, const char *member)`                | 打开颜色对话框，并连接信号槽。                   |
| `options()`                                                  | 获取颜色对话框的选项。                           |
| `selectedColor()`                                            | 获取选中的颜色。                                 |
| `setCurrentColor(const QColor &color)`                       | 设置当前选中的颜色。                             |
| `setOption(QColorDialog::ColorDialogOption option, bool on = true)` | 设置颜色对话框的选项。                           |
| `setOptions(QColorDialog::ColorDialogOptions options)`       | 设置多个颜色对话框选项。                         |
| `testOption(QColorDialog::ColorDialogOption option)`         | 测试颜色对话框是否启用了某个选项。               |

### **重写的公共函数 (Reimplemented Public Functions)**

| 函数名                     | 功能描述                 |
| -------------------------- | ------------------------ |
| `setVisible(bool visible)` | 设置颜色对话框的可见性。 |

### **信号 (Signals)**

| 信号名                                     | 功能描述                   |
| ------------------------------------------ | -------------------------- |
| `colorSelected(const QColor &color)`       | 当用户选择颜色时发出信号。 |
| `currentColorChanged(const QColor &color)` | 当当前颜色更改时发出信号。 |

### **静态公共成员函数 (Static Public Members)**

| 函数名                                                       | 功能描述                             |
| ------------------------------------------------------------ | ------------------------------------ |
| `customColor(int index)`                                     | 获取自定义颜色。                     |
| `customCount()`                                              | 获取自定义颜色的数量。               |
| `getColor(const QColor &initial = Qt::white, QWidget *parent = nullptr, const QString &title = QString(), QColorDialog::ColorDialogOptions options = ColorDialogOptions())` | 显示颜色选择对话框并返回选中的颜色。 |
| `setCustomColor(int index, QColor color)`                    | 设置自定义颜色。                     |
| `setStandardColor(int index, QColor color)`                  | 设置标准颜色。                       |
| `standardColor(int index)`                                   | 获取标准颜色。                       |

### **重写的保护函数 (Reimplemented Protected Functions)**

| 函数名                   | 功能描述                   |
| ------------------------ | -------------------------- |
| `changeEvent(QEvent *e)` | 处理对话框的变化事件。     |
| `done(int result)`       | 完成对话框操作并返回结果。 |

## QFontDialog

### **枚举类型 (Enums)**

| 枚举类型              | 枚举值                | 功能描述                                                     |
| --------------------- | --------------------- | ------------------------------------------------------------ |
| **FontDialogOption**  | `NoButtons`           | 不显示按钮                                                   |
|                       | `DontUseNativeDialog` | 不使用原生对话框                                             |
|                       | `ScalableFonts`       | 仅显示可缩放字体                                             |
|                       | `NonScalableFonts`    | 仅显示不可缩放字体                                           |
|                       | `MonospacedFonts`     | 显示等宽字体                                                 |
|                       | `ProportionalFonts`   | 显示比例字体                                                 |
| **FontDialogOptions** | -                     | 该枚举是 `FontDialogOption` 的标志，表示不同的字体对话框选项。 |

### **属性 (Properties)**

| 属性名        | 类型                | 功能描述               |
| ------------- | ------------------- | ---------------------- |
| `currentFont` | `QFont`             | 获取当前选中的字体。   |
| `options`     | `FontDialogOptions` | 获取字体对话框的选项。 |

### **成员函数 (Member Functions)**

| 函数名                                                       | 功能描述                                         |
| ------------------------------------------------------------ | ------------------------------------------------ |
| `QFontDialog(QWidget *parent = nullptr)`                     | 构造函数，创建字体对话框，指定父窗口。           |
| `QFontDialog(const QFont &initial, QWidget *parent = nullptr)` | 构造函数，创建字体对话框，指定初始字体和父窗口。 |
| `~QFontDialog()`                                             | 析构函数，销毁字体对话框。                       |
| `currentFont()`                                              | 获取当前选中的字体。                             |
| `open(QObject *receiver, const char *member)`                | 打开字体对话框，并连接信号槽。                   |
| `options()`                                                  | 获取字体对话框的选项。                           |
| `selectedFont()`                                             | 获取选中的字体。                                 |
| `setCurrentFont(const QFont &font)`                          | 设置当前选中的字体。                             |
| `setOption(QFontDialog::FontDialogOption option, bool on = true)` | 设置字体对话框的选项。                           |
| `setOptions(QFontDialog::FontDialogOptions options)`         | 设置多个字体对话框选项。                         |
| `testOption(QFontDialog::FontDialogOption option)`           | 测试字体对话框是否启用了某个选项。               |

### **重写的公共函数 (Reimplemented Public Functions)**

| 函数名                     | 功能描述                 |
| -------------------------- | ------------------------ |
| `setVisible(bool visible)` | 设置字体对话框的可见性。 |

### **信号 (Signals)**

| 信号名                                  | 功能描述                   |
| --------------------------------------- | -------------------------- |
| `currentFontChanged(const QFont &font)` | 当当前字体更改时发出信号。 |
| `fontSelected(const QFont &font)`       | 当用户选择字体时发出信号。 |

### **静态公共成员函数 (Static Public Members)**

| 函数名                                                       | 功能描述                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `getFont(bool *ok, const QFont &initial, QWidget *parent = nullptr, const QString &title = QString(), QFontDialog::FontDialogOptions options = FontDialogOptions())` | 显示字体选择对话框并返回选中的字体。返回值 `ok` 表示用户是否点击了 OK。 |
| `getFont(bool *ok, QWidget *parent = nullptr)`               | 显示字体选择对话框，默认返回一个字体，`ok` 参数表示是否点击了 OK。 |

### **重写的保护函数 (Reimplemented Protected Functions)**

| 函数名                   | 功能描述                   |
| ------------------------ | -------------------------- |
| `changeEvent(QEvent *e)` | 处理对话框的变化事件。     |
| `done(int result)`       | 完成对话框操作并返回结果。 |

## QProgressDialog

### **属性 (Properties)**

| 属性名            | 类型      | 功能描述                                                 |
| ----------------- | --------- | -------------------------------------------------------- |
| `autoClose`       | `bool`    | 是否在进度完成后自动关闭对话框。                         |
| `autoReset`       | `bool`    | 是否在进度对话框关闭后自动重置进度条。                   |
| `labelText`       | `QString` | 获取或设置对话框的标签文本。                             |
| `maximum`         | `int`     | 获取或设置进度条的最大值。                               |
| `minimum`         | `int`     | 获取或设置进度条的最小值。                               |
| `minimumDuration` | `int`     | 获取或设置显示进度对话框的最小持续时间（以毫秒为单位）。 |
| `value`           | `int`     | 获取或设置进度条的当前值。                               |
| `wasCanceled`     | `bool`    | 获取是否取消了进度对话框。                               |

### **成员函数 (Member Functions)**

| 函数名                                                       | 功能描述                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QProgressDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())` | 构造函数，创建一个进度对话框。                               |
| `QProgressDialog(const QString &labelText, const QString &cancelButtonText, int minimum, int maximum, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())` | 构造函数，创建一个带有标签、取消按钮和进度范围的进度对话框。 |
| `~QProgressDialog()`                                         | 析构函数，销毁进度对话框。                                   |
| `autoClose()`                                                | 获取是否启用了自动关闭选项。                                 |
| `autoReset()`                                                | 获取是否启用了自动重置选项。                                 |
| `labelText()`                                                | 获取进度对话框的标签文本。                                   |
| `maximum()`                                                  | 获取进度条的最大值。                                         |
| `minimum()`                                                  | 获取进度条的最小值。                                         |
| `minimumDuration()`                                          | 获取最小持续时间。                                           |
| `open(QObject *receiver, const char *member)`                | 打开进度对话框并连接信号槽。                                 |
| `setAutoClose(bool close)`                                   | 设置是否在进度完成后自动关闭对话框。                         |
| `setAutoReset(bool reset)`                                   | 设置是否在进度对话框关闭后自动重置进度条。                   |
| `setBar(QProgressBar *bar)`                                  | 设置自定义的进度条（`QProgressBar`）。                       |
| `setCancelButton(QPushButton *cancelButton)`                 | 设置自定义的取消按钮。                                       |
| `setLabel(QLabel *label)`                                    | 设置自定义的标签控件。                                       |
| `value()`                                                    | 获取进度条的当前值。                                         |
| `wasCanceled()`                                              | 判断是否取消了进度对话框。                                   |

### **重写的公共函数 (Reimplemented Public Functions)**

| 函数名       | 功能描述                   |
| ------------ | -------------------------- |
| `sizeHint()` | 获取进度对话框的建议大小。 |

### **公共槽 (Public Slots)**

| 函数名                                                 | 功能描述                                 |
| ------------------------------------------------------ | ---------------------------------------- |
| `cancel()`                                             | 取消进度对话框并发出 `canceled()` 信号。 |
| `reset()`                                              | 重置进度条到初始状态。                   |
| `setCancelButtonText(const QString &cancelButtonText)` | 设置取消按钮的文本。                     |
| `setLabelText(const QString &text)`                    | 设置进度对话框的标签文本。               |
| `setMaximum(int maximum)`                              | 设置进度条的最大值。                     |
| `setMinimum(int minimum)`                              | 设置进度条的最小值。                     |
| `setMinimumDuration(int ms)`                           | 设置最小显示时间。                       |
| `setRange(int minimum, int maximum)`                   | 设置进度条的最小值和最大值。             |
| `setValue(int progress)`                               | 设置进度条的当前值。                     |

### **信号 (Signals)**

| 信号名       | 功能描述                       |
| ------------ | ------------------------------ |
| `canceled()` | 当进度对话框被取消时发出信号。 |

### **重写的保护函数 (Reimplemented Protected Functions)**

| 函数名                             | 功能描述                       |
| ---------------------------------- | ------------------------------ |
| `changeEvent(QEvent *ev)`          | 处理进度对话框的变化事件。     |
| `closeEvent(QCloseEvent *e)`       | 处理进度对话框的关闭事件。     |
| `resizeEvent(QResizeEvent *event)` | 处理进度对话框的调整大小事件。 |
| `showEvent(QShowEvent *e)`         | 处理进度对话框的显示事件。     |

### **保护槽 (Protected Slots)**

| 函数名        | 功能描述                                   |
| ------------- | ------------------------------------------ |
| `forceShow()` | 强制显示进度对话框，通常在 UI 更新时使用。 |

## QInputDialog

### **公共类型 (Public Types)**

1. **InputDialogOption**
   枚举类型，定义输入对话框的选项：
   - `NoButtons`：不显示按钮。
   - `UseListViewForComboBoxItems`：在组合框中使用列表视图。
   - `UsePlainTextEditForTextInput`：使用纯文本编辑器输入。
2. **InputMode**
   枚举类型，定义输入的模式：
   - `TextInput`：文本输入。
   - `IntInput`：整数输入。
   - `DoubleInput`：浮动点数输入。

### **属性 (Properties)**

| 属性名             | 类型                  | 功能描述                                                   |
| ------------------ | --------------------- | ---------------------------------------------------------- |
| `cancelButtonText` | `QString`             | 获取或设置取消按钮的文本。                                 |
| `comboBoxEditable` | `bool`                | 获取或设置组合框是否可编辑。                               |
| `comboBoxItems`    | `QStringList`         | 获取组合框中的项列表。                                     |
| `doubleDecimals`   | `int`                 | 获取或设置浮动点数输入框的小数位数。                       |
| `doubleMaximum`    | `double`              | 获取或设置浮动点数输入的最大值。                           |
| `doubleMinimum`    | `double`              | 获取或设置浮动点数输入的最小值。                           |
| `doubleStep`       | `double`              | 获取或设置浮动点数输入的步长。                             |
| `doubleValue`      | `int`                 | 获取或设置浮动点数输入的当前值。                           |
| `inputMode`        | `InputMode`           | 获取或设置输入模式（文本、整数、浮动点数）。               |
| `intMaximum`       | `int`                 | 获取或设置整数输入的最大值。                               |
| `intMinimum`       | `int`                 | 获取或设置整数输入的最小值。                               |
| `intStep`          | `int`                 | 获取或设置整数输入的步长。                                 |
| `intValue`         | `int`                 | 获取或设置整数输入的当前值。                               |
| `labelText`        | `QString`             | 获取或设置标签文本。                                       |
| `okButtonText`     | `QString`             | 获取或设置确认按钮的文本。                                 |
| `options`          | `InputDialogOptions`  | 获取或设置输入对话框的选项。                               |
| `textEchoMode`     | `QLineEdit::EchoMode` | 获取或设置文本输入框的回显模式（例如密码输入时隐藏文本）。 |
| `textValue`        | `QString`             | 获取或设置文本输入框的值。                                 |

### **成员函数 (Member Functions)**

| 函数名                                                       | 功能描述                       |
| ------------------------------------------------------------ | ------------------------------ |
| `QInputDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())` | 构造函数，创建一个输入对话框。 |
| `~QInputDialog()`                                            | 析构函数，销毁输入对话框。     |
| `cancelButtonText()`                                         | 获取取消按钮的文本。           |
| `comboBoxItems()`                                            | 获取组合框中的项列表。         |
| `doubleDecimals()`                                           | 获取浮动点数输入框的小数位数。 |
| `doubleMaximum()`                                            | 获取浮动点数输入的最大值。     |
| `doubleMinimum()`                                            | 获取浮动点数输入的最小值。     |
| `doubleStep()`                                               | 获取浮动点数输入的步长。       |
| `doubleValue()`                                              | 获取浮动点数输入的当前值。     |
| `inputMode()`                                                | 获取输入模式。                 |
| `intMaximum()`                                               | 获取整数输入的最大值。         |
| `intMinimum()`                                               | 获取整数输入的最小值。         |
| `intStep()`                                                  | 获取整数输入的步长。           |
| `intValue()`                                                 | 获取整数输入的当前值。         |
| `isComboBoxEditable()`                                       | 判断组合框是否可编辑。         |
| `labelText()`                                                | 获取标签文本。                 |
| `okButtonText()`                                             | 获取确认按钮的文本。           |
| `open(QObject *receiver, const char *member)`                | 打开输入对话框并连接信号槽。   |
| `options()`                                                  | 获取输入对话框的选项。         |
| `setCancelButtonText(const QString &text)`                   | 设置取消按钮的文本。           |
| `setComboBoxEditable(bool editable)`                         | 设置组合框是否可编辑。         |
| `setComboBoxItems(const QStringList &items)`                 | 设置组合框的项列表。           |
| `setDoubleDecimals(int decimals)`                            | 设置浮动点数输入的小数位数。   |
| `setDoubleMaximum(double max)`                               | 设置浮动点数输入的最大值。     |
| `setDoubleMinimum(double min)`                               | 设置浮动点数输入的最小值。     |
| `setDoubleRange(double min, double max)`                     | 设置浮动点数输入的范围。       |
| `setDoubleStep(double step)`                                 | 设置浮动点数输入的步长。       |
| `setDoubleValue(double value)`                               | 设置浮动点数输入的当前值。     |
| `setInputMode(QInputDialog::InputMode mode)`                 | 设置输入模式。                 |
| `setIntMaximum(int max)`                                     | 设置整数输入的最大值。         |
| `setIntMinimum(int min)`                                     | 设置整数输入的最小值。         |
| `setIntRange(int min, int max)`                              | 设置整数输入的范围。           |
| `setIntStep(int step)`                                       | 设置整数输入的步长。           |
| `setIntValue(int value)`                                     | 设置整数输入的当前值。         |
| `setLabelText(const QString &text)`                          | 设置标签文本。                 |
| `setOkButtonText(const QString &text)`                       | 设置确认按钮的文本。           |
| `setOption(QInputDialog::InputDialogOption option, bool on = true)` | 设置输入对话框的选项。         |
| `setOptions(QInputDialog::InputDialogOptions options)`       | 设置多个输入对话框选项。       |
| `setTextEchoMode(QLineEdit::EchoMode mode)`                  | 设置文本输入框的回显模式。     |
| `setTextValue(const QString &text)`                          | 设置文本输入框的当前值。       |
| `testOption(QInputDialog::InputDialogOption option)`         | 测试某个选项是否启用。         |
| `textEchoMode()`                                             | 获取文本输入框的回显模式。     |
| `textValue()`                                                | 获取文本输入框的当前值。       |

### **重写的公共函数 (Reimplemented Public Functions)**

| 函数名                     | 功能描述                   |
| -------------------------- | -------------------------- |
| `done(int result)`         | 当对话框关闭时，返回结果。 |
| `minimumSizeHint()`        | 获取对话框的最小尺寸建议。 |
| `setVisible(bool visible)` | 设置对话框的可见性。       |
| `sizeHint()`               | 获取对话框的推荐尺寸。     |

### **信号 (Signals)**

| 信号名                                   | 功能描述                       |
| ---------------------------------------- | ------------------------------ |
| `doubleValueChanged(double value)`       | 当浮动点数值变化时发出信号。   |
| `doubleValueSelected(double value)`      | 当浮动点数值被选中时发出信号。 |
| `intValueChanged(int value)`             | 当整数值变化时发出信号。       |
| `intValueSelected(int value)`            | 当整数值被选中时发出信号。     |
| `textValueChanged(const QString &text)`  | 当文本值变化时发出信号。       |
| `textValueSelected(const QString &text)` | 当文本值被选中时发出信号。     |

### **静态公共成员函数 (Static Public Members)**

| 函数名                                                       | 功能描述                                               |
| ------------------------------------------------------------ | ------------------------------------------------------ |
| `getDouble(QWidget *parent, const QString &title, const QString &label, double value = 0, double min = -2147483647, double max = 2147483647, int decimals = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), double step = 1)` | 显示浮动点数输入对话框，允许用户输入一个浮动点数。     |
| `getInt(QWidget *parent, const QString &title, const QString &label, int value = 0, int min = -2147483647, int max = 2147483647, int step = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())` | 显示整数输入对话框，允许用户输入一个整数。             |
| `getItem(QWidget *parent, const QString &title, const QString &label, const QStringList &items, int current = 0, bool editable = true, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)` | 显示一个选择项的对话框，允许用户从多个选项中选择一个。 |
| `getMultiLineText(QWidget *parent, const QString &title, const QString &label, const QString &text = QString(), bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)` | 显示多行文本输入对话框。                               |
| `getText(QWidget *parent, const QString &title, const QString &label, QLineEdit::EchoMode mode = QLineEdit::Normal, const QString &text = QString(), bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::InputMethodHints inputMethodHints = Qt::ImhNone)` | 显示文本输入对话框，允许用户输入文本。                 |