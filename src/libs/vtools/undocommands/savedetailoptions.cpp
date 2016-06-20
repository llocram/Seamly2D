/************************************************************************
 **
 **  @file   savedetailoptions.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   12 6, 2014
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Valentina project
 **  <https://bitbucket.org/dismine/valentina> All Rights Reserved.
 **
 **  Valentina is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Valentina is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Valentina.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "savedetailoptions.h"
#include "vpatternpiecedata.h"
#include "../tools/nodeDetails/vabstractnode.h"
#include "../../vwidgets/vmaingraphicsview.h"
#include "../ifc/xml/vabstractpattern.h"

#include <QGraphicsView>

//---------------------------------------------------------------------------------------------------------------------
SaveDetailOptions::SaveDetailOptions(const VDetail &oldDet, const VDetail &newDet, VAbstractPattern *doc,
                                     const quint32 &id, QGraphicsScene *scene, QUndoCommand *parent)
    : VUndoCommand(QDomElement(), doc, parent), oldDet(oldDet), newDet(newDet), scene(scene)
{
    setText(tr("save detail option"));
    nodeId = id;
}

//---------------------------------------------------------------------------------------------------------------------
SaveDetailOptions::~SaveDetailOptions()
{}

//---------------------------------------------------------------------------------------------------------------------
void SaveDetailOptions::undo()
{
    qCDebug(vUndo, "Undo.");

    QDomElement domElement = doc->elementById(nodeId);
    if (domElement.isElement())
    {
        SaveDet(domElement, oldDet);
        doc->RemoveAllChildren(domElement);
        for (int i = 0; i < oldDet.CountNode(); ++i)
        {
           VToolDetail::AddNode(doc, domElement, oldDet.at(i));
        }
        IncrementReferences(oldDet.Missing(newDet));
        emit NeedLiteParsing(Document::LiteParse);
    }
    else
    {
        qCDebug(vUndo, "Can't find detail with id = %u.", nodeId);
        return;
    }
}

//---------------------------------------------------------------------------------------------------------------------
void SaveDetailOptions::redo()
{
    qCDebug(vUndo, "Redo.");

    QDomElement domElement = doc->elementById(nodeId);
    if (domElement.isElement())
    {
        SaveDet(domElement, newDet);
        doc->RemoveAllChildren(domElement);

        QDomElement domData = doc->createElement(VAbstractPattern::TagData);
        doc->SetAttribute(domData, VAbstractPattern::AttrLetter, newDet.GetPatternPieceData().GetLetter());
        doc->SetAttribute(domData, VAbstractPattern::AttrName, newDet.GetPatternPieceData().GetName());
        for (int i = 0; i < newDet.GetPatternPieceData().GetMCPCount(); ++i)
        {
            MaterialCutPlacement mcp = newDet.GetPatternPieceData().GetMCP(i);
            QDomElement domMCP = doc->createElement(VAbstractPattern::TagMCP);
            doc->SetAttribute(domMCP, VAbstractPattern::AttrMaterial, int(mcp.m_eMaterial));
            doc->SetAttribute(domMCP, VAbstractPattern::AttrUserDefined, mcp.m_qsMaterialUserDef);
            doc->SetAttribute(domMCP, VAbstractPattern::AttrCutNumber, mcp.m_iCutNumber);
            doc->SetAttribute(domMCP, VAbstractPattern::AttrPlacement, int(mcp.m_ePlacement));
            domData.appendChild(domMCP);
        }
        domElement.appendChild(domData);

        for (int i = 0; i < newDet.CountNode(); ++i)
        {
           VToolDetail::AddNode(doc, domElement, newDet.at(i));
        }

        DecrementReferences(oldDet.Missing(newDet));
        emit NeedLiteParsing(Document::LiteParse);
    }
    else
    {
        qCDebug(vUndo, "Can't find detail with id = %u.", nodeId);
        return;
    }
}

//---------------------------------------------------------------------------------------------------------------------
bool SaveDetailOptions::mergeWith(const QUndoCommand *command)
{
    const SaveDetailOptions *saveCommand = static_cast<const SaveDetailOptions *>(command);
    SCASSERT(saveCommand != nullptr);
    const quint32 id = saveCommand->getDetId();

    if (id != nodeId)
    {
        return false;
    }

    newDet = saveCommand->getNewDet();
    return true;
}

//---------------------------------------------------------------------------------------------------------------------
int SaveDetailOptions::id() const
{
    return static_cast<int>(UndoCommand::SaveDetailOptions);
}

//---------------------------------------------------------------------------------------------------------------------
void SaveDetailOptions::SaveDet(QDomElement &domElement, const VDetail &det)
{
    doc->SetAttribute(domElement, AttrName, det.getName());
    doc->SetAttribute(domElement, VToolDetail::AttrSupplement, QString().setNum(det.getSeamAllowance()));
    doc->SetAttribute(domElement, VToolDetail::AttrClosed, QString().setNum(det.getClosed()));
    doc->SetAttribute(domElement, VToolDetail::AttrWidth, QString().setNum(det.getWidth()));
}
