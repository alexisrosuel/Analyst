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

#ifndef FENRECHERCHEENTIER_H_INCLUDED
#define FENRECHERCHEENTIER_H_INCLUDED

#include <QtGui>
#include <QApplication>
#include <phonon>
#include <dirent.h>
#include "FenInfoRecherche.h"
#include "FenResultat.h"


class FenRechercheEntier : public QDialog
{
    Q_OBJECT

    public:
        FenRechercheEntier(QWidget *parent);
        QString nomFichier;
        QString vraiNomFichier;
        QString resultat2;
		QString resultatAffiner2;
		QString listeFichiersVrai;
        int nombreTab;
        QString resultat;


    private slots:
        void creerFenetre();
        void creerStatusBar();
        void creerActions();

        void messageOuvrirTousTextes();
        void fonctionOuvrirTousTextes();
        void messageOuvrirToutesImages();
        void fonctionOuvrirToutesImages();
        void messageOuvrirToutesMusiques();
        void fonctionOuvrirToutesMusiques();
        void messageOuvrirToutesVideos();
        void fonctionOuvrirToutesVideos();

        void messageAfficherTousTextes();
        void afficherTextes();
        void messageAfficherToutesImages();
        void afficherImages();
        void messageAfficherToutesMusiques();
        void afficherMusiques();
        void messageAfficherToutesVideos();
        void afficherVideos();

        void afficherToutEditer();
        void fonctionToutEditer();
        void afficherEditerPartie();
        void fonctionEditerPartie();

        void afficherInformations();
        void fonctionInformations();

        void fonctionRechercher();
        //void fonctionAfficherTextes();

        void rechercheFenetre();
        void rechercheCasseEntierFenetre();
        void rechercheCasseFenetre();
        void rechercheEntierFenetre();

        void affiner();

        void fonctionAfficherTextes(const QModelIndex & index);
        void fonctionAfficherTextesSansAfficher(const QModelIndex & index);
        void fonctionFermerTab( int numeroWidget );

        void mouseDoubleClickEvent(QMouseEvent*);
        void mousePressEvent (QMouseEvent*);
        void closeEvent(QCloseEvent*);

        void tick(qint64 time);
        //void closeEvent(QCloseEvent*);

        void fonctionAjouterFichier(QString nomFichier);

    private:
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

        QAction *editerTous;
        QAction *editerPartie;

        QAction *informations;

        QStringListModel *modele;
        QStringList listeFichierOuverts;

        QToolBar *toolBar;
        //QStatusBar *statut;

        Phonon::VideoPlayer *videoPlayer;

        Phonon::SeekSlider *seekSlider;
        Phonon::MediaObject *mediaObject;
        Phonon::AudioOutput *audioOutput;
        Phonon::VolumeSlider *volumeSlider;

        QAction *playAction;
        QAction *pauseAction;
        QAction *stopAction;

        QLabel *timeLcd;

        /******/

        QListView *listView;
        QListView *listView_2;
        QWidget *verticalLayoutWidget_3;
        QVBoxLayout *verticalLayout_3;
        QVBoxLayout *verticalLayout_2;
        QVBoxLayout *verticalLayout;
        QLabel *label;
        QLineEdit *lineEdit;
        QCheckBox *checkBox;
        QCheckBox *checkBox_2;
        QPushButton *pushButton;
        QVBoxLayout *verticalLayout_5;
        QVBoxLayout *verticalLayout_4;
        QSpacerItem *verticalSpacer;
        QLabel *label_3;
        QSpacerItem *verticalSpacer_17;
        QLabel *label_2;
        QLineEdit *lineEdit_2;
        QCheckBox *checkBox_3;
        QCheckBox *checkBox_4;
        QPushButton *pushButton_2;
        QTabWidget *tabWidget;
        QWidget *tab;
        QTextEdit *textEdit;
        QWidget *tab_2;
        QStatusBar *statut;
        QVBoxLayout *layoutStatus;

};

#endif // FENRECHERCHEENTIER_H_INCLUDED
