#ifndef WHITEFIGURES_H
#define WHITEFIGURES_H

#include <QObject>
#include "figure.h"
#define SIZE 8
class WhiteFigures : public QObject
{
    Q_OBJECT
public:
    explicit WhiteFigures(QObject *parent = 0);

signals:

public slots:

private:
    void fillArrayWhiteFigures();
    int arrayWhiteFigure[SIZE][SIZE];

};

#endif // WHITEFIGURES_H
