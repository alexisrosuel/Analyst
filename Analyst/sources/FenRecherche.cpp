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

#include "../headers/FenRecherche.h"

FenRecherche::FenRecherche(QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();
}

void FenRecherche::rechercher()
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

    FenResultat *fenetreResultat = new FenResultat(resultat, resultatAffiner, 5, this);
    fenetreResultat->show();
}

QString FenRecherche::recherche(QString motRecherche)
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
    bool autre = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAutre = "";
    resultatAffiner = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Musics</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir(QString(QDir::homePath() + "/Analyst/" + "DataBase/").toStdString().c_str());

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = QDir::homePath() + "/Analyst/" + "DataBase/";
        donnees += nomFichier;

        QString fichier_texte;
        QFile fichier(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                fichier_texte = fichier.readAll();
                fichier.close();

                if(fichier_texte.contains(motRecherche, Qt::CaseInsensitive))
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

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if((donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatAutre += nomFichier;
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte == true)
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

    if(autre == true)
    {
        resultat += resultatAutre;
    }

    return resultat;
}

QString FenRecherche::rechercheCasse(QString motRecherche)
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
    bool autre = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir(QString(QDir::homePath() + "/Analyst/" + "DataBase/").toStdString().c_str());

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = QDir::homePath() + "/Analyst/" + "DataBase/";
        donnees += nomFichier;

        QString fichier_texte;
        QFile fichier(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                fichier_texte = fichier.readAll();
                fichier.close();

                if(fichier_texte.contains(motRecherche, Qt::CaseSensitive))
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

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if((donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatAutre += nomFichier;
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte)
    {
        resultat += resultatTexte;
    }

    if(image)
    {
        resultat += resultatImage;
    }

    if(musique)
    {
        resultat += resultatMusique;
    }

    if(video)
    {
        resultat += resultatVideo;
    }

    if(autre)
    {
        resultat += resultatAutre;
    }

    return resultat;
}

QString FenRecherche::rechercheEntier(QString motRecherche)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;
    bool autre = false;

    QString resultat;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir(QString(QDir::homePath() + "/Analyst/" + "DataBase/").toStdString().c_str());

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = QDir::homePath() + "/Analyst/" + "DataBase/";
        donnees += nomFichier;

        QString fichier_texte;
        QFile fichier(donnees);

        QTextEdit *nomFichierEntierTexte = new QTextEdit;
        QTextEdit *nomFichierEntier = new QTextEdit;
        nomFichierEntier->setPlainText(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                fichier_texte = fichier.readAll();
                fichier.close();

                nomFichierEntierTexte->setPlainText(fichier_texte);

                if(nomFichierEntierTexte->find(motRecherche, QTextDocument::FindWholeWords))
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

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            resultatAutre += nomFichier;
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte)
    {
        resultat += resultatTexte;
    }

    if(image)
    {
        resultat += resultatImage;
    }

    if(musique)
    {
        resultat += resultatMusique;
    }

    if(video)
    {
        resultat += resultatVideo;
    }

    if(autre)
    {
        resultat += resultatAutre;
    }

    return resultat;
}

QString FenRecherche::rechercheCasseEntier(QString motRecherche)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;
    bool autre = false;

    QString resultat;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir(QString(QDir::homePath() + "/Analyst/" + "DataBase/").toStdString().c_str());

    while ((fichierLu = readdir(rep)) != NULL)
    {
        QString nomFichier(fichierLu->d_name);
        QString donnees = QDir::homePath() + "/Analyst/" + "DataBase/";
        donnees += nomFichier;

        QString fichier_texte;
        QFile fichier(donnees);

        QTextEdit *nomFichierEntierTexte = new QTextEdit;
        QTextEdit *nomFichierEntier = new QTextEdit;
        nomFichierEntier->setPlainText(donnees);

        if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && !(donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                fichier_texte = fichier.readAll();
                fichier.close();

                nomFichierEntierTexte->setPlainText(fichier_texte);

                if((nomFichierEntierTexte->find(motRecherche, QTextDocument::FindWholeWords)) && (nomFichierEntierTexte->find(motRecherche, QTextDocument::FindCaseSensitively)))
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

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }

        else if((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            resultatAutre += nomFichier;
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner += donnees;
            resultatAffiner += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += "<center><h1>" + QnombreResultat;
    resultat += " Results Found</h1></center>";

    if(texte)
    {
        resultat += resultatTexte;
    }

    if(image)
    {
        resultat += resultatImage;
    }

    if(musique)
    {
        resultat += resultatMusique;
    }

    if(video)
    {
        resultat += resultatVideo;
    }

    if(autre)
    {
        resultat += resultatAutre;
    }

    return resultat;
}

void FenRecherche::creerFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    phrase = new QLabel(tr("Mot à rechercher :"));
    mot = new QLineEdit;

    lancer = new QPushButton();
    lancer->setIcon(QIcon(":/icones/Fenetre Recherche/kghostview.png"));
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

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(phrase);
    layout->addWidget(mot);
    layout->addLayout(layoutChercher);

    setLayout(layout);

    setWindowTitle(tr("Analyst - Recherche"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    #if defined(Q_WS_WIN)
        setFixedSize(340,170);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(340,170);
    #endif

    connect(lancer, SIGNAL(clicked()), this, SLOT(rechercher()));
}

void FenRecherche::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        rechercher();
    }
}

void FenRecherche::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
