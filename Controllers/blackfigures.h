#ifndef BLACKFIGURES_H
#define BLACKFIGURES_H

#include <QObject>
#include "figure.h"
#define SIZE 8
class BlackFigures : public QObject
{
    Q_OBJECT
public:
    explicit BlackFigures(QObject *parent = 0);

signals:

public slots:

private:
    void fillArrayWhiteFigures();
    int arrayWhiteFigure[SIZE][SIZE];

};

#endif // BLACKFIGURES_H
