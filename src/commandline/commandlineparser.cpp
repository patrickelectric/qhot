#include "commandlineparser.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include <utility>

CommandLineParser::CommandLineParser(int argc, char *argv[])
    : QCommandLineParser()
{
    setApplicationDescription("Hot reload for nested qml files.");
    addVersionOption();

    for (auto& optionStruct : std::as_const(_optionsStruct)) {
        addOption(optionStruct.option);
    }

    QStringList arguments;
    for(int i{0}; i < argc; i++) {
        arguments.append(argv[i]);
    }
    process(arguments);

    for (auto& optionStruct : std::as_const(_optionsStruct)) {
        if(!isSet(optionStruct.option)) {
            continue;
        }

        // Check if there is a result and if the option accepts it
        if (!optionStruct.option.valueName().isEmpty()) {
            QString result = value(optionStruct.option);
            if (!result.isEmpty()) {
                qDebug().noquote() << QStringLiteral("%1 [%2]: %3")
                                                .arg(optionStruct.option.names().constFirst(),
                                                    optionStruct.option.description(), result);
                optionStruct.function(result);
            } else {
                qDebug().noquote() << QStringLiteral("%1 [%2]: %3")
                                                .arg(optionStruct.option.names().constFirst(),
                                                    optionStruct.option.description(), "No valid parameter.");
            }
        } else {
            qDebug().noquote() << QStringLiteral("%1 [%2]: ON")
                                              .arg(optionStruct.option.names().constFirst(),
                                                  optionStruct.option.description());
            optionStruct.function({});
        }
    }
};

void CommandLineParser::setApplication(QCoreApplication* application)
{
    Q_UNUSED(application)
    QCoreApplication::installTranslator(&_translator);

    for(const auto& function : std::as_const(_posAppFunctions)) {
        function();
    }
}

void CommandLineParser::setEngine(QQmlEngine* engine)
{
    for (auto& path : std::as_const(_importPaths)) {
        engine->addImportPath(path);
    }

    for (auto& path : std::as_const(_pluginPaths)) {
        engine->addPluginPath(path);
    }
}

void CommandLineParser::printHelp()
{
    for (auto& optionStruct : std::as_const(_optionsStruct)) {
        auto names = optionStruct.option.names();
        for(auto& name: names) {
            name.prepend(name.length() > 1 ? "--" : "-");
        }

        auto commands = names.join(", ");
        auto tabs = QString("\t").repeated(3 - (commands.length() + 1)/8);
        qDebug().noquote() << commands << tabs << optionStruct.option.description();
    }
}

void CommandLineParser::_parseQHotProfile(const QString& profilePath)
{
    QFileInfo fInfo{profilePath};
    QString profileFileName = QStringLiteral("qhot-profile.json");
    if (fInfo.fileName() != profileFileName) {
        qWarning() << "Wrong profile:" << fInfo.fileName() << "it should be:" << profileFileName;
        return;
    }

    QFile file{profilePath};
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open json file for reading.";
        return;
    }

    QDir profileDir{fInfo.absolutePath()};

    auto jsonData = file.readAll();
    QJsonParseError error;
    auto jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (jsonDoc.isNull()) {
        qWarning() << error.errorString();
        return;
    }
    if (!jsonDoc.isObject()) {
        qWarning() << "Top level item should be an object";
        return;
    }

    auto jsonObject = jsonDoc.object();

    auto desktop = jsonObject.value(QLatin1String{"desktop"});
    if (desktop.toBool(), false)
        QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    auto style = jsonObject.value(QLatin1String{"style"});
    if (style.isString()) {
        QQuickStyle::setStyle(style.toString());
    }

    auto gles = jsonObject.value(QLatin1String{"gles"});
    if (gles.toBool(), false)
        QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    auto software = jsonObject.value(QLatin1String{"software"});
    if (software.toBool(), false)
        QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

    auto importPaths = jsonObject.value(QLatin1String{"import-path"});
    if (importPaths.isArray()) {
        const auto paths = importPaths.toArray();
        for (const auto &path : paths) {
            _importPaths.append(profileDir.absoluteFilePath(path.toString()));
        }
    }

    auto pluginPaths = jsonObject.value(QLatin1String{"plugin-path"});
    if (pluginPaths.isArray()) {
        const auto paths = pluginPaths.toArray();
        for (const auto &path : paths) {
            _pluginPaths.append(profileDir.absoluteFilePath(path.toString()));
        }
    }

    auto translationFile = jsonObject.value(QLatin1String{"translation"});
    if (translationFile.isString()) {
        _translate(translationFile.toString());
    }

    auto background = jsonObject.value(QLatin1String{"background"});
    if (background.isString()) {
        ProvidesSomething::self()->setBackground(background.toString());
    }

    auto controlsConfPath = jsonObject.value(QLatin1String { "quick-controls-conf" });
    if (controlsConfPath.isString()) {
        auto absPath = profileDir.absoluteFilePath(controlsConfPath.toString());
        qputenv("QT_QUICK_CONTROLS_CONF", absPath.toLocal8Bit());
    }

    auto appName = jsonObject.value(QLatin1String { "app-name" });
    if (appName.isString()) {
        _posAppFunctions.append(
            [appName]{
                qApp->setApplicationName(APPNAME_FORMAT.arg(appName.toString()));
        });
    }
}

void CommandLineParser::_translate(const QString &translationFile)
{
    if(!_translator.load(translationFile)) {
        qDebug() << "Failed to load translation file:" << translationFile;
        return;
    }

#if QT_VERSION > QT_VERSION_CHECK(5, 15, 0)
    qDebug() << "Translation loaded successfully, language:" << _translator.language();
    qDebug() << _translator.translate(nullptr, "car");
#endif

}
