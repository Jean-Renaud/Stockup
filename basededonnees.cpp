#include "basededonnees.h"
#include "produits.h"
#include "fournisseur.h"
#include "qmainwindow.h"
#include "mainwindow.h"
#include "QtUiTools/QUiLoader"
#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QObject>
#include <QCoreApplication>
#include <QTranslator>
#include "basededonnees.h"
#include "ui_mainwindow.h"


using namespace std;
BaseDeDonnees::BaseDeDonnees()
{
}

BaseDeDonnees::~BaseDeDonnees() {
    this->stockup.close();
    this->stockup.removeDatabase(QSqlDatabase::defaultConnection);
}

/*Insertion des éléments dans la base de donnée lors de l'installation de l'application*/
void BaseDeDonnees::insertionEnBdd()
{
    QSqlQuery insererUtilisateur(this->stockup);
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
    QSqlQuery insererProduits(this->stockup);
    insererProduits.exec("SELECT COUNT (id) FROM matieres_Premieres");

    insererProduits.next();

    int presentEnBdd = insererProduits.value(0).toInt();
    if(presentEnBdd == 0)
    {
        insererProduits.exec("INSERT INTO matieres_Premieres (id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Code_fournisseur)"
                             "VALUES(1, 'MP01', 'POIVRE', '0001A164', '01/01/2018', '11h56', 'M1BA', 25, 100, 'Conforme', '03/2019', '01')");

        insererProduits.exec("INSERT INTO matieres_Premieres (id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Code_fournisseur)"
                             "VALUES(2, 'MP02', 'CANNELLE', '0001Z256', '12/03/2018', '15h24', 'M1AL01201', 10, 30, 'Conforme', '05/2020', '03')");
    }
}

/*Création des tables lors de l'installation de l'application*/
void BaseDeDonnees::creerTableBdd()
{
    //Creation de la table
    this->stockup = QSqlDatabase::addDatabase("QSQLITE");
    stockup.setDatabaseName("./stockup.db");

     QSqlQuery creerTable(this->stockup);

     stockup.open();

     creerTable.exec("CREATE TABLE IF NOT EXISTS utilisateurs ("
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

    insertionEnBdd();
}

/*Envoi et enregistrement en base de donnée d'un nouveau produit*/
bool BaseDeDonnees::creerUneReference(Produits &produit)
{
    QSqlQuery insererNouvelleReference(this->stockup);
    insererNouvelleReference.prepare("INSERT INTO matieres_Premieres (Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, "
                                     "Quantite, Etat, DLUO, Code_fournisseur) VALUES (:Reference, :Nom, :Lot, :Date, :Heure, "
                                     ":Emplacement, :Emballage, :Quantite, :Etat, :DLUO, :Code_fournisseur)");
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

    return insererNouvelleReference.exec();
}

/*Permet d'effectuer la recherche d'un produit en stock avec sa référence*/
void BaseDeDonnees::chercherParReference(QSqlQueryModel *modelChercherParReference, QString searchRef)
{
    QSqlQuery listRef;
    listRef.prepare("SELECT id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite,"
                    " SUM(Emballage * Quantite) AS 'Quantite Totale', Etat, DLUO, Code_fournisseur FROM matieres_Premieres WHERE Reference = :reference");

    listRef.bindValue(":reference",searchRef);
    listRef.exec();
    modelChercherParReference->setQuery(listRef);
}

/*Permet de chercher un produit par emplacement*/
void BaseDeDonnees::chercherProduitParEmplacement(QSqlQueryModel *modelChercherProduitEmplacement, QString rechercheEmplacement)
{
    QSqlQuery chercheParEmplacement;
    chercheParEmplacement.prepare("SELECT * FROM matieres_Premieres WHERE Emplacement = :location");
    chercheParEmplacement.bindValue(":location",rechercheEmplacement);
    chercheParEmplacement.exec();
    modelChercherProduitEmplacement->setQuery(chercheParEmplacement);
}

/*Permet de chercher un produit avec son nom*/
void BaseDeDonnees::chercherProduitParNom(QSqlQueryModel *modelchercherProduitParNom, QString chercherProduitParnom)
{
    QSqlQuery listeRechercheNomProduit;
    listeRechercheNomProduit.prepare("SELECT id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite,"
                                     " SUM(Emballage * Quantite) AS 'Quantite Totale', Etat, DLUO, Code_fournisseur FROM matieres_Premieres "
                                     "WHERE Nom LIKE :chercherProduitParnom");
    listeRechercheNomProduit.bindValue(":chercherProduitParnom", chercherProduitParnom + '%');
    listeRechercheNomProduit.exec();
   /* while(listeRechercheNomProduit.next()) {
        qDebug() << "Il y a un résultat";
        qDebug() << listeRechercheNomProduit.value(0).toInt();
    }*/
    modelchercherProduitParNom->setQuery(listeRechercheNomProduit);
}

/*Envoi et enregistrement des nouvelles informations lors de la mise à jour d'un produit*/
bool BaseDeDonnees::miseAjourReference(Produits &MettreAjourProduit)
{
       QSqlQuery miseAjourProduit(this->stockup);
       miseAjourProduit.prepare("UPDATE matieres_Premieres SET id_Produit = :rowid, Reference = :referenceDuProduit, Nom = :nomDuProduit, Date = :date,"
                                "Emplacement = :emplacement, Emballage = :emballage, Quantite = :quantite, Etat = :etat, "
                                "DLUO = :dluo, Lot = :numeroLot, Code_fournisseur = :fournisseur WHERE id_Produit= :rowid");
       miseAjourProduit.bindValue(":rowid", MettreAjourProduit.getId());
       miseAjourProduit.bindValue(":referenceDuProduit", MettreAjourProduit.getRef());
       miseAjourProduit.bindValue(":nomDuProduit", MettreAjourProduit.getNom());
       miseAjourProduit.bindValue(":numeroLot", MettreAjourProduit.getLot());
       miseAjourProduit.bindValue(":date", MettreAjourProduit.getDate());
       miseAjourProduit.bindValue(":emplacement", MettreAjourProduit.getEmplacement());
       miseAjourProduit.bindValue(":emballage", MettreAjourProduit.getEmballage());
       miseAjourProduit.bindValue(":quantite", MettreAjourProduit.getQuantite());
       miseAjourProduit.bindValue(":etat", MettreAjourProduit.getEtat());
       miseAjourProduit.bindValue(":dluo", MettreAjourProduit.getDluo());
       miseAjourProduit.bindValue(":fournisseur", MettreAjourProduit.getCodeFournisseur());

       return miseAjourProduit.exec();
}

/*Permet de mettre à jour un utilisateur*/
bool BaseDeDonnees::miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur)
{
    QSqlQuery miseAjourUtilisateur;
    miseAjourUtilisateur.prepare("UPDATE utilisateurs SET Code = :code, Nom = :nom, Prenom = :prenom, "
                                 "Mot_de_Passe = :mdp, Groupe = :groupe WHERE id = :id");
    miseAjourUtilisateur.bindValue(":id", mettreAjourUtilisateur.getIdUtilisateur());
    miseAjourUtilisateur.bindValue(":code", mettreAjourUtilisateur.getCode());
    miseAjourUtilisateur.bindValue(":nom", mettreAjourUtilisateur.getNom());
    miseAjourUtilisateur.bindValue(":prenom", mettreAjourUtilisateur.getPrenom());
    miseAjourUtilisateur.bindValue(":mdp", mettreAjourUtilisateur.getMdp());
    miseAjourUtilisateur.bindValue(":groupe", mettreAjourUtilisateur.getGroupe());

    return miseAjourUtilisateur.exec();
}

/*Permet de mettre à jour un fournisseur*/
bool BaseDeDonnees::miseAjourFournisseur(Fournisseur &mettreAjourFournisseur)
{
    QSqlQuery miseAjourFournisseur(this->stockup);
    miseAjourFournisseur.prepare("UPDATE fournisseurs SET Code = :code, Nom = :nom, Forme_juridique = :forme_juridique, "
                                 "Adresse = :adresse, Code_postal = :code_postal, Ville = :ville, Pays = :pays, "
                                 "Telephone = :telephone, Siret = :siret, APE = :ape WHERE id = :id");
    miseAjourFournisseur.bindValue(":id", mettreAjourFournisseur.getIdFournisseur());
    miseAjourFournisseur.bindValue(":code", mettreAjourFournisseur.getCodeFournisseur());
    miseAjourFournisseur.bindValue(":nom", mettreAjourFournisseur.getNomSociete());
    miseAjourFournisseur.bindValue(":forme_juridique", mettreAjourFournisseur.getFormeJuridique());
    miseAjourFournisseur.bindValue(":adresse", mettreAjourFournisseur.getAdresse());
    miseAjourFournisseur.bindValue(":code_postal", mettreAjourFournisseur.getCodePostal());
    miseAjourFournisseur.bindValue(":pays", mettreAjourFournisseur.getPays());
    miseAjourFournisseur.bindValue(":ville", mettreAjourFournisseur.getVille());
    miseAjourFournisseur.bindValue(":telephone", mettreAjourFournisseur.getTelephone());
    miseAjourFournisseur.bindValue(":siret", mettreAjourFournisseur.getSiret());
    miseAjourFournisseur.bindValue(":ape", mettreAjourFournisseur.getApe());

    return miseAjourFournisseur.exec();

}

/*Permet de supprimer une référence*/
bool BaseDeDonnees::supprimerReference(Produits &supprimerProduit)
{
    QSqlQuery supprimerLeProduit(this->stockup);
    supprimerLeProduit.prepare("DELETE FROM matieres_premieres WHERE id_Produit= :idProduit");
    supprimerLeProduit.bindValue(":idProduit", supprimerProduit.getId());

    return supprimerLeProduit.exec();
}

/*Envoi et enregistrement en base de donnée d'un nouvel utilisateur*/
bool BaseDeDonnees::creerUnUtilisateur(Utilisateur &employe)
{
    QSqlQuery nouvelUtilisateur(this->stockup);
    nouvelUtilisateur.prepare("INSERT INTO Utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) VALUES (:code, :nom, "
                              ":prenom, :mdp, :groupe);");
    nouvelUtilisateur.bindValue(":code", employe.getCode());
    nouvelUtilisateur.bindValue(":nom", employe.getNom());
    nouvelUtilisateur.bindValue(":prenom", employe.getPrenom());
    nouvelUtilisateur.bindValue(":mdp", employe.getMdp());
    nouvelUtilisateur.bindValue(":groupe", employe.getGroupe());
    return nouvelUtilisateur.exec();
}

/*Envoi et enregistrement en base de donnée d'un nouveau fournisseur*/
bool BaseDeDonnees::creerUnFournisseur(Fournisseur &creerFournisseur)
{
    QSqlQuery creerUnFournisseur(this->stockup);
    creerUnFournisseur.prepare("INSERT INTO fournisseurs (Code, Nom, Forme_juridique, Adresse, Code_postal, Pays, Ville, Telephone,"
                             " Siret, APE) VALUES (:code, :nom, :forme_juridique, :adresse, :code_postal, :pays, :ville, "
                             ":telephone, :siret, :ape)");
    creerUnFournisseur.bindValue(":code", creerFournisseur.getCodeFournisseur());
    creerUnFournisseur.bindValue(":nom", creerFournisseur.getNomSociete());
    creerUnFournisseur.bindValue(":forme_juridique", creerFournisseur.getFormeJuridique());
    creerUnFournisseur.bindValue(":adresse", creerFournisseur.getAdresse());
    creerUnFournisseur.bindValue(":code_postal", creerFournisseur.getCodePostal());
    creerUnFournisseur.bindValue(":pays", creerFournisseur.getPays());
    creerUnFournisseur.bindValue(":ville", creerFournisseur.getVille());
    creerUnFournisseur.bindValue(":telephone", creerFournisseur.getTelephone());
    creerUnFournisseur.bindValue(":siret", creerFournisseur.getSiret());
    creerUnFournisseur.bindValue(":ape", creerFournisseur.getApe());
    return creerUnFournisseur.exec();
}

/*Permet de chercher un fournisseur avec son code*/
void BaseDeDonnees::chercherFournisseur(QString trouverFournisseur)
{
    QSqlQuery rechercherFournisseur(this->stockup);
    rechercherFournisseur.prepare("SELECT * FROM fournisseurs WHERE Code = :code");
    rechercherFournisseur.bindValue(":code",trouverFournisseur);
        if(!rechercherFournisseur.exec())
    {
        qDebug() << ("Erreur");
    }
}

/*Permet de supprimer un fournisseur*/
bool BaseDeDonnees::supprimerUnFournisseur(Fournisseur &supprimerFournisseur)
{
    QSqlQuery supprimerLeFournisseur(this->stockup);
    supprimerLeFournisseur.prepare("DELETE FROM fournisseurs WHERE id = :id");
    supprimerLeFournisseur.bindValue(":id", supprimerFournisseur.getIdFournisseur());
    return supprimerLeFournisseur.exec();
}

/*Permet de supprimer un utilisateur*/
void BaseDeDonnees::supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur)
{
    QSqlQuery supprimerUnUtilisateur(this->stockup);
    supprimerUnUtilisateur.prepare("DELETE FROM utilisateurs WHERE id = :id");
    supprimerUnUtilisateur.bindValue(":id", supprimerUtilisateur.getIdUtilisateur());
    supprimerUnUtilisateur.exec();
}



