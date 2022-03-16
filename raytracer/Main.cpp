#include "stdafx.h"
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library

import Szene;

//Farbe bild[szene.bildHoehe][szene.bildBreite];
Szene szene;
bool update = true;
bool kannRaytrace = false;

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=true;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=false;	// Fullscreen Flag Set To Fullscreen Mode By Default


void display()
{  // Display function will draw the image.
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin(GL_TRIANGLES);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0, 0.9 );
    glEnd(); 
    
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


int main( int argc, char** argv ) {  // Initialize GLUT and 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;
}

/*
void Projektion2D()
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glOrtho(0.0f,szene.bildBreite,szene.bildHoehe,0.0f,-1.0f,1.0f);	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void Projektion3D()
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluPerspective(szene.kamera.fovyGrad,((double)(szene.bildBreite))/(szene.bildHoehe),szene.kamera.clippingNear,szene.kamera.clippingFar);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	gluLookAt(szene.kamera.position.x,szene.kamera.position.y,szene.kamera.position.z,
		szene.kamera.ziel.x,szene.kamera.ziel.y,szene.kamera.ziel.z,
		 szene.kamera.oben.x, szene.kamera.oben.y, szene.kamera.oben.z);

}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport
	}


int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glDisable(GL_LIGHTING);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}


int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	if(update)
	{
	glDrawBuffer(GL_FRONT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	//glLoadIdentity();									// Reset The Current Modelview Matrix
	
	#if defined(VORSCHAU)
		Projektion3D();
		zeichneDreiecke(szene);
		zeichneLichtquellen(szene);
		zeichneBoxen(szene);
		//zeichneNormalen(szene);
		//zeichneReflexion(szene);
	#endif
	update = false;
	}

	if(kannRaytrace)
	{
	Projektion2D();
	raytrace(szene);
	kannRaytrace = false;
	}

}
// Szene laden -----------------------------------------------------------------------------------------
	
	if(strlen(lpCmdLine)!= 0) szene.fnSzene = lpCmdLine;
	getLogfile() << "Commandline:" << lpCmdLine << "\n";
	importSzene(szene);
	

	// Create Our OpenGL Window
	if (!CreateGLWindow("Raytracer",szene.bildBreite,szene.bildHoehe,32,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	importTriangulation(szene);
	test(szene);
	// -----------------------------------------------------------------------------------------------------
	
	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if (keys[VK_UP])
			{
				update= true;
				szene.kamera.position.z-=0.03;
				szene.kamera.ziel.z-=0.03;
				
			}
			if (keys[VK_DOWN])
			{
				update= true;
				szene.kamera.position.z+=0.03;
				szene.kamera.ziel.z+=0.03;
				
			}
			if (keys[VK_LEFT])
			{
				update= true;
				szene.kamera.position.x-=0.03;
				szene.kamera.ziel.x-=0.03;
				
			}
			if (keys[VK_RIGHT])
			{
				update= true;
				szene.kamera.position.x+=0.03;
				szene.kamera.ziel.x+=0.03;
				
			}

			if (keys[VK_RETURN])
			{
				kannRaytrace = true;
				
			}
}
*/
