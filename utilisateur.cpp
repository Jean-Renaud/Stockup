#include "utilisateur.h"

Utilisateur::Utilisateur()
{


}

Utilisateur::Utilisateur(QString idUtilisateur, QString code, QString nom, QString prenom, QString mdp, QString groupe)
{
    this->idUtilisateur = idUtilisateur;
    this->code = code;
    this->nom = nom;
    this->prenom = prenom;
    this->mdp = mdp;
    this->groupe = groupe;

}

QString Utilisateur::getIdUtilisateur()
{
    return this->idUtilisateur;
}
QString Utilisateur::getCode()
{
    return this->code;
}
QString Utilisateur::getNom()
{
    return this->nom;
}
QString Utilisateur::getPrenom()
{
    return this->prenom;
}
QString Utilisateur::getMdp()
{
    return this->mdp;
}
QString Utilisateur::getGroupe()
{
    return this->groupe;
<<<<<<< HEAD
}
void Utilisateur::setGroupe(QString groupe)
{
   this->groupe = groupe;
}
void Utilisateur::setCode(QString code)
{
   this->code = code;
=======
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7
}
