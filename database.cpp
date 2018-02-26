#include "database.h"
#include <QtSql/QSql>
#include <iostream>

database::database()
{
    //ctor
    dbfile = "./database.db";
    void database::openDatabase()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
            bool ok = db.open();
    }
}

database::~database()
{
    //dtor
}



