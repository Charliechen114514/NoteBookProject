# Qt中的并发编程1

​	笔者在Qt官网上找到一个质量比较高的QT并发教程demo，地址如下：[Free Coding Courses | Qt Academy Course Catalog](https://www.qt.io/academy/course-catalog#let's-get-thready!-multithreading-with-qt)，所有的示例demo在：[qt-learning/Multithreading-With-Qt (github.com)](https://github.com/qt-learning/Multithreading-With-Qt/)。笔者这里提供的是翻译。

## 啥是并发

​	程序是一组指示计算机执行什么操作的指令。运行程序会启动一个进程，进程是一个容器，包含运行程序所需的所有指令和引用。进程启动时，它有一个称为线程的执行流，这是程序指令的一条路径。该线程按照程序的逻辑逐条执行指令。

​	程序启动时运行的**第一个执行线程通常称为主线程**。它执行程序的主要功能。主线程还有自己的堆栈，即一块内存区域，用于存储有关函数调用和其他本地数据的信息。有时，您可能希望同时运行程序的某些部分，这意味着多个执行线程同时运行。例如，如果您正在构建视频游戏，您可能希望一个线程处理用户输入，而另一个线程负责渲染图形。为了实现这一点，您可以在程序中创建额外的执行线程。

​	每个执行线程都有自己的堆栈，就像主线程一样。这意味着每个线程都可以独立于其他线程执行其指令。但是，所有线程共享堆空间，这是在程序执行期间存储动态分配对象的内存区域。这使得每个线程都可以独立于其他线程执行其指令。这就是线程与进程的区别，因为进程不共享内存。

## 计算机是如何管理线程的？

​	调度是将 CPU 时间分配给应用程序操作的过程。操作系统执行此过程。由于处理器核心是有限的资源，因此每个线程都会争夺 CPU 时间。这种竞争意味着有时需要根据进程的优先级或所用的调度算法暂停和恢复执行。

​	线程的状态会定期保存。当一个线程的执行恢复时，**如果 CPU 上没有空闲的核心，则另一个线程将被暂停，以便它能够获得 CPU 时间。这称为上下文切换**。调度很重要，因为它可以高效利用系统资源并确保所有进程都能公平地分配 CPU 时间。如果没有调度，一个线程可能会独占 CPU，而其他线程则无限期地等待。

​	总体而言，创建多个执行线程可让您在编写程序时拥有更大的灵活性和能力。但是，它也带来了额外的复杂性，因为您必须仔细管理线程的交互以避免出现问题。多线程允许您使用计算机中的多个内核同时执行各种任务。这可以显著提高 GUI 应用程序的性能，尤其是当它涉及计算量大的任务（例如图像处理或数据分析）时。计算量大意味着对时间、处理能力和内存的需求很高。特定线程可以负责更新和响应具有用户界面的应用程序的用户输入。

## 举个例子

​	我们将使用光线投射渲染球体图像。场景由一个定向光和一个漫反射阴影球体组成。光线投射算法对生成的图像中的每个像素执行大量指令，以识别球体的颜色和阴影。这项任务被认为成本高昂，尤其是当应用程序窗口较大时，因为需要更多像素。

​	这在 GUI 线程上的计算成本很高，因为它涉及复杂的数学计算和遍历屏幕上每个像素的嵌套循环。计算涉及多个三角函数、平方根和点积，可能需要很长时间才能计算出来。

​	当在 GUI 线程上执行此代码时，它可能会导致 UI 冻结或无响应，因为线程被阻止直到计算完成。这可能会导致糟糕的用户体验，尤其是当图像复杂或图像尺寸很大时。这就是多线程变得有用的地方，它允许我们将这种计算转移到其他线程。

​	Qt官方有一个小小的demo，可以参考一下：[qt-learning/Multithreading-With-Qt (github.com)](https://github.com/qt-learning/Multithreading-With-Qt/).00Start就是没有采用多线程进行编写的代码。笔者尝试后发现几乎卡顿到没法让GUI正常流畅的放缩

## 所以使用QThread进行加速

​	QThread是 Qt 框架中的一个类，它提供了一种独立于平台的线程管理方法。它可用于在 Qt 应用程序中创建和管理线程。QThread 提供了启动、暂停和停止线程以及监视线程状态的方法。它还提供了线程间通信和控制任务执行顺序的机制。要启动线程，请调用其 start() 成员函数。

​	在刚刚笔者贴出的示例项目中，有一个类，其唯一任务就是执行计算，如前所述。它被称为 RayCaster，位于 raycaster.h 和 raycaster.cpp 中。代码创建了一个 Sphere 和 Ray 类来表示球体和射线对象。然后，RayCaster 类使用这些对象来渲染图像。使用二次公式，该函数循环遍历图像中的每个像素并计算射线与球体的交点。如果增量值大于或等于零，则表示射线与球体相交，并且该函数使用交点处的法线向量与定向光源之间的角度的余弦来计算像素的颜色。如果增量值为负，则射线未击中球体，像素设置为黑色。最后，该函数返回渲染的图像。

```
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::event(QEvent *event) {
  switch (event->type()) {
  case QEvent::Type::Resize: {
    ui->viewport->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->viewport->resize(this->geometry().size());
    emit resized();
    renderImage();
    break;
  }
  default:
    break;
  }
  return QMainWindow::event(event);
}

void MainWindow::renderImage() {
  RayCaster caster;
  QImage image = caster.render(ui->viewport->size(), devicePixelRatio());
  ui->viewport->setPixmap(QPixmap::fromImage(image));
}
```

​	如何渲染的是示例工程作者认为无关紧要的，感兴趣的朋友请下载工程进行学习。

​	在 mainwindow.cpp 中，有一个方法 renderImage()，每当主窗口收到 Resize 事件时（包括创建时），该方法都会调用 Raycaster::renderImage()。在 MainWindow::event(QEvent *event) 中有事件处理。每次触发 Resize 事件时，我们都会调用 renderImage() 方法，该方法会像前面提到的那样渲染图像。

​	如果您尚未测试过该应用程序，让我们再解释一次发生了什么。当窗口变得足够大时，您将遇到延迟，并且窗口响应会很慢。这是因为我们在 GUI 线程上完成所有工作，而 GUI 线程没有时间在窗口上执行日常工作。即处理系统消息、重新绘制 UI 等……所有时间都花在执行 RayCaster::render 中的光线投射逻辑上。如果我们在窗口中引入其他元素，这种情况会更加明显。例如，在计算期间，文本输入会变慢或无法响应。

```
#include <QThread>

// 可以看到，我们的QThread的正确使用方法跟Java类似，也就是继承的方式实现的
class RenderingThread: public QThread {
public:
   RenderingThread(QSize viewportSize, qreal dpi)
       : m_viewportSize(std::move(viewportSize)), m_dpi(dpi)
    {
        // Constructor runs on main thread
        qDebug() << QThread::currentThreadId() << 
            " - RenderingThread() constructor";  // [1]
    }

    void run() override {
        // This part runs on the actual separate thread
        qDebug() << QThread::currentThreadId() <<
            " - RenderingThread::run()";  // [2]
        RayCaster caster;
        m_result = caster.render(m_viewportSize, m_dpi);
    }

    const QImage& result() { return m_result; }

private:
    QSize m_viewportSize;
    qreal m_dpi;
    QImage m_result;
};
```

上面的类实现了渲染线程并存储了调用 RayCaster::render() 所需的参数。

​	当创建 RenderingThread 类的对象时，构造函数将在与调用代码相同的线程上执行，该线程是主线程。我们可以通过使用 qDebug() 将当前线程 ID 打印到控制台来测试这一点。要在单独的线程上执行 RayCaster::render()，我们必须重写 QThread 类提供的 run() 并将运行该方法的指令放在其中。在这种情况下，run() 创建 RayCaster 的实例并调用 render() 函数，传递存储的 viewportSize 和 dpi 参数。render() 方法的结果存储在成员变量 m_result 中。

​	继承 QObject 的类的对象在设计上是线程仿射的。这意味着它们在与其有关系的线程上接收排队信号。QObject 应该在其仿射线程上被删除。在上面的例子中，RenderingThread 的构造函数在主线程上运行，因为从 QObject 继承的类总是在构造它们的线程上运行。run() 在单独的线程上运行，因为它从 QThread 继承，它的工作是生成一个新线程。

​	我们需要将 RenderingThread() 插入到 MainWindow::renderImage() 方法中；让我们替换已经存在的内容：

```
void MainWindow::renderImage()
{
    auto *thread = new RenderingThread(ui->viewport->size(),
                                       devicePixelRatio());
    thread->start();
}
```

​	现在我们就把渲染逻辑给独立出去了。我们可以在 MainWindow 中创建一个方法 threadFinished()。记得将此方法的签名添加到头文件中。这意味着我们可以在线程完成后获取图像并显示它。我们需要做的最后一件事是将 MainWindow::threadFinished() 连接到线程。当线程完成后，我们可以在 MainWindow::threadFinished() 中收集图像结果。

```
void MainWindow::threadFinished() {
    auto *renderingThread = static_cast<RenderingThread *>(sender());
    const QImage& result = renderingThread->result();
    ui->viewport->setPixmap(QPixmap::fromImage(result));
}
```

```
private:
    void renderImage();
    void threadFinished();
```

```
void MainWindow::renderImage()
{
    auto *thread = new RenderingThread(ui->viewport->size(),
                                       devicePixelRatio());
    QObject::connect(thread,
                     &QThread::finished,
                     this,
                     &MainWindow::threadFinished);
    thread->start();
}
```

```
void MainWindow::renderImage()
{
    auto *thread = new RenderingThread(ui->viewport->size(),
                                       devicePixelRatio());
    QObject::connect(thread,
                     &QThread::finished,
                     this,
                     &MainWindow::threadFinished);
    thread->start();
}
```

## 工作对象：如何管理 Qt 应用程序中的线程？

​	在上一节中，我们使用 QThread 实现了一些基本的线程管理，该线程仅在完成后才与 GUI 线程通信。现在我们将尝试解决之前遇到的问题。对于我们知道不再需要但仍能完全执行的计算，我们可以做些什么？

​	我们需要在各个执行线程之间建立通信机制。GUI 线程需要在新线程上线时持续通信，通知它们不再需要其工作并且应停止工作。

​	为了实现这一点，我们可以使用 QThread::run(); 的默认实现，它运行 QEventLoop（在新选项卡中打开）。创建事件循环使我们能够同步处理事件，同时监听信号以执行某些操作作为对它们的响应，例如启动、停止或取消渲染或图像。

​	首先，我们将创建一个 RenderingWorker 类。这将提供我们可以传递给 QThread::run() 的对象的框架，以便可以在其事件循环中启动和停止其工作。在我们的应用程序中，我们需要确保在调整窗口大小、启动渲染过程、完成渲染过程以及线程退出时通知各个元素。至关重要的是，我们希望在必要时中断线程并取消渲染。例如，如果调整了应用程序的大小，则停止正在进行的所有渲染。

```
class RenderingWorker : public QObject
{
  Q_OBJECT
public:
  RenderingWorker(QSize viewportSize, qreal dpi)
    : m_viewportSize(std::move(viewportSize)), m_dpi(dpi)
  {
  }

  void doWork()
  {
    RayCaster caster;
    m_result = caster.render(m_viewportSize, m_dpi);
    emit done();
  }

  QImage *result() { return &m_result; }

signals:
  void done();

private:
  QSize m_viewportSize;
  qreal m_dpi;
  QImage m_result;
};
```

​	您可能会注意到，RenderingWorker 类与我们之前的多线程实现类似，但有一些显著的区别：RenderingWorker 继承自 QObject 而不是 QThread。它不再是一个线程，而是我们想要在线程上运行的 worker。

​	worker 还会在完成其工作时发出信号 done()。这意味着我们可以在事件循环中执行时连接到对象，并在 worker 完成时收到通知。现在，我们可以替换 MainWindow::renderImage() 中的现有实现。

```
/*
 * Create a new QThread and a RenderingWorker object. Move the rendering worker
 * to the new thread. Establish connections between the thread, worker, and the
 * MainWindow. When the thread starts, doWork() worker is called. Once the
 * worker is finished, done() signal is emitted. The done() signal is connected
 * to both the threadFinished() function of the MainWindow and the quit() slot
 * of the thread. Finally, the thread is started.
 */
void MainWindow::renderImage() {
    auto *thread = new QThread();
    auto *worker = new RenderingWorker(ui->viewport->size(), 
                                       devicePixelRatio());
    worker->moveToThread(thread);

    QObject::connect(thread, &QThread::started, worker, 
                     &RenderingWorker::doWork);
    QObject::connect(worker, &RenderingWorker::done, this,
                     &MainWindow::threadFinished);
    QObject::connect(worker, &RenderingWorker::done, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}
```

​	这是一种更好的方式，复用QObject来完成我们的工作！当 worker 完成其工作时，MainWindow::renderImage 中的一个连接会引用 MainWindow::threadFinished。一旦 worker 完成生成图像，我们就想将其显示给用户。因此，让我们首先在 mainwindow.h 中声明该方法，并将定义添加到 mainwindow.cpp。

```
//...
class MainWindow : public QMainWindow
{
//...

private:
    void threadFinished();
//...
};
```

```
/*
 * When the rendering worker is finished, downcast the sender to
 * retrieve the pointer to the rendering worker. Create a qScopeGuard
 * object to ensure that the rendering worker is deleted later. Check
 * if the size of the rendered image matches the size of the viewport.
 * If not, return without updating the viewport. Set the rendered image.
 */
void MainWindow::threadFinished() {
  auto *renderingWorker = static_cast<RenderingWorker *>(sender());
  auto deleteWorkerLater =
      qScopeGuard([renderingWorker]() { renderingWorker->deleteLater(); });
  if (renderingWorker->result()->size() !=
      ui->viewport->size() * devicePixelRatio())
    return;
  ui->viewport->setPixmap(QPixmap::fromImage(*renderingWorker->result()));
}
```

​	现在，RenderingWorker 类已设置为在新线程上处理作业，并在结果与视口大小匹配时显示新图像。但是，我们仍在使用其他资源来渲染未显示的图像，因为在发出 MainWindow::resized 时不会取消正在进行的作业。让我们首先向 RayCaster::render 方法添加一个取消标志。

```
  //...
  QImage RayCaster::render(const QSize &viewport, 
                           qreal dpi, 
                           bool *cancelFlag) {
    //...
    for (int y = 0; y < scaledViewport.height(); ++y) {
    /* As the image is being rendered, we need to process events to keep the
     * application responsive. We do this by calling processEvents() on the
     * event dispatcher of the current thread. This allows us to process
     * any queued events, in this case the cancel() slot when the window 
     * is resized. */
      QThread::currentThread()->eventDispatcher()->processEvents(
          QEventLoop::ProcessEventsFlag::AllEvents);
          
      // If the cancel flag is set to true, we return an empty image.
      if (*cancelFlag) {
        qDebug() << "Canceled " << viewport;
        return QImage();
      }
      //...
    }
  }
  return image;
}
```

```
//...
class RenderingWorker : public QObject {
  Q_OBJECT
public:
  //...
  void doWork() {
    RayCaster caster;
    m_result = caster.render(m_viewportSize, m_dpi, &m_cancel);
    emit done();
  }
  
  //...
  
  void cancel() { m_cancel = true; }
  
  //...
private:
  //...
  
  bool m_cancel = false;
};

//...

void MainWindow::renderImage() {
  //...
  
  QObject::connect(this, &MainWindow::resized, worker,
                   &RenderingWorker::cancel);
  //...
}
```

​	如果我们想要接收 cancel() 事件，我们在线程的事件调度程序上调用 processEvents()。这意味着它将在循环继续之前处理它发现的任何事件。在这种情况下，这允许我们处理由 MainWindow::resized 信号排队的 cancel() 槽，该信号在主线程上运行。然后，我们可以检查 cancelFlag 并返回一个空图像（如果为真）。请记住，我们还必须将 cancelFlag 传递给 raycaster。

## QRunnable

​	在上一节中，我们创建了一个工作对象类，并将其实例化并在工作线程事件循环上运行。此实现使我们能够创建一种通信机制来取消不再需要的渲染。

​	虽然该解决方案解决了我们的问题，但随着应用程序变得越来越复杂，这可能很难管理。频繁创建和销毁线程也会消耗大量计算资源。Qt 有一个系统来维护可重用线程集合，称为线程池。我们可以使用 Qt 的线程池来管理和降低在应用程序中使用 QThread 对象的创建成本。QThreadPool 是用于管理应用程序中的线程集合的类。当您有需要同时完成的任务（如后台计算或数据处理作业）时，您可以将此任务委托给 QThreadPool（在新选项卡中打开）。它将分配其中一个可用线程来执行您的任务。

​	这比每次需要执行并发操作时创建和销毁线程更有效，因为管理可重用线程池可以减少与线程管理相关的开销。这意味着管理线程生命周期的负担被消除，并且可以将重点放在发布到池中的作业上。要使用其中一个 QThreadPool 线程，需要将从 QRunnable（在新选项卡中打开）子类化的作业传递给 QThreadPool::start()。

​	QRunnable 用于实现 run() 虚拟函数，然后创建该类的对象并将其传递给 QThreadPool::start()。但是，我们甚至不需要为此创建一个从 QRunnable 继承的特殊类。我们可以使用 QRunnable::create 包装一个 lambda 函数，该函数指定我们要发布到池中的作业。在本例中，渲染图像。我们仍然希望将渲染函数封装在一个类中，但我们可以使用 lambda 函数将其传递给线程。