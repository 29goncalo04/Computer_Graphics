#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>

#define _PI_ 3.14159

float alfa = 0.0f, beta = 0.0f, radius = 5.0f;
float camX, camY, camZ;

GLuint vertexCount, vertices, normals;

int timebase = 0, frame = 0;


void sphericalToCartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void prepareCilinder(float height, float radius, int sides) {

	float *v, *n;

	v = (float *)malloc(sizeof(float) * 4 * 3 * 3 * sides);
	n = (float *)malloc(sizeof(float) * 4 * 3 * 3 * sides);


	int vertex = 0;
	float delta = 2.0f * _PI_ / sides;

	for (int i = 0; i < sides; ++i) {
		// top
		// central point
		v[vertex*3 + 0] = 0.0f; 
		v[vertex*3 + 1] = height /2.0f;
		v[vertex*3 + 2] = 0.0f;

		n[vertex*3 + 0] = 0.0f; 
		n[vertex*3 + 1] = 1.0f;
		n[vertex*3 + 2] = 0.0f;

		vertex++;
		v[vertex*3 + 0] = radius * sin( i * delta);
		v[vertex*3 + 1] = height /2.0f;
		v[vertex*3 + 2] = radius * cos( i * delta);

		n[vertex*3 + 0] = 0.0f; 
		n[vertex*3 + 1] = 1.0f;
		n[vertex*3 + 2] = 0.0f;

		vertex++;
		v[vertex*3 + 0] = radius * sin( (i+1) * delta);
		v[vertex*3 + 1] = height /2.0f;
		v[vertex*3 + 2] = radius * cos( (i+1) * delta);

		n[vertex*3 + 0] = 0.0f; 
		n[vertex*3 + 1] = 1.0f;
		n[vertex*3 + 2] = 0.0f;

		// body
		// triangle 1
		vertex++;
		v[vertex*3 + 0] = radius * sin( (i+1) * delta);
		v[vertex*3 + 1] = height /2.0f;
		v[vertex*3 + 2] = radius * cos( (i+1) * delta);

		n[vertex*3 + 0] = sin( (i+1) * delta);
		n[vertex*3 + 1] = 0.0f;
		n[vertex*3 + 2] = cos( (i+1) * delta);

		vertex++;
		v[vertex*3 + 0] = radius * sin( i * delta);
		v[vertex*3 + 1] = height /2.0f;
		v[vertex*3 + 2] = radius * cos( i * delta);

		n[vertex*3 + 0] = sin( i * delta);
		n[vertex*3 + 1] = 0.0f;
		n[vertex*3 + 2] = cos( i * delta);

		vertex++;
		v[vertex*3 + 0] = radius * sin( i * delta);
		v[vertex*3 + 1] = -height /2.0f;
		v[vertex*3 + 2] = radius * cos( i * delta);

		n[vertex*3 + 0] = sin( i * delta);
		n[vertex*3 + 1] = 0.0f;
		n[vertex*3 + 2] = cos( i * delta);

		// triangle 2
		vertex++;
		v[vertex*3 + 0] = radius * sin( (i+1) * delta);
		v[vertex*3 + 1] = -height /2.0f;
		v[vertex*3 + 2] = radius * cos( (i+1) * delta);

		n[vertex*3 + 0] = sin( (i+1) * delta);
		n[vertex*3 + 1] = 0.0f;
		n[vertex*3 + 2] = cos( (i+1) * delta);

		vertex++;
		v[vertex*3 + 0] = radius * sin( (i+1) * delta);
		v[vertex*3 + 1] = height /2.0f;
		v[vertex*3 + 2] = radius * cos( (i+1) * delta);

		n[vertex*3 + 0] = sin( (i+1) * delta);
		n[vertex*3 + 1] = 0.0f;
		n[vertex*3 + 2] = cos( (i+1) * delta);

		vertex++;
		v[vertex*3 + 0] = radius * sin( i * delta);
		v[vertex*3 + 1] = -height /2.0f;
		v[vertex*3 + 2] = radius * cos( i * delta);

		n[vertex*3 + 0] = sin( i * delta);
		n[vertex*3 + 1] = 0.0f;
		n[vertex*3 + 2] = cos( i * delta);

		// base
		// central point
		vertex++;
		v[vertex*3 + 0] = 0.0f; 
		v[vertex*3 + 1] = -height /2.0f;
		v[vertex*3 + 2] = 0.0f;

		n[vertex*3 + 0] = 0.0f;
		n[vertex*3 + 1] = -1.0f;
		n[vertex*3 + 2] = 0.0f;

		vertex++;
		v[vertex*3 + 0] = radius * sin( (i+1) * delta);
		v[vertex*3 + 1] = -height /2.0f;
		v[vertex*3 + 2] = radius * cos( (i+1) * delta);

		n[vertex*3 + 0] = 0.0f;
		n[vertex*3 + 1] = -1.0f;
		n[vertex*3 + 2] = 0.0f;

		vertex++;
		v[vertex*3 + 0] = radius * sin( i * delta);
		v[vertex*3 + 1] = -height /2.0f;
		v[vertex*3 + 2] = radius * cos( i * delta);

		n[vertex*3 + 0] = 0.0f;
		n[vertex*3 + 1] = -1.0f;
		n[vertex*3 + 2] = 0.0f;

		vertex++;
	}

	vertexCount = vertex;

	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER,vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, v, GL_STATIC_DRAW);

	glGenBuffers(1, &normals);
	glBindBuffer(GL_ARRAY_BUFFER,normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, n, GL_STATIC_DRAW);


	free(v);
	free(n);

}


void drawCilinder() {
		
	glBindBuffer(GL_ARRAY_BUFFER,vertices);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,normals);
	glNormalPointer(GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}


void renderScene(void) {

	float pos[4] = {1.0, 1.0, 1.0, 0.0};
	float fps;
	int time;
	char s[64];

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	float white[] = {1.0, 1.0, 1.0, 1.0};
	float whiteS[] = {0.2, 0.2, 0.2, 1.0};
	float red[] = {1.0, 0.0, 0.0, 1.0};
	float green[] = {0.0, 1.0, 0.0, 1.0};
	float lpos[] = {1.0, 1.0, 1.0, 0.0};  // luz direcional (luz vem da (1,1,1))
	float ppos[] = {1.0, 1.0, 1.0, 1.0};  // luz posicional (luz está na (1,1,1))


	//lights
	glLightfv (GL_LIGHT0, GL_AMBIENT, whiteS);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, green);
	glLightfv (GL_LIGHT0, GL_SPECULAR, white);
	glLightfv (GL_LIGHT0, GL_POSITION, lpos);

	//materials
	glMaterialfv (GL_FRONT, GL_AMBIENT, red);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, red);
	glMaterialfv (GL_FRONT, GL_SPECULAR, red);
	glMaterialf (GL_FRONT, GL_SHININESS, 16);

	drawCilinder();

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME); 
	if (time - timebase > 1000) { 
		fps = frame*1000.0/(time-timebase); 
		timebase = time; 
		frame = 0; 
		sprintf(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	} 

// End of frame
	glutSwapBuffers();
}



void processKeys(int key, int xx, int yy) 
{
	switch(key) {
	
		case GLUT_KEY_RIGHT: 
						alfa -=0.1; break;

		case GLUT_KEY_LEFT: 
						alfa += 0.1; break;

		case GLUT_KEY_UP : 
						beta += 0.1f;
						if (beta > 1.5f)
							beta = 1.5f;
						break;

		case GLUT_KEY_DOWN: 
						beta -= 0.1f; 
						if (beta < -1.5f)
							beta = -1.5f;
						break;

		case GLUT_KEY_PAGE_DOWN : radius -= 0.1f; 
			if (radius < 0.1f)
				radius = 0.1f;
			break;

		case GLUT_KEY_PAGE_UP: radius += 0.1f; break;

	}
	sphericalToCartesian();

}



void initGL() {

	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// init
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	sphericalToCartesian();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	prepareCilinder(2,1,16);
}


int main(int argc, char **argv) {

// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");
		
// callback registration
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// keyboard callback registration
	glutSpecialFunc(processKeys);

#ifndef __APPLE__	
// init GLEW
	glewInit();
#endif	


	initGL();

	glutMainLoop();
	
	return 1;
}

