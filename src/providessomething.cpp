#include "providessomething.h"
#include "urlinterceptor.h"

#include <QtCore/QDebug>
#include <QtCore/QDirIterator>
#include <QtQml/QJSEngine>

#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

namespace  {

void loadDummyDataFiles(QQmlEngine &engine, const QString& directory)
{
    QDir dir{directory + QLatin1String{"/dummydata"}, QStringLiteral("*.qml")};
    const auto qmlFiles = dir.entryList();
    for (auto& qmlFile : qmlFiles) {
        QQmlComponent comp{&engine, dir.filePath(qmlFile)};

        if (comp.isError()) {
            const auto errors = comp.errors();
            for (auto& error : errors)
                qWarning() << error.toString();
        }

        auto* objectInstance = comp.create();
        if (objectInstance) {
            qInfo() << "Loaded dummy data:" << dir.filePath(qmlFile);
            auto propertyName = qmlFile;
            propertyName.truncate(propertyName.length() - 4);
            engine.rootContext()->setContextProperty(propertyName, objectInstance);
            objectInstance ->setParent(&engine);
        }
    }
}

} // anonymous


ProvidesSomething::ProvidesSomething()
{
    connect(UrlInterceptor::self(), &UrlInterceptor::newFile, this, [this](const QUrl& path){
        _fileSystemWatcher.addPath(path.toLocalFile());
    });

    connect(&_fileSystemWatcher, &QFileSystemWatcher::fileChanged, this, [this](const QString& path){
        Q_UNUSED(path)
        m_engine->clearComponentCache();
        emit filePathChanged();
    });
}

void ProvidesSomething::setEngine(QQmlEngine* engine)
{
    m_engine = engine;
}

QObject* ProvidesSomething::qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(scriptEngine)

    engine->setObjectOwnership(self(), QQmlEngine::CppOwnership);
    return self();
}

void ProvidesSomething::setFilePath(const QUrl &url) {
    _url = url;
    QFileInfo fileInfo{url.toLocalFile()};
    loadDummyDataFiles(*m_engine, fileInfo.absolutePath());
    _fileSystemWatcher.addPath(url.toLocalFile());
    emit filePathChanged();
}

ProvidesSomething* ProvidesSomething::self()
{
    static ProvidesSomething self;
    return &self;
}

ProvidesSomething::~ProvidesSomething() = default;
