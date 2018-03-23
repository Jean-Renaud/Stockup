#include "database.h"
#include "produits.h"
#include "fournisseur.h"
#include "qmainwindow.h"
#include "QtUiTools/QUiLoader"
#include <QMainWindow>
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
<<<<<<< HEAD
    stockup.setDatabaseName("C:/Users/adai03/Documents/STOCKUP/stockup.db");
=======
    stockup.setDatabaseName("C:/STOCKUP/stockup.db");
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7




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

<<<<<<< HEAD

void database::insertionEnBdd()
=======
void database::creerTableBdd()
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7
{
    QSqlQuery insererUtilisateur;
    insererUtilisateur.exec("SELECT COUNT (id) FROM utilisateurs");

<<<<<<< HEAD
    insererUtilisateur.next();

    int presentDansLaBdd = insererUtilisateur.value(0).toInt();
    if(presentDansLaBdd == 0)
    {


        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                                "VALUES (01, 'Admin', 'admin', 1, 1)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                                "VALUES (02, 'ResponsableLogistique', 'responsable', 2, 2)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                                "VALUES (03, 'Carriste', 'carriste', 3, 3)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                                "VALUES (04, 'LaboQualite', 'labo', 4, 4)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                               "VALUES (05, 'Root', 'superAdmin', 5, 5)");



    }
}
void database::creerTableBdd()
{
    //Creation de la table

    if(ouvertureBdd())
    {
         QSqlQuery creerTable(stockup);

         creerTable.exec("CREATE TABLE IF NOT EXISTS utilisateurs ("
=======
    if(ouvertureBdd())
    {
         QSqlQuery creerTable(stockup);

         creerTable.exec("CREATE TABLE IF NOT EXISTS 'utilisateurs' ("
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7
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

<<<<<<< HEAD
        insertionEnBdd();
=======
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7

    }
    else
    {
         QMessageBox::information(this,tr("Erreur"),tr("La connexion avec la base de donnée à échouée."));
    }
    fermetureBdd();
<<<<<<< HEAD
}

void database::creerUneReference(Produits &produit)
{
=======

}

void database::insertionEnBdd()
{
    QSqlQuery insererUtilisateur;
    insererUtilisateur.exec("SELECT COUNT (id) FROM utilisateurs");

    insererUtilisateur.next();

    int presentDansLaBdd = insererUtilisateur.value(0).toInt();
    if(presentDansLaBdd == 0)
    {


        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                       "VALUES (01, 'Admin', 'admin', 1, 1)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                       "VALUES (02, 'ResponsableLogistique', 'responsable', 2, 2)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                       "VALUES (03, 'Carriste', 'carriste', 3, 3)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                       "VALUES (04, 'LaboQualite', 'labo', 4, 4)");

        insererUtilisateur.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                               "VALUES (05, 'Root', 'superAdmin', 5, 5)");




    }
}


void database::creerUneReference(Produits &produit)
{
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7
    ouvertureBdd();
    QSqlQuery insererNouvelleReference;
    insererNouvelleReference.prepare("INSERT INTO matieres_Premieres (Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Code_fournisseur) VALUES (:Reference, :Nom, :Lot, :Date, :Heure, :Emplacement, :Emballage, :Quantite, :Etat, :DLUO, :Code_fournisseur)");
    insererNouvelleReference.bindValue(":Reference", produit.getRef());
    insererNouvelleReference.bindValue(":Nom", produit.getNom());
    insererNouvelleReference.bindValue(":Lot",produit.getLot());
    insererNouvelleReference.bindValue(":Date",produit.getDate());
    insererNouvelleReference.bindValue(":Heure",produit.getHeure());
    insererNouvelleReference.bindValue(":Emplacement",produit.getEmplacement());
    insererNouvelleReference.bindValue(":Emballage",produit.getEmballage());
    insererNouvelleReference.bindValue(":Quantite",produit.getQuantite());
    insererNouvelleReference.bindValue(":Etat",produit.getEtat());
    insererNouvelleReference.bindValue(":DLUO",produit.getDluo());
    insererNouvelleReference.bindValue(":Code_fournisseur",produit.getCodeFournisseur());

   if(insererNouvelleReference.exec())
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
    miseAjourUtilisateur.bindValue(":id", mettreAjourUtilisateur.getIdUtilisateur());
    miseAjourUtilisateur.bindValue(":code", mettreAjourUtilisateur.getCode());
    miseAjourUtilisateur.bindValue(":nom", mettreAjourUtilisateur.getNom());
    miseAjourUtilisateur.bindValue(":prenom", mettreAjourUtilisateur.getPrenom());
    miseAjourUtilisateur.bindValue(":mdp", mettreAjourUtilisateur.getMdp());
    miseAjourUtilisateur.bindValue(":groupe", mettreAjourUtilisateur.getGroupe());
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
    QSqlQuery miseAjourFournisseur;
    miseAjourFournisseur.prepare("UPDATE fournisseurs SET Code = :code, Nom = :nom, Forme_juridique = :forme_juridique, Adresse = :adresse, Code_postal = :code_postal, Pays = :pays, Ville = :ville, Telephone = :telephone, Siret = :siret, APE = :ape WHERE id = :id");
    miseAjourFournisseur.bindValue(":id", livreur2.getIdFournisseur());
    miseAjourFournisseur.bindValue(":code", livreur2.getCodeFournisseur());
    miseAjourFournisseur.bindValue(":nom", livreur2.getNomSociete());
    miseAjourFournisseur.bindValue(":forme_juridique", livreur2.getFormeJuridique());
    miseAjourFournisseur.bindValue(":adresse", livreur2.getAdresse());
    miseAjourFournisseur.bindValue(":code_postal", livreur2.getCodePostal());
    miseAjourFournisseur.bindValue(":pays", livreur2.getPays());
    miseAjourFournisseur.bindValue(":ville", livreur2.getVille());
    miseAjourFournisseur.bindValue(":telephone", livreur2.getTelephone());
    miseAjourFournisseur.bindValue(":siret", livreur2.getSiret());
    miseAjourFournisseur.bindValue(":ape", livreur2.getApe());
    if(miseAjourFournisseur.exec())
    {

       QMessageBox::information(this,tr("Création réussie"),tr("La mise à jour du fournisseur a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour du fournisseur a échouée"));


    }

    fermetureBdd();


}
void database::supprimerReference(Produits &supprimerProduit)
{
    ouvertureBdd();
    QSqlQuery supprimerLeProduit;
    supprimerLeProduit.prepare("DELETE FROM matieres_premieres WHERE id_Produit= :idProduit");
    supprimerLeProduit.bindValue(":idProduit", supprimerProduit.getId());
    if(!supprimerLeProduit.exec())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("La suppression a échouée."));

    }
    fermetureBdd();
}
void database::chercheProduitParNom(QString chercherProduitParNom)
{

    ouvertureBdd();
    QSqlQuery cherchProduitParNom;
    cherchProduitParNom.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercherNom LIKE '%'");
    cherchProduitParNom.bindValue(":chercherNom", chercherProduitParNom);
    cherchProduitParNom.exec();
    fermetureBdd();
}
void database::creerUnUtilisateur(Utilisateur &employe)
{
    ouvertureBdd();
    QSqlQuery nouvelUtilisateur;
    nouvelUtilisateur.prepare("INSERT INTO Utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) VALUES (:code, :nom, :prenom, :mdp, :groupe);");
    nouvelUtilisateur.bindValue(":code", employe.getCode());
    nouvelUtilisateur.bindValue(":nom", employe.getNom());
    nouvelUtilisateur.bindValue(":prenom", employe.getPrenom());
    nouvelUtilisateur.bindValue(":mdp", employe.getMdp());
    nouvelUtilisateur.bindValue(":groupe", employe.getGroupe());
    if(nouvelUtilisateur.exec())
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
    creerFournisseur.bindValue(":code", livreur.getCodeFournisseur());
    creerFournisseur.bindValue(":nom", livreur.getNomSociete());
    creerFournisseur.bindValue(":forme_juridique", livreur.getFormeJuridique());
    creerFournisseur.bindValue(":adresse", livreur.getAdresse());
    creerFournisseur.bindValue(":code_postal", livreur.getCodePostal());
    creerFournisseur.bindValue(":pays", livreur.getPays());
    creerFournisseur.bindValue(":ville", livreur.getVille());
    creerFournisseur.bindValue(":telephone", livreur.getTelephone());
    creerFournisseur.bindValue(":siret", livreur.getSiret());
    creerFournisseur.bindValue(":ape", livreur.getApe());
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
    supprimerFournisseur.bindValue(":id", livreur3.getIdFournisseur());
    supprimerFournisseur.exec();
    fermetureBdd();
}
void database::supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur)
{
    ouvertureBdd();
    QSqlQuery supprimerUnUtilisateur;
    supprimerUnUtilisateur.prepare("DELETE FROM utilisateurs WHERE id = :id");
    supprimerUnUtilisateur.bindValue(":id", supprimerUtilisateur.getIdUtilisateur());
    supprimerUnUtilisateur.exec();
    fermetureBdd();

}


