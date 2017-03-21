#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

class Game {

private:
	int Money;
	int LifePoints;
	int ActualWave;
	bool PreparingTime;

public:
	Game(int Money, int LifePoints);
	int getMoney() const;
	int getLifePoints() const;
	int getActualWave() const;
	bool getPreparingTime();
	void setMoney(int money);
	void LifePointsDecrase();
	void WaveIncrease();
	void PrepTimeChange();

};

#endif