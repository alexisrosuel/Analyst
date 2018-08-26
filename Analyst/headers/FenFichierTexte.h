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

#ifndef FENFICHIERTEXTE_H_INCLUDED
#define FENFICHIERTEXTE_H_INCLUDED

#include "FenFichierEditerTout.h"

#include <QtGui>

class FenFichierTexte;

class ProxyOpacity : public QObject
{
	Q_OBJECT

    private slots:
        void setOpacity(FenFichierTexte* fenetre)
        {
            emit opacityChanged(fenetre);
        }

    signals:
        void opacityChanged(FenFichierTexte*);
};

class FenFichierTexte : public QDialog
{
	Q_OBJECT

	public:
		FenFichierTexte(QString &texte, QString &fichier, QWidget *parent);

		QString texteVrai;
        QString nomFichier;
        QString partieTexte;

        int nombreResultatAfficher;

        QTextEdit *zoneTexte;

    private slots:
        void chercher();
        void creerFenetre(QString texte, QString fichier);

        void afficherToutEditer();
        void afficherEditerPartie();
        void afficherSuivantMot();
        void afficherPrecedentMot();
        void afficherZoomPlus();
        void afficherZoomMoins();

        void fonctionToutEditer();
        void fonctionEditerPartie();
        void fonctionSelection();
        void fonctionMotChercher();
        void fonctionPrecedentMot();
        void fonctionSuivantMot();
        void fonctionZoomPlus();
        void fonctionZoomMoins();

        void creerStatusBar();
        void creerActions();

        void closeEvent(QCloseEvent*);
        void keyPressEvent(QKeyEvent *event);
        void mousePressEvent(QMouseEvent *e);

        void threadChercher(QString texte, QTextEdit *zoneTexte);

        void mettreHtml();
        void mettrePlain();
        void mettreUpdateAffichage(int value);
        void fonctionChangerPolice();
        void fonctionCurseur();
        void fonctionVert();
        void fonctionRouge();
        void arreter();

        void setOpacity(FenFichierTexte* fenetre);


    signals:
        void signalHtml();
        void signalPlain();
        void updateAffichage(int value);
        void changerPolice();
        void signalCurseur();
        void mettreVert();
        void mettreRouge();

        void changerOpacite(FenFichierTexte* fenetre);



    protected:
        void enterEvent(QEvent *e);


    private:

        QPushButton *afficherRecherche;
        QLineEdit *mot;

        QToolBar *toolBar;
        QStatusBar *statut;
        QProgressBar *progression;

        QAction *editerTous;
        QAction *editerPartie;
        QAction *suivantMot;
        QAction *precedentMot;
        QAction *zoomPlus;
        QAction *zoomMoins;

        QVBoxLayout *layout;

        QProgressDialog* dialog;

        QGraphicsProxyWidget *proxy;

        static ProxyOpacity proxy_opacity;
};






#endif
