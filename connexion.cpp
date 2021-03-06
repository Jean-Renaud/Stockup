#include "connexion.h"
#include "ui_connexion.h"
#include "basededonnees.h"
#include "utilisateur.h"
#include "mainwindow.h"
#include <QMainWindow>

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    ui->seConnecter->setCursor(Qt::PointingHandCursor);
}

Connexion::~Connexion()
{
    delete ui;
}

/*Permet d'établir la connexion lorsqu'on clique sur le bouton se connecter après une vérification de l'existence du compte utilisateur*/
void Connexion::on_seConnecter_clicked()
{
    QString codeUtilisateur;
    QString motDePasse;
    codeUtilisateur = ui->codeConnexion->text();
    motDePasse = ui->motDePasseConnexion->text();

    QSqlQuery connexion(this->bdd->stockup);
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
            this->carriste->setCode(connexion.value(0).toString());
            this->carriste->setGroupe(connexion.value(1).toString());
            this->accept();
            this->close();
        }
        if(compteur < 1)
        {
            ui->verifConnexion->setText("Le code ou le mot de passe est incorrect");
        }
    }
}

void Connexion::setBaseDeDonnees(BaseDeDonnees *bdd) {
    this->bdd = bdd;
}
