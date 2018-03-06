#ifndef DATABASE_H
#define DATABASE_H
#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QtSql/QtSql>
#include <QtDebug>


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
        void connClose()
        {
            stockup.close();
            stockup.removeDatabase(QSqlDatabase::defaultConnection);

        }
        bool connOpen()
        {
            QSqlDatabase stockup = QSqlDatabase::addDatabase("QSQLITE");
            stockup.setDatabaseName("C:/STOCKUP/stockup/stockup.db");
            if(!stockup.open())
            {
                qDebug()<<("Non connecté");
                return false;
            }
            else
            {
                qDebug()<<("Connecté");
                return true;
            }
        }

       // bool insertProduit(std::string name, float reference, int quantity, std::string lot);
        bool deleteProduit(int id);



    protected:

    private:

};

#endif // DATABASE_H
