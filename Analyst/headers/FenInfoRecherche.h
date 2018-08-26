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

#ifndef FENINFORECHERCHE_H_INCLUDED
#define FENINFORECHERCHE_H_INCLUDED

#include "FenAffiner.h"
#include "FenOuvertureFichier.h"
#include "FenFichierImage.h"
#include <QtGui>

class FenInfoRecherche : public QDialog
{
	Q_OBJECT

	public:
        FenInfoRecherche(QString &resultat, QString &resultatAffiner, QWidget *parent);

        QString resultatAffinerVrai;

    private slots:
        void affiner();
        void ouvrir();   // A RETIRER AUSSI DANS LE .cpp
        void afficherTextes();
        void afficherImages();
        void afficherVideos();
        void afficherMusiques();

        void creerActions(QString resultatAffiner);
        void creerStatut();
        void creerFenetre(QString resultat);

        void messageAffiner();
        void messageOuvrirFichier();
        void messageOuvrirTousTextes();
        void messageOuvrirToutesImages();
        void messageOuvrirToutesMusiques();
        void messageOuvrirToutesVideos();
        void messageAfficherTousTextes();
        void messageAfficherToutesImages();
        void messageAfficherToutesMusiques();
        void messageAfficherToutesVideos();

        void fonctionOuvrirToutesVideos();
        void fonctionOuvrirTousTextes();
        void fonctionOuvrirToutesImages();
        void fonctionOuvrirToutesMusiques();

        void closeEvent(QCloseEvent*);

    private:
        QTextEdit *fenetreResultat;
        QPushButton *boutonAffiner;
        QPushButton *boutonOuvrir;

        QAction *outilsAffiner;
        QAction *ouvrirFichier;
        QAction *outilsTexte;
        QAction *outilsImage;
        QAction *outilsVideo;
        QAction *outilsMusique;

        QAction *ouvrirTousTextes;
        QAction *ouvrirToutesImages;
        QAction *ouvrirToutesMusiques;
        QAction *ouvrirToutesVideos;

        QToolBar *toolBar;
        QStatusBar *barreEtat;

        QHBoxLayout *layoutBouton;
        QVBoxLayout *layout;
};

#endif // FENINFORECHERCHE_H_INCLUDED
