#ifndef CONNEXION_H
#define CONNEXION_H
#include <QDialog>
#include "database.h"
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


private slots:

    void on_seConnecter_clicked();

private:
    Ui::Connexion *ui;
    QSqlDatabase stockup;
};

#endif // CONNEXION_H
