#include "produits.h"

Produits::Produits(QString reference, QString nom, QString lot, QDate date, QString heure, QString emplacement,
                   QString emballage, QString quantite, QString etat, QString dluo, QString codeFournisseur)
{
    this->reference = reference;
    this->nom = nom;
    this->lot = lot;
    this->date = date;
    this->heure = heure;
    this->emplacement = emplacement;
    this->emballage = emballage;
    this->quantite = quantite;
    this->etat = etat;
    this->dluo = dluo;
    this->codeFournisseur = codeFournisseur;
}
