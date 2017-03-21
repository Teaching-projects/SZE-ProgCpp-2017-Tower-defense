#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <string>


#define COLUMNS 810
#define ROWS 600
#define TOWER_UNT 30
#define PATH_HEIGHT 60
#define FPS 10

using namespace std;

void drawMap();

void reshape_callback(int w, int h){	//ablak újraméretezésnél beállítja a viewportot
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 , COLUMNS , 0.0 , ROWS, -1.0 , 1.0);
	glMatrixMode(GL_MODELVIEW);
}

int i = 20;
void display_callback(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawMap();
	glColor3f(0.4, 1, 0);
	glRectd(i,ROWS/2-20,i+40,ROWS/2+20);	//ettõl
	i += 10;
	if (i > 1000){
		i = 20;
	}						//eddig, ez "mozgatja" a piros négyzetet jobbra a pályán
	//nyilván ez igazából úgy van megoldva, hogy kirajzol minden egyes képfrissítésnél egy négyzetet, ami az fpsnek megfelelõen megy arréb
	glutSwapBuffers();
}

void timer_callback(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer_callback,0);
}

void init(){	//beállítja a háttérszínt
	glClearColor(0.6, 0.6, 1.0, 1.0);
}

void unit(int x, int y){	//kirajzol egy négyszöget x és y távolságra a bal alsó saroktól(origó)
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x,y);
		glVertex2i(x+TOWER_UNT, y);
		glVertex2i(x+TOWER_UNT, y+TOWER_UNT);
		glVertex2i(x, y+TOWER_UNT);
	glEnd();
}

void drawMap(){
	for (int x = 0; x < COLUMNS; x+=TOWER_UNT)
	{
		for (int y = ROWS / 2 + PATH_HEIGHT / 2; y < ROWS / 2 + PATH_HEIGHT / 2 + 2 * TOWER_UNT; y += TOWER_UNT)
		{
			unit(x, y);
		}
	}
	for (int x = 0; x < COLUMNS; x += TOWER_UNT)
	{
		for (int y = ROWS / 2 - PATH_HEIGHT / 2 - 2 * TOWER_UNT; y < ROWS / 2 - PATH_HEIGHT / 2; y += TOWER_UNT)
		{
			unit(x, y);
		}
	}
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3i(0, ROWS/2-PATH_HEIGHT/2, 0.0);
	glVertex3i(COLUMNS, ROWS/2-PATH_HEIGHT/2, 0.0);
	glVertex3i(COLUMNS, ROWS / 2 + PATH_HEIGHT / 2, 0.0);
	glVertex3i(0, ROWS / 2 + PATH_HEIGHT / 2, 0.0);
	glEnd();

}


int main(int argc, char* argv[]) {

	glutInit(&argc, argv);	// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// Set up some memory buffers for our display
	glutInitWindowSize(COLUMNS, ROWS);	// Set the window size
	glutCreateWindow("Tower Defense");	// Create the window with the title ""
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	init();
	glutMainLoop();
	return 0;
}
/*
	//DANI RÉSZE:--------------------------------------------------------------------------------
float a = -0.8;
float x = 0.0;
float y = 0.4;
float xV = 0.0;
float yV = 0.0;
bool wave = false;
bool fire = false;
int life = 100;
float lifeReduc = 0.1;
GLint gFramesPerSecond = 0;
void *currentfont;
std::string lifeCount;

void initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}


void FPS(void) {
	static GLint Frames = 0;         // frames averaged over 1000mS
	static GLuint Clock;             // [milliSeconds]
	static GLuint NextClock = 0;     // [milliSeconds]

	++Frames;
	Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
	if (Clock < NextClock) return;

	gFramesPerSecond = Frames / 1; // store the averaged number of frames per second

	NextClock = Clock + 1000; // 1000mS=1S in the future
	Frames = 0;
}

void timer(int value)
{
	const int desiredFPS = 120;
	glutTimerFunc(1000 / desiredFPS, timer, ++value);
	GLfloat dt = (gFramesPerSecond>0 ? 1.0 / gFramesPerSecond : 1.0);

	//put your specific idle code here
	//... this code will run at desiredFPS
	//gAngle += dt*360. / 8.; //rotate 360 degrees every 8 seconds
	//end your specific idle code here

	FPS(); //only call once per frame loop to measure FPS
	glutPostRedisplay(); // initiate display() call at desiredFPS rate
}


void setFont(void *font)
{
	currentfont = font;                      // Set the currentfont to the font
}

void drawstring(float x, float y, float z, std::string str)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (unsigned i = 0; i<str.length(); i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, (int)str[i]);
	}
}

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //képernyõtörlés

	setFont(GLUT_BITMAP_HELVETICA_12); //Font set to helvetica with size 12
	glColor3f(1.0, 1.0, 0.0);
	drawstring(-1.0, 0.9, 0.0, "WAVE");

	//std::string s = std::to_string(23);
	lifeCount = "LIFE " + std::to_string(life);

	setFont(GLUT_BITMAP_HELVETICA_12); //Font set to helvetica with size 12
	glColor3f(1.0, 1.0, 0.0);
	drawstring(0.0, 0.9, 0.0, lifeCount);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.2, 0.0);
	glVertex3f(-1.0, 0.2, 0.0);
	glEnd();

	if (life > 50){
		glBegin(GL_TRIANGLES);
		glColor3f(0.5, 1.0, 0.5);
		glVertex3f(a, 0.1, 0.0);
		glVertex3f(a - 0.05, 0.05, 0.0);
		glVertex3f(a + 0.05, 0.05, 0.0);
		glEnd();
	}

	if (life > 0){
		glBegin(GL_TRIANGLES);
		glColor3f(0.5, 1.0, 0.5);
		glVertex3f((a - 0.1), 0.1, 0.0);
		glVertex3f((a - 0.1) - 0.05, 0.05, 0.0);
		glVertex3f((a - 0.1) + 0.05, 0.05, 0.0);
		glEnd();
	}


	//torony
	glBegin(GL_POLYGON);
	glColor3f(0.4, 0.1, 0.9);
	glVertex3f(0.0, 0.4, 0.0);
	glVertex3f(0.1, 0.4, 0.0);
	glVertex3f(0.1, 0.3, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glEnd();

	//lövedék
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.9, 0.4);
	glVertex3f(x, y, 0.0);
	glVertex3f(x + 0.02, y, 0.0);
	glVertex3f(x + 0.02, y - 0.02, 0.0);
	glVertex3f(x, y - 0.02, 0.0);
	glEnd();

	if (fire == true)
	{
		x += xV;
		y += yV;
		if (y < 0.1)  //golyó ütközik
		{
			x = 0.0;
			y = 0.4;
			xV = (a + lifeReduc - x) / 40;
			yV = -0.3 / 40;
			life -= 10;
			if (life == 50){ lifeReduc -= 0.1; }
			if (life == 0){
				wave = false; fire = false; a = -0.8;
				x = 0.0;
				y = 0.4;
				life = 100;
				lifeReduc = 0.1;
			}
		}
	}

	if (wave == true)
	{
		a += 0.002;
		if (a >= 1.0) {
			wave = false; fire = false; a = -0.8;
			x = 0.0;
			y = 0.4;
		}
	}

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && wave == false && x>0 && x<40 && y>10 && y<30) {
		wave = true;
		fire = true;
		xV = (a - x) / 50;
		yV = -0.3 / 50;
		//glutPostRedisplay();
	}
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:                    // 27 is for Esc key
		exit(0);
		break;
	case 32:
		a -= 0.1;
		break;
	default:
		break;
	}
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world :D");
	//initialize();
	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(displayMe);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	initialize();
	glutMainLoop();
	return 0;
}*/