#include "database.h"
#include "produits.h"
#include "fournisseur.h"
#include <iostream>
#include <QMessageBox>
#include <QObject>
#include <QCoreApplication>

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
    stockup.setDatabaseName("C:/Users/adai03/Documents/STOCKUP/stockup.db");




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
                         "Code_fournisseur TEXT NOT NULL"
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

                       insertionUtilisateur();
    }
    else
    {
         QMessageBox::information(this,tr("Erreur"),tr("La connexion avec la base de donnée à échouée."));
    }
    connClose();

}

void database::insertProductValue(Produits &produit)
{
    connOpen();
    QSqlQuery Insert_Product;
    Insert_Product.prepare("INSERT INTO matieres_Premieres (Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Code_fournisseur) VALUES (:Reference, :Nom, :Lot, :Date, :Heure, :Emplacement, :Emballage, :Quantite, :Etat, :DLUO, :Code_fournisseur)");
    Insert_Product.bindValue(":Reference", produit.reference);
    Insert_Product.bindValue(":Nom", produit.nom);
    Insert_Product.bindValue(":Lot",produit.lot);
    Insert_Product.bindValue(":Date",produit.date);
    Insert_Product.bindValue(":Heure",produit.heure);
    Insert_Product.bindValue(":Emplacement",produit.emplacement);
    Insert_Product.bindValue(":Emballage",produit.emballage);
    Insert_Product.bindValue(":Quantite",produit.quantite);
    Insert_Product.bindValue(":Etat",produit.etat);
    Insert_Product.bindValue(":DLUO",produit.dluo);
    Insert_Product.bindValue(":Code_fournisseur",produit.codeFournisseur);

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
void database::updateReference(QString rowid, QString ref, QString name,QString lot2 , QString loc, QString pack, QString quant, QString state2, QString dluo2, QString date2, QString pattern2)

{



    connOpen();
       QSqlQuery Update_Product;
       Update_Product.prepare("UPDATE matieres_Premieres SET Reference = :ref, Nom = :name, Date = :date2, Emplacement = :loc, Emballage = :pack, Quantite = :quant, Etat = :state2, DLUO = :dluo2, Lot = :lot2, Code_fournisseur = :pattern2 WHERE id_Produit= :rowid");
       Update_Product.bindValue(":rowid", rowid);
       Update_Product.bindValue(":ref", ref);
       Update_Product.bindValue(":name", name);
       Update_Product.bindValue(":date2", date2);
       Update_Product.bindValue(":loc", loc);
       Update_Product.bindValue(":pack", pack);
       Update_Product.bindValue(":quant", quant);
       Update_Product.bindValue(":state2", state2);
       Update_Product.bindValue(":dluo2", dluo2);
       Update_Product.bindValue(":lot2", lot2);
       Update_Product.bindValue(":pattern2", pattern2);
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
void database::majUtilisateur(Utilisateur &mettreAjourUtilisateur)
{
    connOpen();
    QSqlQuery miseAjourUtilisateur;
    miseAjourUtilisateur.prepare("UPDATE utilisateurs SET Code = :code, Nom = :nom, Prenom = :prenom, Mot_de_Passe = :mdp, Groupe = :groupe WHERE id = :id");
    miseAjourUtilisateur.bindValue(":id", mettreAjourUtilisateur.id);
    miseAjourUtilisateur.bindValue(":code", mettreAjourUtilisateur.code);
    miseAjourUtilisateur.bindValue(":nom", mettreAjourUtilisateur.nom);
    miseAjourUtilisateur.bindValue(":prenom", mettreAjourUtilisateur.prenom);
    miseAjourUtilisateur.bindValue(":mdp", mettreAjourUtilisateur.mdp);
    miseAjourUtilisateur.bindValue(":groupe", mettreAjourUtilisateur.groupe);
    if(miseAjourUtilisateur.exec())
    {

       QMessageBox::information(this,tr("Mis à jour réussie"),tr("La mise à jour de l'utilisateur a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour de l'utilisateur a échouée"));


    }

    connClose();


}

void database::majProvider(Fournisseur &livreur2)
{
    connOpen();
    QSqlQuery majFournisseur;
    majFournisseur.prepare("UPDATE fournisseurs SET Code = :code, Nom = :nom, Forme_juridique = :forme_juridique, Adresse = :adresse, Code_postal = :code_postal, Pays = :pays, Ville = :ville, Telephone = :telephone, Siret = :siret, APE = :ape WHERE id = :id");
    majFournisseur.bindValue(":id", livreur2.id);
    majFournisseur.bindValue(":code", livreur2.codeDuFournisseur);
    majFournisseur.bindValue(":nom", livreur2.nomSociete);
    majFournisseur.bindValue(":forme_juridique", livreur2.formeJuridique);
    majFournisseur.bindValue(":adresse", livreur2.adresse);
    majFournisseur.bindValue(":code_postal", livreur2.codePostal);
    majFournisseur.bindValue(":pays", livreur2.pays);
    majFournisseur.bindValue(":ville", livreur2.ville);
    majFournisseur.bindValue(":telephone", livreur2.telephone);
    majFournisseur.bindValue(":siret", livreur2.siret);
    majFournisseur.bindValue(":ape", livreur2.ape);
    if(majFournisseur.exec())
    {

       QMessageBox::information(this,tr("Création réussie"),tr("La mise à jour du fournisseur a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour du fournisseur a échouée"));


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

       QMessageBox::information(this,tr("Création réussie"),tr("La création de l'utilisateur a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::information(this,tr("Création échouée"),tr("La création de l'utilisateur a échouée"));


    }

  connClose();

}
void database::createProvider(Fournisseur &livreur)
{

    connOpen();
    QSqlQuery creerFournisseur;
    creerFournisseur.prepare("INSERT INTO fournisseurs (Code, Nom, Forme_juridique, Adresse, Code_postal, Pays, Ville, Telephone, Siret, APE) VALUES (:code, :nom, :forme_juridique, :adresse, :code_postal, :pays, :ville, :telephone, :siret, :ape)");
    creerFournisseur.bindValue(":code", livreur.codeDuFournisseur);
    creerFournisseur.bindValue(":nom", livreur.nomSociete);
    creerFournisseur.bindValue(":forme_juridique", livreur.formeJuridique);
    creerFournisseur.bindValue(":adresse", livreur.adresse);
    creerFournisseur.bindValue(":code_postal", livreur.codePostal);
    creerFournisseur.bindValue(":pays", livreur.pays);
    creerFournisseur.bindValue(":ville", livreur.ville);
    creerFournisseur.bindValue(":telephone", livreur.telephone);
    creerFournisseur.bindValue(":siret", livreur.siret);
    creerFournisseur.bindValue(":ape", livreur.ape);
    if(creerFournisseur.exec())
    {

       QMessageBox::information(this,tr("Création réussie"),tr("La création du fournisseur a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::information(this,tr("Création échouée"),tr("La création du fournisseur a échouée"));


    }

    connClose();

}
void database::chercherFournisseur(QString trouverFournisseur)
{

    connOpen();
    QSqlQuery rechercherFournisseur;
    rechercherFournisseur.prepare("SELECT * FROM fournisseurs WHERE Code = :code");
    rechercherFournisseur.bindValue(":code",trouverFournisseur);
    if(!rechercherFournisseur.exec())
    {
        qDebug() << ("Erreur");
    }
    connClose();
}
void database::supFournisseur(Fournisseur &livreur3)
{
    connOpen();
    QSqlQuery supprimerFournisseur;
    supprimerFournisseur.prepare("DELETE FROM fournisseurs WHERE id = :id");
    supprimerFournisseur.bindValue(":id", livreur3.id);
    supprimerFournisseur.exec();
    connClose();
}
void database::supUtilisateur(Utilisateur &supprimerUtilisateur)
{
    connOpen();
    QSqlQuery supprimerUnUtilisateur;
    supprimerUnUtilisateur.prepare("DELETE FROM utilisateurs WHERE id = :id");
    supprimerUnUtilisateur.bindValue(":id", supprimerUtilisateur.id);
    supprimerUnUtilisateur.exec();
    connClose();

}


