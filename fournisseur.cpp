#include "fournisseur.h"
#include <QString>

Fournisseur::Fournisseur(QString id, QString codeDuFournisseur, QString nomSociete, QString formeJuridique, QString adresse,
                         QString codePostal, QString ville, QString pays, QString telephone, QString siret, QString ape)
{
    this->id = id;
    this->codeDuFournisseur = codeDuFournisseur;
    this-> nomSociete = nomSociete;
    this-> formeJuridique = formeJuridique;
    this-> adresse = adresse;
    this->codePostal = codePostal;
    this->ville = ville;
    this->pays = pays;
    this->telephone = telephone;
    this->siret = siret;
    this->ape = ape;
}

QString Fournisseur::getIdFournisseur()
{
    return this->id;
}
QString Fournisseur::getCodeFournisseur()
{
    return this->codeDuFournisseur;
}
QString Fournisseur::getNomSociete()
{
    return this->nomSociete;
}
QString Fournisseur::getFormeJuridique()
{
    return this->formeJuridique;
}
QString Fournisseur::getAdresse()
{
    return this->adresse;
}
QString Fournisseur::getCodePostal()
{
    return this->codePostal;
}
QString Fournisseur::getVille()
{
    return this->ville;
}
QString Fournisseur::getPays()
{
    return this->pays;
}
QString Fournisseur::getTelephone()
{
    return this->telephone;
}
QString Fournisseur::getSiret()
{
    return this->siret;
}
QString Fournisseur::getApe()
{
    return this->ape;
}
