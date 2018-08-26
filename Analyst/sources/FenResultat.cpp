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

#include "../headers/FenResultat.h"

FenResultat::FenResultat(QString &resultat, QString &resultatAffiner, int afficher, QWidget *parent = 0) : QDialog (parent)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    resultatAffinerVrai = resultatAffiner;

    creerStatut();
    creerActions(resultatAffiner);
    creerFenetre(resultat, afficher);




}

void FenResultat::affiner()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenAffiner *fenetreAffiner = new FenAffiner(resultatAffinerVrai, this);
    fenetreAffiner->show();
}

void FenResultat::ouvrir()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenOuvertureFichier *fenetreOuvertureFichier = new FenOuvertureFichier(resultatAffinerVrai, this);
    fenetreOuvertureFichier->show();
}

void FenResultat::afficherTextes()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int termine = 0;
    int fichier = 0;
    int nombre = 0;

    QString nouveauAffichageTemporaire = "<u><center><h3>\nList of the Texts</u>\n\n</h3></center>";
    QString nouveauAffichage;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        fichier++;

        if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))))
        {
            nomFichier.remove(QDir::homePath() + "/Analyst/" + "DataBase/");
            nouveauAffichage += nomFichier + "<br />";
            nombre++;

        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }

    QString QNombreTout = "<h1><center>";
    QString QNombre;
    QNombre.setNum(nombre);

    QNombreTout += QNombre += " Results Found</h1></center>";

    QString nouveauAffichageTemporaire2 = QNombreTout + nouveauAffichageTemporaire + nouveauAffichage;

    fenetreResultat->setText(nouveauAffichageTemporaire2);
}

void FenResultat::afficherImages()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int termine = 0;
    int fichier = 0;
    int nombre = 0;

    QString nouveauAffichageTemporaire = "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    QString nouveauAffichage;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        fichier++;

        if((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive))))
        {
            nomFichier.remove(QDir::homePath() + "/Analyst/" + "DataBase/");
            nouveauAffichage += nomFichier + "<br />";
            nombre++;

        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }

    QString QNombreTout = "<h1><center>";
    QString QNombre;
    QNombre.setNum(nombre);

    QNombreTout += QNombre += " Results Found</h1></center>";

    QString nouveauAffichageTemporaire2 = QNombreTout + nouveauAffichageTemporaire + nouveauAffichage;

    fenetreResultat->setText(nouveauAffichageTemporaire2);
}

void FenResultat::afficherMusiques()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int termine = 0;
    int fichier = 0;
    int nombre = 0;

    QString nouveauAffichageTemporaire = "<u><center><h3>\nList of the Musics</u>\n\n</h3></center>";
    QString nouveauAffichage;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        fichier++;

        if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))))
        {
            nomFichier.remove(QDir::homePath() + "/Analyst/" + "DataBase/");
            nouveauAffichage += nomFichier + "<br />";
            nombre++;

        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }

    QString QNombreTout = "<h1><center>";
    QString QNombre;
    QNombre.setNum(nombre);

    QNombreTout += QNombre += " Results Found</h1></center>";

    QString nouveauAffichageTemporaire2 = QNombreTout + nouveauAffichageTemporaire + nouveauAffichage;

    fenetreResultat->setText(nouveauAffichageTemporaire2);
}

void FenResultat::afficherVideos()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int termine = 0;
    int fichier = 0;
    int nombre = 0;

    QString nouveauAffichageTemporaire = "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    QString nouveauAffichage;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        fichier++;

        if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))))
        {
            nomFichier.remove(QDir::homePath() + "/Analyst/" + "DataBase/");
            nouveauAffichage += nomFichier + "<br />";
            nombre++;

        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }

    QString QNombreTout = "<h1><center>";
    QString QNombre;
    QNombre.setNum(nombre);

    QNombreTout += QNombre += " Results Found</h1></center>";

    QString nouveauAffichageTemporaire2 = QNombreTout + nouveauAffichageTemporaire + nouveauAffichage;

    fenetreResultat->setText(nouveauAffichageTemporaire2);
}

void FenResultat::messageAffiner()
{
    barreEtat->showMessage(tr("Affiner la recherche"), 2000);
}

void FenResultat::messageOuvrirFichier()
{
    barreEtat->showMessage(tr("Ouvrir un fichier"), 2000);
}

void FenResultat::messageOuvrirTousTextes()
{
    barreEtat->showMessage(tr("Ouvrir tous les textes"), 2000);
}

void FenResultat::messageOuvrirToutesImages()
{
    barreEtat->showMessage(tr("Ouvrir toutes les images"), 2000);
}

void FenResultat::messageOuvrirToutesMusiques()
{
    barreEtat->showMessage(tr("Ouvrir toutes les musiques"), 2000);
}

void FenResultat::messageOuvrirToutesVideos()
{
    barreEtat->showMessage(tr("Ouvrir toutes les videos"), 2000);
}

void FenResultat::messageAfficherTousTextes()
{
    barreEtat->showMessage(tr("Afficher seulement les textes"), 2000);
}

void FenResultat::messageAfficherToutesImages()
{
    barreEtat->showMessage(tr("Afficher seulement les images"), 2000);
}

void FenResultat::messageAfficherToutesMusiques()
{
    barreEtat->showMessage(tr("Afficher seulement les musiques"), 2000);
}

void FenResultat::messageAfficherToutesVideos()
{
    barreEtat->showMessage(tr("Afficher seulement les videos"), 2000);
}

void FenResultat::fonctionOuvrirTousTextes()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    //nombreTextesOuverts = 0;

    int termine = 0;
    int fichier = 0;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        if((nomFichier.count("/") == 2))
        {
            nomFichier.remove(0,7);
        }

        if(!nomFichier.startsWith(QDir::homePath() + "/Analyst/" + "DataBase/"))
        {
            #if defined (linux)
                QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
            #endif

            nomFichier.insert(0, QDir::homePath() + "/Analyst/" + "DataBase/");
        }

        fichier++;

        if((nomFichier.contains(".txt")) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)))
        {
            QFile lancementFichier(nomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                FenFichierTexte *fenetreTexte = new FenFichierTexte(texte, nomFichier, this);
                fenetreTexte->show();
            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier ") + nomFichier + tr(" n'existe pas"));
            }
        }

        if((nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".docx", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)))
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/" + nomFichier));
        }

        if((nomFichier.compare(QDir::homePath() + "/Analyst/" + "DataBase/")) == 0)
        {
            termine = 1;
        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }
}

void FenResultat::fonctionOuvrirToutesImages()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    //nombreImagesOuverts = 0;

    int termine = 0;
    int fichier = 0;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        fichier++;

        if((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive))))
        {
            QFile lancementFichier(nomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                FenFichierImage *fenetreImage = new FenFichierImage(nomFichier, this);
                fenetreImage->show();
            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

        if((nomFichier.compare(QDir::homePath() + "/Analyst/" + "DataBase/")) == 0)
        {
            termine = 1;
        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }
}

void FenResultat::fonctionOuvrirToutesMusiques()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    //nombreMusiquesOuverts = 0;

    int termine = 0;
    int fichier = 0;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        if(!nomFichier.startsWith(QDir::homePath() + "/Analyst/" + "DataBase/"))
        {
            #if defined (linux)
                QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
            #endif

            nomFichier.insert(0, QDir::homePath() + "/Analyst/" + "DataBase/");
        }

        fichier++;

        if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))))
        {
            QFile lancementFichier(nomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                FenFichierMusique *fenetreMusique = new FenFichierMusique(nomFichier, this);
                fenetreMusique->show();
            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

        if((nomFichier.compare(QDir::homePath() + "/Analyst/" + "DataBase/")) == 0)
        {
            termine = 1;
        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }
}

void FenResultat::fonctionOuvrirToutesVideos()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    //nombreVideosOuverts = 0;

    int termine = 0;
    int fichier = 0;

    while(termine == 0)
    {
        QString nomFichier;
        nomFichier = resultatAffinerVrai.section('|', fichier, fichier);

        if(!nomFichier.startsWith(QDir::homePath() + "/Analyst/" + "DataBase/"))
        {
            #if defined (linux)
                QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
                QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
            #endif

            nomFichier.insert(0, QDir::homePath() + "/Analyst/" + "DataBase/");
        }

        fichier++;

        if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))))
        {
            QFile lancementFichier(nomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                FenFichierVideo *fenetreVideo = new FenFichierVideo(nomFichier, this);
                fenetreVideo->show();
            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

        if((nomFichier.compare(QDir::homePath() + "/Analyst/" + "DataBase/")) == 0)
        {
            termine = 1;
        }

        if(nomFichier.isNull())
        {
            termine = 1;
        }
    }
}

void FenResultat::ouvrir_toutes_videos()
{
    fonctionOuvrirToutesVideos();
}

void FenResultat::ouvrir_tous_textes()
{
    fonctionOuvrirTousTextes();
}

void FenResultat::ouvrir_toutes_images()
{
    fonctionOuvrirToutesImages();
}

void FenResultat::ouvrir_toutes_musiques()
{
    fonctionOuvrirToutesMusiques();
}

void FenResultat::creerActions(QString resultatAffiner)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    toolBar = new QToolBar();
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    outilsAffiner = new QAction(this);
    outilsAffiner->setIcon(QIcon(":/icones/Fenetre Resultats/viewmag+.png"));
    outilsAffiner->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    outilsAffiner->setToolTip(tr("Affiner  Ctrl+R"));
    connect(outilsAffiner, SIGNAL(hovered()), this, SLOT(messageAffiner()));
    connect(outilsAffiner, SIGNAL(triggered()), this, SLOT(affiner()));
    toolBar->addAction(outilsAffiner);

    ouvrirFichier = new QAction(this);
    ouvrirFichier->setData(resultatAffiner);
    ouvrirFichier->setIcon(QIcon(":/icones/Fenetre Resultats/folder_green.png"));
    ouvrirFichier->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ouvrirFichier->setToolTip(tr("Ouvrir...  Ctrl+O"));
    connect(ouvrirFichier, SIGNAL(hovered()), this, SLOT(messageOuvrirFichier()));
    connect(ouvrirFichier, SIGNAL(triggered()), this, SLOT(ouvrir()));
    toolBar->addAction(ouvrirFichier);

    toolBar->addSeparator();

    /*               OUVRIR UN SEUL TYPE DE FICHIER             */

    ouvrirTousTextes = new QAction(this);
    ouvrirTousTextes->setIcon(QIcon(":/icones/Fenetre Resultats/soffice.png"));
    ouvrirTousTextes->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    ouvrirTousTextes->setToolTip(tr("Ouvrir tous les textes  Ctrl+T"));
    connect(ouvrirTousTextes, SIGNAL(hovered()), this, SLOT(messageOuvrirTousTextes()));
    connect(ouvrirTousTextes, SIGNAL(triggered()), this, SLOT(ouvrir_tous_textes()));
    toolBar->addAction(ouvrirTousTextes);

    ouvrirToutesImages = new QAction(this);
    ouvrirToutesImages->setIcon(QIcon(":/icones/Fenetre Resultats/png-2.png"));
    ouvrirToutesImages->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    ouvrirToutesImages->setToolTip(tr("Ouvrir toutes les images  Ctrl+P"));
    connect(ouvrirToutesImages, SIGNAL(hovered()), this, SLOT(messageOuvrirToutesImages()));
    connect(ouvrirToutesImages, SIGNAL(triggered()), this, SLOT(ouvrir_toutes_images()));
    toolBar->addAction(ouvrirToutesImages);

    ouvrirToutesMusiques = new QAction(this);
    ouvrirToutesMusiques->setIcon(QIcon(":/icones/Fenetre Resultats/mp3-2.png"));
    ouvrirToutesMusiques->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    ouvrirToutesMusiques->setToolTip(tr("Ouvrir toutes les musiques  Ctrl+M"));
    connect(ouvrirToutesMusiques, SIGNAL(hovered()), this, SLOT(messageOuvrirToutesMusiques()));
    connect(ouvrirToutesMusiques, SIGNAL(triggered()), this, SLOT(ouvrir_toutes_musiques()));
    toolBar->addAction(ouvrirToutesMusiques);

    ouvrirToutesVideos = new QAction(this);
    ouvrirToutesVideos->setIcon(QIcon(":/icones/Fenetre Resultats/mov.png"));
    ouvrirToutesVideos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    ouvrirToutesVideos->setToolTip(tr("Ouvrir toutes les videos  Ctrl+V"));
    connect(ouvrirToutesVideos, SIGNAL(hovered()), this, SLOT(messageOuvrirToutesVideos()));
    connect(ouvrirToutesVideos, SIGNAL(triggered()), this, SLOT(ouvrir_toutes_videos()));
    toolBar->addAction(ouvrirToutesVideos);

    toolBar->addSeparator();

    /*                   AFFIHCHER QU'UN SEUL TYPE DE FICHIER                */

    outilsTexte = new QAction(this);
    outilsTexte->setIcon(QIcon(":/icones/Fenetre Resultats/folder_documents.png"));
    outilsTexte->setShortcut(QKeySequence(Qt::ALT + Qt::Key_T));
    outilsTexte->setToolTip(tr("Afficher seulement les textes  Alt+T"));
    connect(outilsTexte, SIGNAL(hovered()), this, SLOT(messageAfficherTousTextes()));
    connect(outilsTexte, SIGNAL(triggered()), this, SLOT(afficherTextes()));
    toolBar->addAction(outilsTexte);

    outilsImage = new QAction(this);
    outilsImage->setIcon(QIcon(":/icones/Fenetre Resultats/folder_images.png"));
    outilsImage->setShortcut(QKeySequence(Qt::ALT + Qt::Key_P));
    outilsImage->setToolTip(tr("Afficher seulement les images  ALT+P"));
    connect(outilsImage, SIGNAL(hovered()), this, SLOT(messageAfficherToutesImages()));
    connect(outilsImage, SIGNAL(triggered()), this, SLOT(afficherImages()));
    toolBar->addAction(outilsImage);

    outilsMusique = new QAction(this);
    outilsMusique->setIcon(QIcon(":/icones/Fenetre Resultats/folder_music.png"));
    outilsMusique->setShortcut(QKeySequence(Qt::ALT + Qt::Key_M));
    outilsMusique->setToolTip(tr("Afficher seulement les musiques  Alt+M"));
    connect(outilsMusique, SIGNAL(hovered()), this, SLOT(messageAfficherToutesMusiques()));
    connect(outilsMusique, SIGNAL(triggered()), this, SLOT(afficherMusiques()));
    toolBar->addAction(outilsMusique);

    outilsVideo = new QAction(this);
    outilsVideo->setIcon(QIcon(":/icones/Fenetre Resultats/folder_video.png"));
    outilsVideo->setShortcut(QKeySequence(Qt::ALT + Qt::Key_V));
    outilsVideo->setToolTip(tr("Afficher seulement les videos  Alt+V"));
    connect(outilsVideo, SIGNAL(hovered()), this, SLOT(messageAfficherToutesVideos()));
    connect(outilsVideo, SIGNAL(triggered()), this, SLOT(afficherVideos()));
    toolBar->addAction(outilsVideo);
}

void FenResultat::creerStatut()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    barreEtat = new QStatusBar();
    barreEtat->showMessage(tr("Prêt"));
}

void FenResultat::options(int afficher)
{

    if(afficher == 5)
    {
        // Nothing
    }

    else if(afficher == 1)
    {
         afficherTextes();
    }

    else if(afficher == 2)
    {
        afficherImages();
    }

    else if(afficher == 3)
    {
        afficherMusiques();
    }

    else if(afficher == 4)
    {
        afficherVideos();
    }
}

void FenResultat::creerFenetre(QString resultat, int afficher)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    fenetreResultat = new QTextEdit();
    fenetreResultat->setReadOnly(true);
    fenetreResultat->setHtml(resultat);
    fenetreResultat->setFont(QFont("Courier"));

    boutonAffiner = new QPushButton(tr("Affiner !"));
    boutonOuvrir = new QPushButton(tr("Ouvrir des Fichiers !"));

    layoutBouton = new QHBoxLayout;
    layoutBouton->addWidget(boutonAffiner);
    layoutBouton->addWidget(boutonOuvrir);

    layout = new QVBoxLayout;
    layout->addWidget(toolBar);
    layout->addWidget(fenetreResultat);
    layout->addWidget(barreEtat);

    options(afficher);

    setLayout(layout);

    #if defined(Q_WS_WIN)
        setFixedSize(600,500);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(600,500);
    #endif

    setWindowTitle(tr("Analyst - Résultat de la Recherche"));

    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(boutonAffiner, SIGNAL(clicked()), this, SLOT(affiner()));
    connect(boutonOuvrir, SIGNAL(clicked()), this, SLOT(ouvrir()));
}

void FenResultat::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        affiner();
    }
}

void FenResultat::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
