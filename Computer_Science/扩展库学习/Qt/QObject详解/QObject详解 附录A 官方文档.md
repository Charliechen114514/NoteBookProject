# QObject Class

The QObject class is the base class of all Qt objects. [More...](https://doc.qt.io/qt-6/qobject.html#details)

| Header:       | #include < QObject>                                          |
| ------------- | ------------------------------------------------------------ |
| CMake:        | find_package(Qt6 REQUIRED COMPONENTS Core) target_link_libraries(mytarget PRIVATE Qt6::Core) |
| qmake:        | QT += core                                                   |
| Inherited By: | [Q3DObject](https://doc.qt.io/qt-6/q3dobject.html), [Q3DScene](https://doc.qt.io/qt-6/q3dscene.html), [Q3DTheme](https://doc.qt.io/qt-6/q3dtheme.html), [QAbstract3DAxis](https://doc.qt.io/qt-6/qabstract3daxis.html), [QAbstract3DInputHandler](https://doc.qt.io/qt-6/qabstract3dinputhandler.html), [QAbstract3DSeries](https://doc.qt.io/qt-6/qabstract3dseries.html), [QAbstractAnimation](https://doc.qt.io/qt-6/qabstractanimation.html), [QAbstractAxis](https://doc.qt.io/qt-6/qabstractaxis.html), [QAbstractDataProxy](https://doc.qt.io/qt-6/qabstractdataproxy.html), [QAbstractEventDispatcher](https://doc.qt.io/qt-6/qabstracteventdispatcher.html), [QAbstractGrpcClient](https://doc.qt.io/qt-6/qabstractgrpcclient.html), [QAbstractHttpServer](https://doc.qt.io/qt-6/qabstracthttpserver.html), [QAbstractItemDelegate](https://doc.qt.io/qt-6/qabstractitemdelegate.html), [QAbstractItemModel](https://doc.qt.io/qt-6/qabstractitemmodel.html), [QAbstractItemModelTester](https://doc.qt.io/qt-6/qabstractitemmodeltester.html), [QAbstractNetworkCache](https://doc.qt.io/qt-6/qabstractnetworkcache.html), [QAbstractOAuth](https://doc.qt.io/qt-6/qabstractoauth.html), [QAbstractOAuthReplyHandler](https://doc.qt.io/qt-6/qabstractoauthreplyhandler.html), [QAbstractSeries](https://doc.qt.io/qt-6/qabstractseries.html), [QAbstractState](https://doc.qt.io/qt-6/qabstractstate.html), [QAbstractTextDocumentLayout](https://doc.qt.io/qt-6/qabstracttextdocumentlayout.html), [QAbstractTransition](https://doc.qt.io/qt-6/qabstracttransition.html), [QAccessiblePlugin](https://doc.qt.io/qt-6/qaccessibleplugin.html), [QAction](https://doc.qt.io/qt-6/qaction.html), [QActionGroup](https://doc.qt.io/qt-6/qactiongroup.html), [QAmbientSound](https://doc.qt.io/qt-6/qambientsound.html), [QAudioDecoder](https://doc.qt.io/qt-6/qaudiodecoder.html), [QAudioEngine](https://doc.qt.io/qt-6/qaudioengine.html), [QAudioInput](https://doc.qt.io/qt-6/qaudioinput.html), [QAudioListener](https://doc.qt.io/qt-6/qaudiolistener.html), [QAudioOutput](https://doc.qt.io/qt-6/qaudiooutput.html), [QAudioRoom](https://doc.qt.io/qt-6/qaudioroom.html), [QAudioSink](https://doc.qt.io/qt-6/qaudiosink.html), [QAudioSource](https://doc.qt.io/qt-6/qaudiosource.html), [QAxBaseObject](https://doc.qt.io/qt-6/qaxbaseobject.html), [QAxFactory](https://doc.qt.io/qt-6/qaxfactory.html), [QAxScript](https://doc.qt.io/qt-6/qaxscript.html), [QAxScriptManager](https://doc.qt.io/qt-6/qaxscriptmanager.html), [QBarSet](https://doc.qt.io/qt-6/qbarset.html), [QBluetoothDeviceDiscoveryAgent](https://doc.qt.io/qt-6/qbluetoothdevicediscoveryagent.html), [QBluetoothLocalDevice](https://doc.qt.io/qt-6/qbluetoothlocaldevice.html), [QBluetoothServer](https://doc.qt.io/qt-6/qbluetoothserver.html), [QBluetoothServiceDiscoveryAgent](https://doc.qt.io/qt-6/qbluetoothservicediscoveryagent.html), [QBoxSet](https://doc.qt.io/qt-6/qboxset.html), [QButtonGroup](https://doc.qt.io/qt-6/qbuttongroup.html), [QCamera](https://doc.qt.io/qt-6/qcamera.html), [QCanBus](https://doc.qt.io/qt-6/qcanbus.html), [QCanBusDevice](https://doc.qt.io/qt-6/qcanbusdevice.html), [QCandlestickModelMapper](https://doc.qt.io/qt-6/qcandlestickmodelmapper.html), [QCandlestickSet](https://doc.qt.io/qt-6/qcandlestickset.html), [QClipboard](https://doc.qt.io/qt-6/qclipboard.html), [QCoapClient](https://doc.qt.io/qt-6/qcoapclient.html), [QCompleter](https://doc.qt.io/qt-6/qcompleter.html), [QCoreApplication](https://doc.qt.io/qt-6/qcoreapplication.html), [QCustom3DItem](https://doc.qt.io/qt-6/qcustom3ditem.html), [QDataWidgetMapper](https://doc.qt.io/qt-6/qdatawidgetmapper.html), [QDBusAbstractAdaptor](https://doc.qt.io/qt-6/qdbusabstractadaptor.html), [QDBusAbstractInterface](https://doc.qt.io/qt-6/qdbusabstractinterface.html), [QDBusPendingCallWatcher](https://doc.qt.io/qt-6/qdbuspendingcallwatcher.html), [QDBusServer](https://doc.qt.io/qt-6/qdbusserver.html), [QDBusServiceWatcher](https://doc.qt.io/qt-6/qdbusservicewatcher.html), [QDBusVirtualObject](https://doc.qt.io/qt-6/qdbusvirtualobject.html), [QDesignerFormEditorInterface](https://doc.qt.io/qt-6/qdesignerformeditorinterface.html), [QDesignerFormWindowManagerInterface](https://doc.qt.io/qt-6/qdesignerformwindowmanagerinterface.html), [QDnsLookup](https://doc.qt.io/qt-6/qdnslookup.html), [QDrag](https://doc.qt.io/qt-6/qdrag.html), [QDtls](https://doc.qt.io/qt-6/qdtls.html), [QDtlsClientVerifier](https://doc.qt.io/qt-6/qdtlsclientverifier.html), [QEventLoop](https://doc.qt.io/qt-6/qeventloop.html), [QExtensionFactory](https://doc.qt.io/qt-6/qextensionfactory.html), [QExtensionManager](https://doc.qt.io/qt-6/qextensionmanager.html), [QFileSelector](https://doc.qt.io/qt-6/qfileselector.html), [QFileSystemWatcher](https://doc.qt.io/qt-6/qfilesystemwatcher.html), [QFutureWatcher](https://doc.qt.io/qt-6/qfuturewatcher.html), [QGenericPlugin](https://doc.qt.io/qt-6/qgenericplugin.html), [QGeoAreaMonitorSource](https://doc.qt.io/qt-6/qgeoareamonitorsource.html), [QGeoCodeReply](https://doc.qt.io/qt-6/qgeocodereply.html), [QGeoCodingManager](https://doc.qt.io/qt-6/qgeocodingmanager.html), [QGeoCodingManagerEngine](https://doc.qt.io/qt-6/qgeocodingmanagerengine.html), [QGeoPositionInfoSource](https://doc.qt.io/qt-6/qgeopositioninfosource.html), [QGeoRouteReply](https://doc.qt.io/qt-6/qgeoroutereply.html), [QGeoRoutingManager](https://doc.qt.io/qt-6/qgeoroutingmanager.html), [QGeoRoutingManagerEngine](https://doc.qt.io/qt-6/qgeoroutingmanagerengine.html), [QGeoSatelliteInfoSource](https://doc.qt.io/qt-6/qgeosatelliteinfosource.html), [QGeoServiceProvider](https://doc.qt.io/qt-6/qgeoserviceprovider.html), [QGesture](https://doc.qt.io/qt-6/qgesture.html), [QGraphicsAnchor](https://doc.qt.io/qt-6/qgraphicsanchor.html), [QGraphicsEffect](https://doc.qt.io/qt-6/qgraphicseffect.html), [QGraphicsItemAnimation](https://doc.qt.io/qt-6/qgraphicsitemanimation.html), [QGraphicsObject](https://doc.qt.io/qt-6/qgraphicsobject.html), [QGraphicsScene](https://doc.qt.io/qt-6/qgraphicsscene.html), [QGraphicsTransform](https://doc.qt.io/qt-6/qgraphicstransform.html), [QGrpcOperation](https://doc.qt.io/qt-6/qgrpcoperation.html), [QHelpEngineCore](https://doc.qt.io/qt-6/qhelpenginecore.html), [QHelpFilterEngine](https://doc.qt.io/qt-6/qhelpfilterengine.html), [QHelpSearchEngine](https://doc.qt.io/qt-6/qhelpsearchengine.html), [QHttpMultiPart](https://doc.qt.io/qt-6/qhttpmultipart.html), [QIconEnginePlugin](https://doc.qt.io/qt-6/qiconengineplugin.html), [QImageCapture](https://doc.qt.io/qt-6/qimagecapture.html), [QImageIOPlugin](https://doc.qt.io/qt-6/qimageioplugin.html), [QInputDevice](https://doc.qt.io/qt-6/qinputdevice.html), [QInputMethod](https://doc.qt.io/qt-6/qinputmethod.html), [QIODevice](https://doc.qt.io/qt-6/qiodevice.html), [QItemSelectionModel](https://doc.qt.io/qt-6/qitemselectionmodel.html), [QJSEngine](https://doc.qt.io/qt-6/qjsengine.html), [QLayout](https://doc.qt.io/qt-6/qlayout.html), [QLegendMarker](https://doc.qt.io/qt-6/qlegendmarker.html), [QLibrary](https://doc.qt.io/qt-6/qlibrary.html), [QLocalServer](https://doc.qt.io/qt-6/qlocalserver.html), [QLowEnergyController](https://doc.qt.io/qt-6/qlowenergycontroller.html), [QLowEnergyService](https://doc.qt.io/qt-6/qlowenergyservice.html), [QMaskGenerator](https://doc.qt.io/qt-6/qmaskgenerator.html), [QMediaCaptureSession](https://doc.qt.io/qt-6/qmediacapturesession.html), [QMediaDevices](https://doc.qt.io/qt-6/qmediadevices.html), [QMediaPlayer](https://doc.qt.io/qt-6/qmediaplayer.html), [QMediaRecorder](https://doc.qt.io/qt-6/qmediarecorder.html), [QMimeData](https://doc.qt.io/qt-6/qmimedata.html), [QModbusDevice](https://doc.qt.io/qt-6/qmodbusdevice.html), [QModbusReply](https://doc.qt.io/qt-6/qmodbusreply.html), [QMovie](https://doc.qt.io/qt-6/qmovie.html), [QMqttClient](https://doc.qt.io/qt-6/qmqttclient.html), [QMqttSubscription](https://doc.qt.io/qt-6/qmqttsubscription.html), [QNearFieldManager](https://doc.qt.io/qt-6/qnearfieldmanager.html), [QNearFieldTarget](https://doc.qt.io/qt-6/qnearfieldtarget.html), [QNetworkAccessManager](https://doc.qt.io/qt-6/qnetworkaccessmanager.html), [QNetworkCookieJar](https://doc.qt.io/qt-6/qnetworkcookiejar.html), [QNetworkInformation](https://doc.qt.io/qt-6/qnetworkinformation.html), [QObjectCleanupHandler](https://doc.qt.io/qt-6/qobjectcleanuphandler.html), [QOffscreenSurface](https://doc.qt.io/qt-6/qoffscreensurface.html), [QOpcUaClient](https://doc.qt.io/qt-6/qopcuaclient.html), [QOpcUaGdsClient](https://doc.qt.io/qt-6/qopcuagdsclient.html), [QOpcUaHistoryReadResponse](https://doc.qt.io/qt-6/qopcuahistoryreadresponse.html), [QOpcUaKeyPair](https://doc.qt.io/qt-6/qopcuakeypair.html), [QOpcUaNode](https://doc.qt.io/qt-6/qopcuanode.html), [QOpcUaProvider](https://doc.qt.io/qt-6/qopcuaprovider.html), [QOpenGLContext](https://doc.qt.io/qt-6/qopenglcontext.html), [QOpenGLContextGroup](https://doc.qt.io/qt-6/qopenglcontextgroup.html), [QOpenGLDebugLogger](https://doc.qt.io/qt-6/qopengldebuglogger.html), [QOpenGLShader](https://doc.qt.io/qt-6/qopenglshader.html), [QOpenGLShaderProgram](https://doc.qt.io/qt-6/qopenglshaderprogram.html), [QOpenGLTimeMonitor](https://doc.qt.io/qt-6/qopengltimemonitor.html), [QOpenGLTimerQuery](https://doc.qt.io/qt-6/qopengltimerquery.html), [QOpenGLVertexArrayObject](https://doc.qt.io/qt-6/qopenglvertexarrayobject.html), [QPdfDocument](https://doc.qt.io/qt-6/qpdfdocument.html), [QPdfPageNavigator](https://doc.qt.io/qt-6/qpdfpagenavigator.html), [QPdfPageRenderer](https://doc.qt.io/qt-6/qpdfpagerenderer.html), [QPdfWriter](https://doc.qt.io/qt-6/qpdfwriter.html), [QPieSlice](https://doc.qt.io/qt-6/qpieslice.html), [QPlaceManager](https://doc.qt.io/qt-6/qplacemanager.html), [QPlaceManagerEngine](https://doc.qt.io/qt-6/qplacemanagerengine.html), [QPlaceReply](https://doc.qt.io/qt-6/qplacereply.html), [QPluginLoader](https://doc.qt.io/qt-6/qpluginloader.html), [QQmlComponent](https://doc.qt.io/qt-6/qqmlcomponent.html), [QQmlContext](https://doc.qt.io/qt-6/qqmlcontext.html), [QQmlEngineExtensionPlugin](https://doc.qt.io/qt-6/qqmlengineextensionplugin.html), [QQmlExpression](https://doc.qt.io/qt-6/qqmlexpression.html), [QQmlExtensionPlugin](https://doc.qt.io/qt-6/qqmlextensionplugin.html), [QQmlFileSelector](https://doc.qt.io/qt-6/qqmlfileselector.html), [QQmlImageProviderBase](https://doc.qt.io/qt-6/qqmlimageproviderbase.html), [QQmlPropertyMap](https://doc.qt.io/qt-6/qqmlpropertymap.html), [QQuick3DObject](https://doc.qt.io/qt-6/qquick3dobject.html), [QQuickAttachedPropertyPropagator](https://doc.qt.io/qt-6/qquickattachedpropertypropagator.html), [QQuickImageResponse](https://doc.qt.io/qt-6/qquickimageresponse.html), [QQuickItem](https://doc.qt.io/qt-6/qquickitem.html), [QQuickItemGrabResult](https://doc.qt.io/qt-6/qquickitemgrabresult.html), [QQuickRenderControl](https://doc.qt.io/qt-6/qquickrendercontrol.html), [QQuickTextDocument](https://doc.qt.io/qt-6/qquicktextdocument.html), [QQuickTextureFactory](https://doc.qt.io/qt-6/qquicktexturefactory.html), [QQuickWebEngineProfile](https://doc.qt.io/qt-6/qquickwebengineprofile.html), [QRemoteObjectAbstractPersistedStore](https://doc.qt.io/qt-6/qremoteobjectabstractpersistedstore.html), [QRemoteObjectNode](https://doc.qt.io/qt-6/qremoteobjectnode.html), [QRemoteObjectPendingCallWatcher](https://doc.qt.io/qt-6/qremoteobjectpendingcallwatcher.html), [QRemoteObjectReplica](https://doc.qt.io/qt-6/qremoteobjectreplica.html), [QScreen](https://doc.qt.io/qt-6/qscreen.html), [QScreenCapture](https://doc.qt.io/qt-6/qscreencapture.html), [QScroller](https://doc.qt.io/qt-6/qscroller.html), [QScxmlDataModel](https://doc.qt.io/qt-6/qscxmldatamodel.html), [QScxmlInvokableService](https://doc.qt.io/qt-6/qscxmlinvokableservice.html), [QScxmlInvokableServiceFactory](https://doc.qt.io/qt-6/qscxmlinvokableservicefactory.html), [QScxmlStateMachine](https://doc.qt.io/qt-6/qscxmlstatemachine.html), [QSensor](https://doc.qt.io/qt-6/qsensor.html), [QSensorBackend](https://doc.qt.io/qt-6/qsensorbackend.html), [QSensorReading](https://doc.qt.io/qt-6/qsensorreading.html), [QSessionManager](https://doc.qt.io/qt-6/qsessionmanager.html), [QSettings](https://doc.qt.io/qt-6/qsettings.html), [QSGTexture](https://doc.qt.io/qt-6/qsgtexture.html), [QSGTextureProvider](https://doc.qt.io/qt-6/qsgtextureprovider.html), [QSharedMemory](https://doc.qt.io/qt-6/qsharedmemory.html), [QShortcut](https://doc.qt.io/qt-6/qshortcut.html), [QSignalMapper](https://doc.qt.io/qt-6/qsignalmapper.html), [QSignalSpy](https://doc.qt.io/qt-6/qsignalspy.html), [QSocketNotifier](https://doc.qt.io/qt-6/qsocketnotifier.html), [QSoundEffect](https://doc.qt.io/qt-6/qsoundeffect.html), [QSpatialSound](https://doc.qt.io/qt-6/qspatialsound.html), [QSqlDriver](https://doc.qt.io/qt-6/qsqldriver.html), [QSqlDriverPlugin](https://doc.qt.io/qt-6/qsqldriverplugin.html), [QStyle](https://doc.qt.io/qt-6/qstyle.html), [QStyleHints](https://doc.qt.io/qt-6/qstylehints.html), [QStylePlugin](https://doc.qt.io/qt-6/qstyleplugin.html), [QSvgRenderer](https://doc.qt.io/qt-6/qsvgrenderer.html), [QSyntaxHighlighter](https://doc.qt.io/qt-6/qsyntaxhighlighter.html), [QSystemTrayIcon](https://doc.qt.io/qt-6/qsystemtrayicon.html), [Qt3DAnimation::QAbstractAnimation](https://doc.qt.io/qt-6/qt3danimation-qabstractanimation.html), [Qt3DAnimation::QAnimationController](https://doc.qt.io/qt-6/qt3danimation-qanimationcontroller.html), [Qt3DAnimation::QAnimationGroup](https://doc.qt.io/qt-6/qt3danimation-qanimationgroup.html), [Qt3DAnimation::QMorphTarget](https://doc.qt.io/qt-6/qt3danimation-qmorphtarget.html), [Qt3DCore::QAbstractAspect](https://doc.qt.io/qt-6/qt3dcore-qabstractaspect.html), [Qt3DCore::QAspectEngine](https://doc.qt.io/qt-6/qt3dcore-qaspectengine.html), [Qt3DCore::QNode](https://doc.qt.io/qt-6/qt3dcore-qnode.html), [Qt3DCore::Quick::QQmlAspectEngine](https://doc.qt.io/qt-6/qt3dcore-quick-qqmlaspectengine.html), [Qt3DInput::QInputDeviceIntegration](https://doc.qt.io/qt-6/qt3dinput-qinputdeviceintegration.html), [Qt3DInput::QKeyEvent](https://doc.qt.io/qt-6/qt3dinput-qkeyevent.html), [Qt3DInput::QMouseEvent](https://doc.qt.io/qt-6/qt3dinput-qmouseevent.html), [Qt3DInput::QWheelEvent](https://doc.qt.io/qt-6/qt3dinput-qwheelevent.html), [Qt3DRender::QGraphicsApiFilter](https://doc.qt.io/qt-6/qt3drender-qgraphicsapifilter.html), [Qt3DRender::QPickEvent](https://doc.qt.io/qt-6/qt3drender-qpickevent.html), [Qt3DRender::QRenderCapabilities](https://doc.qt.io/qt-6/qt3drender-qrendercapabilities.html), [Qt3DRender::QRenderCaptureReply](https://doc.qt.io/qt-6/qt3drender-qrendercapturereply.html), [Qt3DRender::QStencilOperationArguments](https://doc.qt.io/qt-6/qt3drender-qstenciloperationarguments.html), [Qt3DRender::QStencilTestArguments](https://doc.qt.io/qt-6/qt3drender-qstenciltestarguments.html), [Qt3DRender::QTextureWrapMode](https://doc.qt.io/qt-6/qt3drender-qtexturewrapmode.html), [QTcpServer](https://doc.qt.io/qt-6/qtcpserver.html), [QTextDocument](https://doc.qt.io/qt-6/qtextdocument.html), [QTextObject](https://doc.qt.io/qt-6/qtextobject.html), [QTextToSpeech](https://doc.qt.io/qt-6/qtexttospeech.html), [QThread](https://doc.qt.io/qt-6/qthread.html), [QThreadPool](https://doc.qt.io/qt-6/qthreadpool.html), [QTimeLine](https://doc.qt.io/qt-6/qtimeline.html), [QTimer](https://doc.qt.io/qt-6/qtimer.html), [QTranslator](https://doc.qt.io/qt-6/qtranslator.html), [QUiLoader](https://doc.qt.io/qt-6/quiloader.html), [QUndoGroup](https://doc.qt.io/qt-6/qundogroup.html), [QUndoStack](https://doc.qt.io/qt-6/qundostack.html), [QValidator](https://doc.qt.io/qt-6/qvalidator.html), [QValue3DAxisFormatter](https://doc.qt.io/qt-6/qvalue3daxisformatter.html), [QVideoSink](https://doc.qt.io/qt-6/qvideosink.html), [QVirtualKeyboardAbstractInputMethod](https://doc.qt.io/qt-6/qvirtualkeyboardabstractinputmethod.html), [QVirtualKeyboardDictionary](https://doc.qt.io/qt-6/qvirtualkeyboarddictionary.html), [QVirtualKeyboardDictionaryManager](https://doc.qt.io/qt-6/qvirtualkeyboarddictionarymanager.html), [QVirtualKeyboardInputContext](https://doc.qt.io/qt-6/qvirtualkeyboardinputcontext.html), [QVirtualKeyboardInputEngine](https://doc.qt.io/qt-6/qvirtualkeyboardinputengine.html), [QVirtualKeyboardObserver](https://doc.qt.io/qt-6/qvirtualkeyboardobserver.html), [QVirtualKeyboardTrace](https://doc.qt.io/qt-6/qvirtualkeyboardtrace.html), [QWaylandClient](https://doc.qt.io/qt-6/qwaylandclient.html), [QWaylandObject](https://doc.qt.io/qt-6/qwaylandobject.html), [QWaylandQuickShellIntegration](https://doc.qt.io/qt-6/qwaylandquickshellintegration.html), [QWaylandSurfaceGrabber](https://doc.qt.io/qt-6/qwaylandsurfacegrabber.html), [QWaylandView](https://doc.qt.io/qt-6/qwaylandview.html), [QWaylandXdgPopup](https://doc.qt.io/qt-6/qwaylandxdgpopup.html), [QWaylandXdgToplevel](https://doc.qt.io/qt-6/qwaylandxdgtoplevel.html), [QWebChannel](https://doc.qt.io/qt-6/qwebchannel.html), [QWebChannelAbstractTransport](https://doc.qt.io/qt-6/qwebchannelabstracttransport.html), [QWebEngineContextMenuRequest](https://doc.qt.io/qt-6/qwebenginecontextmenurequest.html), [QWebEngineCookieStore](https://doc.qt.io/qt-6/qwebenginecookiestore.html), [QWebEngineDownloadRequest](https://doc.qt.io/qt-6/qwebenginedownloadrequest.html), [QWebEngineHistory](https://doc.qt.io/qt-6/qwebenginehistory.html), [QWebEngineNavigationRequest](https://doc.qt.io/qt-6/qwebenginenavigationrequest.html), [QWebEngineNewWindowRequest](https://doc.qt.io/qt-6/qwebenginenewwindowrequest.html), [QWebEngineNotification](https://doc.qt.io/qt-6/qwebenginenotification.html), [QWebEnginePage](https://doc.qt.io/qt-6/qwebenginepage.html), [QWebEngineProfile](https://doc.qt.io/qt-6/qwebengineprofile.html), [QWebEngineUrlRequestInterceptor](https://doc.qt.io/qt-6/qwebengineurlrequestinterceptor.html), [QWebEngineUrlRequestJob](https://doc.qt.io/qt-6/qwebengineurlrequestjob.html), [QWebEngineUrlSchemeHandler](https://doc.qt.io/qt-6/qwebengineurlschemehandler.html), [QWebSocket](https://doc.qt.io/qt-6/qwebsocket.html), [QWebSocketServer](https://doc.qt.io/qt-6/qwebsocketserver.html), [QWidget](https://doc.qt.io/qt-6/qwidget.html), [QWindow](https://doc.qt.io/qt-6/qwindow.html), [QWindowCapture](https://doc.qt.io/qt-6/qwindowcapture.html), and [QWinEventNotifier](https://doc.qt.io/qt-6/qwineventnotifier.html) |

- [List of all members, including inherited members](https://doc.qt.io/qt-6/qobject-members.html)
- [Deprecated members](https://doc.qt.io/qt-6/qobject-obsolete.html)

**Note:** All functions in this class are [reentrant](https://doc.qt.io/qt-6/threads-reentrancy.html).

**Note:** These functions are also [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html):

- [connect](https://doc.qt.io/qt-6/qobject.html#connect)(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type)
- [connect(const QObject *sender, const char *signal, const char *method, Qt::ConnectionType type) const](https://doc.qt.io/qt-6/qobject.html#connect-2)
- [connect](https://doc.qt.io/qt-6/qobject.html#connect-3)(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type)
- [connect](https://doc.qt.io/qt-6/qobject.html#connect-4)(const QObject *sender, PointerToMemberFunction signal, Functor functor)
- [connect](https://doc.qt.io/qt-6/qobject.html#connect-5)(const QObject *sender, PointerToMemberFunction signal, const QObject *context, Functor functor, Qt::ConnectionType type)
- [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)(const QObject *sender, const char *signal, const QObject *receiver, const char *method)
- [disconnect(const char *signal, const QObject *receiver, const char *method) const](https://doc.qt.io/qt-6/qobject.html#disconnect-2)
- [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect-5)(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method)
- [deleteLater](https://doc.qt.io/qt-6/qobject.html#deleteLater)()

## Properties

- **[objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop)** : QString

## Public Functions

|                             | **[QObject](https://doc.qt.io/qt-6/qobject.html#QObject)**(QObject **parent* = nullptr) |
| --------------------------- | ------------------------------------------------------------ |
| virtual                     | **[~QObject](https://doc.qt.io/qt-6/qobject.html#dtor.QObject)**() |
| QBindable< QString>         | **[bindableObjectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop)**() |
| bool                        | **[blockSignals](https://doc.qt.io/qt-6/qobject.html#blockSignals)**(bool *block*) |
| const QObjectList &         | **[children](https://doc.qt.io/qt-6/qobject.html#children)**() const |
| QMetaObject::Connection     | **[connect](https://doc.qt.io/qt-6/qobject.html#connect-2)**(const QObject **sender*, const char **signal*, const char **method*, Qt::ConnectionType *type* = Qt::AutoConnection) const |
| bool                        | **[disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect-2)**(const char **signal* = nullptr, const QObject **receiver* = nullptr, const char **method* = nullptr) const |
| bool                        | **[disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect-3)**(const QObject **receiver*, const char **method* = nullptr) const |
| void                        | **[dumpObjectInfo](https://doc.qt.io/qt-6/qobject.html#dumpObjectInfo)**() const |
| void                        | **[dumpObjectTree](https://doc.qt.io/qt-6/qobject.html#dumpObjectTree)**() const |
| QList< QByteArray>          | **[dynamicPropertyNames](https://doc.qt.io/qt-6/qobject.html#dynamicPropertyNames)**() const |
| virtual bool                | **[event](https://doc.qt.io/qt-6/qobject.html#event)**(QEvent **e*) |
| virtual bool                | **[eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)**(QObject **watched*, QEvent **event*) |
| T                           | **[findChild](https://doc.qt.io/qt-6/qobject.html#findChild)**(const QString &*name* = QString(), Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| QList< T>                   | **[findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)**(const QString &*name*, Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| QList< T>                   | **[findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren-1)**(Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| QList< T>                   | **[findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren-2)**(const QRegularExpression &*re*, Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| bool                        | **[inherits](https://doc.qt.io/qt-6/qobject.html#inherits)**(const char **className*) const |
| void                        | **[installEventFilter](https://doc.qt.io/qt-6/qobject.html#installEventFilter)**(QObject **filterObj*) |
| bool                        | **[isQuickItemType](https://doc.qt.io/qt-6/qobject.html#isQuickItemType)**() const |
| bool                        | **[isWidgetType](https://doc.qt.io/qt-6/qobject.html#isWidgetType)**() const |
| bool                        | **[isWindowType](https://doc.qt.io/qt-6/qobject.html#isWindowType)**() const |
| void                        | **[killTimer](https://doc.qt.io/qt-6/qobject.html#killTimer)**(int *id*) |
| virtual const QMetaObject * | **[metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)**() const |
| void                        | **[moveToThread](https://doc.qt.io/qt-6/qobject.html#moveToThread)**(QThread **targetThread*) |
| QString                     | **[objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop)**() const |
| QObject *                   | **[parent](https://doc.qt.io/qt-6/qobject.html#parent)**() const |
| QVariant                    | **[property](https://doc.qt.io/qt-6/qobject.html#property)**(const char **name*) const |
| void                        | **[removeEventFilter](https://doc.qt.io/qt-6/qobject.html#removeEventFilter)**(QObject **obj*) |
| void                        | **[setObjectName](https://doc.qt.io/qt-6/qobject.html#setObjectName)**(const QString &*name*) |
| void                        | **[setObjectName](https://doc.qt.io/qt-6/qobject.html#setObjectName-1)**(QAnyStringView *name*) |
| void                        | **[setParent](https://doc.qt.io/qt-6/qobject.html#setParent)**(QObject **parent*) |
| bool                        | **[setProperty](https://doc.qt.io/qt-6/qobject.html#setProperty)**(const char **name*, const QVariant &*value*) |
| bool                        | **[setProperty](https://doc.qt.io/qt-6/qobject.html#setProperty-1)**(const char **name*, QVariant &&*value*) |
| bool                        | **[signalsBlocked](https://doc.qt.io/qt-6/qobject.html#signalsBlocked)**() const |
| int                         | **[startTimer](https://doc.qt.io/qt-6/qobject.html#startTimer)**(int *interval*, Qt::TimerType *timerType* = Qt::CoarseTimer) |
| int                         | **[startTimer](https://doc.qt.io/qt-6/qobject.html#startTimer-1)**(std::chrono::milliseconds *interval*, Qt::TimerType *timerType* = Qt::CoarseTimer) |
| QThread *                   | **[thread](https://doc.qt.io/qt-6/qobject.html#thread)**() const |

## Public Slots

| void | **[deleteLater](https://doc.qt.io/qt-6/qobject.html#deleteLater)**() |
| ---- | ------------------------------------------------------------ |
|      |                                                              |

## Signals

| void | **[destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)**(QObject **obj* = nullptr) |
| ---- | ------------------------------------------------------------ |
| void | **[objectNameChanged](https://doc.qt.io/qt-6/qobject.html#objectNameChanged)**(const QString &*objectName*) |

## Static Public Members

| QMetaObject::Connection | **[connect](https://doc.qt.io/qt-6/qobject.html#connect)**(const QObject **sender*, const char **signal*, const QObject **receiver*, const char **method*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| ----------------------- | ------------------------------------------------------------ |
| QMetaObject::Connection | **[connect](https://doc.qt.io/qt-6/qobject.html#connect-1)**(const QObject **sender*, const QMetaMethod &*signal*, const QObject **receiver*, const QMetaMethod &*method*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| QMetaObject::Connection | **[connect](https://doc.qt.io/qt-6/qobject.html#connect-3)**(const QObject **sender*, PointerToMemberFunction *signal*, const QObject **receiver*, PointerToMemberFunction *method*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| QMetaObject::Connection | **[connect](https://doc.qt.io/qt-6/qobject.html#connect-4)**(const QObject **sender*, PointerToMemberFunction *signal*, Functor *functor*) |
| QMetaObject::Connection | **[connect](https://doc.qt.io/qt-6/qobject.html#connect-5)**(const QObject **sender*, PointerToMemberFunction *signal*, const QObject **context*, Functor *functor*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| bool                    | **[disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)**(const QObject **sender*, const char **signal*, const QObject **receiver*, const char **method*) |
| bool                    | **[disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect-1)**(const QObject **sender*, const QMetaMethod &*signal*, const QObject **receiver*, const QMetaMethod &*method*) |
| bool                    | **[disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect-4)**(const QMetaObject::Connection &*connection*) |
| bool                    | **[disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect-5)**(const QObject **sender*, PointerToMemberFunction *signal*, const QObject **receiver*, PointerToMemberFunction *method*) |
| const QMetaObject       | **[staticMetaObject](https://doc.qt.io/qt-6/qobject.html#staticMetaObject-var)** |
| QString                 | **[tr](https://doc.qt.io/qt-6/qobject.html#tr)**(const char **sourceText*, const char **disambiguation* = nullptr, int *n* = -1) |

## Protected Functions

| virtual void | **[childEvent](https://doc.qt.io/qt-6/qobject.html#childEvent)**(QChildEvent **event*) |
| ------------ | ------------------------------------------------------------ |
| virtual void | **[connectNotify](https://doc.qt.io/qt-6/qobject.html#connectNotify)**(const QMetaMethod &*signal*) |
| virtual void | **[customEvent](https://doc.qt.io/qt-6/qobject.html#customEvent)**(QEvent **event*) |
| virtual void | **[disconnectNotify](https://doc.qt.io/qt-6/qobject.html#disconnectNotify)**(const QMetaMethod &*signal*) |
| bool         | **[isSignalConnected](https://doc.qt.io/qt-6/qobject.html#isSignalConnected)**(const QMetaMethod &*signal*) const |
| int          | **[receivers](https://doc.qt.io/qt-6/qobject.html#receivers)**(const char **signal*) const |
| QObject *    | **[sender](https://doc.qt.io/qt-6/qobject.html#sender)**() const |
| int          | **[senderSignalIndex](https://doc.qt.io/qt-6/qobject.html#senderSignalIndex)**() const |
| virtual void | **[timerEvent](https://doc.qt.io/qt-6/qobject.html#timerEvent)**(QTimerEvent **event*) |

## Related Non-Members

|      | **[QObjectList](https://doc.qt.io/qt-6/qobject.html#QObjectList-typedef)** |
| ---- | ------------------------------------------------------------ |
| T    | **[qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast)**(QObject **object*) |
| T    | **[qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast-1)**(const QObject **object*) |

## Macros

|      | **[QT_NO_NARROWING_CONVERSIONS_IN_CONNECT](https://doc.qt.io/qt-6/qobject.html#QT_NO_NARROWING_CONVERSIONS_IN_CONNECT)** |
| ---- | ------------------------------------------------------------ |
|      | **[Q_CLASSINFO](https://doc.qt.io/qt-6/qobject.html#Q_CLASSINFO)**(*Name*, *Value*) |
|      | **[Q_EMIT](https://doc.qt.io/qt-6/qobject.html#Q_EMIT)**     |
|      | **[Q_ENUM](https://doc.qt.io/qt-6/qobject.html#Q_ENUM)**(...) |
|      | **[Q_ENUM_NS](https://doc.qt.io/qt-6/qobject.html#Q_ENUM_NS)**(...) |
|      | **[Q_FLAG](https://doc.qt.io/qt-6/qobject.html#Q_FLAG)**(...) |
|      | **[Q_FLAG_NS](https://doc.qt.io/qt-6/qobject.html#Q_FLAG_NS)**(...) |
|      | **[Q_GADGET](https://doc.qt.io/qt-6/qobject.html#Q_GADGET)** |
|      | **[Q_GADGET_EXPORT](https://doc.qt.io/qt-6/qobject.html#Q_GADGET_EXPORT)**(*EXPORT_MACRO*) |
|      | **[Q_INTERFACES](https://doc.qt.io/qt-6/qobject.html#Q_INTERFACES)**(...) |
|      | **[Q_INVOKABLE](https://doc.qt.io/qt-6/qobject.html#Q_INVOKABLE)** |
|      | **[Q_MOC_INCLUDE](https://doc.qt.io/qt-6/qobject.html#Q_MOC_INCLUDE)** |
|      | **[Q_NAMESPACE](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE)** |
|      | **[Q_NAMESPACE_EXPORT](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE_EXPORT)**(*EXPORT_MACRO*) |
|      | **[Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT)** |
|      | **[Q_PROPERTY](https://doc.qt.io/qt-6/qobject.html#Q_PROPERTY)**(...) |
|      | **[Q_REVISION](https://doc.qt.io/qt-6/qobject.html#Q_REVISION)** |
|      | **[Q_SET_OBJECT_NAME](https://doc.qt.io/qt-6/qobject.html#Q_SET_OBJECT_NAME)**(*Object*) |
|      | **[Q_SIGNAL](https://doc.qt.io/qt-6/qobject.html#Q_SIGNAL)** |
|      | **[Q_SIGNALS](https://doc.qt.io/qt-6/qobject.html#Q_SIGNALS)** |
|      | **[Q_SLOT](https://doc.qt.io/qt-6/qobject.html#Q_SLOT)**     |
|      | **[Q_SLOTS](https://doc.qt.io/qt-6/qobject.html#Q_SLOTS)**   |

## Detailed Description

QObject is the heart of the Qt [Object Model](https://doc.qt.io/qt-6/object.html). The central feature in this model is a very powerful mechanism for seamless object communication called [signals and slots](https://doc.qt.io/qt-6/signalsandslots.html). You can connect a signal to a slot with [connect](https://doc.qt.io/qt-6/qobject.html#connect)() and destroy the connection with [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)(). To avoid never ending notification loops you can temporarily block signals with [blockSignals](https://doc.qt.io/qt-6/qobject.html#blockSignals)(). The protected functions [connectNotify](https://doc.qt.io/qt-6/qobject.html#connectNotify)() and [disconnectNotify](https://doc.qt.io/qt-6/qobject.html#disconnectNotify)() make it possible to track connections.

QObjects organize themselves in [object trees](https://doc.qt.io/qt-6/objecttrees.html). When you create a QObject with another object as parent, the object will automatically add itself to the parent's [children](https://doc.qt.io/qt-6/qobject.html#children)() list. The parent takes ownership of the object; i.e., it will automatically delete its children in its destructor. You can look for an object by name and optionally type using [findChild](https://doc.qt.io/qt-6/qobject.html#findChild)() or [findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)().

Every object has an [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop)() and its class name can be found via the corresponding [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)() (see [QMetaObject::className](https://doc.qt.io/qt-6/qmetaobject.html#className)()). You can determine whether the object's class inherits another class in the QObject inheritance hierarchy by using the [inherits](https://doc.qt.io/qt-6/qobject.html#inherits)() function.

When an object is deleted, it emits a [destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() signal. You can catch this signal to avoid dangling references to QObjects.

QObjects can receive events through [event](https://doc.qt.io/qt-6/qobject.html#event)() and filter the events of other objects. See [installEventFilter](https://doc.qt.io/qt-6/qobject.html#installEventFilter)() and [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)() for details. A convenience handler, [childEvent](https://doc.qt.io/qt-6/qobject.html#childEvent)(), can be reimplemented to catch child events.

Last but not least, QObject provides the basic timer support in Qt; see [QTimer](https://doc.qt.io/qt-6/qtimer.html) for high-level support for timers.

Notice that the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro is mandatory for any object that implements signals, slots or properties. You also need to run the [Meta Object Compiler](https://doc.qt.io/qt-6/moc.html) on the source file. We strongly recommend the use of this macro in all subclasses of QObject regardless of whether or not they actually use signals, slots and properties, since failure to do so may lead certain functions to exhibit strange behavior.

All Qt widgets inherit QObject. The convenience function [isWidgetType](https://doc.qt.io/qt-6/qobject.html#isWidgetType)() returns whether an object is actually a widget. It is much faster than [qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast)< [QWidget](https://doc.qt.io/qt-6/qwidget.html) *>(*obj*) or *obj*->[inherits](https://doc.qt.io/qt-6/qobject.html#inherits)("[QWidget](https://doc.qt.io/qt-6/qwidget.html)").

Some QObject functions, e.g. [children](https://doc.qt.io/qt-6/qobject.html#children)(), return a [QObjectList](https://doc.qt.io/qt-6/qobject.html#QObjectList-typedef). [QObjectList](https://doc.qt.io/qt-6/qobject.html#QObjectList-typedef) is a typedef for [QList](https://doc.qt.io/qt-6/qlist.html)< QObject *>.

### Thread Affinity

A QObject instance is said to have a *thread affinity*, or that it *lives* in a certain thread. When a QObject receives a [queued signal](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) or a [posted event](https://doc.qt.io/qt-6/eventsandfilters.html#sending-events), the slot or event handler will run in the thread that the object lives in.

**Note:** If a QObject has no thread affinity (that is, if [thread](https://doc.qt.io/qt-6/qobject.html#thread)() returns zero), or if it lives in a thread that has no running event loop, then it cannot receive queued signals or posted events.

By default, a QObject lives in the thread in which it is created. An object's thread affinity can be queried using [thread](https://doc.qt.io/qt-6/qobject.html#thread)() and changed using [moveToThread](https://doc.qt.io/qt-6/qobject.html#moveToThread)().

All QObjects must live in the same thread as their parent. Consequently:

- [setParent](https://doc.qt.io/qt-6/qobject.html#setParent)() will fail if the two QObjects involved live in different threads.
- When a QObject is moved to another thread, all its children will be automatically moved too.
- [moveToThread](https://doc.qt.io/qt-6/qobject.html#moveToThread)() will fail if the QObject has a parent.
- If QObjects are created within [QThread::run](https://doc.qt.io/qt-6/qthread.html#run)(), they cannot become children of the [QThread](https://doc.qt.io/qt-6/qthread.html) object because the [QThread](https://doc.qt.io/qt-6/qthread.html) does not live in the thread that calls [QThread::run](https://doc.qt.io/qt-6/qthread.html#run)().

**Note:** A QObject's member variables *do not* automatically become its children. The parent-child relationship must be set by either passing a pointer to the child's [constructor](https://doc.qt.io/qt-6/qobject.html#QObject), or by calling [setParent](https://doc.qt.io/qt-6/qobject.html#setParent)(). Without this step, the object's member variables will remain in the old thread when [moveToThread](https://doc.qt.io/qt-6/qobject.html#moveToThread)() is called.



### No Copy Constructor or Assignment Operator

QObject has neither a copy constructor nor an assignment operator. This is by design. Actually, they are declared, but in a `private` section with the macro [Q_DISABLE_COPY](https://doc.qt.io/qt-6/qtclasshelpermacros-qtcore-proxy.html#Q_DISABLE_COPY)(). In fact, all Qt classes derived from QObject (direct or indirect) use this macro to declare their copy constructor and assignment operator to be private. The reasoning is found in the discussion on [Identity vs Value](https://doc.qt.io/qt-6/object.html#identity-vs-value) on the Qt [Object Model](https://doc.qt.io/qt-6/object.html) page.

The main consequence is that you should use pointers to QObject (or to your QObject subclass) where you might otherwise be tempted to use your QObject subclass as a value. For example, without a copy constructor, you can't use a subclass of QObject as the value to be stored in one of the container classes. You must store pointers.

### Auto-Connection

Qt's meta-object system provides a mechanism to automatically connect signals and slots between QObject subclasses and their children. As long as objects are defined with suitable object names, and slots follow a simple naming convention, this connection can be performed at run-time by the [QMetaObject::connectSlotsByName](https://doc.qt.io/qt-6/qmetaobject.html#connectSlotsByName)() function.

[uic](https://doc.qt.io/qt-6/uic.html) generates code that invokes this function to enable auto-connection to be performed between widgets on forms created with *Qt Designer*. More information about using auto-connection with *Qt Designer* is given in the [Using a Designer UI File in Your Application](https://doc.qt.io/qt-6/designer-using-a-ui-file.html) section of the *Qt Designer* manual.

### Dynamic Properties

From Qt 4.2, dynamic properties can be added to and removed from QObject instances at run-time. Dynamic properties do not need to be declared at compile-time, yet they provide the same advantages as static properties and are manipulated using the same API - using [property](https://doc.qt.io/qt-6/qobject.html#property)() to read them and [setProperty](https://doc.qt.io/qt-6/qobject.html#setProperty)() to write them.

From Qt 4.3, dynamic properties are supported by [Qt Designer](https://doc.qt.io/qt-6/designer-widget-mode.html#the-property-editor), and both standard Qt widgets and user-created forms can be given dynamic properties.

### Internationalization (I18n)

All QObject subclasses support Qt's translation features, making it possible to translate an application's user interface into different languages.

To make user-visible text translatable, it must be wrapped in calls to the [tr](https://doc.qt.io/qt-6/qobject.html#tr)() function. This is explained in detail in the [Writing Source Code for Translation](https://doc.qt.io/qt-6/i18n-source-translation.html) document.

**See also** [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html), [QPointer](https://doc.qt.io/qt-6/qpointer.html), [QObjectCleanupHandler](https://doc.qt.io/qt-6/qobjectcleanuphandler.html), [Q_DISABLE_COPY](https://doc.qt.io/qt-6/qtclasshelpermacros-qtcore-proxy.html#Q_DISABLE_COPY)(), and [Object Trees & Ownership](https://doc.qt.io/qt-6/objecttrees.html).

## Property Documentation

### `[bindable]`objectName : [QString](https://doc.qt.io/qt-6/qstring.html)

**Note:** This property supports [QProperty](https://doc.qt.io/qt-6/qproperty.html) bindings.

This property holds the name of this object

You can find an object by name (and type) using [findChild](https://doc.qt.io/qt-6/qobject.html#findChild)(). You can find a set of objects with [findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)().

```
qDebug("MyClass::setPrecision(): (%s) invalid precision %f",
       qPrintable(objectName()), newPrecision);
```

By default, this property contains an empty string.

**See also** [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)() and [QMetaObject::className](https://doc.qt.io/qt-6/qmetaobject.html#className)().

## Member Function Documentation

### `[explicit invokable]`QObject::QObject([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **parent* = nullptr)

Constructs an object with parent object *parent*.

The parent of an object may be viewed as the object's owner. For instance, a [dialog box](https://doc.qt.io/qt-6/qdialog.html) is the parent of the **OK** and **Cancel** buttons it contains.

The destructor of a parent object destroys all child objects.

Setting *parent* to `nullptr` constructs an object with no parent. If the object is a widget, it will become a top-level window.

**Note:** This function can be invoked via the meta-object system and from QML. See [Q_INVOKABLE](https://doc.qt.io/qt-6/qobject.html#Q_INVOKABLE).

**See also** [parent](https://doc.qt.io/qt-6/qobject.html#parent)(), [findChild](https://doc.qt.io/qt-6/qobject.html#findChild)(), and [findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)().

### `[virtual noexcept]`QObject::~QObject()

Destroys the object, deleting all its child objects.

All signals to and from the object are automatically disconnected, and any pending posted events for the object are removed from the event queue. However, it is often safer to use [deleteLater](https://doc.qt.io/qt-6/qobject.html#deleteLater)() rather than deleting a [QObject](https://doc.qt.io/qt-6/qobject.html) subclass directly.

**Warning:** All child objects are deleted. If any of these objects are on the stack or global, sooner or later your program will crash. We do not recommend holding pointers to child objects from outside the parent. If you still do, the [destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() signal gives you an opportunity to detect when an object is destroyed.

**Warning:** Deleting a [QObject](https://doc.qt.io/qt-6/qobject.html) while pending events are waiting to be delivered can cause a crash. You must not delete the [QObject](https://doc.qt.io/qt-6/qobject.html) directly if it exists in a different thread than the one currently executing. Use [deleteLater](https://doc.qt.io/qt-6/qobject.html#deleteLater)() instead, which will cause the event loop to delete the object after all pending events have been delivered to it.

**See also** [deleteLater](https://doc.qt.io/qt-6/qobject.html#deleteLater)().

### `[noexcept]`bool QObject::blockSignals(bool *block*)

If *block* is true, signals emitted by this object are blocked (i.e., emitting a signal will not invoke anything connected to it). If *block* is false, no such blocking will occur.

The return value is the previous value of [signalsBlocked](https://doc.qt.io/qt-6/qobject.html#signalsBlocked)().

Note that the [destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() signal will be emitted even if the signals for this object have been blocked.

Signals emitted while being blocked are not buffered.

**See also** [signalsBlocked](https://doc.qt.io/qt-6/qobject.html#signalsBlocked)() and [QSignalBlocker](https://doc.qt.io/qt-6/qsignalblocker.html).

### `[virtual protected]`void QObject::childEvent([QChildEvent](https://doc.qt.io/qt-6/qchildevent.html) **event*)

This event handler can be reimplemented in a subclass to receive child events. The event is passed in the *event* parameter.

[QEvent::ChildAdded](https://doc.qt.io/qt-6/qevent.html#Type-enum) and [QEvent::ChildRemoved](https://doc.qt.io/qt-6/qevent.html#Type-enum) events are sent to objects when children are added or removed. In both cases you can only rely on the child being a [QObject](https://doc.qt.io/qt-6/qobject.html), or if [isWidgetType](https://doc.qt.io/qt-6/qobject.html#isWidgetType)() returns `true`, a [QWidget](https://doc.qt.io/qt-6/qwidget.html). (This is because, in the [ChildAdded](https://doc.qt.io/qt-6/qevent.html#Type-enum) case, the child is not yet fully constructed, and in the [ChildRemoved](https://doc.qt.io/qt-6/qevent.html#Type-enum) case it might have been destructed already).

[QEvent::ChildPolished](https://doc.qt.io/qt-6/qevent.html#Type-enum) events are sent to widgets when children are polished, or when polished children are added. If you receive a child polished event, the child's construction is usually completed. However, this is not guaranteed, and multiple polish events may be delivered during the execution of a widget's constructor.

For every child widget, you receive one [ChildAdded](https://doc.qt.io/qt-6/qevent.html#Type-enum) event, zero or more [ChildPolished](https://doc.qt.io/qt-6/qevent.html#Type-enum) events, and one [ChildRemoved](https://doc.qt.io/qt-6/qevent.html#Type-enum) event.

The [ChildPolished](https://doc.qt.io/qt-6/qevent.html#Type-enum) event is omitted if a child is removed immediately after it is added. If a child is polished several times during construction and destruction, you may receive several child polished events for the same child, each time with a different virtual table.

**See also** [event](https://doc.qt.io/qt-6/qobject.html#event)().

### const [QObjectList](https://doc.qt.io/qt-6/qobject.html#QObjectList-typedef) &QObject::children() const

Returns a list of child objects. The [QObjectList](https://doc.qt.io/qt-6/qobject.html#QObjectList-typedef) class is defined in the `< QObject>` header file as the following:

```
typedef QList< QObject*> QObjectList;
```

The first child added is the [first](https://doc.qt.io/qt-6/qlist.html#first) object in the list and the last child added is the [last](https://doc.qt.io/qt-6/qlist.html#last) object in the list, i.e. new children are appended at the end.

Note that the list order changes when [QWidget](https://doc.qt.io/qt-6/qwidget.html) children are [raised](https://doc.qt.io/qt-6/qwidget.html#raise) or [lowered](https://doc.qt.io/qt-6/qwidget.html#lower). A widget that is raised becomes the last object in the list, and a widget that is lowered becomes the first object in the list.

**See also** [findChild](https://doc.qt.io/qt-6/qobject.html#findChild)(), [findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)(), [parent](https://doc.qt.io/qt-6/qobject.html#parent)(), and [setParent](https://doc.qt.io/qt-6/qobject.html#setParent)().

### `[static]`[QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) QObject::connect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, const char **signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, const char **method*, [Qt::ConnectionType](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type* = Qt::AutoConnection)

Creates a connection of the given *type* from the *signal* in the *sender* object to the *method* in the *receiver* object. Returns a handle to the connection that can be used to disconnect it later.

You must use the `SIGNAL()` and `SLOT()` macros when specifying the *signal* and the *method*, for example:

```
QLabel *label = new QLabel;
QScrollBar *scrollBar = new QScrollBar;
QObject::connect(scrollBar, SIGNAL(valueChanged(int)),
                 label,  SLOT(setNum(int)));
```

This example ensures that the label always displays the current scroll bar value. Note that the signal and slots parameters must not contain any variable names, only the type. E.g. the following would not work and return false:

```
// WRONG
QObject::connect(scrollBar, SIGNAL(valueChanged(int value)),
                 label, SLOT(setNum(int value)));
```

A signal can also be connected to another signal:

```
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget();

signals:
    void buttonClicked();

private:
    QPushButton *myButton;
};

MyWidget::MyWidget()
{
    myButton = new QPushButton(this);
    connect(myButton, SIGNAL(clicked()),
            this, SIGNAL(buttonClicked()));
}
```

In this example, the `MyWidget` constructor relays a signal from a private member variable, and makes it available under a name that relates to `MyWidget`.

A signal can be connected to many slots and signals. Many signals can be connected to one slot.

If a signal is connected to several slots, the slots are activated in the same order in which the connections were made, when the signal is emitted.

The function returns a [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) that represents a handle to a connection if it successfully connects the signal to the slot. The connection handle will be invalid if it cannot create the connection, for example, if [QObject](https://doc.qt.io/qt-6/qobject.html) is unable to verify the existence of either *signal* or *method*, or if their signatures aren't compatible. You can check if the handle is valid by casting it to a bool.

By default, a signal is emitted for every connection you make; two signals are emitted for duplicate connections. You can break all of these connections with a single [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)() call. If you pass the [Qt::UniqueConnection](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type*, the connection will only be made if it is not a duplicate. If there is already a duplicate (exact same signal to the exact same slot on the same objects), the connection will fail and connect will return an invalid [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html).

**Note:** Qt::UniqueConnections do not work for lambdas, non-member functions and functors; they only apply to connecting to member functions.

The optional *type* parameter describes the type of connection to establish. In particular, it determines whether a particular signal is delivered to a slot immediately or queued for delivery at a later time. If the signal is queued, the parameters must be of types that are known to Qt's meta-object system, because Qt needs to copy the arguments to store them in an event behind the scenes. If you try to use a queued connection and get the error message

```
QObject::connect: Cannot queue arguments of type 'MyType'
(Make sure 'MyType' is registered using qRegisterMetaType().)
```

call [qRegisterMetaType](https://doc.qt.io/qt-6/qmetatype.html#qRegisterMetaType-3)() to register the data type before you establish the connection.

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

**See also** [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)(), [sender](https://doc.qt.io/qt-6/qobject.html#sender)(), [qRegisterMetaType](https://doc.qt.io/qt-6/qmetatype.html#qRegisterMetaType-3)(), [Q_DECLARE_METATYPE](https://doc.qt.io/qt-6/qmetatype.html#Q_DECLARE_METATYPE)(), and [Differences between String-Based and Functor-Based Connections](https://doc.qt.io/qt-6/signalsandslots-syntaxes.html).

### `[static]`[QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) QObject::connect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*method*, [Qt::ConnectionType](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type* = Qt::AutoConnection)

Creates a connection of the given *type* from the *signal* in the *sender* object to the *method* in the *receiver* object. Returns a handle to the connection that can be used to disconnect it later.

The Connection handle will be invalid if it cannot create the connection, for example, the parameters were invalid. You can check if the [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) is valid by casting it to a bool.

This function works in the same way as `connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type)` but it uses [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) to specify signal and method.

**See also** [connect](https://doc.qt.io/qt-6/qobject.html#connect)(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type).

### [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) QObject::connect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, const char **signal*, const char **method*, [Qt::ConnectionType](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type* = Qt::AutoConnection) const

This function overloads connect().

Connects *signal* from the *sender* object to this object's *method*.

Equivalent to connect(*sender*, *signal*, `this`, *method*, *type*).

Every connection you make emits a signal, so duplicate connections emit two signals. You can break a connection using [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)().

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

**See also** [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)().

### `[static]`template < typename PointerToMemberFunction> [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) QObject::connect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, PointerToMemberFunction *signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, PointerToMemberFunction *method*, [Qt::ConnectionType](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type* = Qt::AutoConnection)

This function overloads connect().

Creates a connection of the given *type* from the *signal* in the *sender* object to the *method* in the *receiver* object. Returns a handle to the connection that can be used to disconnect it later.

The signal must be a function declared as a signal in the header. The slot function can be any member function that can be connected to the signal. A slot can be connected to a given signal if the signal has at least as many arguments as the slot, and there is an implicit conversion between the types of the corresponding arguments in the signal and the slot.

Example:

```
QLabel *label = new QLabel;
QLineEdit *lineEdit = new QLineEdit;
QObject::connect(lineEdit, &QLineEdit::textChanged,
                 label,  &QLabel::setText);
```

This example ensures that the label always displays the current line edit text.

A signal can be connected to many slots and signals. Many signals can be connected to one slot.

If a signal is connected to several slots, the slots are activated in the same order as the order the connection was made, when the signal is emitted

The function returns an handle to a connection if it successfully connects the signal to the slot. The Connection handle will be invalid if it cannot create the connection, for example, if [QObject](https://doc.qt.io/qt-6/qobject.html) is unable to verify the existence of *signal* (if it was not declared as a signal) You can check if the [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) is valid by casting it to a bool.

By default, a signal is emitted for every connection you make; two signals are emitted for duplicate connections. You can break all of these connections with a single [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)() call. If you pass the [Qt::UniqueConnection](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type*, the connection will only be made if it is not a duplicate. If there is already a duplicate (exact same signal to the exact same slot on the same objects), the connection will fail and connect will return an invalid [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html).

The optional *type* parameter describes the type of connection to establish. In particular, it determines whether a particular signal is delivered to a slot immediately or queued for delivery at a later time. If the signal is queued, the parameters must be of types that are known to Qt's meta-object system, because Qt needs to copy the arguments to store them in an event behind the scenes. If you try to use a queued connection and get the error message

```
QObject::connect: Cannot queue arguments of type 'MyType'
(Make sure 'MyType' is registered using qRegisterMetaType().)
```

make sure to declare the argument type with [Q_DECLARE_METATYPE](https://doc.qt.io/qt-6/qmetatype.html#Q_DECLARE_METATYPE)

Overloaded functions can be resolved with help of [qOverload](https://doc.qt.io/qt-6/qoverload-qtcore-proxy.html#qOverload).

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

**See also** [Differences between String-Based and Functor-Based Connections](https://doc.qt.io/qt-6/signalsandslots-syntaxes.html).

### `[static]`template < typename PointerToMemberFunction, typename Functor> [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) QObject::connect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, PointerToMemberFunction *signal*, Functor *functor*)

This function overloads connect().

Creates a connection from *signal* in *sender* object to *functor*, and returns a handle to the connection

The signal must be a function declared as a signal in the header. The slot function can be any function or functor that can be connected to the signal. A slot function can be connected to a given signal if the signal has at least as many arguments as the slot function. There must exist implicit conversion between the types of the corresponding arguments in the signal and the slot.

Example:

```
void someFunction();
QPushButton *button = new QPushButton;
QObject::connect(button, &QPushButton::clicked, someFunction);
```

Lambda expressions can also be used:

```
QByteArray page = ...;
QTcpSocket *socket = new QTcpSocket;
socket->connectToHost("qt-project.org", 80);
QObject::connect(socket, &QTcpSocket::connected, [=] () {
        socket->write("GET " + page + "\r\n");
    });
```

The connection will automatically disconnect if the sender is destroyed. However, you should take care that any objects used within the functor are still alive when the signal is emitted.

Overloaded functions can be resolved with help of [qOverload](https://doc.qt.io/qt-6/qoverload-qtcore-proxy.html#qOverload).

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

### `[static]`template < typename PointerToMemberFunction, typename Functor> [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) QObject::connect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, PointerToMemberFunction *signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **context*, Functor *functor*, [Qt::ConnectionType](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) *type* = Qt::AutoConnection)

This function overloads connect().

Creates a connection of a given *type* from *signal* in *sender* object to *functor* to be placed in a specific event loop of *context*, and returns a handle to the connection.

**Note:** Qt::UniqueConnections do not work for lambdas, non-member functions and functors; they only apply to connecting to member functions.

The signal must be a function declared as a signal in the header. The slot function can be any function or functor that can be connected to the signal. A slot function can be connected to a given signal if the signal has at least as many arguments as the slot function. There must exist implicit conversion between the types of the corresponding arguments in the signal and the slot.

Example:

```
void someFunction();
QPushButton *button = new QPushButton;
QObject::connect(button, &QPushButton::clicked, this, someFunction, Qt::QueuedConnection);
```

Lambda expressions can also be used:

```
QByteArray page = ...;
QTcpSocket *socket = new QTcpSocket;
socket->connectToHost("qt-project.org", 80);
QObject::connect(socket, &QTcpSocket::connected, this, [=] () {
        socket->write("GET " + page + "\r\n");
    }, Qt::AutoConnection);
```

The connection will automatically disconnect if the sender or the context is destroyed. However, you should take care that any objects used within the functor are still alive when the signal is emitted.

Overloaded functions can be resolved with help of [qOverload](https://doc.qt.io/qt-6/qoverload-qtcore-proxy.html#qOverload).

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

### `[virtual protected]`void QObject::connectNotify(const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*signal*)

This virtual function is called when something has been connected to *signal* in this object.

If you want to compare *signal* with a specific signal, you can use [QMetaMethod::fromSignal](https://doc.qt.io/qt-6/qmetamethod.html#fromSignal)() as follows:

```
if (signal == QMetaMethod::fromSignal(&MyObject::valueChanged)) {
    // signal is valueChanged
}
```

**Warning:** This function violates the object-oriented principle of modularity. However, it might be useful when you need to perform expensive initialization only if something is connected to a signal.

**Warning:** This function is called from the thread which performs the connection, which may be a different thread from the thread in which this object lives. This function may also be called with a [QObject](https://doc.qt.io/qt-6/qobject.html) internal mutex locked. It is therefore not allowed to re-enter any [QObject](https://doc.qt.io/qt-6/qobject.html) functions, including [isSignalConnected](https://doc.qt.io/qt-6/qobject.html#isSignalConnected)(), from your reimplementation. If you lock a mutex in your reimplementation, make sure that you don't call [QObject](https://doc.qt.io/qt-6/qobject.html) functions with that mutex held in other places or it will result in a deadlock.

**See also** [connect](https://doc.qt.io/qt-6/qobject.html#connect)() and [disconnectNotify](https://doc.qt.io/qt-6/qobject.html#disconnectNotify)().

### `[virtual protected]`void QObject::customEvent([QEvent](https://doc.qt.io/qt-6/qevent.html) **event*)

This event handler can be reimplemented in a subclass to receive custom events. Custom events are user-defined events with a type value at least as large as the [QEvent::User](https://doc.qt.io/qt-6/qevent.html#Type-enum) item of the [QEvent::Type](https://doc.qt.io/qt-6/qevent.html#Type-enum) enum, and is typically a [QEvent](https://doc.qt.io/qt-6/qevent.html) subclass. The event is passed in the *event* parameter.

**See also** [event](https://doc.qt.io/qt-6/qobject.html#event)() and [QEvent](https://doc.qt.io/qt-6/qevent.html).

### `[slot]`void QObject::deleteLater()

Schedules this object for deletion.

The object will be deleted when control returns to the event loop. If the event loop is not running when this function is called (e.g. deleteLater() is called on an object before [QCoreApplication::exec](https://doc.qt.io/qt-6/qcoreapplication.html#exec)()), the object will be deleted once the event loop is started. If deleteLater() is called after the main event loop has stopped, the object will not be deleted. Since Qt 4.8, if deleteLater() is called on an object that lives in a thread with no running event loop, the object will be destroyed when the thread finishes.

Note that entering and leaving a new event loop (e.g., by opening a modal dialog) will *not* perform the deferred deletion; for the object to be deleted, the control must return to the event loop from which deleteLater() was called. This does not apply to objects deleted while a previous, nested event loop was still running: the Qt event loop will delete those objects as soon as the new nested event loop starts.

**Note:** It is safe to call this function more than once; when the first deferred deletion event is delivered, any pending events for the object are removed from the event queue.

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

**See also** [destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() and [QPointer](https://doc.qt.io/qt-6/qpointer.html).

### `[signal]`void QObject::destroyed([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **obj* = nullptr)

This signal is emitted immediately before the object *obj* is destroyed, after any instances of [QPointer](https://doc.qt.io/qt-6/qpointer.html) have been notified, and cannot be blocked.

All the objects's children are destroyed immediately after this signal is emitted.

**See also** [deleteLater](https://doc.qt.io/qt-6/qobject.html#deleteLater)() and [QPointer](https://doc.qt.io/qt-6/qpointer.html).

### `[static]`bool QObject::disconnect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, const char **signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, const char **method*)

Disconnects *signal* in object *sender* from *method* in object *receiver*. Returns `true` if the connection is successfully broken; otherwise returns `false`.

A signal-slot connection is removed when either of the objects involved are destroyed.

disconnect() is typically used in three ways, as the following examples demonstrate.

1. Disconnect everything connected to an object's signals:

   ```
   disconnect(myObject, nullptr, nullptr, nullptr);
   ```

   equivalent to the non-static overloaded function

   ```
   myObject->disconnect();
   ```

2. Disconnect everything connected to a specific signal:

   ```
   disconnect(myObject, SIGNAL(mySignal()), nullptr, nullptr);
   ```

   equivalent to the non-static overloaded function

   ```
   myObject->disconnect(SIGNAL(mySignal()));
   ```

3. Disconnect a specific receiver:

   ```
   disconnect(myObject, nullptr, myReceiver, nullptr);
   ```

   equivalent to the non-static overloaded function

   ```
   myObject->disconnect(myReceiver);
   ```

`nullptr` may be used as a wildcard, meaning "any signal", "any receiving object", or "any slot in the receiving object", respectively.

The *sender* may never be `nullptr`. (You cannot disconnect signals from more than one object in a single call.)

If *signal* is `nullptr`, it disconnects *receiver* and *method* from any signal. If not, only the specified signal is disconnected.

If *receiver* is `nullptr`, it disconnects anything connected to *signal*. If not, slots in objects other than *receiver* are not disconnected.

If *method* is `nullptr`, it disconnects anything that is connected to *receiver*. If not, only slots named *method* will be disconnected, and all other slots are left alone. The *method* must be `nullptr` if *receiver* is left out, so you cannot disconnect a specifically-named slot on all objects.

**Note:** Disconnecting all signal-slot connections will also disconnect the [QObject::destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() signal if it is connected. Doing so can adversely affect classes that rely on this signal for cleaning up resources. It is recommended to disconnect only the specific signals that were connected by application code.

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

**See also** [connect](https://doc.qt.io/qt-6/qobject.html#connect)().

### `[static]`bool QObject::disconnect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*method*)

Disconnects *signal* in object *sender* from *method* in object *receiver*. Returns `true` if the connection is successfully broken; otherwise returns `false`.

This function provides the same possibilities like `disconnect(const QObject *sender, const char *signal, const QObject *receiver, const char *method)` but uses [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) to represent the signal and the method to be disconnected.

Additionally this function returns false and no signals and slots disconnected if:

1. *signal* is not a member of sender class or one of its parent classes.
2. *method* is not a member of receiver class or one of its parent classes.
3. *signal* instance represents not a signal.

QMetaMethod() may be used as wildcard in the meaning "any signal" or "any slot in receiving object". In the same way `nullptr` can be used for *receiver* in the meaning "any receiving object". In this case method should also be QMetaMethod(). *sender* parameter should be never `nullptr`.

**Note:** Disconnecting all signal-slot connections will also disconnect the [QObject::destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() signal if it is connected. Doing so can adversely affect classes that rely on this signal for cleaning up resources. It is recommended to disconnect only the specific signals that were connected by application code.

**See also** [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)(const QObject *sender, const char *signal, const QObject *receiver, const char *method).

### bool QObject::disconnect(const char **signal* = nullptr, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver* = nullptr, const char **method* = nullptr) const

This function overloads disconnect().

Disconnects *signal* from *method* of *receiver*.

A signal-slot connection is removed when either of the objects involved are destroyed.

**Note:** Disconnecting all signal-slot connections will also disconnect the [QObject::destroyed](https://doc.qt.io/qt-6/qobject.html#destroyed)() signal if it is connected. Doing so can adversely affect classes that rely on this signal for cleaning up resources. It is recommended to disconnect only the specific signals that were connected by application code.

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

### bool QObject::disconnect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, const char **method* = nullptr) const

This function overloads disconnect().

Disconnects all signals in this object from *receiver*'s *method*.

A signal-slot connection is removed when either of the objects involved are destroyed.

### `[static]`bool QObject::disconnect(const [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html) &*connection*)

Disconnect a connection.

If the *connection* is invalid or has already been disconnected, do nothing and return false.

**See also** [connect](https://doc.qt.io/qt-6/qobject.html#connect)().

### `[static]`template < typename PointerToMemberFunction> bool QObject::disconnect(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **sender*, PointerToMemberFunction *signal*, const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **receiver*, PointerToMemberFunction *method*)

This function overloads disconnect().

Disconnects *signal* in object *sender* from *method* in object *receiver*. Returns `true` if the connection is successfully broken; otherwise returns `false`.

A signal-slot connection is removed when either of the objects involved are destroyed.

disconnect() is typically used in three ways, as the following examples demonstrate.

1. Disconnect everything connected to an object's signals:

   ```
   disconnect(myObject, nullptr, nullptr, nullptr);
   ```

2. Disconnect everything connected to a specific signal:

   ```
   disconnect(myObject, &MyObject::mySignal(), nullptr, nullptr);
   ```

3. Disconnect a specific receiver:

   ```
   disconnect(myObject, nullptr, myReceiver, nullptr);
   ```

4. Disconnect a connection from one specific signal to a specific slot:

   ```
   QObject::disconnect(lineEdit, &QLineEdit::textChanged,
                    label,  &QLabel::setText);
   ```

`nullptr` may be used as a wildcard, meaning "any signal", "any receiving object", or "any slot in the receiving object", respectively.

The *sender* may never be `nullptr`. (You cannot disconnect signals from more than one object in a single call.)

If *signal* is `nullptr`, it disconnects *receiver* and *method* from any signal. If not, only the specified signal is disconnected.

If *receiver* is `nullptr`, it disconnects anything connected to *signal*. If not, only slots in the specified receiver are disconnected. disconnect() with a non-null *receiver* also disconnects slot functions that were connected with *receiver* as their context object.

If *method* is `nullptr`, it disconnects anything that is connected to *receiver*. If not, only slots named *method* will be disconnected, and all other slots are left alone. The *method* must be `nullptr` if *receiver* is left out, so you cannot disconnect a specifically-named slot on all objects.

**Note:** It is not possible to use this overload to disconnect signals connected to functors or lambda expressions. That is because it is not possible to compare them. Instead, use the overload that takes a [QMetaObject::Connection](https://doc.qt.io/qt-6/qmetaobject-connection.html)

**Note:** This function is [thread-safe](https://doc.qt.io/qt-6/threads-reentrancy.html).

**See also** [connect](https://doc.qt.io/qt-6/qobject.html#connect)().

### `[virtual protected]`void QObject::disconnectNotify(const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*signal*)

This virtual function is called when something has been disconnected from *signal* in this object.

See [connectNotify](https://doc.qt.io/qt-6/qobject.html#connectNotify)() for an example of how to compare *signal* with a specific signal.

If all signals were disconnected from this object (e.g., the signal argument to [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)() was `nullptr`), disconnectNotify() is only called once, and the *signal* will be an invalid [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) ([QMetaMethod::isValid](https://doc.qt.io/qt-6/qmetamethod.html#isValid)() returns `false`).

**Warning:** This function violates the object-oriented principle of modularity. However, it might be useful for optimizing access to expensive resources.

**Warning:** This function is called from the thread which performs the disconnection, which may be a different thread from the thread in which this object lives. This function may also be called with a [QObject](https://doc.qt.io/qt-6/qobject.html) internal mutex locked. It is therefore not allowed to re-enter any [QObject](https://doc.qt.io/qt-6/qobject.html) functions, including [isSignalConnected](https://doc.qt.io/qt-6/qobject.html#isSignalConnected)(), from your reimplementation. If you lock a mutex in your reimplementation, make sure that you don't call [QObject](https://doc.qt.io/qt-6/qobject.html) functions with that mutex held in other places or it will result in a deadlock.

**See also** [disconnect](https://doc.qt.io/qt-6/qobject.html#disconnect)() and [connectNotify](https://doc.qt.io/qt-6/qobject.html#connectNotify)().

### void QObject::dumpObjectInfo() const

Dumps information about signal connections, etc. for this object to the debug output.

**Note:** Before Qt 5.9, this function was not const.

**See also** [dumpObjectTree](https://doc.qt.io/qt-6/qobject.html#dumpObjectTree)().

### void QObject::dumpObjectTree() const

Dumps a tree of children to the debug output.

**Note:** Before Qt 5.9, this function was not const.

**See also** [dumpObjectInfo](https://doc.qt.io/qt-6/qobject.html#dumpObjectInfo)().

### [QList](https://doc.qt.io/qt-6/qlist.html)< [QByteArray](https://doc.qt.io/qt-6/qbytearray.html)> QObject::dynamicPropertyNames() const

Returns the names of all properties that were dynamically added to the object using [setProperty](https://doc.qt.io/qt-6/qobject.html#setProperty)().

### `[virtual]`bool QObject::event([QEvent](https://doc.qt.io/qt-6/qevent.html) **e*)

This virtual function receives events to an object and should return true if the event *e* was recognized and processed.

The event() function can be reimplemented to customize the behavior of an object.

Make sure you call the parent event class implementation for all the events you did not handle.

Example:

```
class MyClass : public QWidget
{
    Q_OBJECT

public:
    MyClass(QWidget *parent = nullptr);
    ~MyClass();

    bool event(QEvent* ev) override
    {
        if (ev->type() == QEvent::PolishRequest) {
            // overwrite handling of PolishRequest if any
            doThings();
            return true;
        } else  if (ev->type() == QEvent::Show) {
            // complement handling of Show if any
            doThings2();
            QWidget::event(ev);
            return true;
        }
        // Make sure the rest of events are handled
        return QWidget::event(ev);
    }
};
```

**See also** [installEventFilter](https://doc.qt.io/qt-6/qobject.html#installEventFilter)(), [timerEvent](https://doc.qt.io/qt-6/qobject.html#timerEvent)(), [QCoreApplication::sendEvent](https://doc.qt.io/qt-6/qcoreapplication.html#sendEvent)(), and [QCoreApplication::postEvent](https://doc.qt.io/qt-6/qcoreapplication.html#postEvent)().

### `[virtual]`bool QObject::eventFilter([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **watched*, [QEvent](https://doc.qt.io/qt-6/qevent.html) **event*)

Filters events if this object has been installed as an event filter for the *watched* object.

In your reimplementation of this function, if you want to filter the *event* out, i.e. stop it being handled further, return true; otherwise return false.

Example:

```
class MainWindow : public QMainWindow
{
public:
    MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private:
    QTextEdit *textEdit;
};

MainWindow::MainWindow()
{
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    textEdit->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == textEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast< QKeyEvent*>(event);
            qDebug() < <  "Ate key press" < <  keyEvent->key();
            return true;
        } else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}
```

Notice in the example above that unhandled events are passed to the base class's eventFilter() function, since the base class might have reimplemented eventFilter() for its own internal purposes.

Some events, such as [QEvent::ShortcutOverride](https://doc.qt.io/qt-6/qevent.html#Type-enum) must be explicitly accepted (by calling [accept](https://doc.qt.io/qt-6/qevent.html#accept)() on them) in order to prevent propagation.

**Warning:** If you delete the receiver object in this function, be sure to return true. Otherwise, Qt will forward the event to the deleted object and the program might crash.

**See also** [installEventFilter](https://doc.qt.io/qt-6/qobject.html#installEventFilter)().

### template < typename T> T QObject::findChild(const [QString](https://doc.qt.io/qt-6/qstring.html) &*name* = QString(), [Qt::FindChildOptions](https://doc.qt.io/qt-6/qt.html#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

Returns the child of this object that can be cast into type T and that is called *name*, or `nullptr` if there is no such object. Omitting the *name* argument causes all object names to be matched. The search is performed recursively, unless *options* specifies the option FindDirectChildrenOnly.

If there is more than one child matching the search, the most direct ancestor is returned. If there are several direct ancestors, it is undefined which one will be returned. In that case, [findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)() should be used.

This example returns a child `QPushButton` of `parentWidget` named `"button1"`, even if the button isn't a direct child of the parent:

```
QPushButton *button = parentWidget->findChild< QPushButton *>("button1");
```

This example returns a `QListWidget` child of `parentWidget`:

```
QListWidget *list = parentWidget->findChild< QListWidget *>();
```

This example returns a child `QPushButton` of `parentWidget` (its direct parent) named `"button1"`:

```
QPushButton *button = parentWidget->findChild< QPushButton *>("button1", Qt::FindDirectChildrenOnly);
```

This example returns a `QListWidget` child of `parentWidget`, its direct parent:

```
QListWidget *list = parentWidget->findChild< QListWidget *>(QString(), Qt::FindDirectChildrenOnly);
```

**See also** [findChildren](https://doc.qt.io/qt-6/qobject.html#findChildren)().

### template < typename T> [QList](https://doc.qt.io/qt-6/qlist.html)< T> QObject::findChildren(const [QString](https://doc.qt.io/qt-6/qstring.html) &*name*, [Qt::FindChildOptions](https://doc.qt.io/qt-6/qt.html#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

Returns all children of this object with the given *name* that can be cast to type T, or an empty list if there are no such objects. A null *name* argument causes all objects to be matched, an empty one only those whose [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop) is empty. The search is performed recursively, unless *options* specifies the option FindDirectChildrenOnly.

The following example shows how to find a list of child `QWidget`s of the specified `parentWidget` named `widgetname`:

```
QList< QWidget *> widgets = parentWidget.findChildren< QWidget *>("widgetname");
```

This example returns all `QPushButton`s that are children of `parentWidget`:

```
QList< QPushButton *> allPButtons = parentWidget.findChildren< QPushButton *>();
```

This example returns all `QPushButton`s that are immediate children of `parentWidget`:

```
QList< QPushButton *> childButtons = parentWidget.findChildren< QPushButton *>(Qt::FindDirectChildrenOnly);
```

**See also** [findChild](https://doc.qt.io/qt-6/qobject.html#findChild)().

### `[since 6.3]`template < typename T> [QList](https://doc.qt.io/qt-6/qlist.html)< T> QObject::findChildren([Qt::FindChildOptions](https://doc.qt.io/qt-6/qt.html#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

This is an overloaded function.

Returns all children of this object that can be cast to type T, or an empty list if there are no such objects. The search is performed recursively, unless *options* specifies the option FindDirectChildrenOnly.

This function was introduced in Qt 6.3.

**See also** [findChild](https://doc.qt.io/qt-6/qobject.html#findChild)().

### template < typename T> [QList](https://doc.qt.io/qt-6/qlist.html)< T> QObject::findChildren(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, [Qt::FindChildOptions](https://doc.qt.io/qt-6/qt.html#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

This function overloads findChildren().

Returns the children of this object that can be cast to type T and that have names matching the regular expression *re*, or an empty list if there are no such objects. The search is performed recursively, unless *options* specifies the option FindDirectChildrenOnly.

### bool QObject::inherits(const char **className*) const

Returns `true` if this object is an instance of a class that inherits *className* or a [QObject](https://doc.qt.io/qt-6/qobject.html) subclass that inherits *className*; otherwise returns `false`.

A class is considered to inherit itself.

Example:

```
QTimer *timer = new QTimer;         // QTimer inherits QObject
timer->inherits("QTimer");          // returns true
timer->inherits("QObject");         // returns true
timer->inherits("QAbstractButton"); // returns false

// QVBoxLayout inherits QObject and QLayoutItem
QVBoxLayout *layout = new QVBoxLayout;
layout->inherits("QObject");        // returns true
layout->inherits("QLayoutItem");    // returns true (even though QLayoutItem is not a QObject)
```

If you need to determine whether an object is an instance of a particular class for the purpose of casting it, consider using [qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast)< Type *>(object) instead.

**See also** [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)() and [qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast)().

### void QObject::installEventFilter([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **filterObj*)

Installs an event filter *filterObj* on this object. For example:

```
monitoredObj->installEventFilter(filterObj);
```

An event filter is an object that receives all events that are sent to this object. The filter can either stop the event or forward it to this object. The event filter *filterObj* receives events via its [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)() function. The [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)() function must return true if the event should be filtered, (i.e. stopped); otherwise it must return false.

If multiple event filters are installed on a single object, the filter that was installed last is activated first.

Here's a `KeyPressEater` class that eats the key presses of its monitored objects:

```
class KeyPressEater : public QObject
{
    Q_OBJECT
    ...

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast< QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
```

And here's how to install it on two widgets:

```
KeyPressEater *keyPressEater = new KeyPressEater(this);
QPushButton *pushButton = new QPushButton(this);
QListView *listView = new QListView(this);

pushButton->installEventFilter(keyPressEater);
listView->installEventFilter(keyPressEater);
```

The [QShortcut](https://doc.qt.io/qt-6/qshortcut.html) class, for example, uses this technique to intercept shortcut key presses.

**Warning:** If you delete the receiver object in your [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)() function, be sure to return true. If you return false, Qt sends the event to the deleted object and the program will crash.

Note that the filtering object must be in the same thread as this object. If *filterObj* is in a different thread, this function does nothing. If either *filterObj* or this object are moved to a different thread after calling this function, the event filter will not be called until both objects have the same thread affinity again (it is *not* removed).

**See also** [removeEventFilter](https://doc.qt.io/qt-6/qobject.html#removeEventFilter)(), [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)(), and [event](https://doc.qt.io/qt-6/qobject.html#event)().

### `[since 6.4]`bool QObject::isQuickItemType() const

Returns `true` if the object is a [QQuickItem](https://doc.qt.io/qt-6/qquickitem.html); otherwise returns `false`.

Calling this function is equivalent to calling `inherits("QQuickItem")`, except that it is much faster.

This function was introduced in Qt 6.4.

### `[protected]`bool QObject::isSignalConnected(const [QMetaMethod](https://doc.qt.io/qt-6/qmetamethod.html) &*signal*) const

Returns `true` if the *signal* is connected to at least one receiver, otherwise returns `false`.

*signal* must be a signal member of this object, otherwise the behaviour is undefined.

```
static const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&MyObject::valueChanged);
if (isSignalConnected(valueChangedSignal)) {
    QByteArray data;
    data = get_the_value();       // expensive operation
    emit valueChanged(data);
}
```

As the code snippet above illustrates, you can use this function to avoid expensive initialization or emitting a signal that nobody listens to. However, in a multithreaded application, connections might change after this function returns and before the signal gets emitted.

**Warning:** This function violates the object-oriented principle of modularity. In particular, this function must not be called from an override of [connectNotify](https://doc.qt.io/qt-6/qobject.html#connectNotify)() or [disconnectNotify](https://doc.qt.io/qt-6/qobject.html#disconnectNotify)(), as those might get called from any thread.

### bool QObject::isWidgetType() const

Returns `true` if the object is a widget; otherwise returns `false`.

Calling this function is equivalent to calling `inherits("QWidget")`, except that it is much faster.

### bool QObject::isWindowType() const

Returns `true` if the object is a window; otherwise returns `false`.

Calling this function is equivalent to calling `inherits("QWindow")`, except that it is much faster.

### void QObject::killTimer(int *id*)

Kills the timer with timer identifier, *id*.

The timer identifier is returned by [startTimer](https://doc.qt.io/qt-6/qobject.html#startTimer)() when a timer event is started.

**See also** [timerEvent](https://doc.qt.io/qt-6/qobject.html#timerEvent)() and [startTimer](https://doc.qt.io/qt-6/qobject.html#startTimer)().

### `[virtual]`const [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html) *QObject::metaObject() const

Returns a pointer to the meta-object of this object.

A meta-object contains information about a class that inherits [QObject](https://doc.qt.io/qt-6/qobject.html), e.g. class name, superclass name, properties, signals and slots. Every [QObject](https://doc.qt.io/qt-6/qobject.html) subclass that contains the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro will have a meta-object.

The meta-object information is required by the signal/slot connection mechanism and the property system. The [inherits](https://doc.qt.io/qt-6/qobject.html#inherits)() function also makes use of the meta-object.

If you have no pointer to an actual object instance but still want to access the meta-object of a class, you can use [staticMetaObject](https://doc.qt.io/qt-6/qobject.html#staticMetaObject-var).

Example:

```
QObject *obj = new QPushButton;
obj->metaObject()->className();             // returns "QPushButton"

QPushButton::staticMetaObject.className();  // returns "QPushButton"
```

**See also** [staticMetaObject](https://doc.qt.io/qt-6/qobject.html#staticMetaObject-var).

### void QObject::moveToThread([QThread](https://doc.qt.io/qt-6/qthread.html) **targetThread*)

Changes the thread affinity for this object and its children. The object cannot be moved if it has a parent. Event processing will continue in the *targetThread*.

To move an object to the main thread, use [QApplication::instance](https://doc.qt.io/qt-6/qcoreapplication.html#instance)() to retrieve a pointer to the current application, and then use [QApplication::thread](https://doc.qt.io/qt-6/qobject.html#thread)() to retrieve the thread in which the application lives. For example:

```
myObject->moveToThread(QApplication::instance()->thread());
```

If *targetThread* is `nullptr`, all event processing for this object and its children stops, as they are no longer associated with any thread.

Note that all active timers for the object will be reset. The timers are first stopped in the current thread and restarted (with the same interval) in the *targetThread*. As a result, constantly moving an object between threads can postpone timer events indefinitely.

A [QEvent::ThreadChange](https://doc.qt.io/qt-6/qevent.html#Type-enum) event is sent to this object just before the thread affinity is changed. You can handle this event to perform any special processing. Note that any new events that are posted to this object will be handled in the *targetThread*, provided it is not `nullptr`: when it is `nullptr`, no event processing for this object or its children can happen, as they are no longer associated with any thread.

**Warning:** This function is *not* thread-safe; the current thread must be same as the current thread affinity. In other words, this function can only "push" an object from the current thread to another thread, it cannot "pull" an object from any arbitrary thread to the current thread. There is one exception to this rule however: objects with no thread affinity can be "pulled" to the current thread.

**See also** [thread](https://doc.qt.io/qt-6/qobject.html#thread)().

### `[private signal]`void QObject::objectNameChanged(const [QString](https://doc.qt.io/qt-6/qstring.html) &*objectName*)

This signal is emitted after the object's name has been changed. The new object name is passed as *objectName*.

**Note:** This is a private signal. It can be used in signal connections but cannot be emitted by the user.

**Note:** Notifier signal for property [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop).

**See also** [QObject::objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop).

### [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) *QObject::parent() const

Returns a pointer to the parent object.

**See also** [setParent](https://doc.qt.io/qt-6/qobject.html#setParent)() and [children](https://doc.qt.io/qt-6/qobject.html#children)().

### [QVariant](https://doc.qt.io/qt-6/qvariant.html) QObject::property(const char **name*) const

Returns the value of the object's *name* property.

If no such property exists, the returned variant is invalid.

Information about all available properties is provided through the [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)() and [dynamicPropertyNames](https://doc.qt.io/qt-6/qobject.html#dynamicPropertyNames)().

**See also** [setProperty](https://doc.qt.io/qt-6/qobject.html#setProperty)(), [QVariant::isValid](https://doc.qt.io/qt-6/qvariant.html#isValid)(), [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)(), and [dynamicPropertyNames](https://doc.qt.io/qt-6/qobject.html#dynamicPropertyNames)().

### `[protected]`int QObject::receivers(const char **signal*) const

Returns the number of receivers connected to the *signal*.

Since both slots and signals can be used as receivers for signals, and the same connections can be made many times, the number of receivers is the same as the number of connections made from this signal.

When calling this function, you can use the `SIGNAL()` macro to pass a specific signal:

```
if (receivers(SIGNAL(valueChanged(QByteArray))) > 0) {
    QByteArray data;
    get_the_value(&data);       // expensive operation
    emit valueChanged(data);
}
```

**Warning:** This function violates the object-oriented principle of modularity. However, it might be useful when you need to perform expensive initialization only if something is connected to a signal.

**See also** [isSignalConnected](https://doc.qt.io/qt-6/qobject.html#isSignalConnected)().

### void QObject::removeEventFilter([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **obj*)

Removes an event filter object *obj* from this object. The request is ignored if such an event filter has not been installed.

All event filters for this object are automatically removed when this object is destroyed.

It is always safe to remove an event filter, even during event filter activation (i.e. from the [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)() function).

**See also** [installEventFilter](https://doc.qt.io/qt-6/qobject.html#installEventFilter)(), [eventFilter](https://doc.qt.io/qt-6/qobject.html#eventFilter)(), and [event](https://doc.qt.io/qt-6/qobject.html#event)().

### `[protected]`[QObject](https://doc.qt.io/qt-6/qobject.html#QObject) *QObject::sender() const

Returns a pointer to the object that sent the signal, if called in a slot activated by a signal; otherwise it returns `nullptr`. The pointer is valid only during the execution of the slot that calls this function from this object's thread context.

The pointer returned by this function becomes invalid if the sender is destroyed, or if the slot is disconnected from the sender's signal.

**Warning:** This function violates the object-oriented principle of modularity. However, getting access to the sender might be useful when many signals are connected to a single slot.

**Warning:** As mentioned above, the return value of this function is not valid when the slot is called via a [Qt::DirectConnection](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) from a thread different from this object's thread. Do not use this function in this type of scenario.

**See also** [senderSignalIndex](https://doc.qt.io/qt-6/qobject.html#senderSignalIndex)().

### `[protected]`int QObject::senderSignalIndex() const

Returns the meta-method index of the signal that called the currently executing slot, which is a member of the class returned by [sender](https://doc.qt.io/qt-6/qobject.html#sender)(). If called outside of a slot activated by a signal, -1 is returned.

For signals with default parameters, this function will always return the index with all parameters, regardless of which was used with [connect](https://doc.qt.io/qt-6/qobject.html#connect)(). For example, the signal `destroyed(QObject *obj = \nullptr)` will have two different indexes (with and without the parameter), but this function will always return the index with a parameter. This does not apply when overloading signals with different parameters.

**Warning:** This function violates the object-oriented principle of modularity. However, getting access to the signal index might be useful when many signals are connected to a single slot.

**Warning:** The return value of this function is not valid when the slot is called via a [Qt::DirectConnection](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) from a thread different from this object's thread. Do not use this function in this type of scenario.

**See also** [sender](https://doc.qt.io/qt-6/qobject.html#sender)(), [QMetaObject::indexOfSignal](https://doc.qt.io/qt-6/qmetaobject.html#indexOfSignal)(), and [QMetaObject::method](https://doc.qt.io/qt-6/qmetaobject.html#method)().

### void QObject::setObjectName(const [QString](https://doc.qt.io/qt-6/qstring.html) &*name*)

Sets the object's name to *name*.

**Note:** Setter function for property [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop).

**See also** [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop)().

### `[since 6.4]`void QObject::setObjectName([QAnyStringView](https://doc.qt.io/qt-6/qanystringview.html) *name*)

This is an overloaded function.

**Note:** Setter function for property [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop).

This function was introduced in Qt 6.4.

### void QObject::setParent([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **parent*)

Makes the object a child of *parent*.

**See also** [parent](https://doc.qt.io/qt-6/qobject.html#parent)() and [children](https://doc.qt.io/qt-6/qobject.html#children)().

### bool QObject::setProperty(const char **name*, const [QVariant](https://doc.qt.io/qt-6/qvariant.html) &*value*)

Sets the value of the object's *name* property to *value*.

If the property is defined in the class using [Q_PROPERTY](https://doc.qt.io/qt-6/qobject.html#Q_PROPERTY) then true is returned on success and false otherwise. If the property is not defined using [Q_PROPERTY](https://doc.qt.io/qt-6/qobject.html#Q_PROPERTY), and therefore not listed in the meta-object, it is added as a dynamic property and false is returned.

Information about all available properties is provided through the [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)() and [dynamicPropertyNames](https://doc.qt.io/qt-6/qobject.html#dynamicPropertyNames)().

Dynamic properties can be queried again using [property](https://doc.qt.io/qt-6/qobject.html#property)() and can be removed by setting the property value to an invalid [QVariant](https://doc.qt.io/qt-6/qvariant.html). Changing the value of a dynamic property causes a [QDynamicPropertyChangeEvent](https://doc.qt.io/qt-6/qdynamicpropertychangeevent.html) to be sent to the object.

**Note:** Dynamic properties starting with "_q_" are reserved for internal purposes.

**See also** [property](https://doc.qt.io/qt-6/qobject.html#property)(), [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)(), [dynamicPropertyNames](https://doc.qt.io/qt-6/qobject.html#dynamicPropertyNames)(), and [QMetaProperty::write](https://doc.qt.io/qt-6/qmetaproperty.html#write)().

### `[since 6.6]`bool QObject::setProperty(const char **name*, [QVariant](https://doc.qt.io/qt-6/qvariant.html) &&*value*)

This function overloads setProperty.

This function was introduced in Qt 6.6.

### `[noexcept]`bool QObject::signalsBlocked() const

Returns `true` if signals are blocked; otherwise returns `false`.

Signals are not blocked by default.

**See also** [blockSignals](https://doc.qt.io/qt-6/qobject.html#blockSignals)() and [QSignalBlocker](https://doc.qt.io/qt-6/qsignalblocker.html).

### int QObject::startTimer(int *interval*, [Qt::TimerType](https://doc.qt.io/qt-6/qt.html#TimerType-enum) *timerType* = Qt::CoarseTimer)

This is an overloaded function that will start a timer of type *timerType* and a timeout of *interval* milliseconds. This is equivalent to calling:

```
startTimer(std::chrono::milliseconds{interval}, timerType);
```

**See also** [timerEvent](https://doc.qt.io/qt-6/qobject.html#timerEvent)(), [killTimer](https://doc.qt.io/qt-6/qobject.html#killTimer)(), and [QTimer::singleShot](https://doc.qt.io/qt-6/qtimer.html#singleShot)().

### int QObject::startTimer(std::chrono::milliseconds *interval*, [Qt::TimerType](https://doc.qt.io/qt-6/qt.html#TimerType-enum) *timerType* = Qt::CoarseTimer)

This is an overloaded function.

Starts a timer and returns a timer identifier, or returns zero if it could not start a timer.

A timer event will occur every *interval* until [killTimer](https://doc.qt.io/qt-6/qobject.html#killTimer)() is called. If *interval* is equal to `std::chrono::duration::zero()`, then the timer event occurs once every time there are no more window system events to process.

The virtual [timerEvent](https://doc.qt.io/qt-6/qobject.html#timerEvent)() function is called with the [QTimerEvent](https://doc.qt.io/qt-6/qtimerevent.html) event parameter class when a timer event occurs. Reimplement this function to get timer events.

If multiple timers are running, the [QTimerEvent::timerId](https://doc.qt.io/qt-6/qtimerevent.html#timerId)() can be used to find out which timer was activated.

Example:

```
class MyObject : public QObject
{
    Q_OBJECT

public:
    MyObject(QObject *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;
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
    qDebug() < <  "Timer ID:" < <  event->timerId();
}
```

Note that [QTimer](https://doc.qt.io/qt-6/qtimer.html)'s accuracy depends on the underlying operating system and hardware. The *timerType* argument allows you to customize the accuracy of the timer. See [Qt::TimerType](https://doc.qt.io/qt-6/qt.html#TimerType-enum) for information on the different timer types. Most platforms support an accuracy of 20 milliseconds; some provide more. If Qt is unable to deliver the requested number of timer events, it will silently discard some.

The [QTimer](https://doc.qt.io/qt-6/qtimer.html) class provides a high-level programming interface with single-shot timers and timer signals instead of events. There is also a [QBasicTimer](https://doc.qt.io/qt-6/qbasictimer.html) class that is more lightweight than [QTimer](https://doc.qt.io/qt-6/qtimer.html) and less clumsy than using timer IDs directly.

**See also** [timerEvent](https://doc.qt.io/qt-6/qobject.html#timerEvent)(), [killTimer](https://doc.qt.io/qt-6/qobject.html#killTimer)(), and [QTimer::singleShot](https://doc.qt.io/qt-6/qtimer.html#singleShot)().

### [QThread](https://doc.qt.io/qt-6/qthread.html) *QObject::thread() const

Returns the thread in which the object lives.

**See also** [moveToThread](https://doc.qt.io/qt-6/qobject.html#moveToThread)().

### `[virtual protected]`void QObject::timerEvent([QTimerEvent](https://doc.qt.io/qt-6/qtimerevent.html) **event*)

This event handler can be reimplemented in a subclass to receive timer events for the object.

[QTimer](https://doc.qt.io/qt-6/qtimer.html) provides a higher-level interface to the timer functionality, and also more general information about timers. The timer event is passed in the *event* parameter.

**See also** [startTimer](https://doc.qt.io/qt-6/qobject.html#startTimer)(), [killTimer](https://doc.qt.io/qt-6/qobject.html#killTimer)(), and [event](https://doc.qt.io/qt-6/qobject.html#event)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html) QObject::tr(const char **sourceText*, const char **disambiguation* = nullptr, int *n* = -1)

Returns a translated version of *sourceText*, optionally based on a *disambiguation* string and value of *n* for strings containing plurals; otherwise returns [QString::fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(*sourceText*) if no appropriate translated string is available.

Example:

```
void SpreadSheet::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    ...
```

If the same *sourceText* is used in different roles within the same context, an additional identifying string may be passed in *disambiguation* (`nullptr` by default). In Qt 4.4 and earlier, this was the preferred way to pass comments to translators.

Example:

```
MyWindow::MyWindow()
{
    QLabel *senderLabel = new QLabel(tr("Name:"));
    QLabel *recipientLabel = new QLabel(tr("Name:", "recipient"));
    ...
```

See [Writing Source Code for Translation](https://doc.qt.io/qt-6/i18n-source-translation.html) for a detailed description of Qt's translation mechanisms in general, and the [Disambiguate Identical Text](https://doc.qt.io/qt-6/i18n-source-translation.html#disambiguate-identical-text) section for information on disambiguation.

**Warning:** This method is reentrant only if all translators are installed *before* calling this method. Installing or removing translators while performing translations is not supported. Doing so will probably result in crashes or other undesirable behavior.

**See also** [QCoreApplication::translate](https://doc.qt.io/qt-6/qcoreapplication.html#translate)() and [Internationalization with Qt](https://doc.qt.io/qt-6/internationalization.html).

## Member Variable Documentation

### const [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html) QObject::staticMetaObject

This variable stores the meta-object for the class.

A meta-object contains information about a class that inherits [QObject](https://doc.qt.io/qt-6/qobject.html), e.g. class name, superclass name, properties, signals and slots. Every class that contains the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro will also have a meta-object.

The meta-object information is required by the signal/slot connection mechanism and the property system. The [inherits](https://doc.qt.io/qt-6/qobject.html#inherits)() function also makes use of the meta-object.

If you have a pointer to an object, you can use [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)() to retrieve the meta-object associated with that object.

Example:

```
QPushButton::staticMetaObject.className();  // returns "QPushButton"

QObject *obj = new QPushButton;
obj->metaObject()->className();             // returns "QPushButton"
```

**See also** [metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)().

## Related Non-Members

### template < typename T> T qobject_cast([QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **object*)

### template < typename T> T qobject_cast(const [QObject](https://doc.qt.io/qt-6/qobject.html#QObject) **object*)

Returns the given *object* cast to type T if the object is of type T (or of a subclass); otherwise returns `nullptr`. If *object* is `nullptr` then it will also return `nullptr`.

The class T must inherit (directly or indirectly) [QObject](https://doc.qt.io/qt-6/qobject.html) and be declared with the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro.

A class is considered to inherit itself.

Example:

```
QObject *obj = new QTimer;          // QTimer inherits QObject

QTimer *timer = qobject_cast< QTimer *>(obj);
// timer == (QObject *)obj

QAbstractButton *button = qobject_cast< QAbstractButton *>(obj);
// button == nullptr
```

The [qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast)() function behaves similarly to the standard C++ `dynamic_cast()`, with the advantages that it doesn't require RTTI support and it works across dynamic library boundaries.

[qobject_cast](https://doc.qt.io/qt-6/qobject.html#qobject_cast)() can also be used in conjunction with interfaces.

**Warning:** If T isn't declared with the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro, this function's return value is undefined.

**See also** [QObject::inherits](https://doc.qt.io/qt-6/qobject.html#inherits)().

### QObjectList

Synonym for [QList](https://doc.qt.io/qt-6/qlist.html)< [QObject](https://doc.qt.io/qt-6/qobject.html) *>.

## Macro Documentation

### QT_NO_NARROWING_CONVERSIONS_IN_CONNECT

Defining this macro will disable narrowing and floating-point-to-integral conversions between the arguments carried by a signal and the arguments accepted by a slot, when the signal and the slot are connected using the PMF-based syntax.

**See also** [QObject::connect](https://doc.qt.io/qt-6/qobject.html#connect).

### Q_CLASSINFO(*Name*, *Value*)

This macro associates extra information to the class, which is available using [QObject::metaObject](https://doc.qt.io/qt-6/qobject.html#metaObject)(). Qt makes only limited use of this feature in [Qt D-Bus](https://doc.qt.io/qt-6/qtdbus-index.html) and [Qt QML](https://doc.qt.io/qt-6/qtqml-index.html) modules.

The extra information takes the form of a *Name* string and a *Value* literal string.

Example:

```
class MyClass : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Pierre Gendron")
    Q_CLASSINFO("URL", "http://www.my-organization.qc.ca")

public:
    ...
};
```

**See also** [QMetaObject::classInfo](https://doc.qt.io/qt-6/qmetaobject.html#classInfo)(), [Using Qt D-Bus Adaptors](https://doc.qt.io/qt-6/usingadaptors.html), and [Extending QML](https://doc.qt.io/qt-6/qtquick-codesamples.html#extending-qml).

### Q_EMIT

Use this macro to replace the `emit` keyword for emitting signals, when you want to use Qt Signals and Slots with a [3rd party signal/slot mechanism](https://doc.qt.io/qt-6/signalsandslots.html#3rd-party-signals-and-slots).

The macro is normally used when `no_keywords` is specified with the `CONFIG` variable in the `.pro` file, but it can be used even when `no_keywords` is *not* specified.

### Q_ENUM(...)

This macro registers an enum type with the meta-object system. It must be placed after the enum declaration in a class that has the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT), [Q_GADGET](https://doc.qt.io/qt-6/qobject.html#Q_GADGET) or [Q_GADGET_EXPORT](https://doc.qt.io/qt-6/qobject.html#Q_GADGET_EXPORT) macro. For namespaces use [Q_ENUM_NS](https://doc.qt.io/qt-6/qobject.html#Q_ENUM_NS)() instead.

For example:

```
class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass(QObject *parent = nullptr);
    ~MyClass();

    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)
    void setPriority(Priority priority);
    Priority priority() const;
};
```

Enumerations that are declared with Q_ENUM have their [QMetaEnum](https://doc.qt.io/qt-6/qmetaenum.html) registered in the enclosing [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html). You can also use [QMetaEnum::fromType](https://doc.qt.io/qt-6/qmetaenum.html#fromType)() to get the [QMetaEnum](https://doc.qt.io/qt-6/qmetaenum.html).

Registered enumerations are automatically registered also to the Qt meta type system, making them known to [QMetaType](https://doc.qt.io/qt-6/qmetatype.html) without the need to use [Q_DECLARE_METATYPE](https://doc.qt.io/qt-6/qmetatype.html#Q_DECLARE_METATYPE)(). This will enable useful features; for example, if used in a [QVariant](https://doc.qt.io/qt-6/qvariant.html), you can convert them to strings. Likewise, passing them to [QDebug](https://doc.qt.io/qt-6/qdebug.html) will print out their names.

Mind that the enum values are stored as signed `int` in the meta object system. Registering enumerations with values outside the range of values valid for `int` will lead to overflows and potentially undefined behavior when accessing them through the meta object system. QML, for example, does access registered enumerations through the meta object system.

**See also** [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

### Q_ENUM_NS(...)

This macro registers an enum type with the meta-object system. It must be placed after the enum declaration in a namespace that has the [Q_NAMESPACE](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE) macro. It is the same as [Q_ENUM](https://doc.qt.io/qt-6/qobject.html#Q_ENUM) but in a namespace.

Enumerations that are declared with Q_ENUM_NS have their [QMetaEnum](https://doc.qt.io/qt-6/qmetaenum.html) registered in the enclosing [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html). You can also use [QMetaEnum::fromType](https://doc.qt.io/qt-6/qmetaenum.html#fromType)() to get the [QMetaEnum](https://doc.qt.io/qt-6/qmetaenum.html).

Registered enumerations are automatically registered also to the Qt meta type system, making them known to [QMetaType](https://doc.qt.io/qt-6/qmetatype.html) without the need to use [Q_DECLARE_METATYPE](https://doc.qt.io/qt-6/qmetatype.html#Q_DECLARE_METATYPE)(). This will enable useful features; for example, if used in a [QVariant](https://doc.qt.io/qt-6/qvariant.html), you can convert them to strings. Likewise, passing them to [QDebug](https://doc.qt.io/qt-6/qdebug.html) will print out their names.

Mind that the enum values are stored as signed `int` in the meta object system. Registering enumerations with values outside the range of values valid for `int` will lead to overflows and potentially undefined behavior when accessing them through the meta object system. QML, for example, does access registered enumerations through the meta object system.

**See also** [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

### Q_FLAG(...)

This macro registers a single [flags type](https://doc.qt.io/qt-6/qflags.html) with the meta-object system. It is typically used in a class definition to declare that values of a given enum can be used as flags and combined using the bitwise OR operator. For namespaces use [Q_FLAG_NS](https://doc.qt.io/qt-6/qobject.html#Q_FLAG_NS)() instead.

The macro must be placed after the enum declaration. The declaration of the flags type is done using the [Q_DECLARE_FLAGS](https://doc.qt.io/qt-6/qflags.html#Q_DECLARE_FLAGS)() macro.

For example, in [QItemSelectionModel](https://doc.qt.io/qt-6/qitemselectionmodel.html), the [SelectionFlags](https://doc.qt.io/qt-6/qitemselectionmodel.html#SelectionFlag-enum) flag is declared in the following way:

```
class QItemSelectionModel : public QObject
{
    Q_OBJECT

public:
    ...
    enum SelectionFlag {
        NoUpdate       = 0x0000,
        Clear          = 0x0001,
        Select         = 0x0002,
        Deselect       = 0x0004,
        Toggle         = 0x0008,
        Current        = 0x0010,
        Rows           = 0x0020,
        Columns        = 0x0040,
        SelectCurrent  = Select | Current,
        ToggleCurrent  = Toggle | Current,
        ClearAndSelect = Clear | Select
    };

    Q_DECLARE_FLAGS(SelectionFlags, SelectionFlag)
    Q_FLAG(SelectionFlags)
    ...
}
```

**Note:** The Q_FLAG macro takes care of registering individual flag values with the meta-object system, so it is unnecessary to use [Q_ENUM](https://doc.qt.io/qt-6/qobject.html#Q_ENUM)() in addition to this macro.

**See also** [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

### Q_FLAG_NS(...)

This macro registers a single [flags type](https://doc.qt.io/qt-6/qflags.html) with the meta-object system. It is used in a namespace that has the [Q_NAMESPACE](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE) macro, to declare that values of a given enum can be used as flags and combined using the bitwise OR operator. It is the same as [Q_FLAG](https://doc.qt.io/qt-6/qobject.html#Q_FLAG) but in a namespace.

The macro must be placed after the enum declaration.

**Note:** The Q_FLAG_NS macro takes care of registering individual flag values with the meta-object system, so it is unnecessary to use [Q_ENUM_NS](https://doc.qt.io/qt-6/qobject.html#Q_ENUM_NS)() in addition to this macro.

**See also** [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

### Q_GADGET

The Q_GADGET macro is a lighter version of the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro for classes that do not inherit from [QObject](https://doc.qt.io/qt-6/qobject.html) but still want to use some of the reflection capabilities offered by [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html). Just like the [Q_OBJECT](https://doc.qt.io/qt-6/qobject.html#Q_OBJECT) macro, it must appear in the private section of a class definition.

Q_GADGETs can have [Q_ENUM](https://doc.qt.io/qt-6/qobject.html#Q_ENUM), [Q_PROPERTY](https://doc.qt.io/qt-6/qobject.html#Q_PROPERTY) and [Q_INVOKABLE](https://doc.qt.io/qt-6/qobject.html#Q_INVOKABLE), but they cannot have signals or slots.

Q_GADGET makes a class member, `staticMetaObject`, available. `staticMetaObject` is of type [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html) and provides access to the enums declared with [Q_ENUM](https://doc.qt.io/qt-6/qobject.html#Q_ENUM).

**See also** [Q_GADGET_EXPORT](https://doc.qt.io/qt-6/qobject.html#Q_GADGET_EXPORT).

### `[since 6.3]`Q_GADGET_EXPORT(*EXPORT_MACRO*)

The Q_GADGET_EXPORT macro works exactly like the [Q_GADGET](https://doc.qt.io/qt-6/qobject.html#Q_GADGET) macro. However, the `staticMetaObject` variable that is made available (see [Q_GADGET](https://doc.qt.io/qt-6/qobject.html#Q_GADGET)) is declared with the supplied *EXPORT_MACRO* qualifier. This is useful if the object needs to be exported from a dynamic library, but the enclosing class as a whole should not be (e.g. because it consists of mostly inline functions).

For example:

```
class Point {
    Q_GADGET_EXPORT(EXPORT_MACRO)
    Q_PROPERTY(int x MEMBER x)
    Q_PROPERTY(int y MEMBER y)
    ~~~
```

This macro was introduced in Qt 6.3.

**See also** [Q_GADGET](https://doc.qt.io/qt-6/qobject.html#Q_GADGET) and [Creating Shared Libraries](https://doc.qt.io/qt-6/sharedlibrary.html).

### Q_INTERFACES(...)

This macro tells Qt which interfaces the class implements. This is used when implementing plugins.

**See also** [Q_DECLARE_INTERFACE](https://doc.qt.io/qt-6/qtplugin.html#Q_DECLARE_INTERFACE)(), [Q_PLUGIN_METADATA](https://doc.qt.io/qt-6/qtplugin.html#Q_PLUGIN_METADATA)(), and [How to Create Qt Plugins](https://doc.qt.io/qt-6/plugins-howto.html).

### Q_INVOKABLE

Apply this macro to declarations of member functions to allow them to be invoked via the meta-object system. The macro is written before the return type, as shown in the following example:

```
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    void normalMethod();
    Q_INVOKABLE void invokableMethod();
};
```

The `invokableMethod()` function is marked up using Q_INVOKABLE, causing it to be registered with the meta-object system and enabling it to be invoked using [QMetaObject::invokeMethod](https://doc.qt.io/qt-6/qmetaobject.html#invokeMethod)(). Since `normalMethod()` function is not registered in this way, it cannot be invoked using [QMetaObject::invokeMethod](https://doc.qt.io/qt-6/qmetaobject.html#invokeMethod)().

If an invokable member function returns a pointer to a [QObject](https://doc.qt.io/qt-6/qobject.html) or a subclass of [QObject](https://doc.qt.io/qt-6/qobject.html) and it is invoked from QML, special ownership rules apply. See [Data Type Conversion Between QML and C++](https://doc.qt.io/qt-6/qtqml-cppintegration-data.html) for more information.

### `[since 6.0]`Q_MOC_INCLUDE

The Q_MOC_INCLUDE macro can be used within or outside a class, and tell the [Meta Object Compiler](https://doc.qt.io/qt-6/moc.html) to add an include.

```
// Put this in your code and the generated code will include this header.
Q_MOC_INCLUDE("myheader.h")
```

This is useful if the types you use as properties or signal/slots arguments are forward declared.

This macro was introduced in Qt 6.0.

### Q_NAMESPACE

The Q_NAMESPACE macro can be used to add [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html) capabilities to a namespace.

Q_NAMESPACEs can have [Q_CLASSINFO](https://doc.qt.io/qt-6/qobject.html#Q_CLASSINFO), [Q_ENUM_NS](https://doc.qt.io/qt-6/qobject.html#Q_ENUM_NS), [Q_FLAG_NS](https://doc.qt.io/qt-6/qobject.html#Q_FLAG_NS), but they cannot have [Q_ENUM](https://doc.qt.io/qt-6/qobject.html#Q_ENUM), [Q_FLAG](https://doc.qt.io/qt-6/qobject.html#Q_FLAG), [Q_PROPERTY](https://doc.qt.io/qt-6/qobject.html#Q_PROPERTY), [Q_INVOKABLE](https://doc.qt.io/qt-6/qobject.html#Q_INVOKABLE), signals nor slots.

Q_NAMESPACE makes an external variable, `staticMetaObject`, available. `staticMetaObject` is of type [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html) and provides access to the enums declared with [Q_ENUM_NS](https://doc.qt.io/qt-6/qobject.html#Q_ENUM_NS)/[Q_FLAG_NS](https://doc.qt.io/qt-6/qobject.html#Q_FLAG_NS).

For example:

```
namespace test {
Q_NAMESPACE
...
```

**See also** [Q_NAMESPACE_EXPORT](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE_EXPORT).

### Q_NAMESPACE_EXPORT(*EXPORT_MACRO*)

The Q_NAMESPACE_EXPORT macro can be used to add [QMetaObject](https://doc.qt.io/qt-6/qmetaobject.html) capabilities to a namespace.

It works exactly like the [Q_NAMESPACE](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE) macro. However, the external `staticMetaObject` variable that gets defined in the namespace is declared with the supplied *EXPORT_MACRO* qualifier. This is useful if the object needs to be exported from a dynamic library.

For example:

```
namespace test {
Q_NAMESPACE_EXPORT(EXPORT_MACRO)
...
```

**See also** [Q_NAMESPACE](https://doc.qt.io/qt-6/qobject.html#Q_NAMESPACE) and [Creating Shared Libraries](https://doc.qt.io/qt-6/sharedlibrary.html).

### Q_OBJECT

The Q_OBJECT macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system.

For example:

```
#include < QObject>

class Counter : public QObject
{
    Q_OBJECT

public:
    Counter() { m_value = 0; }

    int value() const { return m_value; }

public slots:
    void setValue(int value);

signals:
    void valueChanged(int newValue);

private:
    int m_value;
};
```

**Note:** This macro requires the class to be a subclass of [QObject](https://doc.qt.io/qt-6/qobject.html). Use [Q_GADGET](https://doc.qt.io/qt-6/qobject.html#Q_GADGET) or [Q_GADGET_EXPORT](https://doc.qt.io/qt-6/qobject.html#Q_GADGET_EXPORT) instead of Q_OBJECT to enable the meta object system's support for enums in a class that is not a [QObject](https://doc.qt.io/qt-6/qobject.html) subclass.

**See also** [Meta-Object System](https://doc.qt.io/qt-6/metaobjects.html), [Signals and Slots](https://doc.qt.io/qt-6/signalsandslots.html), and [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

### Q_PROPERTY(...)

This macro is used for declaring properties in classes that inherit [QObject](https://doc.qt.io/qt-6/qobject.html). Properties behave like class data members, but they have additional features accessible through the [Meta-Object System](https://doc.qt.io/qt-6/metaobjects.html).

```
Q_PROPERTY(type name
           (READ getFunction [WRITE setFunction] |
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
           [RESET resetFunction]
           [NOTIFY notifySignal]
           [REVISION int | REVISION(int[, int])]
           [DESIGNABLE bool]
           [SCRIPTABLE bool]
           [STORED bool]
           [USER bool]
           [BINDABLE bindableProperty]
           [CONSTANT]
           [FINAL]
           [REQUIRED])
```

The property name and type and the `READ` function are required. The type can be any type supported by [QVariant](https://doc.qt.io/qt-6/qvariant.html), or it can be a user-defined type. The other items are optional, but a `WRITE` function is common. The attributes default to true except `USER`, which defaults to false.

For example:

```
Q_PROPERTY(QString title READ title WRITE setTitle USER true)
```

For more details about how to use this macro, and a more detailed example of its use, see the discussion on [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

**See also** [Qt's Property System](https://doc.qt.io/qt-6/properties.html).

### Q_REVISION

Apply this macro to declarations of member functions to tag them with a revision number in the meta-object system. The macro is written before the return type, as shown in the following example:

```
class Window : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int normalProperty READ normalProperty)
    Q_PROPERTY(int newProperty READ newProperty REVISION(2, 1))

public:
    Window();
    int normalProperty();
    int newProperty();
public slots:
    void normalMethod();
    Q_REVISION(2, 1) void newMethod();
};
```

This is useful when using the meta-object system to dynamically expose objects to another API, as you can match the version expected by multiple versions of the other API. Consider the following simplified example:

```
    Window window;
    int expectedRevision = 0;
    const QMetaObject *windowMetaObject = window.metaObject();
    for (int i=0; i <  windowMetaObject->methodCount(); i++)
        if (windowMetaObject->method(i).revision() < = expectedRevision)
            exposeMethod(windowMetaObject->method(i));
    for (int i=0; i <  windowMetaObject->propertyCount(); i++)
        if (windowMetaObject->property(i).revision() < = expectedRevision)
            exposeProperty(windowMetaObject->property(i));
```

Using the same Window class as the previous example, the newProperty and newMethod would only be exposed in this code when the expected version is `2.1` or greater.

Since all methods are considered to be in revision `0` if untagged, a tag of `Q_REVISION(0)` or `Q_REVISION(0, 0)` is invalid and ignored.

You can pass one or two integer parameters to `Q_REVISION`. If you pass one parameter, it denotes the minor version only. This means that the major version is unspecified. If you pass two, the first parameter is the major version and the second parameter is the minor version.

This tag is not used by the meta-object system itself. Currently this is only used by the [QtQml](https://doc.qt.io/qt-6/qtqml-module.html) module.

For a more generic string tag, see [QMetaMethod::tag](https://doc.qt.io/qt-6/qmetamethod.html#tag)()

**See also** [QMetaMethod::revision](https://doc.qt.io/qt-6/qmetamethod.html#revision)().

### Q_SET_OBJECT_NAME(*Object*)

This macro assigns *Object* the [objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop) "Object".

It doesn't matter whether *Object* is a pointer or not, the macro figures that out by itself.

**See also** [QObject::objectName](https://doc.qt.io/qt-6/qobject.html#objectName-prop)().

### Q_SIGNAL

This is an additional macro that allows you to mark a single function as a signal. It can be quite useful, especially when you use a 3rd-party source code parser which doesn't understand a `signals` or `Q_SIGNALS` groups.

Use this macro to replace the `signals` keyword in class declarations, when you want to use Qt Signals and Slots with a [3rd party signal/slot mechanism](https://doc.qt.io/qt-6/signalsandslots.html#3rd-party-signals-and-slots).

The macro is normally used when `no_keywords` is specified with the `CONFIG` variable in the `.pro` file, but it can be used even when `no_keywords` is *not* specified.

### Q_SIGNALS

Use this macro to replace the `signals` keyword in class declarations, when you want to use Qt Signals and Slots with a [3rd party signal/slot mechanism](https://doc.qt.io/qt-6/signalsandslots.html#3rd-party-signals-and-slots).

The macro is normally used when `no_keywords` is specified with the `CONFIG` variable in the `.pro` file, but it can be used even when `no_keywords` is *not* specified.

### Q_SLOT

This is an additional macro that allows you to mark a single function as a slot. It can be quite useful, especially when you use a 3rd-party source code parser which doesn't understand a `slots` or `Q_SLOTS` groups.

Use this macro to replace the `slots` keyword in class declarations, when you want to use Qt Signals and Slots with a [3rd party signal/slot mechanism](https://doc.qt.io/qt-6/signalsandslots.html#3rd-party-signals-and-slots).

The macro is normally used when `no_keywords` is specified with the `CONFIG` variable in the `.pro` file, but it can be used even when `no_keywords` is *not* specified.

### Q_SLOTS

Use this macro to replace the `slots` keyword in class declarations, when you want to use Qt Signals and Slots with a [3rd party signal/slot mechanism](https://doc.qt.io/qt-6/signalsandslots.html#3rd-party-signals-and-slots).

The macro is normally used when `no_keywords` is specified with the `CONFIG` variable in the `.pro` file, but it can be used even when `no_keywords` is *not* specified.