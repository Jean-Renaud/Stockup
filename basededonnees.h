#ifndef BASEDEDONNEES_H
#define BASEDEDONNEES_H

#include <QMainWindow>
#include <QApplication>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QDebug>
#include <QMessageBox>
#include "utilisateur.h"
#include "produits.h"
#include "fournisseur.h"

class BaseDeDonnees
{
public:
    BaseDeDonnees();
    ~BaseDeDonnees();

    QSqlDatabase stockup;
    void creerTableBdd();
    void insertionBddInstallation();
    void chercheProduitParNom(QString chercherProduitParNom);
    void chercherUnUtilisateur();
    void supprimerReference(Produits &supprimerProduit);
    void chercherFournisseur(QString trouverFournisseur);
    void miseAjourReference(QString rowid, QString referenceDuProduit, QString nomDuProduit, QString numeroLot, QString emplacement,
                            QString emballage, QString quantite, QString etat, QString dluo, QString date, QString fournisseur);
    void creerUneReference(Produits &produit);
    void fermetureBdd();
    bool ouvertureBdd();
    void creerUnUtilisateur(Utilisateur &employe);
    void creerUnFournisseur(Fournisseur &livreur);
    void miseAjourFournisseur(Fournisseur &livreur2);
    void supprimerUnFournisseur(Fournisseur &livreur3);
    void miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur);
    void supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur);
    void insertionEnBdd();

private:

};

#endif // BASEDEDONNEES_H
