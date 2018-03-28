#include "figurecontrollers.h"
#include <iostream>
#include <memory>
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
    int row = index / SIZE;
    int column = index % SIZE;
    int getIdFromArrayFigures = arrayFigures[row][column];
    if(getIdFromArrayFigures > 200){
        switch (getIdFromArrayFigures) {
        case WHITE_ROOK:
            return "qrc:/image/Img/white_rook.png";
            break;
        case WHITE_KNIGHT:
            return "qrc:/image/Img/white_knight.png";
            break;
        case WHITE_BISHOP:
            return "qrc:/image/Img/white_bishop.png";
            break;
        case WHITE_QUEEN:
            return "qrc:/image/Img/white_queen.png";
            break;
        case WHITE_KING:
            return "qrc:/image/Img/white_king.png";
            break;
        case WHITE_PAWN:
            return "qrc:/image/Img/white_pawn.png";
            break;
        }
    } else {
        //black figures
        switch (getIdFromArrayFigures) {
        case BLACK_ROOK:
            return "qrc:/image/Img/black_rook.png";
            break;
        case BLACK_KNIGHT:
            return "qrc:/image/Img/black_knight.png";
            break;
        case BLACK_BISHOP:
            return "qrc:/image/Img/black_bishop.png";
            break;
        case BLACK_QUEEN:
            return "qrc:/image/Img/black_queen.png";
            break;
        case BLACK_KING:
            return "qrc:/image/Img/black_king.png";
            break;
        case BLACK_PAWN:
            return "qrc:/image/Img/black_pawn.png";
            break;
        }
    }
    return "";
}

void FigureControllers::getFigureByIndex(int index)
{
    if(index == EMPTY) return;
    int row = index / SIZE;
    int column = index % SIZE;
    int getIdFromArrayFigures = arrayFigures[row][column];
    bool beatFigure = false;
    int beatIndex = -1;
    if (getIdFromArrayFigures == EMPTY && selectedFigure != EMPTY &&
            !moveList().isEmpty()){
        if(isCommandMove(index)){
            emit commandMoveToIndex(selectedIndexFigure, index);
            int rowSelectedIndex = selectedIndexFigure / SIZE;
            int columnSelectedIndex = selectedIndexFigure % SIZE;
            arrayFigures[rowSelectedIndex][columnSelectedIndex] = EMPTY;
            arrayFigures[row][column] = selectedFigure;
            if(selectedFigure == WHITE_PAWN)
                firstStepWhite = false;
            if(selectedFigure == BLACK_PAWN)
                firstStepBlack = false;
            printArray();
            isNextStepWhite = !isNextStepWhite;
            selectedFigure = EMPTY;
        }
    }
    if(getIdFromArrayFigures != EMPTY && selectedFigure != EMPTY && !beatList().isEmpty())
    {
        beatFigure = true;
        beatIndex = index;

        if(isCommandBeat(index)){
            arrayFigures[row][column] = selectedFigure;
            int rowSelectedIndex = selectedIndexFigure / SIZE;
            int columnSelectedIndex = selectedIndexFigure % SIZE;
            arrayFigures[rowSelectedIndex][columnSelectedIndex] = 0;
            int indexFrom = (rowSelectedIndex * SIZE) + columnSelectedIndex;
            int indexTo = (row * SIZE) + column;
            emit commandBeat(indexFrom, indexTo);
            getIdFromArrayFigures = arrayFigures[row][column];
            printArray();
            isNextStepWhite = !isNextStepWhite;
            selectedFigure = EMPTY;
            m_beatList.clear();
            m_moveList.clear();
        }
    }
    if(getIdFromArrayFigures != EMPTY)
        selectedIndexFigure = index;

    if(getIdFromArrayFigures > 200 && isNextStepWhite){
        switch (getIdFromArrayFigures) {
        case WHITE_ROOK:
            qDebug() <<  "white_rook" << row << column;
            break;
        case WHITE_KNIGHT:
            qDebug() << "white_knight";
            break;
        case WHITE_BISHOP:
            qDebug() << "white_bishop";
            break;
        case WHITE_QUEEN:
            qDebug() << "white_queen";
            break;
        case WHITE_KING:
            qDebug() <<"white_king";
            break;
        case WHITE_PAWN:
            qDebug() <<"white_pawn";
            QVector<QVariant> variantMovePaws = movePawn(true, row, column);
            QVector<QVariant> variantBeatPaws = canPawnBeat(true, row, column);
            setBeatList(QVariantList::fromVector(variantBeatPaws));
            setMoveList(QVariantList::fromVector(variantMovePaws));
            qDebug() << variantBeatPaws.size() << variantMovePaws.size();
            selectedFigure = WHITE_PAWN;
            break;
        }
    }
    else if(!isNextStepWhite){
        //black figures
        switch (getIdFromArrayFigures) {
        case BLACK_ROOK:
            qDebug() << "black_rook";
            break;
        case BLACK_KNIGHT:
            qDebug() << "black_knight";
            break;
        case BLACK_BISHOP:
            qDebug() <<"black_bishop";
            break;
        case BLACK_QUEEN:
            qDebug() << "black_queen";
            break;
        case BLACK_KING:
            qDebug() << "black_king";
            break;
        case BLACK_PAWN:
            qDebug() << "black_pawn";
            selectedFigure = BLACK_PAWN;
            QVector<QVariant> variantMovePaws = movePawn(false, row, column);
            QVector<QVariant> variansBeatPaws = canPawnBeat(false, row, column);
            setMoveList(QVariantList::fromVector(variantMovePaws));
            setBeatList(QVariantList::fromVector(variansBeatPaws));
            break;
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

bool FigureControllers::isCommandMove(int index) const
{
    return moveList().contains(index);
}

bool FigureControllers::isCommandBeat(int index) const
{
    return beatList().contains(index);
}

void FigureControllers::setMoveList(QVariantList moveList)
{
    m_moveList = moveList;
    emit moveListChanged(moveList);
}

void FigureControllers::setBeatList(QVariantList beatList)
{
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
                arrayFigures[i][j] = BLACK_PAWN;
            }
            else if (i == 6){
                arrayFigures[i][j] = WHITE_PAWN;
            }

            if(i == 0){
                if(j == 0 || j == 7)
                    arrayFigures[i][j] = BLACK_ROOK;
                if(j == 1 || j == 6)
                    arrayFigures[i][j] = BLACK_KNIGHT;
                if(j == 2 || j == 5)
                    arrayFigures[i][j] = BLACK_BISHOP;
                if(j == 3)
                    arrayFigures[i][j] = BLACK_QUEEN;
                if(j == 4)
                    arrayFigures[i][j] = BLACK_KING;
            }

            if(i == 7){
                if(j == 0 || j == 7)
                    arrayFigures[i][j] = WHITE_ROOK;
                if(j == 1 || j == 6)
                    arrayFigures[i][j] = WHITE_KNIGHT;
                if(j == 2 || j == 5)
                    arrayFigures[i][j] = WHITE_BISHOP;
                if(j == 3)
                    arrayFigures[i][j] = WHITE_QUEEN;
                if(j == 4)
                    arrayFigures[i][j] = WHITE_KING;
            }
        }
    }
}

int FigureControllers::getIndexThrowRowAndColumn(int row, int column)
{
    return (row * SIZE) + column;
}

QVector<QVariant> FigureControllers::movePawn(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorMovePaws;
    if(isWhite){
        if(row  -STEP_PAWN != -STEP_PAWN){
            if(arrayFigures[row -STEP_PAWN][column] == EMPTY)
                vectorMovePaws.push_back(getIndexThrowRowAndColumn(row -STEP_PAWN, column));
        }
        if(firstStepWhite && arrayFigures[row -DOUBLE_STEP_PAWN][column] == EMPTY)
            vectorMovePaws.push_back(getIndexThrowRowAndColumn(row -DOUBLE_STEP_PAWN, column));
    }
    else
    {
        if(row +STEP_PAWN != SIZE && arrayFigures[row +STEP_PAWN][column] == EMPTY){
            vectorMovePaws.push_back(getIndexThrowRowAndColumn(row +STEP_PAWN, column));
        }
        if(firstStepBlack && arrayFigures[row +DOUBLE_STEP_PAWN][column] == EMPTY){
            vectorMovePaws.push_back(getIndexThrowRowAndColumn(row +DOUBLE_STEP_PAWN, column));
        }
    }
    return vectorMovePaws;
}

QVector<QVariant> FigureControllers::canPawnBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorPawnBeat;
    if(isWhite){
        if(row -STEP_PAWN != -STEP_PAWN ){
            //white figures beat left
            if(column -STEP_PAWN != -STEP_PAWN &&
               arrayFigures[row -STEP_PAWN][column -STEP_PAWN] != EMPTY &&
               arrayFigures[row -STEP_PAWN][column +STEP_PAWN] < 200)
            {
                if(arrayFigures[row-STEP_PAWN][column-STEP_PAWN] < 200)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row -STEP_PAWN, column -STEP_PAWN));
            }
            //white figures beat right
            if(column +STEP_PAWN != SIZE
               && arrayFigures[row -STEP_PAWN][column +STEP_PAWN] != EMPTY
               && arrayFigures[row -STEP_PAWN][column +STEP_PAWN] < 200)
            {
                if(arrayFigures[row -STEP_PAWN][column +STEP_PAWN] < 200)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row -STEP_PAWN, column +STEP_PAWN));
            }
        }
    }else{
        if(row +STEP_PAWN != SIZE ){
            //black figure beat left
            if(column -STEP_PAWN != -STEP_PAWN
               && arrayFigures[row +STEP_PAWN][column -STEP_PAWN] != EMPTY
               && arrayFigures[row +STEP_PAWN][column -STEP_PAWN] > 200)
            {
                if(arrayFigures[row +STEP_PAWN][column -STEP_PAWN] > 200)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row +STEP_PAWN, column -STEP_PAWN));
            }

            //black figure beat right
            if(column +STEP_PAWN != SIZE
               && arrayFigures[row +STEP_PAWN][column +STEP_PAWN] != EMPTY
               && arrayFigures[row +STEP_PAWN][column +STEP_PAWN] > 200)
            {
                if(arrayFigures[row +STEP_PAWN][column +STEP_PAWN] > 200)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row +STEP_PAWN, column +STEP_PAWN));
            }
        }
    }
    return vectorPawnBeat;
}

void FigureControllers::printArray()
{
    for(int i = 0; i < SIZE; i++){
        QString str;
        for(int j = 0; j < SIZE; j++){
            int figure  = arrayFigures[i][j];
            if(figure == 0)
                str.append("[--] ");
            if(figure == 111)
                str.append("[BP] ");
            if(figure == 211)
                str.append("[WP] ");
            if(figure == 101)
                str.append("[BR] ");
            if(figure == 201)
                str.append("[WR] ");
            if(figure == 102)
                str.append("[BK] ");
            if(figure == 202)
                str.append("[WK] ");
            if(figure == 103)
                str.append("[BB] ");
            if(figure == 203)
                str.append("[WB] ");
            if(figure == 104)
                str.append("[BQ] ");
            if(figure == 204)
                str.append("[WQ] ");
            if(figure == 105)
                str.append("[BK] ");
            if(figure == 205)
                str.append("[WK] ");
        }
        qDebug() << str;
    }
}
