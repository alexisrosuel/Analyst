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

#ifndef TUTO_H_INCLUDED
#define TUTO_H_INCLUDED

#include <QtGui>
#include <QApplication>

class Tuto : public QDialog
{
    Q_OBJECT

    public:
        Tuto(QWidget *parent);

        int numero;

    private slots:
        void creerFenetre();

        void fct_suivant();
        void fct_precedent();

        void tuto_accueil();
        void tuto_debut();
        void tuto_recherche_bdd();
        void tuto_resultat();
        void tuto_texte();
        void tuto_edition();
        void tuto_video();
        void tuto_internet();
        void tuto_database();
        void tuto_console();
        void tuto_console_recherche();
        void tuto_console_internet();
        void tuto_console_ouverture();
        void tuto_console_autres();
        void tuto_fin();

    private:
        QPushButton *suivant;
        QPushButton *precedent;

        QLabel *presentation;
        QLabel *image;
        QLabel *trait;
        QLabel *titre;

        QSpacerItem *item;

};

#endif // TUTO_H_INCLUDED
