#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string.h>

class Game {

private:
	int Money;
	int LifePoints;
	int ActualWave;
	int Status;	//1 = jelenleg felkészülési idõ van,  2 = Folyik a wave azaz megy a harc, 3 = Game over vagy mert elfogyott az élet vagy mert elfogyott a wave

public:
	Game(int Money, int LifePoints);
	int getMoney() const;
	int getLifePoints() const;
	int getActualWave() const;
	int getStatus() const;
	void MoneyIncrease(int money);
	void LifePointsDecrase();
	void WaveIncrease();
	void StatusChange(int ujstatus);
	void DrawString(std::string szoveg, int x, int y);
};

#endif