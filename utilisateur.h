#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <QString>

class Utilisateur
{
public:
    Utilisateur(int code, QString mdp, QString nom, QString prenom, int groupe);
    int code;
    QString mdp;
    QString nom;
    QString prenom;
    int groupe;

};

#endif // UTILISATEUR_H
