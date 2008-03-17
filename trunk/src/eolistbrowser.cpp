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
#include <QtSql>
#include "eolistbrowser.h"
#include "config.h"

EoListBrowser::EoListBrowser(QWidget *parent) :
  QWidget(parent), m_model(0), m_currentLanguage("")
{
  ui.setupUi(this);

  rxEscape = QRegExp::QRegExp("('|_|%){1}");

  m_model = new QSqlQueryModel(this);
  ui.list->setModel(m_model);
  QObject::connect(ui.list->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(showTranslation(const QModelIndex&, const QModelIndex&)));
}

EoListBrowser::~EoListBrowser()
{
}

void EoListBrowser::setDb(QSqlDatabase _db, QString _str, QString _search)
{
  m_db = _db;
  m_currentLanguage = _str;
  search(_search);
}

void EoListBrowser::showTranslation(const QModelIndex& _curr, const QModelIndex& /*prev*/)
{
  ui.browser->setHtml(m_model->record(_curr.row()).value("translation").toString());
}

void EoListBrowser::search(const QString& _str)
{
  if (_str.isEmpty())
  {
    m_model->setQuery("SELECT catchword, translation FROM `words`", m_db);
  }
  else
  {
    QString tmp = _str;
    tmp.replace(rxEscape, "\\\\1");
    if (Config::instance()->useWildcards())
    {
      tmp.replace("*", "%");
      tmp.replace(".", "_");
    }
    m_model->setQuery("SELECT catchword, translation FROM `words` WHERE catchword LIKE '" +tmp +"%'", m_db);
    if (0 == ui.list->model()->rowCount())
    {
      if (Config::instance()->checkForPunctation())
      {
        tmp.replace(QRegExp("(^[ ,;\\.:?!\"']+)|([ ,;\\.:?!\"']+$)"), "");
        m_model->setQuery("SELECT catchword, translation FROM `words` WHERE catchword LIKE '" +tmp +"%'", m_db);
      }
      if ("eo" == m_currentLanguage.toLower() && Config::instance()->checkForEoEnding() && 0 == ui.list->model()->rowCount())
      {
        tmp.replace(QRegExp("(jn|j|n)$"), "");
        tmp.replace(QRegExp("(as|is|os|us|u|inta|onta|anta|ita|ota|ata)$"), "i");
        m_model->setQuery("SELECT catchword, translation FROM `words` WHERE catchword LIKE '" +tmp +"%'", m_db);
      }
    }
  }
  ui.list->setCurrentIndex(m_model->index(0, 0));
}

void EoListBrowser::moveSelection(int _step)
{
  QModelIndex idx = m_model->index(ui.list->selectionModel()->currentIndex().row()+_step, 0);
  if (idx.isValid())
  {
    ui.list->setCurrentIndex(idx);
  }
  else
  {
    if (_step < 0)
    {
      ui.list->setCurrentIndex(m_model->index(0, 0));
    }
    else
    {
      m_model->fetchMore(idx);
      if (idx.isValid())
      {
        ui.list->setCurrentIndex(idx);
      }
      else
      {
        /// TODO Zugriff auf das letzte Element
        while (_step > 0 && !idx.isValid())
        {
          --_step;
          idx = m_model->index(ui.list->selectionModel()->currentIndex().row()+_step, 0);
        }
        if (idx.isValid())
          ui.list->setCurrentIndex(idx);
      }
    }
  }
}

void EoListBrowser::setElementOrder(QString _first)
{
  QListView *isList = qobject_cast<QListView *>(ui.splitter->widget(0));
  if (("list" == _first && !isList) || ("browser" == _first && isList))
  {
    QWidget *tmp = ui.splitter->widget(0);
    ui.splitter->insertWidget(0, ui.splitter->widget(1));
    ui.splitter->insertWidget(1, tmp);
  }
}

void EoListBrowser::setOrientation(Qt::Orientation _ori)
{
  ui.splitter->setOrientation(_ori);
}

void EoListBrowser::setCaption(const QString &_str)
{
  ui.box->setTitle(_str);
}

void EoListBrowser::updateMyGui()
{
  if (ui.list->font() != Config::instance()->fontLemmata())
    ui.list->setFont(Config::instance()->fontLemmata());
  if (ui.browser->font() != Config::instance()->fontTranslation())
    ui.browser->setFont(Config::instance()->fontTranslation());
}

