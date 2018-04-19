#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "basededonnees.h"
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
#include <QSqlTableModel>
#include <QDateTime>
#include <QTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Curseurs à afficher sur les boutons
    ui->creerReferenceBtn->setCursor(Qt::PointingHandCursor);
    ui->chercherFournisseur->setCursor(Qt::PointingHandCursor);
    ui->creerFournisseur->setCursor(Qt::PointingHandCursor);
    ui->creerUtilisateur->setCursor(Qt::PointingHandCursor);
    ui->chercherParEmplacement->setCursor(Qt::PointingHandCursor);
    ui->chercherParNomProduit->setCursor(Qt::PointingHandCursor);
    ui->chercherParReference->setCursor(Qt::PointingHandCursor);
    ui->chercheUtilisateurEdit->setCursor(Qt::PointingHandCursor);
    ui->miseAjourProduit->setCursor(Qt::PointingHandCursor);
    ui->triAlphabetiqueStock->setCursor(Qt::PointingHandCursor);
    ui->triAlphabetiqueFournisseur->setCursor(Qt::PointingHandCursor);
    ui->triAlphabetiqueUtilisateur->setCursor(Qt::PointingHandCursor);
    ui->supprimerProduit->setCursor(Qt::PointingHandCursor);
    ui->suppFournisseur->setCursor(Qt::PointingHandCursor);
    ui->suppUtilisateur->setCursor(Qt::PointingHandCursor);
    ui->majFournisseur->setCursor(Qt::PointingHandCursor);
    ui->majUtilisateur->setCursor(Qt::PointingHandCursor);
    ui->miseAjourProduit->setCursor(Qt::PointingHandCursor);
    ui->exportbdd->setCursor(Qt::PointingHandCursor);
    ui->chercherFournisseur->setCursor(Qt::PointingHandCursor);
    ui->nomProduit_2->text().toUpper();
}
MainWindow::~MainWindow()
{
    delete ui;
}

/*Permet de fermer le programme*/
void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::setBaseDeDonnees(BaseDeDonnees *bdd)
{
    this->bdd = bdd;
}

/*Permet de supprimer tous les produits ainsi que tous les comptes fournisseurs*/
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
            QMessageBox::warning(this, "Annulation", "La base de donnée n'a pas été purgée.");
        }
    }
}

/*Création d'un nouveau produit*/
void MainWindow::on_creerReferenceBtn_clicked()
{
    Produits *produit = new Produits      (
                ui->idProduit->text(),
                ui->referenceProduit->text(),
                ui->nomProduit_2->text().toUpper(),
                ui->lotProdiuit->text().toUpper(),
                ui->dateDeCreation->text(),
                ui->heureDeCreation->text(),
                ui->emplacementProduit->text().toUpper(),
                ui->emballageProduit->text(),
                ui->quantiteProduit->text(),
                ui->etatProduit->currentText(),
                ui->dluoProduit->text(),
                ui->codeFour->currentText()
                );

    if(produit->getRef().isEmpty() ||
            produit->getNom().isEmpty() ||
            produit->getLot().isEmpty() || produit->getDate().isEmpty() ||
            produit->getHeure().isEmpty() ||
            produit->getEmplacement().isEmpty() ||
            produit->getEmballage().isEmpty() ||
            produit->getQuantite().isEmpty() ||
            produit->getEtat().isEmpty() ||
            produit->getDluo().isEmpty() ||
            produit->getCodeFournisseur().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous avez laissé un champ vide dans le formulaire de saisie.");
    }
    else{
        //On vérifie qu'il n'y a pas d'enregistrement à cet emplacement.
        QString emplacement;
        emplacement = produit->getEmplacement();
        QSqlQuery verifierEmplacement(this->bdd->stockup);
        verifierEmplacement.prepare("SELECT COUNT(Emplacement) FROM matieres_Premieres WHERE Emplacement = :emplacement");
        verifierEmplacement.bindValue(":emplacement", emplacement);
        if(verifierEmplacement.exec())
        {
            verifierEmplacement.next();

            int compteur = verifierEmplacement.value(0).toInt();

            //Si aucun enregistrement est présent on execute l'enregistrement.
            if(compteur < 1)
            {
                this->bdd->creerUneReference(*produit);
                QMessageBox::information(this,"Création réussie","La création du produit a été enregistrée avec succès.");
            }

            //Veut dire qu'il y a un enregistrement à l'emplacement, on affiche une erreur.
            else if(compteur > 0)
            {
                QMessageBox::critical(this,"Création échouée", "La création du produit a échouée car une référence est déjà enregistrée à cet emplacement.");
            }
        }
        else
        {
            QMessageBox::critical(this,"Création échouée", "La création du produit a échouée car un problème a été rencontré dans la base de données."
                                                           "Si le problème persiste, merci de contacter le développeur à harkos67@gmail.com");
        }
    }
}

/*Permet d'effectuer la recherche d'un produit dans la base de donnée par sa référence*/
void MainWindow::on_chercherParReference_clicked()
{

    QString searchRef = ui->searchRef->text().toUpper();
    if(searchRef.isEmpty()){
        QMessageBox::critical(this, "Erreur", "Vous devez saisir une référence.");
    }
    else{
        bdd->chercherParReference(&this->modal, searchRef);
        ui->listDatabase->setModel(&this->modal);
        ui->listDatabase->verticalHeader()->setVisible(false);
        ui->searchByName->clear();
        ui->searchLocation->clear();
    }
}

/*Permet d'effectuer la recherche d'un produit dans la base de donnée par son emplacement*/
void MainWindow::on_chercherParEmplacement_clicked()
{
    QString rechercheEmplacement = ui->searchLocation->text().toUpper();
    if(rechercheEmplacement.isEmpty()){
        QMessageBox::critical(this, "Erreur", "Vous devez saisir un emplacement.");
    }
    else{
        bdd->chercherProduitParEmplacement(&this->modal, rechercheEmplacement);
        ui->listDatabase->setModel(&this->modal);
        ui->listDatabase->verticalHeader()->setVisible(false);
        ui->searchRef->clear();
        ui->searchByName->clear();
    }
}

/*Permet d'effectuer la recherche d'un produit dans la base de donnée par son nom*/
void MainWindow::on_chercherParNomProduit_clicked()
{
    QString chercherProduitParnom = ui->searchByName->text().toUpper();
    if(chercherProduitParnom.isEmpty()){
        QMessageBox::critical(this, "Erreur", "Vous devez saisir un nom.");
    }
    else{
        bdd->chercherProduitParNom(&this->modal, chercherProduitParnom);
        ui->listDatabase->setModel(&this->modal);
        ui->listDatabase->verticalHeader()->setVisible(false);
        ui->searchRef->clear();
        ui->searchLocation->clear();
    }
}

/*Permet de rechercher un utilisateur dans la base de donnée avec son nom*/
void MainWindow::on_chercheUtilisateur_clicked()
{
    QSqlQueryModel * modal3 = new QSqlQueryModel();
    clearFocus();

    QSqlQuery chercherUnUtilisateur ;
    QString trouverUtilisateur = ui->chercheUtilisateurEdit->text().toUpper();
    chercherUnUtilisateur.prepare("SELECT * FROM utilisateurs WHERE Nom = :nom");
    chercherUnUtilisateur.bindValue(":nom",trouverUtilisateur);
    if(!chercherUnUtilisateur.exec()){

        QMessageBox::critical(this, "Erreur", "Un problème a été rencontré en base de données.");

    }
    else if(trouverUtilisateur.isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous devez saisir un nom d'utilisateur.");
    }
    else{
        modal3->setQuery(chercherUnUtilisateur);
        ui->gestionUtilisateur->setModel(modal3);
        ui->listDatabase->verticalHeader()->setVisible(false);
    }
}

/*Permet d'envoyer les nouvelles informations du produit grâce à une mise à jour*/
void MainWindow::on_miseAjourProduit_clicked()
{
    Produits *mettreAjourProduit = new Produits(ui->idProduit->text(),
                                                ui->referenceProduitMaj->text(),
                                                ui->nomProduitMaj->text().toUpper(),
                                                ui->lotProduitMaj->text(),
                                                ui->dateProduitMaj->text(),
                                                ui->heureDeCreation->text(),
                                                ui->emplacementProduitMaj->text(),
                                                ui->emballageProduitMaj->text(),
                                                ui->quantitePoduitMaj->text(),
                                                ui->etatProduitMaj->currentText(),
                                                ui->dluoProduitMaj->text(),
                                                ui->codeFmajProduit->text()

                                                );
    if(mettreAjourProduit->getRef().isEmpty() ||
            mettreAjourProduit->getLot().isEmpty() ||
            mettreAjourProduit->getDate().isEmpty() ||
            mettreAjourProduit->getEmplacement().isEmpty() ||
            mettreAjourProduit->getEmballage().isEmpty() ||
            mettreAjourProduit->getQuantite().isEmpty() ||
            mettreAjourProduit->getEtat().isEmpty() ||
            mettreAjourProduit->getDluo().isEmpty() ||
            mettreAjourProduit->getCodeFournisseur().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous avez laissé un champ vide dans le formulaire de saisie.");
    }
    else if(this->bdd->miseAjourReference(*mettreAjourProduit))
    {
        QMessageBox::information(this,"Modification réussie","La modification du produit a été enregistrée avec succès.");

        QSqlQueryModel * rafraichir = new QSqlQueryModel();
        ui->listDatabase->verticalHeader()->setVisible(false);
        clearFocus();
        QSqlQuery rafraichirListe(this->bdd->stockup);
        QString idProduit = ui->idProduit->text();
        rafraichirListe.prepare("SELECT id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite,"
                                " SUM(Emballage * Quantite) AS 'Quantite Totale', Etat, DLUO, Code_fournisseur FROM matieres_Premieres WHERE id_Produit = :ref");
        rafraichirListe.bindValue(":ref", idProduit);
        rafraichirListe.exec();
        rafraichir->setQuery(rafraichirListe);
        this->ui->listDatabase->setModel(rafraichir);

        ui->idProduit->clear();
        ui->referenceProduitMaj->clear();
        ui->nomProduitMaj->clear();
        ui->lotProduitMaj->clear();
        ui->dateProduitMaj->clear();
        ui->heureDeCreation->clear();
        ui->emplacementProduitMaj->clear();
        ui->emballageProduitMaj->clear();
        ui->quantitePoduitMaj->clear();
        ui->dluoProduitMaj->clear();
        ui->codeFmajProduit->clear();
    }
    else
    {
        QMessageBox::critical(this,"Modification échouée", "La mise à jour du produit n'a pas été effectuée.");
    }

}

/*Permet de faire la mise à jour d'un produit*/
void MainWindow::on_majFournisseur_clicked()
{
    Fournisseur *mettreAjourFournisseur = new Fournisseur(   ui->idfournisseur->text(),
                                                             ui->cfournisseur->text(),
                                                             ui->nomsociete->text().toUpper(),
                                                             ui->formejuridique->text().toUpper(),
                                                             ui->adresseedit->text().toUpper(),
                                                             ui->codepostal->text(),
                                                             ui->villefournisseur->text().toUpper(),
                                                             ui->paysfournisseur->text().toUpper(),
                                                             ui->telephonefournisseur->text(),
                                                             ui->siretfournisseur->text().toUpper(),
                                                             ui->apefournisseur->text().toUpper()
                                                             );
    if(mettreAjourFournisseur->getIdFournisseur().isEmpty() ||
            mettreAjourFournisseur->getCodeFournisseur().isEmpty() ||
            mettreAjourFournisseur->getNomSociete().isEmpty() ||
            mettreAjourFournisseur->getFormeJuridique().isEmpty() ||
            mettreAjourFournisseur->getAdresse().isEmpty() ||
            mettreAjourFournisseur->getCodePostal().isEmpty() ||
            mettreAjourFournisseur->getVille().isEmpty() ||
            mettreAjourFournisseur->getPays().isEmpty() ||
            mettreAjourFournisseur->getTelephone().isEmpty() ||
            mettreAjourFournisseur->getSiret().isEmpty() ||
            mettreAjourFournisseur->getApe().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Un champ texte est resté vide, vous devez obligatoirement remplir tous les champs.");

    }

    else if(this->bdd->miseAjourFournisseur(*mettreAjourFournisseur))
    {
        QMessageBox::information(this,tr("Mise à jour réussie"),tr("La mise à jour du fournisseur a été enregistrée avec succès."));
        QSqlQueryModel * rafraichirListeMajFournisseur = new QSqlQueryModel();
        ui->listProvider->verticalHeader()->setVisible(false);
        clearFocus();
        QSqlQuery rafraichirListe(this->bdd->stockup);
        QString idUtilisateur = ui->idfournisseur->text();
        rafraichirListe.prepare("SELECT * FROM Fournisseurs WHERE id = :idFournisseur");
        rafraichirListe.bindValue(":idFournisseur", idUtilisateur);
        rafraichirListe.exec();
        rafraichirListeMajFournisseur->setQuery(rafraichirListe);
        this->ui->listProvider->setModel(rafraichirListeMajFournisseur);
    }

    else if(!this->bdd->miseAjourFournisseur(*mettreAjourFournisseur))
    {
        QMessageBox::critical(this, "Erreur", "Un problème a été rencontré dans la base de données.");
    }
    ui->idfournisseur->clear();
    ui->cfournisseur->clear();
    ui->nomsociete->clear();
    ui->formejuridique->clear();
    ui->adresseedit->clear();
    ui->codepostal->clear();
    ui->villefournisseur->clear();
    ui->paysfournisseur->clear();
    ui->telephonefournisseur->clear();
    ui->siretfournisseur->clear();
    ui->apefournisseur->clear();
}

/*Permet de faire la mise à jour d'un utilisateur*/
void MainWindow::on_majUtilisateur_clicked()
{
    Utilisateur *mettreAjourUtilisateur = new Utilisateur(ui->idUtilisateurEdit->text(),
                                                          ui->codeUtilisateurEdit->text(),
                                                          ui->nomUtilisateurEdit->text(),
                                                          ui->prenomUtilisateurEdit->text(),
                                                          ui->mdpUtilisateurEdit->text(),
                                                          ui->groupeUtilisateurEdit->text()
                                                          );

    if(mettreAjourUtilisateur->getCode().isEmpty() ||
            mettreAjourUtilisateur->getNom().isEmpty() ||
            mettreAjourUtilisateur->getPrenom().isEmpty() ||
            mettreAjourUtilisateur->getMdp().isEmpty() ||
            mettreAjourUtilisateur->getGroupe().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Un champ texte est resté vide, vous devez obligatoirement remplir tous les champs.");
    }
    else if(this->bdd->miseAJourUtilisateur(*mettreAjourUtilisateur))
    {
        QMessageBox::information(this, "Modification réussie", "Le profil de l'utilisateur a été mis à jour avec succès.");
        QSqlQueryModel * rafraichirListeMajUtilisateur = new QSqlQueryModel();
        ui->gestionUtilisateur->verticalHeader()->setVisible(false);
        clearFocus();
        QSqlQuery rafraichirListe(this->bdd->stockup);
        QString idUtilisateur = ui->idUtilisateurEdit->text();
        rafraichirListe.prepare("SELECT * FROM Utilisateurs WHERE id = :idUtilisateur");
        rafraichirListe.bindValue(":idUtilisateur", idUtilisateur);
        rafraichirListe.exec();
        rafraichirListeMajUtilisateur->setQuery(rafraichirListe);
        this->ui->gestionUtilisateur->setModel(rafraichirListeMajUtilisateur);
    }
    else
    {
        QMessageBox::information(this,tr("Modification échouée"),tr("La modification de l'utilisateur a échouée"));
    }

    //On réinitialise les champs de saisis.
    ui->idUtilisateurEdit->clear();
    ui->codeUtilisateurEdit->clear();
    ui->nomUtilisateurEdit->clear();
    ui->prenomUtilisateurEdit->clear();
    ui->mdpUtilisateurEdit->clear();
    ui->groupeUtilisateurEdit->clear();
}

/*Permet de supprimer un produit*/
void MainWindow::on_supprimerProduit_clicked()
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
                                              ui->etatProduitMaj->currentText(),
                                              ui->dluoProduitMaj->text(),
                                              ui->codeFmajProduit->text()
                                              );
    if(ui->idProduit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Erreur"),tr("Vous devez selectionner un produit à supprimer."));

    }
    else{
        int reponse = QMessageBox::warning(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du"
                                                                  " stock, cette action est irreversible. Cliquez sur Ok pour confirmer"
                                                                  " ou sur No pour annuler.", QMessageBox::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            this->bdd->supprimerReference(*supprimerProduit);

            QMessageBox::information(this,tr("Succès"),tr("La suppression du produit a bien été effectuée."));
            QSqlQueryModel * rafraichirListeStock = new QSqlQueryModel();
            QSqlQuery rafraichirListe(this->bdd->stockup);
            QString reference = ui->referenceProduitMaj->text();
            rafraichirListe.prepare("SELECT * FROM matieres_Premieres WHERE Reference = :reference");
            rafraichirListe.exec("DELETE FROM sqlite_sequence WHERE name='matieres_Premieres'");
            rafraichirListe.bindValue(":reference", reference);
            rafraichirListe.exec();
            rafraichirListeStock->setQuery(rafraichirListe);
            this->ui->listDatabase->setModel(rafraichirListeStock);
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::critical(this, "Confirmation", "Le produit n'a pas été supprimé.");
        }
        else{
            QMessageBox::critical(this, "Erreur", "La création du fournisseur a échouée car un problème a été rencontré dans la base de données."
                                                  "Si le problème persiste, merci de contacter le développeur à harkos67@gmail.com");
        }
    }
}

/*Permet de créer un utilisateur*/
void MainWindow::on_creerUtilisateur_clicked()
{
    Utilisateur *employe = new Utilisateur(ui->idUtilisateurEdit->text(),
                                           ui->code->text(),
                                           ui->nomUtilisateur->text().toUpper(),
                                           ui->prenom->text().toUpper(),
                                           ui->mdp->text(),
                                           ui->groupe->text()
                                           );
    if(employe->getCode().isEmpty() ||
            employe->getNom().isEmpty() ||
            employe->getPrenom().isEmpty() ||
            employe->getMdp().isEmpty() ||
            employe->getGroupe().isEmpty())
    {

        QMessageBox::critical(this, "Erreur", "Un champ texte est resté vide, vous devez obligatoirement remplir tous les champs.");

    }
    else{
        //On vérifie qu'il n'y a pas d'enregistrement à cet emplacement.
        QString codeUtilisateur;
        codeUtilisateur = employe->getCode();
        QSqlQuery verifierCodeUtilisateur(this->bdd->stockup);
        verifierCodeUtilisateur.prepare("SELECT COUNT(Code) FROM Utilisateurs WHERE Code = :codeUtilisateur");
        verifierCodeUtilisateur.bindValue(":codeUtilisateur", codeUtilisateur);
        if(verifierCodeUtilisateur.exec())
        {
            verifierCodeUtilisateur.next();

            int compteur = verifierCodeUtilisateur.value(0).toInt();
            //Si aucun enregistrement est présent dans la base de données on execute l'enregistrement.
            if(compteur < 1)
            {
                this->bdd->creerUnUtilisateur(*employe);
                QMessageBox::information(this,"Création réussie","La création de l'utilisateur a été enregistrée avec succès.");
                //On réinitialise les champs de saisis.
                ui->idUtilisateurEdit->clear();
                ui->code->clear();
                ui->nomUtilisateur->clear();
                ui->prenom->clear();
                ui->mdp->clear();
                ui->groupe->clear();
            }
            //Veut dire qu'il y a un enregistrement avec ce code, on affiche une erreur.
            else if(compteur > 0)
            {
                QMessageBox::critical(this,"Création échouée", "La création de l'utilisateur a échouée car le code est déjà utilisé.");
            }
        }
        else
        {
            QMessageBox::critical(this,"Création échouée", "La création de l'utilisateur a échouée car un problème a été rencontré dans la base de données."
                                                           "Si le problème persiste, merci de contacter le développeur à harkos67@gmail.com");
        }
    }
}

/*Permet de créer un nouveau fournisseur*/
void MainWindow::on_creerFournisseur_clicked()
{
    Fournisseur *creerFournisseur = new Fournisseur(   ui->idfournisseur->text(),
                                                       ui->codeDuFournisseur->text(),
                                                       ui->nomSociete->text().toUpper(),
                                                       ui->formeJuridique->text().toUpper(),
                                                       ui->adresse->text().toUpper(),
                                                       ui->codePostal->text(),
                                                       ui->ville->text().toUpper(),
                                                       ui->pays->text().toUpper(),
                                                       ui->telephone->text(),
                                                       ui->siret->text().toUpper(),
                                                       ui->ape->text().toUpper()
                                                       );
    if(creerFournisseur->getCodeFournisseur().isEmpty() ||
            creerFournisseur->getNomSociete().isEmpty() ||
            creerFournisseur->getFormeJuridique().isEmpty() ||
            creerFournisseur->getAdresse().isEmpty() ||
            creerFournisseur->getCodePostal().isEmpty() ||
            creerFournisseur-> getVille().isEmpty() ||
            creerFournisseur->getPays().isEmpty() ||
            creerFournisseur->getTelephone().isEmpty() ||
            creerFournisseur->getSiret().isEmpty() ||
            creerFournisseur->getApe().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Vous avez laissé un champ vide dans le formulaire de saisie.");
    }
    else{
        //On vérifie qu'il n'y a pas d'enregistrement à cet emplacement.
        QString codeFournisseur;
        codeFournisseur = creerFournisseur->getCodeFournisseur();
        QSqlQuery verifierCodeFournisseur(this->bdd->stockup);
        verifierCodeFournisseur.prepare("SELECT COUNT(Code) FROM fournisseurs WHERE Code = :codeFournisseur");
        verifierCodeFournisseur.bindValue(":codeFournisseur", codeFournisseur);
        if(verifierCodeFournisseur.exec())
        {
            verifierCodeFournisseur.next();

            int compteur = verifierCodeFournisseur.value(0).toInt();
            //Si aucun enregistrement est présent dans la base de données on execute l'enregistrement.
            if(compteur < 1)
            {
                this->bdd->creerUnFournisseur(*creerFournisseur);
                QMessageBox::information(this,"Création réussie","La création du fournisseur a été enregistrée avec succès.");
                //On réinitialise les champs de saisis.
                ui->idfournisseur->clear();
                ui->codeDuFournisseur->clear();
                ui->nomSociete->clear();
                ui->formeJuridique->clear();
                ui->adresse->clear();
                ui->codePostal->clear();
                ui->ville->clear();
                ui->pays->clear();
                ui->telephone->clear();
                ui->siret->clear();
                ui->ape->clear();
            }
            //Veut dire qu'il y a un enregistrement avec ce code, on affiche une erreur.
            else if(compteur > 0)
            {
                QMessageBox::critical(this,"Création échouée", "La création du fournisseur a échouée car le code est déjà utilisé.");
            }
        }
        else
        {
            QMessageBox::critical(this,"Création échouée", "La création du fournisseur a échouée car un problème a été rencontré dans la base de données."
                                                           "Si le problème persiste, merci de contacter le développeur à harkos67@gmail.com");
        }
    }
}

/*Permet de double-cliquer sur une ligne dans le tableau concernant les produits pour envoyer les
 *informations dans les champs texte en vue d'une mise à jour ou d'une suppression*/
void MainWindow::on_listDatabase_activated(const QModelIndex &index)
{
    QString valeur = ui->listDatabase->model()->data(index).toString();
    ui->listDatabase->verticalHeader()->setVisible(false);
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

    if (!cliqueSurListe.exec()){

        QMessageBox::critical(this, "Erreur", "Un problème a été rencontré dans la base de données.");
    }
    else{
        while(cliqueSurListe.next())
        {
            switch (carriste->getCode().toInt())
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
            ui->etatProduitMaj->setCurrentText(cliqueSurListe.value(7).toString());
            ui->dluoProduitMaj->setText(cliqueSurListe.value(8).toString());
            ui->lotProduitMaj->setText(cliqueSurListe.value(9).toString());
            ui->codeFmajProduit->setText(cliqueSurListe.value(10).toString());
        }

    }
}

/*Permet de double-cliquer sur une ligne dans le tableau concernant les utilisateurs pour envoyer les informations dans les champs
 *texte en vue d'une mise à jour ou d'une suppression*/
void MainWindow::on_gestionUtilisateur_activated(const QModelIndex &index)
{
    QString renvoyerDansChampTexte = ui->gestionUtilisateur->model()->data(index).toString();
    ui->listDatabase->verticalHeader()->setVisible(false);
    QSqlQuery cliqueSurListe;
    cliqueSurListe.prepare("SELECT id, Code, Nom, Prenom, Mot_de_Passe, Groupe FROM utilisateurs WHERE id = :id or "
                           "Code = :code or "
                           "Nom = :nom or "
                           "Prenom = :prenom or "
                           "Mot_de_Passe = :mdp or "
                           "Groupe = :groupe");
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

/*Permet de double-cliquer sur une ligne dans le tableau concernant les fournisseurs pour envoyer les informations dans les champs texte
en vue d'une mise à jour ou d'une suppression*/
void MainWindow::on_listProvider_activated(const QModelIndex &index)
{
    QString majFournisseur = ui->listProvider->model()->data(index).toString();
    ui->listDatabase->verticalHeader()->setVisible(false);
    QSqlQuery cliqueSurListe;
    cliqueSurListe.prepare("SELECT id, Code, Nom, Forme_juridique ,Adresse, "
                           "Code_postal, Ville, Pays, Telephone, Siret, APE FROM fournisseurs "
                           "WHERE id = :id or Code = :code or Nom = :nom or Forme_juridique = :formeJuridique "
                           "or Adresse = :adresse or Code_postal = :codePostal or Pays = :pays or Ville = :ville or "
                           "Telephone = :telephone or Siret = :siret or APE = :ape");
    cliqueSurListe.bindValue(":id", majFournisseur);
    cliqueSurListe.bindValue(":code", majFournisseur);
    cliqueSurListe.bindValue(":nom", majFournisseur);
    cliqueSurListe.bindValue(":formeJuridique", majFournisseur);
    cliqueSurListe.bindValue(":adresse",majFournisseur);
    cliqueSurListe.bindValue(":codePostal", majFournisseur);
    cliqueSurListe.bindValue(":ville", majFournisseur);
    cliqueSurListe.bindValue(":telephone", majFournisseur);
    cliqueSurListe.bindValue(":siret", majFournisseur);
    cliqueSurListe.bindValue(":ape", majFournisseur);

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

/*Permet d'effectuer la recherche d'un fournisseur avec son code*/
void MainWindow::on_chercherFournisseur_clicked()
{
    QSqlQueryModel * modal2 = new QSqlQueryModel();
    clearFocus();
    QSqlQuery listeFournisseurParCode;
    QString chercherFournisseur = ui->trouverfournisseur->text();
    listeFournisseurParCode.prepare("SELECT * FROM fournisseurs WHERE Nom = :nom");
    listeFournisseurParCode.bindValue(":nom",chercherFournisseur);
    if(!listeFournisseurParCode.exec()){
        QMessageBox::critical(this, "Erreur", "Un problème a été rencontré dans la base de données.");
    }
    else{
        modal2->setQuery(listeFournisseurParCode);
        ui->listProvider->setModel(modal2);
        ui->listDatabase->verticalHeader()->setVisible(false);
    }
}

/*Permet de supprimer un fournisseur lorsqu'on clique sur le bouton Supprimer*/
void MainWindow::on_suppFournisseur_clicked()
{


    Fournisseur *supprimerUnFournisseur = new Fournisseur(ui->idfournisseur->text(),
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
    if(ui->idfournisseur->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Erreur"),tr("Vous devez selectionner un produit à supprimer."));

    }
    else{
        int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un produit du stock, "
                                                                   "cette action est irreversible. Cliquez sur OUI pour confirmer ou sur NON"
                                                                   " pour annuler.", QMessageBox::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {

            this->bdd->supprimerUnFournisseur(*supprimerUnFournisseur);

            QMessageBox::information(this,tr("Succès"),tr("La suppression du fournisseur a bien été effectuée."));
            QSqlQueryModel * actualiser = new QSqlQueryModel();
            QSqlQuery actualiserListe;
            actualiserListe.exec("SELECT * FROM fournisseurs");
            actualiserListe.exec("DELETE FROM sqlite_sequence WHERE name='matieres_Premieres'");

            actualiser->setQuery(actualiserListe);
            ui->listProvider->setModel(actualiser);

        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::critical(this, "Confirmation", "Le fournisseur n'a pas été supprimé.");
        }
    }
}

/*Permet de supprimer un utilisateur lorsqu'on clique sur le bouton Supprimer*/
void MainWindow::on_suppUtilisateur_clicked()
{
    {
        Utilisateur *supprimerUtilisateur = new Utilisateur(ui->idUtilisateurEdit->text(),
                                                            ui->code->text(),
                                                            ui->nomUtilisateur->text(),
                                                            ui->prenom->text(),
                                                            ui->mdp->text(),
                                                            ui->groupe->text()
                                                            );
        if(ui->idUtilisateurEdit->text().isEmpty())
        {
            QMessageBox::critical(this, "Information", "Vous devez selectionner un utilisateur à supprimer.");

        }
        else{
            int reponse = QMessageBox::question(this, "Avertissement", "ATTENTION! Vous êtes sur le point de supprimer un profil utilisateur,"
                                                                       " cette action est irreversible. Cliquez sur OUI pour confirmer ou"
                                                                       " sur NON pour annuler.", QMessageBox::Yes | QMessageBox::No);

            if (reponse == QMessageBox::Yes)
            {
                this->bdd->supprimerUnUtilisateur(*supprimerUtilisateur);
                QSqlQueryModel * actualiserListe = new QSqlQueryModel();
                QSqlQuery actualiser(this->bdd->stockup);
                actualiser.exec("SELECT * FROM utilisateurs");
                actualiserListe->setQuery(actualiser);
                this->ui->gestionUtilisateur->setModel(actualiserListe);
                QMessageBox::information(this, "Information", "L'utilisateur a correctement été supprimé.");
                actualiser.exec("DELETE FROM sqlite_sequence WHERE name='utilisateurs'");
            }
            else if (reponse == QMessageBox::No)
            {
                QMessageBox::warning(this, "Information", "L'utilisateur n'a pas été supprimé.");
            }
        }
    }
}

/*Permet d'afficher les utilisateurs par ordre alphabétique lorsqu'on clique sur le bouton Tri alphabétique*/
void MainWindow::on_triAlphabetiqueUtilisateur_clicked()
{
    QSqlQueryModel * triAlphautilisateur = new QSqlQueryModel();
    clearFocus();
    QSqlQuery triAlphaUtilisateur;
    triAlphaUtilisateur.exec("SELECT * FROM utilisateurs ORDER BY Nom ASC");
    triAlphautilisateur->setQuery(triAlphaUtilisateur);
    this->ui->gestionUtilisateur->setModel(triAlphautilisateur);
    ui->gestionUtilisateur->verticalHeader()->setVisible(false);
}

/*Permet d'afficher les fournisseurs par ordre alphabétique lorsqu'on clique sur le bouton Tri alphabétique*/
void MainWindow::on_triAlphabetiqueFournisseur_clicked()
{
    QSqlQueryModel * triAlphafournisseur = new QSqlQueryModel();
    ui->listProvider->verticalHeader()->setVisible(false);
    clearFocus();
    QSqlQuery triAlphaFournisseur(this->bdd->stockup);
    triAlphaFournisseur.prepare("SELECT * FROM fournisseurs ORDER BY Nom");
    triAlphaFournisseur.exec();
    triAlphafournisseur->setQuery(triAlphaFournisseur);
    this->ui->listProvider->setModel(triAlphafournisseur);
}

/*Permet d'afficher le stock par ordre alphabétique lorsqu'on clique sur le bouton Tri alphabétique*/
void MainWindow::on_triAlphabetiqueStock_clicked()
{
    QSqlQueryModel * triAlphaproduits = new QSqlQueryModel();
    clearFocus();
    QSqlQuery triAlphaProduits;
    triAlphaProduits.exec("SELECT id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, "
                          "Emballage * Quantite AS 'Quantite Totale', Etat, DLUO, Code_fournisseur FROM matieres_Premieres ORDER BY Nom ASC");

    triAlphaproduits->setQuery(triAlphaProduits);
    ui->listDatabase->setModel(triAlphaproduits);
    ui->listDatabase->verticalHeader()->setVisible(false);
}

/*Permet de trier le stock par date*/
void MainWindow::on_triParDate_clicked()
{
    QSqlQueryModel * triParDate = new QSqlQueryModel();
    ui->listDatabase->verticalHeader()->setVisible(false);
    clearFocus();
    QSqlQuery triDate(this->bdd->stockup);
    triDate.exec("SELECT id_Produit, Reference, Nom, Lot, Date, Heure, Emplacement, Emballage, Quantite, Quantite*Emballage AS 'Quantité totale',"
                 "Etat, DLUO, Code_fournisseur FROM matieres_Premieres ORDER BY Date DESC");
    triParDate->setQuery(triDate);
    this->ui->listDatabase->setModel(triParDate);
}

/*Permet de griser les onglets de navigation*/
void MainWindow::desactiverOnglet(int index)
{
    ui->tabGestionStock->setTabEnabled(index, false);
}

void MainWindow::moveToTab(int index)
{
    ui->tabGestionStock->setCurrentIndex(index);
}

/*Permission d'accès au groupe carriste pour effectuer des modifications sur les produits*/
void MainWindow::desactiverOngletsGroupeCarriste()
{
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
    ui->supprimerProduit->hide();
    ui->exportbdd->hide();

}

/*Permission d'accès au groupe Labo qualité pour effectuer des modifications sur les produits*/
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
    ui->supprimerProduit->hide();
    ui->exportbdd->hide();
}

/*Permet d'exporter la liste du stock au format csv*/
void MainWindow::on_exportbdd_clicked()
{
    //On remplis le model pour pouvoir télécharger un contenu.
    QSqlQueryModel * exportStock = new QSqlQueryModel();
    clearFocus();
    QSqlQuery exporterCSV;
    exporterCSV.prepare("SELECT * FROM matieres_Premieres");
    exporterCSV.exec();
    exportStock->setQuery(exporterCSV);
    this->ui->listDatabase->setModel(exportStock);
    ui->listDatabase->verticalHeader()->setVisible(false);

    //Permet de récupèrer le contenu de la table et de générer le fichier .csv
    QString donnees = "id_Produit;Reference;Nom;Lot;Date;Heure;Emplacement;Emballage;Quantite;Etat;DLUO;Code_fournisseur;\n";
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer", QString(), "*.csv");
    QFile file(fichier);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream Flux(&file);

        for (int i = 0; i < ui->listDatabase->model()->rowCount(); i++)
        {
            for(int j = 0; j < ui->listDatabase->model()->columnCount(); j++)
            {
                donnees += ui->listDatabase->model()->index(i, j).data().toString();
                donnees += ";";
            }
            donnees += "\n";
        }

        QMessageBox::information(this, "", donnees);
        Flux << donnees;

        file.close();
    }
}

/*Récupère la date du système*/
QString MainWindow::dateCreation()
{
    QString date = QDateTime::currentDateTime().toString("dd/MM/yyyy");
    return date;
}

/*Récupère l'heure système*/
QString MainWindow::heure()
{
    QString heure = QTime::currentTime().toString("hh:mm");
    return heure;
}

/*Méthode qui permet de renvoyer l'heure et la date du système dans le formulaire de création de matière première lorsqu'on clique
 * sur l'onglet Créer une matière et les rend non-modifiables.*/
void MainWindow::on_tabGestionStock_tabBarClicked()
{
    ui->dateDeCreation->setText(dateCreation());
    ui->dateDeCreation->setEnabled(false);
    ui->heureDeCreation->setText(heure());
    ui->heureDeCreation->setEnabled(false);
}

/*Permet de charger la liste des fournisseur dans une combobox*/
void MainWindow::on_chargerFournisseurs_clicked()
{
    QSqlQueryModel * codeBdd = new QSqlQueryModel();
    QSqlQuery * fournisseur = new QSqlQuery(this->bdd->stockup);
    fournisseur->prepare("SELECT Nom FROM fournisseurs");
    if(!fournisseur->exec()){
        QMessageBox::critical(this, "Erreur", "Un problème a été rencontré dans la base de données.");
    }
    else{
        codeBdd->setQuery(*fournisseur);
        ui->codeFour->setModel(codeBdd);
    }
}


