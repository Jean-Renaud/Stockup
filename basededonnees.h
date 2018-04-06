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

/**
 * @class BaseDeDonnees
 * @brief Interface vers fichier de base de données SQlite3
 */
class BaseDeDonnees
{
public:
    BaseDeDonnees();
    ~BaseDeDonnees();

    /**
     * @brief stockup
     */
    QSqlDatabase stockup;

    /**
     * @brief creerTableBdd
     */
    void creerTableBdd();

    /**
     * @brief insertionBddInstallation
     */
    void insertionBddInstallation();

    /**
     * @brief chercherFournisseur
     * @param trouverFournisseur
     */
    void chercherFournisseur(QString trouverFournisseur);

    /**
     * @brief chercherProduitParEmplacement
     * @param modelChercherProduitEmplacement
     * @param rechercheEmplacement
     */
    void chercherProduitParEmplacement(QSqlQueryModel *modelChercherProduitEmplacement, QString rechercheEmplacement);

    /**
     * @brief chercherProduitParNom
     * @param modelchercherProduitParNom
     * @param chercherProduitParnom
     */
    void chercherProduitParNom(QSqlQueryModel *modelchercherProduitParNom, QString chercherProduitParnom);


    /**
     * @brief creerUneReference
     * @param produit
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool creerUneReference(Produits &produit);

    /**
     * @brief miseAjourReference
     * @param MettreAjourProduit
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool miseAjourReference(Produits &MettreAjourProduit);

    /**
     * @brief supprimerReference
     * @param supprimerProduit
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool supprimerReference(Produits &supprimerProduit);

    /**
     * @brief creerUnUtilisateur
     * @param employe
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool creerUnUtilisateur(Utilisateur &employe);

    /**
     * @brief chercherUnUtilisateur
     */
    void chercherUnUtilisateur();

    /**
     * @brief creerUnFournisseur
     * @param creerFournisseur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool creerUnFournisseur(Fournisseur &creerFournisseur);

    /**
     * @brief miseAjourFournisseur
     * @param mettreAjourFournisseur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool miseAjourFournisseur(Fournisseur &mettreAjourFournisseur);

    /**
     * @brief supprimerUnFournisseur
     * @param livreur3
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool supprimerUnFournisseur(Fournisseur &supprimerFournisseur);

    /**
     * @brief miseAJourUtilisateur
     * @param mettreAjourUtilisateur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     */
    bool miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur);

    /**
     * @brief supprimerUnUtilisateur
     * @param supprimerUtilisateur
     */
    void supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur);

    /**
     * @brief insertionEnBdd
     */
    void insertionEnBdd();

    /**
     * @brief chercherParReference
     * @param modelChercherParReference
     * @param searchRef
     */
    void chercherParReference(QSqlQueryModel *modelChercherParReference, QString searchRef);


private:

};

#endif // BASEDEDONNEES_H
