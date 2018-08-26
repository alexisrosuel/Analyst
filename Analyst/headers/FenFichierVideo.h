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

#ifndef FENFICHIERVIDEO_H_INCLUDED
#define FENFICHIERVIDEO_H_INCLUDED

#include <phonon>
#include <QtGui>

class FenFichierVideo : public QDialog
{
	Q_OBJECT

	public:
        FenFichierVideo(QString &vraiNomFichier, QWidget *parent);

        bool is_playing;

    private slots:
        void mouseDoubleClickEvent(QMouseEvent*);
        void mousePressEvent (QMouseEvent*);
        void closeEvent(QCloseEvent*);
        void keyPressEvent(QKeyEvent *event);

        void enterEvent(QEvent*);
        void leaveEvent(QEvent*);

        void creerFenetre(QString vraiNomFichier);

        void tick(qint64 time);

    private:
        QVBoxLayout *layout;
        QHBoxLayout *seekerLayout;

        Phonon::MediaObject *_mediaObject;
        Phonon::VideoWidget *_videoWidget;
        Phonon::AudioOutput *_audioOutput;
        Phonon::SeekSlider *_seekSlider;
        Phonon::VolumeSlider *_volumeSlider;

        QLabel *timeLcd;
        QLabel *volumeLabel;
};



#endif // FENVIDEO_H_INCLUDED
