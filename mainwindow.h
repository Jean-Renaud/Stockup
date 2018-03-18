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



    void on_search_Database_clicked();

    void on_search_Location_clicked();

    void on_listDatabase_activated(const QModelIndex &index);

    void on_update_row_clicked();

    void on_deleteProduct_clicked();

    void on_searchNameProduct_clicked();

    void on_createUser_clicked();

    void on_creerFournisseur_clicked();

    void on_listProvider_activated(const QModelIndex &index);

    //void on_pushButton_clicked();

    //void on_cherchefournisseur_2_clicked();



    void on_fournisseur_clicked();

    void on_majfournisseur_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
