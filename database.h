#ifndef DATABASE_H
#define DATABASE_H
#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QtSql>
#include <QtDebug>

class database : public QMainWindow
{
    public:
        database();
        virtual ~database();

        void createTable();
        void insertProductValue(QString reference, QString date, QString hour, QString location, QString packaging, QString quantity, QString state, QString dluo, QString lot, QString pattern);

        QString dbfile;
        QString fichierbdd;
       // bool insertProduit(std::string name, float reference, int quantity, std::string lot);
        bool deleteProduit(int id);



    protected:

    private:
        QSqlDatabase stockup;

};

#endif // DATABASE_H
