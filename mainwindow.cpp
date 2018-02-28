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

bool database::openDatabase()
{
    QSqlDatabase stockup = QSqlDatabase::addDatabase("QSQLITE");
    stockup.setDatabaseName(QApplication::applicationDirPath() + "/stockup.db");


}

void database::closeDatabase()

{
    stockup.close();
}

void MainWindow::on_button_Create_clicked()
{

    QString reference,date_creation,emplacement, quantite,etat,dluo,lot;
    reference=ui->reference_Product->text();
    date_creation=ui->date_creation->text();
    emplacement=ui->location->text();
    quantite=ui->quantity->text();
    etat=ui->state->text();
    dluo=ui->dluo->text();
    lot=ui->pattern->text();
    database connectToDatabase;
    QSqlQuery Insert_Product;
    Insert_Product.exec("INSERT INTO Product (reference,creation_date,location,quantity,stat,DLUO,pattern)" "VALUES (:reference,:date_creation,:emplacement,:quantite,:etat,:dluo,:lot)");

    if(!Insert_Product.exec())

         QMessageBox::critical(this,tr("Erreur"),tr("Il y a eu un problème avec la création du nouveau produit."));


    else
         QMessageBox::information(this,tr("Création réussie"),tr("La création du produit a été enregistrée avec succès."));



}
