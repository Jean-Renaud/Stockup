#include "database.h"
#include <iostream>
#include <QMessageBox>

database::database()
{
    //ctor

}

database::~database()
{
    //dtor
}

void database::createTable()
{
    //Creation de la table

    QSqlQuery createTable;
    QSqlDatabase stockup = QSqlDatabase::addDatabase("QSQLITE");
    stockup.setDatabaseName("C:/Users/adai03/Documents/STOCKUP/Stockup/stockup.db");
    stockup.open();
    if(stockup.open())
    {
         QSqlQuery createTable(stockup);
         createTable.exec("CREATE TABLE produit (reference_Product INTEGER);");
    }
    else
    {
         QMessageBox::information(this,tr("Erreur"),tr("La connexion avec la base de donnée à échouée."));
    }

}

void database::insertProductValue(QString reference)
{
    QSqlDatabase data;
    data.open();
    QSqlQuery Insert_Product;
    Insert_Product.prepare("INSERT INTO produit (reference_Product) VALUES (:reference)");
    Insert_Product.bindValue(":reference",reference);

   if(Insert_Product.exec())
   {

       QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));

   }

 data.close();

}

