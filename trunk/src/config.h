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

#ifndef CONFIG_H
#define CONFIG_H

#include <QtCore>
#include <QtGui>
#include <QtSql>

class Config
{

  public:
    bool containsPathLexika(const QString&);

  private:
    QSqlDatabase m_db1;
    QSqlDatabase m_db2;
  public:
    bool setDb(const unsigned int, const QString);
    QSqlDatabase db1() const
    {
      return m_db1;
    }
    QSqlDatabase db2() const
    {
      return m_db2;
    }
    void removeDatabases();

  private:
    QString m_currentLexikon1;
    static const QString m_currentLexikon1_def;
    QString m_currentLexikon2;
    static const QString m_currentLexikon2_def;
  public:
    QString currentLexikon1() const
    {
      return m_currentLexikon1;
    }
    QString currentLexikon1_def() const
    {
      return m_currentLexikon1_def;
    }
    QString currentLexikon2() const
    {
      return m_currentLexikon2;
    }
    QString currentLexikon2_def() const
    {
      return m_currentLexikon2_def;
    }
    void setCurrentLexikon1();

  private:
    unsigned int m_cbMode;
    static const unsigned int m_cbMode_def;
    unsigned int m_cbTime;
    static const unsigned int m_cbTime_def;
    bool m_cbUse;
    static const bool m_cbUse_def;
  public:
    void setCbMode(const unsigned int _i)
    {
      m_cbMode = _i;
    }
    int cbMode() const
    {
      return m_cbMode;
    }
    void setCbTime(const unsigned int _i)
    {
      m_cbTime = (1000 > _i) ? 1000 : _i;
    }
    int cbTime() const
    {
      return m_cbTime;
    }
    bool setCbUse(const bool _b)
    {
      if (m_cbUse == _b)
        return false;
      m_cbUse = _b;
      return true;
    }
    bool cbUse() const
    {
      return m_cbUse;
    }

  private:
    bool m_checkForEoEnding;
    static const bool m_checkForEoEnding_def;
  public:
    bool setCheckForEoEnding(const bool _b)
    {
      if (m_checkForEoEnding == _b)
        return false;
      m_checkForEoEnding = _b;
      return true;
    }
    bool checkForEoEnding() const
    {
      return m_checkForEoEnding;
    }

  private:
    bool m_stayOnTop;
    static const bool m_stayOnTop_def;
  public:
    bool setStayOnTop(const bool _b)
    {
      if (m_stayOnTop == _b)
        return false;
      m_stayOnTop = _b;
      return true;
    }
    bool stayOnTop() const
    {
      return m_stayOnTop;
    }

  private:
    bool m_useWildcards;
    static const bool m_useWildcards_def;
  public:
    bool setUseWildcards(const bool _b)
    {
      if (m_useWildcards == _b)
        return false;
      m_useWildcards = _b;
      return true;
    }
    bool useWildcards() const
    {
      return m_useWildcards;
    }

  private:
    QFont m_fontLemmata;
    static const QString m_fontLemmata_def;
    QFont m_fontTranslation;
    static const QString m_fontTranslation_def;
    QFont m_fontSearch;
    static const QString m_fontSearch_def;
  public:
    bool setFontLemmata(const QFont _f)
    {
      if (m_fontLemmata == _f)
        return false;
      m_fontLemmata = _f;
      return true;
    }
    QFont fontLemmata() const
    {
      return m_fontLemmata;
    }
    bool setFontTranslation(const QFont _f)
    {
      if (m_fontTranslation == _f)
        return false;
      m_fontTranslation = _f;
      return true;
    }
    QFont fontTranslation() const
    {
      return m_fontTranslation;
    }
    bool setFontSearch(const QFont _f)
    {
      if (m_fontSearch == _f)
        return false;
      m_fontSearch = _f;
      return true;
    }
    QFont fontSearch() const
    {
      return m_fontSearch;
    }

  private:
    bool m_checkForPunctation;
    static const bool m_checkForPunctation_def;
  public:
    bool setCheckForPunctation(const bool _b)
    {
      if (m_checkForPunctation == _b)
        return false;
      m_checkForPunctation = _b;
      return true;
    }
    bool checkForPunctation() const
    {
      return m_checkForPunctation;
    }

  private:
    QString m_pathToDbs;
    static const QString m_pathToDbs_def;
  public:
    bool setPathToDbs(const QString &_str)
    {
      if (_str == m_pathToDbs)
        return false;
      m_pathToDbs = _str;
      return true;
    }
    QString pathToDbs() const
    {
      return m_pathToDbs;
    }

  private:
    QHash< QString, QHash<QString, QVariant> > m_lexikaInformations;
  public:
    QString lexikaLanguage(const int);
    QMap<QString, QString> languages() const;
    const QHash< QString, QHash<QString, QVariant> > lexikaInformations()
    {
      return m_lexikaInformations;
    }

  private:
    QMap<QString, QVariant> m_currentView;
  public:
    QMap<QString, QVariant> currentView() const
    {
      return m_currentView;
    }
    bool setCurrentView(QString _s, QVariant _v)
    {
      if (m_currentView.contains(_s) && m_currentView.value(_s) == _v)
        return false;
      m_currentView.insert(_s, _v);
      return true;
    }
    void setCurrentView(QMap<QString, QVariant> _v)
    {
      m_currentView = _v;
    }

  private:
    QMap<QString, QMap<QString, QVariant> > m_storedViews;
  public:
    QMap<QString, QMap<QString, QVariant> > storedViews() const
    {
      return m_storedViews;
    }
    void setStoredView(QString _name, QMap<QString, QVariant> _map)
    {
      m_storedViews.insert(_name, _map);
    }
    void removeStoredView(QString _name)
    {
      m_storedViews.remove(_name);
    }

  private:
    bool m_restoreOnStartup;
    static const bool m_restoreOnStartup_def;
  public:
    bool setRestoreOnStartup(const bool _b)
    {
      if (m_restoreOnStartup == _b)
        return false;
      m_restoreOnStartup = _b;
      return true;
    }
    bool restoreOnStartup() const
    {
      return m_restoreOnStartup;
    }

  public:
    void read();
    void write();
    bool readLexikaInformations();

  public:
    static Config* instance()
    {
      static QMutex mutex;
      if (!m_Instance)
      {
        mutex.lock();

        if (!m_Instance)
          m_Instance = new Config;

        mutex.unlock();
      }

      return m_Instance;
    }

  private:
    Config()
    {
    }

    Config(const Config&);
    Config& operator=(const Config&);

    static Config* m_Instance;
};

#endif // CONFIG_H
