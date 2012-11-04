/****************************************************************************
**
** Copyright (C) 2012 tintenbrot
** All rights reserved.
** Many thanks to Cloudmade. Their qtmobility-plugin was a nice sample to
** understand the geoservice of qtmobility.
** Contact: dastintenbrot@gmail.com
**
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** dastintenbrot@gmail.com.
**
****************************************************************************/

#include "qgeomapreply_sqlite.h"
#include "debug_sqlite.h"
#include "qgeomappingmanagerengine_sqlite.h"
#include <QSqlError>
#include <QFile>
#include <QtConcurrentRun>

QGeoMapReplySqlite::QGeoMapReplySqlite(QSqlDatabase *sqlite, const QGeoTiledMapRequest &request, QObject *parent)
        : QGeoTiledMapReply(request, parent)
{
    m_query = QSqlQuery(*sqlite);
    //
    m_tileKey=getTileKey(request);
    //
    QFuture<void> future = QtConcurrent::run(this, &QGeoMapReplySqlite::getTile);
    m_fwatcher.setFuture(future);
    connect(&m_fwatcher, SIGNAL(finished()), this, SLOT(getTileFinished()));
}


QGeoMapReplySqlite::~QGeoMapReplySqlite()
{
}

QString QGeoMapReplySqlite::getTileKey(const QGeoTiledMapRequest &request) const
{
    return QString("SELECT image FROM tiles WHERE x=%1 AND y=%2 AND z=%3").arg(request.column()).arg(request.row()).arg(17-request.zoomLevel());
}

void QGeoMapReplySqlite::getTile()
{
    bool ok;
    ok=m_query.prepare(m_tileKey);
    if (!ok) {
        qDebug() << m_query.lastError();
    }
    ok = m_query.exec();
    if (!ok) {
        qDebug() << m_query.lastError();
    }
    //
    // Image is unique, so next gives the needed tile or not
    if (m_query.next())
    {
        // Imageformat is automatically chosen, so do not define it
        setMapImageData(m_query.value(0).toByteArray());
    }
    else
    {
        QFile fileError(":tile_notavailable");
        fileError.open(QIODevice::ReadOnly);
        setMapImageData(fileError.readAll());
        setMapImageFormat("PNG");
        fileError.close();
    }
}

void QGeoMapReplySqlite::getTileFinished()
{
    setFinished(true);
}

void QGeoMapReplySqlite::abort()
{
    //Needed function (it is public)
}
