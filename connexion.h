#ifndef CONNEXION_H
#define CONNEXION_H
#include <QDialog>
#include "basededonnees.h"
#include "mainwindow.h"
#include "utilisateur.h"



namespace Ui {
class Connexion;
}

/**
 * @brief Permet de gérer la connexion utilisateur
 */
class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = 0);
    ~Connexion();
    /**
     * @brief carriste
     */
    Utilisateur * carriste;

    /**
     * @brief setBaseDeDonnees
     */
    void setBaseDeDonnees(BaseDeDonnees*);

private slots:
    /**
     * @brief on_seConnecter_clicked
     * Permet d'établir la connexion de l'utilisateur à l'application
     */
    void on_seConnecter_clicked();

private:

    /**
     * @brief ui
     */
    Ui::Connexion *ui;

    /**
     * @brief bdd
     */
    BaseDeDonnees *bdd;
};

#endif // CONNEXION_H
