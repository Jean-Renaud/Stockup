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
    /*
    this->stockup = QSqlDatabase::addDatabase("QSQLITE");
    stockup.setDatabaseName("./stockup.db");

    this->stockup.open();
    if(this->stockup.isOpen())
        qDebug() << "Base de données ouverte";
    else
        qDebug() << "Erreur ouverture bdd";
    this->creerTableBdd();
    */
}

BaseDeDonnees::~BaseDeDonnees() {
    this->stockup.close();
    this->stockup.removeDatabase(QSqlDatabase::defaultConnection);
}

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
}
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
void BaseDeDonnees::chercherParReference(QSqlQueryModel *modelChercherParReference, QString searchRef)
{
    QSqlQuery listRef;
    listRef.prepare("SELECT * FROM matieres_Premieres WHERE Reference = :reference");
    listRef.bindValue(":reference",searchRef);
    listRef.exec();
    modelChercherParReference->setQuery(listRef);
}
void BaseDeDonnees::chercherProduitParEmplacement(QSqlQueryModel *modelChercherProduitEmplacement, QString rechercheEmplacement)
{

    QSqlQuery chercheParEmplacement;
    chercheParEmplacement.prepare("SELECT * FROM matieres_Premieres WHERE Emplacement = :location");
    chercheParEmplacement.bindValue(":location",rechercheEmplacement);
    chercheParEmplacement.exec();
    modelChercherProduitEmplacement->setQuery(chercheParEmplacement);


}

void BaseDeDonnees::chercherProduitParNom(QSqlQueryModel *modelchercherProduitParNom, QString chercherProduitParnom)
{
    QSqlQuery listeRechercheNomProduit;
    listeRechercheNomProduit.prepare("SELECT * FROM matieres_Premieres WHERE Nom LIKE :chercherProduitParnom");
    listeRechercheNomProduit.bindValue(":chercherProduitParnom", chercherProduitParnom + '%');
    listeRechercheNomProduit.exec();
   /* while(listeRechercheNomProduit.next()) {
        qDebug() << "Il y a un résultat";
        qDebug() << listeRechercheNomProduit.value(0).toInt();
    }*/
    modelchercherProduitParNom->setQuery(listeRechercheNomProduit);
}

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

bool BaseDeDonnees::miseAjourFournisseur(Fournisseur &livreur2)
{
    QSqlQuery miseAjourFournisseur(this->stockup);
    miseAjourFournisseur.prepare("UPDATE fournisseurs SET Code = :code, Nom = :nom, Forme_juridique = :forme_juridique, "
                                 "Adresse = :adresse, Code_postal = :code_postal, Ville = :ville, Pays = :pays, "
                                 "Telephone = :telephone, Siret = :siret, APE = :ape WHERE id = :id");
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

    return miseAjourFournisseur.exec();

}
bool BaseDeDonnees::supprimerReference(Produits &supprimerProduit)
{
    QSqlQuery supprimerLeProduit(this->stockup);
    supprimerLeProduit.prepare("DELETE FROM matieres_premieres WHERE id_Produit= :idProduit");
    supprimerLeProduit.bindValue(":idProduit", supprimerProduit.getId());

    return supprimerLeProduit.exec();
}
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
bool BaseDeDonnees::creerUnFournisseur(Fournisseur &livreur)
{
    QSqlQuery creerFournisseur(this->stockup);
    creerFournisseur.prepare("INSERT INTO fournisseurs (Code, Nom, Forme_juridique, Adresse, Code_postal, Pays, Ville, Telephone,"
                             " Siret, APE) VALUES (:code, :nom, :forme_juridique, :adresse, :code_postal, :pays, :ville, "
                             ":telephone, :siret, :ape)");
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
    return creerFournisseur.exec();
}

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
bool BaseDeDonnees::supprimerUnFournisseur(Fournisseur &livreur3)
{
    QSqlQuery supprimerFournisseur(this->stockup);
    supprimerFournisseur.prepare("DELETE FROM fournisseurs WHERE id = :id");
    supprimerFournisseur.bindValue(":id", livreur3.getIdFournisseur());
    return supprimerFournisseur.exec();
}
void BaseDeDonnees::supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur)
{
    QSqlQuery supprimerUnUtilisateur(this->stockup);
    supprimerUnUtilisateur.prepare("DELETE FROM utilisateurs WHERE id = :id");
    supprimerUnUtilisateur.bindValue(":id", supprimerUtilisateur.getIdUtilisateur());
    supprimerUnUtilisateur.exec();
}
