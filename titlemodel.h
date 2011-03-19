#ifndef TITLEMODEL_H
#define TITLEMODEL_H

#include <QAbstractItemModel>
//#include <QVariantList>

class TitleModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TitleModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool removeRow(int row, const QModelIndex &parent);
//    bool removeRows(int row, int count, const QModelIndex &parent);
    QModelIndex parent(const QModelIndex &child) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;

signals:
    void RowRemoved(int id);
public slots:
    void InitData(const QVariant & list);
private:
    QVariantList titleList;
};

#endif // TITLEMODEL_H
