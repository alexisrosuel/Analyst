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

#ifndef FENBUG_H_INCLUDED
#define FENBUG_H_INCLUDED

#include <QtGui>
#include <QApplication>
#include <QtNetwork>

class FenBug : public QDialog
{
    Q_OBJECT

    public:
        FenBug(QWidget *parent);

    private slots:
        void creerFenetre();

        void envoi();
        void fin();
        void messageErreur(QNetworkReply::NetworkError);
        void progressionEnvoi(qint64, qint64);


    private:
        QLineEdit *objet;
        QLabel *label_objet;

        QTextEdit *description;
        QLabel *label_description;

        QPushButton *envoyer;
        QPushButton *annuler;

        QProgressBar *progression;

};


#endif // FENBUG_H_INCLUDED
