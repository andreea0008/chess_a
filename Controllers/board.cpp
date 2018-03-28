#include "board.h"
#include <QDebug>


void Board::fillArrayBoard()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(i % 2 == 0){
                if (j %2 == 0){
                    arrayBoard[i][j] = WHITE;
                }else{
                    arrayBoard[i][j] = BLACK;
                }
            }else{
                if (j % 2 == 1){
                    arrayBoard[i][j] = WHITE;
                }else{
                    arrayBoard[i][j] = BLACK;
                }
            }
        }
    }
}

Board::Board(QObject *parent) :
    QObject(parent),
    m_widthAndHeightBoard(640),
    m_sizeChessField(widthAndHeightBoard()/SIZE)
{
    fillArrayBoard();
}

int Board::widthAndHeightBoard() const
{
    return m_widthAndHeightBoard;
}

int Board::sizeChessField() const
{
    return m_sizeChessField;
}

QString Board::getColorByIndex(int index)
{
    int row = index / SIZE;
    int column = index % SIZE;
    return arrayBoard[row][column] == 1 ? "#BDC3C7" : "#6C7A89";
}

QString Board::colorBorderSelect()
{
    return "red";
}

QString Board::colorBeat()
{
    return "#db5c4c";
}

void Board::setWidthAndHeightBoard(int widthAndHeightBoard)
{
    if (m_widthAndHeightBoard == widthAndHeightBoard)
        return;

    m_widthAndHeightBoard = widthAndHeightBoard;
    emit widthAndHeightBoardChanged(widthAndHeightBoard);
}

void Board::setSizeChessField(int sizeChessField)
{
    if (m_sizeChessField == sizeChessField)
        return;

    m_sizeChessField = sizeChessField;
    emit sizeChessFieldChanged(sizeChessField);
}
