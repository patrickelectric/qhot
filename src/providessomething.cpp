#include "providessomething.h"

#include <QDebug>
#include <QJSEngine>
#include <QQmlEngine>

ProvidesSomething::ProvidesSomething()
{
    connect(&_fileSystemWatcher, &QFileSystemWatcher::fileChanged, this, [this](const QString& path){
        qDebug() << "File changed:" << path;
        emit filePathChanged();
    });
}

QQmlComponent* ProvidesSomething::component(QObject *parent)
{
    QQmlEngine *engine = qmlEngine(parent);
    if(!engine) {
        qDebug() << "No qml engine to load visualization.";
        return nullptr;
    }
    QQmlComponent *component = new QQmlComponent(engine, _url);
    return component;
}

QObject* ProvidesSomething::qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(scriptEngine)

    engine->setObjectOwnership(self(), QQmlEngine::CppOwnership);

    return self();
}

ProvidesSomething* ProvidesSomething::self()
{
    static ProvidesSomething self;
    return &self;
}

ProvidesSomething::~ProvidesSomething() = default;
