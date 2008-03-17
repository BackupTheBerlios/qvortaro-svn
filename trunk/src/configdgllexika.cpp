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

#include "configdgllexika.h"
#include "config.h"

ConfigDglLexika::ConfigDglLexika(QWidget *parent) :
  ConfigDglVorlage(parent)
{
  ui.setupUi(this);

  ui.language1->clear();
  QMap<QString, QString> tmp = Config::instance()->languages();
  QMapIterator<QString, QString> i(tmp);
  int j = 0;
  while (i.hasNext())
  {
    i.next();
    zuordnung.insert(i.value(), j++);
    ui.language1->addItem(i.key(), i.value());
    ui.language2->addItem(i.key(), i.value());
  }
  QObject::connect(ui.language1, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_language1(int)));
  QObject::connect(ui.language2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_language2(int)));
}

ConfigDglLexika::~ConfigDglLexika()
{
}

void ConfigDglLexika::updateSettings()
{
  ui.language1->setCurrentIndex(zuordnung.value(Config::instance()->currentLexikon1()));
  ui.language2->setCurrentIndex(zuordnung.value(Config::instance()->currentLexikon2()));
  updateInfo(1);
  updateInfo(2);
}

QStringList ConfigDglLexika::saveSettings()
{
  QStringList ret;

  if (ui.language1->itemData(ui.language1->currentIndex()).toString() != Config::instance()->currentLexikon1())
  {
    Config::instance()->setDb(1, ui.language1->itemData(ui.language1->currentIndex()).toString());
    ret.append("language1");
  }
  if (ui.language2->itemData(ui.language2->currentIndex()).toString() != Config::instance()->currentLexikon2())
  {
    Config::instance()->setDb(2, ui.language2->itemData(ui.language2->currentIndex()).toString());
    ret.append("language2");
  }
  return ret;
}

void ConfigDglLexika::updateInfo(int _i)
{
  QTextBrowser *tb = (1 == _i) ? ui.infoLanguage1 : ui.infoLanguage2;
  QString key = (1 == _i) ? ui.language1->itemData(ui.language1->currentIndex()).toString() : ui.language2->itemData(ui.language2->currentIndex()).toString();

  QHash<QString, QVariant> info = Config::instance()->lexikaInformations().value(key);
  QString rowStart = "<tr><td style=\"font-weight:bold;background-color: #888;color:#ffffff;\">";
  QString rowMiddle = ":</td><td>";
  QString str;
  str.append("<table cellpadding=4 cellspacing=1 border=0>");
  //str.append(rowStart+trUtf8("Name")+rowMiddle+info.value("name").toString()+"</td></tr>");
  str.append(rowStart+trUtf8("Version")+rowMiddle+info.value("version").toString()+"</td></tr>");
  str.append(rowStart+trUtf8("Anzahl der Einträge")+rowMiddle+info.value("count").toString()+"</td></tr>");
  str.append(rowStart+trUtf8("Autor")+rowMiddle+info.value("author").toString()+"</td></tr>");
  str.append(rowStart+trUtf8("Lizenz")+rowMiddle+info.value("license").toString()+"</td></tr>");
  str.append(rowStart+trUtf8("Beschreibung")+rowMiddle+info.value("description").toString()+"</td></tr>");
  str.append("</table>");

  tb->setText(str);
}

void ConfigDglLexika::slot_language1(int)
{
  updateInfo(1);
}

void ConfigDglLexika::slot_language2(int)
{
  updateInfo(2);
}
