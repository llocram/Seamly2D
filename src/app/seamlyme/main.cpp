/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                             *
 *                                                                         *
 ***************************************************************************
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file   main.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   10 7, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include <QMessageBox> // For QT_REQUIRE_VERSION
#include <QTimer>

#include "tmainwindow.h"
#include "mapplication.h"
#include "../fervor/fvupdater.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(seamlymeicon);
  Q_INIT_RESOURCE(theme);
  Q_INIT_RESOURCE(icon);
  Q_INIT_RESOURCE(schema);
  Q_INIT_RESOURCE(flags);

  QT_WARNING_PUSH
  QT_WARNING_DISABLE_GCC("-Wzero-as-null-pointer-constant")
  QT_REQUIRE_VERSION(argc, argv, QT_VERSION_STR)
  QT_WARNING_POP

#ifndef Q_OS_MAC // supports natively
  InitHighDpiScaling(argc, argv);
#endif

  MApplication app(argc, argv);
  app.InitOptions();

  QTimer::singleShot(0, &app, &MApplication::ProcessCMD);

  return app.exec();
}
