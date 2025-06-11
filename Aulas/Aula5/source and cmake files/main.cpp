#include <stdio.h>
#include <ctime>
#include <cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;


void spherical2Cartesian() {

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



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

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

	
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {
	// printf("Vendor: %s\n", glGetString(GL_VENDOR));
	// printf("Renderer: %s\n", glGetString(GL_RENDERER));
	// printf("Version: %s\n", glGetString(GL_VERSION));

	// printf("\nUse Arrows to move the camera up/down and left/right\n");
	// printf("Home and End control the distance from the camera to the origin");
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

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
