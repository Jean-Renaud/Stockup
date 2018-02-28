#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSql>
#include <QtDebug>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_button_Create_clicked();


private slots:



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
