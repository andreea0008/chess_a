#ifndef LOGOFCHESSMOVE_H
#define LOGOFCHESSMOVE_H

#include <QAbstractItemModel>
#define SIZE 8
#define COUNT_OF_CHESS_FIELD 63
class MoveChess
{
public:
    MoveChess(int id, QString descriptionMove) : m_id(id), m_descriptionMove(descriptionMove) {}

    int getId() const { return m_id; }
    QString getDescriptionMove() const { return m_descriptionMove; }

private:
    int m_id;
    QString m_descriptionMove;
};

class LogOfChessMove : public QAbstractItemModel
{
    Q_OBJECT
public:
    LogOfChessMove(QObject *object = 0);
    ~LogOfChessMove();

    enum MoveChessRoles { Id, Move };
    void roles();
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void addMove(int indexFrom, int indexTo);

private:
    QString createDescription(int indexFrom, int indexTo);
    QString getPositionByIndex(int index);
    QHash<int, QByteArray> m_roles;
    QVector<MoveChess*> m_moves;
};

#endif // LOGOFCHESSMOVE_H
