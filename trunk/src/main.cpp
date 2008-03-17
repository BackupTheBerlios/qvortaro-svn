/*************************************************************************
 * qVortaro - A dictionary lookup tool for Esperanto                     *
 * Copyright (C) 2004-2008  Lorenz Haas <qvortaro@lorenz-haas.de>        *
 *************************************************************************
 *                                                                       *
 * This program is free software: you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                       *
 *************************************************************************/

#include "qvortaro.h"

#include <QtGui>
#include <QtCore>
#include <QApplication>

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(qvortaro);

  
  QApplication a(argc, argv);

  QCoreApplication::setOrganizationName("qVortaro");
  QCoreApplication::setOrganizationDomain("qvortaro.berlios.de");
  QCoreApplication::setApplicationName("qVortaro");

  qvortaro w;
  w.show();
  a.connect(&a, SIGNAL(lastWindowClosed()), &w, SLOT(slot_quit()));
  return a.exec();
}
