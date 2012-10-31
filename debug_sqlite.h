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

#ifndef DEBUG_OSZ_H
#define DEBUG_OSZ_H

#include <QString>
#include <QDebug>


#define TILES_M		"Tiles"


#if 0
#define DBG_OSZ(module, msg)
#else
#define DBG_OSZ(module, msg) 							\
	qDebug() << "OSZ_offline:" << module << ":" << msg;
#endif

#endif // DEBUG_OSZ_H
