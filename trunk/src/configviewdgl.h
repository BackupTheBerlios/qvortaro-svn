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

#ifndef CONFIGVIEWDGL_H
#define CONFIGVIEWDGL_H

#include <QtGui>
#include "ui_configviewdgl.h"

class ConfigViewDgl : public QDialog
{
  Q_OBJECT

  public:
    ConfigViewDgl(QWidget *parent = 0);
    ~ConfigViewDgl();

    void viewEdit(const QString&);
    void setCurrentView(QMap<QString, QVariant>);
    QMap<QString, QVariant> getConfig();
    QString name() const
    {
      return ui.name->text();
    }

  private:
    Ui::ConfigViewDglClass ui;
    void updateViewPreview();
    QMap<QString, QVariant> m_updateInfos;
    bool m_edit;

  private slots:
    void on_cLB_currentIndexChanged();
    void on_cLexika_currentIndexChanged();
    void on_cLexikaObjekte_currentIndexChanged();
    void on_cbCaption_currentIndexChanged();
    void on_zeigeLanguage2_stateChanged();
    void slot_checkName(const QString&);
};

#endif // CONFIGVIEWDGL_H
