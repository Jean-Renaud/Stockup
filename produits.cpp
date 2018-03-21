#include "produits.h"

Produits::Produits(QString referenceProduit, QString nomProduit, QString lotProduit, QDate date, QString heure, QString emplacementProduit,
                   QString emballageProduit, QString quantiteProduit, QString etatProduit, QString dluoProduit, QString codeFournisseur)
{
    this->referenceProduit = referenceProduit;
    this->nomProduit = nomProduit;
    this->lotProduit = lotProduit;
    this->date = date;
    this->heure = heure;
    this->emplacementProduit = emplacementProduit;
    this->emballageProduit = emballageProduit;
    this->quantiteProduit = quantiteProduit;
    this->etatProduit = etatProduit;
    this->dluoProduit = dluoProduit;
    this->codeFournisseur = codeFournisseur;
}

QString Produits::getRef()
{
    return this->referenceProduit;
}
QString Produits::getNom()
{
    return this->nomProduit;
}
QString Produits::getLot()
{
    return this->lotProduit;
}
QDate Produits::getDate()
{
    return this->date;
}
QString Produits::getHeure()
{
    return this->heure;
}
QString Produits::getEmplacement()
{
    return this->emplacementProduit;
}
QString Produits::getEmballage()
{
    return this->emballageProduit;
}
QString Produits::getQuantite()
{
    return this->quantiteProduit;
}
QString Produits::getEtat()
{
    return this->etatProduit;
}
QString Produits::getDluo()
{
    return this->dluoProduit;
}
QString Produits::getCodeFournisseur()
{
    return this->codeFournisseur;
}
