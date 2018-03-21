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
        fenetrePrincipale.carriste = Login.carriste;
        qDebug() << fenetrePrincipale.carriste->groupe << " " << Login.carriste->groupe;

        if(fenetrePrincipale.carriste->groupe.toInt() == 1) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(0);
            fenetrePrincipale.disableTab(1);
            fenetrePrincipale.disableTab(4);
            fenetrePrincipale.disableTab(5);
            fenetrePrincipale.disableTab(6);
        }
        if(fenetrePrincipale.carriste->groupe.toInt() == 2) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(2);
            fenetrePrincipale.disableTab(3);


        }
        if(fenetrePrincipale.carriste->groupe.toInt() == 3) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(0);
            fenetrePrincipale.disableTab(2);
            fenetrePrincipale.disableTab(3);
            fenetrePrincipale.disableTab(4);
            fenetrePrincipale.disableTab(5);
            fenetrePrincipale.disableTab(6);
        }
        if(fenetrePrincipale.carriste->groupe.toInt() == 4) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(0);
            fenetrePrincipale.disableTab(2);
            fenetrePrincipale.disableTab(3);
            fenetrePrincipale.disableTab(4);
            fenetrePrincipale.disableTab(5);
            fenetrePrincipale.disableTab(6);
        }
        fenetrePrincipale.show();
    }
    else
    {
        return 0;
    }
    return a.exec();
}
