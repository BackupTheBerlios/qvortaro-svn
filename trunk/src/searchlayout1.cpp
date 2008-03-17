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

#include "searchlayout1.h"
#include "config.h"

SearchLayout1::SearchLayout1(QWidget *parent) :
  QWidget(parent)
{
  ui.setupUi(this);
  ui.searchword->setTracing(true);

  QObject::connect(ui.searchword, SIGNAL(textChanged(const QString&)), this, SLOT(search(const QString&)));
  QObject::connect(ui.searchword, SIGNAL(returnPressed()), this, SLOT(search()));
  QObject::connect(ui.pbClear, SIGNAL(clicked()), this, SLOT(resetSearch()));
}

SearchLayout1::~SearchLayout1()
{

}

void SearchLayout1::updateDb(int _pos)
{
  if (_pos == 1)
    ui.lexikon1->setDb(Config::instance()->db1(), Config::instance()->lexikaLanguage(1), ui.searchword->text());
  if (_pos == 2)
    ui.lexikon2->setDb(Config::instance()->db2(), Config::instance()->lexikaLanguage(2), ui.searchword->text());
  updadeMyGui(); /// TODO verbessern "recursion"
}

void SearchLayout1::updadeMyGui()
{
  ui.lexikon1->updateMyGui();
  ui.lexikon2->updateMyGui();
  ui.searchword->setFont(Config::instance()->fontSearch());

  if (Config::instance()->currentView().contains("zeigeLanguage2"))
  {
    if (true == Config::instance()->currentView().value("zeigeLanguage2") && ui.lexikon2->isHidden())
      ui.lexikon2->search(ui.searchword->text());
    ui.lexikon2->setHidden(!Config::instance()->currentView().value("zeigeLanguage2").toBool());
  }

  switch (Config::instance()->currentView().value("caption").toInt())
  {
    case 1:
      ui.lexikon1->setCaption(Config::instance()->lexikaInformations().value(Config::instance()->currentLexikon1()).value("lang1").toString()+"-"+Config::instance()->lexikaInformations().value(Config::instance()->currentLexikon1()).value("lang2").toString());
      ui.lexikon2->setCaption(Config::instance()->lexikaInformations().value(Config::instance()->currentLexikon2()).value("lang1").toString()+"-"+Config::instance()->lexikaInformations().value(Config::instance()->currentLexikon2()).value("lang2").toString());
      break;
    case 2:
      ui.lexikon1->setCaption(Config::instance()->lexikaInformations().value(Config::instance()->currentLexikon1()).value("name").toString());
      ui.lexikon2->setCaption(Config::instance()->lexikaInformations().value(Config::instance()->currentLexikon2()).value("name").toString());
      break;
    default:
      ui.lexikon1->setCaption(QString::null);
      ui.lexikon2->setCaption(QString::null);
      break;
    }
  }

void SearchLayout1::resetSearch()
{
  ui.searchword->setText(QString::null);
}

void SearchLayout1::cbSearch(const QString& _str)
{
  ui.searchword->setText(_str);
}

void SearchLayout1::search()
{
  search(ui.searchword->text());
}

void SearchLayout1::search(const QString& _str)
{
  if (ui.lexikon1->isVisible())
    ui.lexikon1->search(_str);
  if (ui.lexikon2->isVisible())
    ui.lexikon2->search(_str);
}

void SearchLayout1::moveSelection(int _step, int /*_lexikon*/)
{
  if (ui.lexikon1->isVisible())
    ui.lexikon1->moveSelection(_step);
  if (ui.lexikon2->isVisible())
    ui.lexikon2->moveSelection(_step);
}

void SearchLayout1::setDirection(QBoxLayout::Direction _dir)
{
  QBoxLayout *l = qobject_cast<QBoxLayout *>(ui.lexikonFrame->layout());
  if (l)
  {
    l->setDirection(_dir);
  }
  Config::instance()->setCurrentView("gestaltungLexikaV", (QBoxLayout::TopToBottom == _dir));

}

void SearchLayout1::setOrientation(Qt::Orientation _ori)
{
  ui.lexikon1->setOrientation(_ori);
  ui.lexikon2->setOrientation(_ori);
  Config::instance()->setCurrentView("gestaltungLexikaInnenH", (Qt::Horizontal == _ori));
}

void SearchLayout1::setElementOrder(QString _str)
{
  ui.lexikon1->setElementOrder(_str);
  ui.lexikon2->setElementOrder(_str);
  Config::instance()->setCurrentView("gestaltungLexikaLB", ("list" == _str));
}
