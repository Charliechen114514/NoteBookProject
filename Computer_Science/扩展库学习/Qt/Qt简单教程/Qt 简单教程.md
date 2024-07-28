# Qt 简单教程

## 1：框架概述

### 所有模块

#### Qt的基础模块

​		Qt Essentials 定义了所有平台上 Qt 的基础。它们可在所有受支持的开发平台和经过测试的目标平台上使用。除了测试模块将保持源代码兼容之外，这些模块将在整个 Qt 6 中保持源代码和二进制兼容。

​		基本模块是通用的，可以使用在大多数 Qt 应用程序。用于特殊目的的模块被视为附加模块，即它在所有支持的平台上都可用。

​		下表列出了 Qt 要点：

|                             模块                             |                             描述                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| [Qt Core](https://doc-qt-io.translate.goog/qt-6/qtcore-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                 其他模块使用的核心非图形类。                 |
| [Qt D-Bus](https://doc-qt-io.translate.goog/qt-6/qtdbus-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |             通过 D-Bus 协议进行进程间通信的类。              |
| [Qt GUI](https://doc-qt-io.translate.goog/qt-6/qtgui-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |               图形用户界面 (GUI) 组件的基类。                |
| [Qt Network](https://doc-qt-io.translate.goog/qt-6/qtnetwork-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                使网络编程更容易、更便携的类。                |
| [Qt QML](https://doc-qt-io.translate.goog/qt-6/qtqml-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                 QML 和 JavaScript 语言的类。                 |
| [Qt Quick](https://doc-qt-io.translate.goog/qt-6/qtquick-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |  用于构建具有自定义用户界面的高度动态应用程序的声明性框架。  |
| [Qt Quick Controls](https://doc-qt-io.translate.goog/qt-6/qtquickcontrols-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | 提供轻量级 QML 类型，用于为桌面、嵌入式和移动设备创建高性能用户界面。这些类型采用简单的样式架构并且非常高效。 |
| [Qt Quick Dialogs](https://doc-qt-io.translate.goog/qt-6/qtquickdialogs-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |   用于从 Qt Quick 应用程序创建系统对话框并与之交互的类型。   |
| [Qt Quick Layouts](https://doc-qt-io.translate.goog/qt-6/qtquicklayouts-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |   布局是用于在用户界面中排列基于 Qt Quick 2 的项目的项目。   |
| [Qt Quick Test](https://doc-qt-io.translate.goog/qt-6/qtquicktest-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | QML 应用程序的单元测试框架，其中测试用例编写为 JavaScript 函数。**注意：**二进制兼容性保证不适用于 Qt Quick Test。但是，它将保持源兼容。 |
| [Qt Test](https://doc-qt-io.translate.goog/qt-6/qttest-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | 用于单元测试 Qt 应用程序和库的类。**注意：**二进制兼容性保证不适用于 Qt Test。但是，它将保持源兼容。 |
| [Qt Widgets](https://doc-qt-io.translate.goog/qt-6/qtwidgets-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |              使用 C++ 小部件扩展 Qt GUI 的类。               |

#### Qt 附加组件

​		Qt 附加模块为特定目的带来附加价值。这些模块可能仅在某些开发平台上可用。许多附加模块要么功能齐全并且存在向后兼容性，要么仅适用于某些平台。每个附加模块分别指定其兼容性承诺。

​		下表列出了 Qt 附加组件：

|                             模块                             |                           开发平台                           |                           目标平台                           |                             描述                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| [Active Qt](https://doc-qt-io.translate.goog/qt-6/activeqt-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | [Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | [Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |              使用 ActiveX 和 COM 的应用程序的类              |
| [Qt 3D](https://doc-qt-io.translate.goog/qt-6/qt3d-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |           支持 2D 和 3D 渲染的近实时模拟系统功能。           |
| [Qt 5 Core Compatibility APIs](https://doc-qt-io.translate.goog/qt-6/qtcore5-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |         Qt 5 中存在但 Qt 6 中不存在的 Qt 核心 API。          |
| [Qt Bluetooth](https://doc-qt-io.translate.goog/qt-6/qtbluetooth-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Android](https://doc-qt-io.translate.goog/qt-6/android.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[iOS](https://doc-qt-io.translate.goog/qt-6/ios.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Boot to Qt](https://doc-qt-io.translate.goog/Boot2Qt/?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                    提供对蓝牙硬件的访问。                    |
| [Qt Concurrent](https://doc-qt-io.translate.goog/qt-6/qtconcurrent-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |         用于编写多线程程序而不使用低级线程原语的类。         |
| [Qt Help](https://doc-qt-io.translate.goog/qt-6/qthelp-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |               用于将文档集成到应用程序中的类。               |
| [Qt Image Formats](https://doc-qt-io.translate.goog/qt-6/qtimageformats-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |          其他图像格式的插件：TIFF、MNG、TGA、WBMP。          |
| [Qt Multimedia](https://doc-qt-io.translate.goog/qt-6/qtmultimedia-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                            全部*                             | 一组丰富的 QML 类型和 C++ 类，用于处理多媒体内容。还包括处理相机访问的 API。 |
| [Qt NFC](https://doc-qt-io.translate.goog/qt-6/qtnfc-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Android](https://doc-qt-io.translate.goog/qt-6/android.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[iOS](https://doc-qt-io.translate.goog/qt-6/ios.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | 提供对近场通信 (NFC) 硬件的访问。在桌面平台上，仅支持类型 4 标签的 NDEF 访问。 |
| [Qt OPC UA](https://doc-qt-io.translate.goog/qt-6/qtopcua-overview.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                所有（QNX、WebAssembly 除外）                 |             工业应用中数据建模和数据交换的协议。             |
| [Qt OpenGL](https://doc-qt-io.translate.goog/qt-6/qtopengl-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | C++ 类可以让您在 Qt 应用程序中轻松使用 OpenGL。一个单独的库[Qt OpenGL Widgets C++ Classes](https://doc-qt-io.translate.goog/qt-6/qtopenglwidgets-module.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)提供用于渲染 OpenGL 图形的小部件。 |
| [Qt PDF](https://doc-qt-io.translate.goog/qt-6/qtpdf-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 和[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。 |                用于渲染 PDF 文档的类和函数。                 |
| [Qt Positioning](https://doc-qt-io.translate.goog/qt-6/qtpositioning-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Android](https://doc-qt-io.translate.goog/qt-6/android.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[iOS](https://doc-qt-io.translate.goog/qt-6/ios.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |           提供对位置、卫星信息和区域监控类的访问。           |
| [Qt Print Support](https://doc-qt-io.translate.goog/qt-6/qtprintsupport-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                       全部（iOS 除外）                       |                  使打印更容易、更便携的类。                  |
| [Qt Quick Widgets](https://doc-qt-io.translate.goog/qt-6/qtquickwidgets-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |       提供用于显示 Qt Quick 用户界面的 C++ 小部件类。        |
| [Qt Quick Effects](https://doc-qt-io.translate.goog/qt-6/qtquick-effects-qmlmodule.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 提供 QML 类型，用于将一种或多种简单的图形效果应用于 Qt Quick 项目。 |
| [Qt Quick Particles](https://doc-qt-io.translate.goog/qt-6/qtquick-particles-qmlmodule.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |                  提供粒子效果的 QML 类型。                   |
| [Qt Remote Objects](https://doc-qt-io.translate.goog/qt-6/qtremoteobjects-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qt-remote-objects) |                             全部                             |                             全部                             | 提供了一种易于使用的共享机制[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)进程或设备之间的 API（属性/信号/槽）。 |
| [Qt SCXML](https://doc-qt-io.translate.goog/qt-6/qtscxml-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 提供用于从 SCXML 文件创建状态机并将其嵌入应用程序中的类和工具。 |
| [Qt Sensors](https://doc-qt-io.translate.goog/qt-6/qtsensors-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Android](https://doc-qt-io.translate.goog/qt-6/android.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[iOS](https://doc-qt-io.translate.goog/qt-6/ios.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                   提供对传感器硬件的访问。                   |
| [Qt Serial Bus](https://doc-qt-io.translate.goog/qt-6/qtserialbus-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Boot to Qt](https://doc-qt-io.translate.goog/Boot2Qt/?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | 提供对串行工业总线接口的访问。目前，该模块支持CAN总线和Modbus协议。 |
| [Qt Serial Port](https://doc-qt-io.translate.goog/qt-6/qtserialport-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Boot to Qt](https://doc-qt-io.translate.goog/Boot2Qt/?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |              提供与硬件和虚拟串行端口交互的类。              |
| [Qt Shader Tools](https://doc-qt-io.translate.goog/qt-6/qtshadertools-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 提供跨平台 Qt 着色器管道的工具。这些支持处理图形和计算着色器，使其可用于 Qt Quick 和 Qt 生态系统中的其他组件。 |
| [Qt Spatial Audio](https://doc-qt-io.translate.goog/qt-6/qtspatialaudio-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 提供对空间音频的支持。在 3D 空间中创建包含不同声源和房间相关属性（例如混响）的声音场景。 |
| [Qt SQL](https://doc-qt-io.translate.goog/qt-6/qtsql-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |                使用 SQL 进行数据库集成的类。                 |
| [Qt State Machine](https://doc-qt-io.translate.goog/qt-6/qtstatemachine-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |                提供用于创建和执行状态图的类。                |
| [Qt SVG](https://doc-qt-io.translate.goog/qt-6/qtsvg-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 用于显示 SVG 文件内容的类。支持的子集[SVG 1.2 Tiny](https://translate.google.com/website?sl=auto&tl=zh-CN&hl=zh-CN&client=webapp&u=http://www.w3.org/TR/SVGTiny12/)标准。一个单独的库[Qt SVG Widgets C++ Classes](https://doc-qt-io.translate.goog/qt-6/qtsvgwidgets-module.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)提供对在小部件 UI 中渲染 SVG 文件的支持。 |
| [Qt TextToSpeech](https://doc-qt-io.translate.goog/qt-6/qttexttospeech-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |      提供对从文本合成语音并将其作为音频输出播放的支持。      |
| [Qt UI Tools](https://doc-qt-io.translate.goog/qt-6/qtuitools-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 用于加载的类[QWidget](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)*在运行时在Qt Designer*中动态创建基于表单的表单。 |
| [Qt WebChannel](https://doc-qt-io.translate.goog/qt-6/qtwebchannel-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 提供访问[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)或来自 HTML 客户端的 QML 对象，用于 Qt 应用程序与 HTML/JavaScript 客户端的无缝集成。 |
| [Qt WebEngine](https://doc-qt-io.translate.goog/qt-6/qtwebengine-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 和[macOS](https://doc-qt-io.translate.goog/qt-6/macos.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。 | 使用以下方法将 Web 内容嵌入到应用程序中的类和函数[Chromium browser project](https://translate.google.com/website?sl=auto&tl=zh-CN&hl=zh-CN&client=webapp&u=http://www.chromium.org/Home)。 |
| [Qt WebSockets](https://doc-qt-io.translate.goog/qt-6/qtwebsockets-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 提供符合以下标准的 WebSocket 通信[RFC 6455](https://translate.google.com/website?sl=auto&tl=zh-CN&hl=zh-CN&client=webapp&u=https://datatracker.ietf.org/doc/html/rfc6455)。 |
| [Qt WebView](https://doc-qt-io.translate.goog/qt-6/qtwebview-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                  具有本机 Web 引擎的平台。                   | 通过使用平台本机的 API 在 QML 应用程序中显示 Web 内容，无需包含完整的 Web 浏览器堆栈。 |
| [Qt XML](https://doc-qt-io.translate.goog/qt-6/qtxml-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |            在文档对象模型 (DOM) API 中处理 XML。             |
| [Qt Charts](https://doc-qt-io.translate.goog/qt-6/qtcharts-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 用于显示视觉上令人愉悦的图表的 UI 组件，由静态或动态数据模型驱动。 |
| [Qt CoAP](https://doc-qt-io.translate.goog/qt-6/qtcoap-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |              实现 RFC 7252 定义的 CoAP 客户端。              |
| [Qt Data Visualization](https://doc-qt-io.translate.goog/qt-6/qtdatavisualization-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |         用于创建令人惊叹的 3D 数据可视化的 UI 组件。         |
| [Qt Lottie Animation](https://doc-qt-io.translate.goog/qt-6/qtlottieanimation-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             | 用于以 JSON 格式渲染图形和动画的 QML API，由[Bodymovin](https://translate.google.com/website?sl=auto&tl=zh-CN&hl=zh-CN&client=webapp&u=https://aescripts.com/bodymovin/)Adobe® After Effects 插件。 |
| [Qt MQTT](https://doc-qt-io.translate.goog/qt-6/qtmqtt-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |                  提供 MQTT 协议规范的实现。                  |
| [Qt Network Authorization](https://doc-qt-io.translate.goog/qt-6/qtnetworkauth-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |            为在线服务提供基于 OAuth 的授权支持。             |
| [Qt Quick 3D](https://doc-qt-io.translate.goog/qt-6/qtquick3d-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |    提供用于创建基于 Qt Quick 的 3D 内容或 UI 的高级 API。    |
| [Qt Quick 3D Physics](https://doc-qt-io.translate.goog/qt-6/qtquick3dphysics-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |         所有受支持的平台（QNX 和 INTEGRITY 除外）。          | Qt Quick 3D 物理提供了一个高级 QML 模块，为 Qt Quick 3D 添加了物理模拟功能。 |
| [Qt Quick Timeline](https://doc-qt-io.translate.goog/qt-6/qtquicktimeline-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             |                             全部                             |                启用基于关键帧的动画和参数化。                |
| [Qt Virtual Keyboard](https://doc-qt-io.translate.goog/qt-6/qtvirtualkeyboard-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |                             全部                             | [Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Windows](https://doc-qt-io.translate.goog/qt-6/windows.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)桌面，以及[Boot to Qt](https://doc-qt-io.translate.goog/Boot2Qt/?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)目标。 | 用于实现不同输入法以及 QML 虚拟键盘的框架。支持本地化键盘布局和自定义视觉主题。 |
| [Qt Wayland Compositor](https://doc-qt-io.translate.goog/qt-6/qtwaylandcompositor-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | [Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) | [Linux](https://doc-qt-io.translate.goog/qt-6/linux.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Boot to Qt](https://doc-qt-io.translate.goog/Boot2Qt/?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)目标。 |               提供开发 Wayland 合成器的框架。                |

​		我们在使用这些模块的时候，需要我们在qmake中手动添加

```
QT		+= module_name
```

​		的形式完成。

### 数据类型的定义

​		qt为了保证通用性，在各个平台上都定义了基本的数据类型保证长度的统一。方法是简单的：

```C++
typedef signed char qint8;
```

#### 七种基本的 C++ 数据类型

​		我们回顾一下简单的数据类型的定义

| 类型     | 关键字  |
| -------- | ------- |
| 布尔型   | bool    |
| 字符型   | char    |
| 整型     | int     |
| 浮点型   | float   |
| 双浮点型 | double  |
| 无类型   | void    |
| 宽字符型 | wchar_t |

#### 类型的变量所能存储的最大值和最小值

| 类型               | 位            | 范围                                                         |
| ------------------ | ------------- | ------------------------------------------------------------ |
| char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
| unsigned char      | 1 个字节      | 0 到 255                                                     |
| signed char        | 1 个字节      | -128 到 127                                                  |
| int                | 4 个字节      | -2147483648 到 2147483647                                    |
| unsigned int       | 4 个字节      | 0 到 4294967295                                              |
| signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
| short int          | 2 个字节      | -32768 到 32767                                              |
| unsigned short int | 2 个字节      | 0 到 65,535                                                  |
| signed short int   | 2 个字节      | -32768 到 32767                                              |
| long int           | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
| float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
| double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
| long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
| wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

- 不同平台所占字节数
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/fbb5e72169a5495f9499cffc6b44c9c3.jpg?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6bG86YWxMjMzMw==,size_20,color_FFFFFF,t_70,g_se,x_16)

#### 3.Qt中使用的数据类型

| 类型       | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| qint8      | char                                                         |
| qint16     | short int                                                    |
| qint32     | int                                                          |
| qint64     | long long int                                                |
| qintptr    | 整数类型，用于表示带符号整数中的指针（用于散列等）。qint32 或 qint64 的类型定义 |
| qlonglong  | long long int                                                |
| qptrdiff   | 用于表示指针差异的整数类型。                                 |
| qreal      | 除非 Qt 配置了 -qreal float 选项，否则为 double 类型定义。   |
| qsizetype  | 在 Qt 支持的所有平台上，该类型保证与 size_t 的大小相同。     |
| quint8     | unsigned char                                                |
| quint16    | unsigned short                                               |
| quint32    | unsigned int                                                 |
| quint64    | unsigned long long int                                       |
| quintptr   | 用于在无符号整数中表示指针的整数类型（用于散列等）。quint32 或 quint64 的类型定义 |
| qulonglong | unsigned long long int                                       |
| uchar      | unsigned char.                                               |
| uint       | unsigned int.                                                |
| ulong      | unsigned long.                                               |
| ushort     | unsigned short.                                              |
| float      | 单精度                                                       |
| double     | 双精度                                                       |

### qt宏

#### qt版本相关宏

#### **1.1 QT_VERSION**

​		这个宏展开为数值形式 0xMMNNPP (MM = major, NN = minor, PP = patch) 表示 Qt 编译器版本，例如 Qt 编译器版本为 Qt 5.9.1，则 QT_VERSION 为 0x050901。这个宏常用于条件编译设置，根据 Qt 版本不同，编译不同的代码段。

#### **1.2 QT_VERSION_CHECK**

​		这个宏展开为 Qt 版本号的一个整数表示，用于版本判断的时候条件编译，如下示例：

```cpp
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif
// QMake底层的代码就是这样的实现，检查qt版本来include
```

**1.3 QT_VERSION_STR**
这个宏展开为 Qt 版本号的字符串，用于显示

```
qDebug() << QT_VERSION_STR;
```

#### 内存字节序相关宏（内存数据使用的大小端）

**Q_BYTE_ORDER、Q_BIG_ENDIAN 和 Q_LITTLE_ENDIAN**
`Q_BYTE_ORDER` 表示系统内存中数据使用的字节序；
`Q_BIG_ENDIAN` 表示大端字节序；
`Q_LITTLE_` ENDIAN 表示小端字节序。
这几个宏在需要判断系统字节序时才会用到，使用示例如下：

```cpp
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN			//当前系统是否使用的小端
  ...
#else
  ...
#endif
```

#### 共享库相关宏定义

**3.1 Q_DECL_IMPORT**

**3.2 Q_DECL_EXPORT**

#### 虚函数重载宏

**Q_DECL_OVERRIDE**
在类定义中，用于重载一个虚函数，例如在某个类中重载虚函数 paintEvem()，可以定义如下：

```cpp
void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
```

使用 Q_DECL_OVERRIDE 宏后，如果重载的虚函数没有进行任何重载操作，编译器将会报错。

> 私人建议：不要使用这些宏，毕竟论可移植性还是override更好，事实上跟我猜测的完全一致

![image-20240103195930084](.\Qt 简单教程\image-20240103195930084.png)

#### 函数内不使用参数处理宏

**Q_UNUSED**
这个宏用于在函数中定义不在函数体里使用的参数，如果不使用该宏定义处理，编译器将会报出参数未使用的警告；宏定义使用示例如下，id不需要使用的情况：

```cpp
void MainWindow::on_imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    ui->LabInfo->setText (fileName);
}
```

​		事实上，他完全等价于:

```C++
(void)x;
```

​		这是一个老技巧了，当然现在有更好的`[[maybe_unused]]`，虽然貌似MSVC并不支持。

#### 调试类宏定义

**qDebug**
这是qt中的信息调试宏，还有其他不同等级的调试宏定义，qt中宏定义的源代码如下：

```cpp
#define qDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug
#define qInfo QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).info
#define qWarning QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).warning
#define qCritical QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).critical
#define qFatal QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).fatal
```

以上宏定义都是用于调试信息输出，使用如下：

```cpp
qDebug() << "this is a debug example";
```

**Q_FUNC_INFO**
函数信息宏，包含函数所属类和参数信息，使用如下：

```cpp
qDebug()<<Q_FUNC_INFO<<"this is a debug example";
```

该宏一般和qDebug配合使用，可用于快速定位调试信息位置。
调试信息输出如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/ebe6da52f2534f75ab22e2998d8d2adf.png)

### 元对象解释与分析

​		我们主要是讨论的QObject类。他是所有的Qt的类的父类

​		QObject 类不仅是所有 Qt 对象的基类，还是“[Qt 中的对象模型（Object Model）](https://zhuanlan.zhihu.com/p/43522035)”的核心类。我们知道元对象模型最重要的功能就是“信号-槽”机制，该机制使 Qt 对象之间可以进行无缝的交互。那么只要是 QObject 及其子类，都可以使用信号-槽机制。

**QObject 如果有父对象，必须在同一个线程中**

> *CPU的亲和性， 就是进程要在指定的 CPU 上尽量长时间地运行而不被迁移到其他处理器，也称为CPU关联性；再简单的点的描述就将制定的进程或线程绑定到相应的cpu上；在多核运行的机器上，每个CPU本身自己会有缓存，缓存着进程使用的信息，而进程可能会被OS调度到其他CPU上，如此，CPU cache命中率就低了，当绑定CPU后，程序就会一直在指定的cpu跑，不会由操作系统调度到其他CPU上，性能有一定的提高。*

​		一个 QObject 对象是具有线程亲和性（Thread Affinity）的。什么意思呢？就是这个类创建的对象收到信号或者事件的时候，处理信号的槽函数以及处理事件的某某函数也是和这个对象在一个线程中运行。也就是说，所有跟之相关的东西都必须在同一个线程处理，否则的话就会失败

​		**如果调用 moveToThread() 函数把 QObject 对象移动到其他线程了，那原来的信号可就找不到你了，那么槽函数也就不会再执行。**哦，对了，移动到其他线程也称为改变了这个对象的线程亲和性。默认情况下你在哪个线程创建 QObject 对象，那这个对象就属于哪个线程。查询 QObject 对象的亲和性用 thread() 函数。

​		因为 QObject 对象必须和父对象在同一个线程中，因此：

> - 如果两个 QObject 位于不同线程中，他们不能互相指定为父子关系，即调用 setParent() 将失败；
> - 移动 QObject 到另一个线程中，其所有子对象也都自动移过去；
> - 如果某个 QObject 对象指定了父对象，则调用 moveToThread() 函数将会失败；
> - 在 QThread::run() 中创建的 QObject 对象不能成为 QThread 对象的子对象，因为 QThread 不存在于 QThread::run() 中的线程。

**QObject 类的成员变量是否为其子对象问题**

​		根据官方文档说明，QObject 的成员变量默认不是其子对象，需要调用 setParent() 函数来手动指定，或者成员变量定义的时候构造函数中指明。否则的话，当 QObject 对象移动到其他线程后，成员变量可是不动的保留在旧的线程中。示例代码如下：

```cpp
// Widget.h
Class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QLabel *label;
}
// Widget.cpp
Widget::Widget(QWidget *parent) :
    Widget(parent)
{
    // 指定父对象的一种方法
    label = new QLabel(this);

    // 指定父对象的第二种方法
    label = new QLabel();
    label->setParent(this);
}
```

​		我们创建了一个 Widget 类，继承于 QWidget（QObject 的子类），那么 Widget 自然就是 QObject的子孙。里面有个成员变量 label，默认不是 Widget 的子对象。只有在 cpp 文件中定义时在构造函数中指定或者显示的调用 setParent() 才是 Widget 的子孙。

​		QObject是禁止拷贝赋值的，意味着所有的子类都必须使用指针操作，换而言之，我们无法使用容器直接存储，而是必须使用指针！

#### **QObject 可以干什么？**

​		和 QObject 类相关的有对象信息、信号槽、事件、计时器、线程和翻译。

**安全的删除对象 - deleteLater() 函数**

```text
// 安全析构
void deleteLater()
```

​		这个 deleteLater() 函数主要是往事件循环队列里发送一条“把我删除”的信息。那为啥不直接删除呢？因为有些时候我虽然用完这个对象了，但其他组件可能还依赖它，那么等所有事儿都干完了，控制权会回到事件循环队列中，此时再安全的删除会更好。

​		既然是往事件循环队列里插入“把我删除”，那这个函数可以多次调用没关系，反正最终只会有一个去执行。这好比 sendEvent 是立马发送事件，而 postEvent 是发送到一个队列里，postEvent 可以多次调用。类似的还有绘图中的 repaint() 和 update()，都是一样的道理。

**有信号连接/断开时我们可以做些什么？ - connectNotify等函数**

```text
// 有信号连接时自动调用的函数
virtual void connectNotify(const QMetaMethod &signal)
// 有信号断开时自动调用的函数
virtual void disconnectNotify(const QMetaMethod &signal)

// 示例
if（signal == QMetaMethod :: fromSignal（＆MyObject :: valueChanged））{
    ....
}
```

​		这个 connectNotify() 函数啊，当有别人连接到 QObject 的信号时就会被自动的调用。当然这函数是虚函数，啥都没写，所以平时你也感觉不出什么。但是如果你重新实现了这个函数的话，只要有信号连接，你就可以在这里干些什么。

**调试利器，有多少人连我啊？ - receivers() 函数**

```text
int receivers(const char *signal) const

// 示例
if (receivers(SIGNAL(valueChanged(QByteArray))) > 0) {
    ....
}
```

**到底是谁在连我？ - sender() 函数**

```text
QObject *sender() const
```

​		虽然这函数也是有悖面向对象思想，但用的地方还挺多，尤其是在 QObject 的槽函数中。比如有一个颜色面板，选择一个颜色然后设置文字颜色，肯定是信号槽形式。那我槽中怎么知道我点了哪个颜色呢？这时候在这个槽中就可以用 sender() 来确定是哪个人发出的信号传到我这里了，还是很实用的。

**我该怎么处理接收的事件？ - event() 函数**

```text
virtual bool event(QEvent *e)

// 示例：调用父类函数
if (ev->type() == QEvent::PolishRequest) {
    // 只处理 PolishRequest 事件，其他不处理
    doThings();
    return true;
} else  if (ev->type() == QEvent::Show) {
    // 不仅处理 Show 事件，其他事件交给父类处理
    doThings2();
    QWidget::event(ev);
    return true;
}

// 确保剩余的事件交给父类处理
return QWidget::event(ev);
```

​		所有的事件发生后都可以用该函数来处理。虽然 Qt 已经在这个函数中写了一些代码，但同时 Qt 把这个函数搞成 virtual 虚函数意味着我们可以自定义处理的过程。

​		你要是处理了某事件，记得返回 ture。

​		另一个需要注意的是记得调用父类的 event() 函数来避免遗漏事件。比如 Qt 已经在该函数里写了处理鼠标、处理动画、处理绘图等事件，你要是写不全，**最好是调用父类函数来处理剩余的事件**。有关 Qt 的事件处理会在以后的文章中讲解，QObject 的事件过滤器函数 eventFilter() 等就不赘述了。

**自发启动计时器 - startTimer() 函数**

```text
int startTimer(int interval, Qt::TimerType timerType = Qt::CoarseTimer)
int startTimer(std::chrono::milliseconds time, Qt::TimerType timerType = Qt::CoarseTimer)

// 示例
class MyObject : public QObject
  {
      Q_OBJECT

  public:
      MyObject(QObject *parent = 0);

  protected:
      void timerEvent(QTimerEvent *event);
  };

  MyObject::MyObject(QObject *parent)
      : QObject(parent)
  {
      startTimer(50);     // 50-millisecond timer
      startTimer(1000);   // 1-second timer
      startTimer(60000);  // 1-minute timer

      using namespace std::chrono;
      startTimer(milliseconds(50));
      startTimer(seconds(1));
      startTimer(minutes(1));

      // since C++14 we can use std::chrono::duration literals, e.g.:
      startTimer(100ms);
      startTimer(5s);
      startTimer(2min);
      startTimer(1h);
  }

  void MyObject::timerEvent(QTimerEvent *event)
  {
      qDebug() << "Timer ID:" << event->timerId();
  }
```

一般我们用 QTimer 类来创建个计时器，QTimer 本身就是 QObejct 的子类。其实 QObject 本身就自带计时器功能，调用 startTimer() 函数就启动了，而每一次的计时动作都会发出 QTimerEvent 事件。这样你可以重新实现 timerEvent() 函数来决定每一次的计时想要干什么。

终止计时器的函数是 killTimer()。

**国际化必备 - tr() 函数**

```cpp
QString tr(const char *sourceText, const char *disambiguation = Q_OBJECT, int n = Q_OBJECT)

// 示例
void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    ...
}
```

## **相关的宏**

- 启用 Meta-System 一系列功能：Q_OBJECT
- 配置属性：Q_PROPERTY(...)
- 禁止缩窄转换：QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
- 设置类的额外信息：Q_CLASSINFO(Name, Value)
- 禁用拷贝构造函数、赋值操作符：Q_DISABLE_COPY(Class)
- 第三方使用信号槽：Q_EMIT
- 第三方使用信号：Q_SIGNAL/Q_SIGNALS
- 第三方使用槽函数：Q_SLOT/Q_SLOTS
- 向 Meta-System 注册枚举：Q_ENUM( ...)/Q_ENUM_NS( ...)
- 向 Meta-System 注册flag：Q_FLAG( ...)/Q_FLAG_NS( ...)
- 轻量级 Q_OBJECT：Q_GADGET
- 向 Qt 标记实现了哪些接口：Q_INTERFACES( ...)
- 向 Meta-System 注册方法函数：Q_INVOKABLE
- 给某个函数加个版本：Q_REVISION
- 设置对象名：Q_SET_OBJECT_NAME(Object)