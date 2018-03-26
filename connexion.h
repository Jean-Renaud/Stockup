#ifndef CONNEXION_H
#define CONNEXION_H
#include <QDialog>
#include "basededonnees.h"
#include "mainwindow.h"
#include "utilisateur.h"

namespace Ui {
class Connexion;
}

class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = 0);
    ~Connexion();
    Utilisateur * carriste;

    void setBaseDeDonnees(BaseDeDonnees*);

private slots:

    void on_seConnecter_clicked();

private:
    Ui::Connexion *ui;
    BaseDeDonnees *bdd;
};

#endif // CONNEXION_H
