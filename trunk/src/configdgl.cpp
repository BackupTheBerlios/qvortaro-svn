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

#include <QtGui>
#include "configdgl.h"
#include "configdglvorlage.h"

ConfigDgl::ConfigDgl(QWidget *parent) :
  QDialog(parent)
{
  ui.setupUi(this);
  ui.frame->setStyleSheet("background-image: url(\":dlgTopVortaroBG\"); background-repeat: repeat-x; background-position: bottom; background-color: #ffffff;");
  if (ui.buttonBox->button(QDialogButtonBox::Ok))
    ui.buttonBox->button(QDialogButtonBox::Ok)->setIcon(QIcon(":button_ok"));
  if (ui.buttonBox->button(QDialogButtonBox::Cancel))
    ui.buttonBox->button(QDialogButtonBox::Cancel)->setIcon(QIcon(":button_cancel"));

  QListWidgetItem *newItem = new QListWidgetItem(QIcon(":cAllgemein"), trUtf8("Allgemein"));
  ui.list->insertItem(0, newItem);
  myConfigDglAllgemein = new ConfigDglAllgemein(this);
  myConfigDglAllgemein->updateSettings();
  ui.sw->insertWidget(0, myConfigDglAllgemein);

  newItem = new QListWidgetItem(QIcon(":cFont"), trUtf8("Schrift"));
  ui.list->insertItem(1, newItem);
  myConfigDglFont = new ConfigDglFont(this);
  myConfigDglFont->updateSettings();
  ui.sw->insertWidget(1, myConfigDglFont);

  newItem = new QListWidgetItem(QIcon(":cBook"), trUtf8("Wörterbücher"));
  ui.list->insertItem(2, newItem);
  myConfigDglLexika = new ConfigDglLexika(this);
  myConfigDglLexika->updateSettings();
  ui.sw->insertWidget(2, myConfigDglLexika);

  newItem = new QListWidgetItem(QIcon(":cFind"), trUtf8("Suche"));
  ui.list->insertItem(3, newItem);
  myConfigDglSearch = new ConfigDglSearch(this);
  myConfigDglSearch->updateSettings();
  ui.sw->insertWidget(3, myConfigDglSearch);

  newItem = new QListWidgetItem(QIcon(":cLayout"), trUtf8("Ansicht"));
  ui.list->insertItem(4, newItem);
  myConfigDglView= new ConfigDglView(this);
  myConfigDglView->updateSettings();
  ui.sw->insertWidget(4, myConfigDglView);

  newItem = new QListWidgetItem(QIcon(":cKlipper"), trUtf8("Zwischenspeicher-Überwachung"));
  ui.list->insertItem(5, newItem);
  myConfigDglKlipper = new ConfigDglKlipper(this);
  myConfigDglKlipper->updateSettings();
  ui.sw->insertWidget(5, myConfigDglKlipper);

  QObject::connect(ui.list, SIGNAL(currentRowChanged(int)), this, SLOT(slot_changeCaption(int)));
  ui.list->setCurrentRow(0);
}

ConfigDgl::~ConfigDgl()
{
}

QStringList ConfigDgl::save()
{
  QStringList ret;
  ConfigDglVorlage *wdg;
  for (int i = 0; i < ui.sw->count(); ++i)
  {
    wdg = qobject_cast<ConfigDglVorlage*>(ui.sw->widget(i));
    if (wdg)
      ret += wdg->saveSettings();
  }
  return ret;
}

void ConfigDgl::updateSettings()
{
  ConfigDglVorlage *wdg;
  for (int i = 0; i < ui.sw->count(); ++i)
  {
    wdg = qobject_cast<ConfigDglVorlage*>(ui.sw->widget(i));
    if (wdg)
      wdg->updateSettings();
  }
}

void ConfigDgl::slot_changeCaption(int _page)
{
  if (ui.list->item(_page))
    ui.caption->setText(ui.list->item(_page)->text());
}
