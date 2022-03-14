#include "stdafx.h"

// p1... sind Punkte auf der Ebene
bool intersectPlaneLine(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt);
bool intersectPolygon3Line(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt);
bool intersectDreieckLine(Dreieck& d,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt);

double distancePlanePoint(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d punkt);
/*Vector3d IntersectPolygon3Line(Polygon p,Vector3d l1,Vector3d l2);
Vector3d IntersectPolygon4Line(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d p4,Vector3d L1,Vector3d L2);*/
