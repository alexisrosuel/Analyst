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

#ifndef FENFICHIERVISUALISATION_H_INCLUDED
#define FENFICHIERVISUALISATION_H_INCLUDED

#include <QtGui>
#include "FenInfoFichiers.h"
#include "FenInfoFichiersIndividuels.h"

class FenFichierVisualisation : public QDialog
{
	Q_OBJECT

    public:
        FenFichierVisualisation(int affichage, QWidget *parent);

        bool arreter_copie;

    private slots:
        void fonctionParent();
        void fonctionActualiser();
        void fonctionRenomer();
        void fonctionSupprimer();

        void afficherTextes();
        void afficherImages();
        void afficherVideos();
        void afficherMusiques();
        void afficherTout();

        void afficherInformation();
        void afficherInformationFichier();

        void fonctionNouveauFichier();


        void creerActions();
        void creerFenetre();
        void creerStatusBar();

        void afficherActualiser();
        void afficherMessageImages();
        void afficherMessageInformation();
        void afficherMessageInformationFichier();
        void afficherMessagesMusiques();
        void afficherMessagesTout();
        void afficherMessagesVideos();
        void afficherMessageTextes();
        void afficherParent();
        void afficherRenommer();
        void afficherSupprimer();
        void afficherNouveauFichier();
        void afficherMessageAjouterFichier();
        void ajouterFichier();

        void closeEvent(QCloseEvent*);
        //void keyPressEvent(QKeyEvent *event);

        void threadAjouter(QStringList fichiers);
        void arreter();
        void actualiser_chargement(int i);

    signals:
        void chargement(int i);

    private:
        QAction *repertoireParent;
        QAction *precedent;
        QAction *suivant;
        QAction *actualiser;
        QAction *renomer;
        QAction *supprimer;
        QAction *outilsTexte;
        QAction *outilsImage;
        QAction *outilsVideo;
        QAction *outilsMusique;
        QAction *outilsTout;
        QAction *outilsInformation;
        QAction *outilsInformationFichier;
        QAction *outilsNouveauFichier;
        QAction *ajouter_fichier;

        QListView *vue;

        QStringListModel *modele;
        QStandardItemModel *modele2;

        QDir *direction;

        QToolBar *toolBar;

        QStatusBar *statut;

        QListWidget *m_vue;

        QProgressDialog *dialog;

};

#endif // FENFICHIERVISUALISATION_H_INCLUDED
