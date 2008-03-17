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

#ifndef CONFIGDGL_H
#define CONFIGDGL_H

#include <QtGui>
#include "ui_configdgl.h"
#include "configdglallgemein.h"
#include "configdglfont.h"
#include "configdgllexika.h"
#include "configdglklipper.h"
#include "configdglsearch.h"
#include "configdglview.h"

class ConfigDgl : public QDialog
{
  Q_OBJECT

  public:
    ConfigDgl(QWidget *parent = 0);
    ~ConfigDgl();
    QStringList save();

  private slots:
    void slot_changeCaption(int);

  private:
    Ui::ConfigDglClass ui;
    ConfigDglAllgemein *myConfigDglAllgemein;
    ConfigDglFont *myConfigDglFont;
    ConfigDglLexika *myConfigDglLexika;
    ConfigDglKlipper *myConfigDglKlipper;
    ConfigDglSearch *myConfigDglSearch;
    ConfigDglView *myConfigDglView;
    void updateSettings();
};

#endif // CONFIGDGL_H
