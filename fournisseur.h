#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>


class Fournisseur
{
public:
    Fournisseur(QString codeDuFournisseur, QString nomSociete, QString formeJuridique, QString adresse, QString codePostal, QString ville, QString pays, QString telephone, QString siret, QString ape);
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
     void updateProvider(QString majCodeDuFournisseur, QString majNomSociete, QString majFormeJuridique, QString majAdresse, QString majCodePostal, QString majVille, QString majPays, QString majTelephone, QString majSiret, QString majApe);
     QString majCodeDuFournisseur;
     QString majNomSociete;
     QString majFormeJuridique;
     QString majAdresse;
     QString majCodePostal;
     QString majVille;
     QString majPays;
     QString majTelephone;
     QString majSiret;
     QString majApe;






};

#endif // FOURNISSEUR_H
