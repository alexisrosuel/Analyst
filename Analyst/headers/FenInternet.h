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

#ifndef FENINTERNET_H_INCLUDED
#define FENINTERNET_H_INCLUDED

#include <QtGui>
#include <QtNetwork>

#include "FenFichierTexte.h"
#include "FenFichierImage.h"

class FenInternet : public QDialog
{
    Q_OBJECT

    public:
        FenInternet(bool textes, bool images, bool tout_texts, bool toute_images, bool console, bool display, QString mot_recherche, QWidget *parent);

        QString nomFichier;
        QString vraiNomFichier;
        QString nomFichier_additionel;
        QString vraiNomFichier_additionel;
        QString vraiNomFichier_image;

        QString contenuFichier;
        QString contenuFichier_additionel;

        QString vraiNomFichier_image_additionel;

        QStringList list_document_additionnels;

        int numeroImage;
        int numeroImageSuplementaire;

        bool erreur;
        bool termine;
        bool ok;

        bool textes_vrai;
        bool images_vrai;
        bool tout_texts_vrai;
        bool toute_images_vrai;
        bool console_vrai;
        bool display_vrai;

        QString mot_recherche_vrai;

        void rechercheInternet();

    private slots:
        void lancer_recherche_internet();
        void telechargementTermine();
        void telechargementImageTermine();
        void messageErreur(QNetworkReply::NetworkError);
        void progressionTelechargement(qint64 bytesReceived, qint64 bytesTotal);
        void messageErreur_texte(QNetworkReply::NetworkError);

        void telechargementTermine_additionnel();

        void enregistrer_texte();
        void rechercher_images();
        void rechercher_images_suplementaires(QString nomFichier_image_additionel);
        void rechercher_texte_suplementaires();
        void telechargementImageSuplementaireTermine();
        void arreter();

        void creerFenetre();

        void closeEvent(QCloseEvent*);
        void keyPressEvent(QKeyEvent *event);

    private:
        QLabel *phraseInternet;
        QLineEdit *motInternet;
        QPushButton *boutonInternet;
        QCheckBox *texteSeulement;
        QCheckBox *imagesSeulement;

        QProgressDialog *dialog;

        QCheckBox *texte_suplementaires;
        QCheckBox *images_suplementaires;
        QCheckBox *afficher_texte_suplementaires;
        QCheckBox *afficher_images_suplementaires;
        QGroupBox *group_suplementaire;

};

#endif // FENINTERNET_H_INCLUDED
