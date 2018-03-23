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
<<<<<<< HEAD
    void setGroupe(QString groupe);
    void setCode(QString code);
=======
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7


private:

    QString idUtilisateur;
    QString code;
    QString nom;
    QString prenom;
    QString mdp;
    QString groupe;
};

#endif // UTILISATEUR_H
