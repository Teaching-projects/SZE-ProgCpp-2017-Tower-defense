#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Enemy.h"


class Tower {

private:
	std::string Type;
	int Range;
	int Damage;
	int RateOfFire;
	int X;
	int Y;

public:
	Tower(std::string Type, int Range, int Damage, int RateOfFire, int x, int y);
	std::string getType() const;
	int getRange() const;
	int getDamage() const;
	int getRateOfFire() const;
	void kirajzol(int TOWER_UNIT) const;
	int getX() const;
	int loves(Enemy** e, int nulla);

};

#endif