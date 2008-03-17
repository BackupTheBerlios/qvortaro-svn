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

#ifndef SEARCHLAYOUT1_H
#define SEARCHLAYOUT1_H

#include <QtGui/QWidget>
#include "ui_searchlayout1.h"

class SearchLayout1 : public QWidget
{
  Q_OBJECT

  public:
    SearchLayout1(QWidget *parent = 0);
    ~SearchLayout1();
    void moveSelection(int, int);
    void setDirection(QBoxLayout::Direction);
    void setOrientation(Qt::Orientation);
    void setElementOrder(QString);
    void updadeMyGui();

  public slots:
    void updateDb(int);
    void cbSearch(const QString&);
    void resetSearch();

  private slots:
  void search(const QString&);
  void search();

  private:
    Ui::searchLayout1Class ui;
};

#endif // SEARCHLAYOUT1_H
