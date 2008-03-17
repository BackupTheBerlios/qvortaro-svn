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

#include "configdglfont.h"
#include "config.h"

ConfigDglFont::ConfigDglFont(QWidget *parent) :
  ConfigDglVorlage(parent)
{
  ui.setupUi(this);
  ui.pbLemmata->setIcon(QIcon(":tool"));
  ui.pbTranslation->setIcon(QIcon(":tool"));
  ui.pbSearch->setIcon(QIcon(":tool"));
}

ConfigDglFont::~ConfigDglFont()
{
}

void ConfigDglFont::updateSettings()
{
  ui.prLemmata->setFont(Config::instance()->fontLemmata());
  ui.prTranslation->setFont(Config::instance()->fontTranslation());
  ui.prSearch->setFont(Config::instance()->fontSearch());
  updateFontLabel();
}

QStringList ConfigDglFont::saveSettings()
{
  QStringList ret;
  if (Config::instance()->setFontLemmata(ui.prLemmata->font()))
    ret.append("font");
  if (Config::instance()->setFontTranslation(ui.prTranslation->font()))
    ret.append("font");
  if (Config::instance()->setFontSearch(ui.prSearch->font()))
    ret.append("font");
  return ret;
}

void ConfigDglFont::on_pbLemmata_clicked()
{
  bool ok;
  QFont f = QFontDialog::getFont( &ok, ui.prLemmata->font(), this);
  if (ok)
  {
    ui.prLemmata->setFont(f);
    updateFontLabel();
  }
}

void ConfigDglFont::on_pbTranslation_clicked()
{
  bool ok;
  QFont f = QFontDialog::getFont( &ok, ui.prTranslation->font(), this);
  if (ok)
  {
    ui.prTranslation->setFont(f);
    updateFontLabel();
  }
}

void ConfigDglFont::on_pbSearch_clicked()
{
  bool ok;
  QFont f = QFontDialog::getFont( &ok, ui.prSearch->font(), this);
  if (ok)
  {
    ui.prSearch->setFont(f);
    updateFontLabel();
  }
}

void ConfigDglFont::updateFontLabel()
{
  ui.prLemmata->setText(ui.prLemmata->font().family()+", "+QString::number(ui.prLemmata->font().pointSize()));
  ui.prTranslation->setText(ui.prTranslation->font().family()+", "+QString::number(ui.prTranslation->font().pointSize()));
  ui.prSearch->setText(ui.prSearch->font().family()+", "+QString::number(ui.prSearch->font().pointSize()));
}

