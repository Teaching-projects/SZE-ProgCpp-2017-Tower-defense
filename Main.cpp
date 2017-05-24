#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tower.h"
#include "Enemy.h"
#include "Game.h"


#define COLUMNS 810
#define ROWS 600
#define TOWER_UNIT 30
#define PATH_HEIGHT 60
#define FPS 40

using namespace std;

FILE *ptr_file;
std::vector<Tower> towers_vector;
std::vector<Enemy*> enemy_vector;
Game g1(100,20);
char c;						//torony lerakásnál switch feltétel hogy melyiket tegyük le
void drawMap();
int nulla = 0;
int i = 1;
int beker = 0;
bool tower_placeing = false;

int tower_placing_check(int x, int y){
	if (x < COLUMNS && x>0 && y<ROWS / 2 + PATH_HEIGHT / 2 + 2 * TOWER_UNIT && y> ROWS / 2 - PATH_HEIGHT / 2 - 2 * TOWER_UNIT)
	{
		if (y<ROWS / 2 + PATH_HEIGHT / 2 && y> ROWS / 2 - PATH_HEIGHT / 2)
		{
			return 0;
		}
		return 1;
	}
	else{
		return 0;
	}
}

void reshape_callback(int w, int h){	//ablak újraméretezésnél beállítja a viewportot
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0 , COLUMNS , 0.0 , ROWS, -1.0 , 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouse_control(int button, int state, int x, int y){
	int Tower_x, Tower_y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//cout << x << " " << y << endl;
		if (g1.getStatus()==1 && x<40 && x>2 && y<20 && y>5){		//Ha a WAVE-re kattintunk akkor elindul a hullám
			g1.StatusChange(2);
			g1.WaveIncrease();
			//cout << (*enemy_vector.begin())->getHealth();
			beker = 0;
		}

		else if (x < 70 && x>2 && y < 501 && y>488){				//ha a water toronyra kattintunk akkor a kövi belépésnél ha egy torony helyére kattintunk, akkor lerakja a tornyot
			tower_placeing = true;
			c = 'w';
			cout << "Kattintson egy ures negyzetre a 'water' torony elhelyezesehez\n";
		}
		else if (x < 60 && x>2 && y < 541 && y>528){				//ha a fire toronyra kattintunk akkor a kövi belépésnél ha egy torony helyére kattintunk, akkor lerakja a tornyot
			tower_placeing = true;
			c = 'f';
			cout << "Kattintson egy ures negyzetre a 'fire' torony elhelyezesehez\n";
		}
		else if (x < 68 && x>2 && y < 581 && y>568){				//ha az earth toronyra kattintunk akkor a kövi belépésnél ha egy torony helyére kattintunk, akkor lerakja a tornyot
			tower_placeing = true;
			c = 'e';
			cout << "Kattintson egy ures negyzetre az 'earth' torony elhelyezesehez\n";
		}

		else if (tower_placeing && tower_placing_check(x, y) == 1){
			//cout << x << " " << y << endl;
			Tower_x = x / TOWER_UNIT;
			Tower_x *= TOWER_UNIT;
			if (y == 330) y += 1;
			if (y == 270) y -= 1;
			Tower_y = (ROWS - y) / TOWER_UNIT;
			Tower_y *= TOWER_UNIT;
			switch (c){
			case 'w':
				if (g1.getMoney() >= 10){
					towers_vector.push_back(Tower("water", 110, 20, 10, Tower_x, Tower_y));
					g1.MoneyIncrease(-10);
					cout << "'water' torony letrehozva\n";
				}
				else{
					cout << "Nincs eleg penz a 'water' torony megvasarlasahoz\n";
				}
				break;

			case 'f':
				if (g1.getMoney() >= 20){
					towers_vector.push_back(Tower("fire", 100, 50, 13, Tower_x, Tower_y));	
					g1.MoneyIncrease(-20);
					cout << "'fire' torony letrehozva\n";
				}
				else{
					cout << "Nincs eleg penz a 'fire' torony megvasarlasahoz\n";
				}
				break;

			case 'e':
				if (g1.getMoney() >= 15){
					towers_vector.push_back(Tower("earth", 90, 40, 16, Tower_x, Tower_y));	
					g1.MoneyIncrease(-15);
					cout << "'earth' torony letrehozva\n";
				}
				else{
					cout << "Nincs eleg penz az 'earth' torony megvasarlasahoz\n";
				}
				break;
			}
			tower_placeing = false;
		}
		else{
			tower_placeing = false;
		}
	}
}

void display_callback(){
	int lovesjelzo = 1;
	vector<Enemy*>::iterator iter;
	i += 1;
	glClear(GL_COLOR_BUFFER_BIT);
	drawMap();
	g1.DrawString("WAVE: ", 2, ROWS - 20);
	g1.DrawString(std::to_string(g1.getActualWave()), 50, ROWS - 20);
	g1.DrawString("Life Points: ", COLUMNS / 2 - 50, ROWS - 20);
	g1.DrawString(std::to_string(g1.getLifePoints()), COLUMNS / 2 + 20, ROWS - 20);
	g1.DrawString("Money: ", COLUMNS - 90, ROWS - 20);
	g1.DrawString(std::to_string(g1.getMoney()), COLUMNS - 35, ROWS - 20);
	g1.DrawString("Water Tower: ", 2, 100);
	g1.DrawString("Cost: 10, Damage: 20, Range: 110, ROF: 10", 80, 100);
	g1.DrawString("Fire Tower: ", 2, 60);
	g1.DrawString("Cost: 20, Damage: 50, Range: 100, ROF: 13", 70, 60);
	g1.DrawString("Earth Tower: ", 2, 20);
	g1.DrawString("Cost 15, Damage: 40, Range: 90, ROF: 16", 77, 20);
	for (Tower j : towers_vector){
		j.kirajzol(TOWER_UNIT);
	}
	switch (g1.getStatus()){
		case 2:
			/*if (beker == 0){
				enemy_vector.push_back(&Enemy("asd", 200, 2, 5, 40, ROWS / 2 + 10));
				enemy_vector.push_back(&Enemy("asd", 200, 2, 5, 0, ROWS / 2 + 10));
				enemy_vector.push_back(&Enemy("asd", 200, 2, 5, -40, ROWS / 2 + 10));
				beker++;
			}*/
			for (vector<Enemy*>::iterator k = enemy_vector.begin(); k != enemy_vector.end();)
			{
				if ((*k)->getHealth() > 0 && (*k)->GetX() < COLUMNS - 20){
					(*k)->kirajzol();
					(*k)->Xnovel();
					/*for (Tower j : towers_vector){
						j.loves(&k, i);
					}*/
					glColor3f(0.0, 0.0, 0.0);
					(*k)->drawHP();
					k++;
				}
				else{					//ha a k-adik enemy élete nem több mint 0 vagy a elérte a végét akkor ide lépünk
					if ((*k)->getHealth() <= 0){				//ha az élet volt a gond
						g1.MoneyIncrease((*k)->getGold());		//növeljük a pénzünket
						k = enemy_vector.erase(k);				//és itt ki kell majd törölni a kadik elemet a vektorból
					}
					else
					{
						k = enemy_vector.erase(k);
						g1.LifePointsDecrase();		//egyébként az életünket kell csökkenteni mert végig ért az ellenfél
						if (g1.getLifePoints() <= 0){
							g1.StatusChange(3);
							break;
						}
					}
				}
			}
			for (vector<Tower>::iterator it = towers_vector.begin(); it != towers_vector.end();it++){
				iter = enemy_vector.begin();
				lovesjelzo = 1;
				while (iter != enemy_vector.end() && lovesjelzo == 1){
					if (it->loves(&*iter,i) == 1)
					{
						lovesjelzo = 0;
					}
					iter++;
				}
			}
			if (enemy_vector.empty() && g1.getLifePoints()>0){
				g1.StatusChange(1);
				//cout << "Atraktuk 1esre a jelzot\n";
			}
			break;
		case 3:
			if (beker != 2)
			{
				if (g1.getLifePoints() <= 0){
					beker = 2;
					cout << "\n---GAME OVER---\n";
				}
				else
				{
					beker = 2;
					cout << "\n---YOU WIN---\n";
				}
			}
			break;
	}
	glutSwapBuffers();
}

int beolvas(FILE *ptr_file)
{
	char buf[1000]; //ebbe tesszük a beolvasott karakterláncot
	rsize_t strmax = sizeof buf;
	char *next_token;
	const char s[2] = ";"; //elválasztó karakter
	char *token; //részsztring eleje
	std::string nev;
	int attr[5];
	int i = -1;

	if (fgets(buf, 1000, ptr_file) != NULL) //beolvasunk egy sort ha nem null jöhet a kinyerés
	{
		token = strtok_s(buf,s,&next_token); //elsõ token

		/* többi token */
		while (token != NULL)
		{
			if (i<0)
			{
				nev = token; //név sztring átadása
			}
			else
			{
				attr[i] = atoi(token); //intre konvertálás
			}
			i++;
			token = strtok_s(NULL, s, &next_token);
		}

	}
	else
	{
		return -1; //ha vége a fájlnak
	}

	/*átadjuk a külsõ változóknak az értéket*/
	for (int i = 0; i < 10; i++){
		//cout << i << endl;
		enemy_vector.push_back(new Enemy(nev, attr[0], attr[1], attr[2], attr[3]-(i*40), attr[4]));
	}
	return 0; //ha megtörtént az adatok kinyerése
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
		glVertex2i(x+TOWER_UNIT, y);
		glVertex2i(x+TOWER_UNIT, y+TOWER_UNIT);
		glVertex2i(x, y+TOWER_UNIT);
	glEnd();
}

void drawMap(){
	for (int x = 0; x < COLUMNS; x+=TOWER_UNIT)
	{
		for (int y = ROWS / 2 + PATH_HEIGHT / 2; y < ROWS / 2 + PATH_HEIGHT / 2 + 2 * TOWER_UNIT; y += TOWER_UNIT)
		{
			unit(x, y);
		}
	}
	for (int x = 0; x < COLUMNS; x += TOWER_UNIT)
	{
		for (int y = ROWS / 2 - PATH_HEIGHT / 2 - 2 * TOWER_UNIT; y < ROWS / 2 - PATH_HEIGHT / 2; y += TOWER_UNIT)
		{
			unit(x, y);
		}
	}
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3i(0, ROWS/2-PATH_HEIGHT/2, 0);
	glVertex3i(COLUMNS, ROWS/2-PATH_HEIGHT/2, 0);
	glVertex3i(COLUMNS, ROWS / 2 + PATH_HEIGHT / 2, 0);
	glVertex3i(0, ROWS / 2 + PATH_HEIGHT / 2, 0);
	glEnd();

}

void Idlecallback(){
	if (g1.getStatus() == 1 && beker == 0){
		if (!ptr_file){
			cout << "nem sikerult a fajl megnyitasa\n";
		}

		if (beolvas(ptr_file) == 0);
		else g1.StatusChange(3);
		//enemy_vector.push_back(new Enemy("asd", 200, 2, 5, 40, ROWS / 2 + 10));
		//enemy_vector.push_back( new Enemy("a", 200, 2, 5, 0, ROWS / 2 + 10));
		//enemy_vector.push_back(new Enemy("b", 200, 2, 5, -40, ROWS / 2 + 10));
		//enemy_vector.push_back(new Enemy("c", 200, 2, 5, -80, ROWS / 2 + 10));
		beker = 1;
		glutPostRedisplay();
	}
}


int main(int argc, char* argv[]) {
	fopen_s(&ptr_file,"input.txt", "r");
	//beolvassuk a fájlt és sorról sorra kinyerjük az adatokat
	glutInit(&argc, argv);	// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// Set up some memory buffers for our display
	glutInitWindowSize(COLUMNS, ROWS);	// Set the window size
	glutCreateWindow("Tower Defense");	// Create the window with the title ""
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	glutIdleFunc(Idlecallback);
	glutMouseFunc(mouse_control);
	init();
	glutMainLoop();
	//fclose(ptr_file);
	cout << "valami\n";
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