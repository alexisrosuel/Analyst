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

FenAffiner::FenAffiner(QString listeFichiers, QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();

    listeFichiersVrai = listeFichiers;
}

void FenAffiner::affiner()
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

    if(entier->isChecked())
    {
        if(!casse->isChecked())
        {
            recherche_entier();
        }

        else
        {
            recherche_entier_casse();
        }
    }

    else
    {
        if(!casse->isChecked())
        {
            recherche();
        }

        else
        {
            recherche_casse();
        }
    }
}

void FenAffiner::recherche_casse()
{
    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;
    bool autre = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultat2 = "";
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner2 = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    int fichier = 0;
    bool termine = false;

    while(!termine)
    {
        QString nomFichier;
        nomFichier = listeFichiersVrai.section('|', fichier, fichier);
        fichier++;

        if(nomFichier.isNull())
        {
            termine = true;
        }

        QString contenueTexte;
        QFile fichier(nomFichier);

        if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(mot->text(), Qt::CaseSensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                contenueTexte = fichier.readAll();
                fichier.close();

                if(contenueTexte.contains(mot->text(), Qt::CaseSensitive))
                {
                    //nomFichier = nomFichier.section('/', 1, 100000);
                    resultatTexte += nomFichier.section('/', 1, 100000);
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";
                }
            }
        }

        else if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && (nomFichier.contains(mot->text(), Qt::CaseSensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatTexte += nomFichier.section('/', 1, 100000);
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichier.contains(mot->text(), Qt::CaseSensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatImage += nomFichier.section('/', 1, 100000);
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && (nomFichier.contains(mot->text(), Qt::CaseSensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatVideo += nomFichier.section('/', 1, 100000);
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && (nomFichier.contains(mot->text(), Qt::CaseSensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatMusique += nomFichier.section('/', 1, 100000);
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(nomFichier.contains(mot->text(), Qt::CaseSensitive))
        {
            resultatAutre += nomFichier.section('/', 1, 100000);
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat2 += "<center><h1>" + QnombreResultat;
    resultat2 += " Results Found</h1></center>";

    if(texte)
    {
        resultat2 += resultatTexte;
    }

    if(image)
    {
        resultat2 += resultatImage;
    }

    if(musique)
    {
        resultat2 += resultatMusique;
    }

    if(video)
    {
        resultat2 += resultatVideo;
    }

    if(autre)
    {
        resultat2 += resultatAutre;
    }

    FenResultat *fenetreResultat = new FenResultat(resultat2, resultatAffiner2, 5, this);
    fenetreResultat->show();
}

void FenAffiner::recherche()
{
    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;
    bool autre = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultat2 = "";
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner2 = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    int fichier = 0;
    bool termine = false;

    while(!termine)
    {
        QString nomFichier;

        nomFichier = listeFichiersVrai.section('|', fichier, fichier);
        fichier++;

        if(nomFichier.isNull())
        {
            termine = true;
        }

        QString contenueTexte;
        QFile fichier(nomFichier);

        if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                contenueTexte = fichier.readAll();
                fichier.close();

                if(contenueTexte.contains(mot->text(), Qt::CaseInsensitive))
                {
                    //nomFichier = nomFichier.section('/', 1, 100000);
                    resultatTexte += nomFichier.section('/', 1, 100000);
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";
                }
            }
        }

        else if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && (nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatTexte += nomFichier.section('/', 1, 100000);
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatImage += nomFichier.section('/', 1, 100000);
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && (nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatVideo += nomFichier.section('/', 1, 100000);
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && (nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatMusique += nomFichier.section('/', 1, 100000);
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if((nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatAutre += nomFichier.section('/', 1, 100000);
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat2 += "<center><h1>" + QnombreResultat;
    resultat2 += " Results Found</h1></center>";

    if(texte)
    {
        resultat2 += resultatTexte;
    }

    if(image)
    {
        resultat2 += resultatImage;
    }

    if(musique)
    {
        resultat2 += resultatMusique;
    }

    if(video)
    {
        resultat2 += resultatVideo;
    }

    if(autre)
    {
        resultat2 += resultatAutre;
    }

    FenResultat *fenetreResultat = new FenResultat(resultat2, resultatAffiner2, 5, this);
    fenetreResultat->show();
}

void FenAffiner::recherche_entier_casse()
{
    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;
    bool autre = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultat2 = "";
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner2 = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    int fichier = 0;
    bool termine = false;

    while(!termine)
    {
        QString nomFichier;

        nomFichier = listeFichiersVrai.section('|', fichier, fichier);
        fichier++;

        if(nomFichier.isNull())
        {
            termine = true;
        }

        QString contenueTexte;
        QFile fichier(nomFichier);

        QTextEdit *nomFichierEntierTexte = new QTextEdit;
        QTextEdit *nomFichierEntier = new QTextEdit;
        nomFichierEntier->setPlainText(nomFichier);

        if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                contenueTexte = fichier.readAll();
                fichier.close();

                nomFichierEntierTexte->setPlainText(contenueTexte);

                if((nomFichierEntierTexte->find(mot->text(), QTextDocument::FindWholeWords)) && (nomFichierEntierTexte->find(mot->text(), QTextDocument::FindCaseSensitively)))
                {
                    //nomFichier = nomFichier.section('/', 1, 100000);
                    resultatTexte += nomFichier.section('/', 1, 100000);
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";
                }
            }
        }

        else if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && ((nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(mot->text(), Qt::CaseSensitive))))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatTexte += nomFichier.section('/', 1, 100000);
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && ((nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(mot->text(), Qt::CaseSensitive))))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatImage += nomFichier.section('/', 1, 100000);
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && ((nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(mot->text(), Qt::CaseSensitive))))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatVideo += nomFichier.section('/', 1, 100000);
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && ((nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(mot->text(), Qt::CaseSensitive))))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatMusique += nomFichier.section('/', 1, 100000);
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(mot->text(), Qt::CaseSensitive))))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatAutre += nomFichier.section('/', 1, 100000);
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat2 += "<center><h1>" + QnombreResultat;
    resultat2 += " Results Found</h1></center>";

    if(texte)
    {
        resultat2 += resultatTexte;
    }

    if(image)
    {
        resultat2 += resultatImage;
    }

    if(musique)
    {
        resultat2 += resultatMusique;
    }

    if(video)
    {
        resultat2 += resultatVideo;
    }

    if(autre)
    {
        resultat2 += resultatAutre;
    }

    FenResultat *fenetreResultat = new FenResultat(resultat2, resultatAffiner2, 5, this);
    fenetreResultat->show();
}

void FenAffiner::recherche_entier()
{
    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;
    bool autre = false;

    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, resultatAutre, QnombreResultat;
    resultat2 = "";
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffiner2 = "";
    resultatAutre = "";

    resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
    resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
    resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
    resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";
    resultatAutre += "<u><center><h3>\nOther Results</u>\n\n</h3></center>";

    int fichier = 0;
    bool termine = false;

    while(!termine)
    {
        QString nomFichier;

        nomFichier = listeFichiersVrai.section('|', fichier, fichier);
        fichier++;

        if(nomFichier.isNull())
        {
            termine = true;
        }

        QString contenueTexte;
        QFile fichier(nomFichier);

        QTextEdit *nomFichierEntierTexte = new QTextEdit;
        QTextEdit *nomFichierEntier = new QTextEdit;
        nomFichierEntier->setPlainText(nomFichier);

        if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(mot->text(), Qt::CaseInsensitive)))
        {
            if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                contenueTexte = fichier.readAll();
                fichier.close();

                nomFichierEntierTexte->setPlainText(contenueTexte);

                if(nomFichierEntierTexte->find(mot->text(), QTextDocument::FindWholeWords))
                {
                    //nomFichier = nomFichier.section('/', 1, 100000);
                    resultatTexte += nomFichier.section('/', 1, 100000);
                    resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";
                }
            }
        }

        else if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && (nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatTexte += nomFichier.section('/', 1, 100000);
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatImage += nomFichier.section('/', 1, 100000);
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && (nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatVideo += nomFichier.section('/', 1, 100000);
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && (nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords)))
        {
            //nomFichier = nomFichier.section('/', 1, 100000);
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }

        else if(((nomFichierEntier->find(mot->text(), QTextDocument::FindWholeWords))))
        {
            nomFichier = nomFichier.section('/', -1);
            resultatAutre += nomFichier;
            resultatAutre += "<br />";
            nombreResultat++;
            autre = true;
            resultatAffiner2 += nomFichier;
            resultatAffiner2 += "|";
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat2 += "<center><h1>" + QnombreResultat;
    resultat2 += " Results Found</h1></center>";

    if(texte)
    {
        resultat2 += resultatTexte;
    }

    if(image)
    {
        resultat2 += resultatImage;
    }

    if(musique)
    {
        resultat2 += resultatMusique;
    }

    if(video)
    {
        resultat2 += resultatVideo;
    }

    if(autre)
    {
        resultat2 += resultatAutre;
    }

    FenResultat *fenetreResultat = new FenResultat(resultat2, resultatAffiner2, 5, this);
    fenetreResultat->show();
}

void FenAffiner::creerFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    phrase = new QLabel(tr("Mot à Rechercher :"));
    mot = new QLineEdit;
    lancer = new QPushButton();

    lancer->setIcon(QIcon(":/icones/Fenetre Affiner/kghostview.png"));
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

    #if defined(Q_WS_WIN)
        setFixedSize(340,170);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(340,170);
    #endif

    setWindowTitle(tr("Analyst - Affiner la Recherche"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(lancer, SIGNAL(clicked()), this, SLOT(affiner()));
}

void FenAffiner::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        affiner();
    }
}

void FenAffiner::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
