#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#define SIZE 8
#define WHITE 1
#define BLACK 0

class Board : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int widthAndHeightBoard READ widthAndHeightBoard WRITE setWidthAndHeightBoard NOTIFY widthAndHeightBoardChanged)
    Q_PROPERTY(int sizeChessField READ sizeChessField WRITE setSizeChessField NOTIFY sizeChessFieldChanged)

    int m_widthAndHeightBoard;
    int m_sizeChessField;

    int arrayBoard[SIZE][SIZE];
    void fillArrayBoard();

public:
    explicit Board(QObject *parent = 0);

    int widthAndHeightBoard() const;
    int sizeChessField() const;

    Q_INVOKABLE QString getColorByIndex(int index);
    Q_INVOKABLE QString colorBeat();
    Q_INVOKABLE QString colorBorderSelect();

signals:

    void widthAndHeightBoardChanged(int widthAndHeightBoard);

    void sizeChessFieldChanged(int sizeChessField);

public slots:
    void setWidthAndHeightBoard(int widthAndHeightBoard);
    void setSizeChessField(int sizeChessField);
};

#endif // BOARD_H
