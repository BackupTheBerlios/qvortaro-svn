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

#ifndef CONFIGDGLKLIPPER_H
#define CONFIGDGLKLIPPER_H

#include <QtGui>
#include "configdglvorlage.h"
#include "ui_configdglklipper.h"

class ConfigDglKlipper : public ConfigDglVorlage
{
  Q_OBJECT

  public:
    ConfigDglKlipper(QWidget *parent = 0);
    ~ConfigDglKlipper();
    void updateSettings();
    QStringList saveSettings();

  private:
    Ui::ConfigDglKlipperClass ui;
};

#endif // CONFIGDGLKLIPPER_H
