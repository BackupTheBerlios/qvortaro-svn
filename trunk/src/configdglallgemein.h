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

#ifndef CONFIGDGLALLGEMEIN_H
#define CONFIGDGLALLGEMEIN_H

#include <QtGui>
#include "configdglvorlage.h"
#include "ui_configdglallgemein.h"

class ConfigDglAllgemein : public ConfigDglVorlage
{
  Q_OBJECT

  public:
    ConfigDglAllgemein(QWidget *parent = 0);
    ~ConfigDglAllgemein();
    void updateSettings();
    QStringList saveSettings();

  private slots:
    void on_pbPathToDbs_clicked();

  private:
    Ui::ConfigDglAllgemeinClass ui;
};

#endif // CONFIGDGLALLGEMEIN_H
