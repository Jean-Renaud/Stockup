#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <QString>



/**
 * @brief Permet de gèrer les utilisateurs
 */
class Utilisateur
{
public:

    /**
     * @brief Utilisateur
     */
    Utilisateur();

    /**
     * @brief Utilisateur
     * @param idUtilisateur
     * @param code
     * @param nom
     * @param prenom
     * @param mdp
     * @param groupe
     */
    Utilisateur (QString idUtilisateur, QString code, QString nom, QString prenom, QString mdp, QString groupe);

    /**
     * @brief getIdUtilisateur
     * @return l'id de l'utilisateur.
     */
    QString getIdUtilisateur();

    /**
     * @brief getCode
     * @return le code utilisateur.
     */
    QString getCode();

    /**
     * @brief getNom
     * @return le nom de l'utilisateur.
     */
    QString getNom();

    /**
     * @brief getPrenom
     * @return le prénom de l'utilisateur.
     */
    QString getPrenom();

    /**
     * @brief getMdp
     * @return le mot de passe de l'utilisateur.
     */
    QString getMdp();

    /**
     * @brief getGroupe
     * @return le groupe de l'utilisateur.
     */
    QString getGroupe();

    /**
     * @brief setGroupe
     * @param groupe
     */
    void setGroupe(QString groupe);

    /**
     * @brief setCode
     * @param code
     */
    void setCode(QString code);


private:

    /**
     * @brief idUtilisateur
     */
    QString idUtilisateur;

    /**
     * @brief code
     */
    QString code;

    /**
     * @brief nom
     */
    QString nom;

    /**
     * @brief prenom
     */
    QString prenom;

    /**
     * @brief mdp
     */
    QString mdp;

    /**
     * @brief groupe
     */
    QString groupe;
};

#endif // UTILISATEUR_H
