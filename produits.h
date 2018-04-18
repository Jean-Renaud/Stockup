#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include<QDate>




/**
 * @brief Permet de gèrer les produits
 */
class Produits
{
public:

    /**
     * @brief Produits
     * @param idProduit
     * @param referenceProduit
     * @param nomProduit
     * @param lotProduit
     * @param date
     * @param heure
     * @param emplacementProduit
     * @param emballageProduit
     * @param quantiteProduit
     * @param etatProduit
     * @param dluoProduit
     * @param codeFournisseur
     */
    Produits(QString idProduit, QString referenceProduit, QString nomProduit, QString lotProduit, QString date, QString heure,
             QString emplacementProduit, QString emballageProduit,
             QString quantiteProduit, QString etatProduit, QString dluoProduit, QString codeFournisseur);

    /**
     * @brief getId
     * @return l'id du produit.
     */
    QString getId();

    /**
     * @brief getRef
     * @return le référence du produit.
     */
    QString getRef();

    /**
     * @brief getNom
     * @return le nom du produit.
     */
    QString getNom();

    /**
     * @brief getLot
     * @return le numéro de lot du produit.
     */
    QString getLot();

    /**
     * @brief getDate
     * @return la date de création du produit.
     */
    QString getDate();

    /**
     * @brief getHeure
     * @return l'heure de création du produit.
     */
    QString getHeure();

    /**
     * @brief getEmplacement
     * @return l'emplacement du produit.
     */
    QString getEmplacement();

    /**
     * @brief getEmballage
     * @return la quantité de produit par contenant.
     */
    QString getEmballage();

    /**
     * @brief getQuantite
     * @return la quantité de produit par emplacement.
     */
    QString getQuantite();

    /**
     * @brief getEtat
     * @return l'état du produit à savoir si il est consommable ou non.
     */
    QString getEtat();

    /**
     * @brief getDluo
     * @return le numéro de lot du produit.
     */
    QString getDluo();

    /**
     * @brief getCodeFournisseur
     * @return le code du fournisseur.
     */
    QString getCodeFournisseur();

private :

    /**
     * @brief idProduit
     */
    QString idProduit;

    /**
     * @brief referenceProduit
     */
    QString referenceProduit;

    /**
     * @brief nomProduit
     */
    QString nomProduit;

    /**
     * @brief lotProduit
     */
    QString lotProduit;

    /**
     * @brief date
     */
    QString date;

    /**
     * @brief heure
     */
    QString heure;

    /**
     * @brief emplacementProduit
     */
    QString emplacementProduit;

    /**
     * @brief emballageProduit
     */
    QString emballageProduit;

    /**
     * @brief quantiteProduit
     */
    QString quantiteProduit;

    /**
     * @brief etatProduit
     */
    QString etatProduit;

    /**
     * @brief dluoProduit
     */
    QString dluoProduit;

    /**
     * @brief codeFournisseur
     */
    QString codeFournisseur;
};

#endif // PRODUITS_H

