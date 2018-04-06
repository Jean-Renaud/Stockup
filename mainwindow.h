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
    void disableTab(int);

    /**
     * @brief emplacementOccupe
     */
    void emplacementOccupe();

    /**
     * @brief carriste
     */
    Utilisateur * carriste;


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
     * @brief on_search_Database_clicked
     */
    void on_search_Database_clicked();

    /**
     * @brief on_search_Location_clicked
     */
    void on_search_Location_clicked();

    //void on_chercherParEmplacement_clicked();

    /**
     * @brief on_update_row_clicked
     */
    void on_update_row_clicked();

    /**
     * @brief on_deleteProduct_clicked
     */
    void on_deleteProduct_clicked();

    /**
     * @brief on_searchNameProduct_clicked
     */
    void on_searchNameProduct_clicked();

    /**
     * @brief on_createUser_clicked
     */
    void on_createUser_clicked();

    /**
     * @brief on_creerFournisseur_clicked
     */
    void on_creerFournisseur_clicked();

    /**
     * @brief on_fournisseur_clicked
     */
    void on_fournisseur_clicked();

    /**
     * @brief on_voirStock_clicked
     */
    void on_voirStock_clicked();

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



