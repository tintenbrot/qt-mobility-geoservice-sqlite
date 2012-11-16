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

#include <QDir>

QGeoMappingManagerEngineSqlite::QGeoMappingManagerEngineSqlite(const QMap<QString, QVariant> &parameters, QGeoServiceProvider::Error *error, QString *errorString)
        : QGeoTiledMappingManagerEngine(parameters),
        m_parameters(parameters)
{
    QString sSqliteFile="";
    //
    // Init class to have values if sqlite-file has errors or doesn't exist
    m_sqlite=0;
    int iMinZoom=10;  //Standard
    int iMaxZoom=18;  //Standard
    m_ZoomMin=iMinZoom;
    m_ZoomMax=iMaxZoom;
    //
    Q_UNUSED(error)
    Q_UNUSED(errorString)

    QList<QString> keys = m_parameters.keys();

    sSqliteFile=QDir::homePath()+QDir::separator();
#if defined(__ARMEL__) //Harmattan
    sSqliteFile += "MyDocs";
    sSqliteFile += QDir::separator();
#endif
    sSqliteFile += "maps";
    sSqliteFile += QDir::separator();
    sSqliteFile += SQLITE_FILE;
    //
    if (keys.contains("localfile"))
        sSqliteFile= m_parameters.value("localfile").toString();
    //
    if (!sSqliteFile.isEmpty())
    {
        if (QFile(sSqliteFile).exists())
        {
            //
            // File exists
            bool ok;
            QString sQuery;
            //
            m_sqlite=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","tintenbrotConnect"));
            m_sqlite->setDatabaseName(sSqliteFile);
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
                iMaxZoom=17-query.value(0).toInt();
                m_ZoomMax=iMaxZoom;
                iMaxZoom+=3;
            }
            sQuery=QString("SELECT maxzoom FROM info");
            ok=query.prepare(sQuery);
            ok=query.exec();
            if (query.next())
            {
                iMinZoom=17-query.value(0).toInt();
                m_ZoomMin=iMinZoom;
            }
            //
            // limit Zoomlevels to prevent nonsense-Values to crash app
            if (iMinZoom<0) iMinZoom=0;
            if (iMinZoom>20) iMinZoom=20;
            if (iMaxZoom<0) iMaxZoom=0;
            if (iMaxZoom>20) iMaxZoom=20;
            if (iMinZoom>iMaxZoom)
                std::swap(iMinZoom,iMaxZoom);
        }
    }
    //
    setMinimumZoomLevel(iMinZoom);
    setMaximumZoomLevel(iMaxZoom);
    setTileSize(QSize(256,256));

    //SL_MAP_TYPE (not need within this plugin)
//    QList<QGraphicsGeoMap::MapType> types;
//    types << QGraphicsGeoMap::StreetMap;
//    setSupportedMapTypes(types);
}

int QGeoMappingManagerEngineSqlite::getMaxZoom()
{
    return m_ZoomMax;
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


