#include "mainwindow.h"
#include <QApplication>
#include <connexion.h>
#include "database.h"
#include "utilisateur.h"
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
<<<<<<< HEAD
        //fenetrePrincipale.carriste->setGroupe(Login.carriste->getGroupe());
=======
>>>>>>> 45c1f705aa4f85ad1a2a11a5cbe8e37146d9d7c7

        qDebug() << fenetrePrincipale.carriste->getGroupe() << " " << Login.carriste->getGroupe();

        if(fenetrePrincipale.carriste->getGroupe().toInt() == 1) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(0);
            fenetrePrincipale.disableTab(1);
            fenetrePrincipale.disableTab(4);
            fenetrePrincipale.disableTab(5);
            fenetrePrincipale.disableTab(6);
        }
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 2) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(2);
            fenetrePrincipale.disableTab(3);


        }
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 3) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.disableTab(0);
            fenetrePrincipale.disableTab(2);
            fenetrePrincipale.disableTab(3);
            fenetrePrincipale.disableTab(4);
            fenetrePrincipale.disableTab(5);
            fenetrePrincipale.disableTab(6);
        }
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 4) {
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
