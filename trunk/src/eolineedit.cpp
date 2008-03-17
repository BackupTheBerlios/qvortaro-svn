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

#include <QtCore/QObject>
#include <QtCore>

#include "eolineedit.h"

EoLineEdit::EoLineEdit(QWidget *parent) :
  QLineEdit(parent), m_tracing(false)
{
  myEoLineEditValidator = new EoLineEditValidator(this);
  this->setValidator(myEoLineEditValidator);
}

EoLineEdit::~EoLineEdit()
{
}

void EoLineEdit::setTracing(bool _tracing)
{
  myEoLineEditValidator->setWatching(_tracing);
  //  if (m_tracing == _tracing)
  //    return;
  //
  //  m_tracing = _tracing;
  //
  //  if (m_tracing)
  //  QObject::connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(transform(const QString&)));
  //  else
  //    this->disconnect(SIGNAL(transform(const QString&)));
}

