

#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

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



void drawTerrain() {
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	float rc = 15.0f;
	int numTeapots = 8;
	for(int i = 0; i<numTeapots; i++){
		float angle = (2.0f * M_PI / numTeapots) * i; // Calcula o ângulo de cada teapot
		float x = rc * sin(angle); // Posição X no círculo
		float z = rc * cos(angle); // Posição Z no círculo
	
		glPushMatrix();
			glColor3f(0.0f, 0.0f, 1.0f); // Define a cor azul para os teapots
			glTranslatef(x, 3.0f, z); // Posiciona o teapot ao redor do torus
			glRotatef(angle * (180.0f/M_PI) - 90.0f, 0.0f, 1.0f, 0.0f);  //passa o angle de radianos para graus
			glutSolidTeapot(3.0); // Desenha o teapot com tamanho 3.0
		glPopMatrix();
	}

	float ri = 35.0f;
	numTeapots = 16;
	for(int i = 0; i<numTeapots; i++){
		float angle = (2.0f * M_PI / numTeapots) * i; // Calcula o ângulo de cada teapot
		float x = ri * sin(angle); // Posição X no círculo
		float z = ri * cos(angle); // Posição Z no círculo
	
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f); // Define a cor vermelha para os teapots
			glTranslatef(x, 3.0f, z); // Posiciona o teapot ao redor do torus
			glRotatef(angle * (180.0f/M_PI), 0.0f, 1.0f, 0.0f);  //passa o angle de radianos para graus
			glutSolidTeapot(3.0); // Desenha o teapot com tamanho 3.0
		glPopMatrix();
	}

	glPushMatrix();  // Guarda a matriz de transformação atual
    	glColor3f(1.0f, 0.4f, 0.7f);  // Define a cor do torus (rosa)
    	glTranslatef(0.0f, 3.0f, 0.0f); // Move o torus para cima do plano
    	glutSolidTorus(1.5, 5.0, 30, 30); // (Raio interno, raio externo, fatias, anéis)
	glPopMatrix();  // Restaura a matriz original

	float r = 50.0f;
	srand(123);
	int min = 200, max = 250;
    int numArvores = min + (rand() % (max - min + 1));
	for(int i = 0; i<numArvores; i++){
		float x = 0.0f;
		float z = 0.0f;
		float yTronco = 1.5f;
		float yCopa = 3.5f;
		while(x*x + z*z <= r*r){
			x = -100 + rand()%201;
			z = -100 + rand()%201;
		}
		glPushMatrix();
			glColor3f(0.0f, 1.0f, 0.0f); // Define a cor verde para as copas
			glTranslatef(x, yCopa, z); // Posiciona a copa
			glRotatef(-90, 1.0f, 0.0f, 0.0f);
			glutSolidCone(2.0f, 5.0f, 20, 20); // Desenha a copa
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.647f, 0.165f, 0.165f); // Define a cor castanha para o tronco
			glTranslatef(x, yTronco, z); // Posiciona o tronco
			glRotatef(-90, 1.0f, 0.0f, 0.0f);
			glutSolidCone(0.2f, 5.0f, 20, 20); // Desenha o tronco
		glPopMatrix();
	}
    // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
}



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawTerrain();

// End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {

// put code to process regular keys in here
}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}


void init() {

// 	Load the height map "terreno.jpg"

// 	Build the vertex arrays

// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
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
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	init();	

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

