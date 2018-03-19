#include "utilisateur.h"

Utilisateur::Utilisateur(QString id, QString code, QString nom, QString prenom, QString mdp, QString groupe)
{
    this->id = id;
    this->code = code;
    this->nom = nom;
    this->prenom = prenom;
    this->mdp = mdp;
    this->groupe = groupe;
}
