#include "blackfigures.h"
#include <QDebug>

BlackFigures::BlackFigures(QObject *parent) : QObject(parent)
{
    fillArrayWhiteFigures();
}

void BlackFigures::fillArrayWhiteFigures()
{
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            arrayWhiteFigure[i][j] = 0;
        }
    }
    Figure figure;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(i == 1){
                arrayWhiteFigure[i][j] = figure.pawn;
            }
            if(i == 0){
                if(j == 0 || j == 7){
                  arrayWhiteFigure[i][j] = figure.rook;
                }
                if(j == 1 || j == 6){
                  arrayWhiteFigure[i][j] = figure.knight;
                }
                if(j == 2 || j == 5){
                  arrayWhiteFigure[i][j] = figure.bishop;
                }
                if(j == 3)
                    arrayWhiteFigure[i][j] = figure.queen;
                if(j == 4)
                    arrayWhiteFigure[i][j] = figure.king;
            }
        }
    }

    for(int i = 0; i < SIZE; i++){
        QString line = "";
        for(int j = 0; j < SIZE; j++){
            line += QString::number(arrayWhiteFigure[i][j]) + " ";
        }
        qDebug() << line;
    }
}
