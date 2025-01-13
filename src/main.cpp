#include "commandlineparser.h"
#include "providessomething.h"
#include "urlinterceptor.h"

#include <QApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<ProvidesSomething>("ProvidesSomething", 1, 0, "ProvidesSomething", ProvidesSomething::qmlSingletonRegister);


    QApplication app(argc, argv);
    app.setOrganizationDomain("patrickelectric.work");
    app.setOrganizationName("patrickelectric");
    CommandLineParser commandLineParser(argc, argv);
    commandLineParser.setApplication(&app);

    QQmlApplicationEngine appEngine;
    commandLineParser.setEngine(&appEngine);
    appEngine.load(QUrl("qrc:/main.qml"));

    appEngine.addUrlInterceptor(UrlInterceptor::self());
    ProvidesSomething::self()->setEngine(&appEngine);

    if (commandLineParser.positionalArguments().size()) {
        QDir dir(commandLineParser.positionalArguments().at(0));
        if (!QFile::exists(dir.absolutePath())) {
            qWarning() << "Path" << dir.absolutePath() << "does not exist";
        } else {
            ProvidesSomething::self()->setFilePath(QUrl::fromUserInput(dir.absolutePath()));
        }
    }
    commandLineParser.loadDummyData(&appEngine);

    return app.exec();
}
