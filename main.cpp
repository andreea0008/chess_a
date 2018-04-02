#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Controllers/board.h"
#include "Controllers/whitefigures.h"
#include "Controllers/blackfigures.h"
#include "Controllers/figurecontrollers.h"
#include "Controllers/logofchessmove.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Board board(&engine);
    WhiteFigures whiteFigures(&engine);
    BlackFigures blackFigures(&engine);
    FigureControllers figureControllers(&engine);
    LogOfChessMove logOfChessMove(&engine);

    engine.rootContext()->setContextProperty("board", &board);
    engine.rootContext()->setContextProperty("whiteFigures", &whiteFigures);
    engine.rootContext()->setContextProperty("blackFigures", &blackFigures);
    engine.rootContext()->setContextProperty("figureControllers", &figureControllers);
    engine.rootContext()->setContextProperty("logOfChessMove", &logOfChessMove);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
