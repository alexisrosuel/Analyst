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

#include "../headers/FenFichierMusique.h"

int nombreMusiquesOuverts = 0;
int decalageMusique = 0;
int second_decalage_musique = 0;

FenFichierMusique::FenFichierMusique(QString &vraiNomFichier, QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre(vraiNomFichier);

    int abscisse = 170*nombreMusiquesOuverts + 20*second_decalage_musique;
    int ordonnee = 120*decalageMusique + 20*second_decalage_musique;

    for(int i = 0; i < 170*nombreMusiquesOuverts + 20*second_decalage_musique && abscisse != 0; i += 0)
    {
        //emit placer(i, 120*decalageMusique + 20*second_decalage_musique);
        move(i, 120*decalageMusique + 20*second_decalage_musique);
        show();
        QEventLoop loop;
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i += 3;
    }

    if(nombreMusiquesOuverts == 0)
    {
         move(abscisse, ordonnee + 30);
    }

    else
    {
         move(abscisse, ordonnee + 30);
    }

    nombreMusiquesOuverts++;

    if(nombreMusiquesOuverts == 7)
    {
        nombreMusiquesOuverts = 0;
        decalageMusique++;
    }

    if(decalageMusique == 7)
    {
        decalageMusique = 0;
        nombreMusiquesOuverts = 0;
        second_decalage_musique++;
    }
}

void FenFichierMusique::arreter()
{
    mediaObject->stop();
}

void FenFichierMusique::tick(qint64 time)
{
     QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
     timeLcd->setText(displayTime.toString("mm:ss"));
}

void FenFichierMusique::closeEvent(QCloseEvent*)
{
    mediaObject->stop();

    this->deleteLater();
}

void FenFichierMusique::placer_fenetres(int abscisse, int ordonnee)
{
    move(abscisse, ordonnee);
    show(); qApp->processEvents();
}

void FenFichierMusique::creerFenetre(QString vraiNomFichier)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    mediaObject->setCurrentSource(vraiNomFichier);
    mediaObject->setTickInterval(1000);
    Phonon::createPath(mediaObject,audioOutput);
    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.75);
    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setMediaObject(mediaObject);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(arreter()));

    playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Lancer"), this);
    pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);

    connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()));
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));

    QToolBar *bar = new QToolBar;
    bar->addAction(playAction);
    bar->addAction(pauseAction);
    bar->addAction(stopAction);

    QLabel *volumeLabel = new QLabel;
    volumeLabel->setPixmap(QPixmap("images/volume.png"));

    timeLcd = new QLabel;

    QHBoxLayout *seekerLayout = new QHBoxLayout;
    seekerLayout->addWidget(seekSlider);
    seekerLayout->addWidget(timeLcd);

    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(bar);
    playbackLayout->addStretch();
    playbackLayout->addWidget(volumeLabel);
    playbackLayout->addWidget(volumeSlider);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);
    setLayout(mainLayout);

    QString nomMusique = vraiNomFichier.section('/', -1);
    setWindowTitle("Analyst - \"" + nomMusique + "\"");

    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    timeLcd->setText("00:00");
}




