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

#include "configdglallgemein.h"
#include "config.h"

ConfigDglAllgemein::ConfigDglAllgemein(QWidget *parent) :
  ConfigDglVorlage(parent)
{
  ui.setupUi(this);
  ui.pbPathToDbs->setIcon(QIcon(":pbFolder"));
}

ConfigDglAllgemein::~ConfigDglAllgemein()
{
}

void ConfigDglAllgemein::updateSettings()
{
  ui.restoreOnStartup->setChecked(Config::instance()->restoreOnStartup());
  ui.pathToDbs->setText(Config::instance()->pathToDbs());
}

QStringList ConfigDglAllgemein::saveSettings()
{
  QStringList ret;
  if (Config::instance()->setRestoreOnStartup(ui.restoreOnStartup->isChecked()))
    ret.append("restoreOnStartup");
  if (Config::instance()->setPathToDbs(ui.pathToDbs->text()))
    ret.append("pathToDbs");
  return ret;
}

void ConfigDglAllgemein::on_pbPathToDbs_clicked()
{
  QString dir = QFileDialog::getExistingDirectory(this, trUtf8("Wählen Sie ein Verzeichnis"), ui.pathToDbs->text(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty())
    ui.pathToDbs->setText(dir);
}
