#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basededonnees.h"
#include "utilisateur.h"
#include "produits.h"
#include "fournisseur.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QtSql/QtSql>
#include <QModelIndex>
#include <QWidget>
#include <QSqlRecord>
#include <QDateTime>
#include <QDate>
#include <QDateEdit>
#include <QIcon>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}
void MainWindow::setBaseDeDonnees(BaseDeDonnees *bdd) {
    this->bdd = bdd;
}

void MainWindow::on_actionVider_la_bas_de_donn_es_triggered()

{
    if(carriste->getGroupe().toInt() == 5)
    {
    int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer TOUTE la base de donnée, "
    "cette action est irreversible. Cliquez sur Ok pour confirmer ou sur No pour annuler.", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QSqlQuery purgerBdd;
        purgerBdd.exec("DELETE FROM matieres_Premieres");
        purgerBdd.exec("DELETE FROM fournisseurs");
        purgerBdd.exec("DELETE FROM sqlite_sequence WHERE name='matieres_Premieres'");
        purgerBdd.exec("DELETE FROM sqlite_sequence WHERE name='fournisseurs'");
        QMessageBox::information(this,tr("Succès"),tr("La purge de la base de donnée a bien été effectuée."));
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::critical(this, "Confirmation", "La base de donnée n'a pas été purgée.");
    }
}
}
void MainWindow::on_creerReferenceBtn_clicked()
{
    Produits *produit = new Produits      (
                                           ui->idProduit->text(),
                                           ui->referenceProduit->text(),
                                           ui->nomProduit_2->text(),
                                           ui->lotProdiuit->text(),
                                           ui->dateDeCreation->text(),
                                           ui->heureDeCreation->text(),
                                           ui->emplacementProduit->text(),
                                           ui->emballageProduit->currentText(),
                                           ui->quantiteProduit->text(),
                                           ui->etatProduit->currentText(),
                                           ui->dluoProduit->text(),
                                           ui->codeFournisseur->text());

    if(this->bdd->creerUneReference(*produit))
    {
        QMessageBox::information(this,"Création réussie","La création du produit a été enregistrée avec succès.");
    }
    else
    {
       QMessageBox::critical(this,"Création échouée", "Nope.");
    }
}

void MainWindow::on_search_Database_clicked()
{

    QString searchRef = ui->searchRef->text();

    bdd->chercherParReference(&this->modal, searchRef);

    ui->listDatabase->setModel(&this->modal);

}

void MainWindow::on_search_Location_clicked()
{
    QString rechercheEmplacement = ui->searchLocation->text();

    bdd->chercherProduitParEmplacement(&this->modal, rechercheEmplacement);

    ui->listDatabase->setModel(&this->modal);
}

void MainWindow::on_searchNameProduct_clicked()
{
     QString chercherProduitParnom = ui->searchByName->text();
     bdd->chercherProduitParNom(&this->modal, chercherProduitParnom);
     ui->listDatabase->setModel(&this->modal);
     //ui->listDatabase->verticalHeader()->setVisible(false);
}

void MainWindow::on_listDatabase_activated(const QModelIndex &index)
{

    QString valeur = ui->listDatabase->model()->data(index).toString();
    QSqlQuery cliqueSurListe;
    cliqueSurListe.prepare("SELECT id_Produit, Reference, Nom, Date ,Emplacement, Emballage, Quantite, Etat, DLUO, Lot, Code_fournisseur "
                           "FROM matieres_Premieres "
                           "WHERE id_Produit = :idProduit or "
                           "Reference = :reference or "
                           "Nom = :nom or "
                           "Date = :date or "
                           "Emplacement = :emplacement or "
                           "Emballage = :emballage or "
                           "Quantite = :quantite or "
                           "Etat = :etat or "
                           "DLUO = :dluo or "
                           "Lot = :lot or "
                           "Code_fournisseur = :codeFournisseur");
    cliqueSurListe.bindValue(":idProduit", valeur);
    cliqueSurListe.bindValue(":reference", valeur);
    cliqueSurListe.bindValue(":nom", valeur);
    cliqueSurListe.bindValue(":date", valeur);
    cliqueSurListe.bindValue(":emplacement", valeur);
    cliqueSurListe.bindValue(":emballage", valeur);
    cliqueSurListe.bindValue(":quantite", valeur);
    cliqueSurListe.bindValue(":etat", valeur);
    cliqueSurListe.bindValue(":dluo", valeur);
    cliqueSurListe.bindValue(":lot", valeur);
    cliqueSurListe.bindValue(":codeFournisseur", valeur);

    cliqueSurListe.exec();
    while(cliqueSurListe.next())
    {

        switch (carriste->getGroupe().toInt())
               {
                   case 3:
                       this->desactiverOngletsGroupeCarriste();
                   break;
                   case 4:
                   this->desactiverOngletsGroupeQualite();
                   break;
               }

        ui->idProduit->setText(cliqueSurListe.value(0).toString());
        ui->referenceProduitMaj->setText(cliqueSurListe.value(1).toString());
        ui->nomProduitMaj->setText(cliqueSurListe.value(2).toString());
        ui->dateProduitMaj->setText(cliqueSurListe.value(3).toString());
        ui->emplacementProduitMaj->setText(cliqueSurListe.value(4).toString());
        ui->emballageProduitMaj->setText(cliqueSurListe.value(5).toString());
        ui->quantitePoduitMaj->setText(cliqueSurListe.value(6).toString());
        ui->etatProduitMaj->setText(cliqueSurListe.value(7).toString());
        ui->dluoProduitMaj->setText(cliqueSurListe.value(8).toString());
        ui->lotProduitMaj->setText(cliqueSurListe.value(9).toString());
        ui->codeFmajProduit->setText(cliqueSurListe.value(10).toString());
    }
}

void MainWindow::on_update_row_clicked()
{
    Produits *mettreAjourProduit = new Produits(ui->idProduit->text(),
                                                ui->referenceProduitMaj->text(),
                                                ui->nomProduitMaj->text(),
                                                ui->lotProduitMaj->text(),
                                                ui->dateProduitMaj->text(),
                                                ui->heureDeCreation->text(),
                                                ui->emplacementProduitMaj->text(),
                                                ui->emballageProduitMaj->text(),
                                                ui->quantitePoduitMaj->text(),
                                                ui->etatProduitMaj->text(),
                                                ui->dluoProduitMaj->text(),
                                                ui->codeFmajProduit->text()

                                            );

    if(this->bdd->miseAjourReference(*mettreAjourProduit))
    {
        QMessageBox::information(this,"Modification réussie","La modification du produit a été enregistrée avec succès.");
    }
    else
    {
       QMessageBox::critical(this,"Modification échouée", "La mise à jour du produit n'a pas été effectuée.");
    }
}

void MainWindow::on_majFournisseur_clicked()
{
    Fournisseur *livreur2 = new Fournisseur(   ui->idfournisseur->text(),
                                               ui->cfournisseur->text(),
                                               ui->nomsociete->text(),
                                               ui->formejuridique->text(),
                                               ui->adresseedit->text(),
                                               ui->codepostal->text(),
                                               ui->villefournisseur->text(),
                                               ui->paysfournisseur->text(),
                                               ui->telephonefournisseur->text(),
                                               ui->siretfournisseur->text(),
                                               ui->apefournisseur->text()
                                               );

    if(this->bdd->miseAjourFournisseur(*livreur2))
    {
      QMessageBox::information(this,tr("Mise à jour réussie"),tr("La mise à jour du fournisseur a été enregistrée avec succès."));
    }
    else
    {
      QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour du fournisseur a échouée"));
    }


}



void MainWindow::on_majUtilisateur_clicked()
{
    Utilisateur *mettreAjourUtilisateur = new Utilisateur(ui->idUtilisateurEdit->text(),
                                               ui->codeUtilisateurEdit->text(),
                                               ui->nomUtilisateurEdit->text(),
                                               ui->prenomUtilisateurEdit->text(),
                                               ui->mdpUtilisateurEdit->text(),
                                               ui->groupeUtilisateurEdit->text()
                                               );


    if(this->bdd->miseAJourUtilisateur(*mettreAjourUtilisateur))
    {

      QMessageBox::information(this,tr("Mis à jour réussie"),tr("La mise à jour de l'utilisateur a été enregistrée avec succès."));


    }
    else
    {
       QMessageBox::critical(this,tr("Mise à jour échouée"),tr("La mise à jour de l'utilisateur a échouée"));


    }
}



void MainWindow::on_deleteProduct_clicked()
{

    Produits *supprimerProduit = new Produits(ui->idProduit->text(),
                                              ui->referenceProduitMaj->text(),
                                              ui->nomProduitMaj->text(),
                                              ui->lotProduitMaj->text(),
                                              ui->dateProduitMaj->text(),
                                              ui->heureDeCreation->text(),
                                              ui->emplacementProduitMaj->text(),
                                              ui->emballageProduitMaj->text(),
                                              ui->quantitePoduitMaj->text(),
                                              ui->etatProduitMaj->text(),
                                              ui->dluoProduitMaj->text(),
                                              ui->codeFmajProduit->text()
                                              );

        int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du"
                                                                   " stock, cette action est irreversible. Cliquez sur Ok pour confirmer"
                                                                   " ou sur No pour annuler.", QMessageBox::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            this->bdd->supprimerReference(*supprimerProduit);

            QMessageBox::information(this,tr("Succès"),tr("La suppression du produit a bien été effectuée."));
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::critical(this, "Confirmation", "Le produit n'a pas été supprimé.");
        }
}

void MainWindow::on_chercheUtilisateur_clicked()
{
    QSqlQueryModel * modal3 = new QSqlQueryModel();
    clearFocus();

    QSqlQuery chercherUnUtilisateur ;
    QString trouverUtilisateur = ui->chercheUtilisateurEdit->text();
    chercherUnUtilisateur.prepare("SELECT * FROM utilisateurs WHERE Nom = :nom");
    chercherUnUtilisateur.bindValue(":nom",trouverUtilisateur);
    chercherUnUtilisateur.exec();

    modal3->setQuery(chercherUnUtilisateur);
    ui->gestionUtilisateur->setModel(modal3);
}

void MainWindow::on_createUser_clicked()
{
    Utilisateur *employe = new Utilisateur(ui->idUtilisateurEdit->text(),
                                           ui->code->text(),
                                           ui->nomUtilisateur->text(),
                                           ui->prenom->text(),
                                           ui->mdp->text(),
                                           ui->groupe->text()
                                           );
   if(this->bdd->creerUnUtilisateur(*employe))
    {
       QMessageBox::information(this, "Création réussie", "La création de l'utilisateur a été enregistrée avec succès.");
    }
    else
    {
      QMessageBox::information(this,tr("Création échouée"),tr("La création de l'utilisateur a échouée"));
    }
}

void MainWindow::on_creerFournisseur_clicked()
{
    Fournisseur *livreur = new Fournisseur(   ui->idfournisseur->text(),
                                               ui->codeDuFournisseur->text(),
                                               ui->nomSociete->text(),
                                               ui->formeJuridique->text(),
                                               ui->adresse->text(),
                                               ui->codePostal->text(),
                                               ui->ville->text(),
                                               ui->pays->text(),
                                               ui->telephone->text(),
                                               ui->siret->text(),
                                               ui->ape->text()
                                               );
    if(livreur->getCodeFournisseur().isEmpty() || livreur->getNomSociete().isEmpty() || livreur->getFormeJuridique().isEmpty()
    || livreur->getAdresse().isEmpty() || livreur->getCodePostal().isEmpty() || livreur-> getVille().isEmpty() ||
    livreur->getPays().isEmpty() || livreur->getTelephone().isEmpty() || livreur->getSiret().isEmpty() || livreur->getApe().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous avez laissé un champ vide dans le formulaire de saisie.");
    }
   else if(this->bdd->creerUnFournisseur(*livreur))
   {
      QMessageBox::information(this, "Création réussie", "La création du fournisseur a été enregistrée avec succès.");
   }
   else
   {
      QMessageBox::information(this,tr("Création échouée"),tr("La création du fournisseur a échouée"));
   }
}

void MainWindow::on_gestionUtilisateur_activated(const QModelIndex &index)
{
    QString renvoyerDansChampTexte = ui->gestionUtilisateur->model()->data(index).toString();
    QSqlQuery cliqueSurListe;
    cliqueSurListe.prepare("SELECT id, Code, Nom, Prenom, Mot_de_Passe, Groupe FROM utilisateurs WHERE id = :id or "
                           "Code= :code or "
                           "Nom = :nom or "
                           "Prenom= :prenom or "
                           "Mot_de_Passe = :mdp or "
                           "Groupe= :groupe");
    cliqueSurListe.bindValue(":id", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":code", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":nom", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":prenom", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":mdp",renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":groupe", renvoyerDansChampTexte);
    cliqueSurListe.exec();

    while(cliqueSurListe.next())
    {
        qDebug() << "groupe " << carriste->getGroupe();
        ui->idUtilisateurEdit->setText(cliqueSurListe.value(0).toString());
        ui->codeUtilisateurEdit->setText(cliqueSurListe.value(1).toString());
        ui->nomUtilisateurEdit->setText(cliqueSurListe.value(2).toString());
        ui->prenomUtilisateurEdit->setText(cliqueSurListe.value(3).toString());
        ui->mdpUtilisateurEdit->setText(cliqueSurListe.value(4).toString());
        ui->groupeUtilisateurEdit->setText(cliqueSurListe.value(5).toString());
    }
}

void MainWindow::on_listProvider_activated(const QModelIndex &index)
{

    QString renvoyerDansChampTexte = ui->listProvider->model()->data(index).toString();
    QSqlQuery cliqueSurListe;
    cliqueSurListe.prepare("SELECT id, Code, Nom, Forme_juridique ,Adresse, Code_postal, Pays, Ville, Telephone, Siret, APE FROM fournisseurs"
                           "WHERE id = :id or"
                           "Code = :code or"
                           "Nom = :nom or"
                           "Forme_juridique = :formeJuridique or"
                           "Adresse = :adresse or"
                           "Code_postal= :codePostal or"
                           "Pays = :pays or"
                           "Ville = :ville or"
                           "Telephone = :telephone or"
                           "Siret = :siret or"
                           "APE = :ape");
    cliqueSurListe.bindValue(":id", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":code", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":nom", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":formeJuridique", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":adresse",renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":codePostal", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":ville", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":telephone", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":siret", renvoyerDansChampTexte);
    cliqueSurListe.bindValue(":ape", renvoyerDansChampTexte);

    cliqueSurListe.exec();
    while(cliqueSurListe.next())
    {
        ui->idfournisseur->setText(cliqueSurListe.value(0).toString());
        ui->cfournisseur->setText(cliqueSurListe.value(1).toString());
        ui->nomsociete->setText(cliqueSurListe.value(2).toString());
        ui->formejuridique->setText(cliqueSurListe.value(3).toString());
        ui->adresseedit->setText(cliqueSurListe.value(4).toString());
        ui->codepostal->setText(cliqueSurListe.value(5).toString());
        ui->villefournisseur->setText(cliqueSurListe.value(6).toString());
        ui->paysfournisseur->setText(cliqueSurListe.value(7).toString());
        ui->telephonefournisseur->setText(cliqueSurListe.value(8).toString());
        ui->siretfournisseur->setText(cliqueSurListe.value(9).toString());
        ui->apefournisseur->setText(cliqueSurListe.value(10).toString());
    }
}
void MainWindow::on_fournisseur_clicked()
 {
     QSqlQueryModel * modal2 = new QSqlQueryModel();
     clearFocus();
     QSqlQuery listeFournisseurParCode;
     QString chercherFournisseur = ui->trouverfournisseur->text();
     listeFournisseurParCode.prepare("SELECT * FROM fournisseurs WHERE Code = :code");
     listeFournisseurParCode.bindValue(":code",chercherFournisseur);
     listeFournisseurParCode.exec();
     modal2->setQuery(listeFournisseurParCode);
     ui->listProvider->setModel(modal2);

 }



void MainWindow::on_voirStock_clicked()
{
    QSqlQueryModel * triAlphaproduits = new QSqlQueryModel();
    clearFocus();
    QSqlQuery triAlphaProduits;
    triAlphaProduits.prepare("SELECT * FROM matieres_Premieres ORDER BY Nom");
    triAlphaProduits.exec();
    triAlphaproduits->setQuery(triAlphaProduits);
    ui->listDatabase->setModel(triAlphaproduits);
}



void MainWindow::on_suppFournisseur_clicked()
{
    int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock, "
                                                               "cette action est irreversible. Cliquez sur OUI pour confirmer ou sur NON"
                                                               " pour annuler.", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        Fournisseur *livreur3 = new Fournisseur(ui->idfournisseur->text(),
                                                ui->cfournisseur->text(),
                                                ui->nomsociete->text().toUpper(),
                                                ui->formejuridique->text(),
                                                ui->adresseedit->text(),
                                                ui->codepostal->text(),
                                                ui->villefournisseur->text(),
                                                ui->paysfournisseur->text(),
                                                ui->telephonefournisseur->text(),
                                                ui->siretfournisseur->text(),
                                                ui->apefournisseur->text()
                                                );

        this->bdd->supprimerUnFournisseur(*livreur3);

        QMessageBox::information(this,tr("Succès"),tr("La suppression du fournisseur a bien été effectuée."));
        //this->ui->fournisseur->clicked();
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::critical(this, "Confirmation", "Le fournisseur n'a pas été supprimé.");
    }
}



void MainWindow::on_suppUtilisateur_clicked()
{
    int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock,"
                                                               " cette action est irreversible. Cliquez sur OUI pour confirmer ou"
                                                               " sur NON pour annuler.", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        Utilisateur *supprimerUtilisateur = new Utilisateur(ui->idUtilisateurEdit->text(),
                                                            ui->code->text(),
                                                            ui->nomUtilisateur->text(),
                                                            ui->prenom->text(),
                                                            ui->mdp->text(),
                                                            ui->groupe->text()
                                                            );

        this->bdd->supprimerUnUtilisateur(*supprimerUtilisateur);
        QMessageBox::information(this,tr("Succès"),tr("La suppression du fournisseur a bien été effectuée."));
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::critical(this, "Confirmation", "Le fournisseur n'a pas été supprimé.");
    }
}



void MainWindow::on_triAlphaUtilisateur_clicked()
{
    QSqlQueryModel * triAlphautilisateur = new QSqlQueryModel();
    clearFocus();
    QSqlQuery triAlphaUtilisateur(this->bdd->stockup);
    triAlphaUtilisateur.prepare("SELECT * FROM utilisateurs ORDER BY Nom");
    triAlphaUtilisateur.exec();
    triAlphautilisateur->setQuery(triAlphaUtilisateur);
    this->ui->gestionUtilisateur->setModel(triAlphautilisateur);
}

void MainWindow::on_triAlphaFournisseur_clicked()
{
    QSqlQueryModel * triAlphafournisseur = new QSqlQueryModel();
    clearFocus();
    QSqlQuery triAlphaFournisseur(this->bdd->stockup);
    triAlphaFournisseur.prepare("SELECT * FROM fournisseurs ORDER BY Nom");
    triAlphaFournisseur.exec();
    triAlphafournisseur->setQuery(triAlphaFournisseur);
    this->ui->listProvider->setModel(triAlphafournisseur);
}

void MainWindow::disableTab(int index)
{
    ui->tabGestionStock->setTabEnabled(index, false);
}

void MainWindow::moveToTab(int index)
{
    ui->tabGestionStock->setCurrentIndex(index);
}

void MainWindow::desactiverOngletsGroupeCarriste() {
    ui->idProduit->setEnabled(false);
    ui->nomProduitMaj->setEnabled(false);
    ui->referenceProduitMaj->setEnabled(false);
    ui->nomProduitMaj->setEnabled(false);
    ui->dateProduitMaj->setEnabled(false);
    ui->emballageProduitMaj->setEnabled(false);
    ui->etatProduitMaj->setEnabled(false);
    ui->dluoProduitMaj->setEnabled(false);
    ui->lotProduitMaj->setEnabled(false);
    ui->codeFmajProduit->setEnabled(false);
    ui->deleteProduct->setEnabled(false);
}

void MainWindow::desactiverOngletsGroupeQualite()
{
    ui->idProduit->setEnabled(false);
    ui->nomProduitMaj->setEnabled(false);
    ui->referenceProduitMaj->setEnabled(false);
    ui->nomProduitMaj->setEnabled(false);
    ui->dateProduitMaj->setEnabled(false);
    ui->emplacementProduitMaj->setEnabled(false);
    ui->emballageProduitMaj->setEnabled(false);
    ui->quantitePoduitMaj->setEnabled(false);
    ui->dluoProduitMaj->setEnabled(false);
    ui->lotProduitMaj->setEnabled(false);
    ui->codeFmajProduit->setEnabled(false);
    ui->deleteProduct->setEnabled(false);
}



