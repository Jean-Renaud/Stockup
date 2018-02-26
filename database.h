#ifndef DATABASE_H
#define DATABASE_H
#include "mainwindow.h"
#include <QApplication>
#include <QtSql/qsql.h>

class database
{
    public:
        database();
        virtual ~database();

        void openDatabase();
        void closeDatabase();
        bool executeQuery(std::string query);
        std::string dbfile;
        bool insertProduit(std::string name, float reference, int quantity, std::string lot);
        bool deleteProduit(int id);
    protected:

    private:

};

#endif // DATABASE_H
