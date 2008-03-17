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

#include "configdglsearch.h"
#include "config.h"

ConfigDglSearch::ConfigDglSearch(QWidget *parent) :
  ConfigDglVorlage(parent)
{
  ui.setupUi(this);
}

ConfigDglSearch::~ConfigDglSearch()
{
}

void ConfigDglSearch::updateSettings()
{
  ui.punctation->setChecked(Config::instance()->checkForPunctation());
  ui.eoending->setChecked(Config::instance()->checkForEoEnding());
  ui.cbUseWildcards->setChecked(Config::instance()->useWildcards());
}

QStringList ConfigDglSearch::saveSettings()
{
  QStringList ret;
  if (Config::instance()->setCheckForPunctation(ui.punctation->isChecked()))
    ret.append("punctation");
  if (Config::instance()->setCheckForEoEnding(ui.eoending->isChecked()))
    ret.append("eoending");
  if (Config::instance()->setUseWildcards(ui.cbUseWildcards->isChecked()))
    ret.append("useWildcards");
  return ret;
}
