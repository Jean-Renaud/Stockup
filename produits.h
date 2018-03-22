#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include<QDate>

class Produits
{
public:
    Produits(QString idProduit, QString referenceProduit, QString nomProduits, QString lotProduit, QString date, QString heure, QString emplacementProduit, QString emballageProduit,
    QString quantiteProduit, QString etatProduit, QString dluoProduit, QString codeFournisseur);
    QString getId();
    QString getRef();
    QString getNom();
    QString getLot();
    QString getDate();
    QString getHeure();
    QString getEmplacement();
    QString getEmballage();
    QString getQuantite();
    QString getEtat();
    QString getDluo();
    QString getCodeFournisseur();
private :
    QString idProduit;
    QString referenceProduit;
    QString nomProduit;
    QString lotProduit;
    QString date;
    QString heure;
    QString emplacementProduit;
    QString emballageProduit;
    QString quantiteProduit;
    QString etatProduit;
    QString dluoProduit;
    QString codeFournisseur;
};

#endif // PRODUITS_H

