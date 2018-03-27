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
#include "ui_mainwindow.h"

class BaseDeDonnees
{
public:
    BaseDeDonnees();
    ~BaseDeDonnees();

    QSqlDatabase stockup;
    void creerTableBdd();
    void insertionBddInstallation();
    void chercherUnUtilisateur();
    bool supprimerReference(Produits &supprimerProduit);
    void chercherFournisseur(QString trouverFournisseur);
    bool miseAjourReference(Produits &MettreAjourProduit);
    bool creerUneReference(Produits &produit);
    bool creerUnUtilisateur(Utilisateur &employe);
    bool creerUnFournisseur(Fournisseur &livreur);
    bool miseAjourFournisseur(Fournisseur &livreur2);
    bool supprimerUnFournisseur(Fournisseur &livreur3);
    bool miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur);
    void supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur);
    void insertionEnBdd();
    void chercherParReference(QSqlQueryModel *modelChercherParReference, QString searchRef);
    void chercherProduitParEmplacement(QSqlQueryModel *modelChercherProduitEmplacement, QString rechercheEmplacement);
    void chercherProduitParNom(QSqlQueryModel *modelchercherProduitParNom, QString chercherProduitParnom);

private:

};

#endif // BASEDEDONNEES_H
