#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>

/**
 * @brief Permet de gèrer les fournisseurs
 */
class Fournisseur
{
public:  
    /**
     * @brief Fournisseur
     * @param id
     * @param codeDuFournisseur
     * @param nomSociete
     * @param formeJuridique
     * @param adresse
     * @param codePostal
     * @param ville
     * @param pays
     * @param telephone
     * @param siret
     * @param ape
     */
    Fournisseur(QString id, QString codeDuFournisseur, QString nomSociete, QString formeJuridique, QString adresse,
                QString codePostal, QString ville, QString pays, QString telephone, QString siret, QString ape);

    /**
     * @brief getIdFournisseur
     * @return l'id du fournisseur
     */
    QString getIdFournisseur();

    /**
     * @brief getCodeFournisseur
     * @return le code fournisseur
     */
    QString getCodeFournisseur();

    /**
     * @brief getNomSociete
     * @return le nom de la société
     */
    QString getNomSociete();

    /**
     * @brief getFormeJuridique
     * @return la forme juridique
     */
    QString getFormeJuridique();

    /**
     * @brief getAdresse
     * @return l'adresse
     */
    QString getAdresse();

    /**
     * @brief getCodePostal
     * @return le code postal
     */
    QString getCodePostal();

    /**
     * @brief getVille
     * @return la ville
     */
    QString getVille();

    /**
     * @brief getPays
     * @return le pays
     */
    QString getPays();

    /**
     * @brief getTelephone
     * @return le numéro de téléphone
     */
    QString getTelephone();

    /**
     * @brief getSiret
     * @return le numéro de SIRET
     */
    QString getSiret();

    /**
     * @brief getApe
     * @return le code APE
     */
    QString getApe();

private:

    /**
      * @brief id
      */
     QString id;

     /**
      * @brief codeDuFournisseur
      */
     QString codeDuFournisseur;

     /**
      * @brief nomSociete
      */
     QString nomSociete;

     /**
      * @brief formeJuridique
      */
     QString formeJuridique;

     /**
      * @brief adresse
      */
     QString adresse;

     /**
      * @brief codePostal
      */
     QString codePostal;

     /**
      * @brief ville
      */
     QString ville;

     /**
      * @brief pays
      */
     QString pays;

     /**
      * @brief telephone
      */
     QString telephone;

     /**
      * @brief siret
      */
     QString siret;

     /**
      * @brief ape
      */
     QString ape;
};

#endif // FOURNISSEUR_H
