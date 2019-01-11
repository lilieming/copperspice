/***********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (c) 2012-2019 Ansel Sermersheim
*
* Copyright (C) 2015 The Qt Company Ltd.
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://www.gnu.org/licenses/
*
***********************************************************************/

#include "qxsdattributereference_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

bool XsdAttributeReference::isAttributeUse() const
{
   return false;
}

bool XsdAttributeReference::isReference() const
{
   return true;
}

void XsdAttributeReference::setType(Type type)
{
   m_type = type;
}

XsdAttributeReference::Type XsdAttributeReference::type() const
{
   return m_type;
}

void XsdAttributeReference::setReferenceName(const QXmlName &referenceName)
{
   m_referenceName = referenceName;
}

QXmlName XsdAttributeReference::referenceName() const
{
   return m_referenceName;
}

void XsdAttributeReference::setSourceLocation(const QSourceLocation &location)
{
   m_sourceLocation = location;
}

QSourceLocation XsdAttributeReference::sourceLocation() const
{
   return m_sourceLocation;
}

QT_END_NAMESPACE
