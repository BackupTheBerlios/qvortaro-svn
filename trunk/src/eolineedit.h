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

#ifndef EOLINEEDIT_H
#define EOLINEEDIT_H

#include <QtGui/QLineEdit>

#include "eolineeditvalidator.h"

class EoLineEdit : public QLineEdit
{
  Q_OBJECT

  public:
    EoLineEdit(QWidget *parent = 0);
    ~EoLineEdit();

    enum TransliterationSystem
    { SystemX, SystemH, SystemC};

    /**
     * Legt fest, ob die Eingabe auf ein Esperanto-Schreibsystem hin überprüft werden soll.
     */
    void setTracing(bool _tracing = false);

    bool tracing() const
    {
      return m_tracing;
    }

  private:
    bool m_tracing;
    EoLineEditValidator *myEoLineEditValidator;

};

#endif // EOLINEEDIT_H
