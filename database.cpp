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

bool database::ouvertureBdd()
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
void database::fermetureBdd()
{

    stockup.close();
    stockup.removeDatabase(QSqlDatabase::defaultConnection);
}

void database::creerTableBdd()
{
    //Creation de la table

    if(ouvertureBdd())
    {
         QSqlQuery creerTable(stockup);


         creerTable.exec("create table IF NOT EXISTS 'utilisateurs' ("
                                       "'id' INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "'Code' INTEGER NOT NULL,"
                                       "'Nom' TEXT NOT NULL,"
                                       "'Prenom' TEXT NOT NULL,"
                                       "'Mot_de_Passe' INTEGER NOT NULL,"
                                       "'Groupe' INTEGER NOT NULL"
                                       ");");

        creerTable.exec("CREATE TABLE IF NOT EXISTS matieres_Premieres ("
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

        creerTable.exec("CREATE TABLE IF NOT EXISTS fournisseurs ("
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
    fermetureBdd();

}

void database::creerUneReference(Produits &produit)
{
    ouvertureBdd();
    QSqlQuery Insert_Product;
    Insert_Product.prepare("INSERT INTO matieres_Premieres (Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Code_fournisseur) VALUES (:Reference, :Nom, :Lot, :Date, :Heure, :Emplacement, :Emballage, :Quantite, :Etat, :DLUO, :Code_fournisseur)");
    Insert_Product.bindValue(":Reference", produit.getRef());
    Insert_Product.bindValue(":Nom", produit.getNom());
    Insert_Product.bindValue(":Lot",produit.getLot());
    Insert_Product.bindValue(":Date",produit.getDate());
    Insert_Product.bindValue(":Heure",produit.getHeure());
    Insert_Product.bindValue(":Emplacement",produit.getEmplacement());
    Insert_Product.bindValue(":Emballage",produit.getEmballage());
    Insert_Product.bindValue(":Quantite",produit.getQuantite());
    Insert_Product.bindValue(":Etat",produit.getEtat());
    Insert_Product.bindValue(":DLUO",produit.getDluo());
    Insert_Product.bindValue(":Code_fournisseur",produit.getCodeFournisseur());

   if(Insert_Product.exec())
   {

       QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));

   }
   else
   {
       QMessageBox::critical(this,tr("Création échouée"),tr("Nope."));

   }

 fermetureBdd();


}
void database::miseAjourReference(QString rowid, QString referenceDuProduit, QString nomDuProduit,QString numeroLot , QString emplacement, QString emballage , QString quantite, QString etat, QString dluo, QString date, QString fournisseur)

{

    ouvertureBdd();
       QSqlQuery miseAjourProduit;
       miseAjourProduit.prepare("UPDATE matieres_Premieres SET Reference = :referenceDuProduit, Nom = :nomDuProduit, Date = :date, Emplacement = :emplacement, Emballage = :emballage, Quantite = :quantite, Etat = :etat, DLUO = :dluo, Lot = :numeroLot, Code_fournisseur = :fournisseur WHERE id_Produit= :rowid");
       miseAjourProduit.bindValue(":rowid", rowid);
       miseAjourProduit.bindValue(":referenceDuProduit", referenceDuProduit);
       miseAjourProduit.bindValue(":nomDuProduit", nomDuProduit);
       miseAjourProduit.bindValue(":date", date);
       miseAjourProduit.bindValue(":emplacement", emplacement);
       miseAjourProduit.bindValue(":emballage", emballage);
       miseAjourProduit.bindValue(":quantite", quantite);
       miseAjourProduit.bindValue(":etat", etat);
       miseAjourProduit.bindValue(":dluo", dluo);
       miseAjourProduit.bindValue(":numeroLot", numeroLot);
       miseAjourProduit.bindValue(":fournisseur", fournisseur);
       if(!miseAjourProduit.exec())
       {
           QMessageBox::critical(this,tr("ERREUR"),tr("ERREUR."));

       }
       else
       {
           QMessageBox::information(this,tr("Succès"),tr("La modification du produit a bien été effectuée."));

       }
   fermetureBdd();

}
void database::miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur)
{
    ouvertureBdd();
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

    fermetureBdd();


}

void database::miseAjourFournisseur(Fournisseur &livreur2)
{
    ouvertureBdd();
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

    fermetureBdd();


}
void database::supprimerReference(QString suppRef)
{


    ouvertureBdd();
    QSqlQuery supprimerUnProduit;
    supprimerUnProduit.prepare("DELETE FROM matieres_premieres WHERE id_Produit='"+suppRef+"'");
    supprimerUnProduit.exec();
    if(!supprimerUnProduit.exec())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("La suppression a échouée."));

    }
    fermetureBdd();
}
void database::chercheProduitParNom(QString chercherProduitParNom)
{

    ouvertureBdd();
    QSqlQuery requete;
    requete.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercherNom LIKE '%'");
    requete.bindValue(":chercherNom", chercherProduitParNom);
    requete.exec();
    fermetureBdd();
}
void database::creerUnUtilisateur(Utilisateur &employe)
{
    ouvertureBdd();
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

  fermetureBdd();

}
void database::creerUnFournisseur(Fournisseur &livreur)
{

    ouvertureBdd();
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

    fermetureBdd();

}
void database::chercherFournisseur(QString trouverFournisseur)
{

    ouvertureBdd();
    QSqlQuery rechercherFournisseur;
    rechercherFournisseur.prepare("SELECT * FROM fournisseurs WHERE Code = :code");
    rechercherFournisseur.bindValue(":code",trouverFournisseur);
    if(!rechercherFournisseur.exec())
    {
        qDebug() << ("Erreur");
    }
    fermetureBdd();
}
void database::supprimerUnFournisseur(Fournisseur &livreur3)
{
    ouvertureBdd();
    QSqlQuery supprimerFournisseur;
    supprimerFournisseur.prepare("DELETE FROM fournisseurs WHERE id = :id");
    supprimerFournisseur.bindValue(":id", livreur3.id);
    supprimerFournisseur.exec();
    fermetureBdd();
}
void database::supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur)
{
    ouvertureBdd();
    QSqlQuery supprimerUnUtilisateur;
    supprimerUnUtilisateur.prepare("DELETE FROM utilisateurs WHERE id = :id");
    supprimerUnUtilisateur.bindValue(":id", supprimerUtilisateur.id);
    supprimerUnUtilisateur.exec();
    fermetureBdd();

}


