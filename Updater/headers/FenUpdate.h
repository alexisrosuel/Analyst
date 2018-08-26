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

#ifndef FENUPDATE_H_INCLUDED
#define FENUPDATE_H_INCLUDED

#include <QtNetwork>
#include <QtGui>

class FenUpdate : public QDialog
{
	Q_OBJECT

	public:
		FenUpdate();
		QString version_actuel;
		QString version_fichier;
		QString nouveau_md5;
		qint64 precedent;
		bool erreur;

	private slots:
        void verif_version();
        void telechargement_fichier_termine();
        void a_jour_ok();
        void telecharger_md5();
        void telechargement_md5_termine();
        void telecharger_nouveau();
        void telechargement_nouvelle_version_termine();
        void telechargement_nouvelle_version_analyst_termine();
        void operation_fichier();

        void progression_telechargement(qint64, qint64);
        void message_erreur(QNetworkReply::NetworkError);

    private:
        QLabel *label;
        QLabel *label_texte;
        QLabel *label_vitesse;
        QLabel *label_nombre;
        QProgressBar *bar;

};

#endif // FENUPDATE_H_INCLUDED
