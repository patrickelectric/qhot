#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QQmlApplicationEngine>

#include "commandlineparser.h"
#include "providessomething.h"
#include "urlinterceptor.h"

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<ProvidesSomething>("ProvidesSomething", 1, 0, "ProvidesSomething", ProvidesSomething::qmlSingletonRegister);

    CommandLineParser parser(argc, argv);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine appEngine(QUrl("qrc:/main.qml"));

    appEngine.setUrlInterceptor(UrlInterceptor::self());
    ProvidesSomething::self()->setEngine(&appEngine);

    if(parser.positionalArguments().size()) {
        QDir dir(parser.positionalArguments()[0]);
        if(!QFile::exists(dir.absolutePath())) {
            qDebug() << "Path" << dir.absolutePath() << "does not exist";
        } else {
            ProvidesSomething::self()->setFilePath(QUrl::fromUserInput(dir.absolutePath()));
        }
    }
    return app.exec();
}
