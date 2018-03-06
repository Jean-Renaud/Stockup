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




         createTable.exec("create table if not exists 'Utilisateurs' ('id' INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "'id_Utilisateur' INTEGER NOT NULL,"
                                       " 'Mot_de_Passe' INTEGER NOT NULL,"
                                       "'Nom' TEXT NOT NULL,"
                                       "'Prenom' TEXT NOT NULL,"
                                       "'Groupe' INTEGER NOT NULL"
                                       ");");


        createTable.exec("CREATE TABLE matieres_Premieres ("
                         "id_Produit INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "Reference TEXT NOT NULL,"
                         "Nom TEXT NOT NULL,"
                         "Lot TEXT NOT NULL,"
                         "Date TEXT NOT NULL,"
                         "Heure TEXT NOT NULL,"
                         "Emplacement TEXT NOT NULL,"
                         "Emballage TEXT NOT NULL,"
                         "Quantite TEXT NOT NULL,"
                         "Etat TEXT NOT NULL,"
                         "DLUO TEXT NOT NULL,"
                         "Information TEXT NOT NULL"
                         ");");
    }
    else
    {
         QMessageBox::information(this,tr("Erreur"),tr("La connexion avec la base de donnée à échouée."));
    }
    connClose();

}

void database::insertProductValue(QString Reference, QString Nom, QString Date, QString Heure, QString Emplacement, QString Emballage, QString Quantite, QString Etat, QString DLUO, QString Lot, QString Information)
{
    connOpen();
    QSqlQuery Insert_Product;
    Insert_Product.prepare("INSERT INTO matieres_Premieres (Reference, Nom, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Lot, Information) VALUES (:Reference, :Nom, :Date, :Heure, :Emplacement, :Emballage, :Quantite, :Etat, :DLUO, :Lot, :Information)");
    Insert_Product.bindValue(":Reference", Reference);
    Insert_Product.bindValue(":Nom", Nom);
    Insert_Product.bindValue(":Date",Date);
    Insert_Product.bindValue(":Heure",Heure);
    Insert_Product.bindValue(":Emplacement",Emplacement);
    Insert_Product.bindValue(":Emballage",Emballage);
    Insert_Product.bindValue(":Quantite",Quantite);
    Insert_Product.bindValue(":Etat",Etat);
    Insert_Product.bindValue(":DLUO",DLUO);
    Insert_Product.bindValue(":Lot",Lot);
    Insert_Product.bindValue(":Information",Information);

   if(Insert_Product.exec())
   {

       QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));

   }
   else
   {
       QMessageBox::critical(this,tr("Création échouée"),tr("Nope."));

   }

 connClose();


}

void database::searchReference(QString chercherReference)
{
    connOpen();
    QSqlQuery rechercher;
    rechercher.prepare("SELECT * FROM matieres_Premieres WHERE Reference = :chercherReference");
    rechercher.bindValue(":chercherReference",chercherReference);
    if(!rechercher.exec())
    {
        qDebug() << ("Erreur");
    }
    connClose();



}
void database::updateReference(QString rowid, QString ref, QString name, QString date2, QString loc, QString pack, QString quant, QString state2, QString dluo2, QString lot2, QString pattern2)

{

    connOpen();
    QSqlQuery Update_Product;
    Update_Product.prepare("UPDATE matieres_Premieres SET id_Produit = '"+rowid+"', Reference = '"+ref+"', Nom = '"+name+"', Date = '"+date2+"', Emplacement = '"+loc+"', Emballage = '"+pack+"', Quantite = '"+quant+"', Etat = '"+state2+"', DLUO = '"+dluo2+"', Lot = '"+lot2+"', Information = '"+pattern2+"' WHERE id_Produit='"+rowid+"'");

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


    connOpen();
    QSqlQuery Delete_Product;
    Delete_Product.prepare("DELETE FROM matieres_premieres WHERE id_Produit='"+deleteP+"'");
    Delete_Product.exec();
    if(!Delete_Product.exec())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("La suppression a échouée."));

    }
    else
    {
        QMessageBox::information(this,tr("Succès"),tr("La suppression du produit a bien été effectuée."));

    }
    connClose();
}
void database::searchProductName(QString searchName)
{

    connOpen();
    QSqlQuery SearchbyName;
    SearchbyName.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercherNom LIKE '%'");
    SearchbyName.bindValue(":chercherNom", searchName);
    SearchbyName.exec();
    connClose();
}
