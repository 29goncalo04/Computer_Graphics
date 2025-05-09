#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {
// put code to draw cylinder in here
	float angle = 2*M_PI/slices;
	float halfHeight = height/2.0f;
	glBegin(GL_TRIANGLES);
		for (int i = 0; i<slices; i++){    //face lateral
			float theta1 = i*angle;
			float theta2 = (i+1)*angle;
			float x1 = radius*sin(theta1);
			float z1 = radius*cos(theta1);
			float x2 = radius*sin(theta2);
			float z2 = radius*cos(theta2);

			glColor3f(1.0f, 1.0f, 0.0f);        //      |---/
			glVertex3f(x1, -halfHeight, z1);    //      |  /
			glVertex3f(x2, halfHeight, z2);     //      | /
			glVertex3f(x1, halfHeight, z1);     //      |/

			glColor3f(0.5f, 0.5f, 0.0f);        //         /|     
			glVertex3f(x2, halfHeight, z2);    //         / |
			glVertex3f(x1, -halfHeight, z1);     //      /  |
			glVertex3f(x2, -halfHeight, z2);     //     /___|
		}
		for(int i = 0; i<slices; i++){ //tampa superior
			float theta1 = i*angle;
			float theta2 = (i+1)*angle;
			float x1 = radius*sin(theta1);
			float z1 = radius*cos(theta1);
			float x2 = radius*sin(theta2);
			float z2 = radius*cos(theta2);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0, halfHeight, 0);
			glVertex3f(x1, halfHeight, z1);
			glVertex3f(x2, halfHeight, z2);
		}
		for(int i = 0; i<slices; i++){ //tampa inferior
			float theta1 = i*angle;
			float theta2 = (i+1)*angle;
			float x1 = radius*sin(theta1);
			float z1 = radius*cos(theta1);
			float x2 = radius*sin(theta2);
			float z2 = radius*cos(theta2);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0, -halfHeight, 0);
			glVertex3f(x1, -halfHeight, z1);
			glVertex3f(x2, -halfHeight, z2);
		}
	glEnd();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}