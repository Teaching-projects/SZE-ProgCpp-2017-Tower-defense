#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <iostream>

class Tower{
private:
	std::string Type;
	int Range;
	int Damage;
	int RateOfFire;

public:
	Tower(std::string Type, int Range, int Damage, int RateOfFire);
	std::string getType() const;
	int getRange() const;
	int getDamage() const;
	int getRateOfFire() const;

};

#endif