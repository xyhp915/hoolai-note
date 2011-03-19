#ifndef TITLEITEM_H
#define TITLEITEM_H

#include <QStyledItemDelegate>
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QFrame)
QT_FORWARD_DECLARE_CLASS(QLabel)

class TitleItem : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TitleItem(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
signals:

public slots:
    void DeleteTitle();
private:
    QPushButton *del;
    QLabel *title;
    QFrame *frame;
};

#endif // TITLEITEM_H
