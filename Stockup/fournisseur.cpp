#include "fournisseur.h"

Fournisseur::Fournisseur(QString id, QString codeDuFournisseur, QString nomSociete, QString formeJuridique, QString adresse, QString codePostal, QString ville, QString pays, QString telephone, QString siret, QString ape)
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
