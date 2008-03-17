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

#include "configdglview.h"
#include "config.h"
#include "configviewdgl.h"

ConfigDglView::ConfigDglView(QWidget *parent) :
  ConfigDglVorlage(parent)
{
  ui.setupUi(this);
  m_delete = false;
}

ConfigDglView::~ConfigDglView()
{
}

void ConfigDglView::updateSettings()
{
  ui.tabWidget->setCurrentIndex(0);

  if (Config::instance()->currentView().contains("zeigeLanguage2"))
    ui.zeigeLanguage2->setChecked(Config::instance()->currentView().value("zeigeLanguage2").toBool());
  else
    ui.zeigeLanguage2->setChecked(true);

  if (Config::instance()->currentView().contains("gestaltungLexikaV") && Config::instance()->currentView().value("gestaltungLexikaV").toBool())
    ui.cLexika->setCurrentIndex(1);
  else
    ui.cLexika->setCurrentIndex(0);

  if (Config::instance()->currentView().contains("gestaltungLexikaInnenH") && Config::instance()->currentView().value("gestaltungLexikaInnenH").toBool())
    ui.cLexikaObjekte->setCurrentIndex(0);
  else
    ui.cLexikaObjekte->setCurrentIndex(1);

  if (Config::instance()->currentView().contains("gestaltungLexikaLB") && Config::instance()->currentView().value("gestaltungLexikaLB").toBool())
    ui.cLB->setCurrentIndex(0);
  else
    ui.cLB->setCurrentIndex(1);

  if (Config::instance()->currentView().contains("caption"))
    ui.cbCaption->setCurrentIndex(Config::instance()->currentView().value("caption").toInt());
  else
    ui.cbCaption->setCurrentIndex(1);

  updateCurrentViewPreview();
  updateStoredViewsPage();
}

QStringList ConfigDglView::saveSettings()
{
  QStringList ret;

  if (Config::instance()->setCurrentView("gestaltungLexikaLB", (0 == ui.cLB->currentIndex())))
    ret.append("gestaltungLexikaLB");
  if (Config::instance()->setCurrentView("gestaltungLexikaInnenH", (0 == ui.cLexikaObjekte->currentIndex())))
    ret.append("gestaltungLexikaInnenH");
  if (Config::instance()->setCurrentView("gestaltungLexikaV", (1 == ui.cLexika->currentIndex())))
    ret.append("gestaltungLexikaV");

  if (Config::instance()->setCurrentView("zeigeLanguage2", ui.zeigeLanguage2->isChecked()))
    ret.append("zeigeLanguage2");

  if (Config::instance()->setCurrentView("caption", ui.cbCaption->currentIndex()))
    ret.append("caption");

  if (m_delete)
    ret.append("storedViews");

  return ret;
}

void ConfigDglView::updateCurrentViewPreview()
{
  QString filename = ":l";
  filename += (1 == ui.cLexikaObjekte->currentIndex()) ? "v" : "h";
  filename += (1 == ui.cLB->currentIndex()) ? "bl" : "lb";
  if (1 == ui.cbCaption->currentIndex())
    filename += "s";
  else if (2 == ui.cbCaption->currentIndex())
    filename += "l";

  QPixmap pm(filename);
  pm = pm.scaled(pm.size()/2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

  if (1 == ui.cLexika->currentIndex())
  {
    ui.l1->setPixmap(pm);
    ui.l2->hide();
    if (ui.zeigeLanguage2->isChecked())
    {
      ui.l3->setPixmap(pm);
      ui.l3->show();
    }
    else
    {
      ui.l3->hide();
    }
  }
  else
  {
    ui.l1->setPixmap(pm);
    if (ui.zeigeLanguage2->isChecked())
    {
      ui.l2->setPixmap(pm);
      ui.l2->show();
    }
    else
    {
      ui.l2->hide();
    }
    ui.l3->hide();
  }
}

void ConfigDglView::on_cLB_currentIndexChanged()
{
  updateCurrentViewPreview();
}

void ConfigDglView::on_cLexika_currentIndexChanged()
{
  updateCurrentViewPreview();
}

void ConfigDglView::on_cLexikaObjekte_currentIndexChanged()
{
  updateCurrentViewPreview();
}

void ConfigDglView::on_cbCaption_currentIndexChanged()
{
  updateCurrentViewPreview();
}

void ConfigDglView::on_zeigeLanguage2_stateChanged()
{
  updateCurrentViewPreview();
}

void ConfigDglView::updateStoredViewsPage()
{
  ui.storedViews->clear();
  ui.storedViews->addItems(Config::instance()->storedViews().keys());
  ui.storedViews->setCurrentRow(0);
  ui.pbDelete->setEnabled(0 < ui.storedViews->count());
  ui.pbEdit->setEnabled(0 < ui.storedViews->count());
}

void ConfigDglView::on_pbDelete_clicked()
{
  if (ui.storedViews->currentItem())
  {
    Config::instance()->removeStoredView(ui.storedViews->currentItem()->text());
    m_delete = true;
  }
  updateStoredViewsPage();
}

void ConfigDglView::on_pbEdit_clicked()
{
  if (ui.storedViews->currentItem() && Config::instance()->storedViews().contains(ui.storedViews->currentItem()->text()))
  {
    ConfigViewDgl dlg;
    dlg.viewEdit(ui.storedViews->currentItem()->text());
    dlg.setCurrentView(Config::instance()->storedViews().value(ui.storedViews->currentItem()->text()));
    dlg.adjustSize();
    if (dlg.exec() == QDialog::Accepted)
    {
      Config::instance()->setStoredView(ui.storedViews->currentItem()->text(), dlg.getConfig());
    }
  }
}

void ConfigDglView::on_pbAdd_clicked()
{
  ConfigViewDgl dlg;
  dlg.setCurrentView(Config::instance()->currentView());
  dlg.adjustSize();
  if (dlg.exec() == QDialog::Accepted)
  {
    Config::instance()->setStoredView(dlg.name(), dlg.getConfig());
  }
  updateStoredViewsPage();
}

