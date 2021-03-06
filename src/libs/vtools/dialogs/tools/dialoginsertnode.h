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
 **  @file   dialoginsertnode.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   21 3, 2017
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2017 Seamly2D project
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

#ifndef DIALOGINSERTNODE_H
#define DIALOGINSERTNODE_H

#include "dialogtool.h"
#include "../vpatterndb/vpiecenode.h"

namespace Ui
{
    class DialogInsertNode;
}

class DialogInsertNode : public DialogTool
{
    Q_OBJECT

public:
    explicit DialogInsertNode(const VContainer *data, quint32 toolId, QWidget *parent = nullptr);
    virtual ~DialogInsertNode();

    virtual void SetPiecesList(const QVector<quint32> &list) Q_DECL_OVERRIDE;

    quint32 GetPieceId() const;
    void    SetPieceId(quint32 id);

    VPieceNode GetNode() const;
    void       SetNode(const VPieceNode &node);

public slots:
    virtual void ChosenObject(quint32 id, const SceneObject &type) Q_DECL_OVERRIDE;

protected:
    virtual void CheckState() Q_DECL_FINAL;

private:
    Q_DISABLE_COPY(DialogInsertNode)
    Ui::DialogInsertNode *ui;

    VPieceNode m_node;
    bool m_flagItem;

    void CheckPieces();
    void CheckItem();
};

#endif // DIALOGINSERTNODE_H
