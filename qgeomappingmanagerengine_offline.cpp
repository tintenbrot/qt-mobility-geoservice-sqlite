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

#include "qgeomappingmanagerengine_offline.h"
#include "qgeomapreply_osz.h"
#include "qgeomapreply_sqlite.h"
#include "debug_osz.h"

#include <qgeotiledmaprequest.h>

#include <QDesktopServices>
#include <QSize>
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QFileInfo>

#include "quazip.h"
#include "quazipfile.h"

#include <QSqlQuery>


QGeoMappingManagerEngineOffline::QGeoMappingManagerEngineOffline(const QMap<QString, QVariant> &parameters, QGeoServiceProvider::Error *error, QString *errorString)
        : QGeoTiledMappingManagerEngine(parameters),
        m_parameters(parameters)
{
    qDebug() << "QGeoMappingManagerEngineOsz: Konstruktor";
    //
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
    m_offlinefile += OSZ_FILE;
    qDebug() << "home=" << m_offlinefile;
    //m_offlinefile += OSZ_FILE; //Standard
    //
    if (keys.contains("tintenbrot_offline.filename")) {
        qDebug() << "Got external filename";
        QString sfilename = m_parameters.value("tintenbrot_offline.filename").toString();
        qDebug() << sfilename;
        if (!sfilename.isEmpty())
            if (QFile(sfilename).exists())
                m_offlinefile = sfilename;
    }
    //
    // Check Extension, to have an idea about how to do the reply (QFileInfo does not work. - So pick up extension with string commands)
    QString sExt="OSZ";
    qint32 iPos=m_offlinefile.lastIndexOf(".");
    if (iPos>0) {
        sExt=m_offlinefile.mid(iPos+1).toUpper();
    }
    qDebug() << "Found Extension=" << sExt;

    m_FileFormat=OSZ; //Standard
    if (sExt=="OSZ") m_FileFormat=OSZ;
    if (sExt=="SQLITEDB") m_FileFormat=SQLITEDB;
    //
    switch(m_FileFormat) {
    case OSZ:
        m_zip.setZipName(m_offlinefile);
        qDebug() << "m_oszfile=" << m_offlinefile;
        qDebug() << "Filename set";
        qDebug() << m_zip.getZipName();
        if(!m_zip.open(QuaZip::mdUnzip)) {
            qDebug() << "Manifest: Error opening OSZ-File";
            setMinimumZoomLevel(0.0);
            setMaximumZoomLevel(18.0);
        }
        else {
            qDebug() << "Zip opened check Maifest-File";
            m_zip.setCurrentFile("Manifest.txt");
            qDebug() << "Check in ZIP: Manifest=" << m_zip.hasCurrentFile();
            if (m_zip.hasCurrentFile()) {
                QuaZipFile manifest(&m_zip);
                if(!manifest.open(QIODevice::ReadOnly)) {
                    qDebug() << "ZIP Error File can not be opened";
                }
                else {
                    quint16 uiZoomMin=20;
                    quint16 uiZoomMax=0;
                    char bBuffer[64];
                    qDebug() << "Manifest Size=" << manifest.size();
                    //while(!manifest.atEnd()) {
                    bool boolZoomFinished=false;
                    while(!boolZoomFinished) {
                        //qDebug() << manifest.pos() << "," << manifest.size();
                        quint16 uiValue;
                        qint64 iLineLength;
                        //iLineLength=manifest.readLine(bBuffer,sizeof(bBuffer));
                        iLineLength=manifest.readLine(bBuffer,sizeof(bBuffer));
                        qDebug()<<bBuffer << " / " << iLineLength;
                        QString sLine(bBuffer);
                        sLine=sLine.left(iLineLength-1);
                        if (sLine.left(4)=="zoom") {
                            qDebug() << "Line=" << sLine;
                            uiValue=sLine.mid(5).toInt();
                            qDebug() << "Value=" << uiValue;
                            if (uiValue>uiZoomMax) uiZoomMax=uiValue;
                            if (uiValue<uiZoomMin) uiZoomMin=uiValue;
                        }
                        else
                            boolZoomFinished=true;
                    }
                    manifest.close();
                    setMinimumZoomLevel(uiZoomMin);
                    setMaximumZoomLevel(uiZoomMax);
                    //
                    //Ermitteln des fileformates, Idealerweise mit Hilfe der nächsten Datei
                    m_zip.goToFirstFile();
                    m_zip.goToNextFile();
                    m_tileExt=m_zip.getCurrentFileName().right(3);
                    qDebug() << "m_tileExt=" << m_tileExt;
                }
            }
        }
        break;
    case SQLITEDB:
        bool ok;
        QString sQuery;
        int iMinZoom=10;  //Standard
        int iMaxZoom=18;  //Standard
        //
        m_sqlite=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","tintenbrotConnect"));
        qDebug() << "MainSqlite: m_offlinefile=" << m_offlinefile;
        m_sqlite->setDatabaseName(m_offlinefile);
        ok=m_sqlite->open();
        qDebug() << "SQLITE: Open DB=" << ok;
        if (!ok) {
            qDebug() << "lastError=" << m_sqlite->lastError();
        }
        //
        QSqlQuery query(*m_sqlite);
        //
        sQuery=QString("SELECT minzoom FROM info");
        qDebug() << "Query=" << sQuery;
        ok=query.prepare(sQuery);
        if (!ok) {
            qDebug() << "lastError=" << m_sqlite->lastError();
        }
        ok=query.exec();
        if (!ok) {
            qDebug() << "lastError=" << m_sqlite->lastError();
        }
        qDebug() << "query MINZOOM";
        if (query.next())
        {
            iMinZoom=query.value(0).toInt()+10;
            qDebug() << "minzoom=" << iMinZoom;
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
        break;
    }
    setTileSize(QSize(256,256));


    //SL_MAP_TYPE
    QList<QGraphicsGeoMap::MapType> types;
    types << QGraphicsGeoMap::StreetMap;    
    setSupportedMapTypes(types);

}

QGeoMappingManagerEngineOffline::~QGeoMappingManagerEngineOffline()
{
    if (m_sqlite != 0) {
        qDebug() << "SQLITE: Close DB";
        m_sqlite->close();
        delete m_sqlite;
    }
}

QGeoTiledMapReply* QGeoMappingManagerEngineOffline::getTileImage(const QGeoTiledMapRequest &request)
{
    //qDebug() << "getTileImage m_tileExt=" << m_tileExt;
    QGeoTiledMapReply* mapReply = 0;
    switch (m_FileFormat) {
    case OSZ:
        mapReply = new QGeoMapReplyOsz(m_offlinefile, m_tileExt, request, this);
        break;
    case SQLITEDB:
        mapReply = new QGeoMapReplySqlite(m_sqlite, request, this);
        break;
    }
    qDebug() << "getTileImage ";
    return mapReply;
}


