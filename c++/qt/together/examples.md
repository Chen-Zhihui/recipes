
[toc]

# features

## define a plugin
```c++
PluginPlay.h
PluginPlay.cpp
PluginPlay.json
Activator
```

## insert page to main window
```
auto mainwin = SdkHelper::mainWin();
IWinAppItem item;
```

## login information
```
//example: show logon information
auto logInfo = new QLabel(bar);
auto status = this->statusBar();
status->addWidget(logInfo);
_loginData = SdkHelper::nc()->recentObject<LoginData>(LoginDataKey);
logInfo->setText( _loginData.isLogin() ? "LogON" : "LogOff");

//listen to login/logoff event
auto logon = [this,logInfo](){
    _loginData = SdkHelper::nc()->recentObject<LoginData>(LoginDataKey);
    if( _loginData.login.value())
        logInfo->setText("LogOn");
};

auto logoff = [this,logInfo](){
    _loginData = SdkHelper::nc()->recentObject<LoginData>(LoginDataKey);
    if( !_loginData.login.value())
        logInfo->setText("LogOff");
};

SdkHelper::nc()->addObserverObj<LoginData>(LoginDataKey,
                             this,
                             [this, logon, logoff](const LoginData & obj)
{
     if( obj.isLogin() )
     {
         if( _loginData.isLogin()  )
             logoff();
         logon();
     }
     else
         logoff();
});
```

## send/receive message
```
// example: send and receive msg
{
    MyMsg msg;
    msg.dirtyIt();
    msg.id = "id";
    msg.data = "data";
    SdkHelper::nc()->publishObj(MyMsgKey, msg);

    //example: listen to msg
    SdkHelper::nc()->addObserverObj<MyMsg>(MyMsgKey,
                                 this,
                                 [this](const MyMsg & obj)
    {
        this->browser->clear();
        this->browser->append(obj.toString());
    });
}
```

## call nsite api
```
//example: call MoRS client, fetch all child of user
auto showChildren = bar->addAction("Children");
showChildren->setIcon(QIcon(":/play/image/video.png"));
connect(showChildren, &QAction::triggered, [this]()
{
    browser->clear();
    if( !_loginData.isLogin()) return;

    QString userid = _loginData.userid.value();
    auto ok = [this](const FArray<MObject> & objs){
        QString data = objs.toString();
        this->browser->append(data);
    };
    auto err = [this](int, const QString & msg){
        this->browser->append(msg);
    };

    auto raw = [this](const QByteArray & data){
        this->browser->append(QString(data));
    };
    _client.findChildren(userid, QStringList(), QStringList(), QStringList(),
                         ok, err, raw);
});
```

## jump to another page
```
QDesktopServices::setUrlHandler(Scheme::Template, this ...
QDesktopServices::unsetUrlHandler(Scheme::Space);
PluginPlay::sltOpenUrl(const QUrl & url)
```

```
QUrl url;
url.setScheme(Scheme::Space);
QDesktopServices::openUrl(url);
```

## add action to right botton / icon menu
```
auto service = SdkHelper::registry().getService<SystemIcon>(SystemIcon_IID);
service->addAction(_myact);
```

## show message
```
SdkHelper::showMessage(QString::number(qrand()), "todo:: show me to user");
```


## add action to space page
```
// example: add Space popu up menu tool
auto space = SdkHelper::registry()
        .getService<SpacePluginContainer>(SpacePluginContainer_IID);
QSharedPointer<SpaceShowProperty> spaceTool(new SpaceShowProperty);
_spaceid = spaceTool->id();
space->registerTool(spaceTool);
```
