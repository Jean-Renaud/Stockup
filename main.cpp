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
    QApplication a(argc, argv);
    BaseDeDonnees bdd;
    bdd.creerTableBdd();
    Connexion Login;
    MainWindow fenetrePrincipale;
    Login.setBaseDeDonnees(&bdd);
    fenetrePrincipale.setBaseDeDonnees(&bdd);


    /*Si le code et le mot de passe correspondent alors on ouvre la fenetre principale*/
    if (Login.exec() == QDialog::Accepted)
    {
        fenetrePrincipale.carriste = Login.carriste;

        qDebug() << fenetrePrincipale.carriste->getGroupe() << " " << Login.carriste->getGroupe();

        /*Attribution des droits d'accès aux onglets par rapport à l'appartenance au groupe*/
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 1) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.desactiverOnglet(0);
            fenetrePrincipale.desactiverOnglet(1);
            fenetrePrincipale.desactiverOnglet(4);
            fenetrePrincipale.desactiverOnglet(5);
            fenetrePrincipale.desactiverOnglet(6);
        }
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 2) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.desactiverOnglet(4);
            fenetrePrincipale.desactiverOnglet(5);


        }
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 3) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.desactiverOnglet(0);
            fenetrePrincipale.desactiverOnglet(2);
            //fenetrePrincipale.disableTab(3);
            //fenetrePrincipale.disableTab(4);
            fenetrePrincipale.desactiverOnglet(5);
            fenetrePrincipale.desactiverOnglet(6);
            fenetrePrincipale.desactiverOngletsGroupeCarriste();
        }
        if(fenetrePrincipale.carriste->getGroupe().toInt() == 4) {
            fenetrePrincipale.moveToTab(1);
            fenetrePrincipale.desactiverOnglet(0);
            fenetrePrincipale.desactiverOnglet(2);
            fenetrePrincipale.desactiverOnglet(3);
            fenetrePrincipale.desactiverOnglet(4);
            fenetrePrincipale.desactiverOnglet(5);
            fenetrePrincipale.desactiverOnglet(6);
        }
        fenetrePrincipale.show();
    }
    else
    {
        return 0;
    }
    return a.exec();
}
