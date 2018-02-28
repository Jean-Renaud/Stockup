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
        QSqlDatabase stockup;
        bool openDatabase();
        void closeDatabase();
        std::string dbfile;
        bool insertProduit(std::string name, float reference, int quantity, std::string lot);
        bool deleteProduit(int id);
    protected:

    private:

};

#endif // DATABASE_H
