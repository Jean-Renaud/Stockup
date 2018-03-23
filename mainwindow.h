#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainwindow.h"
#include "utilisateur.h"
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

    void moveToTab(int);
    void disableTab(int);

    Utilisateur * carriste;

    Utilisateur * modifier;



public slots:


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

    void on_fournisseur_clicked();

    void on_voirStock_clicked();

    void on_majFournisseur_clicked();

    void on_suppFournisseur_clicked();

    void on_chercheUtilisateur_clicked();

    void on_gestionUtilisateur_activated(const QModelIndex &index);

    void on_majUtilisateur_clicked();

    void on_suppUtilisateur_clicked();

    void on_triAlphaUtilisateur_clicked();

    void on_triAlphaFournisseur_clicked();

    void disableFormCarriste();

    void disableFormQualite();


    void on_creerReferenceBtn_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H


