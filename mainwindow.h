#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "utilisateur.h"
#include "basededonnees.h"
#include "ui_mainwindow.h"

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
     */
    void desactiverOnglet(int);

    /**
     * @brief emplacementOccupe
     */
    void emplacementOccupe();

    /**
     * @brief carriste
     */
    Utilisateur * carriste;

    QString dateCreation();
    QString heure();

public slots:

    /**
     * @brief desactiverOngletsGroupeCarriste
     */
    void desactiverOngletsGroupeCarriste();

    /**
     * @brief on_actionQuitter_triggered
     */
    void on_actionQuitter_triggered();

    /**
     * @brief on_actionVider_la_bas_de_donn_es_triggered
     */
    void on_actionVider_la_bas_de_donn_es_triggered();

    /**
     * @brief desactiverOngletsGroupeQualite
     */
    void desactiverOngletsGroupeQualite();

    /**
     * @brief on_listDatabase_activated
     * @param index
     */
    void on_listDatabase_activated(const QModelIndex &index);

    /**
     * @brief on_listProvider_activated
     * @param index
     */
    void on_listProvider_activated(const QModelIndex &index);

    /**
     * @brief on_gestionUtilisateur_activated
     * @param index
     */
    void on_gestionUtilisateur_activated(const QModelIndex &index);


private slots:

    /**
     * @brief on_chercherParReference_clicked
     */
    void on_chercherParReference_clicked();

    /**
     * @brief on_chercherParEmplacement_clicked
     */
    void on_chercherParEmplacement_clicked();

    //void on_chercherParEmplacement_clicked();

    /**
     * @brief on_miseAjourProduit_clicked
     */
    void on_miseAjourProduit_clicked();

    /**
     * @brief on_supprimerProduit_clicked
     */
    void on_supprimerProduit_clicked();

    /**
     * @brief on_chercherParNomProduit_clicked
     */
    void on_chercherParNomProduit_clicked();

    /**
     * @brief on_creerUtilisateur_clicked
     */
    void on_creerUtilisateur_clicked();

    /**
     * @brief on_creerFournisseur_clicked
     */
    void on_creerFournisseur_clicked();

    /**
     * @brief on_chercherFournisseur_clicked
     */
    void on_chercherFournisseur_clicked();

    /**
     * @brief on_triAlphabetiqueStock_clicked
     */
    void on_triAlphabetiqueStock_clicked();

    /**
     * @brief on_majFournisseur_clicked
     */
    void on_majFournisseur_clicked();

    /**
     * @brief on_suppFournisseur_clicked
     */
    void on_suppFournisseur_clicked();

    /**
     * @brief on_chercheUtilisateur_clicked
     */
    void on_chercheUtilisateur_clicked();

    /**
     * @brief on_majUtilisateur_clicked
     */
    void on_majUtilisateur_clicked();

    /**
     * @brief on_suppUtilisateur_clicked
     */
    void on_suppUtilisateur_clicked();

    /**
     * @brief on_triAlphaUtilisateur_clicked
     */
    void on_triAlphaUtilisateur_clicked();

    /**
     * @brief on_triAlphaFournisseur_clicked
     */
    void on_triAlphaFournisseur_clicked();

    /**
     * @brief on_creerReferenceBtn_clicked
     */
    void on_creerReferenceBtn_clicked();

    void on_exportbdd_clicked();

    void on_tabGestionStock_tabBarClicked();


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



