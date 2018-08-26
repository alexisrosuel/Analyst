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
#include "../headers/FenUpdate.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    #if defined(Q_WS_X11)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QTranslator translator;
    translator.load(":/langues/updater_en");
    app.installTranslator(&translator);

    app.setApplicationName("Analyst - Updater");

    FenUpdate fenetre;
    fenetre.show();

    return app.exec();
}
