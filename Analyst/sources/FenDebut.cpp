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

#include "../headers/FenDebut.h"

using namespace std;

QString recherche(QString);
QString rechercheCasse(QString);
QString rechercheEntier(QString);
QString rechercheCasseEntier(QString);

QString resultatAffiner;

FenDebut::FenDebut()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();
}

void FenDebut::rechercher()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if (mot->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un mot à rechercher"));
        return;
    }

    QString motRecherche = mot->text();
    QString resultat;

    if(!casse->isChecked())
    {
        if(!entier->isChecked())
        {
            resultat = recherche(motRecherche);
        }

        if(entier->isChecked())
        {
            resultat = rechercheEntier(motRecherche);
        }
    }

    else
    {
        if(!entier->isChecked())
        {
            resultat = rechercheCasse(motRecherche);
        }

        if(entier->isChecked())
        {
            resultat = rechercheCasseEntier(motRecherche);
        }
    }

    FenResultat *fenetreResultat = new FenResultat(resultat, resultatAffiner, this);
    fenetreResultat->show();
}

QString recherche(QString motRecherche)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString resultat;

    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Musics</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir("DataBase/");

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = "DataBase/";
        donnees += nomFichier;

        QString texte;
        QFile fichier(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = fichier.readAll();
                fichier.close();

                if(texte.contains(motRecherche, Qt::CaseInsensitive))
                {
                    resultatTexte += nomFichier;
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffiner += donnees;
                    resultatAffiner += "|";
                }
            }
        }

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte == false)
    {
        resultat += resultatTexte;
    }

    if(image == true)
    {
        resultat += resultatImage;
    }

    if(musique == true)
    {
        resultat += resultatMusique;
    }

    if(video == true)
    {
        resultat += resultatVideo;
    }

    return resultat;
}

QString rechercheCasse(QString motRecherche)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int nombreResultat = 0;
    int texte = 0;
    int image = 0;
    int video = 0;
    int musique = 0;

    QString resultat;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir("DataBase/");

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = "DataBase/";
        donnees += nomFichier;

        QString texte;
        QFile fichier(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = fichier.readAll();
                fichier.close();

                if(texte.contains(motRecherche, Qt::CaseSensitive))
                {
                    resultatTexte += nomFichier;
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = 1;
                    resultatAffiner += donnees;
                    resultatAffiner += "|";
                }
            }
        }

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte == 0)
    {
        resultat += resultatTexte;
    }

    if(image == 1)
    {
        resultat += resultatImage;
    }

    if(musique == 1)
    {
        resultat += resultatMusique;
    }

    if(video == 1)
    {
        resultat += resultatVideo;
    }

    return resultat;
}

QString rechercheEntier(QString motRecherche)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int nombreResultat = 0;
    int texte = 0;
    int image = 0;
    int video = 0;
    int musique = 0;

    QString resultat;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir("DataBase/");

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = "DataBase/";
        donnees += nomFichier;

        QString texte;
        QFile fichier(donnees);

        QTextEdit *nomFichierEntierTexte = new QTextEdit;
        QTextEdit *nomFichierEntier = new QTextEdit;
        nomFichierEntier->setPlainText(donnees);



        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = fichier.readAll();
                fichier.close();

                nomFichierEntierTexte->setPlainText(texte);

                if(nomFichierEntierTexte->find(motRecherche, QTextDocument::FindWholeWords))
                {
                    resultatTexte += nomFichier;
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = 1;
                    resultatAffiner += donnees;
                    resultatAffiner += "|";
                }
            }
        }



        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte == 0)
    {
        resultat += resultatTexte;
    }

    if(image == 1)
    {
        resultat += resultatImage;
    }

    if(musique == 1)
    {
        resultat += resultatMusique;
    }

    if(video == 1)
    {
        resultat += resultatVideo;
    }

    return resultat;
}

QString rechercheCasseEntier(QString motRecherche)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int nombreResultat = 0;
    int texte = 0;
    int image = 0;
    int video = 0;
    int musique = 0;

    QString resultat;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir("DataBase/");

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = "DataBase/";
        donnees += nomFichier;

        QString texte;
        QFile fichier(donnees);

        QTextEdit *nomFichierEntierTexte = new QTextEdit;
        QTextEdit *nomFichierEntier = new QTextEdit;
        nomFichierEntier->setPlainText(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = fichier.readAll();
                fichier.close();

                nomFichierEntierTexte->setPlainText(texte);

                if((nomFichierEntierTexte->find(motRecherche, QTextDocument::FindWholeWords)) && (nomFichierEntierTexte->find(motRecherche, QTextDocument::FindCaseSensitively)))
                {
                    resultatTexte += nomFichier;
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = 1;
                    resultatAffiner += donnees;
                    resultatAffiner += "|";
                }
            }
        }

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = 1;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte == 0)
    {
        resultat += resultatTexte;
    }

    if(image == 1)
    {
        resultat += resultatImage;
    }

    if(musique == 1)
    {
        resultat += resultatMusique;
    }

    if(video == 1)
    {
        resultat += resultatVideo;
    }

    return resultat;
}


void FenDebut::rechercheInternet()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(!texteSeulement->isChecked() && !imagesSeulement->isChecked())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous devez cocher au moins une des deux cases"));
        return;
    }

    if(motInternet->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un mot à rechercher"));
        return;
    }

    numeroImage = 0;

    QString rechercheInternetVrai = motInternet->text();
    rechercheInternetVrai = rechercheInternetVrai.toLower();
    rechercheInternetVrai = rechercheInternetVrai.replace(0,1,rechercheInternetVrai.at(0).toUpper());

    int numeroDuCaractere = 0;

    while(numeroDuCaractere < rechercheInternetVrai.size())
    {
        numeroDuCaractere++;

        if(rechercheInternetVrai.at(numeroDuCaractere).isSpace())
        {
            rechercheInternetVrai = rechercheInternetVrai.replace(numeroDuCaractere,1,"_");
            numeroDuCaractere++;

            if(rechercheInternetVrai.at(numeroDuCaractere).isLower())
            {
                rechercheInternetVrai = rechercheInternetVrai.replace(numeroDuCaractere,1,rechercheInternetVrai.at(numeroDuCaractere).toUpper());
            }

            else if(rechercheInternetVrai.at(numeroDuCaractere).isSpace())
            {
                numeroDuCaractere--;
            }
        }
    }

    motInternet->setText(rechercheInternetVrai);
    motInternet->setReadOnly(true);

    QString nomSite;
    nomSite = "http://fr.wikipedia.org/wiki/" + rechercheInternetVrai;

    const QUrl url = QUrl(nomSite);
    const QNetworkRequest requete(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkReply *reponse = manager->get(requete);

    connect(reponse, SIGNAL(finished()), this, SLOT(telechargementTermine()));
}

void FenDebut::telechargementTermine()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #elif defined (WIN32)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    #endif

    QNetworkReply *reponse = qobject_cast<QNetworkReply*>(sender());
    QString contenuFichier;

    if(texteSeulement->isChecked())
    {
        QString nomFichier = motInternet->text() + "-internet.txt";
        QString nomFichierDonnees = "DataBase/" + nomFichier;

        contenuFichier = reponse->readAll();
        const char* contenuFichierChar= contenuFichier.toStdString().c_str();

        QFile fichier(nomFichierDonnees);
        fichier.open(QIODevice::WriteOnly);
        fichier.write(contenuFichierChar);
        fichier.close();
        reponse->deleteLater();

        FenFichierTexte *fenetreTexte = new FenFichierTexte(contenuFichier, nomFichier, this);
        fenetreTexte->show();
    }

    if(imagesSeulement->isChecked())
    {
        nomFichier = "";

        int i = 0;

        while(i < contenuFichier.size())
        {
            ++i;

            if(contenuFichier.at(i) == 'h')
            {
                ++i;
                if(contenuFichier.at(i) == 't')
                {
                    ++i;
                    if(contenuFichier.at(i) == 't')
                    {
                        ++i;
                        if(contenuFichier.at(i) == 'p')
                        {
                            ++i;
                            if(contenuFichier.at(i) == ':')
                            {
                                ++i;
                                if(contenuFichier.at(i) == '/')
                                {
                                    ++i;
                                    if(contenuFichier.at(i) == '/')
                                    {
                                        ++i;
                                        nomFichier = "http://";
                                        while(contenuFichier.at(i) != '"')
                                        {
                                            nomFichier += contenuFichier.at(i);
                                            ++i;
                                        }

                                        if(nomFichier.startsWith("http://upload.wikimedia.org/wikipedia") && nomFichier.endsWith(".jpg", Qt::CaseInsensitive))
                                        {
                                            vraiNomFichier = nomFichier;

                                            const QUrl url = QUrl(nomFichier);
                                            const QNetworkRequest requete(url);
                                            QNetworkAccessManager *managerImage = new QNetworkAccessManager;
                                            QNetworkReply *reponseImage = managerImage->get(requete);

                                            connect(reponseImage, SIGNAL(finished()), this, SLOT(telechargementImageTermine()));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    motInternet->setReadOnly(false);
}

void FenDebut::telechargementImageTermine()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QNetworkReply *reponseImage = qobject_cast<QNetworkReply*>(sender());

    QString nomImageFichier = vraiNomFichier.section("/",8,8);
    QString nomImageFichierDonnees = "DataBase/" + nomImageFichier;

    QFile fichier(nomImageFichierDonnees);

    if(fichier.exists())
    {
        numeroImage++;
        QString numeroString;
        numeroString.setNum(numeroImage);
        nomImageFichierDonnees.append(numeroImage);
    }

    fichier.close();
    QFile nouveauFichier(nomImageFichierDonnees);

    nouveauFichier.open(QIODevice::WriteOnly);
    nouveauFichier.write(reponseImage->readAll());
    nouveauFichier.close();
    reponseImage->deleteLater();

    FenFichierImage *fenetreImage = new FenFichierImage(nomImageFichierDonnees, this);
    fenetreImage->show();
}

void FenDebut::messageErreur(QNetworkReply::NetworkError)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>") + r->errorString() + "</em>");
    close();
}

void FenDebut::fonctionVisualiser()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    FenFichierVisualisation *fenetreVisualisation = new FenFichierVisualisation(this);
    fenetreVisualisation->show();
}

void FenDebut::afficherLicence()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenLicence *fenetreLicence = new FenLicence(this);
    fenetreLicence->show();
}

void FenDebut::creerFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QTabWidget *onglets = new QTabWidget(this);
    onglets->setGeometry(0,0,340,320);

    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget;
    QWidget *page3 = new QWidget;

    phrase = new QLabel(tr("Mot à rechercher :"));
    mot = new QLineEdit;
    lancer = new QPushButton();

    lancer->setIcon(QIcon(":/icones/Fenetre Principale/kghostview.png"));
    lancer->setIconSize(QSize(64,64));

    casse = new QCheckBox(tr("Respecter la Casse"));
    casse->setChecked(false);

    entier = new QCheckBox(tr("Rechercher le Mot en Entier"));
    entier->setChecked(true);

    QVBoxLayout *layoutCheck = new QVBoxLayout;
    layoutCheck->addWidget(casse);
    layoutCheck->addWidget(entier);

    QHBoxLayout *layoutChercher = new QHBoxLayout;
    layoutChercher->addLayout(layoutCheck);
    layoutChercher->addWidget(lancer);

    phraseInternet = new QLabel(tr("Mot à Rechercher sur Internet :"));
    motInternet = new QLineEdit;
    boutonInternet = new QPushButton();

    boutonInternet->setIcon(QIcon(":/icones/Fenetre Principale/web.png"));
    boutonInternet->setIconSize(QSize(64,64));

    texteSeulement = new QCheckBox(tr("Afficher le Texte"));
    imagesSeulement = new QCheckBox(tr("Afficher les Images              "));
    texteSeulement->setChecked(true);
    imagesSeulement->setChecked(true);

    QVBoxLayout *layoutMotInternet = new QVBoxLayout;
    layoutMotInternet->addWidget(phraseInternet);
    layoutMotInternet->addWidget(motInternet);

    QVBoxLayout *layoutOptionsInternet = new QVBoxLayout;
    layoutOptionsInternet->addWidget(texteSeulement);
    layoutOptionsInternet->addWidget(imagesSeulement);

    QHBoxLayout *layoutInternetBouton = new QHBoxLayout;
    layoutInternetBouton->addLayout(layoutOptionsInternet);
    layoutInternetBouton->addWidget(boutonInternet);

    QVBoxLayout *layoutInternet = new QVBoxLayout;
    layoutInternet->addLayout(layoutMotInternet);
    layoutInternet->addLayout(layoutInternetBouton);

    labelTrait = new QLabel("<hr />");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(phrase);
    layout->addWidget(mot);
    layout->addLayout(layoutChercher);
    layout->addWidget(labelTrait);
    layout->addLayout(layoutInternet);

    visualiser = new QPushButton();
    visualiser->setIcon(QIcon(":/icones/Fenetre Principale/folder_developer.png"));
    visualiser->setIconSize(QSize(64,64));

    phraseVisualiser = new QLabel(tr("Vous pouvez ici gerer votre base <br /> de donnée de maniere efficace et rapide<hr />"));
    phraseEntrer = new QLabel(tr("Acceder maintenant à la base de <br />donnée"));
    phraseInfo = new QLabel(tr("Le system de gestion des fichiers de Analyst<br />"
                        "vous permet de  : <br />"
						"Effectuer des operations sur les fichiers <br />"
						"Afficher seulement les textes, les images, les <br />musiques ou les videos <br />"
						"Afficher les informations de votre base de <br />donnée ou sur vos fichiers<hr /><br />"
                                ));

    QVBoxLayout *layoutGestion = new QVBoxLayout;
    layoutGestion->addWidget(phraseVisualiser);
    layoutGestion->addWidget(phraseInfo);
    layoutGestion->addWidget(labelTrait);

    QHBoxLayout *layoutTout = new QHBoxLayout;
    layoutTout->addWidget(phraseEntrer);
    layoutTout->addWidget(visualiser);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addLayout(layoutGestion);
    layout2->addLayout(layoutTout);

    phrasePresentation = new QLabel(tr("<center>"

					"<h1>Analyst 1.0</h1>"
					"<p>"
						"Programme de recherche dans une <br />"
						"base de donnée et Internet :<br />"
						"Inclu un visionneur du dossier avec <br />"
						"fonctionnalitées"
						" pratiques,<br />"
						"il permet de rechercher, trier, filtrer<br />"
						"enregistrer et lancer les fichiers,<br />"
						"Enfin, il est facile à prendre en main et efficace <br />"
					"</p>"
						"Copyright © 2009-2010 Alexis ROSUEL<br />"
				"</center>"));

    QPushButton *aProposDeQt = new QPushButton(tr("À Propos de Qt"));
    QPushButton *licence = new QPushButton(tr("Licence"));

    QHBoxLayout *layoutBoutonAPropos = new QHBoxLayout;
    layoutBoutonAPropos->addWidget(aProposDeQt);
    layoutBoutonAPropos->addWidget(licence);

    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addWidget(phrasePresentation);
    layout3->addWidget(labelTrait);
    layout3->addLayout(layoutBoutonAPropos);

    page1->setLayout(layout);
    page2->setLayout(layout2);
    page3->setLayout(layout3);

    onglets->addTab(page1, tr("Recherche"));
    onglets->addTab(page2, tr("Gestion du Dossier"));
    onglets->addTab(page3, tr("À Propos..."));

    onglets->setMovable(true);
    onglets->setDocumentMode(true);

    setWindowTitle("Analyst");
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
    setMaximumSize(340,320);
    setMinimumSize(340,320);

    connect(lancer, SIGNAL(clicked()), this, SLOT(rechercher()));
    connect(boutonInternet, SIGNAL(clicked()), this, SLOT(rechercheInternet()));

    connect(visualiser, SIGNAL(clicked()), this, SLOT(fonctionVisualiser()));

    connect(licence, SIGNAL(clicked()), this, SLOT(afficherLicence()));
    connect(aProposDeQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
}

void FenDebut::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
