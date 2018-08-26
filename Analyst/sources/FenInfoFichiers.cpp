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

#include "../headers/FenInfoFichiers.h"

FenInfoFichiers::FenInfoFichiers(QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");

    creerNombre();

    creerTaille();

    creerFenetre();
}

void FenInfoFichiers::creerNombre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QLabel *OctetTotal = new QLabel;
    QLabel *OctetTextes = new QLabel;
    QLabel *OctetImages = new QLabel;
    QLabel *OctetMusiques = new QLabel;
    QLabel *OctetVideos = new QLabel;

    QStringList fichierTextes;
    fichierTextes << "*.txt" << "*.txt" << "*.doc" << "*.pdf" << "*.postscript" << "*.html" << "*.xhtml" << "*.odt" << "*.rtf";

    QStringList fichierImages;
    fichierImages << "*.jpg" << "*.png" << "*.mng" << "*.tiff" << "*.jpeg" << "*.gif" << "*.tga" << "*.rtf" << "*.openexr" << "*.bmp";

    QStringList fichierMusiques;
    fichierMusiques << "*.ogg" << "*.flac" << "*.mp3" << "*.wav" << "*.wma" << "*.aac" << "*.spx";

    QStringList fichierVideos;
    fichierVideos << "*.mov" << "*.mpeg" << "*.ogm" << "*.avi" << "*.theora" << "*.flv" << "*.wmv";

    QStringList files = direction.entryList();
    double octetTotal = 0;

    for(int i = 0; i < files.size(); i++)
    {
        QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + files.at(i));
        octetTotal += (fichier.size()/* / 1000000*/);
    }

    QString QTailleOctet;

    QTailleOctet.setNum(octetTotal);
    OctetTotal->setText(tr("Taille Totale : ") + QTailleOctet + tr(" octets"));

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetTotal->setText(tr("Taille Totale : ") + QTailleOctet + tr(" Ko"));
    }


    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetTotal->setText(tr("Taille Totale : ") + QTailleOctet + tr(" Mo"));
    }

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetTotal->setText(tr("Taille Totale : ") + QTailleOctet + tr(" Go"));
    }


    /*                    TAILLE TEXTES                      */

    files = direction.entryList(fichierTextes);

    octetTotal = 0;

    for(int i = 0; i < files.size(); i++)
    {
        QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + files.at(i));
        octetTotal += (fichier.size()/* / 1000*/);
    }

    QTailleOctet.setNum(octetTotal);
    OctetTextes->setText(tr("Taille des Textes : ") + QTailleOctet + tr(" octets"));

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetTextes->setText(tr("Taille des Textes : ") + QTailleOctet + tr(" Ko"));
    }


    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetTextes->setText(tr("Taille des Textes : ") + QTailleOctet + tr(" Mo"));
    }

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetTextes->setText(tr("Taille des Textes : ") + QTailleOctet + tr(" Go"));
    }


    /*                    TAILLE IMAGES                      */

    files = direction.entryList(fichierImages);

    octetTotal = 0;

    for(int i = 0; i < files.size(); i++)
    {
        QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + files.at(i));
        octetTotal += (fichier.size()/* / 1000000*/);
    }

    QTailleOctet.setNum(octetTotal);
    OctetImages->setText(tr("Taille des Images : ") + QTailleOctet + tr(" octets"));

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetImages->setText(tr("Taille des Images : ") + QTailleOctet + tr(" Ko"));
    }


    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetImages->setText(tr("Taille des Images : ") + QTailleOctet + tr(" Mo"));
    }

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetImages->setText(tr("Taille des Images : ") + QTailleOctet + tr(" Go"));
    }



    /*                    TAILLE MUSIQUES                      */

    files = direction.entryList(fichierMusiques);

    octetTotal = 0;

    for(int i = 0; i < files.size(); i++)
    {
        QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + files.at(i));
        octetTotal += (fichier.size() /*/ 1000000*/);
    }

    QTailleOctet.setNum(octetTotal);
    OctetMusiques->setText(tr("Taille des Musiques : ") + QTailleOctet + tr(" octets"));

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetMusiques->setText(tr("Taille des Musiques : ") + QTailleOctet + tr(" Ko"));
    }


    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetMusiques->setText(tr("Taille des Musiques : ") + QTailleOctet + tr(" Mo"));
    }

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetMusiques->setText(tr("Taille des Musiques : ") + QTailleOctet + tr(" Go"));
    }


    /*                    TAILLE VIDEOS                      */

    files = direction.entryList(fichierVideos);

    octetTotal = 0;

    for(int i = 0; i < files.size(); i++)
    {
        QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + files.at(i));
        octetTotal += (fichier.size() /*/ 1000000*/);
    }

    QTailleOctet.setNum(octetTotal);
    OctetVideos->setText(tr("Taille des Videos : ") + QTailleOctet + tr(" octets"));

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetVideos->setText(tr("Taille des Videos : ") + QTailleOctet + tr(" Ko"));
    }


    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetVideos->setText(tr("Taille des Videos : ") + QTailleOctet + tr(" Mo"));
    }

    if(octetTotal >= 1000)
    {
        octetTotal /= 1000;
        QTailleOctet.setNum(octetTotal);
        OctetVideos->setText(tr("Taille des Videos : ") + QTailleOctet + tr(" Go"));
    }

    layoutOctet = new QVBoxLayout;
    layoutOctet->addWidget(OctetTextes);
    layoutOctet->addWidget(OctetImages);
    layoutOctet->addWidget(OctetMusiques);
    layoutOctet->addWidget(OctetVideos);
    layoutOctet->addWidget(OctetTotal);
}

void FenInfoFichiers::creerTaille()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    /*                    NOMBRE TOTAL                       */

    QStringList files = direction.entryList();
    files.removeOne(".");
    files.removeOne("..");

    QString QNombreFichier;

    int nombreFichier = files.size();
    QNombreFichier.setNum(nombreFichier);

    QLabel *tailleTotale = new QLabel(tr("Total : ") + QNombreFichier);

    /*                    NOMBRE TEXTES                     */

    QStringList fichierTextes;
    fichierTextes << "*.txt" << "*.txt" << "*.doc" << "*.pdf" << "*.postscript" << "*.html" << "*.xhtml" << "*.odt" << "*.rtf";

    files = direction.entryList(fichierTextes);

    nombreFichier = files.size();
    QNombreFichier.setNum(nombreFichier);

    QLabel *tailleTextes = new QLabel(tr("Nombre de Textes : ") + QNombreFichier);

    /*                    NOMBRE IMAGES                      */

    QStringList fichierImages;
    fichierImages << "*.jpg" << "*.png" << "*.mng" << "*.tiff" << "*.jpeg" << "*.gif" << "*.tga" << "*.rtf" << "*.openexr" << "*.bmp";

    files = direction.entryList(fichierImages);

    nombreFichier = files.size();
    QNombreFichier.setNum(nombreFichier);

    QLabel *tailleImages = new QLabel(tr("Nombre d'Images : ") + QNombreFichier);

    /*                    NOMBRE MUSIQUES                     */

    QStringList fichierMusiques;
    fichierMusiques << "*.ogg" << "*.flac" << "*.mp3" << "*.wav" << "*.wma" << "*.aac" << "*.spx";

    files = direction.entryList(fichierMusiques);

    nombreFichier = files.size();
    QNombreFichier.setNum(nombreFichier);

    QLabel *tailleMusiques = new QLabel(tr("Nombre de Musiques : ") + QNombreFichier);

    /*                    NOMBRE VIDEOS                     */

    QStringList fichierVideos;
    fichierVideos << "*.mov" << "*.mpeg" << "*.ogm" << "*.avi" << "*.theora" << "*.flv" << "*.wmv";

    files = direction.entryList(fichierVideos);

    nombreFichier = files.size();
    QNombreFichier.setNum(nombreFichier);

    QLabel *tailleVideos = new QLabel(tr("Nombre de Videos : ") + QNombreFichier);

    layoutTaille = new QVBoxLayout;
    layoutTaille->addWidget(tailleTextes);
    layoutTaille->addWidget(tailleImages);
    layoutTaille->addWidget(tailleMusiques);
    layoutTaille->addWidget(tailleVideos);
    layoutTaille->addWidget(tailleTotale);
}

void FenInfoFichiers::creerFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    image = new QLabel(this);

    QPixmap pixmap(":/icones/Fenetre Informations Dossier/folder.png");
    pixmap = pixmap.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    image->setPixmap(pixmap);
    image->resize(pixmap.size());

    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *layoutTailleImage = new QHBoxLayout;
    layoutTailleImage->addWidget(image);
    layoutTailleImage->addLayout(layoutTaille);
    layoutTailleImage->addLayout(layoutOctet);

    setLayout(layoutTailleImage);
    setWindowTitle(tr("Analyst - Propriétés de la Base de Donnée"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    #if defined(Q_WS_WIN)

    #endif

    #if defined(Q_WS_X11)
        setFixedSize(470,130);
    #endif
}

void FenInfoFichiers::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        this->deleteLater();
    }
}

void FenInfoFichiers::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
