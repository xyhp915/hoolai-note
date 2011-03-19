#ifndef NOTEDATA_H
#define NOTEDATA_H

#include <QObject>
#include <QVariant>
#include <QScopedPointer>
#include <QSqlQuery>
//QT_FORWARD_DECLARE_CLASS(QSqlQuery)

class NoteData : public QObject
{
    Q_OBJECT
public:
    explicit NoteData(QObject *parent = 0);
signals:
    void DatabaseSetting();
    void NoteContent(QVariant note);
    void StatusChanged(QString str);
    void TitleList(QVariant list);
    void CategoryList(QVariant list);
    void DataError(QString str);
public slots:
    void DbConnect();
    void GetNote(const int id);
    int AddNewNote(const QString &title,const QString &author,const int categoryId);
    void AddNewCategory(const QString &category);
    void SaveNote(const int id,const QString &title,const QString &author,const int categoryId,const QString &content);
    void DeleteNote(const int id);
    void GetTitleList();
    void GetCategoryList();
private:
    bool Query(const QString &qstr);
    void CreateNoteData();
    bool db_connected;
    QScopedPointer<QSqlQuery> query;
};

#endif // NOTEDATA_H
