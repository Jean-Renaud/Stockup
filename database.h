#ifndef DATABASE_H
#define DATABASE_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QMessageBox>
#include "utilisateur.h"

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
        void updateReference(QString rowid, QString ref, QString name, QString date2, QString loc, QString pack, QString quant, QString state2, QString dluo2, QString lot2, QString pattern2);
        void insertProductValue(QString Reference, QString Nom, QString Date, QString Heure, QString Emplacement, QString Emballage, QString Quantite, QString Etat, QString DLUO, QString Lot, QString Information);
        void connClose();
        bool connOpen();
        void createUser(Utilisateur &employe);



    protected:

    private:

};

#endif // DATABASE_H
