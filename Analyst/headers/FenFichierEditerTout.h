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

#ifndef FENFICHIEREDITERTOUT_H
#define FENFICHIEREDITERTOUT_H

#include <QtGui>

class FenFichierEditerTout : public QDialog
{
        Q_OBJECT

        public:
            FenFichierEditerTout(QString nomFichier, QString texte, QString resteTexte, int position, bool partie, QWidget *parent);

            int position_fichier;
            QString contenu_fichier_entier;
            QString texte_base;
            bool est_partie;

        private slots:
            void creerFenetre(QString nomFichier, QString texte);
            void creerActions();
            void creerStatusBar();

            void afficherNouveau();
            void afficherOuvrir();
            void afficherEnregistrer();
            void afficherEnregistrerSous();
            void afficherAnnuler();
            void afficherRetablir();
            void afficherModeOnglet();
            void afficherModeTab();
            void afficherVueTile();
            void afficherVueCascade();
            void afficherFermerToutesLesFenetres();

            void fonctionNouveau();
            void fonctionOuvrir();
            void fonctionEnregistrer();
            void fonctionEnregistrerSous();
            void fonctionAnnuler();
            void fonctionRetablir();
            void fonctionModeOnglet();
            void fonctionModeTab();
            void fonctionUndo(bool available);
            void fonctionRedo(bool available);
            void fonctionUpdateAffichage();
            void fonctionVueTile();
            void fonctionVueCascade();
            void fonctionFermerToutesLesFenetres();

            void closeEvent(QCloseEvent*);


        private:
            QToolBar *toolBar;
            QStatusBar *statut;

            QMdiArea *zoneCentrale;
            QMdiSubWindow *sousFenetre;

            QTextEdit *zoneTexte;

            QAction *nouveau;
            QAction *ouvrir;
            QAction *annuler;
            QAction *enregistrer;
            QAction *enregistrerSous;
            QAction *retablir;
            QAction *modeOnglet;
            QAction *modeTab;
            QAction *vueTile;
            QAction *vueCascade;
            QAction *fermerToutesLesFenetres;

};

#endif // FENFICHIEREDITERTOUT_H
