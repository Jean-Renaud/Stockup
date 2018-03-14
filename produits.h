#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>

class Produits
{
public:
    Produits(QString reference, QString nom, QString lot, QString date, QString heure, QString emplacement, QString emballage,
             QString quantite, QString etat, QString dluo, QString codeFournisseur);

    QString reference;
    QString nom;
    QString lot;
    QString date;
    QString heure;
    QString emplacement;
    QString emballage;
    QString quantite;
    QString etat;
    QString dluo;
    QString codeFournisseur;
};

#endif // PRODUITS_H

