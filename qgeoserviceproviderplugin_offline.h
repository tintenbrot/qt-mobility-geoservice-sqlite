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

#ifndef QGEOSERVICEPROVIDER_OFFLINE_H
#define QGEOSERVICEPROVIDER_OFFLINE_H

#include <qgeoserviceproviderfactory.h>
#include <QObject>

QTM_USE_NAMESPACE

class QGeoServiceProviderFactoryOffline : public QObject, public QGeoServiceProviderFactory
{
    Q_OBJECT
    Q_INTERFACES(QtMobility::QGeoServiceProviderFactory)
public:
    QGeoServiceProviderFactoryOffline();
    ~QGeoServiceProviderFactoryOffline();

    QString providerName() const;
    int providerVersion() const;
    QStringList validFileExt() const;

    QGeoMappingManagerEngine* createMappingManagerEngine(const QMap<QString, QVariant> &parameters,
            QGeoServiceProvider::Error *error,
            QString *errorString) const;

};

#endif
