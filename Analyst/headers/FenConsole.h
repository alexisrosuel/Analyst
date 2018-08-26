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

#ifndef FENCONSOLE_H_INCLUDED
#define FENCONSOLE_H_INCLUDED

#include <QtGui>
#include <QApplication>

#include "../headers/FenAffiner.h"
#include "../headers/FenFichierImage.h"
#include "../headers/FenFichierMusique.h"
#include "../headers/FenFichierTexte.h"
#include "../headers/FenFichierVideo.h"
#include "../headers/FenOuvertureFichier.h"
#include "../headers/FenResultat.h"
#include "../headers/FenInfoFichiers.h"
#include "../headers/FenInfoFichiersIndividuels.h"
#include "../headers/FenLicence.h"
#include "../headers/FenFichierEditerTout.h"
#include "../headers/FenFichierVisualisation.h"
#include "../headers/FenRecherche.h"
#include "../headers/FenInternet.h"
#include "../headers/FenRechercheEntier.h"
#include "../headers/FenInfoRecherche.h"

class FenConsole;

class Entre_console : public QTextEdit
{
    Q_OBJECT

    public:
        Entre_console()
        {
        }

   protected:
        void keyPressEvent(QKeyEvent *event);

    signals:
        void signal_analyser();
        void signal_retour();
        void signal_update_affichage(QChar car);
        void signal_bouger(QKeyEvent *event);
};

class FenConsole : public QWidget
{
    Q_OBJECT

    public:
        FenConsole();

    private slots:
        void creerFenetre();
        void analyser();
        void retour();
        void update_affichage(QChar car);
        void bouger(QKeyEvent *event);

        void closeEvent(QCloseEvent *event);

    private:
        Entre_console *commande;
        QTextCursor *cursor;

};


#endif // FENCONSOLE_H_INCLUDED
