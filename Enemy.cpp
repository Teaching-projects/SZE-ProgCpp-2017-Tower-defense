#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, int speed, int gold, int x, int y){
	Name = name;
	Hp = hp;
	Speed = speed;
	Gold = gold;
	X = x;		//Ez a ketto a haromszog felso csucsat adja, ettol 10el van le es balra jobbra a masik ket pontja
	Y = y;
}
std::string Enemy::getName() const{
	return Name;
}
int Enemy::getHealth() const{
	return Hp;
}
int Enemy::getSpeed() const{
	return Speed;
}
int Enemy::getGold() const{
	return Gold;
}
void Enemy::HpLower(int value){
	Hp -= value;
}

void Enemy::kirajzol(){
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 0.2);
		glVertex2i(X, Y);
		glVertex2i(X - 20,Y - 20);
		glVertex2i(X + 20,Y - 20);
	glEnd();
}

void Enemy::Xnovel(){
	X += Speed;
}

int Enemy::GetX() const{
	return X;
}

int Enemy::GetY() const{
	return Y;
}

void Enemy::drawHP()
{
	if (Hp < 0) Hp = 0;
	std::string str =std::to_string(Hp);
	glRasterPos3i(X-25, Y-30, 0);
	for (unsigned i = 0; i<str.length(); i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)str[i]);
	}
}
