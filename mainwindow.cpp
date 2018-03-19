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
   Produits *produit = new Produits (ui->reference_Product->text(),
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
   bdd.insertProductValue(*produit);
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
    database bdd;
        bdd.connOpen();
        QSqlQuery query;
        query.prepare("SELECT id_Produit, Reference, Nom, Date ,Emplacement, Emballage, Quantite, Etat, DLUO, Lot, Code_fournisseur FROM matieres_Premieres where id_Produit ='"+val+"'or Reference='"+val+"' or Nom ='"+val+"' or Lot='"+val+"' or Date='"+val+"' or Emplacement ='"+val+"' or Emballage='"+val+"' or Quantite='"+val+"' or Etat ='"+val+"'or DLUO='"+val+"' or Code_fournisseur ='"+val+"'");
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
    bdd2.majProvider(*livreur2);
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
    bdd2.majUtilisateur(*mettreAjourUtilisateur);
}
void MainWindow::on_deleteProduct_clicked()
{

        int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock, cette action est irreversible. Cliquez sur OUI pour confirmer ou sur NON pour annuler.", QMessageBox::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QString deleteP = ui->id->text();
            database bdd;
            bdd.deleteReference(deleteP);
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
        mabd.connOpen();
        QSqlQuery listNom;

        QString searchName = ui->searchByName->text();
        listNom.prepare("SELECT * FROM matieres_Premieres WHERE Nom = :chercheNom LIKE '%' ");
        listNom.bindValue(":chercheNom",searchName);
        listNom.exec();
        modal->setQuery(listNom);
        ui->listDatabase->setModel(modal);
        //ui->listDatabase->resizeColumnsToContents();
        ui->listDatabase->verticalHeader()->setVisible(false);
        mabd.connClose();
}
void MainWindow::on_chercheUtilisateur_clicked()
{
    QSqlQueryModel * modal3 = new QSqlQueryModel();
    clearFocus();
    database mabd;
    mabd.connOpen();
    QSqlQuery chercherUnUtilisateur;
    QString trouverUtilisateur = ui->chercheUtilisateurEdit->text();
    chercherUnUtilisateur.prepare("SELECT * FROM utilisateurs WHERE Nom = :nom");
    chercherUnUtilisateur.bindValue(":nom",trouverUtilisateur);
    chercherUnUtilisateur.exec();
    modal3->setQuery(chercherUnUtilisateur);
    ui->gestionUtilisateur->setModel(modal3);
    mabd.connClose();
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
    bdd.createUser(*employe);
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
    bdd2.createProvider(*livreur);
}
void MainWindow::on_gestionUtilisateur_activated(const QModelIndex &index)
{
    QString val2 = ui->gestionUtilisateur->model()->data(index).toString();

        database bdd;
        bdd.connOpen();
        QSqlQuery cherche;
        cherche.prepare("SELECT id, Code, Nom, Prenom, Mot_de_Passe, Groupe FROM utilisateurs WHERE id ='"+val2+"' or Code='"+val2+"' or Nom ='"+val2+"' or Prenom='"+val2+"' or Mot_de_Passe ='"+val2+"' or Groupe='"+val2+"'");
        cherche.exec();

        while(cherche.next())
        {
            ui->idUtilisateurEdit->setText(cherche.value(0).toString());
            ui->codeUtilisateurEdit->setText(cherche.value(1).toString());
            ui->nomUtilisateurEdit->setText(cherche.value(2).toString());
            ui->prenomUtilisateurEdit->setText(cherche.value(3).toString());
            ui->mdpUtilisateurEdit->setText(cherche.value(4).toString());
            ui->groupeUtilisateurEdit->setText(cherche.value(5).toString());

        }

        bdd.connClose();
}
void MainWindow::on_listProvider_activated(const QModelIndex &index)
{

    QString val = ui->listProvider->model()->data(index).toString();

    database bdd;
        bdd.connOpen();
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

        bdd.connClose();
}
void MainWindow::on_fournisseur_clicked()
 {
     QSqlQueryModel * modal2 = new QSqlQueryModel();
     clearFocus();
     database data50;
     data50.connOpen();
     QSqlQuery listeFournisseur;
     QString chercherFournisseur = ui->trouverfournisseur->text();
     listeFournisseur.prepare("SELECT * FROM fournisseurs WHERE Code = :code");
     listeFournisseur.bindValue(":code",chercherFournisseur);
     listeFournisseur.exec();
     modal2->setQuery(listeFournisseur);
     ui->listProvider->setModel(modal2);
     data50.connClose();
 }
void MainWindow::on_voirStock_clicked()
{
    QSqlQueryModel * triAlphaproduits = new QSqlQueryModel();
    clearFocus();
    database mabdd;
    mabdd.connOpen();
    QSqlQuery triAlphaProduits;
    triAlphaProduits.prepare("SELECT * FROM matieres_Premieres ORDER BY Nom");
    triAlphaProduits.exec();
    triAlphaproduits->setQuery(triAlphaProduits);
    ui->listDatabase->setModel(triAlphaproduits);
    mabdd.connClose();
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
        bdd2.supFournisseur(*livreur3);
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
        bdd2.supUtilisateur(*supprimerUtilisateur);
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
    mabdd.connOpen();
    QSqlQuery triAlphaUtilisateur;
    triAlphaUtilisateur.prepare("SELECT * FROM utilisateurs ORDER BY Nom");
    triAlphaUtilisateur.exec();
    triAlphautilisateur->setQuery(triAlphaUtilisateur);
    ui->gestionUtilisateur->setModel(triAlphautilisateur);
    mabdd.connClose();
}
void MainWindow::on_triAlphaFournisseur_clicked()
{
    QSqlQueryModel * triAlphafournisseur = new QSqlQueryModel();
    clearFocus();
    database mabdd;
    mabdd.connOpen();
    QSqlQuery triAlphaFournisseur;
    triAlphaFournisseur.prepare("SELECT * FROM fournisseurs ORDER BY Nom");
    triAlphaFournisseur.exec();
    triAlphafournisseur->setQuery(triAlphaFournisseur);
    ui->listProvider->setModel(triAlphafournisseur);
    mabdd.connClose();
}
