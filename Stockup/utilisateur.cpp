#include "utilisateur.h"

Utilisateur::Utilisateur(int code, QString mdp, QString nom, QString prenom, int groupe)
{
    this->code = code;
    this->mdp = mdp;
    this->nom = nom;
    this->prenom = prenom;
    this->groupe = groupe;
}
