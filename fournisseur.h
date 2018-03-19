#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>


class Fournisseur
{
public:
    Fournisseur(QString id, QString codeDuFournisseur, QString nomSociete, QString formeJuridique, QString adresse, QString codePostal, QString ville, QString pays, QString telephone, QString siret, QString ape);
     QString id;
     QString codeDuFournisseur;
     QString nomSociete;
     QString formeJuridique;
     QString adresse;
     QString codePostal;
     QString ville;
     QString pays;
     QString telephone;
     QString siret;
     QString ape;


};

#endif // FOURNISSEUR_H
