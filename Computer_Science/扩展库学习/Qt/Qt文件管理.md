# Qt 文件管理

​	下面聊一下我们Qt的文件管理是如何的。

## QIODevice

​	这是所有的输入输出设备的父类！QIODevice 为支持读写数据块的设备（如 QFile、QBuffer 和 QTcpSocket）提供了通用实现和抽象接口。QIODevice 是抽象的，无法实例化，但通常使用它定义的接口来提供独立于设备的 I/O 功能。例如，Qt 的 XML 类对 QIODevice 指针进行操作，允许它们与各种设备（如文件和缓冲区）一起使用。

​	在访问设备之前，必须调用 open() 来设置正确的 OpenMode（如 ReadOnly 或 ReadWrite）。然后，您可以使用 write() 或 putChar() 写入设备，并通过调用 read()、readLine() 或 readAll() 进行读取。使用完设备后，请调用 close()。

​	QIODevice 区分两种类型的设备：随机访问设备和顺序设备。

1. 随机访问设备支持使用 seek() 查找任意位置。通过调用 pos() 可获得文件中的当前位置。QFile 和 QBuffer 是随机访问设备的示例。

2. 顺序设备不支持查找任意位置。数据必须一次性读取。函数 pos() 和 size() 不适用于顺序设备。QTcpSocket 和 QProcess 就是顺序设备的示例。

​	您可以使用 isSequential() 来确定设备的类型。当有新数据可供读取时，QIODevice 会发出 readyRead()；例如，如果网络上有新数据到达，或者您正在读取的文件中附加了其他数据。您可以调用 bytesAvailable() 来确定当前可供读取的字节数。在使用异步设备（如 QTcpSocket）进行编程时，通常会将 bytesAvailable() 与 readyRead() 信号一起使用，因为数据片段可以在任意时间点到达。每次将数据有效负载写入设备时，QIODevice 都会发出 bytesWritten() 信号。使用 bytesToWrite() 来确定当前等待写入的数据量。

​	QIODevice 的某些子类（如 QTcpSocket 和 QProcess）是异步的。**这意味着 write() 或 read() 等 I/O 函数始终会立即返回，而与设备本身的通信则可能在控制权返回到事件循环时发生。QIODevice 提供的函数允许您强制立即执行这些操作，同时阻止调用线程，而无需进入事件循环。这允许在没有事件循环的情况下或在单独的线程中使用 QIODevice 子类：**

- waitForReadyRead() - 此函数暂停调用线程中的操作，直到有新数据可供读取。

- waitForBytesWritten() - 此函数暂停调用线程中的操作，直到将一个有效负载的数据写入设备。
- waitFor....() - QIODevice 的子类为特定于设备的操作实现阻塞函数。例如，QProcess 有一个名为 waitForStarted() 的函数，它暂停调用线程中的操作，直到进程启动。

从主 GUI 线程调用这些函数可能会导致您的用户界面冻结。示例：

```
QProcess gzip;
gzip.start("gzip", QStringList() << "-c");
if (!gzip.waitForStarted())
return false;

gzip.write("uncompressed data");

QByteArray compressed;
while (gzip.waitForReadyRead())
compressed += gzip.readAll();
```

​	通过对 QIODevice 进行子类化，您可以为自己的 I/O 设备提供相同的接口。**QIODevice 的子类只需要实现受保护的 readData() 和 writeData() 函数。QIODevice 使用这些函数来实现其所有便利函数**，例如 getChar()、readLine() 和 write()。QIODevice 还为您处理访问控制，**因此如果调用 writeData()，您可以放心地假设设备以写入模式打开。**

一些子类（例如 QFile 和 QTcpSocket）使用内存缓冲区来实现数据的中间存储。这减少了所需的设备访问调用次数，这些调用通常非常慢。缓冲使 getChar() 和 putChar() 等函数运行速度更快，因为它们可以在内存缓冲区上操作，而不是直接在设备本身上操作。但是，某些 I/O 操作在缓冲区上不太好用。例如，如果多个用户打开同一个设备并逐个字符地读取，他们可能最终读取了相同的数据，而他们原本想读取的是单独的块。**因此，QIODevice 允许您通过将 Unbuffered 标志传递给 open() 来绕过任何缓冲。在对 QIODevice 进行子类化时，请记住在设备以无缓冲模式打开时绕过您可能使用的任何缓冲区。**

​	通常，来自异步设备的传入数据流是碎片化的，数据块可以在任意时间点到达。要处理数据结构的不完整读取，请使用 QIODevice 实现的事务机制。有关更多详细信息，请参阅 startTransaction() 和相关函数。

​	一些顺序设备支持通过多个通道进行通信。这些通道重新提供具有独立顺序传送属性的单独数据流。打开设备后，您可以通过调用 readChannelCount() 和 writeChannelCount() 函数来确定通道数。要在通道之间切换，请分别调用 setCurrentReadChannel() 和 setCurrentWriteChannel()。QIODevice 还提供其他信号来处理每个通道上的异步通信。

​	在这里，我们可能还会继续一些常见的Qt的IODevice扩展的类。比如说QFile, QSaveFile（这个类用来保存需要花费长时间保存的文件，比如说从网络上下载的文件）等

### 一些常见的API

| **类别**                | **成员/函数**                                                | **说明**                               |
| ----------------------- | ------------------------------------------------------------ | -------------------------------------- |
| **Public Functions**    | `QIODevice()`                                                | 默认构造函数。                         |
|                         | `QIODevice(QObject *parent)`                                 | 构造函数，设置父对象。                 |
|                         | `virtual ~QIODevice()`                                       | 析构函数，销毁 `QIODevice` 实例。      |
|                         | `virtual bool atEnd() const`                                 | 判断是否已到达设备的末尾。             |
|                         | `virtual qint64 bytesAvailable() const`                      | 获取当前可读的数据字节数。             |
|                         | `virtual qint64 bytesToWrite() const`                        | 获取当前可写的数据字节数。             |
|                         | `virtual bool canReadLine() const`                           | 判断是否可以读取一行数据。             |
|                         | `virtual void close()`                                       | 关闭设备。                             |
|                         | `void commitTransaction()`                                   | 提交事务。                             |
|                         | `int currentReadChannel() const`                             | 获取当前读取的通道索引。               |
|                         | `int currentWriteChannel() const`                            | 获取当前写入的通道索引。               |
|                         | `QString errorString() const`                                | 获取设备错误信息。                     |
|                         | `bool getChar(char *c)`                                      | 从设备中读取一个字符。                 |
|                         | `bool isOpen() const`                                        | 判断设备是否打开。                     |
|                         | `bool isReadable() const`                                    | 判断设备是否可读。                     |
|                         | `virtual bool isSequential() const`                          | 判断设备是否为顺序设备（如文件）。     |
|                         | `bool isTextModeEnabled() const`                             | 判断设备是否启用了文本模式。           |
|                         | `bool isTransactionStarted() const`                          | 判断设备事务是否已开始。               |
|                         | `bool isWritable() const`                                    | 判断设备是否可写。                     |
|                         | `virtual bool open(QIODeviceBase::OpenMode mode)`            | 打开设备，设置访问模式。               |
|                         | `QIODeviceBase::OpenMode openMode() const`                   | 获取当前打开模式。                     |
|                         | `qint64 peek(char *data, qint64 maxSize)`                    | 从设备中读取数据但不改变读取位置。     |
|                         | `QByteArray peek(qint64 maxSize)`                            | 从设备中读取数据但不改变读取位置。     |
|                         | `virtual qint64 pos() const`                                 | 获取当前读取位置。                     |
|                         | `bool putChar(char c)`                                       | 向设备写入一个字符。                   |
|                         | `qint64 read(char *data, qint64 maxSize)`                    | 从设备读取数据。                       |
|                         | `QByteArray read(qint64 maxSize)`                            | 从设备读取指定大小的数据。             |
|                         | `QByteArray readAll()`                                       | 从设备读取所有数据。                   |
|                         | `int readChannelCount() const`                               | 获取读取通道数量。                     |
|                         | `qint64 readLine(char *data, qint64 maxSize)`                | 从设备中读取一行数据。                 |
|                         | `QByteArray readLine(qint64 maxSize = 0)`                    | 从设备中读取一行数据。                 |
|                         | `virtual bool reset()`                                       | 重置设备状态。                         |
|                         | `void rollbackTransaction()`                                 | 回滚事务。                             |
|                         | `virtual bool seek(qint64 pos)`                              | 移动设备的读取位置。                   |
|                         | `void setCurrentReadChannel(int channel)`                    | 设置当前读取的通道索引。               |
|                         | `void setCurrentWriteChannel(int channel)`                   | 设置当前写入的通道索引。               |
|                         | `void setTextModeEnabled(bool enabled)`                      | 启用或禁用文本模式。                   |
|                         | `virtual qint64 size() const`                                | 获取设备的大小。                       |
|                         | `qint64 skip(qint64 maxSize)`                                | 跳过设备中的数据。                     |
|                         | `void startTransaction()`                                    | 启动事务。                             |
|                         | `void ungetChar(char c)`                                     | 将一个字符放回设备中。                 |
|                         | `virtual bool waitForBytesWritten(int msecs)`                | 等待数据写入完成。                     |
|                         | `virtual bool waitForReadyRead(int msecs)`                   | 等待设备数据可读。                     |
|                         | `qint64 write(const char *data, qint64 maxSize)`             | 向设备写入数据。                       |
|                         | `qint64 write(const QByteArray &data)`                       | 向设备写入字节数组。                   |
|                         | `qint64 write(const char *data)`                             | 向设备写入数据。                       |
|                         | `int writeChannelCount() const`                              | 获取写入通道数量。                     |
| **Signals**             | `void aboutToClose()`                                        | 信号：设备即将关闭。                   |
|                         | `void bytesWritten(qint64 bytes)`                            | 信号：写入了指定字节数的数据。         |
|                         | `void channelBytesWritten(int channel, qint64 bytes)`        | 信号：指定通道写入了指定字节数的数据。 |
|                         | `void channelReadyRead(int channel)`                         | 信号：指定通道有数据可读。             |
|                         | `void readChannelFinished()`                                 | 信号：读取通道完成。                   |
|                         | `void readyRead()`                                           | 信号：设备有数据可读。                 |
| **Protected Functions** | `virtual qint64 readData(char *data, qint64 maxSize) = 0`    | 纯虚函数，读取数据。                   |
|                         | `virtual qint64 readLineData(char *data, qint64 maxSize)`    | 纯虚函数，读取一行数据。               |
|                         | `void setErrorString(const QString &str)`                    | 设置设备的错误信息。                   |
|                         | `void setOpenMode(QIODeviceBase::OpenMode openMode)`         | 设置设备的打开模式。                   |
|                         | `(since 6.0) virtual qint64 skipData(qint64 maxSize)`        | 跳过指定大小的数据。                   |
|                         | `virtual qint64 writeData(const char *data, qint64 maxSize) = 0` | 纯虚函数，向设备写入数据               |

## 文件读写的类

### QFile

​	QFile直接对文件本身进行抽象！是一种用于读写文本和二进制文件及资源的 I/O 设备。QFile 可以单独使用，也可以更方便地与 QTextStream 或 QDataStream 一起使用。

​	文件名通常在构造函数中传递，但可以使用 setFileName() 随时设置。QFile 要求文件分隔符为“/”，无论操作系统是什么。不支持使用其他分隔符（例如“\”）。

​	您可以使用 exist() 检查文件是否存在，并使用 remove() 删除文件。（QFileInfo 和 QDir 提供了更高级的文件系统相关操作。）使用 open() 打开文件，使用 close() 关闭文件，使用 flush() 刷新文件。通常使用 QDataStream 或 QTextStream 读取和写入数据，但您也可以调用 QIODevice 继承的函数 read()、readLine()、readAll()、write()。 QFile 还继承了 getChar()、putChar() 和 ungetChar()，它们每次处理一个字符。

​	size() 返回文件的大小。您可以使用 pos() 获取当前文件位置，或使用 seek() 移动到新文件位置。如果您已到达文件末尾，atEnd() 将返回 true。

​	以下示例逐行读取文本文件：

```
QFile file("in.txt");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
return;

while (!file.atEnd()) {
	QByteArray line = file.readLine();
	process_line(line);
}
```

​	传递给 open() 的 QIODevice::Text 标志告诉 Qt 将 Windows 样式的行终止符（“\r\n”）转换为 C++ 样式的终止符（“\n”）。默认情况下，QFile 采用二进制，即它不对文件中存储的字节执行任何转换。

​	下一个示例使用 QTextStream 逐行读取文本文件：

```
QFile file("in.txt");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
return;

QTextStream in(&file);
while (!in.atEnd()) {
	QString line = in.readLine();
	process_line(line);
}
```

​	QTextStream 负责将存储在磁盘上的 8 位数据转换为 16 位 Unicode QString。默认情况下，它假定文件采用 UTF-8 编码。可以使用 QTextStream::setEncoding() 进行更改。

要写入文本，我们可以使用运算符<<()，该运算符被重载以在左侧接受 QTextStream，在右侧接受各种数据类型（包括 QString）：

```
QFile file("out.txt");
if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
return;

QTextStream out(&file);
out << "The magic number is: " << 49 << "\n";
```

QDataStream 与之类似，您可以使用运算符<<() 写入数据，使用运算符>>() 读回数据。有关详细信息，请参阅类文档。

信号
与其他 QIODevice 实现（例如 QTcpSocket）不同，QFile 不会发出 aboutToClose()、bytesWritten() 或 readyRead() 信号。此实现细节意味着 QFile 不适合读取和写入某些类型的文件，例如 Unix 平台上的设备文件。

平台特定问题
与 I/O 相关的 Qt API 使用基于 UTF-16 的 QString 来表示文件路径。但是，标准 C++ API（<cstdio> 或 <iostream>）或平台特定 API 通常需要 8 位编码路径。您可以使用 encodeName() 和 decryptName() 在两种表示之间进行转换。

在 Unix 上，有一些特殊的系统文件（例如 /proc 中的文件）的 size() 将始终返回 0，但您仍然可以从此类文件中读取更多数据；数据是在您调用 read() 后直接生成的。但是，在这种情况下，您不能使用 atEnd() 来确定是否还有更多数据要读取（因为 atEnd() 将对声称大小为 0 的文件返回 true）。相反，您应该调用 readAll()，或者重复调用 read() 或 readLine()，直到无法读取更多数据。下一个示例使用 QTextStream 逐行读取 /proc/modules：

```
QFile file("/proc/modules");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	return;

QTextStream in(&file);
QString line = in.readLine();
while (!line.isNull()) {
process_line(line);
line = in.readLine();
}
```

​	在类 Unix 系统和 Windows 上，文件权限的处理方式不同。在类 Unix 系统的不可写目录中，无法创建文件。在 Windows 上并非总是如此，例如，“我的文档”目录通常不可写，但仍可以在其中创建文件。

​	Qt 对文件权限的理解有限，这尤其影响 QFile::setPermissions() 函数。在 Windows 上，Qt 将仅设置旧式只读标志，并且仅在未传递任何 Write* 标志时才设置。Qt 不会操作访问控制列表 (ACL)，这使得该函数对于 NTFS 卷几乎无用。对于使用 VFAT 文件系统的 USB 记忆棒，它可能仍然有用。POSIX ACL 也不受操纵。

在 Android 上，处理内容 URI 时会有一些限制：

- 可能需要通过提示用户访问来获得访问权限，QFileDialog 实现了 Android 的原生文件选择器。
- 旨在遵循范围存储指南，例如使用特定于应用程序的目录而不是其他公共外部目录。有关更多信息，另请参阅存储最佳实践。
- 由于 Qt API（例如 QFile）的设计，无法将后者 API 与 Android 的 MediaStore API 完全集成。

#### API

| **类别**                           | **成员/函数**                                                | **说明**                          |
| ---------------------------------- | ------------------------------------------------------------ | --------------------------------- |
| **Public Functions**               | `QFile()`                                                    | 默认构造函数。                    |
|                                    | `QFile(QObject *parent)`                                     | 构造函数，设置父对象。            |
|                                    | `QFile(const QString &name)`                                 | 构造函数，指定文件名。            |
|                                    | `(since 6.0) QFile(const std::filesystem::path &name)`       | 构造函数，指定文件路径（C++17）。 |
|                                    | `QFile(const QString &name, QObject *parent)`                | 构造函数，指定文件名和父对象。    |
|                                    | `(since 6.0) QFile(const std::filesystem::path &name, QObject *parent)` | 构造函数，指定文件路径和父对象。  |
|                                    | `virtual ~QFile()`                                           | 析构函数，销毁 `QFile` 实例。     |
|                                    | `bool copy(const QString &newName)`                          | 复制文件到新路径。                |
|                                    | `(since 6.0) bool copy(const std::filesystem::path &newName)` | 复制文件到新路径（C++17）。       |
|                                    | `bool exists() const`                                        | 检查文件是否存在。                |
|                                    | `(since 6.0) std::filesystem::path filesystemFileName() const` | 获取文件的文件系统路径（C++17）。 |
|                                    | `(since 6.3) std::filesystem::path filesystemSymLinkTarget() const` | 获取文件的符号链接目标（C++17）。 |
|                                    | `bool link(const QString &linkName)`                         | 创建符号链接。                    |
|                                    | `(since 6.0) bool link(const std::filesystem::path &newName)` | 创建符号链接（C++17）。           |
|                                    | `bool moveToTrash()`                                         | 将文件移动到回收站。              |
|                                    | `(since 6.3) bool open(QIODeviceBase::OpenMode mode, QFileDevice::Permissions permissions)` | 打开文件，指定打开模式和权限。    |
|                                    | `bool open(FILE *fh, QIODeviceBase::OpenMode mode, QFileDevice::FileHandleFlags handleFlags = DontCloseHandle)` | 通过文件指针打开文件。            |
|                                    | `bool open(int fd, QIODeviceBase::OpenMode mode, QFileDevice::FileHandleFlags handleFlags = DontCloseHandle)` | 通过文件描述符打开文件。          |
|                                    | `bool remove()`                                              | 删除文件。                        |
|                                    | `bool rename(const QString &newName)`                        | 重命名文件。                      |
|                                    | `(since 6.0) bool rename(const std::filesystem::path &newName)` | 重命名文件（C++17）。             |
|                                    | `void setFileName(const QString &name)`                      | 设置文件名。                      |
|                                    | `(since 6.0) void setFileName(const std::filesystem::path &name)` | 设置文件路径（C++17）。           |
|                                    | `QString symLinkTarget() const`                              | 获取符号链接的目标路径。          |
| **Reimplemented Public Functions** | `virtual QString fileName() const override`                  | 重写函数，获取文件名。            |
|                                    | `virtual bool open(QIODeviceBase::OpenMode mode) override`   | 重写函数，打开文件。              |
|                                    | `virtual QFileDevice::Permissions permissions() const override` | 重写函数，获取文件权限。          |
|                                    | `virtual bool resize(qint64 sz) override`                    | 重写函数，调整文件大小。          |
|                                    | `virtual bool setPermissions(QFileDevice::Permissions permissions) override` | 重写函数，设置文件权限。          |
|                                    | `virtual qint64 size() const override`                       | 重写函数，获取文件大小。          |
| **Static Public Members**          | `bool copy(const QString &fileName, const QString &newName)` | 静态函数，复制文件。              |
|                                    | `QString decodeName(const QByteArray &localFileName)`        | 解码文件名。                      |
|                                    | `QString decodeName(const char *localFileName)`              | 解码文件名。                      |
|                                    | `QByteArray encodeName(const QString &fileName)`             | 编码文件名。                      |
|                                    | `bool exists(const QString &fileName)`                       | 检查文件是否存在。                |
|                                    | `(since 6.3) std::filesystem::path filesystemSymLinkTarget(const std::filesystem::path &fileName)` | 获取文件的符号链接目标（C++17）。 |
|                                    | `bool link(const QString &fileName, const QString &linkName)` | 创建符号链接。                    |
|                                    | `bool moveToTrash(const QString &fileName, QString *pathInTrash = nullptr)` | 删除文件并将其移入回收站。        |
|                                    | `QFileDevice::Permissions permissions(const QString &fileName)` | 获取文件权限。                    |
|                                    | `(since 6.0) QFileDevice::Permissions permissions(const std::filesystem::path &filename)` | 获取文件权限（C++17）。           |
|                                    | `bool remove(const QString &fileName)`                       | 删除文件。                        |
|                                    | `bool rename(const QString &oldName, const QString &newName)` | 重命名文件。                      |
|                                    | `bool resize(const QString &fileName, qint64 sz)`            | 调整文件大小。                    |
|                                    | `bool setPermissions(const QString &fileName, QFileDevice::Permissions permissions)` | 设置文件权限。                    |
|                                    | `(since 6.0) bool setPermissions(const std::filesystem::path &filename, QFileDevice::Permissions permissionSpec)` | 设置文件权限（C++17）。           |
|                                    | `QString symLinkTarget(const QString &fileName)`             | 获取符号链接的目标路径。          |

## QFileInfo

​	QFileInfo 提供有关文件系统条目的信息，例如其名称、路径、访问权限以及它是常规文件、目录还是符号链接。条目的大小和上次修改/读取时间也可用。QFileInfo 还可用于获取有关 Qt 资源的信息。

​	QFileInfo 可以指向具有绝对路径或相对路径的文件系统条目：

1. 在 Unix 上，绝对路径以目录分隔符“/”开头。在 Windows 上，绝对路径以驱动器规范开头（例如，D:/）。

2. 相对路径以目录名称或常规文件名开头，并指定相对于当前工作目录的文件系统条目路径。
3. 绝对路径的一个示例是字符串“/tmp/quartz”。相对路径可能看起来像“src/fatlib”。您可以使用函数 isRelative() 检查 QFileInfo 使用的是相对路径还是绝对路径。您可以调用函数 makeAbsolute() 将相对 QFileInfo 的路径转换为绝对路径。

注意：以冒号 (:) 开头的路径始终被视为绝对路径，因为它们表示 QResource。

​	QFileInfo 处理的文件系统条目路径在构造函数中或稍后使用 setFile() 设置。使用 exist() 查看条目是否实际存在，使用 size() 获取其大小。

​	文件系统条目的类型通过 isFile()、isDir() 和 isSymLink() 获取。symLinkTarget() 函数提供符号链接指向的目标的绝对路径。

​	文件系统条目的路径元素可以使用 path() 和 fileName() 提取。fileName() 的部分可以使用 baseName()、suffix() 或 completeSuffix() 提取。引用由 Qt 类创建的目录的 QFileInfo 对象不会有尾随目录分隔符“/”。如果您希望在自己的文件信息对象中使用尾随分隔符，只需将一个附加到构造函数或 setFile() 给出的条目路径中即可。

​	日期和时间相关信息由birthTime()、fileTime()、lastModified()、lastRead()和metadataChangeTime()返回。有关访问权限的信息可以通过isReadable()、isWritable()和isExecutable()获取。所有权信息可以通过owner()、ownerId()、group()和groupId()获取。您还可以使用permission()函数在单个语句中检查权限和所有权。

#### 符号链接和快捷方式

​	在Unix（包括macOS和iOS）上，此类中的属性获取函数返回目标的属性（例如时间和大小），而不是符号链接，因为Unix透明地处理符号链接。使用QFile打开符号链接实际上会打开链接的目标。例如：

```
#ifdef Q_OS_UNIX

QFileInfo info1("/home/bob/bin/untabify");
info1.isSymLink(); // 返回 true
info1.absoluteFilePath(); // 返回“/home/bob/bin/untabify”
info1.size(); // 返回 56201
info1.symLinkTarget(); // 返回“/opt/pretty++/bin/untabify”

QFileInfo info2(info1.symLinkTarget());
info2.isSymLink(); // 返回 false
info2.absoluteFilePath(); // 返回“/opt/pretty++/bin/untabify”
info2.size(); // 返回 56201

#endif
```

在 Windows 上，快捷方式（.lnk 文件）目前被视为符号链接。与在 Unix 系统上一样，属性获取器返回目标的大小，而不是 .lnk 文件本身。此行为已弃用，可能会在 Qt 的未来版本中被删除，此后 .lnk 文件将被视为常规文件。

```
#ifdef Q_OS_WIN

QFileInfo info1("C:\\Users\\Bob\\untabify.lnk");
info1.isSymLink(); // 返回 true
info1.absoluteFilePath(); // 返回 "C:/Users/Bob/untabify.lnk"
info1.size(); // 返回 63942
info1.symLinkTarget(); // 返回 "C:/Pretty++/untabify"

QFileInfo info2(info1.symLinkTarget());
info2.isSymLink(); // 返回 false
info2.absoluteFilePath(); // 返回 "C:/Pretty++/untabify"
info2.size(); // 返回 63942

#endif
```

#### NTFS 权限

​	在 NTFS 文件系统上，出于性能原因，所有权和权限检查默认处于禁用状态。要启用它，请包含以下行：

```
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;
```

​	然后通过将 qt_ntfs_permission_lookup 增加和减少 1 来打开和关闭权限检查。

```
qt_ntfs_permission_lookup++; // 打开检查
qt_ntfs_permission_lookup--; // 再次关闭
```

​	注意：由于这是一个非原子全局变量，因此只有在主线程以外的任何线程启动之前或主线程以外的每个线程结束后增加或减少 qt_ntfs_permission_lookup 才是安全的。

​	注意：从 Qt 6.6 开始，变量 qt_ntfs_permission_lookup 已弃用。请使用以下替代方案。管理权限检查的安全简便方法是使用 RAII 类 QNtfsPermissionCheckGuard。

```
void complexFunction()
{
	QNtfsPermissionCheckGuard permissionGuard; // 检查已启用
	// 在此执行需要启用权限检查的复杂操作
} 
```

#### API

| **类别**                  | **成员/函数**                                                | **说明**                                                     |
| ------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Public Functions**      | `QFileInfo()`                                                | 默认构造函数。                                               |
|                           | `QFileInfo(const QFileDevice &file)`                         | 使用 `QFileDevice` 构造 `QFileInfo`。                        |
|                           | `QFileInfo(const QString &path)`                             | 使用文件路径字符串构造 `QFileInfo`。                         |
|                           | `(since 6.0) QFileInfo(const std::filesystem::path &file)`   | 使用 `std::filesystem::path` 构造 `QFileInfo`（C++17）。     |
|                           | `QFileInfo(const QDir &dir, const QString &path)`            | 使用目录和路径构造 `QFileInfo`。                             |
|                           | `(since 6.0) QFileInfo(const QDir &dir, const std::filesystem::path &path)` | 使用目录和 `std::filesystem::path` 构造 `QFileInfo`（C++17）。 |
|                           | `QFileInfo(const QFileInfo &fileinfo)`                       | 拷贝构造函数。                                               |
|                           | `~QFileInfo()`                                               | 析构函数，销毁 `QFileInfo` 对象。                            |
|                           | `QDir absoluteDir() const`                                   | 获取文件的绝对目录。                                         |
|                           | `QString absoluteFilePath() const`                           | 获取文件的绝对路径。                                         |
|                           | `QString absolutePath() const`                               | 获取文件所在目录的绝对路径。                                 |
|                           | `QString baseName() const`                                   | 获取文件的基本名称（不包括扩展名）。                         |
|                           | `QDateTime birthTime() const`                                | 获取文件的创建时间。                                         |
|                           | `(since 6.6) QDateTime birthTime(const QTimeZone &tz) const` | 获取文件的创建时间，并指定时区（C++17）。                    |
|                           | `QString bundleName() const`                                 | 获取文件的捆绑名称。                                         |
|                           | `bool caching() const`                                       | 检查是否启用了缓存。                                         |
|                           | `QString canonicalFilePath() const`                          | 获取文件的规范路径（去除符号链接）。                         |
|                           | `QString canonicalPath() const`                              | 获取文件所在目录的规范路径。                                 |
|                           | `QString completeBaseName() const`                           | 获取完整的基本文件名。                                       |
|                           | `QString completeSuffix() const`                             | 获取完整的文件扩展名。                                       |
|                           | `QDir dir() const`                                           | 获取文件的目录信息。                                         |
|                           | `bool exists() const`                                        | 检查文件是否存在。                                           |
|                           | `QString fileName() const`                                   | 获取文件的名称。                                             |
|                           | `QString filePath() const`                                   | 获取文件的路径（包括文件名）。                               |
|                           | `QDateTime fileTime(QFileDevice::FileTime time) const`       | 获取文件的时间戳（如创建时间、修改时间等）。                 |
|                           | `(since 6.6) QDateTime fileTime(QFileDevice::FileTime time, const QTimeZone &tz) const` | 获取文件的时间戳并指定时区（C++17）。                        |
|                           | `(since 6.0) std::filesystem::path filesystemAbsoluteFilePath() const` | 获取文件的绝对路径（C++17）。                                |
|                           | `(since 6.0) std::filesystem::path filesystemAbsolutePath() const` | 获取文件所在目录的绝对路径（C++17）。                        |
|                           | `(since 6.0) std::filesystem::path filesystemCanonicalFilePath() const` | 获取文件的规范路径（C++17）。                                |
|                           | `(since 6.0) std::filesystem::path filesystemCanonicalPath() const` | 获取文件所在目录的规范路径（C++17）。                        |
|                           | `(since 6.0) std::filesystem::path filesystemFilePath() const` | 获取文件路径（C++17）。                                      |
|                           | `(since 6.2) std::filesystem::path filesystemJunctionTarget() const` | 获取文件的连接目标（C++17）。                                |
|                           | `(since 6.0) std::filesystem::path filesystemPath() const`   | 获取文件的路径（C++17）。                                    |
|                           | `(since 6.6) std::filesystem::path filesystemReadSymLink() const` | 读取符号链接目标（C++17）。                                  |
|                           | `(since 6.0) std::filesystem::path filesystemSymLinkTarget() const` | 获取符号链接的目标（C++17）。                                |
|                           | `QString group() const`                                      | 获取文件所属组名。                                           |
|                           | `uint groupId() const`                                       | 获取文件所属组的 ID。                                        |
|                           | `bool isAbsolute() const`                                    | 检查文件路径是否为绝对路径。                                 |
|                           | `(since 6.4) bool isAlias() const`                           | 检查文件是否为别名。                                         |
|                           | `bool isBundle() const`                                      | 检查文件是否为捆绑包。                                       |
|                           | `bool isDir() const`                                         | 检查文件是否为目录。                                         |
|                           | `bool isExecutable() const`                                  | 检查文件是否可执行。                                         |
|                           | `bool isFile() const`                                        | 检查文件是否为普通文件。                                     |
|                           | `bool isHidden() const`                                      | 检查文件是否为隐藏文件。                                     |
|                           | `bool isJunction() const`                                    | 检查文件是否为联接点。                                       |
|                           | `bool isNativePath() const`                                  | 检查文件路径是否为本地路径。                                 |
|                           | `bool isReadable() const`                                    | 检查文件是否可读。                                           |
|                           | `bool isRelative() const`                                    | 检查文件路径是否为相对路径。                                 |
|                           | `bool isRoot() const`                                        | 检查文件是否为根目录。                                       |
|                           | `bool isShortcut() const`                                    | 检查文件是否为快捷方式。                                     |
|                           | `bool isSymLink() const`                                     | 检查文件是否为符号链接。                                     |
|                           | `bool isSymbolicLink() const`                                | 检查文件是否为符号链接（同 `isSymLink`）。                   |
|                           | `bool isWritable() const`                                    | 检查文件是否可写。                                           |
|                           | `(since 6.2) QString junctionTarget() const`                 | 获取文件的联接点目标（C++17）。                              |
|                           | `QDateTime lastModified() const`                             | 获取文件的最后修改时间。                                     |
|                           | `(since 6.6) QDateTime lastModified(const QTimeZone &tz) const` | 获取文件的最后修改时间并指定时区（C++17）。                  |
|                           | `QDateTime lastRead() const`                                 | 获取文件的最后读取时间。                                     |
|                           | `(since 6.6) QDateTime lastRead(const QTimeZone &tz) const`  | 获取文件的最后读取时间并指定时区（C++17）。                  |
|                           | `bool makeAbsolute()`                                        | 将文件路径转换为绝对路径。                                   |
|                           | `QDateTime metadataChangeTime() const`                       | 获取文件的元数据更改时间。                                   |
|                           | `(since 6.6) QDateTime metadataChangeTime(const QTimeZone &tz) const` | 获取文件的元数据更改时间并指定时区（C++17）。                |
|                           | `QString owner() const`                                      | 获取文件的拥有者。                                           |
|                           | `uint ownerId() const`                                       | 获取文件的拥有者 ID。                                        |
|                           | `QString path() const`                                       | 获取文件的路径。                                             |
|                           | `bool permission(QFileDevice::Permissions permissions) const` | 检查文件是否具有指定权限。                                   |
|                           | `QFileDevice::Permissions permissions() const`               | 获取文件的权限。                                             |
|                           | `(since 6.6) QString readSymLink() const`                    | 读取符号链接（C++17）。                                      |
|                           | `void refresh()`                                             | 刷新文件信息。                                               |
|                           | `void setCaching(bool enable)`                               | 启用或禁用缓存。                                             |
|                           | `void setFile(const QString &path)`                          | 设置文件路径（字符串）。                                     |
|                           | `(since 6.0) void setFile(const std::filesystem::path &path)` | 设置文件路径（C++17）。                                      |
|                           | `void setFile(const QFileDevice &file)`                      | 设置文件（`QFileDevice`）。                                  |
|                           | `void setFile(const QDir &dir, const QString &path)`         | 设置文件（`QDir` 和路径）。                                  |
|                           | `qint64 size() const`                                        | 获取文件大小。                                               |
|                           | `(since 6.0) void stat()`                                    | 获取文件的状态信息。                                         |
|                           | `QString suffix() const`                                     | 获取文件扩展名。                                             |
|                           | `void swap(QFileInfo &other)`                                | 交换两个 `QFileInfo` 对象。                                  |
|                           | `QString symLinkTarget() const`                              | 获取符号链接目标。                                           |
| **Static Public Members** | `bool exists(const QString &path)`                           | 静态函数，检查指定路径的文件是否存在。                       |
| **Related Non-Members**   | `QFileInfoList`                                              | 定义 `QFileInfo` 列表类型。                                  |
|                           | `bool operator!=(const QFileInfo &lhs, const QFileInfo &rhs)` | 比较两个 `QFileInfo` 对象是否不相等。                        |
|                           | `bool operator==(const QFileInfo &lhs, const QFileInfo &rhs)` | 比较两个 `QFileInfo` 对象是否相等。                          |
| **Macros**                | `(since 6.0) QT_IMPLICIT_QFILEINFO_CONSTRUCTION`             | 宏定义，隐式构造 `QFileInfo`。                               |

## QDir

​	QDir 用于操作路径名、访问有关路径和文件的信息以及操作底层文件系统。它还可用于访问 Qt 的资源系统。

​	Qt 使用“/”作为通用目录分隔符，就像“/”在 URL 中用作路径分隔符一样。如果您始终使用“/”作为目录分隔符，Qt 将转换您的路径以符合底层操作系统。

​	QDir 可以使用相对路径或绝对路径指向文件。绝对路径以目录分隔符开头（在 Windows 下，可以选择在前面加上驱动器规范）。相对文件名以目录名或文件名开头，并指定相对于当前目录的路径。

```
QDir("/home/user/Documents")
QDir("C:/Users")
```

​	在 Windows 上，上面的第二个示例在用于访问文件时将被转换为 C:\Users。

```
QDir("images/landscape.png")
```

​	您可以使用 isRelative() 或 isAbsolute() 函数检查 QDir 使用的是相对文件路径还是绝对文件路径。调用 makeAbsolute() 将相对 QDir 转换为绝对路径。

​	注意：以冒号 (:) 开头的路径始终被视为绝对路径，因为它们表示 QResource。

#### 导航和目录操作

​	可以使用 path() 函数获取目录路径，使用 setPath() 函数设置新路径。通过调用 absolutePath() 可以找到目录的绝对路径。

​	使用 dirName() 函数可以找到目录的名称。这通常返回绝对路径中指定目录位置的最后一个元素。但是，如果 QDir 代表当前目录，它也可以返回“。”。

```
QDir("Documents/Letters/Applications").dirName() // “Applications”
QDir().dirName() // “.”
```

​	目录的路径也可以通过 cd() 和 cdUp() 函数更改，这两个函数的操作方式与熟悉的 shell 命令类似。当使用现有目录的名称调用 cd() 时，QDir 对象会更改目录，使其改为表示该目录。cdUp() 函数会更改 QDir 对象的目录，使其引用其父目录；即 cd("..") 等同于 cdUp()。

​	目录可以用 mkdir() 创建，用 rename() 重命名，用 rmdir() 删除。

​	您可以使用 exist() 测试具有给定名称的目录是否存在，可以使用 isReadable()、isAbsolute()、isRelative() 和 isRoot() 测试目录的属性。

refresh() 函数从磁盘重新读取目录的数据。

#### 文件和目录内容

​	目录包含多个条目，表示文件、目录和符号链接。目录中的条目数由 count() 返回。可以使用 entryList() 获取目录中所有条目名称的字符串列表。如果您需要有关每个条目的信息，请使用 entryInfoList() 获取 QFileInfo 对象列表。

​	可以使用 filePath() 和 absoluteFilePath() 构造目录中文件和目录的路径。filePath() 函数返回相对于 QDir 对象路径的指定文件或目录的路径；absoluteFilePath() 返回指定文件或目录的绝对路径。这两个函数都不检查文件或目录是否存在；它们只构造路径。

```
QDir directory("Documents/Letters");
QString path = directory.filePath("contents.txt");
QString absolutePath = directory.absoluteFilePath("contents.txt");
```

​	可以使用 remove() 函数删除文件。目录不能以与文件相同的方式删除；请使用 rmdir() 来删除它们。

​	通过将过滤器应用于 QDir 对象，可以减少 entryList() 和 entryInfoList() 返回的条目数。您可以应用名称过滤器来指定文件名需要匹配的带有通配符的模式、选择条目属性并可区分文件和目录的属性过滤器以及排序顺序。

​	名称过滤器是传递给 setNameFilters() 的字符串列表。属性过滤器由 Filters 的按位或组合组成，这些过滤器在调用 setFilter() 时指定。排序顺序是使用 setSorting() 和 SortFlags 的按位或组合指定的。

您可以使用 match() 函数测试文件名是否与过滤器匹配。调用 entryList() 和 entryInfoList() 时还可以指定过滤器和排序顺序标志，以覆盖先前定义的行为。

#### 当前目录和其他特殊路径

一些返回 QDir 对象的静态函数提供了对某些常见目录的访问。这些函数也有相应的函数返回字符串：

```
QDir QString 返回值
current() currentPath() 应用程序的工作目录
home() homePath() 用户的主目录
root() rootPath() 根目录
temp() tempPath() 系统的临时目录
setCurrent() 静态函数还可用于设置应用程序的工作目录。
```

​	drivers() 静态函数为包含文件系统的每个设备提供根目录列表。在 Unix 系统上，这将返回一个包含单个根目录“/”的列表；在 Windows 上，该列表通常包含 C:/，并且可能包含其他驱动器号，例如 D:/，具体取决于用户系统的配置。

#### 路径操作和字符串

​	使用 canonicalPath() 函数可以将包含引用路径中该点的当前目录的“.”元素、引用父目录的“..”元素和符号链接的路径简化为规范形式。还可以通过使用 cleanPath() 删除多余的“/”和“..”元素来简化路径。

​	有时需要能够以用户平台的本机表示形式显示路径。静态 toNativeSeparators() 函数返回指定路径的副本，其中每个目录分隔符都由底层操作系统的适当分隔符替换。
​	检查目录是否存在：

```
QDir dir("example");
if (!dir.exists())
qWarning("无法找到示例目录");
```

（我们还可以使用静态便利函数 QFileInfo::exists() 或 QFile::exists() 之一。）

遍历目录并读取文件：

```
QDir dir = QDir::root(); // "/"
if (!dir.cd("tmp")) { // "/tmp"
	qWarning("无法找到 \"/tmp\" 目录");
} else {
	QFile file(dir.filePath("ex1.txt")); // "/tmp/ex1.txt"
	if (!file.open(QIODevice::ReadWrite))
		qWarning("无法创建文件 %s", file.name());
}
```

列出当前目录中所有文件（不包括符号链接）的程序，按大小排序，最小文件优先：

```
#include <QDir>
#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QDir dir;
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Size | QDir::Reversed);

	QFileInfoList list = dir.entryInfoList();
	std::cout << " Bytes Filename" << std::endl;
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
		std::cout << std::endl;
	}
	return 0;
}
```

#### 平台特定问题

​	在 Android 上，处理内容 URI 时会有一些限制：

​	可能需要通过实现 Android 原生文件选择器的 QFileDialog 提示用户访问权限。
旨在遵循范围存储指南，例如使用特定于应用的目录而不是其他公共外部目录。有关更多信息，另请参阅存储最佳实践。
由于 Qt API（例如 QFile）的设计，无法将后者 API 与 Android 的 MediaStore API 完全集成。

## 临时文件（夹）

### QTemporaryDir 

QTemporaryDir 用于安全地创建唯一的临时目录。目录本身由构造函数创建。临时目录的名称保证是唯一的（即，保证不会覆盖现有目录），并且目录随后将在 QTemporaryDir 对象销毁时被删除。目录名称是自动生成的，或基于模板创建的，该模板传递给 QTemporaryDir 的构造函数。

示例：

```
// 在函数/方法中...

QTemporaryDir dir;
if (dir.isValid()) {
// dir.path() 返回唯一的目录路径
}

// QTemporaryDir 析构函数会删除临时目录
// 因为它超出范围。
```

​	使用 isValid() 测试是否可以创建临时目录非常重要。不要使用 exist()，因为默认构造的 QDir 代表当前目录，该目录存在。可以通过调用 path() 找到临时目录的路径。

​	临时目录的名称将包含一些静态部分，以及一些计算为唯一的部分。默认路径将由 QCoreApplication::applicationName()（否则为 qt_temp）确定，并将放置在 QDir::tempPath() 返回的临时路径中。如果您指定自己的路径，则相对路径默认不会放置在临时目录中，而是相对于当前工作目录。在所有情况下，都会将一个随机字符串附加到路径以使其唯一。

​	另请参阅 QDir::tempPath()、QDir 和 QTemporaryFile。

#### API

| **类别**             | **成员/函数**                                                | **说明**                             |
| -------------------- | ------------------------------------------------------------ | ------------------------------------ |
| **Public Functions** | `QTemporaryDir()`                                            | 默认构造函数，创建一个临时目录对象。 |
|                      | `QTemporaryDir(const QString &templatePath)`                 | 使用指定的模板路径构造临时目录对象。 |
|                      | `(since 6.4) QTemporaryDir(QTemporaryDir &&other)`           | 移动构造函数。                       |
|                      | `~QTemporaryDir()`                                           | 析构函数，销毁临时目录对象。         |
|                      | `bool autoRemove() const`                                    | 返回临时目录是否在销毁时自动删除。   |
|                      | `QString errorString() const`                                | 返回创建临时目录时的错误信息。       |
|                      | `QString filePath(const QString &fileName) const`            | 获取临时目录下指定文件的完整路径。   |
|                      | `bool isValid() const`                                       | 检查临时目录是否有效。               |
|                      | `QString path() const`                                       | 获取临时目录的路径。                 |
|                      | `bool remove()`                                              | 删除临时目录及其内容。               |
|                      | `void setAutoRemove(bool b)`                                 | 设置是否在销毁时自动删除临时目录。   |
|                      | `(since 6.4) void swap(QTemporaryDir &other)`                | 交换两个临时目录对象。               |
|                      | `(since 6.4) QTemporaryDir &operator=(QTemporaryDir &&other)` | 移动赋值操作符。                     |

### QTemporaryFile

​	QTemporaryFile 用于安全地创建唯一的临时文件。文件本身通过调用 open() 创建。临时文件的名称保证是唯一的（即，保证不会覆盖现有文件），并且在 QTemporaryFile 对象销毁时，该文件随后将被删除。对于将数据存储在临时文件中的应用程序，这是一种避免数据损坏的重要技术。文件名是自动生成的，或基于模板创建的，该模板传递给 QTemporaryFile 的构造函数。

示例：

```
// 在函数/方法中...

QTemporaryFile 文件；
if (file.open()) {
// file.fileName() 返回唯一的文件名
}

// QTemporaryFile 析构函数会删除临时文件
// 因为它超出了范围。
```

​	调用 close() 后重新打开 QTemporaryFile 是安全的。只要 QTemporaryFile 对象本身没有被销毁，唯一的临时文件就会存在，并由 QTemporaryFile 在内部保持打开状态。

​	可以通过调用 fileName() 找到临时文件的文件名。请注意，这仅在文件首次打开后定义；在此之前，该函数返回一个空字符串。

​	临时文件的名称将包含一些静态部分和一些计算为唯一的部分。默认文件名将由 QCoreApplication::applicationName()（否则为 qt_temp）确定，并将放置在 QDir::tempPath() 返回的临时路径中。如果您指定自己的文件名，则相对文件路径将默认不会放置在临时目录中，而是相对于当前工作目录。

​	如果要调用 rename() 函数，则指定正确的目录非常重要，因为 QTemporaryFile 只能在与临时文件本身创建所在的卷/文件系统相同的卷/文件系统中重命名文件。

​	文件名（指定文件模板中最后一个目录路径分隔符之后的部分）可以包含特殊序列“XXXXXX”（至少六个大写“X”字符），它将被替换为文件名的自动生成部分。如果文件名不包含“XXXXXX”，QTemporaryFile 会将生成的部分附加到文件名中。仅考虑第一次出现的“XXXXXX”。

​	注意：在 Linux 上，QTemporaryFile 将尝试创建未命名的临时文件。如果成功，open() 将返回 true，但 exist() 将为 false。如果调用 fileName() 或任何调用它的函数，QTemporaryFile 将为文件命名，因此大多数应用程序不会看到差异。

​	另请参阅 QDir::tempPath() 和 QFile。

## 按照流的方式读写文件

### QTextStream

QTextStream 可以对 QIODevice、QByteArray 或 QString 进行操作。使用 QTextStream 的流式操作符，您可以方便地读取和写入单词、行和数字。对于生成文本，QTextStream 支持字段填充和对齐的格式化选项以及数字的格式化。示例：

```
QFile data("output.txt");
if (data.open(QFile::WriteOnly | QFile::Truncate)) {
	QTextStream out(&data);
	out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7;
	// 写入 "Result: 3.14 2.7 "
}
```

​	使用 QTextStream 读取控制台输入和写入控制台输出也很常见。**QTextStream 具有区域设置感知功能，将使用正确的编码自动解码标准输入。示例：**

```
QTextStream stream(stdin);
QString line;
while (stream.readLineInto(&line)) {
...
}
```

​	除了使用 QTextStream 的构造函数外，您还可以通过调用 setDevice() 或 setString() 设置 QTextStream 操作的设备或字符串。您可以通过调用 seek() 来定位到某个位置，当没有剩余数据可读取时，atEnd() 将返回 true。如果您调用 flush()，QTextStream 会将其写入缓冲区中的所有数据清空到设备中，并在设备上调用 flush()。

​	在内部，QTextStream 使用基于 Unicode 的缓冲区，QTextStream 使用 QStringConverter 自动支持不同的编码。默认情况下，UTF-8 用于读取和写入，但您也可以通过调用 setEncoding() 设置编码。还支持自动 Unicode 检测。启用此功能（默认行为）后，QTextStream 将检测 UTF-8、UTF-16 或 UTF-32 BOM（字节顺序标记），并在读取时切换到适当的 UTF 编码。 QTextStream 默认不写入 BOM，但您可以通过调用 setGenerateByteOrderMark(true) 来启用此功能。当 QTextStream 直接对 QString 进行操作时，编码将被禁用。

1. 读取文本文件时，有三种使用 QTextStream 的常规方法：

2. 逐块读取，通过调用 readLine() 或 readAll()。

3. 逐字读取。QTextStream 支持流式传输到 QStrings、QByteArrays 和 char* 缓冲区。单词以空格分隔，并自动跳过前导空格。


​	逐字符读取，通过流式传输到 QChar 或 char 类型。此方法通常用于在解析文件时方便地处理输入，与字符编码和行尾语义无关。要跳过空格，请调用 skipWhiteSpace()。
​	由于文本流使用缓冲区，因此您不应使用超类的实现从流中读取。例如，如果您有一个 QFile 并且直接使用 QFile::readLine() 而不是使用流从中读取，则文本流的内部位置将与文件的位置不同步。

​	默认情况下，当从文本流中读取数字时，QTextStream 将自动检测数字的基数表示。例如，如果数字以“0x”开头，则假定它是十六进制形式。如果它以数字 1-9 开头，则假定它是十进制形式，依此类推。您可以通过调用 setIntegerBase() 来设置整数基数，从而禁用自动检测。示例：

```
QTextStream in("0x50 0x20");
int firstNumber, secondNumber;

in >> firstNumber; // firstNumber == 80
in >> dec >> secondNumber; // secondNumber == 0

char ch;
in >> ch; // ch == 'x'
```

​	QTextStream 支持多种用于生成文本的格式化选项。您可以通过调用 setFieldWidth() 和 setPadChar() 来设置字段宽度和填充字符。使用 setFieldAlignment() 设置每个字段内的对齐方式。对于实数，调用 setRealNumberNotation() 和 setRealNumberPrecision() 来设置所生成数字的符号（SmartNotation、ScientificNotation、FixedNotation）和数字精度。一些额外的数字格式化选项也可通过 setNumberFlags() 获得。

​	与标准 C++ 库中的 `<iostream>` 一样，QTextStream 还定义了几个全局操纵器函数：

| **操纵器**            | **描述**                                           | **对应的函数或功能**                               |
| --------------------- | -------------------------------------------------- | -------------------------------------------------- |
| `Qt::bin`             | 设置输出为二进制格式                               | `setIntegerBase(2)`                                |
| `Qt::oct`             | 设置输出为八进制格式                               | `setIntegerBase(8)`                                |
| `Qt::dec`             | 设置输出为十进制格式                               | `setIntegerBase(10)`                               |
| `Qt::hex`             | 设置输出为十六进制格式                             | `setIntegerBase(16)`                               |
| `Qt::showbase`        | 显示进制的基数（例如 0x 用于十六进制，0 为八进制） | `setNumberFlags(numberFlags()                      |
| `Qt::forcesign`       | 强制显示符号，即使是正数也显示 "+"                 | `setNumberFlags(numberFlags()                      |
| `Qt::forcepoint`      | 强制显示小数点，即使数字为整数                     | `setNumberFlags(numberFlags()                      |
| `Qt::noshowbase`      | 取消显示进制的基数                                 | `setNumberFlags(numberFlags() & ~ShowBase)`        |
| `Qt::noforcesign`     | 取消强制显示符号                                   | `setNumberFlags(numberFlags() & ~ForceSign)`       |
| `Qt::noforcepoint`    | 取消强制显示小数点                                 | `setNumberFlags(numberFlags() & ~ForcePoint)`      |
| `Qt::uppercasebase`   | 显示大写进制符号（例如十六进制的基数 "0X"）        | `setNumberFlags(numberFlags() | UppercaseDigits) ` |
| `Qt::uppercasedigits` | 显示大写数字（例如十六进制的 "A" 到 "F"）          | `setNumberFlags(numberFlags() | LowercaseDigit `   |
| `Qt::lowercasebase`   | 显示小写进制符号（例如十六进制的基数 "0x"）        | `setNumberFlags(numberFlags() & ~UppercaseBase)`   |
| `Qt::lowercasedigits` | 显示小写数字（例如十六进制的 "a" 到 "f"）          | `setNumberFlags(numberFlags() & ~UppercaseDigits)` |
| `Qt::fixed`           | 设置输出为定点格式（不使用科学计数法）             | `setRealNumberNotation(FixedNotation)`             |
| `Qt::scientific`      | 设置输出为科学计数法格式                           | `setRealNumberNotation(ScientificNotation)`        |
| `Qt::left`            | 设置输出为左对齐                                   | `setFieldAlignment(AlignLeft)`                     |
| `Qt::right`           | 设置输出为右对齐                                   | `setFieldAlignment(AlignRight)`                    |
| `Qt::center`          | 设置输出为居中对齐                                 | `setFieldAlignment(AlignCenter)`                   |
| `Qt::endl`            | 输出换行符并刷新流                                 | `operator<<('\n')` 和 `flush()`                    |
| `Qt::flush`           | 刷新流                                             | `flush()`                                          |
| `Qt::reset`           | 重置流的状态                                       | `reset()`                                          |
| `Qt::ws`              | 跳过所有空白字符                                   | `skipWhiteSpace()`                                 |
| `Qt::bom`             | 设置流生成字节序标记（BOM）                        | `setGenerateByteOrderMark(true)`                   |


此外，Qt 提供了三个接受参数的全局操作符：qSetFieldWidth()、qSetPadChar() 和 qSetRealNumberPrecision()。

#### API

| **函数名称**                                                 | **用途**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QTextStream()`                                              | 构造一个未初始化的 `QTextStream` 对象，后续可绑定设备、字节数组或字符串。 |
| `QTextStream(QIODevice *device)`                             | 使用指定的 `QIODevice` 构造 `QTextStream`，用于读取或写入文件或其他设备的数据流。 |
| `QTextStream(FILE *fileHandle, QIODeviceBase::OpenMode openMode = ReadWrite)` | 使用标准 C 文件指针 (`FILE*`) 构造，用于兼容 C 文件操作。    |
| `QTextStream(QByteArray *array, QIODeviceBase::OpenMode openMode = ReadWrite)` | 使用一个可写字节数组作为目标，用于流式写入数据。             |
| `QTextStream(QString *string, QIODeviceBase::OpenMode openMode = ReadWrite)` | 使用一个字符串作为目标或数据源，适合流式操作字符串内容。     |
| `bool atEnd() const`                                         | 检查流是否到达数据的结尾，返回 `true` 表示数据已读完。       |
| `bool autoDetectUnicode() const`                             | 检查是否启用了自动检测 Unicode 字符集，可用于处理多种编码格式的数据流。 |
| `QIODevice *device() const`                                  | 返回当前绑定的 `QIODevice`，用于确认流操作的数据目标。       |
| `void setDevice(QIODevice *device)`                          | 设置或更改流绑定的设备，如文件或网络套接字。                 |
| `QString read(qint64 maxlen)`                                | 从流中读取最多 `maxlen` 个字符，返回读取的字符串。           |
| `QString readAll()`                                          | 读取流中所有剩余内容，适合读取完整的小文件或数据片段。       |
| `QString readLine(qint64 maxlen = 0)`                        | 读取一行内容，若未指定 `maxlen`，则读取到换行符或流末尾为止。 |
| `bool readLineInto(QString *line, qint64 maxlen = 0)`        | 将读取的行内容直接存入 `line`，可指定最大读取长度，适合逐行处理文本文件。 |
| `void flush()`                                               | 刷新流，将缓存中的数据写入目标设备，确保数据即时存储到文件或设备中。 |
| `int fieldWidth() const`                                     | 获取字段宽度设置，字段宽度决定格式化输出时的最小宽度。       |
| `void setFieldWidth(int width)`                              | 设置字段宽度，适合对齐或格式化输出内容。                     |
| `QStringConverter::Encoding encoding() const`                | 获取当前流的编码格式（如 UTF-8 或 Latin1）。                 |
| `void setEncoding(QStringConverter::Encoding encoding)`      | 设置流的编码格式，用于处理不同的字符编码数据。               |
| `QChar padChar() const`                                      | 获取用于填充字段宽度的字符，默认为空格。                     |
| `void setPadChar(QChar ch)`                                  | 设置填充字段宽度的字符，用于格式化输出对齐。                 |
| `void skipWhiteSpace()`                                      | 跳过流中所有空白字符（如空格、换行符等），适合处理连续格式化数据时的跳过操作。 |
| `int realNumberPrecision() const`                            | 获取实数输出的精度，用于指定小数点后保留的位数。             |
| `void setRealNumberPrecision(int precision)`                 | 设置实数输出的精度，适合科学计算或需要控制显示精度的场景。   |
| `void setStatus(QTextStream::Status status)`                 | 设置流状态，用于标识流操作中出现的错误类型（如读取失败或数据损坏）。 |
| `QString *string() const`                                    | 返回与流关联的字符串对象（如果流绑定了字符串）。             |
| `bool seek(qint64 pos)`                                      | 将流的读写位置移动到指定的字节偏移量，适合随机访问流内容。   |
| `bool generateByteOrderMark() const`                         | 检查是否生成字节序标记（BOM），BOM 用于标识文件的编码顺序，常见于 UTF-8 文件。 |
| `void setGenerateByteOrderMark(bool generate)`               | 设置是否生成 BOM，适合处理跨平台编码一致性的场景。           |

### QDataStream


​	数据流是编码信息的二进制流，完全独立于主机的操作系统、CPU 或字节顺序。例如，Windows 下的 PC 写入的数据流可以由运行 Solaris 的 Sun SPARC 读取。您还可以使用数据流读取/写入原始未编码的二进制数据。如果您想要“解析”输入流，请参阅 QTextStream。

​	QDataStream 类实现了 C++ 基本数据类型（如 char、short、int、char * 等）的序列化。通过将数据分解为原始单元来实现更复杂数据的序列化。

​	数据流与 QIODevice 紧密配合。QIODevice 表示可以从中读取数据和向其中写入数据的输入/输出介质。QFile 类是 I/O 设备的一个示例。

```
QFile file("file.dat");
file.open(QIODevice::WriteOnly);
QDataStream out(&file); // 我们将数据序列化到文件中
out << QString("the answer is"); // 序列化字符串
out << (qint32)42; // 序列化整数
```

示例（从流中读取二进制数据）：

```
QFile file("file.dat");
file.open(QIODevice::ReadOnly);
QDataStream in(&file); // 从文件中读取序列化的数据
QString str;
qint32 a;
in >> str >> a; // 提取“the answer is”和 42
```

​	写入流中的每个项目都以预定义的二进制格式写入，该格式因项目的类型而异。支持的 Qt 类型包括 QBrush、QColor、QDateTime、QFont、QPixmap、QString、QVariant 等。有关支持数据流的所有 Qt 类型的完整列表，请参阅序列化 Qt 数据类型。

​	对于整数，最好始终转换为 Qt 整数类型进行写入，并读回相同的 Qt 整数类型。这样可以确保您获得所需大小的整数，并使您免受编译器和平台差异的影响。

​	枚举可以通过 QDataStream 序列化，而无需手动定义流式操作符。枚举类使用声明的大小进行序列化。

​	初始 I/O 设备通常在构造函数中设置，但可以使用 setDevice() 进行更改。如果您已到达数据的末尾（或者没有设置 I/O 设备），atEnd() 将返回 true。

#### 序列化容器和字符串

​	序列化格式首先是长度说明符，然后是 l 字节的数据。如果版本小于 6.7 或元素数量小于 0xfffffffe（2^32 -2），则长度说明符为一个 quint32。否则，有一个扩展值 0xfffffffe，后跟一个带有实际值的 quint64。此外，对于支持 isNull() 的容器，它被编码为单个 quint32，所有位均已设置且无数据。

​	举一个例子，如果字符串大小适合 32 位，则 char * 字符串被写为一个 32 位整数，等于字符串的长度，包括 '\0' 字节，后跟字符串的所有字符，包括 '\0' 字节。如果字符串大小更大，则写入值 0xffffffffe 作为扩展大小的标记，后跟 64 位实际大小。读取 char * 字符串时，首先读取 4 个字节。如果值不等于 0xffffffffe（扩展大小的标记），则这 4 个字节被视为字符串的 32 位大小。否则，读取接下来的 8 个字节并将其视为字符串的 64 位大小。然后，读取 char * 字符串的所有字符，包括 '\0' 终止符。

#### 版本控制

​	QDataStream 的二进制格式自 Qt 1.0 以来一直在演变，并且可能会继续演变以反映 Qt 中所做的更改。输入或输出复杂类型时，确保使用相同版本的流 (version()) 进行读取和写入非常重要。如果您需要向前和向后兼容，您可以在应用程序中硬编码版本号：

```
stream.setVersion(QDataStream::Qt_4_0);
```

​	如果您正在生成新的二进制数据格式，例如应用程序创建的文档的文件格式，则可以使用 QDataStream 以可移植格式写入数据。通常，您会编写一个简短的标头，其中包含一个魔术字符串和一个版本号，以便为将来的扩展留出空间。例如：

```
QFile file("file.xxx");
file.open(QIODevice::WriteOnly);
QDataStream out(&file);

// 写入带有“魔法数字”和版本的标头
out << (quint32)0xA0B0C0D0;
out << (qint32)123;

out.setVersion(QDataStream::Qt_4_0);

// 写入数据
out << lots_of_interesting_data;
然后使用以下命令将其读入：

QFile file("file.xxx");
file.open(QIODevice::ReadOnly);
QDataStream in(&file);

// 读取并检查标头
quint32 magic;
in >> magic;
if (magic != 0xA0B0C0D0)
return XXX_BAD_FILE_FORMAT;

// 读取版本
qint32 version;
in >> version;
if (version < 100)
return XXX_BAD_FILE_TOO_OLD;
if (version > 123)
return XXX_BAD_FILE_TOO_NEW;

if (version <= 110)
in.setVersion(QDataStream::Qt_3_2);
else
in.setVersion(QDataStream::Qt_4_0);

// 读取数据
in >> lots_of_interesting_data;
if(version >= 120)
in >> data_new_in_XXX_version_1_2;
in >> other_interesting_data;
```

​	您可以选择序列化数据时使用的字节顺序。默认设置是大端序（MSB 优先）。将其更改为小端序会破坏可移植性（除非读取器也更改为小端序）。除非您有特殊要求，否则我们建议保留此设置。

#### 读取和写入原始二进制数据

​	您可能希望直接从数据流读取/写入您自己的原始二进制数据。可以使用 readRawData() 将数据从流中读入预分配的 char *。同样，可以使用 writeRawData() 将数据写入流。请注意，任何数据的编码/解码都必须由您完成。

​	一对类似的函数是 readBytes() 和 writeBytes()。它们与原始对应项的区别如下：readBytes() 读取一个 quint32，该 quint32 被视为要读取的数据的长度，然后将该字节数读入预分配的 char *；writeBytes() 写入一个包含数据长度的 quint32，后面跟着数据。请注意，任何数据的编码/解码（除长度 quint32 之外）都必须由您完成。

#### 读取和写入 Qt 集合类

Qt 容器类也可以序列化为 QDataStream。这些包括 QList、QSet、QHash 和 QMap。流运算符被声明为类的非成员。

#### 读取和写入其他 Qt 类

​	除了此处记录的重载流运算符之外，您可能想要序列化为 QDataStream 的任何 Qt 类都将具有适当的流运算符，这些运算符被声明为类的非成员：

```
QDataStream &operator<<(QDataStream &, const QXxx &);
QDataStream &operator>>(QDataStream &, QXxx &);
```

​	例如，以下是声明为 QImage 类的非成员的流运算符：

```
QDataStream &operator<<(QDataStream &stream, const QImage &image);
QDataStream &operator>>(QDataStream &stream, QImage &image);
```

​	要查看您最喜欢的 Qt 类是否定义了类似的流运算符，请查看类文档页面的相关非成员部分。

#### 使用读取事务

​	当数据流在异步设备上运行时，数据块可以在任意时间点到达。 QDataStream 类实现了一种事务机制，该机制提供了使用一系列流运算符原子读取数据的能力。 例如，您可以通过使用连接到 readyRead() 信号的插槽中的事务来处理来自套接字的不完整读取：

```
in.startTransaction();
QString str;
qint32 a;
in >> str >> a; // 尝试原子读取数据包

if (!in.commitTransaction())
return; // 等待更多数据
```

​	如果没有收到完整的数据包，此代码会将流恢复到初始位置，之后您需要等待更多数据到达。

#### 损坏和安全

​	QDataStream 无法抵御损坏的数据输入，因此不应将其用于安全敏感的情况，即使使用事务也是如此。事务将有助于确定当前是否可以使用异步设备上当前可用的数据解码有效输入，但会假定可用数据格式正确。

​	此外，许多 QDataStream 解组运算符将根据流中找到的信息分配内存。这些运算符不会验证请求的内存量是否合理或是否与流中可用的数据量兼容（例如：解组 QByteArray 或 QString 可能会看到分配几 GB 数据的请求）。

​	QDataStream 不应用于来源不可信的内容。应用程序应设计为尝试仅解码那些来源至少与应用程序本身或其插件一样可信的流。

#### API

### `QDataStream` 类

#### **Public Types**

| **枚举类型**             | **描述**                     |
| ------------------------ | ---------------------------- |
| `ByteOrder`              | 枚举类型，表示字节序。       |
| - `BigEndian`            | 大端字节序（最高字节在前）   |
| - `LittleEndian`         | 小端字节序（最低字节在前）   |
| `FloatingPointPrecision` | 枚举类型，表示浮点数精度。   |
| - `SinglePrecision`      | 单精度浮点数                 |
| - `DoublePrecision`      | 双精度浮点数                 |
| `Status`                 | 枚举类型，表示数据流的状态。 |
| - `Ok`                   | 状态正常                     |
| - `ReadPastEnd`          | 读取超出末尾                 |
| - `ReadCorruptData`      | 读取数据损坏                 |
| - `WriteFailed`          | 写入失败                     |
| - `SizeLimitExceeded`    | 超出大小限制                 |
| `Version`                | 枚举类型，表示 Qt 的版本。   |

#### **Public Functions**

| **函数名**                                                   | **描述**                                                  |
| ------------------------------------------------------------ | --------------------------------------------------------- |
| `QDataStream()`                                              | 默认构造函数                                              |
| `QDataStream(QIODevice *d)`                                  | 构造函数，接受一个 `QIODevice` 作为数据流的输入输出设备。 |
| `QDataStream(const QByteArray &a)`                           | 构造函数，接受一个 `QByteArray` 作为数据流的输入。        |
| `QDataStream(QByteArray *a, QIODeviceBase::OpenMode mode)`   | 构造函数，接受一个 `QByteArray` 指针和打开模式。          |
| `~QDataStream()`                                             | 析构函数                                                  |
| `void abortTransaction()`                                    | 中止事务                                                  |
| `bool atEnd() const`                                         | 检查数据流是否已经到达结尾。                              |
| `QDataStream::ByteOrder byteOrder() const`                   | 获取当前数据流的字节序。                                  |
| `bool commitTransaction()`                                   | 提交当前事务                                              |
| `QIODevice * device() const`                                 | 获取与数据流相关联的设备。                                |
| `QDataStream::FloatingPointPrecision floatingPointPrecision() const` | 获取当前的浮点数精度设置。                                |
| `QDataStream & readBytes(char *&s, qint64 &l)`               | 从数据流中读取原始字节数据。                              |
| `qint64 readRawData(char *s, qint64 len)`                    | 从数据流中读取指定长度的原始数据。                        |
| `void resetStatus()`                                         | 重置数据流的状态。                                        |
| `void rollbackTransaction()`                                 | 回滚当前事务                                              |
| `void setByteOrder(QDataStream::ByteOrder bo)`               | 设置数据流的字节序。                                      |
| `void setDevice(QIODevice *d)`                               | 设置与数据流关联的设备。                                  |
| `void setFloatingPointPrecision(QDataStream::FloatingPointPrecision precision)` | 设置浮点数精度。                                          |
| `void setStatus(QDataStream::Status status)`                 | 设置数据流的状态。                                        |
| `void setVersion(int v)`                                     | 设置数据流的版本。                                        |
| `qint64 skipRawData(qint64 len)`                             | 跳过指定长度的原始数据。                                  |
| `void startTransaction()`                                    | 启动事务                                                  |
| `QDataStream::Status status() const`                         | 获取当前数据流的状态。                                    |
| `int version() const`                                        | 获取数据流的版本号。                                      |
| `QDataStream & writeBytes(const char *s, qint64 len)`        | 将字节数据写入数据流。                                    |
| `qint64 writeRawData(const char *s, qint64 len)`             | 将原始数据写入数据流。                                    |

#### **操作符重载**

| **操作符**                                      | **描述**                               |
| ----------------------------------------------- | -------------------------------------- |
| `QDataStream & operator<<(qint8 i)`             | 将 `qint8` 类型的数据写入数据流。      |
| `QDataStream & operator<<(bool i)`              | 将 `bool` 类型的数据写入数据流。       |
| `QDataStream & operator<<(char16_t c)`          | 将 `char16_t` 类型的数据写入数据流。   |
| `QDataStream & operator<<(char32_t c)`          | 将 `char32_t` 类型的数据写入数据流。   |
| `QDataStream & operator<<(const char *s)`       | 将 C 字符串写入数据流。                |
| `QDataStream & operator<<(double f)`            | 将 `double` 类型的数据写入数据流。     |
| `QDataStream & operator<<(float f)`             | 将 `float` 类型的数据写入数据流。      |
| `QDataStream & operator<<(qint16 i)`            | 将 `qint16` 类型的数据写入数据流。     |
| `QDataStream & operator<<(qint32 i)`            | 将 `qint32` 类型的数据写入数据流。     |
| `QDataStream & operator<<(qint64 i)`            | 将 `qint64` 类型的数据写入数据流。     |
| `QDataStream & operator<<(quint16 i)`           | 将 `quint16` 类型的数据写入数据流。    |
| `QDataStream & operator<<(quint32 i)`           | 将 `quint32` 类型的数据写入数据流。    |
| `QDataStream & operator<<(quint64 i)`           | 将 `quint64` 类型的数据写入数据流。    |
| `QDataStream & operator<<(quint8 i)`            | 将 `quint8` 类型的数据写入数据流。     |
| `QDataStream & operator<<(std::nullptr_t ptr)`  | 将空指针写入数据流。                   |
| `QDataStream & operator>>(bool &i)`             | 从数据流中读取 `bool` 类型的数据。     |
| `QDataStream & operator>>(qint8 &i)`            | 从数据流中读取 `qint8` 类型的数据。    |
| `QDataStream & operator>>(char *&s)`            | 从数据流中读取 C 字符串。              |
| `QDataStream & operator>>(char16_t &c)`         | 从数据流中读取 `char16_t` 类型的数据。 |
| `QDataStream & operator>>(char32_t &c)`         | 从数据流中读取 `char32_t` 类型的数据。 |
| `QDataStream & operator>>(double &f)`           | 从数据流中读取 `double` 类型的数据。   |
| `QDataStream & operator>>(float &f)`            | 从数据流中读取 `float` 类型的数据。    |
| `QDataStream & operator>>(qint16 &i)`           | 从数据流中读取 `qint16` 类型的数据。   |
| `QDataStream & operator>>(qint32 &i)`           | 从数据流中读取 `qint32` 类型的数据。   |
| `QDataStream & operator>>(qint64 &i)`           | 从数据流中读取 `qint64` 类型的数据。   |
| `QDataStream & operator>>(quint16 &i)`          | 从数据流中读取 `quint16` 类型的数据。  |
| `QDataStream & operator>>(quint32 &i)`          | 从数据流中读取 `quint32` 类型的数据。  |
| `QDataStream & operator>>(quint64 &i)`          | 从数据流中读取 `quint64` 类型的数据。  |
| `QDataStream & operator>>(quint8 &i)`           | 从数据流中读取 `quint8` 类型的数据。   |
| `QDataStream & operator>>(std::nullptr_t &ptr)` | 从数据流中读取空指针。                 |
