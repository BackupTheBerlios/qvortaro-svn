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

#include "config.h"
Config* Config::m_Instance = 0;

#ifdef Q_OS_LINUX
const QString Config::m_pathToDbs_def = "~/.qvortaro";
#else
const QString Config::m_pathToDbs_def = QApplication::applicationDirPath()+QDir::separator()+"dict";
#endif

const QString Config::m_currentLexikon1_def = "ts_eode";
const QString Config::m_currentLexikon2_def = "ts_deeo";

const bool Config::m_checkForEoEnding_def = true;
const bool Config::m_checkForPunctation_def = false;
const bool Config::m_restoreOnStartup_def = false;

const bool Config::m_cbUse_def = false;
const unsigned int Config::m_cbMode_def = 0;
const unsigned int Config::m_cbTime_def = 1000;

//const bool Config::m_gestaltungLexikaV_def = true;
//const bool Config::m_gestaltungLexikaInnenH_def = true;
//const bool Config::m_gestaltungLexikaLB_def = true;

const bool Config::m_stayOnTop_def = false;
const bool Config::m_useWildcards_def = true;

const QString Config::m_fontLemmata_def = "Trebuchet MS,12,-1,5,50,0,0,0,0,0";
const QString Config::m_fontTranslation_def = "Trebuchet MS,12,-1,5,50,0,0,0,0,0";
const QString Config::m_fontSearch_def = "Trebuchet MS,12,-1,5,50,0,0,0,0,0";

void Config::read()
{
  QSettings settings;

  settings.beginGroup("Main");
  m_pathToDbs = settings.value( "m_pathToDbs", m_pathToDbs_def ).toString();
  m_restoreOnStartup = settings.value( "m_restoreOnStartup", m_restoreOnStartup_def ).toBool();
  m_currentLexikon1 = settings.value( "m_currentLexikon1", m_currentLexikon1_def ).toString();
  m_currentLexikon2 = settings.value( "m_currentLexikon2", m_currentLexikon2_def ).toString();

  m_stayOnTop = settings.value( "m_stayOnTop", m_stayOnTop_def ).toBool();

  if (!m_fontLemmata.fromString(settings.value( "m_fontLemmata", m_fontLemmata_def ).toString()))
    m_fontLemmata.fromString(m_fontLemmata_def);
  if (!m_fontTranslation.fromString(settings.value( "m_fontTranslation", m_fontTranslation_def ).toString()))
    m_fontTranslation.fromString(m_fontTranslation_def);
  if (!m_fontSearch.fromString(settings.value( "m_fontSearch", m_fontSearch_def ).toString()))
    m_fontSearch.fromString(m_fontSearch_def);
  settings.endGroup();

  settings.beginGroup("Gestaltung");
  m_currentView = settings.value("currentView", QMap<QString,QVariant>()).toMap();
  //  m_gestaltungLexikaV = settings.value( "m_gestaltungLexikaV", m_gestaltungLexikaV_def ).toBool();
  //  m_gestaltungLexikaInnenH = settings.value( "m_gestaltungLexikaInnenH", m_gestaltungLexikaInnenH_def ).toBool();
  //  m_gestaltungLexikaLB = settings.value( "m_gestaltungLexikaLB", m_gestaltungLexikaLB_def ).toBool();
  settings.endGroup();

  settings.beginGroup("Search");
  m_checkForEoEnding = settings.value( "m_checkForEoEnding", m_checkForEoEnding_def ).toBool();
  m_checkForPunctation = settings.value( "m_checkForPunctation", m_checkForPunctation_def ).toBool();
  m_useWildcards = settings.value( "m_useWildcards", m_useWildcards_def ).toBool();
  settings.endGroup();

  settings.beginGroup("Clipboard");
  m_cbUse = settings.value( "m_cbUse", m_cbUse_def ).toBool();
  m_cbMode = settings.value( "m_cbMode", m_cbMode_def ).toUInt();
  setCbTime(settings.value( "m_cbTime", m_cbTime_def ).toUInt());
  settings.endGroup();

  int size = settings.beginReadArray("Views");
  m_storedViews.clear();
  for (int i = 0; i < size; ++i)
  {
    settings.setArrayIndex(i);
    if (!settings.value("k").toString().isEmpty())
      m_storedViews.insert(settings.value("k").toString(), settings.value("v").toMap());
  }
  settings.endArray();

  readLexikaInformations();
}

void Config::write()
{
  QSettings settings;

  settings.beginGroup("Main");
  settings.setValue("m_pathToDbs", m_pathToDbs);
  settings.setValue("m_stayOnTop", m_stayOnTop);
  settings.setValue("m_restoreOnStartup", m_restoreOnStartup);
  settings.setValue("m_currentLexikon1", m_currentLexikon1);
  settings.setValue("m_currentLexikon2", m_currentLexikon2);
  settings.setValue("m_fontLemmata", m_fontLemmata.toString());
  settings.setValue("m_fontTranslation", m_fontTranslation.toString());
  settings.setValue("m_fontSearch", m_fontSearch.toString());
  settings.endGroup();

  settings.beginGroup("Gestaltung");
  settings.setValue("currentView", m_currentView);
  //  settings.setValue("m_gestaltungLexikaV", m_gestaltungLexikaV);
  //  settings.setValue("m_gestaltungLexikaInnenH", m_gestaltungLexikaInnenH);
  //  settings.setValue("m_gestaltungLexikaLB", m_gestaltungLexikaLB);
  settings.endGroup();

  settings.beginGroup("Search");
  settings.setValue("m_checkForEoEnding", m_checkForEoEnding);
  settings.setValue("m_checkForPunctation", m_checkForPunctation);
  settings.setValue("m_useWildcards", m_useWildcards);
  settings.endGroup();

  settings.beginGroup("Clipboard");
  settings.setValue("m_cbUse", m_cbUse);
  settings.setValue("m_cbMode", m_cbMode);
  settings.setValue("m_cbTime", m_cbTime);
  settings.endGroup();

  /// TODO alten schlonz aufräumen!
  settings.beginWriteArray("Views");
  QMapIterator<QString, QMap<QString, QVariant> > i(m_storedViews);
  int j = 0;
  while (i.hasNext())
  {
    i.next();
    settings.setArrayIndex(j++);
    settings.setValue("k", i.key());
    settings.setValue("v", i.value());
  }
  settings.endArray();
}

bool Config::containsPathLexika(const QString &_str)
{
  m_pathToDbs = _str;
  return readLexikaInformations();
}

bool Config::readLexikaInformations()
{
  m_lexikaInformations.clear();

  QDir dir(m_pathToDbs);
  dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable);

  QStringList list = dir.entryList(QStringList("*.db") );
  for (int i = 0; i < list.size(); ++i)
  {
    {
      QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "db_config_tmp");
      QString path = m_pathToDbs + QDir::separator() + list.at(i);
      db.setDatabaseName(path);
      if (db.open() )
      {
        QHash< QString, QVariant> hash;
        QSqlQuery query(db);
        query.exec("SELECT key,val FROM info");
        while (query.next() )
        {
          hash.insert(query.value( 0 ).toString(), query.value( 1 ).toString() );
        }
        hash.insert("path", path);
        if (hash.contains("programm") && "qvortaro" == hash.value("programm"))
          m_lexikaInformations.insert(hash.value( "id" ).toString(), hash);
      }
      else
      {
        qCritical() << "Failed to open database: " << path;
        qCritical() << "Last error:" << db.lastError();
      }
    }
    QSqlDatabase::removeDatabase("db_config_tmp");
  }
  return !m_lexikaInformations.isEmpty();
}

QMap<QString, QString> Config::languages() const
{
  QMap<QString, QString> tmp;
  QList<QString> list = m_lexikaInformations.keys();
  for (int i = 0; i < list.size(); ++i)
  {
    tmp.insert(m_lexikaInformations.value(list.at(i)).value("name").toString(), list.at(i));
  }
  return tmp;
}

bool Config::setDb(const unsigned int _pos, const QString _id)
{
  if ((_pos != 1 && _pos != 2) || !m_lexikaInformations.contains(_id))
    return false;

  QSqlDatabase& db = (_pos == 1) ? m_db1 : m_db2;
  QString& loadedLexika = (_pos == 1) ? m_currentLexikon1 : m_currentLexikon2;
  QString db_id = (_pos == 1) ? "config_db1" : "config_db2";

  if (QSqlDatabase::connectionNames().contains(db_id) )
    QSqlDatabase::removeDatabase(db_id);
  db = QSqlDatabase::addDatabase("QSQLITE", db_id);
  db.setDatabaseName(m_lexikaInformations.value(_id).value("path").toString());
  if ( !db.open() )
  {
    loadedLexika = "";
    qCritical() << "Failed to open database: " << m_lexikaInformations.value(_id).value("path").toString();
    qCritical() << "Last error:" << db.lastError();
    return false;
  }
  else
  {
    loadedLexika = _id;
    return true;
  }
}

void Config::removeDatabases()
{
  if (QSqlDatabase::connectionNames().contains("config_db1") )
  {
    QSqlDatabase::removeDatabase("config_db1");
    m_currentLexikon1.clear();
  }
  if (QSqlDatabase::connectionNames().contains("config_db2") )
  {
    QSqlDatabase::removeDatabase("config_db2");
    m_currentLexikon2.clear();
  }
}

QString Config::lexikaLanguage(const int _i)
{
  QString& lexika = (1 == _i) ? m_currentLexikon1 : m_currentLexikon2;
  if (m_lexikaInformations.contains(lexika) && m_lexikaInformations.value(lexika).contains("lang1"))
    return m_lexikaInformations.value(lexika).value("lang1").toString();
  else
    return QString::null;
  }
