#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QIcon>

#include "translator.h"
#include "fileinput.h"
#include "fileoutput.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    Translator translator;
    qmlRegisterType<Translator>("Translator", 1, 0, "Translator_qml");
    FileInput in;
    qmlRegisterType<FileInput>("FileInput", 1, 0, "FileInput_qml");
    FileOutput out;
    qmlRegisterType<FileOutput>("FileOutput", 1, 0, "FileOutput_qml");

    // Autocreated code
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    // End of autocreated code

    app.setWindowIcon(QIcon(":/images/icon.png"));

    return app.exec();
}
