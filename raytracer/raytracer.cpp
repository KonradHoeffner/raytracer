#include "stdafx.h"
#include "Raytracer.h"

//double alpha = 100; // Winkel in Y - Richtung in Grad
//double beta = alpha*4/3; // Winkel in X-Richtung. Muss normalerweise alpha*fensterbreite/fensterhoehe sein

const Vector3d p1(-50,-50,-105);
const Vector3d p2(0,15,-105);
const Vector3d p3(50,-50,-105);

double abschwaechung(Szene& szene,double entfernung)
{
	return 1/(szene.abschwaechung_konstant+szene.abschwaechung_linear*entfernung+szene.abschwaechung_quadratisch*szene.abschwaechung_quadratisch);
}

// Interpoliert zwischen dem Vektor a und dem Vektor b. Eingaben und Ausgaben werden Normalisiert. t sollte zwischen 0 und 1 liegen.
Vector3d interpoliereVektoren(Vector3d a,Vector3d b, double t)
{
	a.normalize();
	b.normalize();
	if(t<0)
	{
		b=b*-1;
		t=-t;
	}
	Vector3d v = (1-t)*a+t*b;
	v.normalize();
	return v;
}

// Wird benötigt um aus den rechtwinkligen Vektoren a,b und c einen Sehstrahl bilden zu können
Vector3d interpoliereVektoren(Vector3d a,Vector3d b,Vector3d c,double s,double t)
{
	Vector3d d= interpoliereVektoren(a,b,s);
	Vector3d e = interpoliereVektoren(c,b,s);
	return interpoliereVektoren(d,e,t);
}

void print(Vector3d v)
{
	cout << "x= " << v.x << " y= " << v.y << " z= " << v.z << endl;
}

/*
// Bildet linear von 0...hoehe-1 auf -alpha/180 ... +alpha/180 ab
double pixelYToParameter(Szene& szene,int y)
{
	return alpha/180-alpha*y/(szene.bildHoehe-1)/90;
}
	
// Bildet linear von 0...breite-1 auf -beta/180 ... +beta/180 ab
double pixelXToParameter(Szene& szene, int x)
{
	return beta/180-beta*x/(szene.bildBreite-1)/90;
}
*/

/*
// Bildet linear von 0...hoehe-1 auf -alpha/2 ... + alpha/2 ab
double pixelYToWinkel(Szene& szene,int y)
{
	return alpha-2*alpha*y/(szene.bildHoehe-1);
}
	
// Bildet linear von 0...breite-1 auf -beta/180*pi ... +beta/180*pi ab
double pixelXToWinkel(Szene& szene, int x)
{
	return beta-beta*x/(szene.bildBreite-1);
}
*/

void zeichneDreiecke(Szene& szene)
{
		glBegin(GL_TRIANGLES);								
		//glColor3f(1,0,0);
		//glColor3f(1,0,0);
		for(list<Dreieck*>::iterator it=szene.dreiecke.begin();it!=szene.dreiecke.end();it++)
		//int i=0;i<szene.dreiecke.size();i++)
			{

			//Farbe* pFarbe = &bild[y][x];
		glColor3f((*it)->material->ambient.r,(*it)->material->ambient.g,(*it)->material->ambient.b);
		glVertex3f((*it)->p1.x,(*it)->p1.y,(*it)->p1.z);				
		glVertex3f((*it)->p2.x,(*it)->p2.y,(*it)->p2.z);				
		glVertex3f((*it)->p3.x,(*it)->p3.y,(*it)->p3.z);				
	
			
		/*glVertex3f(szene.dreiecke.at(i)->p1.x,szene.dreiecke.at(i)->p1.y,szene.dreiecke.at(i)->p1.z);				
		glVertex3f(szene.dreiecke.at(i)->p2.x,szene.dreiecke.at(i)->p2.y,szene.dreiecke.at(i)->p2.z);				
		glVertex3f(szene.dreiecke.at(i)->p3.x,szene.dreiecke.at(i)->p3.y,szene.dreiecke.at(i)->p3.z);				*/
		}
	glFlush();	
	glEnd();

}

void zeichneLichtquellen(Szene& szene)
{
	glColor3f(1,1,0);
	for(list<Lichtquelle*>::iterator it=szene.lichtquellen.begin();it!=szene.lichtquellen.end();it++)
	{
		glPushMatrix();
		glTranslatef((*it)->position.x,(*it)->position.y,(*it)->position.z);
		auxSolidSphere(0.1);
		glPopMatrix();
	}
}

void zeichneBoxen(Szene& szene, BoundingBox& box)
{
		//box.distanz = szene.boundingBox.distanz+100;
		float f = 1.0/(1+(box.distanz-szene.boundingBox.distanz)*(box.distanz-szene.boundingBox.distanz)/100);
		glColor3f(f,f,1);	
		glPushMatrix();
		glTranslatef((box.min.x+box.max.x)/2,(box.min.y+box.max.y)/2,(box.min.z+box.max.z)/2);
		auxWireBox(box.max.x-box.min.x,box.max.y-box.min.y,box.max.z-box.min.z);
		glPopMatrix();
		for(list<BoundingBox*>::iterator it=box.kindBoxen.begin();it!=box.kindBoxen.end();it++)
		{
			//assert(0);
			zeichneBoxen(szene,**it);
		}
}

void zeichneNormalen(Szene& szene)
{
	for(list<Dreieck*>::iterator it=szene.dreiecke.begin();it!=szene.dreiecke.end();it++)
	{
		glPushMatrix();
		Vector3d mittelPunkt = (*it)->getMittelpunkt();
		glTranslatef(mittelPunkt.x,mittelPunkt.y,mittelPunkt.z);
		//glScalef(0.2,0.2,0.2);
		glColor3f(1,1,1);
		Vector3d n = (*it)->getNormale(mittelPunkt,szene.kamera.getSichtVektor())*2;

		glBegin(GL_LINES);								
		
		glVertex3f(0,0,0);	
		glVertex3f(n.x,n.y,n.z);	

		glEnd();

		glPopMatrix();
glFlush();	
	}
}

void zeichneReflexion(Szene& szene)
{
	for(list<Dreieck*>::iterator it=szene.dreiecke.begin();it!=szene.dreiecke.end();it++)
	{
		glPushMatrix();
		Vector3d sichtVektor = szene.kamera.getSichtVektor();
		Vector3d mittelPunkt = (*it)->getMittelpunkt();
		glTranslatef(mittelPunkt.x,mittelPunkt.y,mittelPunkt.z);
		//glScalef(0.2,0.2,0.2);
		glColor3f(1,1,0);
		Vector3d n = (*it)->getNormale(mittelPunkt,szene.kamera.getSichtVektor());
		
		Vector3d r = 2*(n.dot(-sichtVektor))*n+sichtVektor;
		if((r).winkel(-sichtVektor)>(PI/2)) r*=-1;				
		glBegin(GL_LINES);								
		
		glVertex3f(0,0,0);	
		glVertex3f(r.x,r.y,r.z);	

		glEnd();

		glPopMatrix();
glFlush();	
	}
}

void zeichneBoxen(Szene&szene)
{
	//szene.boundingBox.erzeugeLeereKindBoxen();
	zeichneBoxen(szene,szene.boundingBox);
}


void raytrace(Szene& szene)
{
		//alpha = szene.kamera.fovy;
		//beta = szene.kamera.fovy*szene.bildBreite/szene.bildHoehe;
		cerr << "test";
		//Kamera kamera;
		cout << endl << endl;

		double winkelX;
		double winkelY;
		Vector3d sichtVektor = szene.kamera.getSichtVektor();
		Vector3d oben = szene.kamera.oben;
		Vector3d rechts = szene.kamera.getRechts();
		Vector3d sichtVektorGedrehtY;
		Vector3d sichtVektorGedreht;

		for(int y=0;y<szene.bildHoehe;y++)
		{
			winkelY = szene.kamera.fovy * (-0.5+double(y)/(szene.bildHoehe-1));
			sichtVektorGedrehtY = sichtVektor.rotate(rechts,winkelY);

			for(int x=0;x<szene.bildBreite;x++)
			{
				winkelX = - szene.kamera.fovx * (-0.5+double(x)/(szene.bildBreite-1));
		
				sichtVektorGedreht = sichtVektorGedrehtY.rotate(oben,winkelX);
				Farbe farbe =calculate(szene,szene.kamera.position,sichtVektorGedreht,STRAHL_REKURSIONS_TIEFE);
					
				farbe.cap();

	// OPEN GL DRAWING -----------------------------------------
				glBegin(GL_POINTS);								
				glColor3f(1,0,0);
				{

					//Farbe* pFarbe = &bild[y][x];
					//glColor3f(pFarbe->r,pFarbe->g,pFarbe->b);
					glColor3f(farbe.r,farbe.g,farbe.b);
					//glColor3f(1,1,1);
				
				glVertex3f(x,y,0.0f);				
				}
				//glFlush();	
				glEnd();
// ---------------------------------------------------------		
		}

	}
	
	//for(int i=0;i<500;i++) bild[200][i].gruen = 1;
	//cout << "Raytracing...";
//	calculate();
}

	Farbe calculate(Szene& szene,Vector3d& position,Vector3d& sichtVektor,int tiefe)
	{
		if(tiefe<=0) return szene.hintergrundfarbe;

		sichtVektor.normalize();
		//const Vector3d& position,const Vector3d& sehStrahl
		Vector3d schnittPunkt;
		
		SchnittEreignis* pSchnittEreignis = szene.boundingBox.getFirstSchnittEreignis(position,position+sichtVektor*1000,szene.kamera.clippingNear,szene.kamera.clippingFar);
		if(pSchnittEreignis)
		{
			Farbe ambient = pSchnittEreignis->pDreieck->material->ambient*szene.ambientehelligkeit;
			Farbe diffus(0,0,0);
			Farbe spiegelnd(0,0,0);
		

			for(list<Lichtquelle*>::iterator itLicht=szene.lichtquellen.begin();itLicht!=szene.lichtquellen.end();itLicht++)
			{
				// Nichts im Weg zur Lichtquelle
				if(!szene.boundingBox.isSchnitt(pSchnittEreignis->schnittPunkt,(*itLicht)->position,szene.kamera.clippingNear,szene.kamera.clippingFar))
				{
				// Diffus
				// l - Vektor zur Lichtquelle				
				Vector3d l = ((*itLicht)->position)-(pSchnittEreignis->schnittPunkt);
				l.normalize();
				// r - Richtung der Reflexion
				Vector3d r = 2*(pSchnittEreignis->normale.dot(l))*(pSchnittEreignis->normale)-l;
				//r.normalize();
				if(l.dot(pSchnittEreignis->normale)>0)
					diffus = diffus +
					pSchnittEreignis->pDreieck->material->diffus * 
					(*itLicht)->farbe * 
					l.dot(pSchnittEreignis->normale)*abschwaechung(szene,l.length())
					 
					;
				// Spiegelnd
				spiegelnd = spiegelnd + pSchnittEreignis->pDreieck->material->spiegelnd *
					(*itLicht)->farbe * 
					abschwaechung(szene,l.length())*
					max(0,
					pow(
					r.dot(-sichtVektor),
					pSchnittEreignis->pDreieck->material->glanz * 2
					)
					);					
				}
			}
			
			//diffus = pSchnittEreignis->pDreieck->material->diffus;
			//diffus.set(-1,0,0);
			Farbe farbe = ambient+diffus+spiegelnd;

			// Material ist transparent oder reflektiert?
			
			double undurchsichtigkeit= pSchnittEreignis->pDreieck->material->diffus.a;
			double mattigkeit= pSchnittEreignis->pDreieck->material->spiegelnd.a;
			double brechung = pSchnittEreignis->pDreieck->material->ambient.a;
			#if defined(TRANSPARENZ)
				if(undurchsichtigkeit!=1)
				{		
					if(brechung!=1)
					{
					
						Vector3d vorne  = (-sichtVektor).cross(pSchnittEreignis->normale);
						sichtVektor = sichtVektor.rotate(vorne,(1-brechung)*2*PI);
					}
					Farbe teilfarbe = calculate(szene,pSchnittEreignis->schnittPunkt,sichtVektor,tiefe-1);
					farbe = farbe*undurchsichtigkeit + teilfarbe* (1-undurchsichtigkeit);				

				};
			#endif
			//pSchnittEreignis->normale.normalize();
			#if defined(REFLEXION)	// Um Verzweigung zu beschränken wird nur entweder Transparenz oder Reflexion zugelassen
				if(undurchsichtigkeit==1&&mattigkeit!=1)
				{
					Vector3d reflexion = 2*(pSchnittEreignis->normale.dot(-sichtVektor))*(pSchnittEreignis->normale)+sichtVektor;
					//Vector3d reflexion = (-sichtVektor).rotate(pSchnittEreignis->normale,PI);
					//if((reflexion).winkel(-sichtVektor)>(PI/2)) reflexion	*=-1;				
					//reflexion.normalize();
					Farbe teilfarbe = calculate(szene,pSchnittEreignis->schnittPunkt,reflexion,tiefe-1);
					farbe = farbe*mattigkeit + teilfarbe* (1-mattigkeit);
				}
			#endif
			return (farbe);
		}
		// Kein Schnittpunkt gefunden
		return szene.hintergrundfarbe;
	}
	
	void trace()
	{
	}
