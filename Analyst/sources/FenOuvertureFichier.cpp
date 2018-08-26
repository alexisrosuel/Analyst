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

#include "../headers/FenOuvertureFichier.h"

FenOuvertureFichier::FenOuvertureFichier(QString listeDesFichiers, QWidget *parent = 0) : QDialog (parent)   // &listeDesFichiers
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    listeFichiers = listeDesFichiers;
    creerFenetre(listeDesFichiers);
}

void FenOuvertureFichier::ouvrir()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if (nomFichier->toPlainText().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un nom de fichier à ouvrir"));
        return;
    }

    QString nomDesFichiers(nomFichier->toPlainText());
    QString fichier = "a";
    int numeroFichier = 0;

    while(!fichier.isNull())
    {
        fichier = nomDesFichiers.section("\n", numeroFichier, numeroFichier);
        numeroFichier++;

        if((fichier.contains(".txt", Qt::CaseInsensitive)) || (fichier.contains(".pdf", Qt::CaseInsensitive)) || (fichier.contains(".postscript", Qt::CaseInsensitive)) || (fichier.contains(".html", Qt::CaseInsensitive)) || (fichier.contains(".xhtml", Qt::CaseInsensitive)) || (fichier.contains(".rtf", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = QDir::homePath() + "/Analyst/" + "DataBase/";
            vraiNomFichier += fichier;

            QFile lancementFichier(vraiNomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                FenFichierTexte *fenetreTexte = new FenFichierTexte(texte, fichier, this);
                fenetreTexte->show();
                qApp->processEvents();
            }

            else
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier n'existe pas"));
            }
        }

        else if((fichier.contains(".doc", Qt::CaseInsensitive)) || (fichier.contains(".docx", Qt::CaseInsensitive)) || (fichier.contains(".odt", Qt::CaseInsensitive)))
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::homePath() + "/Analyst/" + "/DataBase/" + fichier));
        }

        else if((fichier.contains(".jpg", Qt::CaseInsensitive)) || (fichier.contains(".png", Qt::CaseInsensitive)) || (fichier.contains(".mng", Qt::CaseInsensitive)) || (fichier.contains(".tiff", Qt::CaseInsensitive)) || (fichier.contains(".jpeg", Qt::CaseInsensitive)) || (fichier.contains(".gif", Qt::CaseInsensitive)) || (fichier.contains(".tga", Qt::CaseInsensitive))  || (fichier.contains(".bmp", Qt::CaseInsensitive)) || (fichier.contains(".openexr", Qt::CaseInsensitive)))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = QDir::homePath() + "/Analyst/" + "DataBase/";
            vraiNomFichier += fichier;

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                FenFichierImage *fenetreImage = new FenFichierImage(vraiNomFichier, this);
                fenetreImage->show();
                qApp->processEvents();
            }
        }

        else if(((fichier.contains(".mov", Qt::CaseInsensitive)) || (fichier.contains(".mpeg", Qt::CaseInsensitive)) || (fichier.contains(".ogm", Qt::CaseInsensitive)) || (fichier.contains(".avi", Qt::CaseInsensitive)) || (fichier.contains(".theora", Qt::CaseInsensitive)) || (fichier.contains(".flv", Qt::CaseInsensitive)) || (fichier.contains(".wmv", Qt::CaseInsensitive))))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = QDir::homePath() + "/Analyst/" + "DataBase/";
            vraiNomFichier += fichier;

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                FenFichierVideo *fenetreVideo = new FenFichierVideo(vraiNomFichier, this);
                fenetreVideo->show();
            }
        }

        else if(((fichier.contains(".ogg", Qt::CaseInsensitive)) || (fichier.contains(".flac", Qt::CaseInsensitive)) || (fichier.contains(".mp3", Qt::CaseInsensitive)) || (fichier.contains(".wav", Qt::CaseInsensitive)) || (fichier.contains(".wma", Qt::CaseInsensitive)) || (fichier.contains(".aac", Qt::CaseInsensitive)) || (fichier.contains(".spx", Qt::CaseInsensitive))))
        {
            QString vraiNomFichier;
            vraiNomFichier = "";
            vraiNomFichier = QDir::homePath() + "/Analyst/" + "DataBase/";
            vraiNomFichier += fichier;

            if(!QFile::exists(vraiNomFichier))
            {
                QMessageBox::critical(this,tr("Erreur"),tr("Le fichier n'existe pas"));
                return;
            }

            else
            {
                FenFichierMusique *fenetreMusique = new FenFichierMusique(vraiNomFichier, this);
                fenetreMusique->show();
            }
        }

        else if(!fichier.isEmpty())
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::homePath() + "/Analyst/" + "/DataBase/" + fichier));
        }
    }
}

void FenOuvertureFichier::ouvrir_appel()
{
    ouvrir();
}

void FenOuvertureFichier::creerFenetre(QString listeDesFichiers)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    phrase = new QLabel(tr("Nom des Fichiers à Ouvrir :"));
    nomFichier = new QTextEdit;
    boutonOuvrir = new QPushButton(tr("Ouvrir !"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(phrase);
    layout->addWidget(nomFichier);
    layout->addWidget(boutonOuvrir);

    setLayout(layout);

    setWindowTitle(tr("Analyst - Ouverture de Fichiers"));

    #if defined(Q_WS_WIN)
        setFixedSize(500,500);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(500,500);
    #endif

    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(boutonOuvrir, SIGNAL(clicked()), this, SLOT(ouvrir_appel()));
}

void FenOuvertureFichier::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        ouvrir();
    }
}

void FenOuvertureFichier::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
