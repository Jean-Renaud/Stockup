#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QtSql/QtSql>

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
