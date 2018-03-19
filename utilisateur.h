#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <QString>

class Utilisateur
{
public:
    Utilisateur (QString id, QString code, QString nom, QString prenom,  QString mdp, QString groupe);
    QString id;
    QString code;
    QString nom;
    QString prenom;
    QString mdp;  
    QString groupe;

};

#endif // UTILISATEUR_H
