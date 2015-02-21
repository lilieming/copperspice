/***********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
* Copyright (c) 2012-2014 Ansel Sermersheim
* Copyright (c) 2012-2014 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software: you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with CopperSpice.  If not, see
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#ifndef QSCRIPTDEBUGGERCODEFINDERWIDGET_P_H
#define QSCRIPTDEBUGGERCODEFINDERWIDGET_P_H

#include <qscriptdebuggercodefinderwidgetinterface_p.h>

QT_BEGIN_NAMESPACE

class QScriptDebuggerCodeFinderWidgetPrivate;

class QScriptDebuggerCodeFinderWidget : public QScriptDebuggerCodeFinderWidgetInterface
{
   CS_OBJECT(QScriptDebuggerCodeFinderWidget)

 public:
   QScriptDebuggerCodeFinderWidget(QWidget *parent = 0);
   ~QScriptDebuggerCodeFinderWidget();

   int findOptions() const;

   QString text() const;
   void setText(const QString &text);

   void setOK(bool ok);
   void setWrapped(bool wrapped);

 protected:
   void keyPressEvent(QKeyEvent *e);

 private:
   Q_DECLARE_PRIVATE(QScriptDebuggerCodeFinderWidget)
   Q_DISABLE_COPY(QScriptDebuggerCodeFinderWidget) 

   CS_SLOT_1(Private, void _q_updateButtons())
   CS_SLOT_2(_q_updateButtons)
 
   CS_SLOT_1(Private, void _q_onTextChanged(const QString &un_named_arg1))
   CS_SLOT_2(_q_onTextChanged)
  
   CS_SLOT_1(Private, void _q_next())
   CS_SLOT_2(_q_next)

   CS_SLOT_1(Private, void _q_previous())
   CS_SLOT_2(_q_previous)
  
};

QT_END_NAMESPACE

#endif
