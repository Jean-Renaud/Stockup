#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "utilisateur.h"
#include "produits.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QtSql/QtSql>
#include <QModelIndex>
#include <QWidget>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database maBdd;

    maBdd.createTable();

    QMenu *menuFile = menuBar()->addMenu("&Fichier");

    QAction *actionLogout = new QAction("&Deconnexion", this);
    menuFile->addAction(actionLogout);
    QAction *actionQuit = new QAction("&Quitter", this);
    menuFile->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuit->setIcon(QIcon("quit.png"));

    QMenu *menuEdition = menuBar()->addMenu("&Produit");
    QAction *actionSearchProduct = new QAction("&Rechercher", this);
    menuEdition->addAction(actionSearchProduct);
    QAction *actionCreateProduct = new QAction("&Créer un produit", this);
    menuEdition->addAction(actionCreateProduct);
    QAction *actionUpdateProduct = new QAction("&Modifier un produit", this);
    menuEdition->addAction(actionUpdateProduct);
    QAction *actionDeleteProduct = new QAction("&Supprimer un produit", this);
    menuEdition->addAction(actionDeleteProduct);

    QMenu *menuUsers = menuBar()->addMenu("&Utilisateur");
    QAction *actionSearchUser = new QAction("&Rechercher un utilisateur", this);
    menuUsers->addAction(actionSearchUser);
    QAction *actionCreateUser = new QAction("&Créer un utilisateur", this);
    menuUsers->addAction(actionCreateUser);
    QAction *actionUpdateUser = new QAction("&Modifier un utilisateur", this);
    menuUsers->addAction(actionUpdateUser);
    QAction *actionDeleteUser = new QAction("&Supprimer un utilisateur", this);
    menuUsers->addAction(actionDeleteUser);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_Create_clicked()
{
  /* QString Reference = ui->reference_Product->text();
   QString Nom = ui->nomProduit_2->text();
   QString Date = ui->date->text();
   QString Heure = ui->hour->text();
   QString Emplacement = ui->location->text();
   QString Emballage = ui->packaging->text();
   QString Quantite = ui->quantity->text();
   QString Etat = ui->state->currentText();
   QString DLUO = ui->dluo->text();
   QString Lot = ui->lot->text();
   QString Information = ui->pattern->currentText();*/

   Produits *produit = new Produits (ui->reference_Product->text(),
                                          ui->nomProduit_2->text(),
                                          ui->date->text(),
                                          ui->hour->text(),
                                          ui->location->text(),
                                          ui->packaging->text(),
                                          ui->quantity->text(),
                                          ui->state->currentText(),
                                          ui->dluo->text(),
                                          ui->lot->text(),
                                          ui->codeFournisseur->text());

   database bdd;
   bdd.insertProductValue(*produit);


   /*database bdd;
   bdd.insertProductValue(Reference, Nom, Date, Heure, Emplacement, Emballage, Quantite, Etat, DLUO, Lot, Information);*/




}



void MainWindow::on_search_Database_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->clear();
        database bdd;
        bdd.connOpen();
        QSqlQuery listRef;
        QString searchRef = ui->searchRef->text();
        listRef.prepare("SELECT * FROM matieres_Premieres WHERE Reference = :reference");
        listRef.bindValue(":reference",searchRef);
        listRef.exec();
        modal->setQuery(listRef);
        ui->listDatabase->setModel(modal);
        ui->listDatabase->resizeColumnsToContents();
        bdd.connClose();
}

void MainWindow::on_search_Location_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel();
        database bdd;
        bdd.connOpen();
        QSqlQuery listLoc;

        QString searchLocation = ui->searchLocation->text();
        listLoc.prepare("SELECT * FROM matieres_Premieres WHERE Emplacement = :location");
        listLoc.bindValue(":location",searchLocation);
        listLoc.exec();
        modal->setQuery(listLoc);
        ui->listDatabase->setModel(modal);
        bdd.connClose();


}

void MainWindow::on_listDatabase_activated(const QModelIndex &index)
{
    QString val = ui->listDatabase->model()->data(index).toString();
    ui->listDatabase->resizeColumnsToContents();
    clearFocus();
    database bdd;
        bdd.connOpen();
        QSqlQuery query;
        query.prepare("SELECT id_Produit, Reference, Nom, Date ,Emplacement, Emballage, Quantite, Etat, DLUO, Lot, Code_fournisseur FROM matieres_Premieres where id_Produit ='"+val+"'or Reference='"+val+"' or Nom ='"+val+"' or Date='"+val+"' or Emplacement ='"+val+"' or Emballage='"+val+"' or Quantite='"+val+"' or Etat ='"+val+"'or DLUO='"+val+"' or Lot='"+val+"' or Code_fournisseur ='"+val+"'");
        query.exec();

        while(query.next())
        {

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

        bdd.connClose();

}

void MainWindow::on_update_row_clicked()
{
    QString rowid = ui->id->text();
    QString ref = ui->ref->text();
    QString name =ui->nomProduit->text();
    QString date2 = ui->date_2->text();
    QString loc = ui->emplacement->text();
    QString pack = ui->packaging_2->text();
    QString quant = ui->quantite->text();
    QString state2 = ui->etat->text();
    QString dluo2 = ui->dluo_2->text();
    QString lot2 = ui->lot_2->text();
    QString pattern2 = ui->codef->text();

    database bdd;
    bdd.updateReference(rowid, ref, name, date2, loc, pack, quant, state2, dluo2, lot2, pattern2);

}

void MainWindow::on_deleteProduct_clicked()
{
    QString deleteP = ui->id->text();
    database bdd;

    database data25;
    bdd.deleteReference(deleteP);

}

void MainWindow::on_searchNameProduct_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
        database mabd;
        mabd.connOpen();
        QSqlQuery listNom;

        QString searchName = ui->searchByName->text();
        listNom.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercheNom");
        listNom.bindValue(":chercheNom",searchName);
        listNom.exec();
        modal->setQuery(listNom);
        ui->listDatabase->setModel(modal);
        ui->listDatabase->resizeColumnsToContents();
        mabd.connClose();

}
void MainWindow::on_createUser_clicked()
{
    Utilisateur *employe = new Utilisateur(ui->code->text().toInt(),
                                           ui->nomUtilisateur->text(),
                                           ui->prenom->text(),
                                           ui->mdp->text(),
                                           ui->groupe->text().toInt()
                                           );


    database bdd;
    bdd.createUser(*employe);
}

void MainWindow::on_creerFournisseur_clicked()
{
    Fournisseur *livreur = new Fournisseur(ui->codeDuFournisseur->text(),
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
    bdd2.createProvider(*livreur);

}
