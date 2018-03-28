#ifndef FIGURECONTROLLERS_H
#define FIGURECONTROLLERS_H

#include <QObject>
#include <QVector>
#include <QVariant>

#define SIZE 8
#define EMPTY 0
#define STEP_PAWN 1
#define DOUBLE_STEP_PAWN 2
#define MEDIANA_FIGURES 200

class FigureControllers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList moveList READ moveList WRITE setMoveList NOTIFY moveListChanged)
    Q_PROPERTY(QVariantList beatList READ beatList WRITE setBeatList NOTIFY beatListChanged)

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

public slots:
    void setMoveList(QVariantList moveList);
    void setBeatList(QVariantList beatList);

signals:
    void possibleChessMove(QVector<QVariant> listMove);
    void possibleChessBeat(int index, QVector<QVariant> listBeat);
    void moveListChanged(QVariantList moveList);
    void beatListChanged(QVariantList beatList);
    void commandMoveToIndex(int moveFromIndex, int moveToIndex);
    void commandBeat(int beatFrom, int beatTo);

private:
    QVector<QVariant> movePawn(bool isWhite, int row, int column);
    QVector<QVariant> canPawnBeat(bool isWhite, int row, int column);
    QVariantList m_moveList;
    QVariantList m_beatList;

    int selectedIndexFigure;
    int selectedFigure;
    bool firstStepBlack, firstStepWhite;
    bool isNextStepWhite;
    int arrayFigures[SIZE][SIZE];

    void fillArray();    
    int getIndexThrowRowAndColumn(int row, int column);
    void printArray();
};

#endif // FIGURECONTROLLERS_H
