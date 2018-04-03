#include "figurecontrollers.h"
#include <iostream>
#include <memory>
#include <QDebug>


FigureControllers::FigureControllers(QObject *parent) : QObject(parent),
    firstStepBlack(true),
    firstStepWhite(true),
    m_isNextStepWhite(true)
{
    fillArray();
}

QString FigureControllers::getPathToIconByIndex(int index)
{
    int row = index / SIZE;
    int column = index % SIZE;
    int getIdFromArrayFigures = arrayFigures[row][column];
    if(getIdFromArrayFigures > MEDIANA_FIGURES){
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
    int row = index / SIZE;
    int column = index % SIZE;
    int getIdFromArrayFigures = arrayFigures[row][column];
    bool beatFigure = false;
    int beatIndex = -1;
    qDebug() << "get_id_fro,_array_figures: " << getIdFromArrayFigures;
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
            setIsNextStepWhite(!isNextStepWhite());
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
            arrayFigures[rowSelectedIndex][columnSelectedIndex] = EMPTY;
            int indexFrom = (rowSelectedIndex * SIZE) + columnSelectedIndex;
            int indexTo = (row * SIZE) + column;
            emit commandBeat(indexFrom, indexTo);
            getIdFromArrayFigures = arrayFigures[row][column];
            printArray();
            setIsNextStepWhite(!isNextStepWhite());
            selectedFigure = EMPTY;
            m_beatList.clear();
            m_moveList.clear();
        }
    }
    if(getIdFromArrayFigures != EMPTY)
        selectedIndexFigure = index;

    if(getIdFromArrayFigures > MEDIANA_FIGURES && isNextStepWhite()){
        switch (getIdFromArrayFigures) {
        case WHITE_ROOK:
            qDebug() <<  "white_rook" << row << column;
            setMoveList(QVariantList::fromVector(moveRook(row, column)));
            setBeatList(QVariantList::fromVector(canRookBeat(true, row, column)));
            selectedFigure = WHITE_ROOK;
            break;
        case WHITE_KNIGHT:
            qDebug() << "white_knight";
            setMoveList(QVariantList::fromVector(moveKnight(row, column)));
            setBeatList(QVariantList::fromVector(canKnightBeat(true, row, column)));
            selectedFigure = WHITE_KNIGHT;
            break;
        case WHITE_BISHOP:
            qDebug() << "white_bishop";
            setMoveList(QVariantList::fromVector(moveBishop(row, column)));
            setBeatList(QVariantList::fromVector(canBishopBeat(true, row, column)));
            selectedFigure = WHITE_BISHOP;
            break;
        case WHITE_QUEEN:
            qDebug() << "white_queen";
            setMoveList(QVariantList::fromVector(moveQueen(row, column)));
            setBeatList(QVariantList::fromVector(canQueenBeat(true, row, column)));
            selectedFigure = WHITE_QUEEN;
            break;
        case WHITE_KING:
            qDebug() <<"white_king";
            setMoveList(QVariantList::fromVector(moveKing(row, column)));
            setBeatList(QVariantList::fromVector(canKingBeat(true, row, column)));
            selectedFigure = WHITE_KING;
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
    else if(!isNextStepWhite()){
        //black figures
        switch (getIdFromArrayFigures) {
        case BLACK_ROOK:
            qDebug() << "black_rook";
            setMoveList(QVariantList::fromVector(moveRook(row, column)));
            setBeatList(QVariantList::fromVector(canRookBeat(false, row, column)));
            selectedFigure = BLACK_ROOK;
            break;
        case BLACK_KNIGHT:
            qDebug() << "black_knight";
            setMoveList(QVariantList::fromVector(moveKnight(row, column)));
            setBeatList(QVariantList::fromVector(canKnightBeat(false, row, column)));
            selectedFigure = BLACK_KNIGHT;
            break;
        case BLACK_BISHOP:
            qDebug() <<"black_bishop";
            setMoveList(QVariantList::fromVector(moveBishop(row, column)));
            setBeatList(QVariantList::fromVector(canBishopBeat(false, row, column)));
            selectedFigure = BLACK_BISHOP;
            break;
        case BLACK_QUEEN:
            qDebug() << "black_queen";
            setMoveList(QVariantList::fromVector(moveQueen(row, column)));
            setBeatList(QVariantList::fromVector(canQueenBeat(false, row, column)));
            selectedFigure = BLACK_QUEEN;
            break;
        case BLACK_KING:
            qDebug() << "black_king";
            setMoveList(QVariantList::fromVector(moveKing(row, column)));
            setBeatList(QVariantList::fromVector(canKingBeat(false, row, column)));
            selectedFigure = BLACK_KING;
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

bool FigureControllers::isNextStepWhite() const
{
    return m_isNextStepWhite;
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

void FigureControllers::setIsNextStepWhite(bool isNextStepWhite)
{
    if (m_isNextStepWhite == isNextStepWhite)
        return;

    m_isNextStepWhite = isNextStepWhite;
    emit isNextStepWhiteChanged(isNextStepWhite);
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
//next function move
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

QVector<QVariant> FigureControllers::moveKnight(int row, int column)
{
    QVector<QVariant> vectorMoveKnight;
    //UP
    //row up 2 and left 1
    if(row -LONG_STEP_KNIGHT >= EMPTY && row -LONG_STEP_KNIGHT < SIZE &&
            column -SHORT_STEP_KNIGHT >= EMPTY && column -SHORT_STEP_KNIGHT < SIZE &&
            arrayFigures[row -LONG_STEP_KNIGHT][column -SHORT_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row -LONG_STEP_KNIGHT, column -SHORT_STEP_KNIGHT));
    }
    //row up 1 and left 2
    if(row -SHORT_STEP_KNIGHT >= EMPTY && row -SHORT_STEP_KNIGHT < SIZE &&
            column -LONG_STEP_KNIGHT >= EMPTY && column -LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row -SHORT_STEP_KNIGHT][column -LONG_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row -SHORT_STEP_KNIGHT, column -LONG_STEP_KNIGHT));
    }
    //row up 2 and right 1
    if(row -LONG_STEP_KNIGHT >= EMPTY && row -LONG_STEP_KNIGHT < SIZE &&
            column +SHORT_STEP_KNIGHT < SIZE && column +SHORT_STEP_KNIGHT >= EMPTY &&
            arrayFigures[row -LONG_STEP_KNIGHT][column +SHORT_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row -LONG_STEP_KNIGHT, column +SHORT_STEP_KNIGHT));
    }
    //row up 1 and right 2
    if(row -SHORT_STEP_KNIGHT >= EMPTY && row -SHORT_STEP_KNIGHT < SIZE &&
            column +LONG_STEP_KNIGHT >= EMPTY && column +LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row -SHORT_STEP_KNIGHT][column +LONG_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row -SHORT_STEP_KNIGHT, column +LONG_STEP_KNIGHT));
    }
    //DOWN
    //row down 2 and left 1
    if(row +LONG_STEP_KNIGHT >= EMPTY && row +LONG_STEP_KNIGHT < SIZE &&
            column -SHORT_STEP_KNIGHT >= EMPTY && column -SHORT_STEP_KNIGHT < SIZE &&
            arrayFigures[row +LONG_STEP_KNIGHT][column -SHORT_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row +LONG_STEP_KNIGHT, column -SHORT_STEP_KNIGHT));
    }
    //row down 1 and left 2
    if(row +SHORT_STEP_KNIGHT >= EMPTY && row +SHORT_STEP_KNIGHT < SIZE &&
            column -LONG_STEP_KNIGHT >= EMPTY && column -LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row +SHORT_STEP_KNIGHT][column -LONG_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row +SHORT_STEP_KNIGHT, column -LONG_STEP_KNIGHT));
    }
    //row down 2 and right 1
    if(row +LONG_STEP_KNIGHT >= EMPTY && row +SHORT_STEP_KNIGHT < SIZE &&
            column +SHORT_STEP_KNIGHT < SIZE && column +SHORT_STEP_KNIGHT >= EMPTY &&
            arrayFigures[row +LONG_STEP_KNIGHT][column +SHORT_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row +LONG_STEP_KNIGHT, column +SHORT_STEP_KNIGHT));
    }
    //row down 1 and right 2
    if(row +SHORT_STEP_KNIGHT >= EMPTY && row +SHORT_STEP_KNIGHT < SIZE &&
            column +LONG_STEP_KNIGHT >= EMPTY && column +LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row +SHORT_STEP_KNIGHT][column +LONG_STEP_KNIGHT] == EMPTY)
    {
        vectorMoveKnight.push_back(getIndexThrowRowAndColumn(row +SHORT_STEP_KNIGHT, column +LONG_STEP_KNIGHT));
    }

    return vectorMoveKnight;
}

QVector<QVariant> FigureControllers::moveRook(int row, int column)
{
    QVector<QVariant> vectorMoveRook;
    //move up
    for(int nextUpStep = 1; nextUpStep < (SIZE); nextUpStep++)
    {
        int identifireNextUpFigure = arrayFigures[row -nextUpStep][column];
        if(identifireNextUpFigure == EMPTY && (row -nextUpStep) >= EMPTY)
            vectorMoveRook.push_back(getIndexThrowRowAndColumn(row -nextUpStep, column));
        else
            break;
    }
    //move down
    for(int nextDownStep = 1; nextDownStep < (SIZE); nextDownStep++){
        int identifireNextDownFigure = arrayFigures[row +nextDownStep][column];
        if(identifireNextDownFigure == EMPTY && (row +nextDownStep) < SIZE)
            vectorMoveRook.push_back(getIndexThrowRowAndColumn(row +nextDownStep, column));
        else
            break;
    }
    //move left
    for(int nextLeftStep = 1; nextLeftStep < SIZE; nextLeftStep++){
        int identifireNextLeftFigure = arrayFigures[row][column -nextLeftStep];
        if(identifireNextLeftFigure == EMPTY && (column -nextLeftStep) >= EMPTY)
            vectorMoveRook.push_back(getIndexThrowRowAndColumn(row, column -nextLeftStep));
        else
            break;
    }
    //move right
    for(int nextRightStep = 1; nextRightStep < (SIZE); nextRightStep++){
        int identifireNextRightFigure = arrayFigures[row][column +nextRightStep];
        if(identifireNextRightFigure == EMPTY && (column +nextRightStep) < SIZE)
            vectorMoveRook.push_back(getIndexThrowRowAndColumn(row, column +nextRightStep));
        else
            break;
    }

    return vectorMoveRook;
}

QVector<QVariant> FigureControllers::moveBishop(int row, int column)
{
    QVector<QVariant> vectorMoveBishop;

    //UP AND LEFT
    for(int stepToUpAndLeft = 1; stepToUpAndLeft < SIZE; stepToUpAndLeft++){
        int identifireNextUpAndLeft = arrayFigures[row -stepToUpAndLeft][column -stepToUpAndLeft];
        if((identifireNextUpAndLeft == EMPTY) && (row -stepToUpAndLeft >= EMPTY) && (column -stepToUpAndLeft >= EMPTY))
            vectorMoveBishop.push_back(getIndexThrowRowAndColumn(row -stepToUpAndLeft, column -stepToUpAndLeft));
        else
            break;
    }

    //UP AND RIGHT
    for(int stepToUpAndRight = 1; stepToUpAndRight < SIZE; stepToUpAndRight++){
        int identifireNextUpAndRight = arrayFigures[row -stepToUpAndRight][column +stepToUpAndRight];
        if((identifireNextUpAndRight == EMPTY) && (row -stepToUpAndRight >= EMPTY) && (column +stepToUpAndRight < SIZE))
            vectorMoveBishop.push_back(getIndexThrowRowAndColumn(row -stepToUpAndRight, column +stepToUpAndRight));
        else
            break;
    }

    //DOWN AND LEFT
    for(int stepToDownAndLeft = 1; stepToDownAndLeft < SIZE; stepToDownAndLeft++){
        int identifireNextDownAndLeft = arrayFigures[row +stepToDownAndLeft][column -stepToDownAndLeft];
        if((identifireNextDownAndLeft == EMPTY) && (row +stepToDownAndLeft < SIZE) && (column -stepToDownAndLeft >= EMPTY))
            vectorMoveBishop.push_back(getIndexThrowRowAndColumn(row +stepToDownAndLeft, column -stepToDownAndLeft));
        else
            break;
    }

    //DOWN AND RIGHT
    for(int stepToDownAndRight = 1; stepToDownAndRight < SIZE; stepToDownAndRight++){
        int identirireNextDownAndRightFigure = arrayFigures[row +stepToDownAndRight][column +stepToDownAndRight];
        if((identirireNextDownAndRightFigure == EMPTY) && (row + stepToDownAndRight < SIZE) && (column +stepToDownAndRight < SIZE))
            vectorMoveBishop.push_back(getIndexThrowRowAndColumn(row +stepToDownAndRight, column +stepToDownAndRight));
        else
            break;
    }
    return vectorMoveBishop;
}

QVector<QVariant> FigureControllers::moveQueen(int row, int column)
{
    QVector<QVariant> vectorMoveQueen;
    vectorMoveQueen.append(moveRook(row, column));
    vectorMoveQueen.append(moveBishop(row, column));
    return vectorMoveQueen;
}

QVector<QVariant> FigureControllers::moveKing(int row, int column)
{
   QVector<QVariant> vectorMoveKing;
   //only up
   if(arrayFigures[row -STEP_KING][column] == EMPTY && (row -STEP_KING >= EMPTY))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column));

   //up and left
   if((arrayFigures[row -STEP_KING][column -STEP_KING] == EMPTY) && (row -STEP_KING >= EMPTY) && (column -STEP_KING >= EMPTY))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column -STEP_KING));

   //up and right
   if((arrayFigures[row -STEP_KING][column +STEP_KING] == EMPTY) && (row -STEP_KING >= EMPTY) && (column +STEP_KING < SIZE))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column +STEP_KING));

   //only left
   if((arrayFigures[row][column -STEP_KING] == EMPTY) && (column -STEP_KING >=EMPTY))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row, column -STEP_KING));

   //only right
   if((arrayFigures[row][column +STEP_KING] == EMPTY) && (column +STEP_KING < SIZE))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row, column +STEP_KING));

   //only down
   if((arrayFigures[row +STEP_KING][column] == EMPTY) && (row +STEP_KING) < SIZE)
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column));

   //left down
   if((arrayFigures[row +STEP_KING][column -STEP_KING] == EMPTY) && (row +STEP_KING < SIZE) && (column -STEP_KING >= EMPTY))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column -STEP_KING));

   //right down
   if((arrayFigures[row +STEP_KING][column +STEP_KING] == EMPTY) && (row +STEP_KING < SIZE) && (column +STEP_KING < SIZE))
       vectorMoveKing.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column +STEP_KING));

   return vectorMoveKing;
}

//next function beat
QVector<QVariant> FigureControllers::canPawnBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorPawnBeat;
    if(isWhite){
        if(row -STEP_PAWN != -STEP_PAWN ){
            //white figures beat left
            if(column -STEP_PAWN != -STEP_PAWN &&
               arrayFigures[row -STEP_PAWN][column -STEP_PAWN] != EMPTY &&
               arrayFigures[row -STEP_PAWN][column +STEP_PAWN] < MEDIANA_FIGURES)
            {
                if(arrayFigures[row-STEP_PAWN][column-STEP_PAWN] < MEDIANA_FIGURES)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row -STEP_PAWN, column -STEP_PAWN));
            }
            //white figures beat right
            if(column +STEP_PAWN != SIZE
               && arrayFigures[row -STEP_PAWN][column +STEP_PAWN] != EMPTY
               && arrayFigures[row -STEP_PAWN][column +STEP_PAWN] < MEDIANA_FIGURES)
            {
                if(arrayFigures[row -STEP_PAWN][column +STEP_PAWN] < MEDIANA_FIGURES)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row -STEP_PAWN, column +STEP_PAWN));
            }
        }
    }else{
        if(row +STEP_PAWN != SIZE ){
            //black figure beat left
            if(column -STEP_PAWN != -STEP_PAWN
               && arrayFigures[row +STEP_PAWN][column -STEP_PAWN] != EMPTY
               && arrayFigures[row +STEP_PAWN][column -STEP_PAWN] > MEDIANA_FIGURES)
            {
                if(arrayFigures[row +STEP_PAWN][column -STEP_PAWN] > MEDIANA_FIGURES)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row +STEP_PAWN, column -STEP_PAWN));
            }

            //black figure beat right
            if(column +STEP_PAWN != SIZE
               && arrayFigures[row +STEP_PAWN][column +STEP_PAWN] != EMPTY
               && arrayFigures[row +STEP_PAWN][column +STEP_PAWN] > MEDIANA_FIGURES)
            {
                if(arrayFigures[row +STEP_PAWN][column +STEP_PAWN] > MEDIANA_FIGURES)
                    vectorPawnBeat.push_back(getIndexThrowRowAndColumn(row +STEP_PAWN, column +STEP_PAWN));
            }
        }
    }
    return vectorPawnBeat;
}

QVector<QVariant> FigureControllers::canKnightBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorKnightBeat;
    int getIdentifierFigure = 0;
    int indexThrowRowAndColumn = 0;
    //UP
    //row up 2 and left 1
    if(row -LONG_STEP_KNIGHT >= EMPTY && row -LONG_STEP_KNIGHT < SIZE &&
            column -SHORT_STEP_KNIGHT >= EMPTY && column -SHORT_STEP_KNIGHT < SIZE &&
            arrayFigures[row -LONG_STEP_KNIGHT][column -SHORT_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row -LONG_STEP_KNIGHT][column -SHORT_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row -LONG_STEP_KNIGHT, column -SHORT_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }

    //row up 1 and left 2
    if(row -SHORT_STEP_KNIGHT >= EMPTY && row -SHORT_STEP_KNIGHT < SIZE &&
            column -LONG_STEP_KNIGHT >= EMPTY && column -LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row -SHORT_STEP_KNIGHT][column -LONG_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row -SHORT_STEP_KNIGHT][column -LONG_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row -SHORT_STEP_KNIGHT, column -LONG_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }

    //row up 2 and right 1
    if(row -LONG_STEP_KNIGHT >= EMPTY && row -LONG_STEP_KNIGHT < SIZE &&
            column +SHORT_STEP_KNIGHT < SIZE && column +SHORT_STEP_KNIGHT >= EMPTY &&
            arrayFigures[row -LONG_STEP_KNIGHT][column +SHORT_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row -LONG_STEP_KNIGHT][column +SHORT_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row -LONG_STEP_KNIGHT, column +SHORT_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }
    //row up 1 and right 2
    if(row -SHORT_STEP_KNIGHT >= EMPTY && row -SHORT_STEP_KNIGHT < SIZE &&
            column +LONG_STEP_KNIGHT >= EMPTY && column +LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row -SHORT_STEP_KNIGHT][column +LONG_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row -SHORT_STEP_KNIGHT][column +LONG_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row -SHORT_STEP_KNIGHT, column +LONG_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }


    //DOWN
    //row down 2 and left 1
    if(row +LONG_STEP_KNIGHT >= EMPTY && row +LONG_STEP_KNIGHT < SIZE &&
            column -SHORT_STEP_KNIGHT >= EMPTY && column -SHORT_STEP_KNIGHT < SIZE &&
            arrayFigures[row +LONG_STEP_KNIGHT][column -SHORT_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row +LONG_STEP_KNIGHT][column -SHORT_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row +LONG_STEP_KNIGHT, column -SHORT_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }
    //row down 1 and left 2
    if(row +SHORT_STEP_KNIGHT >= EMPTY && row +SHORT_STEP_KNIGHT < SIZE &&
            column -LONG_STEP_KNIGHT >= EMPTY && column -LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row +SHORT_STEP_KNIGHT][column -LONG_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row +SHORT_STEP_KNIGHT][column -LONG_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row +SHORT_STEP_KNIGHT, column -LONG_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }
    //row down 2 and right 1
    if(row +LONG_STEP_KNIGHT >= EMPTY && row +SHORT_STEP_KNIGHT < SIZE &&
            column +SHORT_STEP_KNIGHT < SIZE && column +SHORT_STEP_KNIGHT >= EMPTY &&
            arrayFigures[row +LONG_STEP_KNIGHT][column +SHORT_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row +LONG_STEP_KNIGHT][column +SHORT_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row +LONG_STEP_KNIGHT, column +SHORT_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }
    //row down 1 and right 2
    if(row +SHORT_STEP_KNIGHT >= EMPTY && row +SHORT_STEP_KNIGHT < SIZE &&
            column +LONG_STEP_KNIGHT >= EMPTY && column +LONG_STEP_KNIGHT < SIZE &&
            arrayFigures[row +SHORT_STEP_KNIGHT][column +LONG_STEP_KNIGHT] != EMPTY)
    {
        getIdentifierFigure = arrayFigures[row +SHORT_STEP_KNIGHT][column +LONG_STEP_KNIGHT];
        indexThrowRowAndColumn = getIndexThrowRowAndColumn(row +SHORT_STEP_KNIGHT, column +LONG_STEP_KNIGHT);
        if(isWhite && getIdentifierFigure < MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
        else if(!isWhite && getIdentifierFigure > MEDIANA_FIGURES)
            vectorKnightBeat.push_back(indexThrowRowAndColumn);
    }

    return vectorKnightBeat;
}

QVector<QVariant> FigureControllers::canRookBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorRookBeat;

    //beat up
    for(int nextUpBeat = 1; nextUpBeat < SIZE; nextUpBeat++){
        int identifireNextUpFigure = arrayFigures[row -nextUpBeat][column];
        if(identifireNextUpFigure == EMPTY && row -nextUpBeat >= EMPTY)
            continue;


        if(identifireNextUpFigure != EMPTY && row -nextUpBeat >= EMPTY){
            bool nextFigureEnemyBlack = identifireNextUpFigure < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;
            if(isWhite && nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row -nextUpBeat, column));
                break;
            }
            else if(!isWhite && !nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row -nextUpBeat, column));
                break;
            }
        }
    }
    //beat down
    for(int nextDownBeat = 1; nextDownBeat < SIZE; nextDownBeat++){
        int identifireNextDownFigure = arrayFigures[row +nextDownBeat][column];
        if(identifireNextDownFigure == EMPTY && row +nextDownBeat < SIZE)
            continue;

        if(identifireNextDownFigure != EMPTY && row +nextDownBeat < SIZE){
            bool nextFigureEnemyBlack = identifireNextDownFigure < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row +nextDownBeat, column));
                break;
            }
            else if(!isWhite && !nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row +nextDownBeat, column));
                break;
            }
        }

    }
    //beat left
    for(int nextLeftBeat = 1; nextLeftBeat < SIZE; nextLeftBeat++){
        int identifireFigureNextLeft = arrayFigures[row][column -nextLeftBeat];
        if(identifireFigureNextLeft == EMPTY && column -nextLeftBeat >= EMPTY)
            continue;

        if(identifireFigureNextLeft != EMPTY && column -nextLeftBeat >= EMPTY){
            bool nextFigureEnemyBlack = identifireFigureNextLeft < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row, column -nextLeftBeat));
                break;
            }
            else if(!isWhite && !nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row, column -nextLeftBeat));
                break;
            }
        }
    }

    //beat right
    for(int nextRightBeat = 1; nextRightBeat < SIZE; nextRightBeat++){
        int identifireFigureNextRight = arrayFigures[row][column +nextRightBeat];
        if(identifireFigureNextRight == EMPTY && column + nextRightBeat < SIZE)
            continue;

        if(identifireFigureNextRight != EMPTY && column +nextRightBeat < SIZE){
            bool nextFigureEnemyBlack = identifireFigureNextRight < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row, column +nextRightBeat));
                break;
            }
            else if(!isWhite && !nextFigureEnemyBlack){
                vectorRookBeat.push_back(getIndexThrowRowAndColumn(row, column +nextRightBeat));
                break;
            }
        }
    }

    return vectorRookBeat;
}

QVector<QVariant> FigureControllers::canBishopBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorBishopBeat;
    //UP AND LEFT
    for(int stepToUpAndLeft = 1; stepToUpAndLeft < SIZE; stepToUpAndLeft++){
        int identifireNextUpAndLeftBeatFigure = arrayFigures[row -stepToUpAndLeft][column -stepToUpAndLeft];
        if((identifireNextUpAndLeftBeatFigure == EMPTY) && (row -stepToUpAndLeft >= EMPTY) && (column -stepToUpAndLeft >= EMPTY))
            continue;
        if((identifireNextUpAndLeftBeatFigure != EMPTY) && (row -stepToUpAndLeft >= EMPTY) && (column -stepToUpAndLeft >= EMPTY))
        {
            bool nextFigureEnemyBlack = identifireNextUpAndLeftBeatFigure < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row -stepToUpAndLeft, column -stepToUpAndLeft));
                break;
            }
            else if(!isWhite && !nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row -stepToUpAndLeft, column -stepToUpAndLeft));
                break;
            }
        }
    }

    //UP AND RIGHT
    for(int stepToUpAndRight = 1; stepToUpAndRight < SIZE; stepToUpAndRight++){
        int identifireNextUpAndRightBeatFigure = arrayFigures[row -stepToUpAndRight][column +stepToUpAndRight];
        if((identifireNextUpAndRightBeatFigure == EMPTY) && (row -stepToUpAndRight >= EMPTY) && (column +stepToUpAndRight < SIZE))
            continue;

        if((identifireNextUpAndRightBeatFigure != EMPTY) && (row -stepToUpAndRight >= EMPTY) && (column +stepToUpAndRight < SIZE)){
            bool nextFigureEnemyBlack = identifireNextUpAndRightBeatFigure < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row -stepToUpAndRight, column +stepToUpAndRight));
                break;
            }
            else if(!isWhite && !nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row -stepToUpAndRight, column +stepToUpAndRight));
                break;
            }
        }
    }

    //DOWN AND LEFT
    for(int stepToDownAndLeft = 1; stepToDownAndLeft < SIZE; stepToDownAndLeft++){
        int identifireNextDownAndLeftBeatFigure = arrayFigures[row +stepToDownAndLeft][column -stepToDownAndLeft];
        if((identifireNextDownAndLeftBeatFigure == EMPTY) && (row +stepToDownAndLeft < SIZE) && (column -stepToDownAndLeft >= EMPTY))
            continue;
        if((identifireNextDownAndLeftBeatFigure != EMPTY) && (row +stepToDownAndLeft < SIZE) && (column -stepToDownAndLeft >= EMPTY))
        {
            bool nextFigureEnemyBlack = identifireNextDownAndLeftBeatFigure < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row +stepToDownAndLeft, column -stepToDownAndLeft));
                break;
            }else if(!isWhite && !nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row +stepToDownAndLeft, column -stepToDownAndLeft));
                break;
            }
        }
    }

    //DOWN AND RIGHT
    for(int stepToDownAndRight = 1; stepToDownAndRight < SIZE; stepToDownAndRight++){
        int identifireNextDownAndRightBeatFigure = arrayFigures[row +stepToDownAndRight][column +stepToDownAndRight];
        if((identifireNextDownAndRightBeatFigure == EMPTY) && (row +stepToDownAndRight < SIZE) && (column +stepToDownAndRight < SIZE))
            continue;
        if((identifireNextDownAndRightBeatFigure != EMPTY) && (row +stepToDownAndRight < SIZE) && (column +stepToDownAndRight < SIZE))
        {
            bool nextFigureEnemyBlack = identifireNextDownAndRightBeatFigure < MEDIANA_FIGURES;
            if((!nextFigureEnemyBlack && isWhite) || (nextFigureEnemyBlack && !isWhite))
                break;

            if(isWhite && nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row +stepToDownAndRight, column +stepToDownAndRight));
                break;
            }else if(!isWhite && !nextFigureEnemyBlack){
                vectorBishopBeat.push_back(getIndexThrowRowAndColumn(row +stepToDownAndRight, column +stepToDownAndRight));
                break;
            }
        }
    }


    return vectorBishopBeat;
}

QVector<QVariant> FigureControllers::canQueenBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorQueenBeat;

    vectorQueenBeat.append(canRookBeat(isWhite, row, column));
    vectorQueenBeat.append(canBishopBeat(isWhite, row, column));

    return vectorQueenBeat;
}

QVector<QVariant> FigureControllers::canKingBeat(bool isWhite, int row, int column)
{
    QVector<QVariant> vectorKingBeat;
    //only up
    if(arrayFigures[row -STEP_KING][column] != EMPTY && (row -STEP_KING >= EMPTY)){
        if(arrayFigures[row -STEP_KING][column] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column));
        if(arrayFigures[row -STEP_KING][column] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column));
    }

    //up and left
    if((arrayFigures[row -STEP_KING][column -STEP_KING] != EMPTY) && (row -STEP_KING >= EMPTY) && (column -STEP_KING >= EMPTY)){
        if(arrayFigures[row -STEP_KING][column -STEP_KING] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column -STEP_KING));
        if(arrayFigures[row -STEP_KING][column -STEP_KING] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column -STEP_KING));
    }

    //up and right
    if((arrayFigures[row -STEP_KING][column +STEP_KING] != EMPTY) && (row -STEP_KING >= EMPTY) && (column +STEP_KING < SIZE)){
        if(arrayFigures[row -STEP_KING][column +STEP_KING] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column +STEP_KING));
        if(arrayFigures[row -STEP_KING][column +STEP_KING] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row -STEP_KING, column +STEP_KING));
    }

    //only left
    if((arrayFigures[row][column -STEP_KING] != EMPTY) && (column -STEP_KING >=EMPTY)){
        if(arrayFigures[row][column -STEP_KING] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row, column -STEP_KING));
        if(arrayFigures[row][column -STEP_KING] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row, column -STEP_KING));
    }
    //only right
    if((arrayFigures[row][column +STEP_KING] != EMPTY) && (column +STEP_KING < SIZE)){
        if(arrayFigures[row][column +STEP_KING] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row, column +STEP_KING));
        if(arrayFigures[row][column +STEP_KING] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row, column +STEP_KING));
    }

    //only down
    if((arrayFigures[row +STEP_KING][column] != EMPTY) && (row +STEP_KING) < SIZE){
        if(arrayFigures[row +STEP_KING][column] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column));
        if(arrayFigures[row +STEP_KING][column] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column));
    }

    //left down
    if((arrayFigures[row +STEP_KING][column -STEP_KING] != EMPTY) && (row +STEP_KING < SIZE) && (column -STEP_KING >= EMPTY)){
        if(arrayFigures[row +STEP_KING][column -STEP_KING] > MEDIANA_FIGURES && !isWhite)
             vectorKingBeat.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column -STEP_KING));
        if(arrayFigures[row +STEP_KING][column -STEP_KING] < MEDIANA_FIGURES && isWhite)
             vectorKingBeat.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column -STEP_KING));
    }

    //right down
    if((arrayFigures[row +STEP_KING][column +STEP_KING] != EMPTY) && (row +STEP_KING < SIZE) && (column +STEP_KING < SIZE)){
        if(arrayFigures[row +STEP_KING][column +STEP_KING] > MEDIANA_FIGURES && !isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column +STEP_KING));
        if(arrayFigures[row +STEP_KING][column +STEP_KING] < MEDIANA_FIGURES && isWhite)
            vectorKingBeat.push_back(getIndexThrowRowAndColumn(row +STEP_KING, column +STEP_KING));
    }


    return vectorKingBeat;
}

void FigureControllers::printArray()
{
    for(int i = EMPTY; i < SIZE; i++){
        QString str;
        for(int j = EMPTY; j < SIZE; j++){
            int figure  = arrayFigures[i][j];
            if(figure == EMPTY)
                str.append("[--] ");
            if(figure == BLACK_PAWN)
                str.append("[BP] ");
            if(figure == WHITE_PAWN)
                str.append("[WP] ");
            if(figure == BLACK_ROOK)
                str.append("[BR] ");
            if(figure == WHITE_ROOK)
                str.append("[WR] ");
            if(figure == BLACK_KNIGHT)
                str.append("[BK] ");
            if(figure == WHITE_KNIGHT)
                str.append("[WK] ");
            if(figure == BLACK_BISHOP)
                str.append("[BB] ");
            if(figure == WHITE_BISHOP)
                str.append("[WB] ");
            if(figure == BLACK_QUEEN)
                str.append("[BQ] ");
            if(figure == WHITE_QUEEN)
                str.append("[WQ] ");
            if(figure == BLACK_KING)
                str.append("[BK] ");
            if(figure == WHITE_KING)
                str.append("[WK] ");
        }
        qDebug() << str;
    }
}
