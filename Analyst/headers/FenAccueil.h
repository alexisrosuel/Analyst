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

#ifndef FENACCUEIL_H_INCLUDED
#define FENACCUEIL_H_INCLUDED

#include "FenRecherche.h"
#include "FenRechercheEntier.h"
#include "FenInternet.h"
#include "FenFichierVisualisation.h"
#include "FenLicence.h"
#include "FenBug.h"
#include "Tuto.h"

#include <QtGui>
#include <QApplication>

class Bouton : public QPushButton
{
    Q_OBJECT

    public:
        Bouton()
        {
        }

    protected:
        void enterEvent(QEvent*);
        void leaveEvent(QEvent*);

     signals:
        void signalMessages();
        void cleanMessage();

};

class FenAccueil : public QWidget
{
    Q_OBJECT

    public:
        FenAccueil();

    private slots:
        void creerFenetre();

        void changerMessagesRecherche();
        void changerMessagesInternet();
        void changerMessagesGestion();

        void clean();

        void lancerRecherche();
        void lancerInternet();
        void lancerVisualisation();

        void fonctionPleinEcran();
        void fonctionPetitEcran();

        void fonctionLicence();

        void report_bug();
        void lancer_tuto();


        void keyPressEvent(QKeyEvent *event);



    private:
        QLabel *phrase;

        QPushButton *boutonPleinEcran;
        QPushButton *boutonPetitEcran;

        QPushButton *boutonLicence;
        QPushButton *boutonLicenceQt;
        QPushButton *boutonBug;
        QPushButton *boutonTuto;

        Bouton *boutonRecherche;
        Bouton *boutonInternet;
        Bouton *boutonGestion;
};

#endif // FENACCUEIL_H_INCLUDED
