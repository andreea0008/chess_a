#ifndef FIGURECONTROLLERS_H
#define FIGURECONTROLLERS_H

#include <QObject>
#include <QVector>
#include <QVariant>

#define SIZE 8
class FigureControllers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList moveList READ moveList WRITE setMoveList NOTIFY moveListChanged)
    Q_PROPERTY(QVariantList beatList READ beatList WRITE setBeatList NOTIFY beatListChanged)
public:
    explicit FigureControllers(QObject *parent = 0);

    Q_INVOKABLE QString getPathToIconByIndex(int index);
    Q_INVOKABLE void getFigureByIndex(int index);
    QVariantList moveList() const;
    QVariantList beatList() const;

    bool isCommandMove(int index);
    bool isCommandBeat(int index);

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
    int arrayFigures[SIZE][SIZE];
    void fillArray();
    int getIndexThrowRowAndColumn(int row, int column);
    QVector<QVariant> movePawn(bool isWhite, int row, int column);
    QVector<QVariant> canPawnBeat(bool isWhite, int row, int column);

    QVariantList m_moveList;
    QVariantList m_beatList;

    int selectedIndexFigure;
    int selectedFigure;

    bool firstStepBlack, firstStepWhite;

    bool isNextStepWhite;
};

#endif // FIGURECONTROLLERS_H
