#include "mainwindow.h"
#include "notedata.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    data=new NoteData(this);
    connect(data,SIGNAL(DataError(QString)),this,SLOT(ErrorMessage(QString)));
    data->DbConnect();
}

MainWindow::~MainWindow()
{

}
void MainWindow::OpenNewNote(const QVariant &note)
{

}

void MainWindow::ErrorMessage(const QString &str)
{
    QMessageBox box(this);
    box.setText(str);
    box.exec();
}
