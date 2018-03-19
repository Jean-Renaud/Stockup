#include "connexion.h"
#include "ui_connexion.h"
#include "database.h"
#include "mainwindow.h"
#include <QMainWindow>

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);

}

Connexion::~Connexion()
{
    delete ui;
}
void Connexion::on_seConnecter_clicked()
{
   database bddConnexion;
   QString codeUtilisateur;
   QString motDepasse;
    codeUtilisateur = ui->codeConnexion->text();
    motDepasse = ui->motDePasseConnexion->text();
    if (!bddConnexion.connOpen())
   {
        qDebug() <<"Echec de l'ouverture de la base de données.";
        return;
    }

    QSqlQuery connexion;
    connexion.prepare("SELECT * FROM utilisateurs WHERE Code = :code AND Mot_de_Passe = :mdp");
    connexion.bindValue(":code", codeUtilisateur);
    connexion.bindValue(":mdp", motDepasse);
    if(connexion.exec())
    {
        int compteur = 0;
        while (connexion.next())
        {
          compteur++;
        }
        if(compteur == 1)
        {
            ui->verifConnexion->setText("L'utilisateur est bien connecté");
            this->accept();

            this->close();
            //MainWindow fenetrePrincipale;
            //fenetrePrincipale.show();
        }
        if(compteur < 1)
        {
            ui->verifConnexion->setText("Le code ou le mot de passe est incorrect");
        }
    }
    bddConnexion.connClose();

}