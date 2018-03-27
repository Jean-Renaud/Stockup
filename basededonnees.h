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
   // bool chercheProduitParNom();
    void chercherUnUtilisateur();
    bool supprimerReference(Produits &supprimerProduit);
    void chercherFournisseur(QString trouverFournisseur);
    bool miseAjourReference(Produits &MettreAjourProduit);
    bool creerUneReference(Produits &produit);
    void creerUnUtilisateur(Utilisateur &employe);
    bool creerUnFournisseur(Fournisseur &livreur);
    bool miseAjourFournisseur(Fournisseur &livreur2);
    void supprimerUnFournisseur(Fournisseur &livreur3);
    bool miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur);
    void supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur);
    void insertionEnBdd();

private:

};

#endif // BASEDEDONNEES_H
