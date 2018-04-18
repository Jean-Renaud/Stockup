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
     * Permet de créer les tables sql à l'installation de l'application
     */
    void creerTableBdd();

    /**
     * @brief insertionBddInstallation
     * Permet de faire des insertion dans les tables de la base de données lors de l'installation de l'application
     */
    void insertionBddInstallation();

    /**
     * @brief chercherFournisseur
     * @param trouverFournisseur
     * Permet d'effectuer la recherche d'un fournisseur
     */
    void chercherFournisseur(QString trouverFournisseur);

    /**
     * @brief chercherProduitParEmplacement
     * @param modelChercherProduitEmplacement
     * @param rechercheEmplacement
     * Permet de faire la recherche d'une matière première par emplacement
     */
    void chercherProduitParEmplacement(QSqlQueryModel *modelChercherProduitEmplacement, QString rechercheEmplacement);

    /**
     * @brief chercherProduitParNom
     * @param modelchercherProduitParNom
     * @param chercherProduitParnom
     * Permet de faire la recherche d'une matière première par nom
     */
    void chercherProduitParNom(QSqlQueryModel *modelchercherProduitParNom, QString chercherProduitParnom);


    /**
     * @brief creerUneReference
     * @param produit
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de créer une nouvelle référence
     */
    bool creerUneReference(Produits &produit);

    /**
     * @brief miseAjourReference
     * @param MettreAjourProduit
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de faire la mise à jour d'une référence
     */
    bool miseAjourReference(Produits &MettreAjourProduit);

    /**
     * @brief supprimerReference
     * @param supprimerProduit
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de supprimer une référence
     */
    bool supprimerReference(Produits &supprimerProduit);

    /**
     * @brief creerUnUtilisateur
     * @param employe
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de créer un nouvel utilisateur
     */
    bool creerUnUtilisateur(Utilisateur &employe);

    /**
     * @brief chercherUnUtilisateur
     * Permet de chercher un utilisateur dans la base de données
     */
    void chercherUnUtilisateur();

    /**
     * @brief creerUnFournisseur
     * @param creerFournisseur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de créer un fournisseur
     */
    bool creerUnFournisseur(Fournisseur &creerFournisseur);

    /**
     * @brief miseAjourFournisseur
     * @param mettreAjourFournisseur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de mettre à jour un fournisseur
     */
    bool miseAjourFournisseur(Fournisseur &mettreAjourFournisseur);

    /**
     * @brief supprimerUnFournisseur
     * @param supprimerUnFournisseur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de supprimer un fournisseur
     */
    bool supprimerUnFournisseur(Fournisseur &supprimerFournisseur);

    /**
     * @brief miseAJourUtilisateur
     * @param mettreAjourUtilisateur
     * @return si l'opération en base de donnée s'est effectuée ou non.
     * Permet de mettre à jour un utilisateur
     */
    bool miseAJourUtilisateur(Utilisateur &mettreAjourUtilisateur);

    /**
     * @brief supprimerUnUtilisateur
     * @param supprimerUtilisateur
     * Permet de supprimer un utilisateur
     */
    void supprimerUnUtilisateur(Utilisateur &supprimerUtilisateur);

    /**
     * @brief insertionEnBdd
     * Execute la méthode qui fait l'insertion des données dans les tables lors de l'installation
     */
    void insertionEnBdd();

    /**
     * @brief chercherParReference
     * @param modelChercherParReference
     * @param searchRef
     * Permet de chercher une référence dans la base de donnée avec sa référence
     */
    void chercherParReference(QSqlQueryModel *modelChercherParReference, QString searchRef);


private:

};

#endif // BASEDEDONNEES_H
