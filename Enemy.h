#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>

class Enemy {

private:
	std::string Name;
	int Hp;
	int Speed;
	int Gold;

public:
	Enemy(std::string name, int Hp, int Speed, int Gold);
	std::string getName() const;
	int getHealth() const;
	int getSpeed() const;
	int getGold() const;
	void HpLower(int value);

};

#endif