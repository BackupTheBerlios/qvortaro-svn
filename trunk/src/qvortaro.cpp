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

#include "qvortaro.h"
#include "config.h"
#include "configdgl.h"
#include "configviewdgl.h"
#include "qvortaroueber.h"

qvortaro::qvortaro(QWidget *parent) :
  QMainWindow(parent)
{
  Config::instance()->read();

  ui.setupUi(this);
  statusBar()->hide();
  createMenuAndActions();
  QObject::connect(m_aBeenden, SIGNAL(triggered()), this, SLOT(slot_quit()));
  QObject::connect(m_agAnordnungLexika, SIGNAL(triggered(QAction*)), this, SLOT(slot_changeAnordnungLexika(QAction*)));
  QObject::connect(m_agGestaltungLexikaAnordnung, SIGNAL(triggered(QAction*)), this, SLOT(slot_changeGestaltungLexika(QAction*)));
  QObject::connect(m_agGestaltungLexikaGestaltung, SIGNAL(triggered(QAction*)), this, SLOT(slot_changeGestaltungLexika(QAction*)));
  QObject::connect(m_agLexika1, SIGNAL(triggered(QAction*)), this, SLOT(slot_changeLexika1(QAction*)));
  QObject::connect(m_agLexika2, SIGNAL(triggered(QAction*)), this, SLOT(slot_changeLexika2(QAction*)));
  QObject::connect(m_agCaption, SIGNAL(triggered(QAction*)), this, SLOT(slot_changeCaption(QAction*)));
  QObject::connect(m_aProgrammEinrichten, SIGNAL(triggered()), this, SLOT(slot_configDgl()));
  QObject::connect(m_aAnsichtSpeichern, SIGNAL(triggered()), this, SLOT(slot_ansichtSpeichern()));
  QObject::connect(m_aAnsichtZeigeLanguage2, SIGNAL(triggered(bool)), this, SLOT(slot_zeigeLanguage2()));
  QObject::connect(m_aAnsichtZeigeLanguage2, SIGNAL(toggled(bool)), this, SLOT(slot_zeigeLanguage2()));
  QObject::connect(m_agAnsichtLaden, SIGNAL(triggered(QAction*)), this, SLOT(slot_ansichtLaden(QAction*)));
  QObject::connect(m_aUeber, SIGNAL(triggered()), this, SLOT(slot_showUeber()));
  QObject::connect(m_aStayOnTop, SIGNAL(triggered(bool)), this, SLOT(slot_stayOnTop()));

  mySearchLayout1 = new SearchLayout1();
  ui.sw->insertWidget(0, mySearchLayout1);

  ui.sw->setCurrentIndex(0);

  // Zwischenablage
  m_cb = QApplication::clipboard();
  m_cbStringLast = getCbString();
  m_cbTimer = new QTimer(this);
  m_cbTimer->setSingleShot(true);
  QObject::connect(m_cbTimer, SIGNAL(timeout()), this, SLOT(slot_checkCb()));
  slot_checkCb();

  // Keine Wörterbücher gefunden
  if (Config::instance()->languages().isEmpty())
  {
    if (!Config::instance()->containsPathLexika(QApplication::applicationDirPath()+QDir::separator()+"dict") && !Config::instance()->containsPathLexika(QApplication::applicationDirPath()))
      QMessageBox::warning(
          this,
          "qVortaro - "+trUtf8("Keine Wörterbücher gefunden"),
          trUtf8("Es konnten keine Wörterbucher gefunden werden!\n\n"
            "Bitte überprüfen Sie unter »Einstellungen->aVortaro einrichten«,\n" "ob der richtige Pfad zum Ordner mit den Wörterbüchern\n" "angegeben wurde."),
          QMessageBox::Ok);
  }

  if (Config::instance()->restoreOnStartup() && !Config::instance()->currentView().isEmpty() && Config::instance()->currentView().contains("zeigeLanguage2"))
  {
    restoreView(Config::instance()->currentView());
    m_aStayOnTop->setChecked(Config::instance()->stayOnTop());
    slot_stayOnTop();
  }
  else
  {
    m_aStayOnTop->setChecked(false);
    slot_stayOnTop();
    Config::instance()->setCurrentView(getDefaultView());
    restoreView(getDefaultView());
    adjustSize();
  }
}

qvortaro::~qvortaro()
{
}

QString qvortaro::getCbString() const
{
  if (1 == Config::instance()->cbMode())
    return m_cb->text(QClipboard::Selection);
  else if (2 == Config::instance()->cbMode())
    return m_cb->text(QClipboard::FindBuffer);
  else
    return m_cb->text(QClipboard::Clipboard);
}

void qvortaro::slot_checkCb()
{
  if (!Config::instance()->cbUse())
    return;

  QString cbString = getCbString();
  if (cbString != m_cbStringLast && !cbString.isEmpty())
  {
    m_cbStringLast = cbString;
    if (ui.sw->currentWidget() == mySearchLayout1)
      mySearchLayout1->cbSearch(m_cbStringLast);
  }
  m_cbTimer->start(Config::instance()->cbTime());
}

void qvortaro::slot_quit()
{
  Config::instance()->setCurrentView(getView());
  Config::instance()->write();
  Config::instance()->removeDatabases();
  qApp->quit();
}

void qvortaro::keyPressEvent(QKeyEvent * e)
{
  /// TODO weitere shortcuts einbauen
  int keyValue = e->key();
  //  Qt::KeyboardModifiers keyModifier = e->modifiers();
  switch (keyValue)
  {
    case Qt::Key_Down:
      mySearchLayout1->moveSelection( 1, 1);
      break;
    case Qt::Key_Up:
      mySearchLayout1->moveSelection( -1, 1);
      break;
    case Qt::Key_PageDown:
      mySearchLayout1->moveSelection( 5, 1);
      break;
    case Qt::Key_PageUp:
      mySearchLayout1->moveSelection( -5, 1);
      break;
    case Qt::Key_Escape:
      mySearchLayout1->resetSearch();
      break;
  }
}

void qvortaro::slot_ansichtSpeichern()
{
  ConfigViewDgl dlg;
  dlg.setCurrentView(getView());
  dlg.adjustSize();

  if (dlg.exec() == QDialog::Accepted)
  {
    QString name = dlg.name();
    if (!name.isEmpty() && !Config::instance()->storedViews().keys().contains(name))
    {
      Config::instance()->setStoredView(name, dlg.getConfig());
      createActionsForViews();
      restoreView(Config::instance()->storedViews().value(name));
    }
    else
    {
      QMessageBox::warning(
          this,
          "qVortaro",
          trUtf8("Ansicht konnte nicht gespeichert werden.\n Mögliche Ursachen:\n - Der angegebene Name wird bereits verwendet\n - Der angegebene Namen war leer"),
          QMessageBox::Ok);
    }
  }
}

void qvortaro::slot_configDgl()
{
  ConfigDgl dlg;
  dlg.adjustSize();

  if (dlg.exec() == QDialog::Accepted)
  {
    QStringList changes = dlg.save();
    if (changes.contains("font") || changes.contains("zeigeLanguage2"))
    {
      mySearchLayout1->updadeMyGui();
    }
    if (changes.contains("language1"))
    {
      mySearchLayout1->updateDb(1);
    }
    if (changes.contains("language2"))
    {
      mySearchLayout1->updateDb(2);
    }
    if (changes.contains("klipper"))
    {
      slot_checkCb();
    }
    if (changes.contains("gestaltungLexikaLB"))
    {
      if (Config::instance()->currentView().value("gestaltungLexikaLB").toBool())
        m_aGestaltungLexikaLB->trigger();
      else
        m_aGestaltungLexikaBL->trigger();
    }
    if (changes.contains("gestaltungLexikaInnenH"))
    {
      if (Config::instance()->currentView().value("gestaltungLexikaInnenH").toBool())
        m_aGestaltungLexikaHorizontal->trigger();
      else
        m_aGestaltungLexikaVertikal->trigger();
    }
    if (changes.contains("gestaltungLexikaV"))
    {
      if (Config::instance()->currentView().value("gestaltungLexikaV").toBool())
        m_aAnordnungLexikaVertikal->trigger();
      else
        m_aAnordnungLexikaHorizontal->trigger();
    }
    if (changes.contains("caption"))
    {
      switch (Config::instance()->currentView().value("caption").toInt())
      {
        case 0:
          m_aCaptionNone->trigger();
          break;
        case 2:
          m_aCaptionLong->trigger();
          break;
        default:
          m_aCaptionShort->trigger();
          break;
      }
    }
    if (changes.contains("pathToDbs"))
      QMessageBox::warning(this, "qVortaro - "+trUtf8("Neustart erforderlich"),
          trUtf8("Die Änderung des Ordners zu den Wörterbüchern wird erst\n nach einem Neustart wirksam."),
          QMessageBox::Ok);
  }
  createActionsForViews();
}

void qvortaro::createMenuAndActions()
{
  m_mFile = new QMenu(trUtf8("&Datei"), this);

  m_aBeenden = new QAction(QIcon(":aBeenden"), trUtf8("B&eenden"), this);
  m_aBeenden->setShortcut(tr("Ctrl+Q"));
  m_mFile->addAction(m_aBeenden);

  m_mView = new QMenu(trUtf8("&Ansicht"), this);

  m_mAnsichtLaden = new QMenu(trUtf8("Gespeicherte Ansicht laden"), this);
  m_mAnsichtLaden->setIcon(QIcon(":actionLoadView"));
  m_agAnsichtLaden = new QActionGroup(this);
  m_mView->addMenu(m_mAnsichtLaden);
  createActionsForViews();

  m_aAnsichtSpeichern = new QAction(QIcon(":actionSaveView"), trUtf8("Aktuelle Ansicht speichern"), this);
  m_mView->addAction(m_aAnsichtSpeichern);

  m_mView->addSeparator();
  m_aAnsichtZeigeLanguage2 = new QAction(trUtf8("Wörterbuch 2 anzeigen"), this);
  m_aAnsichtZeigeLanguage2->setCheckable(true);
  m_aAnsichtZeigeLanguage2->setChecked(true);
  m_mView->addAction(m_aAnsichtZeigeLanguage2);

  m_mView->addSeparator();
  m_mLexika1 = new QMenu(trUtf8("Wörterbuch 1"), this);
  m_mLexika1->setIcon(QIcon(":aBuch"));
  m_agLexika1 = new QActionGroup(this);
  m_mView->addMenu(m_mLexika1);
  m_mLexika2 = new QMenu(trUtf8("Wörterbuch 2"), this);
  m_mLexika2->setIcon(QIcon(":aBuch"));
  m_agLexika2 = new QActionGroup(this);
  m_mView->addMenu(m_mLexika2);

  // Caption
  m_mView->addSeparator();
  m_mCaption = new QMenu(trUtf8("Wörterbuchüberschrift"), this);
  m_mCaption->setIcon(QIcon(":aCaption"));
  m_aCaptionNone = new QAction(trUtf8("keine"), this);
  m_aCaptionNone->setCheckable(true);
  m_aCaptionShort = new QAction(trUtf8("kurz"), this);
  m_aCaptionShort->setCheckable(true);
  m_aCaptionShort->setChecked(true);
  m_aCaptionLong = new QAction(trUtf8("lang"), this);
  m_aCaptionLong->setCheckable(true);
  m_agCaption = new QActionGroup(this);
  m_agCaption->setExclusive(true);
  m_agCaption->addAction(m_aCaptionNone);
  m_agCaption->addAction(m_aCaptionShort);
  m_agCaption->addAction(m_aCaptionLong);
  m_mCaption->addAction(m_aCaptionNone);
  m_mCaption->addAction(m_aCaptionShort);
  m_mCaption->addAction(m_aCaptionLong);
  m_mView->addMenu(m_mCaption);

  // Anordnung
  m_mView->addSeparator();
  m_mAnordnungLexika = new QMenu(trUtf8("Anordnung der Wörterbücher im Hauptfenster"), this);
  m_mAnordnungLexika->setIcon(QIcon(":aAusrichtung"));
  m_agAnordnungLexika = new QActionGroup(this);
  m_aAnordnungLexikaHorizontal = new QAction(QIcon(":aLR"), trUtf8("nebeneinander"), this);
  m_aAnordnungLexikaHorizontal->setCheckable(true);
  m_aAnordnungLexikaVertikal = new QAction(QIcon(":aTB"), trUtf8("untereinander"), this);
  m_aAnordnungLexikaVertikal->setCheckable(true);
  m_agAnordnungLexika->addAction(m_aAnordnungLexikaHorizontal);
  m_agAnordnungLexika->addAction(m_aAnordnungLexikaVertikal);
  m_agAnordnungLexika->setExclusive(true);
  m_aAnordnungLexikaVertikal->setChecked(true);

  m_mAnordnungLexika->addAction(m_aAnordnungLexikaHorizontal);
  m_mAnordnungLexika->addAction(m_aAnordnungLexikaVertikal);
  m_mView->addMenu(m_mAnordnungLexika);

  // Gestaltung
  m_mGestaltungLexika = new QMenu(trUtf8("Anordnung der Sprachfelder"), this);
  m_mGestaltungLexika->setIcon(QIcon(":aAusrichtung"));
  m_mGestaltungLexikaAnordnung = new QMenu(trUtf8("Anordnung der Wörter und Übersetzungen"), this);
  m_mGestaltungLexikaAnordnung->setIcon(QIcon(":aAusrichtung"));
  m_agGestaltungLexikaAnordnung = new QActionGroup(this);
  m_aGestaltungLexikaHorizontal = new QAction(QIcon(":aLR"), trUtf8("nebeneinander"), this);
  m_aGestaltungLexikaHorizontal->setCheckable(true);
  m_aGestaltungLexikaVertikal = new QAction(QIcon(":aTB"), trUtf8("untereinander"), this);
  m_aGestaltungLexikaVertikal->setCheckable(true);
  m_agGestaltungLexikaAnordnung->addAction(m_aGestaltungLexikaHorizontal);
  m_agGestaltungLexikaAnordnung->addAction(m_aGestaltungLexikaVertikal);
  m_agGestaltungLexikaAnordnung->setExclusive(true);
  m_aGestaltungLexikaHorizontal->setChecked(true);
  m_mGestaltungLexikaAnordnung->addAction(m_aGestaltungLexikaHorizontal);
  m_mGestaltungLexikaAnordnung->addAction(m_aGestaltungLexikaVertikal);
  m_mGestaltungLexika->addMenu(m_mGestaltungLexikaAnordnung);

  m_mGestaltungLexikaGestaltung = new QMenu(trUtf8("Reihenfolge der Wörter und Übersetzungen"), this);
  m_mGestaltungLexikaGestaltung->setIcon(QIcon(":aAusrichtung"));
  m_agGestaltungLexikaGestaltung = new QActionGroup(this);
  m_aGestaltungLexikaLB = new QAction(QIcon(":aCwTr"), trUtf8("Wörter - Übersetzungen"), this);
  m_aGestaltungLexikaLB->setCheckable(true);
  m_aGestaltungLexikaBL = new QAction(QIcon(":aTrCw"), trUtf8("Übersetzungen - Wörter"), this);
  m_aGestaltungLexikaBL->setCheckable(true);
  m_agGestaltungLexikaGestaltung->addAction(m_aGestaltungLexikaLB);
  m_agGestaltungLexikaGestaltung->addAction(m_aGestaltungLexikaBL);
  m_agGestaltungLexikaGestaltung->setExclusive(true);
  m_aGestaltungLexikaLB->setChecked(true);
  m_mGestaltungLexikaGestaltung->addAction(m_aGestaltungLexikaLB);
  m_mGestaltungLexikaGestaltung->addAction(m_aGestaltungLexikaBL);
  m_mGestaltungLexika->addMenu(m_mGestaltungLexikaGestaltung);

  m_mView->addMenu(m_mGestaltungLexika);

  createActionsForLexika();

  m_mEinstellungen = new QMenu(trUtf8("&Einstellungen"), this);
  m_aStayOnTop = new QAction(trUtf8("Fenster immer im Vordergrund halten"), this);
  m_aStayOnTop->setCheckable(true);
  m_mEinstellungen->addAction(m_aStayOnTop);
  m_aProgrammEinrichten = new QAction(QIcon(":aConfigure"), trUtf8("qVortaro ein&richten ..."), this);
  m_mEinstellungen->addAction(m_aProgrammEinrichten);

  m_mHilfe = new QMenu(trUtf8("&Hilfe"), this);
  m_aUeber = new QAction(QIcon(":icon_16"), trUtf8("Ü&ber qVortaro"), this);
  m_mHilfe->addAction(m_aUeber);

  menuBar()->addMenu(m_mFile);
  menuBar()->addMenu(m_mView);
  menuBar()->addMenu(m_mEinstellungen);
  menuBar()->addMenu(m_mHilfe);
}

void qvortaro::createActionsForViews()
{
  QList<QAction*> list = m_agAnsichtLaden->actions();
  while (!list.isEmpty())
  {
    m_mAnsichtLaden->removeAction(list.first());
    m_agAnsichtLaden->removeAction(list.first());
    delete list.takeFirst();
  }
  QList<QString> tmp = Config::instance()->storedViews().keys();
  for (int i = 0; i < tmp.size(); ++i)
  {
    QAction *act = new QAction(QIcon(":actionView"), tmp.at(i), this);
    m_agAnsichtLaden->addAction(act);
    m_mAnsichtLaden->addAction(act);
  }
  m_mAnsichtLaden->setEnabled(0 < m_agAnsichtLaden->actions().count());
}

void qvortaro::createActionsForLexika()
{
  // lexikon 1
  QList<QAction*> list = m_agLexika1->actions();
  while (!list.isEmpty())
  {
    m_mLexika1->removeAction(list.first());
    m_agLexika1->removeAction(list.first());
    delete list.takeFirst();
  }
  QMap<QString, QString> tmp = Config::instance()->languages();
  QMapIterator<QString, QString> i(tmp);
  while (i.hasNext())
  {
    i.next();
    QAction *act = new QAction(i.key(), this);
    act->setCheckable(true);
    act->setChecked(i.value() == Config::instance()->currentLexikon1());
    act->setData(i.value());
    m_agLexika1->addAction(act);
    m_mLexika1->addAction(act);
  }

  // lexikon 2
  list = m_agLexika2->actions();
  while (!list.isEmpty())
  {
    m_mLexika2->removeAction(list.first());
    m_agLexika2->removeAction(list.first());
    delete list.takeFirst();
  }
  tmp = Config::instance()->languages();
  QMapIterator<QString, QString> j(tmp);
  while (j.hasNext())
  {
    j.next();
    QAction *act = new QAction(j.key(), this);
    act->setCheckable(true);
    act->setChecked(j.value() == Config::instance()->currentLexikon2());
    act->setData(j.value());
    m_agLexika2->addAction(act);
    m_mLexika2->addAction(act);
  }
}

void qvortaro::slot_zeigeLanguage2()
{
  Config::instance()->setCurrentView("zeigeLanguage2", m_aAnsichtZeigeLanguage2->isChecked());
  mySearchLayout1->updadeMyGui();
}

void qvortaro::slot_changeCaption(QAction *_act)
{
  if (_act == m_aCaptionLong)
    Config::instance()->setCurrentView("caption", 2);
  else if (_act == m_aCaptionNone)
    Config::instance()->setCurrentView("caption", 0);
  else
    Config::instance()->setCurrentView("caption", 1);
  mySearchLayout1->updadeMyGui();
}

void qvortaro::slot_changeLexika1(QAction *_act)
{
  Config::instance()->setDb(1, _act->data().toString());
  if (mySearchLayout1->isVisible())
    mySearchLayout1->updateDb(1);
}

void qvortaro::slot_changeLexika2(QAction *_act)
{
  Config::instance()->setDb(2, _act->data().toString());
  if (mySearchLayout1->isVisible())
    mySearchLayout1->updateDb(2);
}

void qvortaro::slot_changeAnordnungLexika(QAction *_act)
{
  if (_act == m_aAnordnungLexikaHorizontal)
    mySearchLayout1->setDirection(QBoxLayout::LeftToRight);
  else
    mySearchLayout1->setDirection(QBoxLayout::TopToBottom);
}

void qvortaro::slot_changeGestaltungLexika(QAction*)
{
  if (m_agGestaltungLexikaAnordnung->checkedAction() == m_aGestaltungLexikaHorizontal)
    mySearchLayout1->setOrientation(Qt::Horizontal);
  else
    mySearchLayout1->setOrientation(Qt::Vertical);

  if (m_agGestaltungLexikaGestaltung->checkedAction() == m_aGestaltungLexikaBL)
    mySearchLayout1->setElementOrder("browser");
  else
    mySearchLayout1->setElementOrder("list");
}

QMap<QString, QVariant> qvortaro::getView()
{
  QMap<QString, QVariant> tmp;
  tmp.insert("pos", pos());
  tmp.insert("size", size());
  tmp.insert("savePosSize", true);

  tmp.insert("zeigeLanguage2", m_aAnsichtZeigeLanguage2);

  if (m_agLexika1->checkedAction())
    tmp.insert("lexika1", m_agLexika1->checkedAction()->data());
  if (m_agLexika2->checkedAction())
    tmp.insert("lexika2", m_agLexika2->checkedAction()->data());
  tmp.insert("loadLexika", true);

  if (m_agCaption->checkedAction() == m_aCaptionLong)
    tmp.insert("caption", 2);
  else if (m_agCaption->checkedAction() == m_aCaptionNone)
    tmp.insert("caption", 0);
  else
    tmp.insert("caption", 1);

  tmp.insert("gestaltungLexikaLB", Config::instance()->currentView().value("gestaltungLexikaLB"));
  tmp.insert("gestaltungLexikaInnenH", Config::instance()->currentView().value("gestaltungLexikaInnenH"));
  tmp.insert("gestaltungLexikaV", Config::instance()->currentView().value("gestaltungLexikaV"));

  return tmp;
}

QMap<QString, QVariant> qvortaro::getDefaultView()
{
  QMap<QString, QVariant> tmp;
  tmp.insert("pos", pos());
  tmp.insert("size", size());
  tmp.insert("savePosSize", false);
  tmp.insert("zeigeLanguage2", true);
  tmp.insert("lexika1", Config::instance()->currentLexikon1_def());
  tmp.insert("lexika2", Config::instance()->currentLexikon2_def());
  tmp.insert("loadLexika", true);
  tmp.insert("caption", 1);
  tmp.insert("gestaltungLexikaLB", true);
  tmp.insert("gestaltungLexikaInnenH", true);
  tmp.insert("gestaltungLexikaV", true);

  return tmp;
}

void qvortaro::slot_ansichtLaden(QAction *_act)
{
  if (Config::instance()->storedViews().contains(_act->text()))
    restoreView(Config::instance()->storedViews().value(_act->text()));
}

void qvortaro::restoreView(const QMap<QString, QVariant>& _conf)
{
  if (!_conf.contains("savePosSize") || _conf.value("savePosSize").toBool())
  {
    if (_conf.contains("size"))
      resize(_conf.value("size").toSize());
    if (_conf.contains("pos"))
      move(_conf.value("pos").toPoint());
  }

  if (_conf.contains("zeigeLanguage2"))
    m_aAnsichtZeigeLanguage2->setChecked(_conf.value("zeigeLanguage2").toBool());

  if (_conf.contains("gestaltungLexikaLB") && !_conf.value("gestaltungLexikaLB").toBool())
    m_aGestaltungLexikaBL->trigger();
  else
    m_aGestaltungLexikaLB->trigger();

  if (_conf.contains("gestaltungLexikaInnenH") && !_conf.value("gestaltungLexikaInnenH").toBool())
    m_aGestaltungLexikaVertikal->trigger();
  else
    m_aGestaltungLexikaHorizontal->trigger();

  if (_conf.contains("gestaltungLexikaV") && !_conf.value("gestaltungLexikaV").toBool())
    m_aAnordnungLexikaHorizontal->trigger();
  else
    m_aAnordnungLexikaVertikal->trigger();

  if (_conf.contains("caption"))
  {
    if (0 == _conf.value("caption").toInt())
      m_aCaptionNone->trigger();
    else if (2 == _conf.value("caption").toInt())
      m_aCaptionLong->trigger();
    else
      m_aCaptionShort->trigger();
  }

  if (!_conf.contains("loadLexika") || _conf.value("loadLexika").toBool())
  {
    if (_conf.contains("lexika1"))
    {
      if (Config::instance()->setDb(1, _conf.value("lexika1").toString()) || Config::instance()->setDb(1, Config::instance()->currentLexikon1_def()))
      {
      }
      mySearchLayout1->updateDb(1);
    }
    if (_conf.contains("lexika2"))
    {
      if (Config::instance()->setDb(2, _conf.value("lexika2").toString()) || Config::instance()->setDb(2, Config::instance()->currentLexikon2_def()))
      {
      }
      mySearchLayout1->updateDb(2);

    }
  }
}

void qvortaro::slot_showUeber()
{
  QVortaroUeber dlg;
  dlg.adjustSize();
  dlg.exec();
}

void qvortaro::slot_stayOnTop()
{
  Qt::WindowFlags flags = this->windowFlags();
  if ((flags & Qt::WindowStaysOnTopHint) == Qt::WindowStaysOnTopHint)
  {
    if (!m_aStayOnTop->isChecked())
      this->setWindowFlags(flags & ~Qt::WindowStaysOnTopHint);
  }
  else
  {
    if (m_aStayOnTop->isChecked())
    {
      flags |= Qt::WindowStaysOnTopHint;
      this->setWindowFlags(flags);
    }
  }
  Config::instance()->setStayOnTop(m_aStayOnTop->isChecked());
  this->show();
}

