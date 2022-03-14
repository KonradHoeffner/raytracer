#include "StdAfx.h"
#include "3DMath.h"

Vector3d Nullvektor(234234,234212,12323);

// Schnittpunkt zwischen Ebene und einem Liniensegment
// p1-3: 3 Punkte in der Ebene, L1 und 2: Start - und Zielpunkt der Linie

//COLLISION-------------------------------------------------------------------------
/*const int MaxPolys=100;
int AnzPolys=0;
Vector3d polys[MaxPolys][4];

void AddPoly(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d p4)
{
 Polys[AnzPolys][0]=p1;
 Polys[AnzPolys][1]=p2;
 Polys[AnzPolys][2]=p3;
 Polys[AnzPolys][3]=P4;
 AnzPolys++;
};*/


//-----------------------------------------------------------------------------------

/*bool IntersectPlaneLine(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt) 
{
double D,Dist1,Dist2; // Distanz von den beiden Randpunkten der Linie
Vector3d normale=((p2-p1)%(p3-p1)).normalized(); // Normalenvektor entsteht durch Kreuzprodukt der Aufspannvektoren, normalisiert
// Form: Ax+By+Cz+D=0 ,A,B,C = Normalenvektor[x,y,z], x,y,z = bel. Punkt von Ebene (hier p1) -> D=-n*p1
D=-(normale*p1); // D ist die Entfernung der Ebene vom Ursprung [0,0,0]
// nun in Ax+By+Cz+D einsetzten, Entfernung kommt heraus
Dist1=(normale*l1)+D;
Dist2=(normale*l2)+D;
if ((Dist1*Dist2)>0) return false;
schnittPunkt = (l1+(((l2-l1).normalized())*Dist1));
return true;
};*/

double distancePlanePoint(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d punkt)
{
double d; // d ist die Entfernung der Ebene vom Ursprung [0,0,0]
Vector3d normale=((p2-p1)%(p3-p1)).normalized(); // Normalenvektor entsteht durch Kreuzprodukt der Aufspannvektoren, normalisiert
// Form: Ax+By+Cz+D=0 ,A,B,C = Normalenvektor[x,y,z], x,y,z = bel. Punkt von Ebene (hier p1) -> D=-n*p1
d=-(normale*p1); 
return abs((normale*punkt)+d);
}

bool intersectPlaneLine(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt) 
{
double d,dist1,dist2; // Distanz von den beiden Randpunkten der Linie
Vector3d normale=((p2-p1)%(p3-p1)).normalized(); // Normalenvektor entsteht durch Kreuzprodukt der Aufspannvektoren, normalisiert
// Form: Ax+By+Cz+D=0 ,A,B,C = Normalenvektor[x,y,z], x,y,z = bel. Punkt von Ebene (hier p1) -> D=-n*p1
d=-(normale*p1); // D ist die Entfernung der Ebene vom Ursprung [0,0,0]
// nun in Ax+By+Cz+D einsetzten, Entfernung der Punkte L1 und L2 von der Ebene kommt heraus
dist1=(normale*l1)+d;
dist2=(normale*l2)+d;
cout << "dist1 " << dist1 << endl << "dist2 " << dist2 << endl;
// Beide auf derselben Seite der Ebene -> kein Schnittpunkt
if ((dist1*dist2)>0) return false;
// Geradengleichung P = L1 + t*L1L2
Vector3d l1l2 =(l2-l1);
l1l2.print();
// Geradengleichung P einsetzen in N*P + D = 0 -> N*(L1+t*L2) + D = 0 -> t = -(D+n*L1)/(L1L2*n)

double t = -(d+normale*l1)/(l1l2*normale);
cout << "t " << t << endl;
schnittPunkt = (l1)+t*l1l2;
cout << "Distanz Schnittpunkt - Ebene : " << normale*schnittPunkt+d<< endl;
//schnittPunkt = (l1+(((l2-l1).normalized())*dist1));
return true;
};

bool intersectPolygon3Line(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt)
{
 Vector3d v;
 if(!intersectPlaneLine(p1,p2,p3,l1,l2,v)) return false;
 Vector3d vP1=(p1-v).normalized();
 Vector3d vP2=(p2-v).normalized();
 Vector3d vP3=(p3-v).normalized();
 double angle=(vP1.winkel(vP2))+(vP2.winkel(vP3))+(vP3.winkel(vP1));
 /*char message[10];
 itoa(angle*100,message,10);
 MessageBox(NULL,message, "Winkelsumme",MB_ICONINFORMATION);*/
 if ((angle>359.95)&(angle<360.15)) angle=360;
 if (!((angle>(PI*2-0.1))&&(angle<PI*2+0.1))) return false;
 schnittPunkt = v;
 return true;
};

bool intersectDreieckLine(Dreieck& d,Vector3d l1,Vector3d l2,Vector3d& schnittPunkt)
{
	return intersectPolygon3Line(d.p1,d.p2,d.p3,l1,l2,schnittPunkt);
}

/*Vector3d IntersectPolygon4Line(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d p4,Vector3d L1,Vector3d L2)
{
 Vector3d r=IntersectPlaneLine(p1,p2,p3,L1,L2);
 if(r==Nullvektor) return Nullvektor;
 Vector3d vP1=(p1-r).normalized();
 Vector3d vP2=(p2-r).normalized();
 Vector3d vP3=(p3-r).normalized();
 Vector3d vP4=(p4-r).normalized();
 double angle=(vP1<vP2)+(vP2<vP3)+(vP3<vP4)+(vP4<vP1);
 if ((angle>357)&(angle<363)) angle=360;
 if (angle!=360) return Nullvektor;
 return r;
};*/


/*bool Collide(Vector3d L1,Vector3d L2)
{
 for(int i=0;i<AnzPolys;i++)
 {
  if (IntersectPolygon4Line(Polys[i][0],Polys[i][1],Polys[i][2],Polys[i][3],L1,L2)!=Nullvektor) return true;
 };
 return false;
};*/
