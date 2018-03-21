#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "utilisateur.h"
#include "produits.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QtSql/QtSql>
#include <QModelIndex>
#include <QWidget>
#include <QSqlRecord>
#include <QDateTime>
#include <QDate>
#include <QDateEdit>
#include <QIcon>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database maBdd;

    maBdd.creerTableBdd();

    QMenu *menuFile = menuBar()->addMenu("&Fichier");


    QAction *actionQuit = new QAction("&Quitter", this);
    menuFile->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuit->setIcon(QIcon("quit.png"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_Create_clicked()
{
   Produits *produit = new Produits      (ui->reference_Product->text(),
                                          ui->nomProduit_2->text(),                                         
                                          ui->lot->text(),
                                          ui->date->date(),
                                          ui->hour->text(),
                                          ui->location->text(),
                                          ui->packaging->currentText(),
                                          ui->quantity->text(),
                                          ui->state->currentText(),
                                          ui->dluo->text(),
                                          ui->codeFournisseur->text());
   database bdd;
   bdd.creerUneReference(*produit);
}



void MainWindow::on_search_Database_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->clear();
        database bdd;
        bdd.ouvertureBdd();
        QSqlQuery listRef;
        QString searchRef = ui->searchRef->text();
        listRef.prepare("SELECT * FROM matieres_Premieres WHERE Reference = :reference");
        listRef.bindValue(":reference",searchRef);
        listRef.exec();
         modal->setQuery(listRef);
           ui->listDatabase->setModel(modal);

       bdd.fermetureBdd();
}



void MainWindow::on_search_Location_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
        database bdd;
        bdd.ouvertureBdd();
        QSqlQuery listLoc;

        QString searchLocation = ui->searchLocation->text();
        listLoc.prepare("SELECT * FROM matieres_Premieres WHERE Emplacement = :location");
        listLoc.bindValue(":location",searchLocation);
        listLoc.exec();
        modal->setQuery(listLoc);
        ui->listDatabase->setModel(modal);
        bdd.fermetureBdd();
}



void MainWindow::on_listDatabase_activated(const QModelIndex &index)
{

    QString val = ui->listDatabase->model()->data(index).toString();
    database bdd;
        bdd.ouvertureBdd();
        QSqlQuery query;
        query.prepare("SELECT id_Produit, Reference, Nom, Date ,Emplacement, Emballage, Quantite, Etat, DLUO, Lot, Code_fournisseur FROM matieres_Premieres where id_Produit ='"+val+"'or Reference='"+val+"' or Nom ='"+val+"' or Lot='"+val+"' or Date='"+val+"' or Emplacement ='"+val+"' or Emballage='"+val+"' or Quantite='"+val+"' or Etat ='"+val+"'or DLUO='"+val+"' or Code_fournisseur ='"+val+"'");
        query.exec();
        while(query.next())
        {
            switch (carriste->groupe.toInt())
            {
                case 3:
                    this->disableFormCarriste();
                break;
                case 4:
                this->disableFormQualite();
                break;
            }
            ui->id->setText(query.value(0).toString());
            ui->ref->setText(query.value(1).toString());
            ui->nomProduit->setText(query.value(2).toString());
            ui->date_2->setText(query.value(3).toString());
            ui->emplacement->setText(query.value(4).toString());
            ui->packaging_2->setText(query.value(5).toString());
            ui->quantite->setText(query.value(6).toString());
            ui->etat->setText(query.value(7).toString());
            ui->dluo_2->setText(query.value(8).toString());
            ui->lot_2->setText(query.value(9).toString());
            ui->codef->setText(query.value(10).toString());
        }

        bdd.fermetureBdd();

}



void MainWindow::on_update_row_clicked()
{
    QString rowid = ui->id->text();
    QString reference = ui->ref->text();
    QString nom =ui->nomProduit->text();
    QString date = ui->date_2->text();
    QString emplacement = ui->emplacement->text();
    QString emballage = ui->packaging_2->text();
    QString quantite = ui->quantite->text();
    QString etat = ui->etat->text();
    QString dluo = ui->dluo_2->text();
    QString lot = ui->lot_2->text();
    QString codeFournisseur = ui->codef->text();

    database bdd;
    bdd.miseAjourReference(rowid, reference, nom, date, emplacement, emballage, quantite, etat, dluo, lot, codeFournisseur);

}



void MainWindow::on_majFournisseur_clicked()
{
    Fournisseur *livreur2 = new Fournisseur(   ui->idfournisseur->text(),
                                               ui->cfournisseur->text(),
                                               ui->nomsociete->text(),
                                               ui->formejuridique->text(),
                                               ui->adresseedit->text(),
                                               ui->codepostal->text(),
                                               ui->villefournisseur->text(),
                                               ui->paysfournisseur->text(),
                                               ui->telephonefournisseur->text(),
                                               ui->siretfournisseur->text(),
                                               ui->apefournisseur->text()
                                               );
    database bdd2;
    bdd2.miseAjourFournisseur(*livreur2);
}



void MainWindow::on_majUtilisateur_clicked()
{
    Utilisateur *mettreAjourUtilisateur = new Utilisateur(ui->idUtilisateurEdit->text(),
                                               ui->codeUtilisateurEdit->text(),
                                               ui->nomUtilisateurEdit->text(),
                                               ui->prenomUtilisateurEdit->text(),
                                               ui->mdpUtilisateurEdit->text(),
                                               ui->groupeUtilisateurEdit->text()
                                               );
    database bdd2;
    bdd2.miseAJourUtilisateur(*mettreAjourUtilisateur);
}



void MainWindow::on_deleteProduct_clicked()
{

        int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock, cette action est irreversible. Cliquez sur Ok pour confirmer ou sur No pour annuler.", QMessageBox::Ok | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QString supprimerRef = ui->id->text();
            database bdd;
            bdd.supprimerReference(supprimerRef);

            QMessageBox::information(this,tr("Succès"),tr("La suppression du produit a bien été effectuée."));

        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::critical(this, "Confirmation", "Le produit n'a pas été supprimé.");
        }
}



void MainWindow::on_searchNameProduct_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    clearFocus();
        database mabd;
        mabd.ouvertureBdd();
        QSqlQuery listeRechercheNomProduit;

        QString searchName = ui->searchByName->text();
        listeRechercheNomProduit.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercheNom LIKE '%' ");
        listeRechercheNomProduit.bindValue(":chercheNom",searchName);
        listeRechercheNomProduit.exec();
        modal->setQuery(listeRechercheNomProduit);
        ui->listDatabase->setModel(modal);
        ui->listDatabase->verticalHeader()->setVisible(false);
        mabd.fermetureBdd();
}



void MainWindow::on_chercheUtilisateur_clicked()
{
    QSqlQueryModel * modal3 = new QSqlQueryModel();
    clearFocus();
    database mabd;
    mabd.ouvertureBdd();
    QSqlQuery chercherUnUtilisateur;
    QString trouverUtilisateur = ui->chercheUtilisateurEdit->text();
    chercherUnUtilisateur.prepare("SELECT * FROM utilisateurs WHERE Nom = :nom");
    chercherUnUtilisateur.bindValue(":nom",trouverUtilisateur);
    chercherUnUtilisateur.exec();
    modal3->setQuery(chercherUnUtilisateur);
    ui->gestionUtilisateur->setModel(modal3);
    mabd.fermetureBdd();
}



void MainWindow::on_createUser_clicked()
{
    Utilisateur *employe = new Utilisateur(ui->idUtilisateurEdit->text(),
                                           ui->code->text(),
                                           ui->nomUtilisateur->text(),
                                           ui->prenom->text(),
                                           ui->mdp->text(),
                                           ui->groupe->text()
                                           );
    database bdd;
    bdd.creerUnUtilisateur(*employe);
}



void MainWindow::on_creerFournisseur_clicked()
{
    Fournisseur *livreur = new Fournisseur(   ui->idfournisseur->text(),
                                               ui->codeDuFournisseur->text(),
                                               ui->nomSociete->text(),
                                               ui->formeJuridique->text(),
                                               ui->adresse->text(),
                                               ui->codePostal->text(),
                                               ui->ville->text(),
                                               ui->pays->text(),
                                               ui->telephone->text(),
                                               ui->siret->text(),
                                               ui->ape->text()
                                               );
    database bdd2;
    bdd2.creerUnFournisseur(*livreur);
}



void MainWindow::on_gestionUtilisateur_activated(const QModelIndex &index)
{
    QString val2 = ui->gestionUtilisateur->model()->data(index).toString();

        database bdd;
        bdd.ouvertureBdd();
        QSqlQuery cherche;
        cherche.prepare("SELECT id, Code, Nom, Prenom, Mot_de_Passe, Groupe FROM utilisateurs WHERE id ='"+val2+"' or Code='"+val2+"' or Nom ='"+val2+"' or Prenom='"+val2+"' or Mot_de_Passe ='"+val2+"' or Groupe='"+val2+"'");
        cherche.exec();

        while(cherche.next())
        {
            qDebug() << "groupe " << carriste->groupe;
            ui->idUtilisateurEdit->setText(cherche.value(0).toString());
            ui->codeUtilisateurEdit->setText(cherche.value(1).toString());
            ui->nomUtilisateurEdit->setText(cherche.value(2).toString());
            ui->prenomUtilisateurEdit->setText(cherche.value(3).toString());
            ui->mdpUtilisateurEdit->setText(cherche.value(4).toString());
            ui->groupeUtilisateurEdit->setText(cherche.value(5).toString());

        }

        bdd.fermetureBdd();
}



void MainWindow::on_listProvider_activated(const QModelIndex &index)
{

    QString val = ui->listProvider->model()->data(index).toString();

    database bdd;
        bdd.ouvertureBdd();
        QSqlQuery query;
        query.prepare("SELECT id, Code, Nom, Forme_juridique ,Adresse, Code_postal, Pays, Ville, Telephone, Siret, APE "
                      "FROM fournisseurs where id ='"+val+"'or code='"+val+"' or Nom ='"+val+"' or Forme_juridique='"+val+"' "
                      "or Adresse ='"+val+"' or Code_postal='"+val+"' or Pays='"+val+"' or Ville ='"+val+"'or Telephone='"+val+"'"
                      " or Siret='"+val+"' or APE ='"+val+"'");
        query.exec();
        while(query.next())
        {
            ui->idfournisseur->setText(query.value(0).toString());
            ui->cfournisseur->setText(query.value(1).toString());
            ui->nomsociete->setText(query.value(2).toString());
            ui->formejuridique->setText(query.value(3).toString());
            ui->adresseedit->setText(query.value(4).toString());
            ui->codepostal->setText(query.value(5).toString());
            ui->villefournisseur->setText(query.value(6).toString());
            ui->paysfournisseur->setText(query.value(7).toString());
            ui->telephonefournisseur->setText(query.value(8).toString());
            ui->siretfournisseur->setText(query.value(9).toString());
            ui->apefournisseur->setText(query.value(10).toString());
        }

        bdd.fermetureBdd();
}



void MainWindow::on_fournisseur_clicked()
 {
     QSqlQueryModel * modal2 = new QSqlQueryModel();
     clearFocus();
     database data50;
     data50.ouvertureBdd();
     QSqlQuery listeFournisseurParCode;
     QString chercherFournisseur = ui->trouverfournisseur->text();
     listeFournisseurParCode.prepare("SELECT * FROM fournisseurs WHERE Code = :code");
     listeFournisseurParCode.bindValue(":code",chercherFournisseur);
     listeFournisseurParCode.exec();
     modal2->setQuery(listeFournisseurParCode);
     ui->listProvider->setModel(modal2);
     data50.fermetureBdd();
 }



void MainWindow::on_voirStock_clicked()
{
    QSqlQueryModel * triAlphaproduits = new QSqlQueryModel();
    clearFocus();
    database mabdd;
    mabdd.ouvertureBdd();
    QSqlQuery triAlphaProduits;
    triAlphaProduits.prepare("SELECT * FROM matieres_Premieres ORDER BY Nom");
    triAlphaProduits.exec();
    triAlphaproduits->setQuery(triAlphaProduits);
    ui->listDatabase->setModel(triAlphaproduits);
    mabdd.fermetureBdd();
}



void MainWindow::on_suppFournisseur_clicked()
{
    int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock, cette action est irreversible. Cliquez sur OUI pour confirmer ou sur NON pour annuler.", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        Fournisseur *livreur3 = new Fournisseur(ui->idfournisseur->text(),
                                                ui->cfournisseur->text(),
                                                ui->nomsociete->text(),
                                                ui->formejuridique->text(),
                                                ui->adresseedit->text(),
                                                ui->codepostal->text(),
                                                ui->villefournisseur->text(),
                                                ui->paysfournisseur->text(),
                                                ui->telephonefournisseur->text(),
                                                ui->siretfournisseur->text(),
                                                ui->apefournisseur->text()

                    );
        database bdd2;
        bdd2.supprimerUnFournisseur(*livreur3);
        QMessageBox::information(this,tr("Succès"),tr("La suppression du fournisseur a bien été effectuée."));
        ui->fournisseur->clicked();
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::critical(this, "Confirmation", "Le fournisseur n'a pas été supprimé.");
    }
}



void MainWindow::on_suppUtilisateur_clicked()
{
    int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock, cette action est irreversible. Cliquez sur OUI pour confirmer ou sur NON pour annuler.", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        Utilisateur *supprimerUtilisateur = new Utilisateur(ui->idUtilisateurEdit->text(),
                                                            ui->code->text(),
                                                            ui->nomUtilisateur->text(),
                                                            ui->prenom->text(),
                                                            ui->mdp->text(),
                                                            ui->groupe->text()
                                                            );

        database bdd2;
        bdd2.supprimerUnUtilisateur(*supprimerUtilisateur);
        QMessageBox::information(this,tr("Succès"),tr("La suppression du fournisseur a bien été effectuée."));
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::critical(this, "Confirmation", "Le fournisseur n'a pas été supprimé.");
    }
}



void MainWindow::on_triAlphaUtilisateur_clicked()
{
    QSqlQueryModel * triAlphautilisateur = new QSqlQueryModel();
    clearFocus();
    database mabdd;
    mabdd.ouvertureBdd();
    QSqlQuery triAlphaUtilisateur;
    triAlphaUtilisateur.prepare("SELECT * FROM utilisateurs ORDER BY Nom");
    triAlphaUtilisateur.exec();
    triAlphautilisateur->setQuery(triAlphaUtilisateur);
    ui->gestionUtilisateur->setModel(triAlphautilisateur);
    mabdd.fermetureBdd();
}



void MainWindow::on_triAlphaFournisseur_clicked()
{
    QSqlQueryModel * triAlphafournisseur = new QSqlQueryModel();
    clearFocus();
    database mabdd;
    mabdd.ouvertureBdd();
    QSqlQuery triAlphaFournisseur;
    triAlphaFournisseur.prepare("SELECT * FROM fournisseurs ORDER BY Nom");
    triAlphaFournisseur.exec();
    triAlphafournisseur->setQuery(triAlphaFournisseur);
    ui->listProvider->setModel(triAlphafournisseur);
    mabdd.fermetureBdd();
}



void MainWindow::disableTab(int index)
{
    ui->tabGestionStock->setTabEnabled(index, false);
}



void MainWindow::moveToTab(int index)
{
    ui->tabGestionStock->setCurrentIndex(index);
}



void MainWindow::disableFormCarriste() {
    ui->id->setEnabled(false);
    ui->nomProduit->setEnabled(false);
    ui->ref->setEnabled(false);
    ui->nomProduit->setEnabled(false);
    ui->date_2->setEnabled(false);
    ui->packaging_2->setEnabled(false);
    ui->etat->setEnabled(false);
    ui->dluo_2->setEnabled(false);
    ui->lot_2->setEnabled(false);
    ui->codef->setEnabled(false);
    ui->deleteProduct->setEnabled(false);

}



void MainWindow::disableFormQualite()
{
    ui->id->setEnabled(false);
    ui->nomProduit->setEnabled(false);
    ui->ref->setEnabled(false);
    ui->nomProduit->setEnabled(false);
    ui->date_2->setEnabled(false);
    ui->emplacement->setEnabled(false);
    ui->packaging_2->setEnabled(false);
    ui->quantite->setEnabled(false);
    ui->dluo_2->setEnabled(false);
    ui->lot_2->setEnabled(false);
    ui->codef->setEnabled(false);
    ui->deleteProduct->setEnabled(false);
}



void database::insertionUtilisateur()
{
    QSqlQuery connexion;
    connexion.exec("SELECT COUNT(id) FROM utilisateurs");

    connexion.next();

    int presentDansLaBdd = connexion.value(0).toInt();
    if(presentDansLaBdd == 0)
    {

        connexion.exec("INSERT INTO utilisateurs (Code, Nom, Prenom, Mot_de_Passe, Groupe) "
                       "VALUES (01, 'Admin', 'adm', 1, 5)");

    }
}
