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
#include <QImage>
#include <QBuffer>

QGeoMapReplySqlite::QGeoMapReplySqlite(QSqlDatabase *sqlite, const QGeoTiledMapRequest &request, QObject *parent)
        : QGeoTiledMapReply(request, parent)
{
    m_query = QSqlQuery(*sqlite);
    //
    QGeoMappingManagerEngineSqlite *mapManagerEngineSqlite = static_cast<QGeoMappingManagerEngineSqlite*>(parent);
    m_MaxZoom=mapManagerEngineSqlite->getMaxZoom();
    //
    getTileKey(request);
    //
    QFuture<void> future = QtConcurrent::run(this, &QGeoMapReplySqlite::getTile);
    m_fwatcher.setFuture(future);
    connect(&m_fwatcher, SIGNAL(finished()), this, SLOT(getTileFinished()));
}


QGeoMapReplySqlite::~QGeoMapReplySqlite()
{
}

void QGeoMapReplySqlite::getTileKey(const QGeoTiledMapRequest &request)
{
    int iZoom=request.zoomLevel();
    int iX=request.column();
    int iY=request.row();
    int iWidth=256;
    int iLeft=0, iTop=0;
    //
    if (iZoom>m_MaxZoom) //Need PixelZoom
    {
        int iDiff=iZoom-m_MaxZoom;
        iZoom=m_MaxZoom;
        iLeft=iX % (1<<iDiff);
        iTop=iY % (1<<iDiff);
        iX=iX>>iDiff;
        iY=iY>>iDiff;
        iWidth=iWidth>>iDiff;
        iLeft=iLeft*iWidth;
        iTop=iTop*iWidth;
    }
    m_CutOut.setLeft(iLeft);
    m_CutOut.setTop(iTop);
    m_CutOut.setWidth(iWidth);
    m_CutOut.setHeight(iWidth); //tiles are squared, so Width=Height!

    m_tileKey=QString("SELECT image FROM tiles WHERE x=%1 AND y=%2 AND z=%3").arg(iX).arg(iY).arg(17-iZoom);;
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
        if (m_CutOut.width()==256) {
            // Imageformat is automatically chosen, so do not define it
            setMapImageData(m_query.value(0).toByteArray());
        }
        else //Pixelzoom is needed
        {
            QImage myPixelZoom=QImage::fromData(m_query.value(0).toByteArray());
            myPixelZoom=myPixelZoom.copy(m_CutOut);
            myPixelZoom=myPixelZoom.scaled(QSize(256,256));
            //
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            myPixelZoom.save(&buffer, "JPG"); //JPG-Handling is much faster then PNG
            setMapImageData(ba);
            setMapImageFormat("JPG");
        }
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
