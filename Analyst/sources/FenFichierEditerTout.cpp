/*

Copyright © 2009-2010 Alexis Rosuel

Analyst is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Analyst is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Analyst.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "../headers/FenAffiner.h"

using namespace std;

FenFichierEditerTout::FenFichierEditerTout(QString nomFichier, QString texte, QString resteTexte, int position, bool partie, QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    position_fichier = position;
    contenu_fichier_entier = resteTexte;
    texte_base = texte;
    est_partie = partie;

    creerStatusBar();
    creerActions();
    creerFenetre(nomFichier, texte);
}

void FenFichierEditerTout::creerActions()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    nouveau = new QAction(this);
    nouveau->setIcon(QIcon(":/icones/Fenetre Editer Tout/readme.png"));
    nouveau->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    nouveau->setToolTip(tr("Nouveau  Ctrl+N"));
    connect(nouveau, SIGNAL(hovered()), this, SLOT(afficherNouveau()));
    connect(nouveau, SIGNAL(triggered()), this, SLOT(fonctionNouveau()));
    toolBar->addAction(nouveau);

    ouvrir = new QAction(this);
    ouvrir->setIcon(QIcon(":/icones/Fenetre Editer Tout/kfm.png"));
    ouvrir->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ouvrir->setToolTip(tr("Ouvrir...  Ctrl+O"));
    connect(ouvrir, SIGNAL(hovered()), this, SLOT(afficherOuvrir()));
    connect(ouvrir, SIGNAL(triggered()), this, SLOT(fonctionOuvrir()));
    toolBar->addAction(ouvrir);

    enregistrer = new QAction(this);
    enregistrer->setIcon(QIcon(":/icones/Fenetre Editer Tout/db_update.png"));
    enregistrer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    enregistrer->setToolTip(tr("Enregistrer  Ctrl+S"));
    connect(enregistrer, SIGNAL(hovered()), this, SLOT(afficherEnregistrer()));
    connect(enregistrer, SIGNAL(triggered()), this, SLOT(fonctionEnregistrer()));
    toolBar->addAction(enregistrer);

    enregistrerSous = new QAction(this);
    enregistrerSous->setIcon(QIcon(":/icones/Fenetre Editer Tout/save_all.png"));
    enregistrerSous->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    enregistrerSous->setToolTip(tr("Enregistrer sous...  Ctrl+P"));
    connect(enregistrerSous, SIGNAL(hovered()), this, SLOT(afficherEnregistrerSous()));
    connect(enregistrerSous, SIGNAL(triggered()), this, SLOT(fonctionEnregistrerSous()));
    toolBar->addAction(enregistrerSous);

    toolBar->addSeparator();

    annuler = new QAction(this);
    annuler->setIcon(QIcon(":/icones/Fenetre Editer Tout/agt_back.png"));
    annuler->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    annuler->setToolTip(tr("Annuler  Ctrl+U"));
    connect(annuler, SIGNAL(hovered()), this, SLOT(afficherAnnuler()));
    connect(annuler, SIGNAL(triggered()), this, SLOT(fonctionAnnuler()));
    annuler->setEnabled(false);
    toolBar->addAction(annuler);

    retablir = new QAction(this);
    retablir->setIcon(QIcon(":/icones/Fenetre Editer Tout/agt_forward.png"));
    retablir->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    retablir->setToolTip(tr("Refaire  Ctrl+R"));
    connect(retablir, SIGNAL(hovered()), this, SLOT(afficherRetablir()));
    connect(retablir, SIGNAL(triggered()), this, SLOT(fonctionRetablir()));
    retablir->setEnabled(false);
    toolBar->addAction(retablir);

    toolBar->addSeparator();

    modeOnglet = new QAction(this);
    modeOnglet->setIcon(QIcon(":/icones/Fenetre Editer Tout/tab.png"));
    modeOnglet->setShortcut(QKeySequence(Qt::ALT + Qt::Key_T));
    modeOnglet->setToolTip(tr("Switch to tabs mode  Alt+T"));
    connect(modeOnglet, SIGNAL(hovered()), this, SLOT(afficherModeOnglet()));
    connect(modeOnglet, SIGNAL(triggered()), this, SLOT(fonctionModeOnglet()));
    toolBar->addAction(modeOnglet);

    modeTab = new QAction(this);
    modeTab->setIcon(QIcon(":/icones/Fenetre Editer Tout/view_fit_height.png"));
    modeTab->setShortcut(QKeySequence(Qt::ALT + Qt::Key_W));
    modeTab->setToolTip(tr("Switch to multi window mode  Alt+W"));
    connect(modeTab, SIGNAL(hovered()), this, SLOT(afficherModeTab()));
    connect(modeTab, SIGNAL(triggered()), this, SLOT(fonctionModeTab()));
    modeTab->setEnabled(false);
    toolBar->addAction(modeTab);

    toolBar->addSeparator();

    vueTile = new QAction(this);
    vueTile->setIcon(QIcon(":/icones/Fenetre Editer Tout/view_left_right.png"));
    vueTile->setShortcut(QKeySequence(Qt::ALT + Qt::Key_V));
    vueTile->setToolTip(tr("Passer en vue normale  Alt+V"));
    connect(vueTile, SIGNAL(hovered()), this, SLOT(afficherVueTile()));
    connect(vueTile, SIGNAL(triggered()), this, SLOT(fonctionVueTile()));
    vueTile->setEnabled(false);
    toolBar->addAction(vueTile);

    vueCascade = new QAction(this);
    vueCascade->setIcon(QIcon(":/icones/Fenetre Editer Tout/view_tree.png"));
    vueCascade->setShortcut(QKeySequence(Qt::ALT + Qt::Key_S));
    vueCascade->setToolTip(tr("Passer en vue cascade  Alt+S"));
    connect(vueCascade, SIGNAL(hovered()), this, SLOT(afficherVueCascade()));
    connect(vueCascade, SIGNAL(triggered()), this, SLOT(fonctionVueCascade()));
    toolBar->addAction(vueCascade);

    toolBar->addSeparator();

    fermerToutesLesFenetres = new QAction(this);
    fermerToutesLesFenetres->setIcon(QIcon(":/icones/Fenetre Editer Tout/view_remove.png"));
    fermerToutesLesFenetres->setShortcut(QKeySequence(Qt::ALT + Qt::Key_D));
    fermerToutesLesFenetres->setToolTip(tr("Effacer toutes les fenetres  Alt+D"));
    connect(fermerToutesLesFenetres, SIGNAL(hovered()), this, SLOT(afficherFermerToutesLesFenetres()));
    connect(fermerToutesLesFenetres, SIGNAL(triggered()), this, SLOT(fonctionFermerToutesLesFenetres()));
    toolBar->addAction(fermerToutesLesFenetres);
}

void FenFichierEditerTout::creerStatusBar()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut = new QStatusBar();
    statut->showMessage(tr("Prêt"));
}

void FenFichierEditerTout::afficherNouveau()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Créer un nouveau fichier"), 2000);
}

void FenFichierEditerTout::afficherOuvrir()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Ouvrir un fichier"), 2000);
}

void FenFichierEditerTout::afficherEnregistrer()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Enregistrer"), 2000);
}

void FenFichierEditerTout::afficherEnregistrerSous()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Enregistrer sous..."), 2000);
}

void FenFichierEditerTout::afficherAnnuler()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Annuler"), 2000);
}

void FenFichierEditerTout::afficherRetablir()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Rétablir"), 2000);
}

void FenFichierEditerTout::afficherModeOnglet()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Passer en mode onglets"), 2000);
}

void FenFichierEditerTout::afficherModeTab()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Passer en mode Multi Fenetres"), 2000);
}

void FenFichierEditerTout::afficherVueTile()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher les fenetres en vue normale"), 2000);
}

void FenFichierEditerTout::afficherVueCascade()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher les fenetres en vue cascade"), 2000);
}

void FenFichierEditerTout::afficherFermerToutesLesFenetres()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Fermer toutes les fenetres"), 2000);
}

void FenFichierEditerTout::fonctionModeOnglet()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneCentrale->setViewMode(QMdiArea::TabbedView);
    modeOnglet->setEnabled(false);
    modeTab->setEnabled(true);
}

void FenFichierEditerTout::fonctionModeTab()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneCentrale->setViewMode(QMdiArea::SubWindowView);
    modeTab->setEnabled(false);
    modeOnglet->setEnabled(true);
}

void FenFichierEditerTout::fonctionNouveau()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte = new QTextEdit;
    zoneTexte->setFont(QFont("Courier"));
    //connect(zoneTexte, SIGNAL(selectionChanged()), this, SLOT(fonctionUpdateAffichage()));

    sousFenetre = zoneCentrale->addSubWindow(zoneTexte);
    sousFenetre->setAttribute(Qt::WA_DeleteOnClose);
    sousFenetre->setWindowTitle(tr("Nouveau Document"));
    sousFenetre->resize(500,450);
    sousFenetre->setWindowIcon(QIcon(":/icones/Fenetre Editer Tout/readme.png"));
    sousFenetre->show();
}

void FenFichierEditerTout::fonctionOuvrir()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir..."), QDir::homePath() + "/Analyst/" + "/DataBase");

    if(path.isNull())
    {
        return;
    }

    QString texte;
    QFile fichier(path);

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         texte = fichier.readAll();
         fichier.close();
    }

    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier !"));
    }

    zoneTexte = new QTextEdit;
    zoneTexte->setHtml(texte);
    zoneTexte->setFont(QFont("Courier"));

    sousFenetre = zoneCentrale->addSubWindow(zoneTexte);
    sousFenetre->setAttribute(Qt::WA_DeleteOnClose);

    QString nomFichier = path.section('/', -1);
    sousFenetre->setWindowTitle(nomFichier);
    sousFenetre->resize(500,450);
    sousFenetre->setWindowIcon(QIcon(":/icones/Fenetre Editer Tout/readme.png"));
    sousFenetre->show();
}

void FenFichierEditerTout::fonctionEnregistrer()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(position_fichier < 0)
    {
        position_fichier -= position_fichier;
    }

    if(zoneCentrale->currentSubWindow()->windowTitle().compare(tr("Nouveau Document"), Qt::CaseSensitive) != 0)
    {
        zoneTexte = zoneCentrale->currentSubWindow()->findChild<QTextEdit *>();

        if(zoneCentrale->currentSubWindow()->windowTitle().startsWith("*"))
        {
            QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + zoneCentrale->currentSubWindow()->windowTitle().remove(0,1));
            fichier.open(QIODevice::WriteOnly | QIODevice::Text);

            if(!est_partie)
            {
                QTextStream flux(&fichier);
                flux << zoneTexte->toPlainText();
            }

            else
            {
                QString texte_entier = contenu_fichier_entier;
                texte_entier.remove(position_fichier, texte_base.length());
                texte_entier.insert(position_fichier, zoneTexte->toPlainText());
                QTextStream flux(&fichier);
                flux << texte_entier;
            }

            fichier.close();
            fichier.deleteLater();
        }

        else
        {
            QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + zoneCentrale->currentSubWindow()->windowTitle());
            fichier.open(QIODevice::WriteOnly | QIODevice::Text);

            if(!est_partie)
            {
                QTextStream flux(&fichier);
                flux << zoneTexte->toPlainText();
            }

            else
            {
                QString texte_entier = contenu_fichier_entier;
                texte_entier.remove(position_fichier, texte_base.length());
                texte_entier.insert(position_fichier, zoneTexte->toPlainText());
                QTextStream flux(&fichier);
                flux << texte_entier;
            }

            fichier.close();
            fichier.deleteLater();
        }

        if(zoneCentrale->currentSubWindow()->windowTitle().startsWith("*"))
        {
            zoneCentrale->currentSubWindow()->setWindowTitle(zoneCentrale->currentSubWindow()->windowTitle().remove(0,1));
        }

        else
        {
            zoneCentrale->currentSubWindow()->setWindowTitle(zoneCentrale->currentSubWindow()->windowTitle());
        }
    }

    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous devez d'abord spécifier le nom du fichier en passant par \"Enregistrer Sous...\""));
    }
}

void FenFichierEditerTout::fonctionEnregistrerSous()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString path = QFileDialog::getSaveFileName(this, tr("Enregistrer sous..."), QDir::homePath() + "/Analyst/" + "/DataBase");

    if(path.isNull())
    {
        return;
    }

    zoneTexte = zoneCentrale->currentSubWindow()->findChild<QTextEdit *>();

    QFile fichier(path);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream flux(&fichier);
    flux << zoneTexte->toPlainText();

    fichier.close();

    QString nomDocument = path.section('/', -1);
    zoneCentrale->currentSubWindow()->setWindowTitle(nomDocument);

    fichier.deleteLater();
}

void FenFichierEditerTout::fonctionAnnuler()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte->undo();
}

void FenFichierEditerTout::fonctionRetablir()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte->redo();
}

void FenFichierEditerTout::fonctionVueTile()
{
    zoneCentrale->tileSubWindows();
    vueTile->setEnabled(false);
    vueCascade->setEnabled(true);
}

void FenFichierEditerTout::fonctionVueCascade()
{
    zoneCentrale->cascadeSubWindows();
    vueTile->setEnabled(true);
    vueCascade->setEnabled(false);
}

void FenFichierEditerTout::fonctionFermerToutesLesFenetres()
{
    int reponse = QMessageBox::warning(this, tr("Attention"), tr("Si vous possédez des données non enregistrées, elles seront perdues. Voulez vous continuer ? Un nouveau document vide sera alors créé."), QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        zoneCentrale->closeAllSubWindows();
        zoneTexte->deleteLater();
        sousFenetre->deleteLater();

        zoneTexte = new QTextEdit;
        zoneTexte->setFont(QFont("Courier"));
        //connect(zoneTexte, SIGNAL(selectionChanged()), this, SLOT(fonctionUpdateAffichage()));

        sousFenetre = new QMdiSubWindow(zoneCentrale);
        sousFenetre = zoneCentrale->addSubWindow(zoneTexte);
        sousFenetre->setAttribute(Qt::WA_DeleteOnClose);
        sousFenetre->setWindowTitle(tr("Nouveau Document"));
        sousFenetre->resize(500,450);
        sousFenetre->setWindowIcon(QIcon(":/icones/Fenetre Editer Tout/readme.png"));
        sousFenetre->show();
    }

    else if (reponse == QMessageBox::No)
    {
        return;
    }
}

void FenFichierEditerTout::fonctionUndo(bool available)
{
    if(available)
    {
        annuler->setEnabled(true);
    }

    else
    {
        annuler->setEnabled(false);
    }
}

void FenFichierEditerTout::fonctionRedo(bool available)
{
    if(available)
    {
        retablir->setEnabled(true);
    }

    else
    {
        retablir->setEnabled(false);
    }
}

void FenFichierEditerTout::fonctionUpdateAffichage()
{
    if(!zoneCentrale->currentSubWindow()->windowTitle().startsWith("*"))
    {
        zoneCentrale->currentSubWindow()->setWindowTitle(tr("*").append(zoneCentrale->currentSubWindow()->windowTitle()));
    }
}

void FenFichierEditerTout::creerFenetre(QString nomFichier, QString texte)
{
    #if defined (linux)
       QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
       QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
       QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneCentrale = new QMdiArea;

    zoneTexte = new QTextEdit;

    if(texte.contains("</"))
    {
        zoneTexte->setHtml(texte);
    }

    else
    {
        zoneTexte->setPlainText(texte);
    }

    zoneTexte->setFont(QFont("Courier"));
    connect(zoneTexte, SIGNAL(undoAvailable(bool)), this, SLOT(fonctionUndo(bool)));
    connect(zoneTexte, SIGNAL(redoAvailable(bool)), this, SLOT(fonctionRedo(bool)));
    connect(zoneTexte, SIGNAL(textChanged()), this, SLOT(fonctionUpdateAffichage()));

    sousFenetre = new QMdiSubWindow();
    sousFenetre = zoneCentrale->addSubWindow(zoneTexte);
    sousFenetre->setAttribute(Qt::WA_DeleteOnClose);
    sousFenetre->setWindowTitle(nomFichier.section('/', -1));
    sousFenetre->resize(500,450);
    sousFenetre->setWindowIcon(QIcon(":/icones/Fenetre Editer Tout/readme.png"));
    sousFenetre->show();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(toolBar);
    layout->addWidget(zoneCentrale);
    layout->addWidget(statut);

    setLayout(layout);

    #if defined(Q_WS_WIN)
        resize(900,800);
    #endif

    #if defined(Q_WS_X11)
        resize(900,800);
    #endif

    setWindowTitle(tr("Editeur de fichiers"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
}

void FenFichierEditerTout::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
