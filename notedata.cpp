#include "notedata.h"
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

NoteData::NoteData(QObject *parent) :
        QObject(parent),db_connected(false)
{
}

void NoteData::DbConnect()
{
    QSettings setter("hoolai-note","note");
    QString host=setter.value("hostname").toString();
    QString dataname=setter.value("dataname").toString();
    QString username=setter.value("username").toString();
    QString password=setter.value("password").toString();
    int port=setter.value("port");
    if(host.isEmpty() || dataname.isEmpty() ||
       username.isEmpty() || password.isEmpty())
    {
        emit StatusChanged(tr("plase setting"));
        emit DatabaseSetting();
        return;
    }
    emit StatusChanged(tr("connecting..."));
    db_connected=false;
    QSqlDatabase db=QSqlDatabase::database("note",false);
    if(db.isValid())
    {
        db=QSqlDatabase::addDatabase("QMYSQL","note");
    }
    else
    {
        db.close();
    }
    db.setHostName(host);
    db.setPort(port);
    db.setUserName(username);
    db.setPassword(password);
    if(!db.open())
    {
        emit StatusChanged(tr("open error!"));
        emit DataError(db.lastError().text());
        return ;
    }
    db_connected=true;
    query.reset(new QSqlQuery(db));
}
bool NoteData::Query(const QString &qstr)
{
    if(!db_connected)
        return false;
    if(!query->exec(qstr))
    {
        emit DataError(query->lastError().text());
        return false;
    }

    return true;
}

void NoteData::GetNote(const int id)
{
    query->clear();
    emit StatusChanged(tr("opening..."));
    QString qstr=QString(tr("SELECT artical.id,artical.title,artical.author,artical.date,artical.content,artical.category,category.name from `artical` join `category` on artical.category=category.id where artical.id=%1")).arg(id);
    Query(qstr);
    query->next();
    QVariantMap note;
    note.insert("id",query->value(0));
    note.insert("title",query->value(1));
    note.insert("author",query->value(2));
    note.insert("date",query->value(3));
    note.insert("content",query->value(4));
    note.insert("category-id",query->value(5));
    note.insert("category-name",query->value(6));

    emit NoteContent(QVariant(note));
    emit StatusChanged(tr("done"));
}
int NoteData::AddNewNote(const QString &title, const QString &author, const int categoryId)
{
    query->clear();
    QString qstr=QString(tr("INSERT INTO `artical` (`id`,`title`,`author`,`date`,`category`) VALUES (NULL,'%1','%2',NOW(),'%3');SELECT `id`  FROM `artical` WHERE ID = @@Identity")
                         .arg(title,author).arg(categoryId));
    if(!Query(qstr))
        return -1;
    query->next();
    return query->value(0).toInt();
}
void NoteData::AddNewCategory(const QString &category)
{
    query->clear();
    QString qstr=QString(tr("INSERT INTO `category` (`id`,`name`) VALUES (NULL,'%1')")).arg(category);
    if(!Query(qstr))
        return;

    emit StatusChanged(tr("category added"));
}
void NoteData::SaveNote(const int id, const QString &title, const QString &author, const int categoryId, const QString &content)
{
    query->clear();
    QString _content(content);
    _content.replace(QRegExp("([\"\'\\\\])"),"\\\\1");
    QString qstr=QString(tr("UPDATE `artical` SET `title`='%1',`author`='%2',`date`=NOW(),`content`='%3',`category`='%4' WHERE (`id`='%5')")
                         ).arg(title,author,_content).arg(categoryId).arg(id);
    if(!Query(qstr))
    {
        emit StatusChanged(tr("save error"));
        return;
    }

    emit StatusChanged(tr("saved"));
}
void NoteData::DeleteNote(const int id)
{
    query->clear();
    QString qstr=QString(tr("DELETE FROM `artical` WHERE (`id`='%1')")).arg(id);
    if(!Query(qstr))
    {
        emit StatusChanged(tr("delete error"));
        return;
    }

    emit StatusChanged(tr("delete done"));
}
void NoteData::GetTitleList()
{
    query->clear();
    QString qstr=QString(tr("SELECT artical.id,artical.title,artical.author,artical.date,artical.category,category.name from `artical` join `category` on artical.category=category.id"));
    if(!Query(qstr))
        return;
    QVariantList titles;
    while(query->next())
    {
        QVariantMap tit;
        tit.insert("id",query->value(0));
        tit.insert("title",query->value(1));
        tit.insert("author",query->value(2));
        tit.insert("date",query->value(3));
        tit.insert("category-id",query->value(4));
        tit.insert("category-name",query->value(5));
        titles.append(QVariant(tit));
    }
    emit TitleList(QVariant(titles));
}
void NoteData::GetCategoryList()
{
    query->clear();
    QString qstr(tr("select * from category"));
    if(!Query(qstr))
        return;
    QVariantList categorys;
    while(query->next())
    {
        QVariantMap cate;
        cate.insert("category-id",query->value(0));
        cate.insert("category-name",query->value(1));
        categorys.append(QVariant(cate));
    }
    emit CategoryList(QVariant(categorys));
}
