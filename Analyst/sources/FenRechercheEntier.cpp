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

#include "../headers/FenRechercheEntier.h"

QString resultatAffinerFenetre;
/*QString rechercheFenetre(QString);
QString rechercheCasseFenetre(QString);
QString rechercheEntierFenetre(QString);
QString rechercheCasseEntierFenetre(QString);*/

FenRechercheEntier::FenRechercheEntier(QWidget *parent = 0) : QDialog (parent)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();
    creerStatusBar();
    creerActions();
}

void FenRechercheEntier::fonctionRechercher()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if (label->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un mot à rechercher"));
        return;
    }

    if(!checkBox->isChecked())
    {
        if(!checkBox_2->isChecked())
        {
            rechercheFenetre();
        }

        if(checkBox_2->isChecked())
        {
            rechercheEntierFenetre();
        }
    }

    else
    {
        if(!checkBox_2->isChecked())
        {
            rechercheCasseFenetre();
        }

        if(checkBox_2->isChecked())
        {
            rechercheCasseEntierFenetre();
        }
    }

    //modele = new QStringListModel(&listeFichiers);

    //textEdit->setHtml(resultat);
}

void FenRechercheEntier::rechercheFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString motRecherche = lineEdit->text();

    QStringList listeFichiers;
    QStringList listeFichiersTexte;
    QStringList listeFichiersImage;
    QStringList listeFichiersMusique;
    QStringList listeFichiersVideo;

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
    resultatAffinerFenetre = "";

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
                    resultatAffinerFenetre += donnees;
                    resultatAffinerFenetre += "|";
                    listeFichiersTexte << nomFichier;
                }
            }
        }

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatTexte += nomFichier;
            resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersTexte << nomFichier;
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatImage += nomFichier;
            resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersImage << nomFichier;
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatVideo += nomFichier;
            resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersVideo << nomFichier;
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseInsensitive)))
        {
            resultatMusique += nomFichier;
            resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersMusique << nomFichier;
        }
    }

    QnombreResultat.setNum(nombreResultat);
    resultat += QnombreResultat + " Results Found";
    resultat += " Results Found</h1></center>";

    //listeFichiers << resultat;

    if(texte == false)
    {
        listeFichiers << listeFichiersTexte;
        resultat += resultatTexte;
    }

    if(image == true)
    {
        listeFichiers << listeFichiersImage;
        resultat += resultatImage;
    }

    if(musique == true)
    {
        listeFichiers << listeFichiersMusique;
        resultat += resultatMusique;
    }

    if(video == true)
    {
        listeFichiers << listeFichiersVideo;
        resultat += resultatVideo;
    }

    //listView_2->setPalette(QPalette(QColor(QRgb("#AARRGGBB"))));

    modele = new QStringListModel(listeFichiers);
    listView_2->setModel(modele);

    listView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    listView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    //connect(listView_2, SIGNAL(doubleClicked()), this, SLOT(fonctionAfficherTextes()));



}

void FenRechercheEntier::rechercheCasseFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString motRecherche = lineEdit->text();

    QStringList listeFichiers;
    QStringList listeFichiersTexte;
    QStringList listeFichiersImage;
    QStringList listeFichiersMusique;
    QStringList listeFichiersVideo;

    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;

    QString resultat;
    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffinerFenetre = "";

    /*resultatTexte += "          List of the Texts";
    resultatImage += "          List of the Pictures";
    resultatMusique += "            List of the Musics";
    resultatVideo += "          List of the Videos";
*/
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

                if(texte.contains(motRecherche, Qt::CaseInsensitive))
                {
                    //resultatTexte += nomFichier;
                    //resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffinerFenetre += donnees;
                    resultatAffinerFenetre += "|";
                    listeFichiersTexte << nomFichier;
                }
            }
        }

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            //resultatTexte += nomFichier;
            //resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersTexte << nomFichier;
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            //resultatImage += nomFichier;
            //resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersImage << nomFichier;
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            //resultatVideo += nomFichier;
            //resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersVideo << nomFichier;
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (donnees.contains(motRecherche, Qt::CaseSensitive)))
        {
            //resultatMusique += nomFichier;
            //resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersMusique << nomFichier;
        }
    }

    //QnombreResultat.setNum(nombreResultat);
    //resultat += QnombreResultat + " Results Found";
    //resultat += " Results Found</h1></center>";

    //listeFichiers << resultat;

    if(texte == false)
    {
        listeFichiers << listeFichiersTexte;
    }

    if(image == true)
    {
        listeFichiers << listeFichiersImage;
    }

    if(musique == true)
    {
        listeFichiers << listeFichiersMusique;
    }

    if(video == true)
    {
        listeFichiers << listeFichiersVideo;
    }

    //listView_2->setPalette(QPalette(QColor(QRgb("#AARRGGBB"))));

    modele = new QStringListModel(listeFichiers);
    listView_2->setModel(modele);

}

void FenRechercheEntier::rechercheEntierFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString motRecherche = lineEdit->text();

    QStringList listeFichiers;
    QStringList listeFichiersTexte;
    QStringList listeFichiersImage;
    QStringList listeFichiersMusique;
    QStringList listeFichiersVideo;

    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;

    QString resultat;
    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffinerFenetre = "";

    /*resultatTexte += "          List of the Texts";
    resultatImage += "          List of the Pictures";
    resultatMusique += "            List of the Musics";
    resultatVideo += "          List of the Videos";
*/
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
                    //resultatTexte += nomFichier;
                    //resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffinerFenetre += donnees;
                    resultatAffinerFenetre += "|";
                    listeFichiersTexte << nomFichier;
                }
            }
        }

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            //resultatTexte += nomFichier;
            //resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersTexte << nomFichier;
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            //resultatImage += nomFichier;
            //resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersImage << nomFichier;
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            //resultatVideo += nomFichier;
            //resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersVideo << nomFichier;
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && (nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)))
        {
            //resultatMusique += nomFichier;
            //resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersMusique << nomFichier;
        }
    }

    //QnombreResultat.setNum(nombreResultat);
    //resultat += QnombreResultat + " Results Found";
    //resultat += " Results Found</h1></center>";

    //listeFichiers << resultat;

    if(texte == false)
    {
        listeFichiers << listeFichiersTexte;
    }

    if(image == true)
    {
        listeFichiers << listeFichiersImage;
    }

    if(musique == true)
    {
        listeFichiers << listeFichiersMusique;
    }

    if(video == true)
    {
        listeFichiers << listeFichiersVideo;
    }

    //listView_2->setPalette(QPalette(QColor(QRgb("#AARRGGBB"))));

    modele = new QStringListModel(listeFichiers);
    listView_2->setModel(modele);


}

void FenRechercheEntier::rechercheCasseEntierFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString motRecherche = lineEdit->text();

    QStringList listeFichiers;
    QStringList listeFichiersTexte;
    QStringList listeFichiersImage;
    QStringList listeFichiersMusique;
    QStringList listeFichiersVideo;

    int nombreResultat = 0;
    bool texte = false;
    bool image = false;
    bool video = false;
    bool musique = false;

    QString resultat;
    QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
    resultatImage = "";
    resultatMusique = "";
    resultatTexte = "";
    resultatVideo = "";
    resultatAffinerFenetre = "";

    /*resultatTexte += "          List of the Texts";
    resultatImage += "          List of the Pictures";
    resultatMusique += "            List of the Musics";
    resultatVideo += "          List of the Videos";
*/
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
                    //resultatTexte += nomFichier;
                    //resultatTexte += "<br />";
                    nombreResultat++;
                    texte = true;
                    resultatAffinerFenetre += donnees;
                    resultatAffinerFenetre += "|";
                    listeFichiersTexte << nomFichier;
                }
            }
        }

        else if(((donnees.contains(".txt", Qt::CaseInsensitive)) || (donnees.contains(".doc", Qt::CaseInsensitive)) || (donnees.contains(".pdf", Qt::CaseInsensitive)) || (donnees.contains(".postscript", Qt::CaseInsensitive)) || (donnees.contains(".html", Qt::CaseInsensitive)) || (donnees.contains(".xhtml", Qt::CaseInsensitive)) || (donnees.contains(".odt", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            //resultatTexte += nomFichier;
            //resultatTexte += "<br />";
            nombreResultat++;
            texte = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersTexte << nomFichier;
        }

        if(((donnees.contains(".jpg", Qt::CaseInsensitive)) || (donnees.contains(".png", Qt::CaseInsensitive)) || (donnees.contains(".mng", Qt::CaseInsensitive)) || (donnees.contains(".tiff", Qt::CaseInsensitive)) || (donnees.contains(".jpeg", Qt::CaseInsensitive)) || (donnees.contains(".gif", Qt::CaseInsensitive)) || (donnees.contains(".tga", Qt::CaseInsensitive)) || (donnees.contains(".rtf", Qt::CaseInsensitive)) || (donnees.contains(".openexr", Qt::CaseInsensitive) || (donnees.contains(".bmp", Qt::CaseInsensitive)))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            //resultatImage += nomFichier;
            //resultatImage += "<br />";
            nombreResultat++;
            image = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersImage << nomFichier;
        }

        if(((donnees.contains(".mov", Qt::CaseInsensitive)) || (donnees.contains(".mpeg", Qt::CaseInsensitive)) || (donnees.contains(".ogm", Qt::CaseInsensitive)) || (donnees.contains(".avi", Qt::CaseInsensitive)) || (donnees.contains(".theora", Qt::CaseInsensitive)) || (donnees.contains(".flv", Qt::CaseInsensitive)) || (donnees.contains(".wmv", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            //resultatVideo += nomFichier;
            //resultatVideo += "<br />";
            nombreResultat++;
            video = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersVideo << nomFichier;
        }

        if(((donnees.contains(".ogg", Qt::CaseInsensitive)) || (donnees.contains(".flac", Qt::CaseInsensitive)) || (donnees.contains(".mp3", Qt::CaseInsensitive)) || (donnees.contains(".wav", Qt::CaseInsensitive)) || (donnees.contains(".wma", Qt::CaseInsensitive)) || (donnees.contains(".aac", Qt::CaseInsensitive)) || (donnees.contains(".spx", Qt::CaseInsensitive))) && ((nomFichierEntier->find(motRecherche, QTextDocument::FindWholeWords)) && (donnees.contains(motRecherche, Qt::CaseSensitive))))
        {
            //resultatMusique += nomFichier;
            //resultatMusique += "<br />";
            nombreResultat++;
            musique = true;
            resultatAffinerFenetre += donnees;
            resultatAffinerFenetre += "|";
            listeFichiersMusique << nomFichier;
        }
    }

    //QnombreResultat.setNum(nombreResultat);
    //resultat += QnombreResultat + " Results Found";
    //resultat += " Results Found</h1></center>";

    //listeFichiers << resultat;

    if(texte == false)
    {
        listeFichiers << listeFichiersTexte;
    }

    if(image == true)
    {
        listeFichiers << listeFichiersImage;
    }

    if(musique == true)
    {
        listeFichiers << listeFichiersMusique;
    }

    if(video == true)
    {
        listeFichiers << listeFichiersVideo;
    }

    //listView_2->setPalette(QPalette(QColor(QRgb("#AARRGGBB"))));

    modele = new QStringListModel(listeFichiers);
    listView_2->setModel(modele);

    //listeFichiersVrai = listeFichiers.toString();

}

void FenRechercheEntier::fonctionAfficherTextesSansAfficher( const QModelIndex & index )
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QItemSelectionModel *selection = listView->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole);

        if((elementSelectionne.toString().contains(".txt", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".doc", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".pdf", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".postscript", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".html", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".xhtml", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".odt", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".rtf", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            QFile lancementFichier(vraiNomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                QTextEdit *nouveauTexte = new QTextEdit;
                nouveauTexte->setReadOnly(true);

                if(texte.contains("</"))
                {
                    nouveauTexte->setHtml(texte);
                }

                else
                {
                    nouveauTexte->setPlainText(texte);
                }

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(nouveauTexte, nomImage);

                tabWidget->setCurrentWidget(nouveauTexte);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);

            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

        if((elementSelectionne.toString().contains(".jpg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".png", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".mng", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".tiff", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".jpeg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".gif", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".tga", Qt::CaseInsensitive))  || (elementSelectionne.toString().contains(".bmp", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".openexr", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {


                label = new QLabel(this);
                QPixmap pixmap(vraiNomFichier);
                pixmap = pixmap.scaled(701, 421, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                label->setPixmap(pixmap);
                label->resize(pixmap.size());
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(label, nomImage);

                tabWidget->setCurrentWidget(label);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);

                //verticalLayout_6->addWidget(label);

                //textEdit->setHtml("<img src = \""+ vraiNomFichier +"\" alt = \"\"/>"); QMessageBox::critical(this,tr("Erreur"), vraiNomFichier);

                //isPicture = false;
                //temp = false;

                //images = new QLabel(this);
                /*QPixmap pixmap(elementSelectionne.toString()); QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                //pixmap = pixmap.scaled(450, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                label_4->setPixmap(pixmap);
                label_4->resize(pixmap.size());
                label_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
*/
            }
        }

        if(((elementSelectionne.toString().contains(".mov", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".mpeg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".ogm", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".avi", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".theora", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".flv", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".wmv", Qt::CaseInsensitive))))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                videoPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
                videoPlayer->load(Phonon::MediaSource(vraiNomFichier));

                videoPlayer->play();
                videoPlayer->pause();

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(videoPlayer, nomImage);

                tabWidget->setCurrentWidget(videoPlayer);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);
            }
        }

        if(((elementSelectionne.toString().contains(".ogg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".flac", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".mp3", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".wav", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".wma", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".aac", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".spx", Qt::CaseInsensitive))))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
                mediaObject = new Phonon::MediaObject(this);
                Phonon::createPath(mediaObject, audioOutput);

                volumeSlider = new Phonon::VolumeSlider;
                volumeSlider->setAudioOutput(audioOutput);

                //metaInformationResolver = new Phonon::MediaObject(this);

                mediaObject = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(vraiNomFichier));

                Phonon::createPath(mediaObject, audioOutput);

                mediaObject->setTickInterval(1000);
                connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

                playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Lancer"), this);
                pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
                stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);

                connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
                connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()));
                connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));

                QToolBar *bar = new QToolBar;
                bar->addAction(playAction);
                bar->addAction(pauseAction);
                bar->addAction(stopAction);

                seekSlider = new Phonon::SeekSlider(this);
                seekSlider->setMediaObject(mediaObject);

                QLabel *volumeLabel = new QLabel;
                volumeLabel->setPixmap(QPixmap("images/volume.png"));

                timeLcd = new QLabel;

                QHBoxLayout *seekerLayout = new QHBoxLayout;
                seekerLayout->addWidget(seekSlider);
                seekerLayout->addWidget(timeLcd);

                QHBoxLayout *playbackLayout = new QHBoxLayout;
                playbackLayout->addWidget(bar);
                playbackLayout->addStretch();
                playbackLayout->addWidget(volumeLabel);
                playbackLayout->addWidget(volumeSlider);

                QVBoxLayout *mainLayout = new QVBoxLayout;
                mainLayout->addLayout(seekerLayout);
                mainLayout->addLayout(playbackLayout);
                setLayout(mainLayout);

                QWidget *widget = new QWidget;
                widget->setLayout(mainLayout);

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(widget, nomImage);

                tabWidget->setCurrentWidget(widget);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);


            }
        }
    }
}

void FenRechercheEntier::fonctionAfficherTextes( const QModelIndex & index )
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QItemSelectionModel *selection = listView_2->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole);

        fonctionAjouterFichier(elementSelectionne.toString());

        if((elementSelectionne.toString().contains(".txt", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".doc", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".pdf", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".postscript", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".html", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".xhtml", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".odt", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".rtf", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            QFile lancementFichier(vraiNomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                QTextEdit *nouveauTexte = new QTextEdit;
                nouveauTexte->setReadOnly(true);

                if(texte.contains("</"))
                {
                    nouveauTexte->setHtml(texte);
                }

                else
                {
                    nouveauTexte->setPlainText(texte);
                }

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(nouveauTexte, nomImage);

                tabWidget->setCurrentWidget(nouveauTexte);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);

            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

        if((elementSelectionne.toString().contains(".jpg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".png", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".mng", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".tiff", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".jpeg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".gif", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".tga", Qt::CaseInsensitive))  || (elementSelectionne.toString().contains(".bmp", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".openexr", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {


                label = new QLabel(this);
                QPixmap pixmap(vraiNomFichier);
                pixmap = pixmap.scaled(701, 421, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                label->setPixmap(pixmap);
                label->resize(pixmap.size());
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(label, nomImage);

                tabWidget->setCurrentWidget(label);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);

                //verticalLayout_6->addWidget(label);

                //textEdit->setHtml("<img src = \""+ vraiNomFichier +"\" alt = \"\"/>"); QMessageBox::critical(this,tr("Erreur"), vraiNomFichier);

                //isPicture = false;
                //temp = false;

                //images = new QLabel(this);
                /*QPixmap pixmap(elementSelectionne.toString()); QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                //pixmap = pixmap.scaled(450, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                label_4->setPixmap(pixmap);
                label_4->resize(pixmap.size());
                label_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
*/
            }
        }

        if(((elementSelectionne.toString().contains(".mov", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".mpeg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".ogm", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".avi", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".theora", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".flv", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".wmv", Qt::CaseInsensitive))))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                videoPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
                videoPlayer->load(Phonon::MediaSource(vraiNomFichier));

                videoPlayer->play();
                videoPlayer->pause();

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(videoPlayer, nomImage);

                tabWidget->setCurrentWidget(videoPlayer);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);
            }
        }

        if(((elementSelectionne.toString().contains(".ogg", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".flac", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".mp3", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".wav", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".wma", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".aac", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".spx", Qt::CaseInsensitive))))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
                mediaObject = new Phonon::MediaObject(this);
                Phonon::createPath(mediaObject, audioOutput);

                volumeSlider = new Phonon::VolumeSlider;
                volumeSlider->setAudioOutput(audioOutput);

                //metaInformationResolver = new Phonon::MediaObject(this);

                mediaObject = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(vraiNomFichier));

                Phonon::createPath(mediaObject, audioOutput);

                mediaObject->setTickInterval(1000);
                connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

                playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Lancer"), this);
                pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
                stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);

                connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
                connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()));
                connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));

                QToolBar *bar = new QToolBar;
                bar->addAction(playAction);
                bar->addAction(pauseAction);
                bar->addAction(stopAction);

                seekSlider = new Phonon::SeekSlider(this);
                seekSlider->setMediaObject(mediaObject);

                QLabel *volumeLabel = new QLabel;
                volumeLabel->setPixmap(QPixmap("images/volume.png"));

                timeLcd = new QLabel;

                QHBoxLayout *seekerLayout = new QHBoxLayout;
                seekerLayout->addWidget(seekSlider);
                seekerLayout->addWidget(timeLcd);

                QHBoxLayout *playbackLayout = new QHBoxLayout;
                playbackLayout->addWidget(bar);
                playbackLayout->addStretch();
                playbackLayout->addWidget(volumeLabel);
                playbackLayout->addWidget(volumeSlider);

                QVBoxLayout *mainLayout = new QVBoxLayout;
                mainLayout->addLayout(seekerLayout);
                mainLayout->addLayout(playbackLayout);
                setLayout(mainLayout);

                QWidget *widget = new QWidget;
                widget->setLayout(mainLayout);

                QString nomImage = vraiNomFichier.section('/', -1);
                tabWidget->addTab(widget, nomImage);

                tabWidget->setCurrentWidget(widget);
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);


            }
        }
    }
}

void FenRechercheEntier::affiner()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(checkBox_4->isChecked())
    {

        if(!checkBox_3->isChecked())
        {
            int nombreResultat = 0;
            int texte = 1;
            int image = 0;
            int video = 0;
            int musique = 0;

            QString motRecherche = lineEdit_2->text();

            QStringList listeFichiers;
            QStringList listeFichiersTexte;
            QStringList listeFichiersImage;
            QStringList listeFichiersMusique;
            QStringList listeFichiersVideo;

            QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
            resultat2 = "";
            resultatImage = "";
            resultatMusique = "";
            resultatTexte = "";
            resultatVideo = "";
            resultatAffiner2 = "";

            resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
            resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
            resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
            resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

            int fichier = 0;
            int termine = 0;

            while(termine == 0)
            {
                QString nomFichier;

                nomFichier = listeFichiersVrai.section('|', fichier, fichier); QMessageBox::information(this, "erreur", nomFichier);
                fichier++;

                if(nomFichier.isNull())
                {
                    termine = 1;
                }

                QString contenueTexte;
                QFile fichier(nomFichier);

                QTextEdit *nomFichierEntierTexte = new QTextEdit;
                QTextEdit *nomFichierEntier = new QTextEdit;
                nomFichierEntier->setPlainText(nomFichier);

                if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {
                    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        contenueTexte = fichier.readAll();
                        fichier.close();

                        nomFichierEntierTexte->setPlainText(contenueTexte);

                        if(nomFichierEntierTexte->find(lineEdit->text(), QTextDocument::FindWholeWords))
                        {
                            //nomFichier = nomFichier.section('/', 1, 100000);
                            //resultatTexte += nomFichier;
                            //resultatTexte += "<br />";
                            nombreResultat++;
                            texte = 1;
                            resultatAffiner2 += nomFichier;
                            resultatAffiner2 += "|";

                            listeFichiersTexte << nomFichier;
                        }
                    }
                }

                if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && (nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)))
                {

                    nombreResultat++;
                    texte = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersTexte << nomFichier;
                }

                if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)))
                {

                    nombreResultat++;
                    image = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersImage << nomFichier;
                }

                if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && (nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)))
                {

                    nombreResultat++;
                    video = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersVideo << nomFichier;
                }

                if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && (nomFichierEntier->find(lineEdit->text(), QTextDocument::FindWholeWords)))
                {

                    nombreResultat++;
                    musique = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersMusique << nomFichier;
                }
            }

            QnombreResultat.setNum(nombreResultat);
            resultat2 += "<center><h1>" + QnombreResultat;
            resultat2 += " Results Found</h1></center>";

            if(texte == 1)
            {
                resultat2 += resultatTexte;
            }

            if(image == 1)
            {
                resultat2 += resultatImage;
            }

            if(musique == 1)
            {
                resultat2 += resultatMusique;
            }

            if(video == 1)
            {
                resultat2 += resultatVideo;
            }

            modele = new QStringListModel(listeFichiers);
            listView_2->setModel(modele);
        }

        else
        {
            int nombreResultat = 0;
            int texte = 1;
            int image = 0;
            int video = 0;
            int musique = 0;

            QString motRecherche = lineEdit_2->text();

            QStringList listeFichiers;
            QStringList listeFichiersTexte;
            QStringList listeFichiersImage;
            QStringList listeFichiersMusique;
            QStringList listeFichiersVideo;

            QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
            resultat2 = "";
            resultatImage = "";
            resultatMusique = "";
            resultatTexte = "";
            resultatVideo = "";
            resultatAffiner2 = "";

            resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
            resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
            resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
            resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

            int fichier = 0;
            int termine = 0;

            while(termine == 0)
            {
                QString nomFichier;

                nomFichier = listeFichiersVrai.section('|', fichier, fichier);
                fichier++;

                if(nomFichier.isNull())
                {
                    termine = 1;
                }

                QString contenueTexte;
                QFile fichier(nomFichier);

                QTextEdit *nomFichierEntierTexte = new QTextEdit;
                QTextEdit *nomFichierEntier = new QTextEdit;
                nomFichierEntier->setPlainText(nomFichier);

                if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {
                    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        contenueTexte = fichier.readAll();
                        fichier.close();

                        nomFichierEntierTexte->setPlainText(contenueTexte);

                        if((nomFichierEntierTexte->find(lineEdit_2->text(), QTextDocument::FindWholeWords)) && (nomFichierEntierTexte->find(lineEdit_2->text(), QTextDocument::FindCaseSensitively)))

                        {

                            nombreResultat++;
                            texte = 1;
                            resultatAffiner2 += nomFichier;
                            resultatAffiner2 += "|";

                            listeFichiersTexte << nomFichier;
                        }
                    }
                }

                if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && ((nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive))))
                {

                    nombreResultat++;
                    texte = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersImage << nomFichier;
                }

                if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && ((nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive))))
                {

                    nombreResultat++;
                    image = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersImage << nomFichier;
                }

                if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && ((nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive))))
                {

                    nombreResultat++;
                    video = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersVideo << nomFichier;
                }

                if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && ((nomFichierEntier->find(lineEdit_2->text(), QTextDocument::FindWholeWords)) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive))))
                {

                    nombreResultat++;
                    musique = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersMusique << nomFichier;
                }
            }

            QnombreResultat.setNum(nombreResultat);
            resultat2 += "<center><h1>" + QnombreResultat;
            resultat2 += " Results Found</h1></center>";

            if(texte == 1)
            {
                resultat2 += resultatTexte;
            }

            if(image == 1)
            {
                resultat2 += resultatImage;
            }

            if(musique == 1)
            {
                resultat2 += resultatMusique;
            }

            if(video == 1)
            {
                resultat2 += resultatVideo;
            }

            modele = new QStringListModel(listeFichiers);
            listView_2->setModel(modele);
        }
    }

    else
    {
        if(!checkBox_3->isChecked())
        {
            int nombreResultat = 0;
            int texte = 1;
            int image = 0;
            int video = 0;
            int musique = 0;

            QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
            resultat2 = "";
            resultatImage = "";
            resultatMusique = "";
            resultatTexte = "";
            resultatVideo = "";
            resultatAffiner2 = "";

            QString motRecherche = lineEdit_2->text();

            QStringList listeFichiers;
            QStringList listeFichiersTexte;
            QStringList listeFichiersImage;
            QStringList listeFichiersMusique;
            QStringList listeFichiersVideo;

            resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
            resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
            resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
            resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

            int fichier = 0;
            int termine = 0;

            while(termine == 0)
            {
                QString nomFichier;

                nomFichier = listeFichiersVrai.section('|', fichier, fichier);
                fichier++;

                if(nomFichier.isNull())
                {
                    termine = 1;
                }

                QString contenueTexte;
                QFile fichier(nomFichier);

                if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {
                    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        contenueTexte = fichier.readAll();
                        fichier.close();

                        if(contenueTexte.contains(lineEdit_2->text(), Qt::CaseInsensitive))
                        {

                            nombreResultat++;
                            texte = 1;
                            resultatAffiner2 += nomFichier;
                            resultatAffiner2 += "|";

                            listeFichiersTexte << nomFichier;
                        }
                    }
                }

                if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {

                    nombreResultat++;
                    texte = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersTexte << nomFichier;
                }

                if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {

                    nombreResultat++;
                    image = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersImage << nomFichier;
                }

                if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {

                    nombreResultat++;
                    video = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersVideo << nomFichier;
                }

                if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseInsensitive)))
                {

                    nombreResultat++;
                    musique = 1;
                    resultatAffiner2 += nomFichier;
                    resultatAffiner2 += "|";

                    listeFichiersMusique << nomFichier;
                }
            }


        QnombreResultat.setNum(nombreResultat);
        resultat2 += "<center><h1>" + QnombreResultat;
        resultat2 += " Results Found</h1></center>";

        if(texte == 1)
        {
            resultat2 += resultatTexte;
        }

        if(image == 1)
        {
            resultat2 += resultatImage;
        }

        if(musique == 1)
        {
            resultat2 += resultatMusique;
        }

        if(video == 1)
        {
            resultat2 += resultatVideo;
        }

        modele = new QStringListModel(listeFichiers);
        listView_2->setModel(modele);
    }

    else
    {
        int nombreResultat = 0;
        int texte = 1;
        int image = 0;
        int video = 0;
        int musique = 0;

        QString motRecherche = lineEdit_2->text();

        QStringList listeFichiers;
        QStringList listeFichiersTexte;
        QStringList listeFichiersImage;
        QStringList listeFichiersMusique;
        QStringList listeFichiersVideo;

        QString resultatTexte, resultatImage, resultatVideo, resultatMusique, QnombreResultat;
        resultat2 = "";
        resultatImage = "";
        resultatMusique = "";
        resultatTexte = "";
        resultatVideo = "";
        resultatAffiner2 = "";

        resultatTexte += "<u><center><h3>\n\nList of the Texts</u>\n\n</h3></center>";
        resultatImage += "<u><center><h3>\nList of the Pictures</u>\n\n</h3></center>";
        resultatMusique += "<u><center><h3>\nList of the Music</u>\n\n</h3></center>";
        resultatVideo += "<u><center><h3>\nList of the Videos</u>\n\n</h3></center>";

        int fichier = 0;
        int termine = 0;

        while(termine == 0)
        {
            QString nomFichier;
            nomFichier = listeFichiersVrai.section('|', fichier, fichier);
            fichier++;

            if(nomFichier.isNull())
            {
                termine = 1;
            }

            QString contenueTexte;
            QFile fichier(nomFichier);

            if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && !(nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive)))
            {
                if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    contenueTexte = fichier.readAll();
                    fichier.close();

                    if(contenueTexte.contains(lineEdit_2->text(), Qt::CaseSensitive))
                    {

                        nombreResultat++;
                        texte = 1;
                        resultatAffiner2 += nomFichier;
                        resultatAffiner2 += "|";

                        listeFichiersTexte << nomFichier;
                    }
                }
            }

            if(((nomFichier.contains(".txt", Qt::CaseInsensitive)) || (nomFichier.contains(".doc", Qt::CaseInsensitive)) || (nomFichier.contains(".pdf", Qt::CaseInsensitive)) || (nomFichier.contains(".postscript", Qt::CaseInsensitive)) || (nomFichier.contains(".html", Qt::CaseInsensitive)) || (nomFichier.contains(".xhtml", Qt::CaseInsensitive)) || (nomFichier.contains(".odt", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive)))
            {

                nombreResultat++;
                texte = 1;
                resultatAffiner2 += nomFichier;
                resultatAffiner2 += "|";

                listeFichiersTexte << nomFichier;
            }

            if(((nomFichier.contains(".jpg", Qt::CaseInsensitive)) || (nomFichier.contains(".png", Qt::CaseInsensitive)) || (nomFichier.contains(".mng", Qt::CaseInsensitive)) || (nomFichier.contains(".tiff", Qt::CaseInsensitive)) || (nomFichier.contains(".jpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".gif", Qt::CaseInsensitive)) || (nomFichier.contains(".tga", Qt::CaseInsensitive)) || (nomFichier.contains(".rtf", Qt::CaseInsensitive)) || (nomFichier.contains(".openexr", Qt::CaseInsensitive) || (nomFichier.contains(".bmp", Qt::CaseInsensitive)))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive)))
            {

                nombreResultat++;
                image = 1;
                resultatAffiner2 += nomFichier;
                resultatAffiner2 += "|";

                listeFichiersImage << nomFichier;
            }

            if(((nomFichier.contains(".mov", Qt::CaseInsensitive)) || (nomFichier.contains(".mpeg", Qt::CaseInsensitive)) || (nomFichier.contains(".ogm", Qt::CaseInsensitive)) || (nomFichier.contains(".avi", Qt::CaseInsensitive)) || (nomFichier.contains(".theora", Qt::CaseInsensitive)) || (nomFichier.contains(".flv", Qt::CaseInsensitive)) || (nomFichier.contains(".wmv", Qt::CaseInsensitive))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive)))
            {

                nombreResultat++;
                video = 1;
                resultatAffiner2 += nomFichier;
                resultatAffiner2 += "|";

                listeFichiersVideo << nomFichier;
            }

            if(((nomFichier.contains(".ogg", Qt::CaseInsensitive)) || (nomFichier.contains(".flac", Qt::CaseInsensitive)) || (nomFichier.contains(".mp3", Qt::CaseInsensitive)) || (nomFichier.contains(".wav", Qt::CaseInsensitive)) || (nomFichier.contains(".wma", Qt::CaseInsensitive)) || (nomFichier.contains(".aac", Qt::CaseInsensitive)) || (nomFichier.contains(".spx", Qt::CaseInsensitive))) && (nomFichier.contains(lineEdit_2->text(), Qt::CaseSensitive)))
            {

                nombreResultat++;
                musique = 1;
                resultatAffiner2 += nomFichier;
                resultatAffiner2 += "|";

                listeFichiersMusique << nomFichier;
            }
        }

        QnombreResultat.setNum(nombreResultat);
        resultat2 += "<center><h1>" + QnombreResultat;
        resultat2 += " Results Found</h1></center>";

        if(texte == 1)
        {
            resultat2 += resultatTexte;
        }

        if(image == 1)
        {
            resultat2 += resultatImage;
        }

        if(musique == 1)
        {
            resultat2 += resultatMusique;
        }

        if(video == 1)
        {
            resultat2 += resultatVideo;
        }

        modele = new QStringListModel(listeFichiers);
        listView_2->setModel(modele);

        }
    }
}

void FenRechercheEntier::fonctionAjouterFichier(QString nomFichier)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QStringListModel *modele2 = new QStringListModel;
    listeFichierOuverts << nomFichier;
    modele2->setStringList(listeFichierOuverts);
    listView->setModel(modele2);


}


void FenRechercheEntier::messageOuvrirTousTextes()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Ouvrir tous les textes"), 2000);
}

void FenRechercheEntier::fonctionOuvrirTousTextes()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QItemSelectionModel *selection = listView->selectionModel(); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
    QModelIndexList listeSelections = selection->selectedIndexes(); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));

        fonctionAjouterFichier(elementSelectionne.toString()); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));

        if((elementSelectionne.toString().contains(".txt", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".doc", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".pdf", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".postscript", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".html", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".xhtml", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".odt", Qt::CaseInsensitive)) || (elementSelectionne.toString().contains(".rtf", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier; QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            vraiNomFichier = "";
            vraiNomFichier = "DataBase/";
            vraiNomFichier += elementSelectionne.toString();

            QFile lancementFichier(vraiNomFichier); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll(); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
                lancementFichier.close();

                QTextEdit *nouveauTexte = new QTextEdit; QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
                nouveauTexte->setReadOnly(true);

                if(texte.contains("</"))
                {
                    nouveauTexte->setHtml(texte);
                }

                else
                {
                    nouveauTexte->setPlainText(texte);
                }

                QString nomTexte = vraiNomFichier.section('/', -1); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
                tabWidget->addTab(nouveauTexte, nomTexte);

                tabWidget->setCurrentWidget(nouveauTexte); QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
                tabWidget->setMovable(true);
                tabWidget->setTabsClosable(true);

            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

    }
}

void FenRechercheEntier::messageOuvrirToutesImages()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Ouvrir tous les images"), 2000);
}

void FenRechercheEntier::fonctionOuvrirToutesImages()
{

}

void FenRechercheEntier::messageOuvrirToutesMusiques()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Ouvrir tous les musiques"), 2000);
}

void FenRechercheEntier::fonctionOuvrirToutesMusiques()
{

}

void FenRechercheEntier::messageOuvrirToutesVideos()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Ouvrir tous les videos"), 2000);
}

void FenRechercheEntier::fonctionOuvrirToutesVideos()
{

}

void FenRechercheEntier::messageAfficherTousTextes()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher tous les textes"), 2000);
}

void FenRechercheEntier::afficherTextes()
{

}

void FenRechercheEntier::messageAfficherToutesImages()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher tous les images"), 2000);
}

void FenRechercheEntier::afficherImages()
{

}

void FenRechercheEntier::messageAfficherToutesMusiques()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher tous les musiques"), 2000);
}

void FenRechercheEntier::afficherMusiques()
{

}

void FenRechercheEntier::messageAfficherToutesVideos()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher tous les videos"), 2000);
}

void FenRechercheEntier::afficherVideos()
{

}

void FenRechercheEntier::afficherToutEditer()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Editer le document"), 2000);
}

void FenRechercheEntier::fonctionToutEditer()
{

}

void FenRechercheEntier::afficherEditerPartie()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Editer le texte séléctionné"), 2000);
}

void FenRechercheEntier::fonctionEditerPartie()
{

}

void FenRechercheEntier::afficherInformations()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Afficher les résultats détaillés de la recherche"), 2000);

    //QMessageBox::critical(this, tr("Erreur"), tr("Vous devez séléctionner du texte pour pouvoir l'éditer"));
}

void FenRechercheEntier::fonctionInformations()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif



    FenInfoRecherche *fenetreInfoRecherche = new FenInfoRecherche(resultat, resultatAffinerFenetre, this);
    fenetreInfoRecherche->show();

    //FenResultat *fenetreResultat = new FenResultat(resultat, this);
    //fenetreResultat->show();

}

void FenRechercheEntier::fonctionFermerTab(int numeroWidget)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    tabWidget->removeTab(numeroWidget);
}



void FenRechercheEntier::mousePressEvent (QMouseEvent*)
{
    if(videoPlayer->isPaused())
    {
        videoPlayer->play();
    }

    else if(videoPlayer->isPlaying())
    {
        videoPlayer->pause();
    }

    else
    {
        videoPlayer->play();
    }
}

void FenRechercheEntier::closeEvent(QCloseEvent*)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    videoPlayer->stop();   // VIDEO
    mediaObject->stop();  // Musique

    this->deleteLater();
}

void FenRechercheEntier::mouseDoubleClickEvent(QMouseEvent*)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    videoPlayer->stop();
    videoPlayer->play();
    videoPlayer->pause();
}

void FenRechercheEntier::tick(qint64 time)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
     timeLcd->setText(displayTime.toString("mm:ss"));
}

void FenRechercheEntier::creerStatusBar()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut = new QStatusBar(this);
    statut->showMessage(tr("Pret"));

    //QMessageBox::critical(this, tr("Erreur"), statut->currentMessage());

    //statusBar()->showMessage(tr("Ready"));
    //QProgressBar *progression = new QProgressBar;
    //statut->addWidget(progression);

}

void FenRechercheEntier::creerActions()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    /*               OUVRIR UN SEUL TYPE DE FICHIER             */

    ouvrirTousTextes = new QAction(this);
    ouvrirTousTextes->setIcon(QIcon(":/icones/Fenetre Recherche Entier/soffice.png"));
    connect(ouvrirTousTextes, SIGNAL(hovered()), this, SLOT(messageOuvrirTousTextes()));
    connect(ouvrirTousTextes, SIGNAL(triggered()), this, SLOT(fonctionOuvrirTousTextes()));
    toolBar->addAction(ouvrirTousTextes);

    ouvrirToutesImages = new QAction(this);
    ouvrirToutesImages->setIcon(QIcon(":/icones/Fenetre Recherche Entier/png-2.png"));
    connect(ouvrirToutesImages, SIGNAL(hovered()), this, SLOT(messageOuvrirToutesImages()));
    connect(ouvrirToutesImages, SIGNAL(triggered()), this, SLOT(fonctionOuvrirToutesImages()));
    toolBar->addAction(ouvrirToutesImages);

    ouvrirToutesMusiques = new QAction(this);
    ouvrirToutesMusiques->setIcon(QIcon(":/icones/Fenetre Recherche Entier/mp3-2.png"));
    connect(ouvrirToutesMusiques, SIGNAL(hovered()), this, SLOT(messageOuvrirToutesMusiques()));
    connect(ouvrirToutesMusiques, SIGNAL(triggered()), this, SLOT(fonctionOuvrirToutesMusiques()));
    toolBar->addAction(ouvrirToutesMusiques);

    ouvrirToutesVideos = new QAction(this);
    ouvrirToutesVideos->setIcon(QIcon(":/icones/Fenetre Recherche Entier/mov.png"));
    connect(ouvrirToutesVideos, SIGNAL(hovered()), this, SLOT(messageOuvrirToutesVideos()));
    connect(ouvrirToutesVideos, SIGNAL(triggered()), this, SLOT(fonctionOuvrirToutesVideos()));
    toolBar->addAction(ouvrirToutesVideos);

    toolBar->addSeparator();

    /*                   AFFIHCHER QU'UN SEUL TYPE DE FICHIER                */

    outilsTexte = new QAction(this);
    outilsTexte->setIcon(QIcon(":/icones/Fenetre Recherche Entier/folder_documents.png"));
    connect(outilsTexte, SIGNAL(hovered()), this, SLOT(messageAfficherTousTextes()));
    connect(outilsTexte, SIGNAL(triggered()), this, SLOT(afficherTextes()));
    toolBar->addAction(outilsTexte);

    outilsImage = new QAction(this);
    outilsImage->setIcon(QIcon(":/icones/Fenetre Recherche Entier/folder_images.png"));
    connect(outilsImage, SIGNAL(hovered()), this, SLOT(messageAfficherToutesImages()));
    connect(outilsImage, SIGNAL(triggered()), this, SLOT(afficherImages()));
    toolBar->addAction(outilsImage);

    outilsVideo = new QAction(this);
    outilsVideo->setIcon(QIcon(":/icones/Fenetre Recherche Entier/folder_video.png"));
    connect(outilsVideo, SIGNAL(hovered()), this, SLOT(messageAfficherToutesVideos()));
    connect(outilsVideo, SIGNAL(triggered()), this, SLOT(afficherVideos()));
    toolBar->addAction(outilsVideo);

    outilsMusique = new QAction(this);
    outilsMusique->setIcon(QIcon(":/icones/Fenetre Recherche Entier/folder_music.png"));
    connect(outilsMusique, SIGNAL(hovered()), this, SLOT(messageAfficherToutesMusiques()));
    connect(outilsMusique, SIGNAL(triggered()), this, SLOT(afficherMusiques()));
    toolBar->addAction(outilsMusique);

    toolBar->addSeparator();

    editerTous = new QAction(this);
    editerTous->setIcon(QIcon(":/icones/Fenetre Recherche Entier/kedit.png"));
    connect(editerTous, SIGNAL(hovered()), this, SLOT(afficherToutEditer()));
    connect(editerTous, SIGNAL(triggered()), this, SLOT(fonctionToutEditer()));
    toolBar->addAction(editerTous);

    editerPartie = new QAction(this);
    editerPartie->setIcon(QIcon(":/icones/Fenetre Recherche Entier/editpaste.png"));
    connect(editerPartie, SIGNAL(hovered()), this, SLOT(afficherEditerPartie()));
    connect(editerPartie, SIGNAL(triggered()), this, SLOT(fonctionEditerPartie()));
    editerPartie->setEnabled(false);
    toolBar->addAction(editerPartie);

    toolBar->addSeparator();

    informations = new QAction(this);
    informations->setIcon(QIcon(":/icones/Fenetre Recherche Entier/info.png"));
    connect(informations, SIGNAL(hovered()), this, SLOT(afficherInformations()));
    connect(informations, SIGNAL(triggered()), this, SLOT(fonctionInformations()));
    toolBar->addAction(informations);
}



void FenRechercheEntier::creerFenetre()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif



    listView = new QListView(this);
    listView->setObjectName(QString::fromUtf8("listView"));
    listView->setGeometry(QRect(10, 40, 281, 631));



    listView_2 = new QListView(this);
    listView_2->setObjectName(QString::fromUtf8("listView_2"));
    listView_2->setGeometry(QRect(310, 470, 921, 201));



    verticalLayoutWidget_3 = new QWidget(this);
    verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
    verticalLayoutWidget_3->setGeometry(QRect(1020, 40, 163, 421));



    verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    verticalLayout_3->setContentsMargins(0, 0, 0, 0);



    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));



    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));



    label = new QLabel(verticalLayoutWidget_3);
    label->setObjectName(QString::fromUtf8("label"));



    verticalLayout->addWidget(label);

    lineEdit = new QLineEdit(verticalLayoutWidget_3);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    verticalLayout->addWidget(lineEdit);

    checkBox = new QCheckBox(verticalLayoutWidget_3);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    verticalLayout->addWidget(checkBox);

    checkBox_2 = new QCheckBox(verticalLayoutWidget_3);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    verticalLayout->addWidget(checkBox_2);

    pushButton = new QPushButton(verticalLayoutWidget_3);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    verticalLayout->addWidget(pushButton);

    verticalLayout_5 = new QVBoxLayout();
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

    verticalSpacer = new QSpacerItem(88, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_4->addItem(verticalSpacer);

    label_3 = new QLabel(verticalLayoutWidget_3);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    verticalLayout_4->addWidget(label_3);

    verticalSpacer_17 = new QSpacerItem(153, 88, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_4->addItem(verticalSpacer_17);

    verticalLayout_5->addLayout(verticalLayout_4);

    label_2 = new QLabel(verticalLayoutWidget_3);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout_5->addWidget(label_2);

    lineEdit_2 = new QLineEdit(verticalLayoutWidget_3);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

    verticalLayout_5->addWidget(lineEdit_2);

    checkBox_3 = new QCheckBox(verticalLayoutWidget_3);
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

    verticalLayout_5->addWidget(checkBox_3);

    checkBox_4 = new QCheckBox(verticalLayoutWidget_3);
    checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

    verticalLayout_5->addWidget(checkBox_4);

    pushButton_2 = new QPushButton(verticalLayoutWidget_3);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    verticalLayout_5->addWidget(pushButton_2);


    verticalLayout->addLayout(verticalLayout_5);


    verticalLayout_2->addLayout(verticalLayout);


    verticalLayout_3->addLayout(verticalLayout_2);

    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setGeometry(QRect(310, 40, 701, 421));

    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));

    textEdit = new QTextEdit(tab);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setGeometry(QRect(0, -30, 701, 421));
    textEdit->setMinimumSize(QSize(100, 100));
    textEdit->setReadOnly(true);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    tabWidget->addTab(tab_2, QString());

    tabWidget->setCurrentIndex(0);



    label->setText(tr("Mot à rechercher"));
    checkBox->setText(tr("Respecter la casse"));
    checkBox->setChecked(false);
    checkBox_2->setText(tr("Rechercher le mot\nen entier"));
    checkBox_2->setChecked(true);
    pushButton->setText("");
    pushButton->setIcon(QIcon(":/icones/Fenetre Recherche Entier/kghostview.png"));
    pushButton->setIconSize(QSize(60,60));
    pushButton->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    textEdit->setFont(QFont("Courier"));

    label_2->setText(tr("Affiner"));
    checkBox_3->setText(tr("Respecter la casse"));
    checkBox_3->setChecked(false);
    checkBox_4->setText(tr("Rechercher le mot\nen entier"));
    checkBox_4->setChecked(true);
    pushButton_2->setText("");
    pushButton_2->setIcon(QIcon(":/icones/Fenetre Recherche Entier/kghostview.png"));
    pushButton_2->setIconSize(QSize(60,60));
    pushButton_2->setStyleSheet("background-color: transparent; border: 0; outline: 0;");

    label_3->setText("<hr />");

    tabWidget->removeTab(1);
    tabWidget->removeTab(0);

    listView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    listView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(pushButton, SIGNAL(clicked()), this, SLOT(fonctionRechercher()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(affiner()));
    connect(listView_2, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(fonctionAfficherTextes(const QModelIndex &)));
    connect(listView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(fonctionAfficherTextesSansAfficher(const QModelIndex &)));
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(fonctionFermerTab(int)));



    setWindowTitle("Analyst");
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    #if defined(Q_WS_WIN)

    #endif

    #if defined(Q_WS_X11)
        setFixedSize(1238,692);
    #endif
}
