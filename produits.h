#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include<QDate>

class Produits
{
public:
    Produits(QString idProduit, QString referenceProduit, QString nomProduit, QString lotProduit, QString date, QString heure, QString emplacementProduit, QString emballageProduit,
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
   /* void setId(QString idProduit);
    void setRef(QString referenceProduit);
    void setNom(QString nomProduit);
    void setLot(QString lotProduit);
    void setDate(QString date);
    void setHeure(QString heure);
    void setEmplacement(QString emplacementProduit);
    void setEmballage(QString emballageProduit);
    void setQuantite(QString quantiteProduit);
    void setEtat(QString etatProduit);
    void setDluo(QString dluoProduit);
    void setCodeFournisseur(QString codeFournisseur);*/
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

