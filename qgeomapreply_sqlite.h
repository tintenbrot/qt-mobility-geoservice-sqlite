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

#ifndef QGEOMAPREPLY_SQLITE_H
#define QGEOMAPREPLY_SQLITE_H

#include <qgeotiledmapreply.h>
#include <QSqlQuery>
#include <QFutureWatcher>
#include <QRect>


QTM_USE_NAMESPACE

class QGeoMappingManagerEngineOffline;

class QGeoMapReplySqlite : public QGeoTiledMapReply
{
    Q_OBJECT

public:
    QGeoMapReplySqlite(QSqlDatabase *sqlite, const QGeoTiledMapRequest &request, QObject *parent = 0);

    ~QGeoMapReplySqlite();

    //QString getTileKey(const QGeoTiledMapRequest &request) const;


    void abort();

private slots:

protected:
    void getTile();

protected slots:
    void getTileFinished();

private:
    void getTileKey(const QGeoTiledMapRequest &request);

    QSqlQuery m_query;
    QString m_tileKey;
    int m_MaxZoom;
    QRect m_CutOut;
    QFutureWatcher<void> m_fwatcher;
};

#endif
