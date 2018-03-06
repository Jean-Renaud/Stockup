#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
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
   QString reference = ui->reference_Product->text();
   QString date = ui->date->text();
   QString hour = ui->hour->text();
   QString location = ui->location->text();
   QString packaging = ui->packaging->text();
   QString quantity = ui->quantity->text();
   QString state = ui->state->currentText();
   QString dluo = ui->dluo->text();
   QString lot = ui->lot->text();
   QString pattern = ui->pattern->currentText();

   database data;
   data.insertProductValue(reference, date, hour, location, packaging, quantity, state, dluo, lot, pattern);




}



void MainWindow::on_search_Database_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->clear();
        database mabd;
        mabd.connOpen();
        QSqlQuery listRef;
        QString searchRef = ui->searchRef->text();
        listRef.prepare("SELECT * FROM product WHERE reference = :reference");
        listRef.bindValue(":reference",searchRef);
        listRef.exec();
        modal->setQuery(listRef);
        ui->listDatabase->setModel(modal);
        mabd.connClose();
}

void MainWindow::on_search_Location_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel();
        database mabd;
        mabd.connOpen();
        QSqlQuery listLoc;

        QString searchLocation = ui->searchLocation->text();
        listLoc.prepare("SELECT * FROM product WHERE location = :location");
        listLoc.bindValue(":location",searchLocation);
        listLoc.exec();
        modal->setQuery(listLoc);
        ui->listDatabase->setModel(modal);
        mabd.connClose();


}

void MainWindow::on_listDatabase_activated(const QModelIndex &index)
{
    QString val = ui->listDatabase->model()->data(index).toString();
    clearFocus();
    database madb;
        madb.connOpen();
        QSqlQuery query;
        query.prepare("SELECT id_Product,reference,date,location,packaging,quantity,state,dluo,lot,pattern FROM product where id_Product ='"+val+"'or reference='"+val+"' or date='"+val+"' or location ='"+val+"' or packaging='"+val+"' or quantity='"+val+"' or state ='"+val+"'or dluo='"+val+"' or lot='"+val+"' or pattern ='"+val+"'");
        query.exec();

        while(query.next())
        {

            ui->id->setText(query.value(0).toString());
            ui->ref->setText(query.value(1).toString());
            ui->date_2->setText(query.value(2).toString());
            ui->emplacement->setText(query.value(3).toString());
            ui->packaging_2->setText(query.value(4).toString());
            ui->quantite->setText(query.value(5).toString());
            ui->etat->setText(query.value(6).toString());
            ui->dluo_2->setText(query.value(7).toString());
            ui->lot_2->setText(query.value(8).toString());
            ui->information->setText(query.value(9).toString());

        }

        madb.connClose();

}

void MainWindow::on_update_row_clicked()
{
    QString rowid = ui->id->text();

    QString ref = ui->ref->text();
    QString date2 = ui->date_2->text();
    QString loc = ui->emplacement->text();
    QString pack = ui->packaging_2->text();
    QString quant = ui->quantite->text();
    QString state2 = ui->etat->text();
    QString dluo2 = ui->dluo_2->text();
    QString lot2 = ui->lot_2->text();
    QString pattern2 = ui->information->text();

    database data23;
    data23.updateReference(rowid, ref, date2, loc, pack, quant, state2, dluo2, lot2, pattern2);

}

void MainWindow::on_deleteProduct_clicked()
{
    QString deleteP = ui->id->text();


    /*QString refDel = ui->ref->text();
    QString dateDel = ui->date_2->text();
    QString locDel = ui->emplacement->text();
    QString packDel = ui->packaging_2->text();
    QString quantDel = ui->quantite->text();
    QString stateDel = ui->etat->text();
    QString dluoDel = ui->dluo_2->text();
    QString lotDel = ui->lot_2->text();
    QString patternDel = ui->information->text();*/
    database data25;
    data25.deleteReference(deleteP);

}
