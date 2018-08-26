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

#include "../headers/FenFichierImage.h"

int nombreImagesOuverts = 0;
int decalageImage = 0;
int second_decalage_image = 0;

FenFichierImage::FenFichierImage(QString &vraiNomFichier, QWidget *parent = 0) : QDialog (parent)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    int abscisse = 170*nombreImagesOuverts + 20*second_decalage_image;
    int ordonnee = 170*decalageImage + 20*second_decalage_image;

    creerFenetre(vraiNomFichier);

    for(int i = 0; i < abscisse; i += 0)
    {
        move(i, ordonnee);
        show();
        QEventLoop loop;
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i += 3;

    }

    if(nombreImagesOuverts == 0)
    {
        move(abscisse, ordonnee);
    }

    else
    {
        move(abscisse, ordonnee+30);
    }

    nombreImagesOuverts++;
    if(nombreImagesOuverts == 7)
    {
        nombreImagesOuverts = 0;
        decalageImage++;
    }

    if(decalageImage == 4)
    {
        decalageImage = 0;
        nombreImagesOuverts = 0;
        second_decalage_image++;
    }

    if(second_decalage_image == 4)
    {
        decalageImage = 0;
        nombreImagesOuverts = 0;
        second_decalage_image = 0;
    }
}

void FenFichierImage::creerFenetre(QString vraiNomFichier)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    temp = false;

    label = new QLabel(this);
    QPixmap pixmap(vraiNomFichier);

    if(pixmap.isNull())
    {
        QFile fichier(vraiNomFichier);
        fichier.remove();
        fichier.deleteLater();
        this->deleteLater();
        nombreImagesOuverts--;
    }

    label->setPixmap(pixmap);
    label->resize(pixmap.size());
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);

    QString nomImage = vraiNomFichier.section('/', -1);
    setWindowTitle("Analyst - \"" + nomImage + "\"");

    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
    nomImageFonction = vraiNomFichier;

    temp = true;
}

void FenFichierImage::resizeEvent(QResizeEvent *event)
{
    QPixmap pix(nomImageFonction);
    label->setPixmap(pix.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void FenFichierImage::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        this->deleteLater();
    }
}

void FenFichierImage::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
