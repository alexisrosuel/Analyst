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

#ifndef FENAFFICHER_H_INCLUDED
#define FENAFFICHER_H_INCLUDED

#include <QtGui>
#include <dirent.h>
#include "FenResultat.h"

class FenAffiner : public QDialog
{
	Q_OBJECT

	public:
		FenAffiner(QString resultat, QWidget *parent);

		QString listeFichiersVrai;
		QString resultat2;
		QString resultatAffiner2;

    private slots:
        void affiner();
        void recherche();
        void recherche_casse();
        void recherche_entier();
        void recherche_entier_casse();

        void creerFenetre();

        void closeEvent(QCloseEvent*);
        void keyPressEvent(QKeyEvent *event);

    private:
        QLabel *phrase;
        QLineEdit *mot;
        QPushButton *lancer;
        QCheckBox *casse;
        QCheckBox *entier;
};


#endif
