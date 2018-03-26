#include "mainwindow.h"
#include <QApplication>
#include <connexion.h>
#include "basededonnees.h"
#include "utilisateur.h"
#include <iostream>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    BaseDeDonnees bdd;
    QApplication a(argc, argv);
    Connexion Login;
    MainWindow fenetrePrincipale;
    Login.setBaseDeDonnees(&bdd);
    fenetrePrincipale.setBaseDeDonnees(&bdd);

    if (Login.exec() == QDialog::Accepted)
    {
        fenetrePrincipale.carriste = Login.carriste;
        //fenetrePrincipale.carriste->setGroupe(Login.carriste->getGroupe());

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
