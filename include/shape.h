//
// Created by huacheng on 11/17/21.
//

#ifndef NCUBE_SHAPE_H
#define NCUBE_SHAPE_H

#define CuboidDim 3
#define CuboidNodes 8
typedef double ShapePrecision;
typedef unsigned int ShapeIndex;

extern const ShapePrecision LinearCuboidNaNbCoeff[CuboidDim*CuboidDim*CuboidNodes*CuboidNodes];
const ShapePrecision * DefaultLinearCuboidNaNb(ShapeIndex,ShapeIndex,ShapeIndex,ShapeIndex);
typedef struct
{
    ShapePrecision Scale[CuboidDim];
    ShapePrecision * (*NaNb)(ShapeIndex,ShapeIndex,ShapeIndex,ShapeIndex);
} LinearCuboid;

typedef struct
{
    ShapePrecision * GCX;
    ShapePrecision * (*NaNb)(ShapeIndex,ShapeIndex,ShapeIndex,ShapeIndex);
} LinearCap;



#endif //NCUBE_SHAPE_H
