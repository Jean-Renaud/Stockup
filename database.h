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
        void insertProductValue(QString reference);

        QString dbfile;
        QString fichierbdd;
        bool insertProduit(std::string name, float reference, int quantity, std::string lot);
        bool deleteProduit(int id);



    protected:

    private:
        QSqlDatabase stockup;

};

#endif // DATABASE_H
