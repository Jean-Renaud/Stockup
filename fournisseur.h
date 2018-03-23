#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>


class Fournisseur
{
public:
    Fournisseur(QString id, QString codeDuFournisseur, QString nomSociete, QString formeJuridique, QString adresse, QString codePostal, QString ville, QString pays, QString telephone, QString siret, QString ape);

    QString getIdFournisseur();
    QString getCodeFournisseur();
    QString getNomSociete();
    QString getFormeJuridique();
    QString getAdresse();
    QString getCodePostal();
    QString getVille();
    QString getPays();
    QString getTelephone();
    QString getSiret();
    QString getApe();

private:
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
