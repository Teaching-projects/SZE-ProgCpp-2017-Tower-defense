#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string.h>


class Enemy {

private:
	std::string Name;
	int Hp;
	int Speed;
	int Gold;
	int X;
	int Y;

public:
	Enemy(std::string name, int Hp, int Speed, int Gold, int x, int y);
	std::string getName() const;
	int getHealth() const;
	int getSpeed() const;
	int getGold() const;
	void HpLower(int value);
	void kirajzol();
	void Xnovel();		//gyakorlatilag ez kell a mozgatáshoz, arréb rakjuk az Xet a Speeddel
	int GetX() const;
	int GetY() const;
	void drawHP();
};

#endif