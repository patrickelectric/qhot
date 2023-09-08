#pragma once

#include <functional>

#include <QtGlobal>

#include <QCommandLineParser>
#include <QDebug>
#include <QQmlEngine>
#include <QQuickStyle>
#include <QTranslator>

#include "../providessomething.h"

#define APPNAME_FORMAT QStringLiteral("qhot (%1)")

/**
 * @brief Deal with command lines
 *
 */
class CommandLineParser : public QCommandLineParser {
public:
    /**
     * @brief Construct a new Command Line Parser object
     *  The constructor will deal with the arguments
     *
     * @param app
     */
    CommandLineParser(int argc, char *argv[]);

    /**
     * @brief Destroy the Command Line Parser object
     *
     */
    ~CommandLineParser() = default;

    /**
     * @brief Set the QQmlEngine to do the necessary configuration
     *
     * @param qmlengine
     */
    void setEngine(QQmlEngine* engine);

    /**
     * @brief Set the QCoreApplication to do the necessary configuration
     *
     * @param application
     */
    void setApplication(QCoreApplication* application);

private:
    struct OptionStruct {
        QCommandLineOption option;
        std::function<void(const QString&)> function;
    };

    QList<std::function<void()>> _posAppFunctions;

    void printHelp();
    void _parseQHotProfile(const QString& profilePath);
    void _translate(const QString& translationFile);

    QStringList _importPaths;
    QStringList _pluginPaths;

    QTranslator _translator;

    QList<OptionStruct> _optionsStruct {
        {
            {{"help", "h", "?"}, "Give this friendly help message for our confort"},
            [this](const QString&) { printHelp(); exit(0); },
        },
        {
            {"desktop", "Force use of desktop GL (AA_UseDesktopOpenGL)"},
            [](const QString&) { QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL); },
        },
        {
            {"style", "Change style"},
            [this](const QString& argument) { _posAppFunctions.append([argument]{ QQuickStyle::setStyle(argument); }); },
        },
        {
            {"gles", "Force use of GLES (AA_UseOpenGLES)"},
            [](const QString&) { QCoreApplication::setAttribute(Qt::AA_UseOpenGLES); },
        },
        {
            {"software", "Force use of software rendering (Qt::AA_UseSoftwareOpenGL)"},
            [](const QString&) { QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL); },
        },
        {
            {{"import-path", "I"}, "Add list of **import** paths (path:path)", "paths"},
            [this](const QString& argument) { _importPaths = argument.split(':'); },
        },
        {
            {{"plugin-path", "P"}, "Add list of **plugin** paths (path:path)", "paths"},
            [this](const QString& argument) { _pluginPaths = argument.split(':'); },
        },
        {
            {"translation", "Set the translation file (file)", "file"},
            [this](const QString& argument) { _translate(argument); },
        },
        {
            {"profile-path", "Path (including filename) to qhot-profile.json", "file"},
            [this](const QString& argument) { _parseQHotProfile(argument); },
        },
        {
            {"background", "Set the background color", "color"},
            [](const QString& color) { ProvidesSomething::self()->setBackground(color); },
        },
        {
            {"quick-controls-conf", "Path (including filename) to qtquickcontrols2.conf", "file"},
            [](const QString& path) { qputenv("QT_QUICK_CONTROLS_CONF", path.toLocal8Bit()); },
        },
        {
            {"app-name", "Name of the application to set in QGuiApplication::setApplicationName", "name"},
            [this](const QString& argument) { _posAppFunctions.append([argument]{ qApp->setApplicationName(APPNAME_FORMAT.arg(argument)); });},
        },
    };
};
