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

#ifndef FENRECHERCHE_H_INCLUDED
#define FENRECHERCHE_H_INCLUDED

#include <QtGui>
#include <dirent.h>

#include "FenResultat.h"

class FenRecherche : public QDialog
{
    Q_OBJECT

    public:
        FenRecherche(QWidget *parent);

        QString nomFichier;
        QString vraiNomFichier;

        QString resultatAffiner;

        int numeroImage;

        QString recherche(QString motRecherche);
        QString rechercheCasse(QString motRecherche);
        QString rechercheEntier(QString motRecherche);
        QString rechercheCasseEntier(QString motRecherche);

    private slots:
        void rechercher();
        void creerFenetre();

        void closeEvent(QCloseEvent*);
        void keyPressEvent(QKeyEvent *event);

    private:
        QLabel *phrase;
        QLineEdit *mot;
        QPushButton *lancer;
        QCheckBox *casse;
        QCheckBox *entier;

        QProgressDialog *dialog;

};

#endif // FENRECHERCHE_H_INCLUDED
