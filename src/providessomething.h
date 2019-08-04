#pragma once

#include <QFileSystemWatcher>
#include <QQmlComponent>
#include <QObject>
#include <QString>
#include <QUrl>

class QJSEngine;
class QQmlEngine;

/**
 * @brief Manage the project ProvidesSomething
 *
 */
class ProvidesSomething : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Return ProvidesSomething pointer
     *
     * @return ProvidesSomething*
     */
    static ProvidesSomething* self();

    /**
     * @brief Return a pointer of this singleton to the qml register function
     *
     * @param engine
     * @param scriptEngine
     * @return QObject*
     */
    static QObject* qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine);

    /**
     * @brief Returns something
     *
     * @return QString
     */
    QUrl filePath() {
        return _url;
    }

    /**
     * @brief Set the file path
     *
     * @param url
     */
    void setFilePath(const QUrl& url) {
        _url = url;
        _fileSystemWatcher.addPath(url.toLocalFile());
        emit filePathChanged();
    }
    Q_PROPERTY(QUrl filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)

    /**
     * @brief Set the qml engine
     *
     * @param engine
     */
    void setEngine(QQmlEngine* engine);

signals:
    void filePathChanged();

private:
    Q_DISABLE_COPY(ProvidesSomething);

    /**
     * @brief Construct a new Device Manager object
     *
     */
    ProvidesSomething();

    /**
     * @brief Destroy the Provides Something object
     *
     */
    ~ProvidesSomething();

    QFileSystemWatcher _fileSystemWatcher;
    QUrl _url;
    QQmlEngine* m_engine;
};
