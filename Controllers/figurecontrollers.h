#ifndef FIGURECONTROLLERS_H
#define FIGURECONTROLLERS_H

#include <QObject>
#include <QVector>
#include <QVariant>

#define SIZE 8
#define EMPTY 0
#define STEP_PAWN 1
#define STEP_KING 1
#define DOUBLE_STEP_PAWN 2
#define SHORT_STEP_KNIGHT 1
#define LONG_STEP_KNIGHT 2
#define MEDIANA_FIGURES 200

class FigureControllers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList moveList READ moveList WRITE setMoveList NOTIFY moveListChanged)
    Q_PROPERTY(QVariantList beatList READ beatList WRITE setBeatList NOTIFY beatListChanged)
    Q_PROPERTY(bool isNextStepWhite READ isNextStepWhite WRITE setIsNextStepWhite NOTIFY isNextStepWhiteChanged)

    enum FIGURE{
        BLACK_PAWN = 111, BLACK_ROOK = 101, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING,
        WHITE_PAWN = 211, WHITE_ROOK = 201, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING
    };
public:
    explicit FigureControllers(QObject *parent = 0);

    Q_INVOKABLE QString getPathToIconByIndex(int index);
    Q_INVOKABLE void getFigureByIndex(int index);
    QVariantList moveList() const;
    QVariantList beatList() const;

    bool isCommandMove(int index) const;
    bool isCommandBeat(int index) const;    
    bool isNextStepWhite() const;

public slots:
    void setMoveList(QVariantList moveList);
    void setBeatList(QVariantList beatList);    
    void setIsNextStepWhite(bool isNextStepWhite);

signals:
    void possibleChessMove(QVector<QVariant> listMove);
    void possibleChessBeat(int index, QVector<QVariant> listBeat);
    void moveListChanged(QVariantList moveList);
    void beatListChanged(QVariantList beatList);
    void commandMoveToIndex(int moveFromIndex, int moveToIndex);
    void commandBeat(int beatFrom, int beatTo);    
    void isNextStepWhiteChanged(bool isNextStepWhite);

private:
    QVector<QVariant> movePawn(bool isWhite, int row, int column);
    QVector<QVariant> moveKnight(int row, int column);
    QVector<QVariant> moveRook(int row, int column);
    QVector<QVariant> moveBishop(int row, int column);
    QVector<QVariant> moveQueen(int row, int column);
    QVector<QVariant> moveKing(int row, int column);

    QVector<QVariant> canPawnBeat(bool isWhite, int row, int column);
    QVector<QVariant> canKnightBeat(bool isWhite, int row, int column);
    QVector<QVariant> canRookBeat(bool isWhite, int row, int column);
    QVector<QVariant> canBishopBeat(bool isWhite, int row, int column);
    QVector<QVariant> canQueenBeat(bool isWhite, int row, int column);
    QVector<QVariant> canKingBeat(bool isWhite, int row, int column);
    QVariantList m_moveList;
    QVariantList m_beatList;

    int selectedIndexFigure;
    int selectedFigure;
    bool firstStepBlack, firstStepWhite;
    int arrayFigures[SIZE][SIZE];

    void fillArray();    
    int getIndexThrowRowAndColumn(int row, int column);
    void printArray();
    bool m_isNextStepWhite;
};

#endif // FIGURECONTROLLERS_H
