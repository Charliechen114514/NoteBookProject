 QObject Class

QObject 类是所有 Qt 对象的基类。[更多的...](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#details)

| Header:       | #include < QObject>                                          |
| ------------- | ------------------------------------------------------------ |
| CMake:        | find_package(Qt6 REQUIRED COMPONENTS Core) target_link_libraries(mytarget PRIVATE Qt6::Core) |
| qmake:        | QT += core                                                   |
| Inherited By: | [Q3DObject](https://doc-qt-io.translate.goog/qt-6/q3dobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Q3DScene](https://doc-qt-io.translate.goog/qt-6/q3dscene.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Q3DTheme](https://doc-qt-io.translate.goog/qt-6/q3dtheme.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstract3DAxis](https://doc-qt-io.translate.goog/qt-6/qabstract3daxis.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstract3DInputHandler](https://doc-qt-io.translate.goog/qt-6/qabstract3dinputhandler.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstract3DSeries](https://doc-qt-io.translate.goog/qt-6/qabstract3dseries.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractAnimation](https://doc-qt-io.translate.goog/qt-6/qabstractanimation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractAxis](https://doc-qt-io.translate.goog/qt-6/qabstractaxis.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractDataProxy](https://doc-qt-io.translate.goog/qt-6/qabstractdataproxy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractEventDispatcher](https://doc-qt-io.translate.goog/qt-6/qabstracteventdispatcher.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractGrpcClient](https://doc-qt-io.translate.goog/qt-6/qabstractgrpcclient.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractHttpServer](https://doc-qt-io.translate.goog/qt-6/qabstracthttpserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractItemDelegate](https://doc-qt-io.translate.goog/qt-6/qabstractitemdelegate.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractItemModel](https://doc-qt-io.translate.goog/qt-6/qabstractitemmodel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractItemModelTester](https://doc-qt-io.translate.goog/qt-6/qabstractitemmodeltester.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractNetworkCache](https://doc-qt-io.translate.goog/qt-6/qabstractnetworkcache.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractOAuth](https://doc-qt-io.translate.goog/qt-6/qabstractoauth.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractOAuthReplyHandler](https://doc-qt-io.translate.goog/qt-6/qabstractoauthreplyhandler.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractSeries](https://doc-qt-io.translate.goog/qt-6/qabstractseries.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractState](https://doc-qt-io.translate.goog/qt-6/qabstractstate.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractTextDocumentLayout](https://doc-qt-io.translate.goog/qt-6/qabstracttextdocumentlayout.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAbstractTransition](https://doc-qt-io.translate.goog/qt-6/qabstracttransition.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAccessiblePlugin](https://doc-qt-io.translate.goog/qt-6/qaccessibleplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAction](https://doc-qt-io.translate.goog/qt-6/qaction.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QActionGroup](https://doc-qt-io.translate.goog/qt-6/qactiongroup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAmbientSound](https://doc-qt-io.translate.goog/qt-6/qambientsound.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioDecoder](https://doc-qt-io.translate.goog/qt-6/qaudiodecoder.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioEngine](https://doc-qt-io.translate.goog/qt-6/qaudioengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioInput](https://doc-qt-io.translate.goog/qt-6/qaudioinput.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioListener](https://doc-qt-io.translate.goog/qt-6/qaudiolistener.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioOutput](https://doc-qt-io.translate.goog/qt-6/qaudiooutput.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioRoom](https://doc-qt-io.translate.goog/qt-6/qaudioroom.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioSink](https://doc-qt-io.translate.goog/qt-6/qaudiosink.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAudioSource](https://doc-qt-io.translate.goog/qt-6/qaudiosource.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAxBaseObject](https://doc-qt-io.translate.goog/qt-6/qaxbaseobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAxFactory](https://doc-qt-io.translate.goog/qt-6/qaxfactory.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAxScript](https://doc-qt-io.translate.goog/qt-6/qaxscript.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QAxScriptManager](https://doc-qt-io.translate.goog/qt-6/qaxscriptmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QBarSet](https://doc-qt-io.translate.goog/qt-6/qbarset.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QBluetoothDeviceDiscoveryAgent](https://doc-qt-io.translate.goog/qt-6/qbluetoothdevicediscoveryagent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QBluetoothLocalDevice](https://doc-qt-io.translate.goog/qt-6/qbluetoothlocaldevice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QBluetoothServer](https://doc-qt-io.translate.goog/qt-6/qbluetoothserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QBluetoothServiceDiscoveryAgent](https://doc-qt-io.translate.goog/qt-6/qbluetoothservicediscoveryagent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QBoxSet](https://doc-qt-io.translate.goog/qt-6/qboxset.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QButtonGroup](https://doc-qt-io.translate.goog/qt-6/qbuttongroup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCamera](https://doc-qt-io.translate.goog/qt-6/qcamera.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCanBus](https://doc-qt-io.translate.goog/qt-6/qcanbus.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCanBusDevice](https://doc-qt-io.translate.goog/qt-6/qcanbusdevice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCandlestickModelMapper](https://doc-qt-io.translate.goog/qt-6/qcandlestickmodelmapper.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCandlestickSet](https://doc-qt-io.translate.goog/qt-6/qcandlestickset.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QClipboard](https://doc-qt-io.translate.goog/qt-6/qclipboard.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCoapClient](https://doc-qt-io.translate.goog/qt-6/qcoapclient.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCompleter](https://doc-qt-io.translate.goog/qt-6/qcompleter.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCoreApplication](https://doc-qt-io.translate.goog/qt-6/qcoreapplication.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QCustom3DItem](https://doc-qt-io.translate.goog/qt-6/qcustom3ditem.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDataWidgetMapper](https://doc-qt-io.translate.goog/qt-6/qdatawidgetmapper.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDBusAbstractAdaptor](https://doc-qt-io.translate.goog/qt-6/qdbusabstractadaptor.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDBusAbstractInterface](https://doc-qt-io.translate.goog/qt-6/qdbusabstractinterface.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDBusPendingCallWatcher](https://doc-qt-io.translate.goog/qt-6/qdbuspendingcallwatcher.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDBusServer](https://doc-qt-io.translate.goog/qt-6/qdbusserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDBusServiceWatcher](https://doc-qt-io.translate.goog/qt-6/qdbusservicewatcher.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDBusVirtualObject](https://doc-qt-io.translate.goog/qt-6/qdbusvirtualobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDesignerFormEditorInterface](https://doc-qt-io.translate.goog/qt-6/qdesignerformeditorinterface.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDesignerFormWindowManagerInterface](https://doc-qt-io.translate.goog/qt-6/qdesignerformwindowmanagerinterface.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDnsLookup](https://doc-qt-io.translate.goog/qt-6/qdnslookup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDrag](https://doc-qt-io.translate.goog/qt-6/qdrag.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDtls](https://doc-qt-io.translate.goog/qt-6/qdtls.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QDtlsClientVerifier](https://doc-qt-io.translate.goog/qt-6/qdtlsclientverifier.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QEventLoop](https://doc-qt-io.translate.goog/qt-6/qeventloop.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QExtensionFactory](https://doc-qt-io.translate.goog/qt-6/qextensionfactory.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QExtensionManager](https://doc-qt-io.translate.goog/qt-6/qextensionmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QFileSelector](https://doc-qt-io.translate.goog/qt-6/qfileselector.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QFileSystemWatcher](https://doc-qt-io.translate.goog/qt-6/qfilesystemwatcher.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QFutureWatcher](https://doc-qt-io.translate.goog/qt-6/qfuturewatcher.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGenericPlugin](https://doc-qt-io.translate.goog/qt-6/qgenericplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoAreaMonitorSource](https://doc-qt-io.translate.goog/qt-6/qgeoareamonitorsource.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoCodeReply](https://doc-qt-io.translate.goog/qt-6/qgeocodereply.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoCodingManager](https://doc-qt-io.translate.goog/qt-6/qgeocodingmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoCodingManagerEngine](https://doc-qt-io.translate.goog/qt-6/qgeocodingmanagerengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoPositionInfoSource](https://doc-qt-io.translate.goog/qt-6/qgeopositioninfosource.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoRouteReply](https://doc-qt-io.translate.goog/qt-6/qgeoroutereply.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoRoutingManager](https://doc-qt-io.translate.goog/qt-6/qgeoroutingmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoRoutingManagerEngine](https://doc-qt-io.translate.goog/qt-6/qgeoroutingmanagerengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoSatelliteInfoSource](https://doc-qt-io.translate.goog/qt-6/qgeosatelliteinfosource.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGeoServiceProvider](https://doc-qt-io.translate.goog/qt-6/qgeoserviceprovider.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGesture](https://doc-qt-io.translate.goog/qt-6/qgesture.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGraphicsAnchor](https://doc-qt-io.translate.goog/qt-6/qgraphicsanchor.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGraphicsEffect](https://doc-qt-io.translate.goog/qt-6/qgraphicseffect.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGraphicsItemAnimation](https://doc-qt-io.translate.goog/qt-6/qgraphicsitemanimation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGraphicsObject](https://doc-qt-io.translate.goog/qt-6/qgraphicsobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGraphicsScene](https://doc-qt-io.translate.goog/qt-6/qgraphicsscene.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGraphicsTransform](https://doc-qt-io.translate.goog/qt-6/qgraphicstransform.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QGrpcOperation](https://doc-qt-io.translate.goog/qt-6/qgrpcoperation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QHelpEngineCore](https://doc-qt-io.translate.goog/qt-6/qhelpenginecore.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QHelpFilterEngine](https://doc-qt-io.translate.goog/qt-6/qhelpfilterengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QHelpSearchEngine](https://doc-qt-io.translate.goog/qt-6/qhelpsearchengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QHttpMultiPart](https://doc-qt-io.translate.goog/qt-6/qhttpmultipart.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QIconEnginePlugin](https://doc-qt-io.translate.goog/qt-6/qiconengineplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QImageCapture](https://doc-qt-io.translate.goog/qt-6/qimagecapture.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QImageIOPlugin](https://doc-qt-io.translate.goog/qt-6/qimageioplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QInputDevice](https://doc-qt-io.translate.goog/qt-6/qinputdevice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QInputMethod](https://doc-qt-io.translate.goog/qt-6/qinputmethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QIODevice](https://doc-qt-io.translate.goog/qt-6/qiodevice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QItemSelectionModel](https://doc-qt-io.translate.goog/qt-6/qitemselectionmodel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QJSEngine](https://doc-qt-io.translate.goog/qt-6/qjsengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QLayout](https://doc-qt-io.translate.goog/qt-6/qlayout.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QLegendMarker](https://doc-qt-io.translate.goog/qt-6/qlegendmarker.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QLibrary](https://doc-qt-io.translate.goog/qt-6/qlibrary.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QLocalServer](https://doc-qt-io.translate.goog/qt-6/qlocalserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QLowEnergyController](https://doc-qt-io.translate.goog/qt-6/qlowenergycontroller.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QLowEnergyService](https://doc-qt-io.translate.goog/qt-6/qlowenergyservice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMaskGenerator](https://doc-qt-io.translate.goog/qt-6/qmaskgenerator.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMediaCaptureSession](https://doc-qt-io.translate.goog/qt-6/qmediacapturesession.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMediaDevices](https://doc-qt-io.translate.goog/qt-6/qmediadevices.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMediaPlayer](https://doc-qt-io.translate.goog/qt-6/qmediaplayer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMediaRecorder](https://doc-qt-io.translate.goog/qt-6/qmediarecorder.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMimeData](https://doc-qt-io.translate.goog/qt-6/qmimedata.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QModbusDevice](https://doc-qt-io.translate.goog/qt-6/qmodbusdevice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QModbusReply](https://doc-qt-io.translate.goog/qt-6/qmodbusreply.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMovie](https://doc-qt-io.translate.goog/qt-6/qmovie.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMqttClient](https://doc-qt-io.translate.goog/qt-6/qmqttclient.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QMqttSubscription](https://doc-qt-io.translate.goog/qt-6/qmqttsubscription.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QNearFieldManager](https://doc-qt-io.translate.goog/qt-6/qnearfieldmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QNearFieldTarget](https://doc-qt-io.translate.goog/qt-6/qnearfieldtarget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QNetworkAccessManager](https://doc-qt-io.translate.goog/qt-6/qnetworkaccessmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QNetworkCookieJar](https://doc-qt-io.translate.goog/qt-6/qnetworkcookiejar.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QNetworkInformation](https://doc-qt-io.translate.goog/qt-6/qnetworkinformation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QObjectCleanupHandler](https://doc-qt-io.translate.goog/qt-6/qobjectcleanuphandler.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOffscreenSurface](https://doc-qt-io.translate.goog/qt-6/qoffscreensurface.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpcUaClient](https://doc-qt-io.translate.goog/qt-6/qopcuaclient.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpcUaGdsClient](https://doc-qt-io.translate.goog/qt-6/qopcuagdsclient.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpcUaHistoryReadResponse](https://doc-qt-io.translate.goog/qt-6/qopcuahistoryreadresponse.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpcUaKeyPair](https://doc-qt-io.translate.goog/qt-6/qopcuakeypair.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpcUaNode](https://doc-qt-io.translate.goog/qt-6/qopcuanode.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpcUaProvider](https://doc-qt-io.translate.goog/qt-6/qopcuaprovider.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLContext](https://doc-qt-io.translate.goog/qt-6/qopenglcontext.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLContextGroup](https://doc-qt-io.translate.goog/qt-6/qopenglcontextgroup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLDebugLogger](https://doc-qt-io.translate.goog/qt-6/qopengldebuglogger.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLShader](https://doc-qt-io.translate.goog/qt-6/qopenglshader.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLShaderProgram](https://doc-qt-io.translate.goog/qt-6/qopenglshaderprogram.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLTimeMonitor](https://doc-qt-io.translate.goog/qt-6/qopengltimemonitor.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLTimerQuery](https://doc-qt-io.translate.goog/qt-6/qopengltimerquery.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QOpenGLVertexArrayObject](https://doc-qt-io.translate.goog/qt-6/qopenglvertexarrayobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPdfDocument](https://doc-qt-io.translate.goog/qt-6/qpdfdocument.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPdfPageNavigator](https://doc-qt-io.translate.goog/qt-6/qpdfpagenavigator.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPdfPageRenderer](https://doc-qt-io.translate.goog/qt-6/qpdfpagerenderer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPdfWriter](https://doc-qt-io.translate.goog/qt-6/qpdfwriter.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPieSlice](https://doc-qt-io.translate.goog/qt-6/qpieslice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPlaceManager](https://doc-qt-io.translate.goog/qt-6/qplacemanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPlaceManagerEngine](https://doc-qt-io.translate.goog/qt-6/qplacemanagerengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPlaceReply](https://doc-qt-io.translate.goog/qt-6/qplacereply.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QPluginLoader](https://doc-qt-io.translate.goog/qt-6/qpluginloader.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlComponent](https://doc-qt-io.translate.goog/qt-6/qqmlcomponent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlContext](https://doc-qt-io.translate.goog/qt-6/qqmlcontext.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlEngineExtensionPlugin](https://doc-qt-io.translate.goog/qt-6/qqmlengineextensionplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlExpression](https://doc-qt-io.translate.goog/qt-6/qqmlexpression.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlExtensionPlugin](https://doc-qt-io.translate.goog/qt-6/qqmlextensionplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlFileSelector](https://doc-qt-io.translate.goog/qt-6/qqmlfileselector.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlImageProviderBase](https://doc-qt-io.translate.goog/qt-6/qqmlimageproviderbase.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQmlPropertyMap](https://doc-qt-io.translate.goog/qt-6/qqmlpropertymap.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuick3DObject](https://doc-qt-io.translate.goog/qt-6/qquick3dobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickAttachedPropertyPropagator](https://doc-qt-io.translate.goog/qt-6/qquickattachedpropertypropagator.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickImageResponse](https://doc-qt-io.translate.goog/qt-6/qquickimageresponse.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickItem](https://doc-qt-io.translate.goog/qt-6/qquickitem.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickItemGrabResult](https://doc-qt-io.translate.goog/qt-6/qquickitemgrabresult.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickRenderControl](https://doc-qt-io.translate.goog/qt-6/qquickrendercontrol.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickTextDocument](https://doc-qt-io.translate.goog/qt-6/qquicktextdocument.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickTextureFactory](https://doc-qt-io.translate.goog/qt-6/qquicktexturefactory.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QQuickWebEngineProfile](https://doc-qt-io.translate.goog/qt-6/qquickwebengineprofile.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QRemoteObjectAbstractPersistedStore](https://doc-qt-io.translate.goog/qt-6/qremoteobjectabstractpersistedstore.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QRemoteObjectNode](https://doc-qt-io.translate.goog/qt-6/qremoteobjectnode.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QRemoteObjectPendingCallWatcher](https://doc-qt-io.translate.goog/qt-6/qremoteobjectpendingcallwatcher.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QRemoteObjectReplica](https://doc-qt-io.translate.goog/qt-6/qremoteobjectreplica.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScreen](https://doc-qt-io.translate.goog/qt-6/qscreen.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScreenCapture](https://doc-qt-io.translate.goog/qt-6/qscreencapture.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScroller](https://doc-qt-io.translate.goog/qt-6/qscroller.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScxmlDataModel](https://doc-qt-io.translate.goog/qt-6/qscxmldatamodel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScxmlInvokableService](https://doc-qt-io.translate.goog/qt-6/qscxmlinvokableservice.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScxmlInvokableServiceFactory](https://doc-qt-io.translate.goog/qt-6/qscxmlinvokableservicefactory.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QScxmlStateMachine](https://doc-qt-io.translate.goog/qt-6/qscxmlstatemachine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSensor](https://doc-qt-io.translate.goog/qt-6/qsensor.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSensorBackend](https://doc-qt-io.translate.goog/qt-6/qsensorbackend.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSensorReading](https://doc-qt-io.translate.goog/qt-6/qsensorreading.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSessionManager](https://doc-qt-io.translate.goog/qt-6/qsessionmanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSettings](https://doc-qt-io.translate.goog/qt-6/qsettings.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSGTexture](https://doc-qt-io.translate.goog/qt-6/qsgtexture.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSGTextureProvider](https://doc-qt-io.translate.goog/qt-6/qsgtextureprovider.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSharedMemory](https://doc-qt-io.translate.goog/qt-6/qsharedmemory.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QShortcut](https://doc-qt-io.translate.goog/qt-6/qshortcut.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSignalMapper](https://doc-qt-io.translate.goog/qt-6/qsignalmapper.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSignalSpy](https://doc-qt-io.translate.goog/qt-6/qsignalspy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSocketNotifier](https://doc-qt-io.translate.goog/qt-6/qsocketnotifier.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSoundEffect](https://doc-qt-io.translate.goog/qt-6/qsoundeffect.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSpatialSound](https://doc-qt-io.translate.goog/qt-6/qspatialsound.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSqlDriver](https://doc-qt-io.translate.goog/qt-6/qsqldriver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSqlDriverPlugin](https://doc-qt-io.translate.goog/qt-6/qsqldriverplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QStyle](https://doc-qt-io.translate.goog/qt-6/qstyle.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QStyleHints](https://doc-qt-io.translate.goog/qt-6/qstylehints.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QStylePlugin](https://doc-qt-io.translate.goog/qt-6/qstyleplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSvgRenderer](https://doc-qt-io.translate.goog/qt-6/qsvgrenderer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSyntaxHighlighter](https://doc-qt-io.translate.goog/qt-6/qsyntaxhighlighter.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QSystemTrayIcon](https://doc-qt-io.translate.goog/qt-6/qsystemtrayicon.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DAnimation::QAbstractAnimation](https://doc-qt-io.translate.goog/qt-6/qt3danimation-qabstractanimation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DAnimation::QAnimationController](https://doc-qt-io.translate.goog/qt-6/qt3danimation-qanimationcontroller.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DAnimation::QAnimationGroup](https://doc-qt-io.translate.goog/qt-6/qt3danimation-qanimationgroup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DAnimation::QMorphTarget](https://doc-qt-io.translate.goog/qt-6/qt3danimation-qmorphtarget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DCore::QAbstractAspect](https://doc-qt-io.translate.goog/qt-6/qt3dcore-qabstractaspect.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DCore::QAspectEngine](https://doc-qt-io.translate.goog/qt-6/qt3dcore-qaspectengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DCore::QNode](https://doc-qt-io.translate.goog/qt-6/qt3dcore-qnode.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DCore::Quick::QQmlAspectEngine](https://doc-qt-io.translate.goog/qt-6/qt3dcore-quick-qqmlaspectengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DInput::QInputDeviceIntegration](https://doc-qt-io.translate.goog/qt-6/qt3dinput-qinputdeviceintegration.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DInput::QKeyEvent](https://doc-qt-io.translate.goog/qt-6/qt3dinput-qkeyevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DInput::QMouseEvent](https://doc-qt-io.translate.goog/qt-6/qt3dinput-qmouseevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DInput::QWheelEvent](https://doc-qt-io.translate.goog/qt-6/qt3dinput-qwheelevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QGraphicsApiFilter](https://doc-qt-io.translate.goog/qt-6/qt3drender-qgraphicsapifilter.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QPickEvent](https://doc-qt-io.translate.goog/qt-6/qt3drender-qpickevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QRenderCapabilities](https://doc-qt-io.translate.goog/qt-6/qt3drender-qrendercapabilities.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QRenderCaptureReply](https://doc-qt-io.translate.goog/qt-6/qt3drender-qrendercapturereply.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QStencilOperationArguments](https://doc-qt-io.translate.goog/qt-6/qt3drender-qstenciloperationarguments.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QStencilTestArguments](https://doc-qt-io.translate.goog/qt-6/qt3drender-qstenciltestarguments.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [Qt3DRender::QTextureWrapMode](https://doc-qt-io.translate.goog/qt-6/qt3drender-qtexturewrapmode.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTcpServer](https://doc-qt-io.translate.goog/qt-6/qtcpserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTextDocument](https://doc-qt-io.translate.goog/qt-6/qtextdocument.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTextObject](https://doc-qt-io.translate.goog/qt-6/qtextobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTextToSpeech](https://doc-qt-io.translate.goog/qt-6/qtexttospeech.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QThread](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QThreadPool](https://doc-qt-io.translate.goog/qt-6/qthreadpool.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTimeLine](https://doc-qt-io.translate.goog/qt-6/qtimeline.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QTranslator](https://doc-qt-io.translate.goog/qt-6/qtranslator.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QUiLoader](https://doc-qt-io.translate.goog/qt-6/quiloader.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QUndoGroup](https://doc-qt-io.translate.goog/qt-6/qundogroup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QUndoStack](https://doc-qt-io.translate.goog/qt-6/qundostack.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QValidator](https://doc-qt-io.translate.goog/qt-6/qvalidator.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QValue3DAxisFormatter](https://doc-qt-io.translate.goog/qt-6/qvalue3daxisformatter.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVideoSink](https://doc-qt-io.translate.goog/qt-6/qvideosink.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardAbstractInputMethod](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboardabstractinputmethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardDictionary](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboarddictionary.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardDictionaryManager](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboarddictionarymanager.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardInputContext](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboardinputcontext.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardInputEngine](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboardinputengine.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardObserver](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboardobserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QVirtualKeyboardTrace](https://doc-qt-io.translate.goog/qt-6/qvirtualkeyboardtrace.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandClient](https://doc-qt-io.translate.goog/qt-6/qwaylandclient.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandObject](https://doc-qt-io.translate.goog/qt-6/qwaylandobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandQuickShellIntegration](https://doc-qt-io.translate.goog/qt-6/qwaylandquickshellintegration.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandSurfaceGrabber](https://doc-qt-io.translate.goog/qt-6/qwaylandsurfacegrabber.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandView](https://doc-qt-io.translate.goog/qt-6/qwaylandview.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandXdgPopup](https://doc-qt-io.translate.goog/qt-6/qwaylandxdgpopup.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWaylandXdgToplevel](https://doc-qt-io.translate.goog/qt-6/qwaylandxdgtoplevel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebChannel](https://doc-qt-io.translate.goog/qt-6/qwebchannel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebChannelAbstractTransport](https://doc-qt-io.translate.goog/qt-6/qwebchannelabstracttransport.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineContextMenuRequest](https://doc-qt-io.translate.goog/qt-6/qwebenginecontextmenurequest.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineCookieStore](https://doc-qt-io.translate.goog/qt-6/qwebenginecookiestore.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineDownloadRequest](https://doc-qt-io.translate.goog/qt-6/qwebenginedownloadrequest.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineHistory](https://doc-qt-io.translate.goog/qt-6/qwebenginehistory.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineNavigationRequest](https://doc-qt-io.translate.goog/qt-6/qwebenginenavigationrequest.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineNewWindowRequest](https://doc-qt-io.translate.goog/qt-6/qwebenginenewwindowrequest.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineNotification](https://doc-qt-io.translate.goog/qt-6/qwebenginenotification.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEnginePage](https://doc-qt-io.translate.goog/qt-6/qwebenginepage.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineProfile](https://doc-qt-io.translate.goog/qt-6/qwebengineprofile.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineUrlRequestInterceptor](https://doc-qt-io.translate.goog/qt-6/qwebengineurlrequestinterceptor.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineUrlRequestJob](https://doc-qt-io.translate.goog/qt-6/qwebengineurlrequestjob.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebEngineUrlSchemeHandler](https://doc-qt-io.translate.goog/qt-6/qwebengineurlschemehandler.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebSocket](https://doc-qt-io.translate.goog/qt-6/qwebsocket.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWebSocketServer](https://doc-qt-io.translate.goog/qt-6/qwebsocketserver.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWidget](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), [QWindow](https://doc-qt-io.translate.goog/qt-6/qwindow.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp), and [QWinEventNotifier](https://doc-qt-io.translate.goog/qt-6/qwineventnotifier.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) |

- [所有成员的列表，包括继承的成员](https://doc-qt-io.translate.goog/qt-6/qobject-members.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)
- [已弃用的成员](https://doc-qt-io.translate.goog/qt-6/qobject-obsolete.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)

**注意：**该类中的所有函数都是[reentrant](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**注意：**这些功能也[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp):

- [connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)()
- [connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-2)()
- [connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-3)()
- [connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-4)()
- [connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-5)()
- [disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)()
- [disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-2)()
- [disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-5)()
- [deleteLater](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#deleteLater)()

## 特性

- **[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)** : QString

## 公共方法

|                             | **[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject)**(QObject **parent* = nullptr) |
| --------------------------- | ------------------------------------------------------------ |
| virtual                     | **[~QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dtor.QObject)**() |
| QBindable<QString>          | **[bindableObjectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)**() |
| bool                        | **[blockSignals](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#blockSignals)**(bool *block*) |
| const QObjectList &         | **[children](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#children)**() const |
| QMetaObject::Connection     | **[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-2)**(const QObject **sender*, const char **signal*, const char **method*, Qt::ConnectionType *type* = Qt::AutoConnection) const |
| bool                        | **[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-2)**(const char **signal* = nullptr, const QObject **receiver* = nullptr, const char **method* = nullptr) const |
| bool                        | **[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-3)**(const QObject **receiver*, const char **method* = nullptr) const |
| void                        | **[dumpObjectInfo](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dumpObjectInfo)**() const |
| void                        | **[dumpObjectTree](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dumpObjectTree)**() const |
| QList<QByteArray>           | **[dynamicPropertyNames](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dynamicPropertyNames)**() const |
| virtual bool                | **[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)**(QEvent **e*) |
| virtual bool                | **[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)**(QObject **watched*, QEvent **event*) |
| T                           | **[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)**(const QString &*name* = QString(), Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| QList< T>                   | **[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)**(const QString &*name*, Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| QList< T>                   | **[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren-1)**(Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| QList< T>                   | **[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren-2)**(const QRegularExpression &*re*, Qt::FindChildOptions *options* = Qt::FindChildrenRecursively) const |
| bool                        | **[inherits](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#inherits)**(const char **className*) const |
| void                        | **[installEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#installEventFilter)**(QObject **filterObj*) |
| bool                        | **[isQuickItemType](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isQuickItemType)**() const |
| bool                        | **[isWidgetType](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isWidgetType)**() const |
| bool                        | **[isWindowType](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isWindowType)**() const |
| void                        | **[killTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#killTimer)**(int *id*) |
| virtual const QMetaObject * | **[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)**() const |
| void                        | **[moveToThread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#moveToThread)**(QThread **targetThread*) |
| QString                     | **[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)**() const |
| QObject *                   | **[parent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#parent)**() const |
| QVariant                    | **[property](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#property)**(const char **name*) const |
| void                        | **[removeEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#removeEventFilter)**(QObject **obj*) |
| void                        | **[setObjectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setObjectName)**(const QString &*name*) |
| void                        | **[setObjectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setObjectName-1)**(QAnyStringView *name*) |
| void                        | **[setParent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setParent)**(QObject **parent*) |
| bool                        | **[setProperty](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setProperty)**(const char **name*, const QVariant &*value*) |
| bool                        | **[signalsBlocked](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#signalsBlocked)**() const |
| int                         | **[startTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#startTimer)**(int *interval*, Qt::TimerType *timerType* = Qt::CoarseTimer) |
| int                         | **[startTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#startTimer-1)**(std::chrono::milliseconds *time*, Qt::TimerType *timerType* = Qt::CoarseTimer) |
| QThread *                   | **[thread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#thread)**() const |

## 公共槽

| void | **[deleteLater](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#deleteLater)**() |
| ---- | ------------------------------------------------------------ |
|      |                                                              |

## 信号

| void | **[destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)**(QObject **obj* = nullptr) |
| ---- | ------------------------------------------------------------ |
| void | **[objectNameChanged](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectNameChanged)**(const QString &*objectName*) |

## 静态公共成员

| QMetaObject::Connection | **[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)**(const QObject **sender*, const char **signal*, const QObject **receiver*, const char **method*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| ----------------------- | ------------------------------------------------------------ |
| QMetaObject::Connection | **[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-1)**(const QObject **sender*, const QMetaMethod &*signal*, const QObject **receiver*, const QMetaMethod &*method*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| QMetaObject::Connection | **[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-3)**(const QObject **sender*, PointerToMemberFunction *signal*, const QObject **receiver*, PointerToMemberFunction *method*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| QMetaObject::Connection | **[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-4)**(const QObject **sender*, PointerToMemberFunction *signal*, Functor *functor*) |
| QMetaObject::Connection | **[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect-5)**(const QObject **sender*, PointerToMemberFunction *signal*, const QObject **context*, Functor *functor*, Qt::ConnectionType *type* = Qt::AutoConnection) |
| bool                    | **[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)**(const QObject **sender*, const char **signal*, const QObject **receiver*, const char **method*) |
| bool                    | **[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-1)**(const QObject **sender*, const QMetaMethod &*signal*, const QObject **receiver*, const QMetaMethod &*method*) |
| bool                    | **[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-4)**(const QMetaObject::Connection &*connection*) |
| bool                    | **[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect-5)**(const QObject **sender*, PointerToMemberFunction *signal*, const QObject **receiver*, PointerToMemberFunction *method*) |
| const QMetaObject       | **[staticMetaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#staticMetaObject-var)** |
| QString                 | **[tr](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#tr)**(const char **sourceText*, const char **disambiguation* = nullptr, int *n* = -1) |

## protected function

| virtual void | **[childEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#childEvent)**(QChildEvent **event*) |
| ------------ | ------------------------------------------------------------ |
| virtual void | **[connectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connectNotify)**(const QMetaMethod &*signal*) |
| virtual void | **[customEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#customEvent)**(QEvent **event*) |
| virtual void | **[disconnectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnectNotify)**(const QMetaMethod &*signal*) |
| bool         | **[isSignalConnected](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isSignalConnected)**(const QMetaMethod &*signal*) const |
| int          | **[receivers](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#receivers)**(const char **signal*) const |
| QObject *    | **[sender](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#sender)**() const |
| int          | **[senderSignalIndex](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#senderSignalIndex)**() const |
| virtual void | **[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)**(QTimerEvent **event*) |

## 相关非成员

|      | **[QObjectList](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObjectList-typedef)** |
| ---- | ------------------------------------------------------------ |
| T    | **[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast)**(QObject **object*) |
| T    | **[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast-1)**(const QObject **object*) |

## 宏

|      | **[QT_NO_NARROWING_CONVERSIONS_IN_CONNECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QT_NO_NARROWING_CONVERSIONS_IN_CONNECT)** |
| ---- | ------------------------------------------------------------ |
|      | **[Q_CLASSINFO](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_CLASSINFO)**(*Name*, *Value*) |
|      | **[Q_EMIT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_EMIT)** |
|      | **[Q_ENUM](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM)**(...) |
|      | **[Q_ENUM_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM_NS)**(...) |
|      | **[Q_FLAG](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG)**(...) |
|      | **[Q_FLAG_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG_NS)**(...) |
|      | **[Q_GADGET](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET)** |
|      | **[Q_GADGET_EXPORT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET_EXPORT)**(*EXPORT_MACRO*) |
|      | **[Q_INTERFACES](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_INTERFACES)**(...) |
|      | **[Q_INVOKABLE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_INVOKABLE)** |
|      | **[Q_MOC_INCLUDE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_MOC_INCLUDE)** |
|      | **[Q_NAMESPACE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE)** |
|      | **[Q_NAMESPACE_EXPORT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE_EXPORT)**(*EXPORT_MACRO*) |
|      | **[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)** |
|      | **[Q_PROPERTY](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_PROPERTY)**(...) |
|      | **[Q_REVISION](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_REVISION)** |
|      | **[Q_SET_OBJECT_NAME](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_SET_OBJECT_NAME)**(*Object*) |
|      | **[Q_SIGNAL](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_SIGNAL)** |
|      | **[Q_SIGNALS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_SIGNALS)** |
|      | **[Q_SLOT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_SLOT)** |
|      | **[Q_SLOTS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_SLOTS)** |

## 详细说明

QObject 是 Qt 的核心[Object Model](https://doc-qt-io.translate.goog/qt-6/object.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。该模型的核心特征是一种非常强大的无缝对象通信机制，称为[signals and slots](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。您可以将信号连接到插槽[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)() 并破坏与的连接[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)()。为了避免永无休止的通知循环，您可以暂时阻止信号[blockSignals](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#blockSignals)()。受保护的函数[connectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connectNotify)（） 和[disconnectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnectNotify)() 使得跟踪连接成为可能。

QObjects 组织自己[object trees](https://doc-qt-io.translate.goog/qt-6/objecttrees.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。当您创建一个以另一个对象作为父对象的 QObject 时，该对象将自动将其自身添加到父对象的 QObject 中[children](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#children)（） 列表。父对象拥有该对象的所有权；即，它将自动在其析构函数中删除其子级。您可以按名称查找对象，也可以使用类型来查找对象[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)（） 或者[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)()。

每个对象都有一个[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)() 及其类名可以通过相应的[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)（） （看[QMetaObject::className](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#className)())。您可以使用以下方法确定对象的类是否继承了 QObject 继承层次结构中的另一个类[inherits](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#inherits)（） 功能。

当一个对象被删除时，它会发出一个[destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)（） 信号。您可以捕获此信号以避免对 QObject 的悬空引用。

QObjects 可以通过以下方式接收事件[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)() 并过滤其他对象的事件。看[installEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#installEventFilter)（） 和[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)（）了解详情。一个便利的处理者，[childEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#childEvent)()，可以重新实现以捕获子事件。

最后但并非最不重要的一点是，QObject 在 Qt 中提供了基本的计时器支持；看[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)对定时器的高级支持。

请注意，[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)宏对于任何实现信号、槽或属性的对象都是必需的。您还需要运行[Meta Object Compiler](https://doc-qt-io.translate.goog/qt-6/moc.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)在源文件上。我们强烈建议在 QObject 的所有子类中使用此宏，无论它们是否实际使用信号、槽和属性，因为不这样做可能会导致某些函数表现出奇怪的行为。

所有 Qt 小部件都继承 QObject。便利功能[isWidgetType](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isWidgetType)() 返回一个对象是否实际上是一个小部件。它比[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast)<[QWidget](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)*>( *obj* ) 或*obj* ->[inherits](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#inherits)（“[QWidget](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)”）。

一些QObject函数，例如[children](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#children)()，返回一个[QObjectList](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObjectList-typedef)。[QObjectList](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObjectList-typedef)是一个类型定义[QList](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)<QObject *>。

### 线程亲和力

据说 QObject 实例具有*线程关联性*，或者说它*存在*于某个线程中。当 QObject 接收到[queued signal](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum)或一个[posted event](https://doc-qt-io.translate.goog/qt-6/eventsandfilters.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#sending-events)，槽或事件处理程序将在对象所在的线程中运行。

**注意：**如果 QObject 没有线程亲和性（也就是说，如果[thread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#thread)() 返回零），或者如果它位于没有运行事件循环的线程中，则它无法接收排队信号或发布的事件。

默认情况下，QObject 存在于创建它的线程中。可以使用以下方式查询对象的线程关联性[thread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#thread)() 并更改为使用[moveToThread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#moveToThread)()。

所有 QObject 必须与其父对象位于同一线程中。最后：

- [setParent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setParent)如果涉及的两个 QObject 位于不同的线程中，() 将失败。
- 当 QObject 被移动到另一个线程时，它的所有子对象也将自动移动。
- [moveToThread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#moveToThread)如果 QObject 有父对象，() 将失败。
- 如果 QObjects 创建于[QThread::run](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#run)()，他们不能成为[QThread](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)对象因为[QThread](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)不存在于调用的线程中[QThread::run](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#run)()。

**注意：** QObject 的成员变量*不会*自动成为其子变量。父子关系必须通过传递一个指向子对象的指针来设置[constructor](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject)，或通过致电[setParent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setParent)()。如果没有这一步，对象的成员变量将保留在旧线程中[moveToThread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#moveToThread)（） 叫做。



### 无复制构造函数或赋值运算符

QObject 既没有复制构造函数，也没有赋值运算符。这是设计使然。实际上，它们是被声明的，但是在`private`带有宏的部分中[Q_DISABLE_COPY](https://doc-qt-io.translate.goog/qt-6/qtclasshelpermacros-proxy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DISABLE_COPY)()。事实上，所有从 QObject 派生（直接或间接）的 Qt 类都使用此宏来声明其复制构造函数和赋值运算符为私有。推理可以在以下讨论中找到[Identity vs Value](https://doc-qt-io.translate.goog/qt-6/object.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#identity-vs-value)在Qt上[Object Model](https://doc-qt-io.translate.goog/qt-6/object.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)页。

主要结果是您应该使用指向 QObject（或 QObject 子类）的指针，否则您可能会想使用 QObject 子类作为值。例如，如果没有复制构造函数，则无法使用 QObject 的子类作为要存储在容器类之一中的值。您必须存储指针。

### 自动连接

Qt 的元对象系统提供了一种自动连接 QObject 子类及其子类之间的信号和槽的机制。只要使用合适的对象名称定义对象，并且槽遵循简单的命名约定，就可以在运行时通过[QMetaObject::connectSlotsByName](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connectSlotsByName)（） 功能。

[uic](https://doc-qt-io.translate.goog/qt-6/uic.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)*生成调用此函数的代码，以启用使用Qt Designer*创建的表单上的小部件之间执行自动连接。*有关使用Qt Designer*自动连接的更多信息，请参阅[Using a Designer UI File in Your Application](https://doc-qt-io.translate.goog/qt-6/designer-using-a-ui-file.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)*Qt Designer*手册的部分。

### 动态属性

从 Qt 4.2 开始，可以在运行时向 QObject 实例添加和删除动态属性。动态属性不需要在编译时声明，但它们提供与静态属性相同的优点，并且使用相同的 API 进行操作 - 使用[property](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#property)() 阅读它们并[setProperty](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setProperty)() 来写它们。

从 Qt 4.3 开始，支持动态属性[Qt Designer](https://doc-qt-io.translate.goog/qt-6/designer-widget-mode.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#the-property-editor)，并且标准 Qt 小部件和用户创建的表单都可以被赋予动态属性。

### 国际化 (I18n)

所有 QObject 子类都支持 Qt 的翻译功能，从而可以将应用程序的用户界面翻译成不同的语言。

为了使用户可见的文本可翻译，必须将其包含在对[tr](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#tr)（） 功能。这在[Writing Source Code for Translation](https://doc-qt-io.translate.goog/qt-6/i18n-source-translation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)文档。

**也可以看看**[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[QPointer](https://doc-qt-io.translate.goog/qt-6/qpointer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[QObjectCleanupHandler](https://doc-qt-io.translate.goog/qt-6/qobjectcleanuphandler.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Q_DISABLE_COPY](https://doc-qt-io.translate.goog/qt-6/qtclasshelpermacros-proxy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DISABLE_COPY)（）， 和[Object Trees & Ownership](https://doc-qt-io.translate.goog/qt-6/objecttrees.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

## 属性文档

### `[bindable]`objectName : [QString](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)

**注：**该属性支持[QProperty](https://doc-qt-io.translate.goog/qt-6/qproperty.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)绑定。

该属性保存该对象的名称

您可以使用以下命令按名称（和类型）查找对象[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)()。您可以找到一组对象[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)()。

```
qDebug("MyClass::setPrecision(): (%s) invalid precision %f",
       qPrintable(objectName()), newPrecision);
```

默认情况下，该属性包含一个空字符串。

**也可以看看**[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)（） 和[QMetaObject::className](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#className)()。

## 成员函数文档

### `[invokable]`QObject::QObject([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **parent* = nullptr)

使用父对象构造一个对象*parent*。

对象的父对象可以被视为该对象的所有者。例如，一个[dialog box](https://doc-qt-io.translate.goog/qt-6/qdialog.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)是 的父级**OK**和**Cancel**它包含的按钮。

父对象的析构函数会销毁所有子对象。

环境*parent*构造`nullptr`一个没有父对象的对象。如果该对象是一个小部件，它将成为一个顶级窗口。

**注意：**该函数可以通过元对象系统和 QML 调用。看[Q_INVOKABLE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_INVOKABLE)。

**也可以看看**[parent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#parent)(),[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)（）， 和[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)()。

### `[virtual]`QObject::~QObject()

销毁对象，删除其所有子对象。

传入和传出该对象的所有信号都会自动断开，并且该对象的任何挂起的已发布事件都会从事件队列中删除。然而，使用通常更安全[deleteLater](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#deleteLater)() 而不是删除[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)直接子类化。

**警告：**所有子对象都将被删除。如果这些对象中的任何一个位于堆栈或全局中，那么您的程序迟早会崩溃。我们不建议从父对象外部保存指向子对象的指针。如果您仍然这样做，[destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)() 信号使您有机会检测对象何时被销毁。

**警告：**删除[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)当挂起的事件正在等待传递时可能会导致崩溃。您不得删除[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)如果它存在于与当前正在执行的线程不同的线程中，则直接执行。使用[deleteLater](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#deleteLater)() 而是，这将导致事件循环在所有待处理事件传递给对象后删除该对象。

**也可以看看**[deleteLater](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#deleteLater)()。

### bool QObject::blockSignals(bool *block*)

如果*block*为 true 时，该对象发出的信号将被阻止（即，发出信号不会调用与其连接的任何对象）。如果*block*为 false，则不会发生此类阻塞。

返回值是之前的值[signalsBlocked](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#signalsBlocked)()。

请注意，[destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)即使该对象的信号已被阻止， () 信号也会被发射。

被阻止时发出的信号不会被缓冲。

**也可以看看**[signalsBlocked](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#signalsBlocked)（） 和[QSignalBlocker](https://doc-qt-io.translate.goog/qt-6/qsignalblocker.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[virtual protected]`void QObject::childEvent([QChildEvent](https://doc-qt-io.translate.goog/qt-6/qchildevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) **event*)

该事件处理程序可以在子类中重新实现以接收子事件。该事件在*event*范围。

[QEvent::ChildAdded](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)和[QEvent::ChildRemoved](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)添加或删除子项时，事件会发送到对象。在这两种情况下，您只能依靠孩子作为[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 或者如果[isWidgetType](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isWidgetType)() 返回`true`, a[QWidget](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。（这是因为，在[ChildAdded](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)在这种情况下，孩子还没有完全构造出来，并且在[ChildRemoved](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)如果它可能已经被破坏了）。

[QEvent::ChildPolished](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)当子项被完善或添加完善的子项时，事件将发送到小部件。如果您收到子级抛光事件，则子级的构建通常已完成。但是，这并不能得到保证，并且在小部件的构造函数执行期间可能会传递多个抛光事件。

对于每个子小部件，您都会收到一个[ChildAdded](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)事件，零个或多个[ChildPolished](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)事件，以及一个[ChildRemoved](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)事件。

这[ChildPolished](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)如果添加子项后立即将其删除，则事件将被忽略。如果一个子项在构建和销毁过程中被多次抛光，您可能会收到同一个子项的多个子项抛光事件，每次都使用不同的虚拟表。

**也可以看看**[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)()。

### const [QObjectList](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObjectList-typedef) &QObject::children() const

返回子对象的列表。这[QObjectList](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObjectList-typedef)类在头文件中定义`<QObject>`如下：

```
typedef QList<QObject*> QObjectList;
```

添加的第一个孩子是[first](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#first)列表中的对象，最后添加的子对象是[last](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#last)列表中的对象，即新的子对象附加在末尾。

请注意，列表顺序会在以下情况发生变化：[QWidget](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)孩子们是[raised](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#raise)或者[lowered](https://doc-qt-io.translate.goog/qt-6/qwidget.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#lower)。升起的小部件将成为列表中的最后一个对象，降下的小部件将成为列表中的第一个对象。

**也可以看看**[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)(),[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)(),[parent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#parent)（）， 和[setParent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setParent)()。

### `[static]`[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::connect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, const char **signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, const char **method*, [Qt::ConnectionType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type* = Qt::AutoConnection)

创建给定的连接*type*来自*signal*在里面*sender*反对*method*在里面*receiver*目的。返回连接的句柄，稍后可用于断开连接。

指定时必须使用`SIGNAL()`和宏`SLOT()`*signal*和*method*， 例如：

```
QLabel *label = new QLabel;
QScrollBar *scrollBar = new QScrollBar;
QObject::connect(scrollBar, SIGNAL(valueChanged(int)),
                 label,  SLOT(setNum(int)));
```

此示例确保标签始终显示当前滚动条值。请注意，信号和槽参数不得包含任何变量名称，只能包含类型。例如，以下内容将不起作用并返回 false：

```
// WRONG
QObject::connect(scrollBar, SIGNAL(valueChanged(int value)),
                 label, SLOT(setNum(int value)));
```

一个信号也可以连接到另一个信号：

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

在此示例中，`MyWidget`构造函数中继来自私有成员变量的信号，并使其在与 相关的名称下可用`MyWidget`。

一个信号可以连接到许多插槽和信号。一个插槽可以连接多个信号。

如果一个信号连接到多个插槽，则当信号发出时，这些插槽将按照连接时的相同顺序被激活。

该函数返回一个[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)如果成功将信号连接到插槽，则表示连接的句柄。如果无法创建连接，连接句柄将无效，例如，如果[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)无法验证两者的存在*signal*或者*method*，或者如果他们的签名不兼容。您可以通过将句柄转换为布尔值来检查句柄是否有效。

默认情况下，您建立的每个连接都会发出一个信号；对于重复连接会发出两个信号。您可以用一个命令来断开所有这些连接[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)（） 称呼。如果您通过了[Qt::UniqueConnection](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type*，只有在不重复的情况下才会建立连接。如果已经存在重复项（相同对象上完全相同的插槽的完全相同的信号），连接将失败并且连接将返回无效[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**注意：** Qt::UniqueConnections 不适用于 lambda、非成员函数和函子；它们仅适用于连接到成员函数。

可选的*type*参数描述要建立的连接类型。特别是，它确定特定信号是立即传送到时隙还是稍后排队传送。如果信号排队，参数必须是 Qt 元对象系统已知的类型，因为 Qt 需要复制参数以将它们存储在幕后的事件中。如果您尝试使用排队连接并收到错误消息

```
QObject::connect: Cannot queue arguments of type 'MyType'
(Make sure 'MyType' is registered using qRegisterMetaType().)
```

称呼[qRegisterMetaType](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qRegisterMetaType-3)() 在建立连接之前注册数据类型。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)(),[sender](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#sender)(),[qRegisterMetaType](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qRegisterMetaType-3)(),[Q_DECLARE_METATYPE](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DECLARE_METATYPE)（）， 和[Differences between String-Based and Functor-Based Connections](https://doc-qt-io.translate.goog/qt-6/signalsandslots-syntaxes.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[static]`[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::connect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*method*, [Qt::ConnectionType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type* = Qt::AutoConnection)

创建给定的连接*type*来自*signal*在里面*sender*反对*method*在里面*receiver*目的。返回连接的句柄，稍后可用于断开连接。

如果无法创建连接，则连接句柄将无效，例如参数无效。您可以检查是否[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)通过将其转换为 bool 来使其有效。

该函数的工作方式`connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type)`与[QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)指定信号和方法。

**也可以看看**[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)（const QObject *发送方、const char *信号、const QObject *接收方、const char *方法、Qt::ConnectionType 类型）。

### [QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::connect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, const char **signal*, const char **method*, [Qt::ConnectionType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type* = Qt::AutoConnection) const

该函数重载了 connect()。

连接*signal*来自*sender*对象到这个对象的*method*。

相当于连接(*sender*,*signal*, `this`,*method*,*type*）。

您建立的每个连接都会发出一个信号，因此重复的连接会发出两个信号。您可以使用以下命令断开连接[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)()。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)()。

### `[static]`template < typename PointerToMemberFunction> [QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::connect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, PointerToMemberFunction *signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, PointerToMemberFunction *method*, [Qt::ConnectionType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type* = Qt::AutoConnection)

该函数重载了 connect()。

创建给定的连接*type*来自*signal*在里面*sender*反对*method*在里面*receiver*目的。返回连接的句柄，稍后可用于断开连接。

该信号必须是在标头中声明为信号的函数。槽函数可以是任何可以连接到信号的成员函数。如果信号至少具有与槽一样多的参数，并且信号和槽中相应参数的类型之间存在隐式转换，则槽可以连接到给定信号。

例子：

```
QLabel *label = new QLabel;
QLineEdit *lineEdit = new QLineEdit;
QObject::connect(lineEdit, &QLineEdit::textChanged,
                 label,  &QLabel::setText);
```

此示例确保标签始终显示当前行编辑文本。

一个信号可以连接到许多插槽和信号。一个插槽可以连接多个信号。

如果一个信号连接到多个插槽，则当信号发出时，这些插槽将按照与建立连接的顺序相同的顺序激活

如果该函数成功地将信号连接到槽，则返回一个连接句柄。如果无法创建连接，连接句柄将无效，例如，如果[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)无法验证是否存在*signal*（如果它没有声明为信号）您可以检查是否[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)通过将其转换为 bool 来使其有效。

默认情况下，您建立的每个连接都会发出一个信号；对于重复连接会发出两个信号。您可以用一个命令来断开所有这些连接[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)（） 称呼。如果您通过了[Qt::UniqueConnection](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type*，只有在不重复的情况下才会建立连接。如果已经存在重复项（相同对象上完全相同的插槽的完全相同的信号），连接将失败并且连接将返回无效[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

可选的*type*参数描述要建立的连接类型。特别是，它确定特定信号是立即传送到时隙还是稍后排队传送。如果信号排队，参数必须是 Qt 元对象系统已知的类型，因为 Qt 需要复制参数以将它们存储在幕后的事件中。如果您尝试使用排队连接并收到错误消息

```
QObject::connect: Cannot queue arguments of type 'MyType'
(Make sure 'MyType' is registered using qRegisterMetaType().)
```

确保声明参数类型[Q_DECLARE_METATYPE](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DECLARE_METATYPE)

重载的函数可以通过以下方法解决[qOverload](https://doc-qt-io.translate.goog/qt-6/qoverload-proxy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qOverload)。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[Differences between String-Based and Functor-Based Connections](https://doc-qt-io.translate.goog/qt-6/signalsandslots-syntaxes.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[static]`template <typename PointerToMemberFunction, typename Functor> [QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::connect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, PointerToMemberFunction *signal*, Functor *functor*)

该函数重载了 connect()。

从以下位置创建连接*signal*在*sender*反对*functor*，并返回连接的句柄

该信号必须是在标头中声明为信号的函数。槽函数可以是任何可以连接到信号的函数或函子。如果信号具有至少与槽函数一样多的参数，则槽函数可以连接到给定信号。信号和槽中相应参数的类型之间必须存在隐式转换。

例子：

```
void someFunction();
QPushButton *button = new QPushButton;
QObject::connect(button, &QPushButton::clicked, someFunction);
```

还可以使用 Lambda 表达式：

```
QByteArray page = ...;
QTcpSocket *socket = new QTcpSocket;
socket->connectToHost("qt-project.org", 80);
QObject::connect(socket, &QTcpSocket::connected, [=] () {
        socket->write("GET " + page + "\r\n");
    });
```

如果发送者被破坏，连接将自动断开。但是，您应该注意，当发出信号时，函子中使用的任何对象仍然处于活动状态。

重载的函数可以通过以下方法解决[qOverload](https://doc-qt-io.translate.goog/qt-6/qoverload-proxy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qOverload)。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[static]`template <typename PointerToMemberFunction, typename Functor> [QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::connect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, PointerToMemberFunction *signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **context*, Functor *functor*, [Qt::ConnectionType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum) *type* = Qt::AutoConnection)

该函数重载了 connect()。

创建给定的连接*type*从*signal*在*sender*反对*functor*被放置在特定的事件循环中*context*，并返回连接的句柄。

**注意：** Qt::UniqueConnections 不适用于 lambda、非成员函数和函子；它们仅适用于连接到成员函数。

该信号必须是在标头中声明为信号的函数。槽函数可以是任何可以连接到信号的函数或函子。如果信号具有至少与槽函数一样多的参数，则槽函数可以连接到给定信号。信号和槽中相应参数的类型之间必须存在隐式转换。

例子：

```
void someFunction();
QPushButton *button = new QPushButton;
QObject::connect(button, &QPushButton::clicked, this, someFunction, Qt::QueuedConnection);
```

还可以使用 Lambda 表达式：

```
QByteArray page = ...;
QTcpSocket *socket = new QTcpSocket;
socket->connectToHost("qt-project.org", 80);
QObject::connect(socket, &QTcpSocket::connected, this, [=] () {
        socket->write("GET " + page + "\r\n");
    }, Qt::AutoConnection);
```

如果发送者或上下文被破坏，连接将自动断开。但是，您应该注意，当发出信号时，函子中使用的任何对象仍然处于活动状态。

重载的函数可以通过以下方法解决[qOverload](https://doc-qt-io.translate.goog/qt-6/qoverload-proxy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qOverload)。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[virtual protected]`void QObject::connectNotify(const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*signal*)

当某些东西连接到时会调用此虚函数*signal*在这个对象中。

如果你想比较*signal*对于特定信号，您可以使用[QMetaMethod::fromSignal](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#fromSignal)（） 如下：

```
if (signal == QMetaMethod::fromSignal(&MyObject::valueChanged)) {
    // signal is valueChanged
}
```

**警告：**该函数违反了面向对象的模块化原则。但是，当您仅在某些东西连接到信号时才需要执行昂贵的初始化时，它可能很有用。

**警告：**该函数是从执行连接的线程调用的，该线程可能与该对象所在的线程不同。该函数也可以用[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)内部互斥体已锁定。因此，不允许重新输入任何内容[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)功能，包括[isSignalConnected](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isSignalConnected)()，来自您的重新实现。如果您在重新实现中锁定互斥锁，请确保您不会调用[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)函数的互斥体保存在其他地方，否则会导致死锁。

**也可以看看**[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)（） 和[disconnectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnectNotify)()。

### `[virtual protected]`void QObject::customEvent([QEvent](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) **event*)

可以在子类中重新实现此事件处理程序以接收自定义事件。自定义事件是用户定义的事件，其类型值至少与[QEvent::User](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)的项目[QEvent::Type](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)枚举，通常是[QEvent](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)子类。该事件在*event*范围。

**也可以看看**[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)（） 和[QEvent](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[slot]`void QObject::deleteLater()

安排删除该对象。

当控制权返回到事件循环时，该对象将被删除。如果调用此函数时事件循环未运行（例如，之前在对象上调用了deleteLater()）[QCoreApplication::exec](https://doc-qt-io.translate.goog/qt-6/qcoreapplication.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#exec)())，一旦事件循环启动，该对象就会被删除。如果在主事件循环停止后调用deleteLater()，则该对象将不会被删除。从 Qt 4.8 开始，如果对存在于没有运行事件循环的线程中的对象调用 deleteLater()，则该对象将在线程结束时被销毁。

请注意，进入和离开新的事件循环（例如，通过打开模式对话框）将不会*执行*延迟删除；对于要删除的对象，控件必须返回到调用deleteLater() 的事件循环。这不适用于在先前的嵌套事件循环仍在运行时删除的对象：Qt 事件循环将在新的嵌套事件循环启动后立即删除这些对象。

**注意：**多次调用该函数是安全的；当第一个延迟删除事件被传递时，该对象的任何待处理事件都将从事件队列中删除。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)（） 和[QPointer](https://doc-qt-io.translate.goog/qt-6/qpointer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[signal]`void QObject::destroyed([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **obj* = nullptr)

该信号在物体之前立即发出*obj*在发生任何事件后被销毁[QPointer](https://doc-qt-io.translate.goog/qt-6/qpointer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)已通知，无法屏蔽。

该信号发出后，所有对象的子对象都会立即被销毁。

**也可以看看**[deleteLater](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#deleteLater)（） 和[QPointer](https://doc-qt-io.translate.goog/qt-6/qpointer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### `[static]`bool QObject::disconnect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, const char **signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, const char **method*)

断开连接*signal*在对象中*sender*从*method*在对象中*receiver*。`true`如果连接成功断开则返回；否则返回`false`.

当涉及的任何一个对象被销毁时，信号槽连接就会被删除。

connect() 通常以三种方式使用，如以下示例所示。

1. 断开与对象信号连接的所有连接：

   ```
   disconnect(myObject, nullptr, nullptr, nullptr);
   ```

   相当于非静态重载函数

   ```
   myObject->disconnect();
   ```

2. 断开连接到特定信号的所有连接：

   ```
   disconnect(myObject, SIGNAL(mySignal()), nullptr, nullptr);
   ```

   相当于非静态重载函数

   ```
   myObject->disconnect(SIGNAL(mySignal()));
   ```

3. 断开特定接收器的连接：

   ```
   disconnect(myObject, nullptr, myReceiver, nullptr);
   ```

   相当于非静态重载函数

   ```
   myObject->disconnect(myReceiver);
   ```

`nullptr`可以用作通配符，分别表示“任何信号”、“任何接收对象”或“接收对象中的任何槽”。

这*sender*也许永远不会`nullptr`。（您无法在一次调用中断开来自多个对象的信号。）

如果*signal*是`nullptr`，它断开连接*receiver*和*method*来自任何信号。如果没有，则仅断开指定的信号。

如果*receiver*是的`nullptr`，它会断开连接到的任何东西*signal*。如果不是，则插入除*receiver*没有断开连接。

如果*method*是的`nullptr`，它会断开所有连接到的连接*receiver*。如果没有，则仅指定插槽*method*将被断开连接，并且所有其他插槽将保持不变。这*method*必须是`nullptr`如果*receiver*被遗漏，因此您无法断开所有对象上特定命名的插槽。

**注意：**断开所有信号槽连接也会断开[QObject::destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)() 信号（如果已连接）。这样做可能会对依赖此信号来清理资源的类产生不利影响。建议仅断开由应用程序代码连接的特定信号。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)()。

### `[static]`bool QObject::disconnect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*method*)

断开连接*signal*在对象中*sender*从*method*在对象中*receiver*。`true`如果连接成功断开则返回；否则返回`false`.

`disconnect(const QObject *sender, const char *signal, const QObject *receiver, const char *method)`该函数提供了与但使用相同的可能性[QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)来表示要断开的信号和方法。

此外，如果出现以下情况，该函数将返回 false，并且不会断开任何信号和槽：

1. *signal*不是发送者类或其父类之一的成员。
2. *method*不是接收者类或其父类之一的成员。
3. *signal*实例不代表信号。

QMetaMethod() 可以用作通配符，含义为“任何信号”或“接收对象中的任何槽”。以同样的方式`nullptr`可以用于*receiver*意思是“任何接收对象”。在这种情况下，方法也应该是 QMetaMethod()。*sender*参数应该是 never `nullptr`。

**注意：**断开所有信号槽连接也会断开[QObject::destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)() 信号（如果已连接）。这样做可能会对依赖此信号来清理资源的类产生不利影响。建议仅断开由应用程序代码连接的特定信号。

**也可以看看**[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)（const QObject *发送者，const char *信号，const QObject *接收者，const char *方法）。

### bool QObject::disconnect(const char **signal* = nullptr, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver* = nullptr, const char **method* = nullptr) const

该函数重载disconnect()。

断开连接*signal*从*method*的*receiver*。

当涉及的任何一个对象被销毁时，信号槽连接就会被删除。

**注意：**断开所有信号槽连接也会断开[QObject::destroyed](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#destroyed)() 信号（如果已连接）。这样做可能会对依赖此信号来清理资源的类产生不利影响。建议仅断开由应用程序代码连接的特定信号。

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### bool QObject::disconnect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, const char **method* = nullptr) const

该函数重载disconnect()。

断开该对象中的所有信号*receiver*的*method*。

当涉及的任何一个对象被销毁时，信号槽连接就会被删除。

### `[static]`bool QObject::disconnect(const [QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*connection*)

断开连接。

如果*connection*无效或已断开连接，不执行任何操作并返回 false。

**也可以看看**[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)()。

### `[static]`template < typename PointerToMemberFunction> bool QObject::disconnect(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **sender*, PointerToMemberFunction *signal*, const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **receiver*, PointerToMemberFunction *method*)

该函数重载disconnect()。

断开连接*signal*在对象中*sender*从*method*在对象中*receiver*。`true`如果连接成功断开则返回；否则返回`false`.

当涉及的任何一个对象被销毁时，信号槽连接就会被删除。

connect() 通常以三种方式使用，如以下示例所示。

1. 断开与对象信号连接的所有连接：

   ```
   disconnect(myObject, nullptr, nullptr, nullptr);
   ```

2. 断开连接到特定信号的所有连接：

   ```
   disconnect(myObject, &MyObject::mySignal(), nullptr, nullptr);
   ```

3. 断开特定接收器的连接：

   ```
   disconnect(myObject, nullptr, myReceiver, nullptr);
   ```

4. 断开从一个特定信号到特定插槽的连接：

   ```
   QObject::disconnect(lineEdit, &QLineEdit::textChanged,
                    label,  &QLabel::setText);
   ```

`nullptr`可以用作通配符，分别表示“任何信号”、“任何接收对象”或“接收对象中的任何槽”。

这*sender*也许永远不会`nullptr`。（您无法在一次调用中断开来自多个对象的信号。）

如果*signal*是`nullptr`，它断开连接*receiver*和*method*来自任何信号。如果没有，则仅断开指定的信号。

如果*receiver*是的`nullptr`，它会断开连接到的任何东西*signal*。如果不是，则仅断开指定接收器中的插槽。与非空断开连接（）*receiver*还断开与连接的插槽功能*receiver*作为他们的上下文对象。

如果*method*是的`nullptr`，它会断开所有连接到的连接*receiver*。如果没有，则仅指定插槽*method*将被断开连接，并且所有其他插槽将保持不变。这*method*必须是`nullptr`如果*receiver*被遗漏，因此您无法断开所有对象上特定命名的插槽。

**注意：**无法使用此重载来断开连接到函子或 lambda 表达式的信号。那是因为无法对它们进行比较。相反，使用需要 a 的重载[QMetaObject::Connection](https://doc-qt-io.translate.goog/qt-6/qmetaobject-connection.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)

**注：**该函数是[thread-safe](https://doc-qt-io.translate.goog/qt-6/threads-reentrancy.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)()。

### `[virtual protected]`void QObject::disconnectNotify(const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*signal*)

当某些东西与网络断开连接时，将调用此虚函数*signal*在这个对象中。

看[connectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connectNotify)() 作为如何比较的示例*signal*具有特定的信号。

如果所有信号都与该对象断开连接（例如，信号参数[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)() 是`nullptr`)，disconnectNotify() 只调用一次，并且*signal*将是无效的[QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)（[QMetaMethod::isValid](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isValid)() 返回`false`)。

**警告：**该函数违反了面向对象的模块化原则。但是，它对于优化对昂贵资源的访问可能很有用。

**警告：**该函数是从执行断开连接的线程调用的，该线程可能与该对象所在的线程是不同的线程。该函数也可以用[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)内部互斥体已锁定。因此，不允许重新输入任何内容[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)功能，包括[isSignalConnected](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isSignalConnected)()，来自您的重新实现。如果您在重新实现中锁定互斥锁，请确保您不会调用[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)函数的互斥体保存在其他地方，否则会导致死锁。

**也可以看看**[disconnect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnect)（） 和[connectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connectNotify)()。

### void QObject::dumpObjectInfo() const

将此对象的有关信号连接等的信息转储到调试输出。

**注意：**在 Qt 5.9 之前，该函数不是 const。

**也可以看看**[dumpObjectTree](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dumpObjectTree)()。

### void QObject::dumpObjectTree() const

将子树转储到调试输出。

**注意：**在 Qt 5.9 之前，该函数不是 const。

**也可以看看**[dumpObjectInfo](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dumpObjectInfo)()。

### [QList](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)<[QByteArray](https://doc-qt-io.translate.goog/qt-6/qbytearray.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)> QObject::dynamicPropertyNames() const

返回使用动态添加到对象的所有属性的名称[setProperty](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setProperty)()。

### `[virtual]`bool QObject::event([QEvent](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) **e*)

该虚函数接收对象的事件，如果事件发生则应返回 true*e*被识别并处理。

可以重新实现 event() 函数来自定义对象的行为。

确保为所有未处理的事件调用父事件类实现。

例子：

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

**也可以看看**[installEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#installEventFilter)(),[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)(),[QCoreApplication::sendEvent](https://doc-qt-io.translate.goog/qt-6/qcoreapplication.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#sendEvent)（）， 和[QCoreApplication::postEvent](https://doc-qt-io.translate.goog/qt-6/qcoreapplication.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#postEvent)()。

### `[virtual]`bool QObject::eventFilter([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **watched*, [QEvent](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) **event*)

如果此对象已作为事件过滤器安装，则过滤事件*watched*目的。

在您重新实现此函数时，如果您想过滤*event*out，即停止进一步处理，返回true；否则返回 false。

例子：

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
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "Ate key press" << keyEvent->key();
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

请注意，在上面的示例中，未处理的事件被传递给基类的 eventFilter() 函数，因为基类可能出于其自身的内部目的重新实现了 eventFilter()。

一些事件，例如[QEvent::ShortcutOverride](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)必须明确接受（通过调用[accept](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#accept)() ）以防止传播。

**警告：**如果在此函数中删除接收者对象，请务必返回 true。否则，Qt 会将事件转发给已删除的对象，程序可能会崩溃。

**也可以看看**[installEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#installEventFilter)()。

### template < typename T> T QObject::findChild(const [QString](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*name* = QString(), [Qt::FindChildOptions](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

返回该对象的子对象，该对象可以转换为类型 T 并称为*name*，或者`nullptr`如果不存在这样的对象。省略*name*参数导致所有对象名称匹配。搜索是递归执行的，除非*options*指定选项 FindDirectChildrenOnly。

如果有多个子代与搜索匹配，则返回最直接的祖先。如果有多个直接祖先，则未定义将返回哪一个。在这种情况下，[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)应使用()。

此示例返回name`QPushButton`的子级，即使该按钮不是父级的直接子级：`parentWidget``"button1"`

```
QPushButton *button = parentWidget->findChild<QPushButton *>("button1");
```

此示例返回`QListWidget`的子级`parentWidget`：

```
QListWidget *list = parentWidget->findChild<QListWidget *>();
```

`QPushButton`此示例返回名为的`parentWidget`（其直接父级）的子级`"button1"`：

```
QPushButton *button = parentWidget->findChild<QPushButton *>("button1", Qt::FindDirectChildrenOnly);
```

此示例返回 的`QListWidget`子级`parentWidget`，即其直接父级：

```
QListWidget *list = parentWidget->findChild<QListWidget *>(QString(), Qt::FindDirectChildrenOnly);
```

**也可以看看**[findChildren](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChildren)()。

### template < typename T> [QList](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)< T> QObject::findChildren(const [QString](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*name*, [Qt::FindChildOptions](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

返回具有给定值的该对象的所有子对象*name*可以转换为 T 类型，如果没有这样的对象，则转换为空列表。空值*name*参数导致所有对象都匹配，空对象仅匹配那些[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)是空的。搜索是递归执行的，除非*options*指定选项 FindDirectChildrenOnly。

以下示例显示如何查找`QWidget`指定`parentWidget`name的 child 列表`widgetname`：

```
QList<QWidget *> widgets = parentWidget.findChildren<QWidget *>("widgetname");
```

此示例返回`QPushButton`的所有子代`parentWidget`：

```
QList<QPushButton *> allPButtons = parentWidget.findChildren<QPushButton *>();
```

此示例返回 的所有`QPushButton`直接子代`parentWidget`：

```
QList<QPushButton *> childButtons = parentWidget.findChildren<QPushButton *>(Qt::FindDirectChildrenOnly);
```

**也可以看看**[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)()。

### `[since 6.3]`template < typename T> [QList](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)< T> QObject::findChildren([Qt::FindChildOptions](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

这是一个过载功能。

返回此对象的所有可转换为类型 T 的子对象，如果没有此类对象，则返回空列表。搜索是递归执行的，除非*options*指定选项 FindDirectChildrenOnly。

该功能是在 Qt 6.3 中引入的。

**也可以看看**[findChild](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#findChild)()。

### template < typename T> [QList](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)< T> QObject::findChildren(const [QRegularExpression](https://doc-qt-io.translate.goog/qt-6/qregularexpression.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*re*, [Qt::FindChildOptions](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#FindChildOption-enum) *options* = Qt::FindChildrenRecursively) const

该函数重载了findChildren()。

返回此对象的子对象，这些子对象可以转换为类型 T 并且其名称与正则表达式匹配*re*，如果不存在此类对象，则为空列表。搜索是递归执行的，除非*options*指定选项 FindDirectChildrenOnly。

### bool QObject::inherits(const char **className*) const

返回`true`此对象是否是继承的类的实例*className*或一个[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)继承的子类*className*; 否则返回`false`.

类被认为继承了自身。

例子：

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

如果您需要确定一个对象是否是特定类的实例以进行强制转换，请考虑使用[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast)改为 <Type *>(object)。

**也可以看看**[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)（） 和[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast)()。

### void QObject::installEventFilter([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **filterObj*)

安装事件过滤器*filterObj*在这个物体上。例如：

```
monitoredObj->installEventFilter(filterObj);
```

事件过滤器是一个接收发送到该对象的所有事件的对象。过滤器可以停止事件或将其转发到该对象。事件过滤器*filterObj*通过其接收事件[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)（） 功能。这[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)如果事件应该被过滤（即停止），() 函数必须返回 true；否则它必须返回 false。

如果单个对象上安装了多个事件过滤器，则首先激活最后安装的过滤器。

这是一个`KeyPressEater`类，它吃掉其监视对象的按键：

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
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
```

以下是如何将其安装在两个小部件上：

```
KeyPressEater *keyPressEater = new KeyPressEater(this);
QPushButton *pushButton = new QPushButton(this);
QListView *listView = new QListView(this);

pushButton->installEventFilter(keyPressEater);
listView->installEventFilter(keyPressEater);
```

这[QShortcut](https://doc-qt-io.translate.goog/qt-6/qshortcut.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)例如，class 使用此技术来拦截快捷键按下。

**警告：**如果您删除了接收器对象[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)()函数，一定要返回true。如果返回 false，Qt 会将事件发送到已删除的对象，程序将崩溃。

注意，过滤对象必须与该对象在同一个线程中。如果*filterObj*在不同的线程中，该函数不执行任何操作。如果其中之一*filterObj*或者在调用此函数后该对象被移动到不同的线程，事件过滤器将不会被调用，直到两个对象再次具有相同的线程亲和力（它不会被*删除*）。

**也可以看看**[removeEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#removeEventFilter)(),[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)（）， 和[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)()。

### `[since 6.4]`bool QObject::isQuickItemType() const

`true`如果该对象是一个则返回[QQuickItem](https://doc-qt-io.translate.goog/qt-6/qquickitem.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp); 否则返回`false`.

调用此函数与调用 等效`inherits("QQuickItem")`，只是速度要快得多。

该功能是在 Qt 6.4 中引入的。

### `[protected]`bool QObject::isSignalConnected(const [QMetaMethod](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*signal*) const

返回`true`如果*signal*连接到至少一个接收器，否则返回`false`。

*signal*必须是该对象的信号成员，否则行为未定义。

```
static const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&MyObject::valueChanged);
if (isSignalConnected(valueChangedSignal)) {
    QByteArray data;
    data = get_the_value();       // expensive operation
    emit valueChanged(data);
}
```

正如上面的代码片段所示，您可以使用此函数来避免昂贵的初始化或发出无人监听的信号。但是，在多线程应用程序中，在此函数返回之后和发出信号之前，连接可能会发生变化。

**警告：**该函数违反了面向对象的模块化原则。特别是，不得从重写中调用此函数[connectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connectNotify)（） 或者[disconnectNotify](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disconnectNotify)()，因为它们可能会从任何线程调用。

### bool QObject::isWidgetType() const

返回`true`该对象是否是一个小部件；否则返回`false`.

调用此函数与调用 等效`inherits("QWidget")`，只是速度要快得多。

### bool QObject::isWindowType() const

返回`true`对象是否为窗口；否则返回`false`.

调用此函数与调用 等效`inherits("QWindow")`，只是速度要快得多。

### void QObject::killTimer(int *id*)

使用计时器标识符杀死计时器，*id*。

定时器标识符由以下命令返回[startTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#startTimer)() 当定时器事件启动时。

**也可以看看**[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)（） 和[startTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#startTimer)()。

### `[virtual]`const [QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) *QObject::metaObject() const

返回指向该对象的元对象的指针。

元对象包含有关继承的类的信息[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)，例如类名、超类名、属性、信号和槽。每一个[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)子类包含[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)宏将有一个元对象。

信号/槽连接机制和属性系统需要元对象信息。这[inherits](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#inherits)() 函数也利用了元对象。

如果您没有指向实际对象实例的指针，但仍想访问类的元对象，则可以使用[staticMetaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#staticMetaObject-var)。

例子：

```
QObject *obj = new QPushButton;
obj->metaObject()->className();             // returns "QPushButton"

QPushButton::staticMetaObject.className();  // returns "QPushButton"
```

**也可以看看**[staticMetaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#staticMetaObject-var)。

### void QObject::moveToThread([QThread](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) **targetThread*)

更改该对象及其子对象的线程关联性。如果该对象有父对象，则无法移动该对象。事件处理将在*targetThread*。

要将对象移动到主线程，请使用[QApplication::instance](https://doc-qt-io.translate.goog/qt-6/qcoreapplication.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#instance)() 检索指向当前应用程序的指针，然后使用[QApplication::thread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#thread)() 检索应用程序所在的线程。例如：

```
myObject->moveToThread(QApplication::instance()->thread());
```

如果*targetThread*是`nullptr`，该对象及其子对象的所有事件处理都会停止，因为它们不再与任何线程关联。

请注意，该对象的所有活动计时器都将被重置。计时器首先在当前线程中停止，然后在下一个线程中重新启动（以相同的间隔）。*targetThread*。因此，在线程之间不断移动对象可能会无限期地推迟计时器事件。

A[QEvent::ThreadChange](https://doc-qt-io.translate.goog/qt-6/qevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Type-enum)事件在线程关联性更改之前发送到此对象。您可以处理此事件以执行任何特殊处理。请注意，发布到该对象的任何新事件都将在*targetThread*，前提是它不是`nullptr`：当它是时`nullptr`，该对象或其子对象不会发生任何事件处理，因为它们不再与任何线程关联。

**警告：**该函数不是*线程*安全的；当前线程必须与当前线程关联性相同。换句话说，该函数只能将对象从当前线程“推”到另一个线程，而不能将对象从任意线程“拉”到当前线程。然而，这一规则有一个例外：没有线程关联的对象可以“拉”到当前线程。

**也可以看看**[thread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#thread)()。

### `[private signal]`void QObject::objectNameChanged(const [QString](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*objectName*)

该信号在对象名称更改后发出。新对象名称传递为*objectName*。

**注意：**这是一个私人信号。它可以用于信号连接，但不能由用户发出。

**注意：**属性的通知程序信号[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)。

**也可以看看**[QObject::objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)。

### [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) *QObject::parent() const

返回指向父对象的指针。

**也可以看看**[setParent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setParent)（） 和[children](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#children)()。

### [QVariant](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::property(const char **name*) const

返回对象的值*name*财产。

如果不存在这样的属性，则返回的变体无效。

有关所有可用属性的信息通过[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)（） 和[dynamicPropertyNames](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dynamicPropertyNames)()。

**也可以看看**[setProperty](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#setProperty)(),[QVariant::isValid](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isValid)(),[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)（）， 和[dynamicPropertyNames](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dynamicPropertyNames)()。

### `[protected]`int QObject::receivers(const char **signal*) const

返回连接到的接收器的数量*signal*。

由于时隙和信号都可以用作信号的接收器，并且相同的连接可以进行多次，因此接收器的数量与该信号建立的连接的数量相同。

调用该函数时，可以使用`SIGNAL()`宏来传递特定信号：

```
if (receivers(SIGNAL(valueChanged(QByteArray))) > 0) {
    QByteArray data;
    get_the_value(&data);       // expensive operation
    emit valueChanged(data);
}
```

**警告：**该函数违反了面向对象的模块化原则。但是，当您仅在某些东西连接到信号时才需要执行昂贵的初始化时，它可能很有用。

**也可以看看**[isSignalConnected](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#isSignalConnected)()。

### void QObject::removeEventFilter([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **obj*)

删除事件过滤器对象*obj*来自这个对象。如果尚未安装此类事件过滤器，则该请求将被忽略。

当该对象被销毁时，该对象的所有事件过滤器都会自动删除。

即使在事件过滤器激活期间（即从[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)（） 功能）。

**也可以看看**[installEventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#installEventFilter)(),[eventFilter](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#eventFilter)（）， 和[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)()。

### `[protected]`[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) *QObject::sender() const

如果在由信号激活的槽中调用，则返回指向发送信号的对象的指针；否则返回`nullptr`。该指针仅在从该对象的线程上下文调用该函数的槽执行期间有效。

如果发送者被销毁，或者槽与发送者的信号断开连接，则该函数返回的指针将变得无效。

**警告：**该函数违反了面向对象的模块化原则。但是，当许多信号连接到单个插槽时，访问发送器可能会很有用。

**警告：**如上所述，当通过 a 调用该槽时，该函数的返回值无效[Qt::DirectConnection](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum)来自与该对象线程不同的线程。请勿在此类场景中使用此功能。

**也可以看看**[senderSignalIndex](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#senderSignalIndex)()。

### `[protected]`int QObject::senderSignalIndex() const

返回调用当前执行槽的信号的元方法索引，该信号是由返回的类的成员[sender](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#sender)()。如果在由信号激活的槽之外调用，则返回 -1。

对于具有默认参数的信号，此函数将始终返回包含所有参数的索引，无论使用哪个参数[connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)()。例如，信号`destroyed(QObject *obj = \nullptr)`将有两个不同的索引（带参数和不带参数），但此函数将始终返回带参数的索引。当使用不同参数重载信号时，这并不适用。

**警告：**该函数违反了面向对象的模块化原则。但是，当许多信号连接到单个插槽时，访问信号索引可能会很有用。

**警告：**当通过 a 调用该槽时，该函数的返回值无效[Qt::DirectConnection](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#ConnectionType-enum)来自与该对象线程不同的线程。请勿在此类场景中使用此功能。

**也可以看看**[sender](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#sender)(),[QMetaObject::indexOfSignal](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#indexOfSignal)（）， 和[QMetaObject::method](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#method)()。

### void QObject::setObjectName(const [QString](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*name*)

将对象的名称设置为*name*。

**注意：**属性的 Setter 函数[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)。

**也可以看看**[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)()。

### `[since 6.4]`void QObject::setObjectName([QAnyStringView](https://doc-qt-io.translate.goog/qt-6/qanystringview.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) *name*)

这是一个过载功能。

**注意：**属性的 Setter 函数[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)。

该功能是在 Qt 6.4 中引入的。

### void QObject::setParent([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **parent*)

使该对象成为以下对象的子对象*parent*。

**也可以看看**[parent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#parent)（） 和[children](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#children)()。

### bool QObject::setProperty(const char **name*, const [QVariant](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) &*value*)

设置对象的值*name*财产给*value*。

如果该属性是在类中定义的[Q_PROPERTY](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_PROPERTY)那么成功时返回 true，否则返回 false。如果未使用定义该属性[Q_PROPERTY](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_PROPERTY)，因此未在元对象中列出，它被添加为动态属性并返回 false。

有关所有可用属性的信息通过[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)（） 和[dynamicPropertyNames](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dynamicPropertyNames)()。

可以使用再次查询动态属性[property](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#property)() 并可以通过将属性值设置为无效来删除[QVariant](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。更改动态属性的值会导致[QDynamicPropertyChangeEvent](https://doc-qt-io.translate.goog/qt-6/qdynamicpropertychangeevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)发送到对象。

**注意：**以“_q_”开头的动态属性保留用于内部目的。

**也可以看看**[property](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#property)(),[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)(),[dynamicPropertyNames](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#dynamicPropertyNames)（）， 和[QMetaProperty::write](https://doc-qt-io.translate.goog/qt-6/qmetaproperty.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#write)()。

### bool QObject::signalsBlocked() const

`true`如果信号被阻塞则返回；否则返回`false`.

默认情况下，信号不会被阻止。

**也可以看看**[blockSignals](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#blockSignals)（） 和[QSignalBlocker](https://doc-qt-io.translate.goog/qt-6/qsignalblocker.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### int QObject::startTimer(int *interval*, [Qt::TimerType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#TimerType-enum) *timerType* = Qt::CoarseTimer)

启动计时器并返回计时器标识符，如果无法启动计时器则返回零。

计时器事件将每隔*interval*毫秒直到[killTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#killTimer)（） 叫做。如果*interval*为 0，则每当没有更多的窗口系统事件需要处理时，定时器事件就会发生一次。

虚拟的[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)() 函数被调用[QTimerEvent](https://doc-qt-io.translate.goog/qt-6/qtimerevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)定时器事件发生时的事件参数类。重新实现此函数以获取计时器事件。

如果多个定时器正在运行，[QTimerEvent::timerId](https://doc-qt-io.translate.goog/qt-6/qtimerevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerId)() 可用于找出哪个计时器被激活。

例子：

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
    qDebug() << "Timer ID:" << event->timerId();
}
```

注意[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)的准确性取决于底层操作系统和硬件。这*timerType*参数允许您自定义计时器的精度。看[Qt::TimerType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#TimerType-enum)有关不同计时器类型的信息。大多数平台支持20毫秒的精度；有些提供更多。如果 Qt 无法交付所请求数量的计时器事件，它将默默地丢弃一些事件。

这[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)类提供了带有单次定时器和定时器信号而不是事件的高级编程接口。还有一个[QBasicTimer](https://doc-qt-io.translate.goog/qt-6/qbasictimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)比这个更轻量级的类[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)并且比直接使用计时器 ID 更简洁。

**也可以看看**[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)(),[killTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#killTimer)（）， 和[QTimer::singleShot](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#singleShot)()。

### int QObject::startTimer(std::chrono::milliseconds *time*, [Qt::TimerType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#TimerType-enum) *timerType* = Qt::CoarseTimer)

这是一个过载功能。

启动计时器并返回计时器标识符，如果无法启动计时器则返回零。

计时器事件将每隔*time*间隔直到[killTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#killTimer)（） 叫做。如果*time*等于`std::chrono::duration::zero()`，那么每当没有更多的窗口系统事件需要处理时，计时器事件就会发生一次。

虚拟的[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)() 函数被调用[QTimerEvent](https://doc-qt-io.translate.goog/qt-6/qtimerevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)定时器事件发生时的事件参数类。重新实现此函数以获取计时器事件。

如果多个定时器正在运行，[QTimerEvent::timerId](https://doc-qt-io.translate.goog/qt-6/qtimerevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerId)() 可用于找出哪个计时器被激活。

例子：

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
    qDebug() << "Timer ID:" << event->timerId();
}
```

注意[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)的准确性取决于底层操作系统和硬件。这*timerType*参数允许您自定义计时器的精度。看[Qt::TimerType](https://doc-qt-io.translate.goog/qt-6/qt.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#TimerType-enum)有关不同计时器类型的信息。大多数平台支持20毫秒的精度；有些提供更多。如果 Qt 无法交付所请求数量的计时器事件，它将默默地丢弃一些事件。

这[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)类提供了带有单次定时器和定时器信号而不是事件的高级编程接口。还有一个[QBasicTimer](https://doc-qt-io.translate.goog/qt-6/qbasictimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)比这个更轻量级的类[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)并且比直接使用计时器 ID 更简洁。

**也可以看看**[timerEvent](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#timerEvent)(),[killTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#killTimer)（）， 和[QTimer::singleShot](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#singleShot)()。

### [QThread](https://doc-qt-io.translate.goog/qt-6/qthread.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) *QObject::thread() const

返回对象所在的线程。

**也可以看看**[moveToThread](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#moveToThread)()。

### `[virtual protected]`void QObject::timerEvent([QTimerEvent](https://doc-qt-io.translate.goog/qt-6/qtimerevent.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) **event*)

该事件处理程序可以在子类中重新实现，以接收对象的计时器事件。

[QTimer](https://doc-qt-io.translate.goog/qt-6/qtimer.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)为计时器功能提供更高级别的接口，以及有关计时器的更多一般信息。定时器事件被传递到*event*范围。

**也可以看看**[startTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#startTimer)(),[killTimer](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#killTimer)（）， 和[event](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#event)()。

### `[static]`[QString](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::tr(const char **sourceText*, const char **disambiguation* = nullptr, int *n* = -1)

返回翻译版本*sourceText*，可选地基于*disambiguation*字符串和值*n*对于包含复数的字符串；否则返回[QString::fromUtf8](https://doc-qt-io.translate.goog/qt-6/qstring.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#fromUtf8)（*sourceText*) 如果没有合适的翻译字符串可用。

例子：

```
void SpreadSheet::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    ...
```

如果一样的话*sourceText*用于同一上下文中的不同角色，可以传入一个附加的标识字符串*disambiguation*（`nullptr`默认情况下）。在 Qt 4.4 及更早版本中，这是向翻译人员传递注释的首选方式。

例子：

```
MyWindow::MyWindow()
{
    QLabel *senderLabel = new QLabel(tr("Name:"));
    QLabel *recipientLabel = new QLabel(tr("Name:", "recipient"));
    ...
```

看[Writing Source Code for Translation](https://doc-qt-io.translate.goog/qt-6/i18n-source-translation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)有关 Qt 翻译机制的一般详细说明，以及[Disambiguate Identical Text](https://doc-qt-io.translate.goog/qt-6/i18n-source-translation.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#disambiguate-identical-text)有关消歧信息的部分。

**警告：**仅当在调用此方法*之前*安装了所有转换器时，此方法才是可重入的。不支持在执行翻译时安装或删除翻译器。这样做可能会导致崩溃或其他不良行为。

**也可以看看**[QCoreApplication::translate](https://doc-qt-io.translate.goog/qt-6/qcoreapplication.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#translate)（） 和[Internationalization with Qt](https://doc-qt-io.translate.goog/qt-6/internationalization.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

## 成员变量文档

### const [QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp) QObject::staticMetaObject

该变量存储类的元对象。

元对象包含有关继承的类的信息[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)，例如类名、超类名、属性、信号和槽。每个包含以下内容的类[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)宏还将有一个元对象。

信号/槽连接机制和属性系统需要元对象信息。这[inherits](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#inherits)() 函数也利用了元对象。

如果你有一个指向对象的指针，你可以使用[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)() 检索与该对象关联的元对象。

例子：

```
QPushButton::staticMetaObject.className();  // returns "QPushButton"

QObject *obj = new QPushButton;
obj->metaObject()->className();             // returns "QPushButton"
```

**也可以看看**[metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)()。

## 相关非成员

### template < typename T> T qobject_cast([QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **object*)

### template < typename T> T qobject_cast(const [QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#QObject) **object*)

返回给定的*object*如果对象属于 T 类型（或子类），则强制转换为 T 类型；否则返回`nullptr`. 如果*object*那么`nullptr`它也会回归`nullptr`。

类 T 必须继承（直接或间接）[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)并与[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)宏。

类被认为继承了自身。

例子：

```
QObject *obj = new QTimer;          // QTimer inherits QObject

QTimer *timer = qobject_cast<QTimer *>(obj);
// timer == (QObject *)obj

QAbstractButton *button = qobject_cast<QAbstractButton *>(obj);
// button == nullptr
```

这[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast)() 函数的行为与标准 C++ 类似`dynamic_cast()`，优点是不需要 RTTI 支持并且可以跨动态库边界工作。

[qobject_cast](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#qobject_cast)()也可以与接口结合使用；看到[Plug & Paint](https://doc-qt-io.translate.goog/qt-6/qtwidgets-tools-plugandpaint-app-example.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)示例以了解详细信息。

**警告：**如果 T 没有用[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)宏，该函数的返回值未定义。

**也可以看看**[QObject::inherits](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#inherits)()。

### QObjectList

同义词[QList](https://doc-qt-io.translate.goog/qt-6/qlist.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)<[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)*>。

## 宏文档

### QT_NO_NARROWING_CONVERSIONS_IN_CONNECT

当使用基于 PMF 的语法连接信号和槽时，定义此宏将禁用信号携带的参数与槽接受的参数之间的缩小和浮点到整数转换。

**也可以看看**[QObject::connect](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#connect)。

### Q_CLASSINFO(*Name*, *Value*)

该宏将额外信息与类相关联，可以使用[QObject::metaObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#metaObject)()。Qt 仅在以下情况中有限地使用了此功能[Qt D-Bus](https://doc-qt-io.translate.goog/qt-6/qtdbus-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)和[Qt QML](https://doc-qt-io.translate.goog/qt-6/qtqml-index.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)模块。

额外信息采用以下形式*Name*字符串和一个*Value*文字字符串。

例子：

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

**也可以看看**[QMetaObject::classInfo](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#classInfo)(),[Using Qt D-Bus Adaptors](https://doc-qt-io.translate.goog/qt-6/usingadaptors.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 和[Extending QML](https://doc-qt-io.translate.goog/qt-6/qtquick-codesamples.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#extending-qml)。

### Q_EMIT

当您想要将`emit`Qt Signals and Slots 与[3rd party signal/slot mechanism](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#3rd-party-signals-and-slots)。

宏通常在与文件中的变量`no_keywords`一起指定时使用，但即使未*指定*也可以使用。`CONFIG``.pro``no_keywords`

### Q_ENUM(...)

该宏向元对象系统注册一个枚举类型。它必须放在具有以下属性的类中的枚举声明之后[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT),[Q_GADGET](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET)或者[Q_GADGET_EXPORT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET_EXPORT)宏。对于命名空间使用[Q_ENUM_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM_NS)（） 反而。

例如：

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

使用 Q_ENUM 声明的枚举有其[QMetaEnum](https://doc-qt-io.translate.goog/qt-6/qmetaenum.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)已在附件中注册[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。您还可以使用[QMetaEnum::fromType](https://doc-qt-io.translate.goog/qt-6/qmetaenum.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#fromType)() 得到[QMetaEnum](https://doc-qt-io.translate.goog/qt-6/qmetaenum.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

已注册的枚举也会自动注册到 Qt 元类型系统，从而使它们为人所知[QMetaType](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)无需使用[Q_DECLARE_METATYPE](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DECLARE_METATYPE)()。这将启用有用的功能；例如，如果用于[QVariant](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)，您可以将它们转换为字符串。同样，将它们传递给[QDebug](https://doc-qt-io.translate.goog/qt-6/qdebug.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)会打印出他们的名字。

`int`请注意，枚举值在元对象系统中以带符号的形式存储。通过元对象系统访问枚举时，使用有效值范围之外的值注册枚举`int`将导致溢出和潜在的未定义行为。例如，QML 确实通过元对象系统访问已注册的枚举。

**也可以看看**[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_ENUM_NS(...)

该宏向元对象系统注册一个枚举类型。它必须放置在具有以下名称的命名空间中的枚举声明之后[Q_NAMESPACE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE)宏。它是一样的[Q_ENUM](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM)但在命名空间中。

使用 Q_ENUM_NS 声明的枚举有其[QMetaEnum](https://doc-qt-io.translate.goog/qt-6/qmetaenum.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)已在附件中注册[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。您还可以使用[QMetaEnum::fromType](https://doc-qt-io.translate.goog/qt-6/qmetaenum.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#fromType)() 得到[QMetaEnum](https://doc-qt-io.translate.goog/qt-6/qmetaenum.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

已注册的枚举也会自动注册到 Qt 元类型系统，从而使它们为人所知[QMetaType](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)无需使用[Q_DECLARE_METATYPE](https://doc-qt-io.translate.goog/qt-6/qmetatype.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DECLARE_METATYPE)()。这将启用有用的功能；例如，如果用于[QVariant](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)，您可以将它们转换为字符串。同样，将它们传递给[QDebug](https://doc-qt-io.translate.goog/qt-6/qdebug.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)会打印出他们的名字。

`int`请注意，枚举值在元对象系统中以带符号的形式存储。通过元对象系统访问枚举时，使用有效值范围之外的值注册枚举`int`将导致溢出和潜在的未定义行为。例如，QML 确实通过元对象系统访问已注册的枚举。

**也可以看看**[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_FLAG(...)

该宏注册一个[flags type](https://doc-qt-io.translate.goog/qt-6/qflags.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)与元对象系统。它通常用在类定义中来声明给定枚举的值可以用作标志并使用按位 OR 运算符进行组合。对于命名空间使用[Q_FLAG_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG_NS)（） 反而。

宏必须放置在枚举声明之后。标志类型的声明是使用[Q_DECLARE_FLAGS](https://doc-qt-io.translate.goog/qt-6/qflags.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DECLARE_FLAGS)() 宏。

例如，在[QItemSelectionModel](https://doc-qt-io.translate.goog/qt-6/qitemselectionmodel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 这[SelectionFlags](https://doc-qt-io.translate.goog/qt-6/qitemselectionmodel.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#SelectionFlag-enum)标志通过以下方式声明：

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

**注意：** Q_FLAG 宏负责向元对象系统注册各个标志值，因此无需使用[Q_ENUM](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM)() 除了这个宏之外。

**也可以看看**[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_FLAG_NS(...)

该宏注册一个[flags type](https://doc-qt-io.translate.goog/qt-6/qflags.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)与元对象系统。它用于具有以下名称的命名空间[Q_NAMESPACE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE)宏，声明给定枚举的值可以用作标志并使用按位 OR 运算符进行组合。它是一样的[Q_FLAG](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG)但在命名空间中。

宏必须放置在枚举声明之后。

**注意：** Q_FLAG_NS 宏负责向元对象系统注册各个标志值，因此没有必要使用[Q_ENUM_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM_NS)() 除了这个宏之外。

**也可以看看**[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_GADGET

Q_GADGET 宏是一个更轻量级的版本[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)不继承自的类的宏[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)但仍然想使用一些提供的反射功能[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。就像[Q_OBJECT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_OBJECT)宏，它必须出现在类定义的私有部分。

Q_GADGET 可以有[Q_ENUM](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM),[Q_PROPERTY](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_PROPERTY)和[Q_INVOKABLE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_INVOKABLE)，但它们不能有信号或槽。

Q_GADGET 使类成员`staticMetaObject`可用。`staticMetaObject`属于类型[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)并提供对声明的枚举的访问[Q_ENUM](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM)。

**也可以看看**[Q_GADGET_EXPORT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET_EXPORT)。

### `[since 6.3]`Q_GADGET_EXPORT(*EXPORT_MACRO*)

Q_GADGET_EXPORT 宏的工作方式与[Q_GADGET](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET)宏。然而，`staticMetaObject`可用的变量（参见[Q_GADGET](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET)）与提供的一起声明*EXPORT_MACRO*预选赛。如果需要从动态库导出对象，但封闭类作为一个整体不应该这样做（例如，因为它主要由内联函数组成），那么这很有用。

例如：

```
class Point {
    Q_GADGET_EXPORT(EXPORT_MACRO)
    Q_PROPERTY(int x MEMBER x)
    Q_PROPERTY(int y MEMBER y)
    ~~~
```

该宏是在 Qt 6.3 中引入的。

**也可以看看**[Q_GADGET](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET)和[Creating Shared Libraries](https://doc-qt-io.translate.goog/qt-6/sharedlibrary.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_INTERFACES(...)

该宏告诉 Qt 该类实现了哪些接口。这在实现插件时使用。

例子：

```
class BasicToolsPlugin : public QObject,
                         public BrushInterface,
                         public ShapeInterface,
                         public FilterInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.PlugAndPaint.BrushInterface" FILE "basictools.json")
    Q_INTERFACES(BrushInterface ShapeInterface FilterInterface)

public:
    ...
};
```

请参阅[Plug & Paint Basic Tools](https://doc-qt-io.translate.goog/qt-6/qtwidgets-tools-plugandpaint-plugins-basictools-example.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)示例以了解详细信息。

**也可以看看**[Q_DECLARE_INTERFACE](https://doc-qt-io.translate.goog/qt-6/qtplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_DECLARE_INTERFACE)(),[Q_PLUGIN_METADATA](https://doc-qt-io.translate.goog/qt-6/qtplugin.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_PLUGIN_METADATA)（）， 和[How to Create Qt Plugins](https://doc-qt-io.translate.goog/qt-6/plugins-howto.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_INVOKABLE

将此宏应用于成员函数的声明，以允许通过元对象系统调用它们。宏写在返回类型之前，如下例所示：

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

该`invokableMethod()`函数使用 Q_INVOKABLE 进行标记，使其在元对象系统中注册并允许使用以下命令调用它[QMetaObject::invokeMethod](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#invokeMethod)()。由于`normalMethod()`函数不是以这种方式注册的，因此无法使用以下方式调用它[QMetaObject::invokeMethod](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#invokeMethod)()。

如果一个可调用成员函数返回一个指向[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)或一个子类[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)它是从 QML 调用的，适用特殊的所有权规则。看[Data Type Conversion Between QML and C++](https://doc-qt-io.translate.goog/qt-6/qtqml-cppintegration-data.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)了解更多信息。

### `[since 6.0]`Q_MOC_INCLUDE

Q_MOC_INCLUDE 宏可以在类内部或外部使用，并告诉[Meta Object Compiler](https://doc-qt-io.translate.goog/qt-6/moc.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)添加包含。

```
// Put this in your code and the generated code will include this header.
Q_MOC_INCLUDE("myheader.h")
```

如果用作属性或信号/槽参数的类型是前向声明的，这非常有用。

该宏是在 Qt 6.0 中引入的。

### Q_NAMESPACE

Q_NAMESPACE 宏可用于添加[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)命名空间的功能。

Q_NAMESPACE 可以有[Q_CLASSINFO](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_CLASSINFO),[Q_ENUM_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM_NS),[Q_FLAG_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG_NS)，但他们不能有[Q_ENUM](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM),[Q_FLAG](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG),[Q_PROPERTY](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_PROPERTY),[Q_INVOKABLE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_INVOKABLE)、信号或槽。

Q_NAMESPACE 使外部变量`staticMetaObject`可用。`staticMetaObject`属于类型[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)并提供对声明的枚举的访问[Q_ENUM_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_ENUM_NS)/[Q_FLAG_NS](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_FLAG_NS)。

例如：

```
namespace test {
Q_NAMESPACE
...
```

**也可以看看**[Q_NAMESPACE_EXPORT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE_EXPORT)。

### Q_NAMESPACE_EXPORT(*EXPORT_MACRO*)

Q_NAMESPACE_EXPORT 宏可用于添加[QMetaObject](https://doc-qt-io.translate.goog/qt-6/qmetaobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)命名空间的功能。

它的工作原理与[Q_NAMESPACE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE)宏。`staticMetaObject`但是，在命名空间中定义的外部变量是使用提供的声明的*EXPORT_MACRO*预选赛。如果需要从动态库导出对象，这非常有用。

例如：

```
namespace test {
Q_NAMESPACE_EXPORT(EXPORT_MACRO)
...
```

**也可以看看**[Q_NAMESPACE](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_NAMESPACE)和[Creating Shared Libraries](https://doc-qt-io.translate.goog/qt-6/sharedlibrary.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_OBJECT

Q_OBJECT 宏必须出现在声明其自己的信号和槽或使用 Qt 元对象系统提供的其他服务的类定义的私有部分中。

例如：

```
#include <QObject>

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

**注意：**该宏要求该类是以下类的子类[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。使用[Q_GADGET](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET)或者[Q_GADGET_EXPORT](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#Q_GADGET_EXPORT)而不是 Q_OBJECT 来启用元对象系统对非类中枚举的支持[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)子类。

**也可以看看**[Meta-Object System](https://doc-qt-io.translate.goog/qt-6/metaobjects.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp),[Signals and Slots](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)， 和[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_PROPERTY(...)

该宏用于声明继承的类中的属性[QObject](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。属性的行为类似于类数据成员，但它们具有可通过[Meta-Object System](https://doc-qt-io.translate.goog/qt-6/metaobjects.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

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

属性名称、类型和`READ`功能是必需的。类型可以是任何支持的类型[QVariant](https://doc-qt-io.translate.goog/qt-6/qvariant.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)，或者它可以是用户定义的类型。其他项目是可选的，但`WRITE`功能是通用的。这些属性默认为 true `USER`，但默认为 false。

例如：

```
Q_PROPERTY(QString title READ title WRITE setTitle USER true)
```

有关如何使用此宏的更多详细信息及其使用的更详细示例，请参阅有关的讨论[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

**也可以看看**[Qt's Property System](https://doc-qt-io.translate.goog/qt-6/properties.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)。

### Q_REVISION

将此宏应用于成员函数的声明，以使用元对象系统中的修订号来标记它们。宏写在返回类型之前，如下例所示：

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

当使用元对象系统将对象动态公开给另一个 API 时，这非常有用，因为您可以匹配其他 API 的多个版本所期望的版本。考虑以下简化示例：

```
    Window window;
    int expectedRevision = 0;
    const QMetaObject *windowMetaObject = window.metaObject();
    for (int i=0; i < windowMetaObject->methodCount(); i++)
        if (windowMetaObject->method(i).revision() <= expectedRevision)
            exposeMethod(windowMetaObject->method(i));
    for (int i=0; i < windowMetaObject->propertyCount(); i++)
        if (windowMetaObject->property(i).revision() <= expectedRevision)
            exposeProperty(windowMetaObject->property(i));
```

使用与前面的示例相同的 Window 类，只有当预期版本为或更高版本时，newProperty 和 newMethod 才会在此代码中公开`2.1`。

由于如果未加标签，所有方法都被视为修订版，因此 或 的`0`标签无效并被忽略。`Q_REVISION(0)``Q_REVISION(0, 0)`

您可以将一两个整数参数传递给`Q_REVISION`. 如果传递一个参数，则仅表示次要版本。这意味着主要版本未指定。如果传递两个，第一个参数是主版本，第二个参数是次版本。

元对象系统本身不使用此标记。目前这仅被使用[QtQml](https://doc-qt-io.translate.goog/qt-6/qtqml-module.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp)模块。

有关更通用的字符串标签，请参阅[QMetaMethod::tag](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#tag)()

**也可以看看**[QMetaMethod::revision](https://doc-qt-io.translate.goog/qt-6/qmetamethod.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#revision)()。

### Q_SET_OBJECT_NAME(*Object*)

该宏指定*Object*这[objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)“目的”。

是否并不重要*Object*是否是一个指针，宏会自己计算出来。

**也可以看看**[QObject::objectName](https://doc-qt-io.translate.goog/qt-6/qobject.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#objectName-prop)()。

### Q_SIGNAL

这是一个附加宏，允许您将单个函数标记为信号。它非常有用，特别是当您使用不理解 a`signals`或`Q_SIGNALS`groups 的第 3 方源代码解析器时。

当您想要将`signals`Qt 信号和槽与[3rd party signal/slot mechanism](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#3rd-party-signals-and-slots)。

宏通常在与文件中的变量`no_keywords`一起指定时使用，但即使未*指定*也可以使用。`CONFIG``.pro``no_keywords`

### Q_SIGNALS

当您想要将`signals`Qt 信号和槽与[3rd party signal/slot mechanism](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#3rd-party-signals-and-slots)。

宏通常在与文件中的变量`no_keywords`一起指定时使用，但即使未*指定*也可以使用。`CONFIG``.pro``no_keywords`

### Q_SLOT

这是一个附加宏，允许您将单个函数标记为槽。它非常有用，特别是当您使用不理解 a`slots`或`Q_SLOTS`groups 的第 3 方源代码解析器时。

当您想要将`slots`Qt 信号和槽与[3rd party signal/slot mechanism](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#3rd-party-signals-and-slots)。

宏通常在与文件中的变量`no_keywords`一起指定时使用，但即使未*指定*也可以使用。`CONFIG``.pro``no_keywords`

### Q_SLOTS

当您想要将`slots`Qt 信号和槽与[3rd party signal/slot mechanism](https://doc-qt-io.translate.goog/qt-6/signalsandslots.html?_x_tr_sl=auto&_x_tr_tl=zh-CN&_x_tr_hl=zh-CN&_x_tr_pto=wapp#3rd-party-signals-and-slots)。

宏通常在与文件中的变量`no_keywords`一起指定时使用，但即使未*指定*也可以使用。`CONFIG``.pro``no_keywords`