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

#ifndef FENINFOFICHIERS_H_INCLUDED
#define FENINFOFICHIERS_H_INCLUDED

#include <QtGui>

class FenInfoFichiers : public QDialog
{
	Q_OBJECT

    public:
        FenInfoFichiers(QWidget *parent);

    private slots:
        void creerTaille();
        void creerNombre();

        void creerFenetre();

        void closeEvent(QCloseEvent*);
        void keyPressEvent(QKeyEvent *event);

    private:
        QDir direction;

        QLabel *image;

        QVBoxLayout *layoutOctet;
        QVBoxLayout *layoutTaille;

};

#endif // FENINFOFICHIERS_H_INCLUDED
