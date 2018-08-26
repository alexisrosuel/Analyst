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

#include "../headers/FenFichierVideo.h"

int nombreVideosOuverts = 0;
int decalageVideo = 0;

FenFichierVideo::FenFichierVideo(QString &vraiNomFichier, QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre(vraiNomFichier);

    nombreVideosOuverts++;

    int abscisse = 20*nombreVideosOuverts + 300*decalageVideo;
    int ordonnee = 20*nombreVideosOuverts;


    for(int i = 0; i < 20*nombreVideosOuverts + 300*decalageVideo; i += 0)
    {
        move(i, 20*nombreVideosOuverts);
        show();
        QEventLoop loop;
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i += 3;

    }

    if(nombreVideosOuverts == 0)
    {
         move(abscisse, ordonnee);
    }

    else
    {
         move(abscisse, ordonnee + 30);
    }

    if(nombreVideosOuverts == 10)
    {
        nombreVideosOuverts = 0;
        decalageVideo++;
    }
}

void FenFichierVideo::tick(qint64 time)
{
     QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
     timeLcd->setText(displayTime.toString("mm:ss"));
}


void FenFichierVideo::enterEvent(QEvent*)
{
    _seekSlider->show();
    timeLcd->show();
    volumeLabel->show();
    _volumeSlider->show();

    seekerLayout = new QHBoxLayout;
    seekerLayout->addWidget(_seekSlider);
    seekerLayout->addWidget(timeLcd);
    seekerLayout->addWidget(volumeLabel);
    seekerLayout->addWidget(_volumeSlider);

    layout->addLayout(seekerLayout);
}

void FenFichierVideo::leaveEvent(QEvent*)
{
    seekerLayout->deleteLater();
    _seekSlider->hide();
    timeLcd->hide();
    volumeLabel->hide();
    _volumeSlider->hide();
}

void FenFichierVideo::mousePressEvent (QMouseEvent*)
{
    if(!is_playing)
    {
        _mediaObject->play();
        is_playing = true;
    }

    else if(is_playing)
    {
        _mediaObject->pause();
        is_playing = false;
    }

    else
    {
        _mediaObject->play();
        is_playing = true;
    }
}

void FenFichierVideo::closeEvent(QCloseEvent*)
{
    _mediaObject->stop();
    is_playing = false;

    this->deleteLater();
}

void FenFichierVideo::mouseDoubleClickEvent(QMouseEvent*)
{
    _mediaObject->stop();
    _mediaObject->play();
    _mediaObject->pause();

    is_playing = false;
}

void FenFichierVideo::creerFenetre(QString vraiNomFichier)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    _mediaObject = new Phonon::MediaObject();
    _mediaObject->setCurrentSource(vraiNomFichier);
    _mediaObject->play();
    _mediaObject->pause();

    is_playing = false;

    _videoWidget = new Phonon::VideoWidget();
    _videoWidget->setBaseSize(height()-height()*0.9, width());

    _audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory);
    _audioOutput->setVolume(0.75);

    _seekSlider = new Phonon::SeekSlider();
    _seekSlider->setMediaObject(_mediaObject);

    _volumeSlider = new Phonon::VolumeSlider(_audioOutput);

    Phonon::createPath(_mediaObject, _videoWidget);
    Phonon::createPath(_mediaObject, _audioOutput);

    connect(_mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

    volumeLabel = new QLabel;
    volumeLabel->setPixmap(QPixmap("images/volume.png"));

    timeLcd = new QLabel;

    layout = new QVBoxLayout;
    layout->addWidget(_videoWidget);
    setLayout(layout);

    QString nomVideo = vraiNomFichier.section('/', -1);
    setWindowTitle("Analyst - \"" + nomVideo + "\"");

    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
}

void FenFichierVideo::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        showFullScreen();
    }
}
