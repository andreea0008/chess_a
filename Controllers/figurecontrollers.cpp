#include "figurecontrollers.h"
#include <QDebug>

FigureControllers::FigureControllers(QObject *parent) : QObject(parent),
    firstStepBlack(true),
    firstStepWhite(true),
    isNextStepWhite(true)
{
    fillArray();
}

QString FigureControllers::getPathToIconByIndex(int index)
{
    int row = index / 8;
    int column = index % 8;
    int getIdFromArrayFigures = arrayFigures[row][column];
    if(getIdFromArrayFigures > 200){
        switch (getIdFromArrayFigures) {
        case 201:
            return "qrc:/image/Img/white_rook.png";
            break;
        case 202:
            return "qrc:/image/Img/white_knight.png";
            break;
        case 203:
            return "qrc:/image/Img/white_bishop.png";
            break;
        case 204:
            return "qrc:/image/Img/white_queen.png";
            break;
        case 205:
            return "qrc:/image/Img/white_king.png";
            break;
        case 211:
            return "qrc:/image/Img/white_pawn.png";
            break;
        }
    } else {
        //black figures
        switch (getIdFromArrayFigures) {
        case 101:
            return "qrc:/image/Img/black_rook.png";
            break;
        case 102:
            return "qrc:/image/Img/black_knight.png";
            break;
        case 103:
            return "qrc:/image/Img/black_bishop.png";
            break;
        case 104:
            return "qrc:/image/Img/black_queen.png";
            break;
        case 105:
            return "qrc:/image/Img/black_king.png";
            break;
        case 111:
            return "qrc:/image/Img/black_pawn.png";
            break;
        }
    }
    return "";
}

void FigureControllers::getFigureByIndex(int index)
{
    int row = index / 8;
    int column = index % 8;
    int getIdFromArrayFigures = arrayFigures[row][column];
    if (getIdFromArrayFigures == 0)  {
        setBeatList(QVariantList::fromVector(canPawnBeat(isNextStepWhite, row, column)));
        qCritical() << "Not_select_figure" << selectedIndexFigure << beatList();

        bool isMove = isCommandMove(index);
        bool isBeat = isCommandBeat(index);
        qDebug() << isMove << "is_can_beat: " << isBeat << index << row << column;
//        if(!isMove){
//            m_beatList.clear();
//            m_moveList.clear();
////            setBeatList(m_beatList);
////            setMoveList(m_moveList);
////            selectedIndexFigure = -1;
//        }
//        if(isBeat){
//            qDebug() << "SELECT_BEAT";
//            emit commandMoveToIndex(selectedIndexFigure, index);
//            int rowSelectedIndex = selectedIndexFigure / 8;
//            int columnSelectedIndex = selectedIndexFigure % 8;
//            qDebug() << row << column << " : "<< rowSelectedIndex << columnSelectedIndex << selectedFigure;
////            arrayFigures[rowSelectedIndex][columnSelectedIndex] = 0;
////            arrayFigures[row][column] = selectedFigure;
//        }
////        else{
//            qDebug() << "selectedindex " << selectedIndexFigure;
            emit commandMoveToIndex(selectedIndexFigure, index);
            int rowSelectedIndex = selectedIndexFigure / 8;
            int columnSelectedIndex = selectedIndexFigure % 8;
            arrayFigures[rowSelectedIndex][columnSelectedIndex] = 0;
            arrayFigures[row][column] = selectedFigure;
            if(selectedFigure == 211)
                firstStepWhite = false;
            if(selectedFigure == 111)
                firstStepBlack = false;

////        }
        isNextStepWhite = !isNextStepWhite;
    }else{
        bool isBeat = isCommandBeat(index);
        qDebug() << "figure select" << index << isBeat;
        if(isBeat){
            int rowSelectedIndex = selectedIndexFigure / 8;
            int columnSelectedIndex = selectedIndexFigure % 8;

            arrayFigures[rowSelectedIndex][columnSelectedIndex] = 0;
            arrayFigures[rowSelectedIndex][columnSelectedIndex] = selectedFigure;
            emit commandBeat(selectedIndexFigure, index);
        }


    }
    selectedIndexFigure = index;

    if(getIdFromArrayFigures > 200 && isNextStepWhite){
        qDebug() << "selectedIndexFigure: " << selectedIndexFigure << index;

        switch (getIdFromArrayFigures) {
        case 201:

            qDebug() <<  "white_rook" << row << column;
            break;
        case 202:
            qDebug() << "white_knight";
            break;
        case 203:
            qDebug() << "white_bishop";
            break;
        case 204:
            qDebug() << "white_queen";
            break;
        case 205:
            qDebug() <<"white_king";
            break;
        case 211:
            qDebug() <<"white_pawn";
            selectedFigure = 211;
            QVector<QVariant> variantMovePaws = movePawn(true, row, column);
            QVector<QVariant> variansBeatPaws = canPawnBeat(true, row, column);
            setMoveList(QVariantList::fromVector(variantMovePaws));
            setBeatList(QVariantList::fromVector(variansBeatPaws));
            break;
        }
    }
    else{
        if(!isNextStepWhite){
            //black figures
            switch (getIdFromArrayFigures) {
            case 101:
                qDebug() << "black_rook";
                break;
            case 102:
                qDebug() << "black_knight";
                break;
            case 103:
                qDebug() <<"black_bishop";
                break;
            case 104:
                qDebug() << "black_queen";
                break;
            case 105:
                qDebug() << "black_king";
                break;
            case 111:
                qDebug() << "black_pawn";
                selectedFigure = 111;
                QVector<QVariant> variantMovePaws = movePawn(false, row, column);
                QVector<QVariant> variansBeatPaws = canPawnBeat(false, row, column);
                setMoveList(QVariantList::fromVector(variantMovePaws));
                setBeatList(QVariantList::fromVector(variansBeatPaws));
                break;
            }
        }
    }
}

QVariantList FigureControllers::moveList() const
{
    return m_moveList;
}

QVariantList FigureControllers::beatList() const
{
    return m_beatList;
}

bool FigureControllers::isCommandMove(int index)
{
    foreach (QVariant indexFromList, moveList()) {
        if(indexFromList.toInt() == index)
            return true;
    }
    return false;
}

bool FigureControllers::isCommandBeat(int index)
{

    return beatList().contains(index);
}

void FigureControllers::setMoveList(QVariantList moveList)
{
    //    if (m_moveList == moveList)
    //        return;

    m_moveList = moveList;
    emit moveListChanged(moveList);
}

void FigureControllers::setBeatList(QVariantList beatList)
{
    //    if (m_beatList == beatList)
    //        return;

    m_beatList = beatList;
    emit beatListChanged(beatList);
}

void FigureControllers::fillArray()
{
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            arrayFigures[i][j] = 0;
        }
    }

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(i == 1){
                arrayFigures[i][j] = 111;
            }
            else if (i == 6){
                arrayFigures[i][j] = 211;
            }

            if(i == 0){
                if(j == 0 || j == 7){
                    arrayFigures[i][j] = 101;
                }
                if(j == 1 || j == 6){
                    arrayFigures[i][j] = 102;
                }
                if(j == 2 || j == 5){
                    arrayFigures[i][j] = 103;
                }
                if(j == 3)
                    arrayFigures[i][j] = 104;
                if(j == 4)
                    arrayFigures[i][j] = 105;
            }

            if(i == 7){
                if(j == 0 || j == 7){
                    arrayFigures[i][j] = 201;
                }
                if(j == 1 || j == 6){
                    arrayFigures[i][j] = 202;
                }
                if(j == 2 || j == 5){
                    arrayFigures[i][j] = 203;
                }
                if(j == 3)
                    arrayFigures[i][j] = 204;
                if(j == 4)
                    arrayFigures[i][j] = 205;
            }
        }
    }
}

int FigureControllers::getIndexThrowRowAndColumn(int row, int column)
{
    int index = 0;

    index += (row * 8);
    index += column;
    qDebug() << index;

    return index;
}

QVector<QVariant> FigureControllers::movePawn(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorMovePaws;
    if(isWhite){
        if(row-1 != -1){
            qDebug() << "you can beat: " << row-1;
            if(arrayFigures[row - 1][column] == 0)
                vectorMovePaws.push_back(getIndexThrowRowAndColumn(row-1, column));
        }
        if(firstStepWhite && arrayFigures[row - 2][column] == 0)
            vectorMovePaws.push_back(getIndexThrowRowAndColumn(row-2, column));
    }

    else{
        if(row + 1 != 8 && arrayFigures[row+1][column] == 0){
            vectorMovePaws.push_back(getIndexThrowRowAndColumn(row+1, column));
        }
        if(firstStepBlack && arrayFigures[row+2][column] == 0){
            vectorMovePaws.push_back(getIndexThrowRowAndColumn(row+2, column));
        }
    }
    qDebug() <<  "vectorMovePaws: "<< vectorMovePaws;
    return vectorMovePaws;
}

QVector<QVariant> FigureControllers::canPawnBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorPawnBeat;
    if(isWhite){
        if(row-1 != -1 ){
            if(column -1 != -1  && arrayFigures[row-1][column-1] != 0){
//                qDebug() << "you can beat: " << row-1 << column -1;
                vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row-1, column -1));
            }
            if(column +1 != 8 && arrayFigures[row-1][column+1] != 0){
//                qDebug() << "you can beat: " << row-1 << column +1;
                vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row-1, column +1));
            }
        }
    }else{
        if(row+1 != 8 ){
            if(column -1 != -1 && arrayFigures[row+1][column-1] != 0){
//                qDebug() << "you can beat: " << row+1 << column -1;
                vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row+1, column -1));
            }
            if(column +1 != 8 && arrayFigures[row+1][column+1] != 0){
//                qDebug() << "you can beat: " << row+1 << column +1;
                vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row+1, column +1));
            }
        }
    }
    return vectorPawnBeat;
}
