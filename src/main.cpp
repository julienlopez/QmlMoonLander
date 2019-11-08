#include "simulator.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<Simulator>("QmlMoonLander", 1, 0, "Simulator", "");

    Simulator sim;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("simulator", &sim);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                     [url](QObject* obj, const QUrl& objUrl) {
                         if(!obj && url == objUrl) QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
