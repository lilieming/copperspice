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

#include <qclipboard.h>

#ifndef QT_NO_CLIPBOARD

#include <qapplication.h>
#include <qapplication_p.h>
#include <qpixmap.h>
#include <qclipboard_p.h>
#include <qvariant.h>
#include <qbuffer.h>
#include <qimage.h>
#include <qtextcodec.h>

QT_BEGIN_NAMESPACE

#ifndef Q_WS_X11
QClipboard::QClipboard(QObject *parent)
   : QObject(parent), d_ptr(new QClipboardPrivate)
{
   // nothing
}
#endif

#ifndef Q_OS_WIN32
QClipboard::~QClipboard()
{
}
#endif

QString QClipboard::text(QString &subtype, Mode mode) const
{
   const QMimeData *const data = mimeData(mode);
   if (!data) {
      return QString();
   }

   const QStringList formats = data->formats();
   if (subtype.isEmpty()) {
      if (formats.contains(QLatin1String("text/plain"))) {
         subtype = QLatin1String("plain");
      } else {
         for (int i = 0; i < formats.size(); ++i)
            if (formats.at(i).startsWith(QLatin1String("text/"))) {
               subtype = formats.at(i).mid(5);
               break;
            }
         if (subtype.isEmpty()) {
            return QString();
         }
      }
   } else if (!formats.contains(QLatin1String("text/") + subtype)) {
      return QString();
   }

   const QByteArray rawData = data->data(QLatin1String("text/") + subtype);

#ifndef QT_NO_TEXTCODEC
   QTextCodec *codec = QTextCodec::codecForMib(106); // utf-8 is default
   if (subtype == QLatin1String("html")) {
      codec = QTextCodec::codecForHtml(rawData, codec);
   } else {
      codec = QTextCodec::codecForUtfText(rawData, codec);
   }
   return codec->toUnicode(rawData);

#else
   return rawData;
#endif

}

QString QClipboard::text(Mode mode) const
{
   const QMimeData *data = mimeData(mode);
   return data ? data->text() : QString();
}

void QClipboard::setText(const QString &text, Mode mode)
{
   QMimeData *data = new QMimeData;
   data->setText(text);
   setMimeData(data, mode);
}

QImage QClipboard::image(Mode mode) const
{
   const QMimeData *data = mimeData(mode);
   if (!data) {
      return QImage();
   }
   return qvariant_cast<QImage>(data->imageData());
}

void QClipboard::setImage(const QImage &image, Mode mode)
{
   QMimeData *data = new QMimeData;
   data->setImageData(image);
   setMimeData(data, mode);
}

QPixmap QClipboard::pixmap(Mode mode) const
{
   const QMimeData *data = mimeData(mode);
   return data ? qvariant_cast<QPixmap>(data->imageData()) : QPixmap();
}

void QClipboard::setPixmap(const QPixmap &pixmap, Mode mode)
{
   QMimeData *data = new QMimeData;
   data->setImageData(pixmap);
   setMimeData(data, mode);
}

bool QClipboard::supportsSelection() const
{
   return supportsMode(Selection);
}

bool QClipboard::supportsFindBuffer() const
{
   return supportsMode(FindBuffer);
}

bool QClipboard::ownsClipboard() const
{
   return ownsMode(Clipboard);
}

bool QClipboard::ownsSelection() const
{
   return ownsMode(Selection);
}

bool QClipboard::ownsFindBuffer() const
{
   return ownsMode(FindBuffer);
}

void QClipboard::emitChanged(Mode mode)
{
   switch (mode) {
      case Clipboard:
         emit dataChanged();
         break;
      case Selection:
         emit selectionChanged();
         break;
      case FindBuffer:
         emit findBufferChanged();
         break;
      default:
         break;
   }
   emit changed(mode);
}

const char *QMimeDataWrapper::format(int n) const
{
   if (formats.isEmpty()) {
      QStringList fmts = data->formats();
      for (int i = 0; i < fmts.size(); ++i) {
         formats.append(fmts.at(i).toLatin1());
      }
   }
   if (n < 0 || n >= formats.size()) {
      return 0;
   }
   return formats.at(n).data();
}

QByteArray QMimeDataWrapper::encodedData(const char *format) const
{
   if (QLatin1String(format) != QLatin1String("application/x-qt-image")) {
      return data->data(QLatin1String(format));
   } else {
      QVariant variant = data->imageData();
      QImage img = qvariant_cast<QImage>(variant);
      QByteArray ba;
      QBuffer buffer(&ba);
      buffer.open(QIODevice::WriteOnly);
      img.save(&buffer, "PNG");
      return ba;
   }
}

QVariant QMimeSourceWrapper::retrieveData(const QString &mimetype, QVariant::Type) const
{
   return source->encodedData(mimetype.toLatin1());
}

bool QMimeSourceWrapper::hasFormat(const QString &mimetype) const
{
   return source->provides(mimetype.toLatin1());
}

QStringList QMimeSourceWrapper::formats() const
{
   QStringList fmts;
   int i = 0;
   const char *fmt;
   while ((fmt = source->format(i))) {
      fmts.append(QLatin1String(fmt));
      ++i;
   }
   return fmts;
}

#endif // QT_NO_CLIPBOARD

QT_END_NAMESPACE
