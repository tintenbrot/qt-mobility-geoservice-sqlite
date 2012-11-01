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

#include "qgeomappingmanagerengine_sqlite.h"
#include "qgeomapreply_sqlite.h"

#include <qgeotiledmaprequest.h>

#include <QDesktopServices>
#include <QSize>
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QFileInfo>


#include <QSqlQuery>


QGeoMappingManagerEngineSqlite::QGeoMappingManagerEngineSqlite(const QMap<QString, QVariant> &parameters, QGeoServiceProvider::Error *error, QString *errorString)
        : QGeoTiledMappingManagerEngine(parameters),
        m_parameters(parameters)
{
    m_sqlite=0;
    //
    Q_UNUSED(error)
    Q_UNUSED(errorString)

    QList<QString> keys = m_parameters.keys();

    m_tileExt="png";
    m_offlinefile=QDir::homePath()+QDir::separator();
#if defined(__ARMEL__) //Harmattan
    m_offlinefile +=  "MyDocs";
    m_offlinefile += QDir::separator();
#endif
    m_offlinefile += "maps";
    m_offlinefile += QDir::separator();
    m_offlinefile += SQLITE_FILE;
    //
    if (keys.contains("tintenbrot_offline.filename")) {
        QString sfilename = m_parameters.value("tintenbrot_offline.filename").toString();
        if (!sfilename.isEmpty())
            if (QFile(sfilename).exists())
                m_offlinefile = sfilename;
    }
    bool ok;
    QString sQuery;
    int iMinZoom=10;  //Standard
    int iMaxZoom=18;  //Standard
    //
    m_sqlite=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","tintenbrotConnect"));
    m_sqlite->setDatabaseName(m_offlinefile);
    ok=m_sqlite->open();
    if (!ok) {
        qDebug() << "lastError=" << m_sqlite->lastError();
    }
    //
    QSqlQuery query(*m_sqlite);
    //
    sQuery=QString("SELECT minzoom FROM info");
    ok=query.prepare(sQuery);
    if (!ok) {
        qDebug() << "lastError=" << m_sqlite->lastError();
    }
    ok=query.exec();
    if (!ok) {
        qDebug() << "lastError=" << m_sqlite->lastError();
    }
    if (query.next())
    {
        iMinZoom=query.value(0).toInt()+10;
    }
    sQuery=QString("SELECT maxzoom FROM info");
    ok=query.prepare(sQuery);
    ok=query.exec();
    if (query.next())
    {
        iMaxZoom=query.value(0).toInt()+10;
    }
    //
    setMinimumZoomLevel(iMinZoom);
    setMaximumZoomLevel(iMaxZoom);
    setTileSize(QSize(256,256));

    //SL_MAP_TYPE
    QList<QGraphicsGeoMap::MapType> types;
    types << QGraphicsGeoMap::StreetMap;    
    setSupportedMapTypes(types);
}

QGeoMappingManagerEngineSqlite::~QGeoMappingManagerEngineSqlite()
{
    if (m_sqlite != 0) {
        qDebug() << "SQLITE: Close DB";
        m_sqlite->close();
        delete m_sqlite;
    }
}

QGeoTiledMapReply* QGeoMappingManagerEngineSqlite::getTileImage(const QGeoTiledMapRequest &request)
{
    QGeoTiledMapReply* mapReply = 0;
    mapReply = new QGeoMapReplySqlite(m_sqlite, request, this);
    return mapReply;
}


