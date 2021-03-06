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

#ifndef QGEOMAPPINGMANAGERENGINE_SQLITE_H
#define QGEOMAPPINGMANAGERENGINE_SQLITE_H

#include "qgeoserviceproviderplugin_sqlite.h"

#include <qgeoserviceprovider.h>
#include <qgeotiledmappingmanagerengine.h>

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#define SQLITE_FILE "default.sqlitedb"

QTM_USE_NAMESPACE

class QGeoMappingManagerEngineSqlite : public QGeoTiledMappingManagerEngine
{
    Q_OBJECT
public:
    QGeoMappingManagerEngineSqlite(const QMap<QString, QVariant> &parameters,
                                  QGeoServiceProvider::Error *error,
                                  QString *errorString);
    ~QGeoMappingManagerEngineSqlite();

    QGeoTiledMapReply* getTileImage(const QGeoTiledMapRequest &request);

    int getMaxZoom();

private:
    Q_DISABLE_COPY(QGeoMappingManagerEngineSqlite)

    QMap<QString, QVariant> m_parameters;

    quint16 m_ZoomMin;
    quint16 m_ZoomMax;

    QSqlDatabase *m_sqlite;

};

#endif
