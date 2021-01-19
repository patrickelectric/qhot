#include "commandlineparser.h"
#include "providessomething.h"
#include "urlinterceptor.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<ProvidesSomething>("ProvidesSomething", 1, 0, "ProvidesSomething", ProvidesSomething::qmlSingletonRegister);

    CommandLineParser commandLineParser(argc, argv);

    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("patrickelectric.work");
    app.setOrganizationName("patrickelectric");
    commandLineParser.setApplication(&app);

    QQmlApplicationEngine appEngine(QUrl("qrc:/main.qml"));
    commandLineParser.setEngine(&appEngine);

    appEngine.setUrlInterceptor(UrlInterceptor::self());
    ProvidesSomething::self()->setEngine(&appEngine);

    if (commandLineParser.positionalArguments().size()) {
        QDir dir(commandLineParser.positionalArguments().at(0));
        if (!QFile::exists(dir.absolutePath())) {
            qWarning() << "Path" << dir.absolutePath() << "does not exist";
        } else {
            ProvidesSomething::self()->setFilePath(QUrl::fromUserInput(dir.absolutePath()));
        }
    }

    return app.exec();
}
