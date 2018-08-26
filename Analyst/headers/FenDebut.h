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

#ifndef FENDEBUT_H_INCLUDED
#define FENDEBUT_H_INCLUDED

#include "FenResultat.h"
#include "FenFichierVisualisation.h"
#include "FenLicence.h"

#include <QtGui>
#include <QtNetwork>
#include <dirent.h>

class FenDebut : public QWidget
{
    Q_OBJECT


    public:
        FenDebut();

        QString nomFichier;
        QString vraiNomFichier;

        int numeroImage;

    private slots:
        void rechercher();
        void rechercheInternet();
        void telechargementTermine();
        void telechargementImageTermine();
        void fonctionVisualiser();

        //void slotActivationSystemTray(QSystemTrayIcon::ActivationReason reason);

        //void closeEvent(QCloseEvent*);

        void messageErreur(QNetworkReply::NetworkError);

        void afficherLicence();

        void creerFenetre();

        void closeEvent(QCloseEvent*);


    private:
        QLabel *phrase;
        QLineEdit *mot;
        QPushButton *lancer;
        QCheckBox *casse;
        QCheckBox *entier;
        QLabel *labelTrait;
        QLabel *phraseInternet;
        QLineEdit *motInternet;
        QPushButton *boutonInternet;
        QCheckBox *texteSeulement;
        QCheckBox *imagesSeulement;

        QPushButton *visualiser;
        QLabel *phraseVisualiser;

        QGroupBox *groupBox;

        QLabel *phrasePresentation;
        QLabel *phraseEntrer;
        QLabel *phraseInfo;

        QSystemTrayIcon *sticon;




};

#endif
