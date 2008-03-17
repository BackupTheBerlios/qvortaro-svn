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

#include "eolineeditvalidator.h"

EoLineEditValidator::EoLineEditValidator(QObject * parent) :
  QValidator(parent), m_watching(false)
{
}

EoLineEditValidator::~EoLineEditValidator()
{
}

QValidator::State EoLineEditValidator::validate(QString& _str, int& _pos) const
{
  if (!m_watching)
    return Acceptable;

  /// TODO auch andere Systeme außer "x" verwenden...
  QRegExp rx("[ghujcs]{1}(x){1}");
  rx.setCaseSensitivity(Qt::CaseInsensitive);
  if (_str.contains(rx))
    _pos -= fake_fixup(_str);
  return Acceptable;
}

int EoLineEditValidator::fake_fixup(QString & _str) const
{
  int lengthCopy = _str.length();

  QString system = "x";
  if (_str.contains(system, Qt::CaseSensitive))
  {
    _str.replace("g"+system, QString::fromUtf8("ĝ"));
    _str.replace("h"+system, QString::fromUtf8("ĥ"));
    _str.replace("u"+system, QString::fromUtf8("ŭ"));
    _str.replace("j"+system, QString::fromUtf8("ĵ"));
    _str.replace("c"+system, QString::fromUtf8("ĉ"));
    _str.replace("s"+system, QString::fromUtf8("ŝ"));
    _str.replace("G"+system, QString::fromUtf8("Ĝ"));
    _str.replace("H"+system, QString::fromUtf8("Ĥ"));
    _str.replace("U"+system, QString::fromUtf8("Ŭ"));
    _str.replace("J"+system, QString::fromUtf8("Ĵ"));
    _str.replace("C"+system, QString::fromUtf8("Ĉ"));
    _str.replace("S"+system, QString::fromUtf8("Ŝ"));
  }
  if (system != "^")
  {
    system.toUpper();
    if (_str.contains(system, Qt::CaseSensitive))
    {
      _str.replace("g"+system, QString::fromUtf8("ĝ"));
      _str.replace("h"+system, QString::fromUtf8("ĥ"));
      _str.replace("u"+system, QString::fromUtf8("ŭ"));
      _str.replace("j"+system, QString::fromUtf8("ĵ"));
      _str.replace("c"+system, QString::fromUtf8("ĉ"));
      _str.replace("s"+system, QString::fromUtf8("ŝ"));
      _str.replace("G"+system, QString::fromUtf8("Ĝ"));
      _str.replace("H"+system, QString::fromUtf8("Ĥ"));
      _str.replace("U"+system, QString::fromUtf8("Ŭ"));
      _str.replace("J"+system, QString::fromUtf8("Ĵ"));
      _str.replace("C"+system, QString::fromUtf8("Ĉ"));
      _str.replace("S"+system, QString::fromUtf8("Ŝ"));
    }
  }

  return (lengthCopy - _str.length());
}
