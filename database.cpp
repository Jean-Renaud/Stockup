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

    if(connOpen())
    {
         QSqlQuery createTable(stockup);




         createTable.exec("create table if not exists 'users' ('id' INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "'id_login' INTEGER NOT NULL,"
                                       " 'password' INTEGER NOT NULL,"
                                       "'name' TEXT NOT NULL,"
                                       "'first_name' TEXT NOT NULL,"
                                       "'userGroup' INTEGER NOT NULL"
                                       ");");


        createTable.exec("CREATE TABLE product ("
                         "id_Product INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "reference TEXT NOT NULL,"
                         "date TEXT NOT NULL,"
                         "hour TEXT NOT NULL,"
                         "location TEXT NOT NULL,"
                         "packaging TEXT NOT NULL,"
                         "quantity TEXT NOT NULL,"
                         "state TEXT NOT NULL,"
                         "dluo TEXT NOT NULL,"
                         "lot TEXT NOT NULL,"
                         "pattern TEXT NOT NULL"
                         ");");
    }
    else
    {
         QMessageBox::information(this,tr("Erreur"),tr("La connexion avec la base de donnée à échouée."));
    }
    connClose();

}

void database::insertProductValue(QString reference, QString date, QString hour, QString location, QString packaging, QString quantity, QString state, QString dluo, QString lot, QString pattern)
{
    connOpen();
    QSqlQuery Insert_Product;
    Insert_Product.prepare("INSERT INTO product (reference, date, hour, location, packaging, quantity, state, dluo, lot, pattern) VALUES (:reference, :date, :hour, :location, :packaging, :quantity, :state, :dluo, :lot, :pattern)");
    Insert_Product.bindValue(":reference",reference);
    Insert_Product.bindValue(":date",date);
    Insert_Product.bindValue(":hour",hour);
    Insert_Product.bindValue(":location",location);
    Insert_Product.bindValue(":packaging",packaging);
    Insert_Product.bindValue(":quantity",quantity);
    Insert_Product.bindValue(":state",state);
    Insert_Product.bindValue(":dluo",dluo);
    Insert_Product.bindValue(":lot",lot);
    Insert_Product.bindValue(":pattern",pattern);

   if(Insert_Product.exec())
   {

       QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));

   }

 connClose();


}

void database::searchReference(QString searchRef)
{
    connOpen();
    QSqlQuery search;
    search.prepare("SELECT * FROM product WHERE reference = :searchRef");
    search.bindValue(":searchRef",searchRef);
    if(!search.exec())
    {
        qDebug() << ("Erreur");
    }
    connClose();



}
void database::updateReference(QString rowid, QString ref, QString date2, QString loc, QString pack, QString quant, QString state2, QString dluo2, QString lot2, QString pattern2)

{

    connOpen();
    QSqlQuery Update_Product;
    Update_Product.prepare("UPDATE product SET rowid = '"+rowid+"', reference = '"+ref+"', date = '"+date2+"', location = '"+loc+"', packaging = '"+pack+"', quantity = '"+quant+"', state = '"+state2+"', dluo = '"+dluo2+"', lot = '"+lot2+"', pattern = '"+pattern2+"' WHERE rowid='"+rowid+"'");

    if(!Update_Product.exec())
    {
        QMessageBox::critical(this,tr("ERREUR"),tr("ERREUR."));

    }
    else
    {
        QMessageBox::information(this,tr("Succès"),tr("La modification du produit a bien été effectuée."));

    }
connClose();


}
void database::deleteReference(QString deleteP)
{

    database base30;
    base30.connOpen();
    QSqlQuery Delete_Product;
    Delete_Product.prepare("DELETE FROM product WHERE id_Product='"+deleteP+"'");
    Delete_Product.exec();
}
