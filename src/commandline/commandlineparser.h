#pragma once

#include <functional>

#include <QCommandLineParser>
#include <QQmlEngine>


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
    void setEngine(QQmlEngine* engine)
    {
        engine->setImportPathList(_importPaths);
        engine->setPluginPathList(_pluginPaths);
    }

private:
    struct OptionStruct {
        QCommandLineOption option;
        std::function<void(const QString&)> function;
    };

    void printHelp();

    QStringList _importPaths;
    QStringList _pluginPaths;

    QList<OptionStruct> _optionsStruct {
        {
            {{"help", "h", "?"}, "Give this friendly help message for our confort"},
            [this](const QString&) { printHelp(); },
        },
        {
            {"desktop", "Force use of desktop GL (AA_UseDesktopOpenGL)"},
            [](const QString&) { QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL); },
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
    };
};
