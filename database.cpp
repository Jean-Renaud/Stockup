#include "database.h"
#include <iostream>
#include <QMessageBox>
#include <QObject>

database::database()
{
    //ctor

}

database::~database()
{
    //dtor
}

bool database::connOpen()
{

    QSqlDatabase stockup = QSqlDatabase::addDatabase("QSQLITE");
    stockup.setDatabaseName("C:/Users/adai03/Documents/STOCKUP/Stockup/stockup.db");
    if(!stockup.open())
    {
        qDebug()<<("Non connecté");
        return false;
    }
    else
    {
        qDebug()<<("Connecté");
        return true;
    }
}

void database::connClose()
{

    stockup.close();
    stockup.removeDatabase(QSqlDatabase::defaultConnection);
}

void database::createTable()
{
    //Creation de la table

    if(connOpen())
    {
         QSqlQuery createTable(stockup);




         createTable.exec("create table IF NOT EXISTS 'utilisateurs' ("
                                       "'id' INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "'Code' INTEGER NOT NULL,"
                                       "'Nom' TEXT NOT NULL,"
                                       "'Prenom' TEXT NOT NULL,"
                                       "'Mot_de_Passe' INTEGER NOT NULL,"
                                       "'Groupe' INTEGER NOT NULL"
                                       ");");


        createTable.exec("CREATE TABLE IF NOT EXISTS matieres_Premieres ("
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

        createTable.exec("CREATE TABLE IF NOT EXISTS fournisseurs ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "Code INTEGER NOT NULL,"
                         "Nom TEXT NOT NULL,"
                         "Forme_juridique TEXT NOT NULL,"
                         "Adresse TEXT NOT NULL,"
                         "Code_postal TEXT NOT NULL,"
                         "Pays TEXT NOT NULL,"
                         "Ville TEXT NOT NULL,"
                         "Telephone TEXT NOT NULL,"
                         "Siret TEXT NOT NULL,"
                         "APE TEXT NOT NULL"
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
void database::createUser(Utilisateur &employe)
{
    connOpen();
    QSqlQuery createuser;
    createuser.prepare("INSERT INTO Utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) VALUES (:code, :nom, :prenom, :mdp, :groupe);");
    createuser.bindValue(":code", employe.code);
    createuser.bindValue(":nom", employe.nom);
    createuser.bindValue(":prenom", employe.prenom);
    createuser.bindValue(":mdp", employe.mdp);
    createuser.bindValue(":groupe", employe.groupe);
    if(createuser.exec())
    {

       QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::information(this,tr("Création échouée"),tr("Nope."));


    }

  connClose();

}
