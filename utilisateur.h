#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <QString>

class Utilisateur
{
public:
    Utilisateur();
    Utilisateur (QString idUtilisateur, QString code, QString nom, QString prenom, QString mdp, QString groupe);
    QString getIdUtilisateur();
    QString getCode();
    QString getNom();
    QString getPrenom();
    QString getMdp();
    QString getGroupe();
    void setGroupe(QString groupe);
    void setCode(QString code);


private:

    QString idUtilisateur;
    QString code;
    QString nom;
    QString prenom;
    QString mdp;
    QString groupe;
};

#endif // UTILISATEUR_H
