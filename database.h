#ifndef DATABASE_H
#define DATABASE_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QDebug>
#include <QMessageBox>
#include "utilisateur.h"
#include "produits.h"
#include "fournisseur.h"

class database : public QMainWindow
{
    public:
        database();
        virtual ~database();
        QSqlDatabase stockup;
        void creerTableBdd();
        void chercheProduitParNom(QString chercherProduitParNom);
        void supprimerReference(QString suppRef);
        void chercherFournisseur(QString trouverFournisseur);
        void miseAjourReference(QString rowid, QString referenceDuProduit, QString nomDuProduit, QString numeroLot, QString emplacement, QString emballage, QString quantite, QString etat, QString dluo, QString date, QString fournisseur);
        void creerUneReference(Produits &produit);
        void fermetureBdd();
        bool ouvertureBdd();
        void creerUnUtilisateur(Utilisateur &employe);
        void creerUnFournisseur(Fournisseur &livreur);
        void miseAjourFournisseur(Fournisseur &livreur2);
        void supprimerUnFournisseur(Fournisseur &livreur3);
        void miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur);
        void supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur);
        void insertionUtilisateur();

    protected:
    private:
};

#endif // DATABASE_H
