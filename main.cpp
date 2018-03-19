#include "mainwindow.h"
#include <QApplication>
#include <connexion.h>
#include "database.h"
#include <iostream>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Connexion Login;
    MainWindow fenetrePrincipale;
   if (Login.exec() == QDialog::Accepted)
    {
        fenetrePrincipale.show();
    }
   else
    {
       return 0;
    }
    return a.exec();
}
