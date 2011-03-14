#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
class NoteData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void OpenNewNote(const QVariant &note);
    void OpenNote(const int id);
    void ErrorMessage(const QString &str);
private:
    NoteData *data;
};

#endif // MAINWINDOW_H
