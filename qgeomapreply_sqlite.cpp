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
#include "debug_osz.h"
#include "qgeomappingmanagerengine_offline.h"
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
        setMapImageData(query.value(0).toByteArray());
//        quint16 uiIdentifier = query.value(0).toByteArray().at(0) < 8;
//        uiIdentifier += query.value(0).toByteArray().at(1);
//        qDebug() << "Identifier=" << uiIdentifier;
//        qDebug() << "Kennung(0)=" << (quint8)query.value(0).toByteArray().at(0);
//        qDebug() << "Kennung(1)=" << (quint8)query.value(0).toByteArray().at(1);
//        qDebug() << "Kennung(2)=" << (quint8)query.value(0).toByteArray().at(2);
//        if (uiIdentifier==0xFFD8) //ID: JPG
//            setMapImageFormat("JPG");
        // GeoServiceProvider chooses the correct format atomatically. - So setting of ImageFormat is not neccessary
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
