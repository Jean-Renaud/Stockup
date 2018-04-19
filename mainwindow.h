#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "utilisateur.h"
#include "basededonnees.h"


#include <QApplication>
#include <QtSql/QSql>
#include <QtDebug>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief Permet de gèrer toutes les interactions dans la fenêtre principale
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief setBaseDeDonnees
     */
    void setBaseDeDonnees(BaseDeDonnees*);

    /**
     * @brief moveToTab
     */
    void moveToTab(int);

    /**
     * @brief disableTab
     * Permet de désactiver les onglet en fonction des droits utilisateurs
     */
    void desactiverOnglet(int);

    /**
     * @brief carriste
     */
    Utilisateur * carriste;

    /**
     * @brief dateCreation
     * @return la date du système
     * Permet d'obtenir la date du système
     */
    QString dateCreation();

    /**
     * @brief heure
     * @return l'heure du système
     * Permet d'obtenir l'heure du système
     */
    QString heure();

public slots:

    /**
     * @brief desactiverOngletsGroupeCarriste
     * Liste les différents onglets désactivés pour le groupe carriste
     */
    void desactiverOngletsGroupeCarriste();

    /**
     * @brief on_actionQuitter_triggered
     * Permet de fermer l'application
     */
    void on_actionQuitter_triggered();

    /**
     * @brief on_actionVider_la_bas_de_donn_es_triggered
     * Permet de purger la table matieres_Premieres et Fournisseurs.
     */
    void on_actionVider_la_bas_de_donn_es_triggered();

    /**
     * @brief desactiverOngletsGroupeQualite
     * Liste les différents onglets désactivés pour le groupe labo qualite
     */
    void desactiverOngletsGroupeQualite();

    /**
     * @brief on_listDatabase_activated
     * @param index
     * Permet de rendre la vue cliquable pour la gestion du stock

     */
    void on_listDatabase_activated(const QModelIndex &index);

    /**
     * @brief on_listProvider_activated
     * @param index
     * Permet de rendre la vue cliquable pour la gestion des fournisseurs

     */
    void on_listProvider_activated(const QModelIndex &index);

    /**
     * @brief on_gestionUtilisateur_activated
     * @param index
     * Permet de rendre la vue cliquable pour la gestion des utilisateurs
     */
    void on_gestionUtilisateur_activated(const QModelIndex &index);


private slots:

    /**
     * @brief on_chercherParReference_clicked
     * Permet de faire une recherche par référence
     */
    void on_chercherParReference_clicked();

    /**
     * @brief on_chercherParEmplacement_clicked
     * Permet de faire une recherche par emplacement
     */
    void on_chercherParEmplacement_clicked();

    /**
     * @brief on_miseAjourProduit_clicked
     * permet de valider les saisies pour faire la mise à jour
     */
    void on_miseAjourProduit_clicked();

    /**
     * @brief on_supprimerProduit_clicked
     * Permet de supprimer un produit
     */
    void on_supprimerProduit_clicked();

    /**
     * @brief on_chercherParNomProduit_clicked
     * Permet de faire une recherche par nom
     */
    void on_chercherParNomProduit_clicked();

    /**
     * @brief on_creerUtilisateur_clicked
     * Permet de valider les saisies du formulaire de création utilisateur pour créer un nouvel utilisateur
     */
    void on_creerUtilisateur_clicked();

    /**
     * @brief on_creerFournisseur_clicked
     * Permet de valider les saisies du formulaire de création fournisseur pour créer un nouveau fournisseur
     */
    void on_creerFournisseur_clicked();

    /**
     * @brief on_chercherFournisseur_clicked
     * Permet de chercher un fournisseur
     */
    void on_chercherFournisseur_clicked();

    /**
     * @brief on_triAlphabetiqueStock_clicked
     * Permet de trier le stock par ordre alphabétique
     */
    void on_triAlphabetiqueStock_clicked();

    /**
     * @brief on_majFournisseur_clicked
     * Permet de valider les saisies pour mettre à jour un fournisseur
     */
    void on_majFournisseur_clicked();

    /**
     * @brief on_suppFournisseur_clicked
     * Permet de supprimer un fournisseur
     */
    void on_suppFournisseur_clicked();

    /**
     * @brief on_chercheUtilisateur_clicked
     * Permet de chercher un utilisateur
     */
    void on_chercheUtilisateur_clicked();

    /**
     * @brief on_majUtilisateur_clicked
     * Permet de mettre à jour un utilisateur
     */
    void on_majUtilisateur_clicked();

    /**
     * @brief on_suppUtilisateur_clicked
     * Permet de supprimer un utilisateur
     */
    void on_suppUtilisateur_clicked();

    /**
     * @brief on_triAlphabetiqueUtilisateur_clicked
     * Permet de trier les utilisateurs par ordre alphabétique
     */
    void on_triAlphabetiqueUtilisateur_clicked();

    /**
     * @brief on_triAlphabetiqueFournisseur_clicked
     * Permet de trier les fournisseurs par ordre alphabétique
     */
    void on_triAlphabetiqueFournisseur_clicked();

    /**
     * @brief on_creerReferenceBtn_clicked
     * Permet de valider les saisies du formulaire de création de matières premières pour créer une nouvelle référence
     */
    void on_creerReferenceBtn_clicked();
    /**
     * @brief on_exportbdd_clicked
     * Permet d'exporter la base de donnée au format .csv
     */
    void on_exportbdd_clicked();

    /**
     * @brief on_tabGestionStock_tabBarClicked
     * Lorsqu'on clique sur l'onglet Créer une référence, les champs heure et date se remplissent automatiquement
     */
    void on_tabGestionStock_tabBarClicked();

    /**
     * @brief on_triParDate_clicked
     * Permet de trier le stock par ordre alphabétique
     */
    void on_triParDate_clicked();

    /**
     * @brief on_chargerFournisseurs_clicked
     * Permet d'envoyer la liste des fournisseurs dans un combobox
     */
    void on_chargerFournisseurs_clicked();

private:

    /**
     * @brief bdd
     */
    BaseDeDonnees *bdd;

    /**
     * @brief ui
     */
    Ui::MainWindow *ui;

    /**
     * @brief modal
     */
    QSqlQueryModel modal;

    /**
     * @brief produit
     */
    Produits *produit;
};

#endif // MAINWINDOW_H



