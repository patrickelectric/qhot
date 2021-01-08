#pragma once

#include <QtCore/QFileSystemWatcher>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtGui/QColor>
#include <QtQml/QQmlComponent>

class QJSEngine;
class QQmlEngine;

/**
 * @brief Manage the project ProvidesSomething
 *
 */
class ProvidesSomething : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)

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

    /**
     * @brief Set the qml engine
     *
     * @param engine
     */
    void setEngine(QQmlEngine* engine);

    QColor background() const { return _background; }
    void setBackground(const QColor& color) {
        if (color != _background) {
            _background = color;
            emit backgroundChanged();
        }
    }

signals:
    void filePathChanged();
    void backgroundChanged();

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
    QColor _background{"white"};
};
