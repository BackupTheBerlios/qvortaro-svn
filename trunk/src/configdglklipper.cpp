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

#include "configdglklipper.h"
#include "config.h"

ConfigDglKlipper::ConfigDglKlipper(QWidget *parent) :
  ConfigDglVorlage(parent)
{
  ui.setupUi(this);
}

ConfigDglKlipper::~ConfigDglKlipper()
{
}

void ConfigDglKlipper::updateSettings()
{
  ui.cbUse->setChecked(Config::instance()->cbUse());
  ui.cbTime->setValue(Config::instance()->cbTime());
  ui.cbMode->setCurrentIndex(Config::instance()->cbMode());
}

QStringList ConfigDglKlipper::saveSettings()
{
  QStringList ret;
  Config::instance()->setCbMode(ui.cbMode->currentIndex());
  Config::instance()->setCbTime(ui.cbTime->value());
  if (Config::instance()->setCbUse(ui.cbUse->isChecked()))
    ret.append("klipper");
  return ret;
}
