#ifndef DATABASE_H
#define DATABASE_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QMessageBox>
#include "utilisateur.h"
#include "produits.h"
#include "fournisseur.h"

class database : public QMainWindow
{
    public:
        database();
        virtual ~database();
        QSqlDatabase stockup;
        void createTable();
        void searchProductName(QString searchName);
        void searchReference(QString chercherReference);
        void deleteReference(QString deleteP);
        void chercherFournisseur(QString trouverFournisseur);
        void updateReference(QString rowid, QString ref, QString name, QString date2, QString loc, QString pack, QString quant, QString state2, QString dluo2, QString lot2, QString pattern2);
        void insertProductValue(Produits &produit);
        void connClose();
        bool connOpen();
        void createUser(Utilisateur &employe);
        void createProvider(Fournisseur &livreur);





    protected:

    private:

};

#endif // DATABASE_H
