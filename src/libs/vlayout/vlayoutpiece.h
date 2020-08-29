/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                            *
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
 **  @file   vlayoutdetail.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   2 1, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Seamly2D project
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

#ifndef VLAYOUTDETAIL_H
#define VLAYOUTDETAIL_H

#include <qcompilerdetection.h>
#include <QDate>
#include <QLineF>
#include <QMatrix>
#include <QPointF>
#include <QRectF>
#include <QSharedDataPointer>
#include <QString>
#include <QTypeInfo>
#include <QVector>
#include <QtGlobal>

#include "../ifc/xml/vabstractpattern.h"
#include "../vpatterndb/floatItemData/vpatternlabeldata.h"
#include "../vpatterndb/floatItemData/vpiecelabeldata.h"
#include "../vpatterndb/vcontainer.h"
#include "vabstractpiece.h"

class VLayoutPieceData;
class VLayoutPiecePath;
class QGraphicsItem;
class QGraphicsPathItem;
class VTextManager;

class VLayoutPiece :public VAbstractPiece
{
    Q_DECLARE_TR_FUNCTIONS(VLayoutPiece)
public:
                              VLayoutPiece();
                              VLayoutPiece(const VLayoutPiece &detail);

    virtual                  ~VLayoutPiece() Q_DECL_OVERRIDE;

    VLayoutPiece              &operator=(const VLayoutPiece &detail);

#ifdef Q_COMPILER_RVALUE_REFS
	VLayoutPiece                &operator=(VLayoutPiece &&detail) Q_DECL_NOTHROW;
#endif

	  void                      Swap(VLayoutPiece &detail) Q_DECL_NOTHROW;

    static VLayoutPiece       Create(const VPiece &piece, const VContainer *pattern);

    QVector<QPointF>          GetContourPoints() const;
    void                      SetCountourPoints(const QVector<QPointF> &points, bool hideMainPath = false);

    QVector<QPointF>          GetSeamAllowancePoints() const;
    void                      SetSeamAllowancePoints(const QVector<QPointF> &points, bool seamAllowance = true,
                                                     bool seamAllowanceBuiltIn = false);

    QVector<QPointF>          GetLayoutAllowancePoints() const;
    void                      SetLayoutAllowancePoints();

    QVector<QLineF>           getNotches() const;
    void                      setNotches(const QVector<QLineF> &notches);

    QVector<QVector<QPointF>> InternalPathsForCut(bool cut) const;
    QVector<VLayoutPiecePath> GetInternalPaths() const;
    void                      SetInternalPaths(const QVector<VLayoutPiecePath> &internalPaths);

    QPointF                   GetPieceTextPosition() const;
    QStringList               GetPieceText() const;
    void                      SetPieceText(const QString &qsName, const VPieceLabelData& data,
                                           const QFont& font,  const VContainer *pattern);

    QPointF                   GetPatternTextPosition() const;
    QStringList               GetPatternText() const;
    void                      SetPatternInfo(VAbstractPattern *pDoc, const VPatternLabelData& geom,
                                             const QFont& font, const VContainer *pattern);

    void                      SetGrainline(const VGrainlineData& geom, const VContainer *pattern);
    QVector<QPointF>          GetGrainline() const;

    QTransform                GetMatrix() const;
    void                      SetMatrix(const QTransform &matrix);

    qreal                     GetLayoutWidth() const;
    void                      SetLayoutWidth(const qreal &value);

    bool                      IsMirror() const;
    void                      SetMirror(bool value);

    void                      Translate(qreal dx, qreal dy);
    void                      Rotate(const QPointF &originPoint, qreal degrees);
    void                      Mirror(const QLineF &edge);

    int                       DetailEdgesCount() const;
    int                       LayoutEdgesCount() const;

    QLineF                    DetailEdge(int i) const;
    QLineF                    LayoutEdge(int i) const;

    int                       DetailEdgeByPoint(const QPointF &p1) const;
    int                       LayoutEdgeByPoint(const QPointF &p1) const;

    QRectF                    DetailBoundingRect() const;
    QRectF                    LayoutBoundingRect() const;
    qreal                     Diagonal() const;

    bool                      isNull() const;
    qint64                    Square() const;
    QPainterPath              ContourPath() const;

    QPainterPath              LayoutAllowancePath() const;

    Q_REQUIRED_RESULT QGraphicsItem     *GetItem(bool textAsPaths) const;

private:
    QSharedDataPointer<VLayoutPieceData> d_;

    QVector<QPointF>                     DetailPath() const;

    Q_REQUIRED_RESULT QGraphicsPathItem *GetMainItem() const;
    Q_REQUIRED_RESULT QGraphicsPathItem *GetMainPathItem() const;

    void                                 CreateInternalPathItem(int i, QGraphicsItem *parent) const;
    void                                 CreateLabelStrings(QGraphicsItem *parent, const QVector<QPointF> &labelShape,
                                                            const VTextManager &tm, bool textAsPaths) const;
    void                                 CreateGrainlineItem(QGraphicsItem *parent) const;

    template<class T>
    QVector<T> Map(const QVector<T>& points) const;

    QLineF                               Edge(const QVector<QPointF> &path, int i) const;
    int                                  EdgeByPoint(const QVector<QPointF> &path, const QPointF &p1) const;
};

Q_DECLARE_TYPEINFO(VLayoutPiece, Q_MOVABLE_TYPE);

#endif // VLAYOUTDETAIL_H
