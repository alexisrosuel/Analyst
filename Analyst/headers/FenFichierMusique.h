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

#ifndef FENFICHIERMUSIQUE_H_INCLUDED
#define FENFICHIERMUSIQUE_H_INCLUDED

#include <phonon>
#include <QtGui>
#include <QThread>

class FenFichierMusique : public QDialog
{
	Q_OBJECT

	public:
        FenFichierMusique(QString &vraiNomFichier, QWidget *parent);

    private slots:
        void tick(qint64 time);
        void arreter();

        void closeEvent(QCloseEvent*);

        void creerFenetre(QString vraiNomFichier);

        void placer_fenetres(int abscisse, int ordonnee);

    private:
        Phonon::SeekSlider *seekSlider;
        Phonon::MediaObject *mediaObject;
        Phonon::AudioOutput *audioOutput;
        Phonon::VolumeSlider *volumeSlider;

        QAction *playAction;
        QAction *pauseAction;
        QAction *stopAction;

        QLabel *timeLcd;

};

#endif // FENMUSIQUE_H_INCLUDED
