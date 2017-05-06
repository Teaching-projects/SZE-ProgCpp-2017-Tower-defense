#include "Game.h"

Game::Game(int money, int lifePoints){
	Money = money;
	LifePoints = lifePoints;
	ActualWave = 0;
	Status = 1;
}

int Game::getMoney() const{
	return Money;
}
int Game::getLifePoints() const{
	return LifePoints;
}
int Game::getActualWave() const{
	return ActualWave;
}
int Game::getStatus() const{
	return Status;
}

void Game::MoneyIncrease(int money){
	Money += money;
}
void Game::LifePointsDecrase(){
	LifePoints--;
}
void Game::WaveIncrease(){
	ActualWave++;
}
void Game::StatusChange(int ujstatus){	//nincs ellenõrizve, mert a default állapotra állításnál bajok lehetnek játék közben, ezért fontos hogy mindig a megfelelõ értéket kapja paraméterként
	this->Status = ujstatus;
}

void Game::DrawString(std::string szoveg, int x, int y)
{
	std::string str = szoveg;
	glRasterPos3i(x,y, 0);
	for (unsigned i = 0; i<str.length(); i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)str[i]);
	}
}

