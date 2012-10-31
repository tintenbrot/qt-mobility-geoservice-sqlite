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

#ifndef QGEOMAPPINGMANAGERENGINE_OFFLINE_H
#define QGEOMAPPINGMANAGERENGINE_OFFLINE_H

#include "qgeoserviceproviderplugin_offline.h"

#include <qgeoserviceprovider.h>
#include <qgeotiledmappingmanagerengine.h>
#include "quazip.h"
#include "quazipfile.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// If tile is recently updated - do not send any request to server until N days pass
// def tile cache size in bytes;  use 0 value for unlimited cache;
#define OSZ_FILE "default.sqlitedb"

QTM_USE_NAMESPACE

class QGeoMappingManagerEngineOffline : public QGeoTiledMappingManagerEngine
{
    Q_OBJECT
public:
    QGeoMappingManagerEngineOffline(const QMap<QString, QVariant> &parameters,
                                  QGeoServiceProvider::Error *error,
                                  QString *errorString);
    ~QGeoMappingManagerEngineOffline();

    QGeoTiledMapReply* getTileImage(const QGeoTiledMapRequest &request);


private:
    Q_DISABLE_COPY(QGeoMappingManagerEngineOffline)

    QMap<QString, QVariant> m_parameters;

    enum t_FileFormat { OSZ=0, SQLITEDB };

    QuaZip  m_zip;
    quint16 m_ZoomMin;
    quint16 m_ZoomMax;

    QString m_offlinefile;
    QString m_tileExt;

    QSqlDatabase *m_sqlite;


    t_FileFormat m_FileFormat;
};

#endif
