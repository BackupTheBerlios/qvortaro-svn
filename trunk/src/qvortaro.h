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

#ifndef QVORTARO_H
#define QVORTARO_H

#include <QtGui>

#include "searchlayout1.h"
#include "ui_qvortaro.h"

class qvortaro : public QMainWindow
{
  Q_OBJECT

  public:
    qvortaro(QWidget *parent = 0);
    ~qvortaro();

  private:
    Ui::qvortaroClass ui;
    SearchLayout1 *mySearchLayout1;
    QTimer *m_cbTimer;
    QClipboard *m_cb;
    QString m_cbStringLast;
    QString getCbString() const;
    QMap<QString, QVariant> getView();
    void restoreView(const QMap<QString, QVariant>&);

    void createMenuAndActions();
    void createActionsForLexika();
    void createActionsForViews();
    QMenu *m_mFile;
    QAction *m_aBeenden;

    QMenu *m_mView;

    QMenu *m_mAnsichtLaden;
    QActionGroup *m_agAnsichtLaden;

    QAction *m_aAnsichtSpeichern;
    QAction *m_aAnsichtZeigeLanguage2;

    QMenu *m_mLexika1;
    QActionGroup *m_agLexika1;
    QMenu *m_mLexika2;
    QActionGroup *m_agLexika2;

    QMenu *m_mCaption;
    QActionGroup *m_agCaption;
    QAction *m_aCaptionNone;
    QAction *m_aCaptionShort;
    QAction *m_aCaptionLong;

    QMenu *m_mAnordnungLexika;
    QActionGroup *m_agAnordnungLexika;
    QAction *m_aAnordnungLexikaHorizontal;
    QAction *m_aAnordnungLexikaVertikal;

    QMenu *m_mGestaltungLexika;
    QMenu *m_mGestaltungLexikaAnordnung;
    QActionGroup *m_agGestaltungLexikaAnordnung;
    QMenu *m_mGestaltungLexikaGestaltung;
    QActionGroup *m_agGestaltungLexikaGestaltung;
    QAction *m_aGestaltungLexikaLB;
    QAction *m_aGestaltungLexikaBL;
    QAction *m_aGestaltungLexikaHorizontal;
    QAction *m_aGestaltungLexikaVertikal;

    QMenu *m_mEinstellungen;
    QAction *m_aStayOnTop;
    QAction *m_aProgrammEinrichten;

    QMenu *m_mHilfe;
    QAction *m_aUeber;

  private slots:
    void slot_checkCb();
    void slot_changeAnordnungLexika(QAction*);
    void slot_changeGestaltungLexika(QAction*);
    void slot_changeLexika1(QAction*);
    void slot_changeLexika2(QAction*);
    void slot_changeCaption(QAction*);
    void slot_configDgl();
    void slot_ansichtSpeichern();
    void slot_zeigeLanguage2();
    void slot_ansichtLaden(QAction*);
    void slot_showUeber();
    void slot_stayOnTop();
    QMap<QString, QVariant> getDefaultView();

  public slots:
    void slot_quit();

  protected:
    void keyPressEvent(QKeyEvent*);

};

#endif // QVORTARO_H
