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

#ifndef CONFIGDGLVIEW_H
#define CONFIGDGLVIEW_H

#include <QtGui>
#include "configdglvorlage.h"
#include "ui_configdglview.h"

class ConfigDglView : public ConfigDglVorlage
{
  Q_OBJECT

  public:
    ConfigDglView(QWidget *parent = 0);
    ~ConfigDglView();
    void updateSettings();
    QStringList saveSettings();

  private:
    Ui::ConfigDglViewClass ui;
    void updateStoredViewsPage();
    bool m_delete;

  private slots:
    void updateCurrentViewPreview();
    void on_cLB_currentIndexChanged();
    void on_cLexika_currentIndexChanged();
    void on_cLexikaObjekte_currentIndexChanged();
    void on_zeigeLanguage2_stateChanged();
    void on_cbCaption_currentIndexChanged();
    void on_pbDelete_clicked();
    void on_pbEdit_clicked();
    void on_pbAdd_clicked();
};

#endif // CONFIGDGLVIEW_H
