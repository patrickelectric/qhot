#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QQmlApplicationEngine>

#include "providessomething.h"

int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<ProvidesSomething>("ProvidesSomething", 1, 0, "ProvidesSomething", ProvidesSomething::qmlSingletonRegister);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine appEngine(QUrl("qrc:/main.qml"));

    if(app.arguments().size() > 1) {
        QDir dir(app.arguments()[1]);
        if(!QFile::exists(dir.absolutePath())) {
            qDebug() << "Path" << dir.absolutePath() << "does not exist";
        } else {
            ProvidesSomething::self()->setFilePath(QUrl::fromUserInput(dir.absolutePath()));
        }
    }
    return app.exec();
}
