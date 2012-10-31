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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

QGeoMapReplySqlite::QGeoMapReplySqlite(QSqlDatabase *sqlite, const QGeoTiledMapRequest &request, QObject *parent)
        : QGeoTiledMapReply(request, parent),
        m_tileRequest(request)
{
    bool ok;

    QSqlQuery query(*sqlite);
    QString sQuery=QString("SELECT image FROM tiles WHERE x=%1 AND y=%2").arg(request.column()).arg(request.row());
    qDebug() << "Query=" << sQuery;
    ok=query.prepare(sQuery);
    if (!ok) {
        qDebug() << query.lastError();
    }
    ok = query.exec();
    qDebug() << "SQLITE: Query: " << ok;
    if (!ok) {
        qDebug() << query.lastError();
    }
    //
    // Image ist eindeutig, also mit Next kommt ein Bild oder nicht
    if (query.next())
    {
        // Imageformat is automatically chosen, so do not define it
        setMapImageData(query.value(0).toByteArray());
        setFinished(true);
    }
    else
    {
        QFile fileError(":tile_notavailable");
        fileError.open(QIODevice::ReadOnly);
        setMapImageData(fileError.readAll());
        setMapImageFormat("PNG");
        fileError.close();
        setFinished(true);
    }
}


QGeoMapReplySqlite::~QGeoMapReplySqlite()
{
}


void QGeoMapReplySqlite::abort()
{
    //Needed function (it is public)
}
