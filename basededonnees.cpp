#include "basededonnees.h"
#include "produits.h"
#include "fournisseur.h"
#include "qmainwindow.h"
#include "QtUiTools/QUiLoader"
#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QObject>
#include <QCoreApplication>
#include <QTranslator>

using namespace std;
BaseDeDonnees::BaseDeDonnees()
{
    this->stockup = QSqlDatabase::addDatabase("QSQLITE");

    stockup.setDatabaseName("C:/Users/adai03/Documents/STOCKUP/stockup.db");

    this->stockup.open();
    if(this->stockup.isOpen())
        qDebug() << "Base de données ouverte";
    else
        qDebug() << "Erreur ouverture bdd";
    this->creerTableBdd();
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

     QSqlQuery creerTable(this->stockup);

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

void BaseDeDonnees::creerUneReference(Produits &produit)
{
    QSqlQuery insererNouvelleReference(this->stockup);
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
       //QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));
   }
   else
   {
      // QMessageBox::critical(this,"Création échouée", "Nope.");

   }


}
void BaseDeDonnees::miseAjourReference(QString rowid, QString referenceDuProduit, QString nomDuProduit,QString numeroLot , QString emplacement, QString emballage , QString quantite, QString etat, QString dluo, QString date, QString fournisseur)
{
       QSqlQuery miseAjourProduit(this->stockup);
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
           //QMessageBox::critical(this,tr("ERREUR"),tr("ERREUR."));

       }
       else
       {
           //QMessageBox::information(this,tr("Succès"),tr("La modification du produit a bien été effectuée."));

       }

}
void BaseDeDonnees::miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur)
{
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

      // QMessageBox::information(this,tr("Mis à jour réussie"),tr("La mise à jour de l'utilisateur a été enregistrée avec succès."));


    }
    else
    {
      // QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour de l'utilisateur a échouée"));


    }
}

void BaseDeDonnees::miseAjourFournisseur(Fournisseur &livreur2)
{
    QSqlQuery miseAjourFournisseur(this->stockup);
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

      // QMessageBox::information(this,tr("Création réussie"),tr("La mise à jour du fournisseur a été enregistrée avec succès."));


    }
    else
    {
     //  QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour du fournisseur a échouée"));


    }
}
void BaseDeDonnees::supprimerReference(Produits &supprimerProduit)
{
    QSqlQuery supprimerLeProduit(this->stockup);
    supprimerLeProduit.prepare("DELETE FROM matieres_premieres WHERE id_Produit= :idProduit");
    supprimerLeProduit.bindValue(":idProduit", supprimerProduit.getId());
    if(!supprimerLeProduit.exec())
    {
      //  QMessageBox::critical(this, tr("Erreur"), tr("La suppression a échouée."));

    }
}
void BaseDeDonnees::chercheProduitParNom(QString chercherProduitParNom)
{
    QSqlQuery cherchProduitParNom(this->stockup);
    cherchProduitParNom.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercherNom LIKE '%'");
    cherchProduitParNom.bindValue(":chercherNom", chercherProduitParNom);
    cherchProduitParNom.exec();
}
void BaseDeDonnees::creerUnUtilisateur(Utilisateur &employe)
{
    QSqlQuery nouvelUtilisateur(this->stockup);
    nouvelUtilisateur.prepare("INSERT INTO Utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) VALUES (:code, :nom, :prenom, :mdp, :groupe);");
    nouvelUtilisateur.bindValue(":code", employe.getCode());
    nouvelUtilisateur.bindValue(":nom", employe.getNom());
    nouvelUtilisateur.bindValue(":prenom", employe.getPrenom());
    nouvelUtilisateur.bindValue(":mdp", employe.getMdp());
    nouvelUtilisateur.bindValue(":groupe", employe.getGroupe());
    if(nouvelUtilisateur.exec())
    {

      // QMessageBox::information(this, "Création réussie", "La création de l'utilisateur a été enregistrée avec succès.");


    }
    else
    {
      // QMessageBox::information(this,tr("Création échouée"),tr("La création de l'utilisateur a échouée"));
    }
}
void BaseDeDonnees::creerUnFournisseur(Fournisseur &livreur)
{
    QSqlQuery creerFournisseur(this->stockup);
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

       //QMessageBox::information(this,tr("Création réussie"),tr("La création du fournisseur a été enregistrée avec succès."));


    }
    else
    {
      // QMessageBox::information(this,tr("Création échouée"),tr("La création du fournisseur a échouée"));


    }
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
void BaseDeDonnees::supprimerUnFournisseur(Fournisseur &livreur3)
{
    QSqlQuery supprimerFournisseur(this->stockup);
    supprimerFournisseur.prepare("DELETE FROM fournisseurs WHERE id = :id");
    supprimerFournisseur.bindValue(":id", livreur3.getIdFournisseur());
    supprimerFournisseur.exec();
}
void BaseDeDonnees::supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur)
{
    QSqlQuery supprimerUnUtilisateur(this->stockup);
    supprimerUnUtilisateur.prepare("DELETE FROM utilisateurs WHERE id = :id");
    supprimerUnUtilisateur.bindValue(":id", supprimerUtilisateur.getIdUtilisateur());
    supprimerUnUtilisateur.exec();
}
