#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include<QDate>

class Produits
{
public:
    Produits(QString referenceProduit, QString nomProduit, QString lotProduit, QDate date, QString heure, QString emplacementProduit, QString emballageProduit,
             QString quantiteProduit, QString etatProduit, QString dluoProduit, QString codeFournisseur);
    QString getRef();
    QString getNom();
    QString getLot();
    QDate getDate();
    QString getHeure();
    QString getEmplacement();
    QString getEmballage();
    QString getQuantite();
    QString getEtat();
    QString getDluo();
    QString getCodeFournisseur();
private :
    QString referenceProduit;
    QString nomProduit;
    QString lotProduit;
    QDate date;
    QString heure;
    QString emplacementProduit;
    QString emballageProduit;
    QString quantiteProduit;
    QString etatProduit;
    QString dluoProduit;
    QString codeFournisseur;
};

#endif // PRODUITS_H

