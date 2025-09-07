# Qt中的设计模式：经典的MVC，MVP和MVVM

## 前言

​	笔者这里最近正在研究经典的三大 Model/View 框架，不得不说，我先前的确写过Qt在这里的体现，但是，笔者认为之前的文章中，我只是机械的memcpy的Qt的阐述，理解不够深刻，最近的工程经验让我慢慢开始仔细的评估自己编写和组织工程的条例和逻辑。慢慢体会到MVC，MVP和MVVM这些架构的不同点。这里，笔者先将过去笔者的五篇翻译+重述的文章放到这里，供对Qt具体实现感兴趣的朋友参考一下：

> [Qt中的Model与View（Qt官网翻译版）_qtmodeler中文版-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/143460640)
>
> [Qt中的Model与View 2_qt setselectionmodel-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/143460780)
>
> [Qt中的Model与View 3：从样例出发理解QStringListModel和QListView_qlistview与什么model-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/143461288)
>
> [Qt中的Model与View 4：QStandardItemModel与QTableView_qtableview model-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/143462433)
>
> [Qt中的Model与View5: QStyledItemDelegate_qt mdv模式 qstyleditemdelegate-CSDN博客](https://blog.csdn.net/charlie114514191/article/details/143462660)

## 在那之前，先仔细聊聊MVC MVVM MVP模式

​	Qt在介绍自己的MVC抽象的时候就已经谈到了咱们的MVC，

- M：Model，实际上的后端数据，换而言之，Model是干货，是准备被展示的数据的存储处理中心。咱们开餐馆的中，M你可以认为就是纯厨房
- V：View，实际上展示的前端数据，换而言之，咱们天天设计可以直观看到的界面就是View在发力，我们通过一定的方式将Model的东西传过来，View结合自己的逻辑把这些东西亮出来给别人看，另一方面，他又要收集前端的交互，把用户的想法和修改的内容传递回去Model，这就是View起到的作用
- C：Controller，我们知道UI前端和数据后端打交道，显然要有桥接，三种模式的变种就在这里做出来差异的，这里既然是MVC，这里的C就是控制器Controller，负责把咱们的M和V串联起来。

> 如果上面的例子让你抓耳挠腮，请看伟大的GPT怎么说呢：
>
> 想象你走进一家餐厅：
>
> - **顾客（User）**：提出需求（我要一份牛排）。
> - **服务员（View）**：把顾客的要求记录、把菜上到桌上，是和顾客直接打交道的人。
> - **厨房（Model）**：真正做菜的地方，有配方、存货、厨师（业务逻辑与数据）。
> - **领班/经理（Controller/Presenter/ViewModel）**：负责把服务员和厨房协调起来，保证点菜、出菜、上菜都顺利进行。
>
> 不同的架构就是这家餐厅里“谁当经理”、“服务员该多聪明”、“信息流怎样跑”的不同组织方式。

## MVC是如何工作的？

​	在前面我们聊MVC依次是什么的时候，咱们就已经大致勾勒出来了MVC的工作框架了。

> 1. 用户在 View 上点击“下单”。
> 2. View 将事件传给 Controller。
> 3. Controller 调用 Model 去处理（比如在数据库写入订单）。
> 4. Model 改变后，通常 Controller 会通知 View 去刷新显示（或者 View 自己查询 Model）。
>
> 需要注意是：经典的MVC中View不是完全被动的，可以直接读取/观察 Model（实现方式有多种），所以 View 有时并非完全被动。交互的逻辑全部放到了Controller 是主动的中介，负责解释用户意图并让 Model 做事。
>
> ```
> // Controller
> onClickAddItem(item) {
>   model.add(item) // 
>   view.refresh(model.getViewData())	// View被Controller触发了更新
> }
> ```

​	仔细我们分析一下这个流程，你会发现这些问题

- 当界面逻辑复杂时，Controller 往往会变得臃肿（变成 God Object）。
- View 与 Model 间可能会存在双向依赖或时序问题。

## MVC 在 Qt 中的样子

Qt 的 MVC 思想其实早就体现在 Qt 的 Model/View 框架里，只不过 Qt 的实现有自己的演化路径。通常我们把 QAbstractItemModel（及其子类）看作 Model，把 QListView、QTableView、QTreeView 等视作 View，而 Controller 这个角色并不是一个固定的类，而更多落到应用逻辑层或某个 QObject 上去处理用户输入与导航。

在一个典型的 QWidget 应用中，你会看到这样的分工：Model 负责数据存储、增删改查和通知（通过 model->dataChanged()、beginInsertRows()/endInsertRows() 等），View 负责显示和基础交互（选择、滚动、内建的编辑支持），而 Controller 则作为 glue 层，接收来自 View 的信号（比如按钮被按下、菜单项被触发），调用 Model 改变数据，并根据需要让 View 刷新或切换界面。

实现时的一个常见做法是在 Controller（或叫 Coordinator）里连接信号与槽。例如，QPushButton 的 clicked() 被连接到 Controller 的槽，Controller 在槽里调用 model 的修改接口，Model 发出数据改变信号，View 根据 model 的通知重绘。注意 Qt 的 Model/View 已经把很多细节封装好了：你通常不需要手动刷新每个界面元素，只要正确触发 Model 的变更通知，View 会自动更新。

容易踩到的坑在于职责不清。如果把显示逻辑和业务逻辑都堆到 Controller 中，它就会变得臃肿。在 Qt 项目里，这种情况通常表现为一个巨大的 QWidget 子类或 QObject 子类处理所有交互、数据库和网络逻辑。为了避免这一点，建议把纯业务逻辑抽到单独的类（service 或 manager），让 Controller 只做协调与视图相关的决策。

## MVP（Model-View-Presenter）——把展示逻辑交给 Presenter

​	很好，我们注意到了MVC中

- C很容易退化成一个反设计模式：上帝模式，这是我们不希望的
- V疑似太有主动权了，有时候我们工程中一些人喜欢V主动，一些人喜欢V被动，MVC允许两个操作并存，这就导致潜在的直接依赖，不好解耦合

​	所以在MVP中，我们收回了V的主动权，他就必须听从P的智慧，完全只跟P打交道，相当于P是超级加强版的，结构化的C。在这个设计模式中：

- **Model**：厨房（和 MVC 一样）。
- **View**：服务员，但更被动，只负责 UI 展示与收集用户输入。
- **Presenter**：新的领班，它掌握了所有的展示逻辑——向 Model 请求数据，处理后命令 View 更新。

1. View 捕获用户事件（比如按下按钮），把事件转发给 Presenter。
2. Presenter 调用 Model 做事或取数据。
3. Presenter 根据 Model 的返回组织成 View 需要的数据格式，然后调用 View 的方法（比如 `showList(items)`）。

#### 关键的特点

- Presenter 与 View 通过接口交互（接口方法很明确），Presenter 不直接依赖具体 UI 实现，方便测试。换而言之，我们这里更加的抽象了，我们只关心View的接口而不是实现，同理我们的Model
- View 非常被动，不包含业务逻辑或展示决策。

#### 好处

- 易于单元测试（Presenter 可以 mock View），展示逻辑集中且清晰。
- 当 UI 平台变化（比如从桌面切到手机），改 View 而 Presenter 可复用。

#### 坏处

- Presenter 会承担很多逻辑（类似 Controller 的“重”问题），但比 Controller 更结构化。换而言之，是一个更加代码逻辑清晰的MVC，但是可惜的是，我们更希望的是P不要成为God Object
- 如果 View 很多交互细节，接口会膨胀，维护成本上升。

```text
// View 接口
interface IView {
  showItems(list)
  showError(msg)
}

// Presenter
onViewLoaded() {
  model.loadItems(
    success: items => view.showItems(transform(items)),
    failure: err => view.showError(err)
  )
}
```

## MVP 在 Qt（纯 QWidget）中的实用方式

当你希望把 UI 层完全隔离、提高可测试性时，MVP 很适合 QWidget 世界。View 通过一个抽象接口（纯虚类）暴露需要的展示方法，具体的 QWidget 实现这个接口并负责 UI 绘制与事件转发，而 Presenter 则持有 View 的接口指针，负责所有的展示逻辑和与 Model 的交互。

例如，定义一个 ILoginView 接口，声明 showError(const QString&)、showProgress(bool) 等方法；LoginWidget（继承 QWidget）实现 ILoginView，并在用户点击登录时把事件转给 Presenter。Presenter 在后台调用登录服务（Model 层），根据返回调用 view->showError 或 view->showProgress。因为 Presenter 与具体的 QWidget 没耦合，单元测试时可以用 mock 的 ILoginView 来验证 Presenter 的逻辑。

MVP 在 Qt 的优点非常实用：你可以把 Presenter 写成纯 C++ 类、无需任何 GUI 依赖，方便在 CI 中跑逻辑测试；同时，Presenter 的接口清晰，适合团队分工——UI 工程师只做 View，逻辑工程师维护 Presenter。缺点是接口数量会随 View 的复杂度增加而膨胀，要对接口设计下功夫，避免把大量微交互方法暴露出来。这里的平衡点是把复杂业务拆成若干 UseCase 或 Interactor，Presenter 只负责把 UseCase 的结果映射到 View。

## MVVM（Model-View-ViewModel）——把“中介”变成可以绑定的数据层

MVVM则是更加现代的机制，他尝试进一步解耦合M和V的耦合，我们出现了ViewModel，也就是双向的接口声明

- **Model**：厨房（数据与业务）。
- **View**：服务员（UI），通过数据绑定直接“观察” ViewModel。
- **ViewModel**：转换器 + 状态持有者（它暴露可绑定的属性与命令）。

#### 流程（简化）

- View 通过数据绑定把自身的控件（例如输入框、列表）绑定到 ViewModel 的属性或命令。用户修改 View 就会自动更新 ViewModel，ViewModel 改变数据后通过绑定自动让 View 刷新。

#### 关键特点

- 强调**数据绑定**（binding）——UI 与 ViewModel 之间可以是双向绑定或单向绑定。（更加强迫的依赖接口而不是实现）
- ViewModel 不直接依赖 View（它不知道具体的 UI），因此非常利于测试。

#### 优点

- 大幅减少样板代码（你不用手动在代码里写 `view.setXXX()`）。
- 适合有数据绑定框架的环境（如 WPF、Android 的 DataBinding、Qt 的 QML）。
- 方便做双向数据同步（表单编辑、即时预览等场景）。

#### 缺点

- 如果没有框架支持，手动实现绑定会把工程复杂化。
- ViewModel 中可能包含大量状态与逻辑，导致复杂度上升。

```text
// ViewModel
class VM {
  property name
  command saveCommand
}

// View (伪声明式绑定)
<TextBox bind:value="vm.name" />
<Button bind:click="vm.saveCommand" />
```

- **MVC**：Controller 解释用户动作，Controller 主动。——想象领班直接去厨房下命令。
- **MVP**：Presenter 把“展示逻辑”都揽走，View 非常被动。——领班把菜谱、上菜流程都写好，服务员只负责搬菜。
- **MVVM**：View 与 ViewModel 用「数据绑定」握手，代码里少了很多手动更新窗体的样板。——服务员和领班之间有自动传菜带，菜来了自动放桌上。

## MVVM 在 Qt 下最自然的落地是 QML + QObject

如果你的项目使用 QML 做 UI，那么 MVVM（或类似思想）几乎是天然契合的。View（QML）通过属性绑定（在 QML 里写 `text: viewModel.title`）直接和一个 QObject 派生的 ViewModel 绑定。ViewModel 通过 Q_PROPERTY、信号和槽暴露状态与操作。QAbstractListModel 或 QAbstractItemModel 也常作为列表场景下的“Model”或“collection viewModel”。

在具体实现上，你会把 ViewModel 写为 QObject 子类，使用 Q_PROPERTY 暴露可观察的属性，使用 Q_INVOKABLE 或 slot 暴露命令。然后在 C++ 向 QML 注入这个 ViewModel，可以通过 QQmlContext::setContextProperty 或注册类型到 QML。QML 的双向绑定和属性变更通知机制可以把大量样板代码从 C++ 层拿掉，使界面代码非常简洁。

但 MVVM 在纯 QWidget 世界里并非没有意义，只是代价更高。因为 QWidget 本身并不提供声明式绑定，你要么借助第三方数据绑定库，要么在 C++ 层手动 connect 很多信号与槽来模拟绑定，这往往会把好处抵消掉。因此在 QWidget 项目里，很多团队选择 MVP 来获得更好的测试性和明确的接口，而在 QML 项目里优先选 MVVM。

## Qt 特有的模型：Model/View/Delegate（以及它和这些模式的关系）

Qt 的 Model/View 系统引入了 Delegate 的角色（例如 QStyledItemDelegate），专门负责把数据“渲染”成具体的单元（单元格、行）。这使得 Qt 的实现看起来更像是 MVC 与 MVVM 混合的产物：Model 负责数据与通知，View 负责布局和用户输入，Delegate 负责把 Model 的数据变成可交互的子控件（或编辑器）。在这条路线里，Controller 的角色分散到 Framework 的各个部分中，而不是单一对象。

理解这点有助于在实际开发中做出权衡。若你在用 QTableView 并配套自定义 QAbstractTableModel 与 QStyledItemDelegate，你实际上在利用 Qt 自带的“半成品”MVC，很多同步、编辑细节都由框架处理，你需要关注模型契约（data()/setData()/flags() 等）和 Delegate 的绘制/编辑逻辑。

------

## 常见误区与陷阱

- **“MVVM 就是万能”**：没有绑定框架时，强行套 MVVM 只会制造样板代码和复杂度。
- **“把所有东西都放到 Presenter/ViewModel”**：这会导致中介成为新的 God Object，失去分层价值。
- **混合模式不可怕，但要有清晰边界**：实际工程中常常混合使用（例如 Controller 处理导航，ViewModel 处理页面状态），关键是要写清责任划分。

------

## 快问快答

**Q：MVC、MVP、MVVM 哪个最好？**
 A：没有万能之选。看具体场景、团队经验、是否有绑定框架、测试需求，再决定。

**Q：如何避免 Presenter/ViewModel 变成上帝对象？**
 A：把职能拆细，引入 Use Case / Interactor 层，把业务流程（而不是展示逻辑）放到独立层里。

**Q：在 Qt 中用哪个？**
 A：如果你用 QML，MVVM（或类似思想）非常自然；如果是纯 QWidget，MVP 或 MVC 更常见，取决于你愿不愿意手动实现数据绑定。

# Examples

## 示例一：Widgets — MVC（QAbstractListModel + QListView）

这个示例展示了一个可增删字符串项的简单列表。核心是自定义 `StringListModel`（继承自 `QAbstractListModel`），`MainWindow` 作为 Controller/Coordinator，负责把 View（QListView、按钮）和 Model 连在一起。

```cpp
// stringlistmodel.h
#pragma once
#include <QAbstractListModel>
#include <QStringList>

class StringListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit StringListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return m_items.count();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
            return {};
        if (role == Qt::DisplayRole) return m_items.at(index.row());
        return {};
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override {
        if (!index.isValid()) return {};
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (role == Qt::EditRole && index.isValid()) {
            m_items[index.row()] = value.toString();
            emit dataChanged(index, index);
            return true;
        }
        return false;
    }

    void addItem(const QString& s) {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
        m_items.append(s);
        endInsertRows();
    }

    void removeAt(int row) {
        if (row < 0 || row >= m_items.size()) return;
        beginRemoveRows(QModelIndex(), row, row);
        m_items.removeAt(row);
        endRemoveRows();
    }

private:
    QStringList m_items;
};
// mainwindow.h
#pragma once
#include <QMainWindow>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include "stringlistmodel.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QWidget(parent) {
        model = new StringListModel(this);
        model->addItem("alpha");
        model->addItem("beta");

        listView = new QListView(this);
        listView->setModel(model);
        listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

        input = new QLineEdit(this);
        addBtn = new QPushButton("Add", this);
        removeBtn = new QPushButton("Remove Selected", this);

        auto *lay = new QVBoxLayout(this);
        lay->addWidget(listView);
        lay->addWidget(input);
        lay->addWidget(addBtn);
        lay->addWidget(removeBtn);

        connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAdd);
        connect(removeBtn, &QPushButton::clicked, this, &MainWindow::onRemove);
    }

private slots:
    void onAdd() {
        const QString text = input->text().trimmed();
        if (!text.isEmpty()) {
            model->addItem(text);
            input->clear();
        }
    }
    void onRemove() {
        const QModelIndex idx = listView->currentIndex();
        if (idx.isValid()) model->removeAt(idx.row());
    }

private:
    StringListModel* model;
    QListView* listView;
    QLineEdit* input;
    QPushButton* addBtn;
    QPushButton* removeBtn;
};
// main.cpp
#include <QApplication>
#include "mainwindow.h"
int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
```

在这个模式里，Qt 框架为你处理了大量细节：当你在模型中调用 `beginInsertRows()` / `endInsertRows()` 或 `dataChanged()` 时，Linked View 会自动刷新显示。Controller（这里是 `MainWindow`）把 View 的信号翻译成对 Model 的操作。

------

## 示例二：Widgets — MVP（登录窗口）

此示例展示如何用接口隔离 View 与 Presenter，使 Presenter 可以用 mock View 单元测试。

```cpp
// iloginview.h
#pragma once
#include <QString>

class ILoginView {
public:
    virtual ~ILoginView() = default;
    virtual void showProgress(bool visible) = 0;
    virtual void showError(const QString& msg) = 0;
    virtual void onLoginSuccess() = 0;
};
// loginpresenter.h
#pragma once
#include <QObject>
#include <QTimer>
#include "iloginview.h"

class LoginPresenter : public QObject {
    Q_OBJECT
public:
    LoginPresenter(ILoginView* v, QObject* parent = nullptr) : QObject(parent), view(v) {}

    void login(const QString& user, const QString& pass) {
        if (user.isEmpty() || pass.isEmpty()) {
            view->showError("user or pass empty");
            return;
        }
        view->showProgress(true);
        // 模拟异步登录：使用 QTimer 单次触发
        QTimer::singleShot(800, this, [this, user, pass]() {
            view->showProgress(false);
            if (user == "admin" && pass == "123") view->onLoginSuccess();
            else view->showError("invalid credentials");
        });
    }

private:
    ILoginView* view;
};
// loginwidget.h
#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "iloginview.h"
#include "loginpresenter.h"

class LoginWidget : public QWidget, public ILoginView {
    Q_OBJECT
public:
    LoginWidget(QWidget* parent = nullptr) : QWidget(parent) {
        userEdit = new QLineEdit(this);
        passEdit = new QLineEdit(this);
        passEdit->setEchoMode(QLineEdit::Password);
        loginBtn = new QPushButton("Login", this);
        status = new QLabel(this);

        auto *lay = new QVBoxLayout(this);
        lay->addWidget(userEdit);
        lay->addWidget(passEdit);
        lay->addWidget(loginBtn);
        lay->addWidget(status);

        presenter = new LoginPresenter(this, this);
        connect(loginBtn, &QPushButton::clicked, this, &LoginWidget::onClicked);
    }

    // ILoginView impl
    void showProgress(bool visible) override {
        status->setText(visible ? "Logging in..." : "");
    }
    void showError(const QString& msg) override {
        status->setText(QStringLiteral("Error: ") + msg);
    }
    void onLoginSuccess() override {
        status->setText("Login OK");
    }

private slots:
    void onClicked() {
        presenter->login(userEdit->text(), passEdit->text());
    }

private:
    QLineEdit* userEdit;
    QLineEdit* passEdit;
    QPushButton* loginBtn;
    QLabel* status;
    LoginPresenter* presenter;
};
```

在这个例子中，`LoginPresenter` 完全不知道 `LoginWidget` 的具体类型，它只通过 `ILoginView` 交互。这样就很容易以 `MockILoginView` 做单元测试来断言登录流程的分支。

------

## 示例三：Widgets — MVVM（在 QWidget 下的模拟实现）

因为 QWidget 不提供声明式绑定，下面我们用 `QObject`（含 `Q_PROPERTY`）作为 ViewModel，并用信号/槽把 View 与 ViewModel 连接起来。示例为一个简单的表单，ViewModel 持有 `name` 属性，View 的 `QLineEdit` 与 ViewModel 同步。

关键点：**避免循环更新**（View -> ViewModel -> View 再触发 View -> ...）。常见方法是比较新旧值或在更新时临时阻断信号（`blockSignals(true/false)`）。

```cpp
// personviewmodel.h
#pragma once
#include <QObject>

class PersonViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit PersonViewModel(QObject* parent = nullptr) : QObject(parent) {}

    QString name() const { return m_name; }
    void setName(const QString& v) {
        if (m_name == v) return;
        m_name = v; emit nameChanged(m_name);
    }

signals:
    void nameChanged(const QString&);

private:
    QString m_name;
};
// mvvmwidget.h
#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include "personviewmodel.h"

class MVVMWidget : public QWidget {
    Q_OBJECT
public:
    MVVMWidget(QWidget* parent = nullptr) : QWidget(parent) {
        viewModel = new PersonViewModel(this);
        auto* edit = new QLineEdit(this);
        auto* label = new QLabel(this);

        auto* lay = new QVBoxLayout(this);
        lay->addWidget(edit);
        lay->addWidget(label);

        // View -> ViewModel
        connect(edit, &QLineEdit::textEdited, this, [this](const QString& t) {
            // 直接设置，会触发 viewModel->nameChanged
            viewModel->setName(t);
        });

        // ViewModel -> View
        connect(viewModel, &PersonViewModel::nameChanged, this, [edit, label](const QString& newName) {
            // 避免重复设置导致的循环（如果值不变则不会 set）
            if (edit->text() != newName) {
                // blockSignals 避免再次触发 textEdited
                bool old = edit->blockSignals(true);
                edit->setText(newName);
                edit->blockSignals(old);
            }
            label->setText(QStringLiteral("Hello, %1").arg(newName));
        });

        // 初始化一个值
        viewModel->setName("QtDev");
    }

private:
    PersonViewModel* viewModel;
};
```

这个模式把状态集中在 `PersonViewModel`，使逻辑（例如姓名校验、格式化）可以放在 ViewModel 内部，而 View 只是把用户动作转成对 ViewModel 的调用，并观察 ViewModel 的变化来渲染界面。虽然比 QML 中写法更啰嗦，但在没有声明式绑定时这是一种折衷方案