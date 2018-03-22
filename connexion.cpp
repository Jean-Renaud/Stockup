#include "connexion.h"
#include "ui_connexion.h"
#include "database.h"
#include "utilisateur.h"
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
   QString motDePasse;
    codeUtilisateur = ui->codeConnexion->text();
    motDePasse = ui->motDePasseConnexion->text();
    if (!bddConnexion.ouvertureBdd())
   {
        qDebug() <<"Echec de l'ouverture de la base de données.";
        return;
    }

    QSqlQuery connexion;
    connexion.prepare("SELECT Code, Groupe FROM utilisateurs WHERE Code = :code AND Mot_de_Passe = :mdp");
    connexion.bindValue(":code", codeUtilisateur);
    connexion.bindValue(":mdp", motDePasse);
    if(connexion.exec())
    {
        int compteur = 0;
        while (connexion.next())
        {
          compteur++;
        }
        if(compteur == 1)
        {
            connexion.previous();
            ui->verifConnexion->setText("L'utilisateur est bien connecté");

            this->carriste = new Utilisateur();
            this->carriste->getCode() = connexion.value(0).toString();
            this->carriste->getMdp() = connexion.value(1).toString();

            this->accept();

            this->close();

        }
        if(compteur < 1)
        {
            ui->verifConnexion->setText("Le code ou le mot de passe est incorrect");
        }
    }
    bddConnexion.fermetureBdd();

}
