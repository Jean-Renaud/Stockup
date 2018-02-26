#include "mainwindow.h"
#include <QApplication>
#include "database.h"
#include <QtSql/QSql>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    database bdd;
       bdd.openDatabase();

       bdd.executeQuery("CREATE TABLE IF NOT EXISTS produits (nom TEXT, prix FLOAT, qtevendue INT)");
       /*bdd.insertProduit("Banane", 1.3, 10);
       bdd.insertProduit("Avocat", 2.5, 1);
       bdd.insertProduit("Tomate", 1., 666);*/
    w.show();

    return a.exec();
}
