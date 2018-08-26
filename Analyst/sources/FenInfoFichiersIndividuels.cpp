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

#include "../headers/FenInfoFichiersIndividuels.h"

FenInfoFichiersIndividuels::FenInfoFichiersIndividuels(QString &nomFichier, QWidget *parent) : QDialog(parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QFileInfo fichier("DataBase/" + nomFichier);

    QString typeFichier = fichier.completeSuffix();

    int taille = fichier.size();
    QString tailleFichier;

    if(taille >= 1000000000)
    {
        taille /= 1000000000;
        tailleFichier.setNum(taille);
        tailleFichier += " Go";
    }

    else if(taille >= 1000000)
    {
        taille /= 1000000;
        tailleFichier.setNum(taille);
        tailleFichier += " Mo";
    }

    else if(taille >= 1000)
    {
        taille /= 1000;
        tailleFichier.setNum(taille);
        tailleFichier += " Ko";
    }

    else if(taille < 1000)
    {
        tailleFichier.setNum(taille);
        tailleFichier += " Bytes";
    }

    QVariant date = fichier.created();
    QString dateFichier = date.toString();
    QString str = dateFichier.section('T', 0, 0);
    QString str2 = dateFichier.section('T', 1, 1);
    dateFichier = str + " at " + str2;

    QVariant derniereDate = fichier.lastModified();
    QString derniereDateFichier = derniereDate.toString();
    str = derniereDateFichier.section('T', 0, 0);
    str2 = derniereDateFichier.section('T', 1, 1);
    derniereDateFichier = str + " at " + str2;

    QVariant derniereOuverture = fichier.lastRead();
    QString derniereOuvertureFichier = derniereOuverture.toString();
    str = derniereOuvertureFichier.section('T', 0, 0);
    str2 = derniereOuvertureFichier.section('T', 1, 1);
    derniereOuvertureFichier = str + " at " + str2;

    QString groupeFichier = fichier.group();

    QString proprietaireFichier = fichier.owner();

    creerFenetre(nomFichier, typeFichier, tailleFichier, dateFichier, derniereDateFichier, derniereOuvertureFichier, groupeFichier, proprietaireFichier);
}

void FenInfoFichiersIndividuels::creerFenetre(QString nomFichier, QString typeFichier, QString tailleFichier, QString dateFichier, QString derniereDateFichier, QString derniereOuvertureFichier, QString groupeFichier, QString proprietaireFichier)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QLabel *nom = new QLabel("Name : " + nomFichier);
    QLabel *type = new QLabel("Type : " + typeFichier);
    QLabel *taille = new QLabel("Size : " + tailleFichier);
    QLabel *date = new QLabel("Date added to the database : " + dateFichier);
    QLabel *derniereDate = new QLabel("Date of last modification : " + derniereDateFichier);
    QLabel *derniereOuverture = new QLabel("Date of the last opening : " + derniereOuvertureFichier);
    QLabel *groupe = new QLabel("Belongs to the group : " + groupeFichier);
    QLabel *proprietaire = new QLabel("Belongs to : " + proprietaireFichier);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(nom);
    layout->addWidget(type);
    layout->addWidget(taille);
    layout->addWidget(date);
    layout->addWidget(derniereDate);
    layout->addWidget(derniereOuverture);

     #if defined (linux)
        layout->addWidget(groupe);
        layout->addWidget(proprietaire);
    #endif

    setLayout(layout);

    setWindowTitle(tr("Analyst - Propriétés de \"") + nomFichier + "\"");
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    #if defined(Q_WS_WIN)

    #endif

    #if defined(Q_WS_X11)
        setFixedSize(400,160);
    #endif
}

void FenInfoFichiersIndividuels::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        this->deleteLater();
    }
}

void FenInfoFichiersIndividuels::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
