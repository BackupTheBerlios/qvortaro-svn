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

#include "configviewdgl.h"
#include "config.h"

ConfigViewDgl::ConfigViewDgl(QWidget *parent) :
  QDialog(parent)
{
  ui.setupUi(this);
  ui.frame->setStyleSheet("background-image: url(\":dlgTopVortaroBG\"); background-repeat: repeat-x; background-position: bottom; background-color: #ffffff;");
  if (ui.buttonBox->button(QDialogButtonBox::Ok))
  {
    ui.buttonBox->button(QDialogButtonBox::Ok)->setIcon(QIcon(":button_ok"));
    ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
  }
  if (ui.buttonBox->button(QDialogButtonBox::Cancel))
    ui.buttonBox->button(QDialogButtonBox::Cancel)->setIcon(QIcon(":button_cancel"));
  QObject::connect(ui.name, SIGNAL(textChanged(const QString&)), this, SLOT(slot_checkName(const QString&)));
  m_edit = false;
}

ConfigViewDgl::~ConfigViewDgl()
{
}

void ConfigViewDgl::viewEdit(const QString &_name)
{
  ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
  ui.label_name->hide();
  ui.name->hide();
  QObject::disconnect(ui.name);
  m_edit = true;
  ui.caption->setText(trUtf8("Bearbeite Ansicht '%1'").arg(_name)+"  ");
}

void ConfigViewDgl::slot_checkName(const QString &_name)
{
  if (ui.buttonBox->button(QDialogButtonBox::Ok))
    ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!_name.isEmpty() && !Config::instance()->storedViews().keys().contains(_name));
}

void ConfigViewDgl::setCurrentView(QMap<QString, QVariant> _map)
{
  m_updateInfos = _map;

  ui.name->clear();
  ui.cbPosSize->setChecked(true);

  // Wörterbücher
  ui.zeigeLanguage2->setChecked(_map.value("zeigeLanguage2").toBool());
  ui.language1->clear();
  ui.language2->clear();
  QMap<QString, int> zuordnung;
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
  ui.language1->setCurrentIndex(zuordnung.value(_map.value("lexika1").toString()));
  ui.language2->setCurrentIndex(zuordnung.value(_map.value("lexika2").toString()));
  if (m_edit && _map.contains("loadLexika"))
    ui.gbLexika->setChecked(_map.value("loadLexika").toBool());
  else
    ui.gbLexika->setChecked(false);

  // Anordnung
  if (_map.value("gestaltungLexikaV").toBool())
    ui.cLexika->setCurrentIndex(1);
  else
    ui.cLexika->setCurrentIndex(0);

  if (_map.value("gestaltungLexikaInnenH").toBool())
    ui.cLexikaObjekte->setCurrentIndex(0);
  else
    ui.cLexikaObjekte->setCurrentIndex(1);

  if (_map.value("gestaltungLexikaLB").toBool())
    ui.cLB->setCurrentIndex(0);
  else
    ui.cLB->setCurrentIndex(1);

  ui.cbCaption->setCurrentIndex(_map.value("caption").toInt());

  updateViewPreview();
}

QMap<QString, QVariant> ConfigViewDgl::getConfig()
{
  QMap<QString, QVariant> tmp;
  tmp.insert("pos", m_updateInfos.value("pos"));
  tmp.insert("size", m_updateInfos.value("size"));
  tmp.insert("savePosSize", ui.cbPosSize->isChecked());

  tmp.insert("zeigeLanguage2", ui.zeigeLanguage2->isChecked());
  tmp.insert("lexika1", ui.language1->itemData(ui.language1->currentIndex()));
  tmp.insert("lexika2", ui.language2->itemData(ui.language2->currentIndex()));
  tmp.insert("loadLexika", ui.gbLexika->isChecked());

  switch (ui.cbCaption->currentIndex())
  {
    case 0:
      tmp.insert("caption", 0);
      break;
    case 2:
      tmp.insert("caption", 2);
      break;
    default:
      tmp.insert("caption", 1);
      break;
  }

  tmp.insert("gestaltungLexikaLB", (0 == ui.cLB->currentIndex()));
  tmp.insert("gestaltungLexikaInnenH", (0 == ui.cLexikaObjekte->currentIndex()));
  tmp.insert("gestaltungLexikaV", (1 == ui.cLexika->currentIndex()));

  return tmp;
}

void ConfigViewDgl::updateViewPreview()
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

void ConfigViewDgl::on_cLB_currentIndexChanged()
{
  updateViewPreview();
}

void ConfigViewDgl::on_cLexika_currentIndexChanged()
{
  updateViewPreview();
}

void ConfigViewDgl::on_cLexikaObjekte_currentIndexChanged()
{
  updateViewPreview();
}

void ConfigViewDgl::on_cbCaption_currentIndexChanged()
{
  updateViewPreview();
}

void ConfigViewDgl::on_zeigeLanguage2_stateChanged()
{
  updateViewPreview();
}

