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

#include <QtGui>
#include "../headers/FenAccueil.h"
#include "../headers/FenConsole.h"
#include "../headers/Tuto.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QSplashScreen splash;
    splash.show();

    QPixmap pixmap(":/icones/Icones/Analyst-0.png");
    splash.setMask(QRegion(pixmap.mask()));
    splash.setPixmap(pixmap);
    qApp->processEvents();

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    pixmap.load(":/icones/Icones/Analyst-25.png");
    splash.setMask(QRegion(pixmap.mask()));
    splash.setPixmap(pixmap);
    qApp->processEvents();

    QTranslator translator;
    translator.load(":/langues/analyst_en");
    app.installTranslator(&translator);

    pixmap.load(":/icones/Icones/Analyst-50.png");
    splash.setMask(QRegion(pixmap.mask()));
    splash.setPixmap(pixmap);
    qApp->processEvents();

    QDir *directory = new QDir();

    if(!directory->exists(QString(QDir::homePath() + "/Analyst/" + "DataBase")))
    {
        if((directory->mkpath(QString(QDir::homePath() + "/Analyst/" + "DataBase"))))
        {
            QMessageBox::information(NULL, "Information", "The folder containing the Database does not exist, has been created and registered under the name \"Database \" at " + QDir::homePath() + "/Analyst/");
        }
    }

    pixmap.load(":/icones/Icones/Analyst-75.png");
    splash.setMask(QRegion(pixmap.mask()));
    splash.setPixmap(pixmap);
    qApp->processEvents();

    app.setApplicationName("Analyst");

    pixmap.load(":/icones/Icones/Analyst-100.png");
    splash.setMask(QRegion(pixmap.mask()));
    splash.setPixmap(pixmap);
    qApp->processEvents();

    QSettings settings(QString(QDir::homePath() + "/Analyst/" + "analyst.ini"), QSettings::IniFormat);
    QString premier_lance = settings.value("premier").toString();

    FenAccueil fenetre;
    fenetre.show();

    FenConsole fenetreConsole;
    fenetreConsole.show();

    if(premier_lance.startsWith("1") && premier_lance.endsWith("1"))
    {
        settings.setValue("premier", 0);
        Tuto *fenetre_tuto = new Tuto(NULL);
        fenetre_tuto->show();
    }

    splash.finish(&fenetreConsole);

    return app.exec();
}
