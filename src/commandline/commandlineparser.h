#pragma once

#include <functional>

#include <QCommandLineParser>
#include <QDebug>
#include <QQmlEngine>
#include <QQuickStyle>
#include <QTranslator>


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
    void setApplication(QCoreApplication* application)
    {
        Q_UNUSED(application)
        QCoreApplication::installTranslator(&_translator);

        for(auto function : _posAppFunctions) {
            function();
        }
    }

private:
    struct OptionStruct {
        QCommandLineOption option;
        std::function<void(const QString&)> function;
    };

    QList<std::function<void()>> _posAppFunctions;

    void printHelp();

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
            {"scaling", "Enable High DPI scaling (AA_EnableHighDpiScaling)"},
            [](const QString&) { QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); },
        },
        {
            {"no-scaling", "Disable High DPI scaling (AA_DisableHighDpiScaling)"},
            [](const QString&) { QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling); },
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
            [this](const QString& argument) {
                if(!_translator.load(argument)) {
                    qDebug() << "Failed to load translation file:" << argument;
                }
            },
        },
    };
};
